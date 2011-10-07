//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ILIFFE_BUFFER_HPP
#define NT2_CORE_CONTAINER_MEMORY_ILIFFE_BUFFER_HPP

//==============================================================================
/**
  * \file
  * \brief Defines and implements the \c nt2::memory::iliffe_buffer class
  **/
//==============================================================================

#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <nt2/sdk/memory/config.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/meta/add_pointers.hpp>
#include <nt2/core/container/memory/adapted/iliffe_buffer.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /**
    * \brief Hierarchically allocated memory buffer.
    *
    * iliffe_buffer models the NT2 Buffer concept by handling a segment of memory
    * defined by a set of base indices, sizes and padding strategy. This segment
    * is then accessible through the Buffer interface.
    *
    * iliffe_buffer uses the Iliffe vector allocation scheme to allow fast
    * multi-dimensionnal access by precomputing index tables of nD pointers. This
    * precomputation allows the memory access to be performed as a simple chain
    * of operator[] calls. Base indices also have no runtime cost as they are
    * precomputed as offset on the original addresses.
    *
    * \tparam Dimensions  Number of dimensions stored in this Buffer
    * \tparam Type        Type of values stored in this Buffer
    * \tparam Padding     Padding strategy for this Buffer
    * \tparam Allocator   Memory allocator used by this Buffer
   **/
  //============================================================================
  template< std::size_t Dimensions
          , typename Type
          , typename Padding
          , typename Allocator
          >
  struct iliffe_buffer
  {
    typedef typename Allocator::template rebind<memory::byte>::other  allocator;

    //==========================================================================
    /** Type of the value stored in current buffer                            */
    //==========================================================================
    typedef typename Allocator::value_type                    value_type;

    //==========================================================================
    /** Type of the pointer giving access to the stored values                */
    //==========================================================================
    typedef typename Allocator::pointer                       pointer;

    //==========================================================================
    /** Type of the pointer giving access to the stored values as constants   */
    //==========================================================================
    typedef typename Allocator::const_pointer                 const_pointer;

    //==========================================================================
    /** Type of the iterator to the iliffe_buffer values                      */
    //==========================================================================
    typedef typename Allocator::pointer                       iterator;

    //==========================================================================
    /** Type of the const_iterator to the iliffe_buffer values                */
    //==========================================================================
    typedef typename Allocator::const_pointer                 const_iterator;

    //==========================================================================
    /** Type of reference to a value                                          */
    //==========================================================================
    typedef typename Allocator::reference                     reference;

    //==========================================================================
    /** Type of reference to a constant value                                 */
    //==========================================================================
    typedef typename Allocator::const_reference               const_reference;

    //==========================================================================
    /** Type representing an amount of values                                 */
    //==========================================================================
    typedef typename Allocator::size_type                     size_type;

    //==========================================================================
    /** Type representing an offset between values                            */
    //==========================================================================
    typedef typename Allocator::difference_type               difference_type;

    //==========================================================================
    /** Type of the pointer to buffer storage area                            */
    //==========================================================================
    typedef typename meta::add_pointers<Type,Dimensions>::type  data_type;

    //==========================================================================
    /** Type of the pointer to buffer indices                                 */
    //==========================================================================
    typedef typename meta::add_pointers<Type,Dimensions-1>::type&  sub_data_type;

    //==========================================================================
    /** Type of the constant pointer to buffer indices                        */
    //==========================================================================
    typedef typename meta::add_pointers<Type const,Dimensions-1>::type& const_sub_data_type;

    //==========================================================================
    /**
      * Default constructor yields an empty iliffe buffer
     **/
    //==========================================================================
    iliffe_buffer(Allocator const&  a = Allocator())
      : data_(0), begin_(0), end_(0), numel_(0), alloc_(a) {}

    //==========================================================================
    /**
      * Initializes a Iliffe buffer by allocating memory for its own ownership.
      * For a given number of dimensions \c N , the constructor will allocate
      * enough memory to store N indexing tables and the actual data size as
      * defined by the sizes and padding parameters.
      *
      * \param szs FusionRandomAccessSequence containing the dimensions of the
      *            buffer
      * \param bss FusionRandomAccessSequence containing the base indices of the
      *            buffer
      * \param p   Padding strategy of the buffer
      * \param a   Allocator instance used by the buffer
     **/
    //==========================================================================
    template<typename Sizes, typename Bases> inline void
    initialize( Sizes const&      szs
              , Bases const&      bss
              , Padding const&    p
              )
    {
      // Stores the outer base index required for proper deallocation
      idx_ = boost::fusion::at_c<Dimensions-1>(bss);

      // Computes the number of values to store
      size_type numel = slice<1>(szs,p);

      // If non-empty ...
      if(numel != 0)
      {
        // Computes the number of bytes for the data and the indexing
        size_type data_size = numel * sizeof(value_type);
        size_type idx_size  = index_size(szs,p);

        // Fix numel_ to store the proper number of aligned data
        numel_ = idx_size+data_size;

        // Allocate that much bytes
        memory::byte* ptr = alloc_.allocate(numel_);

        // Points to the begining of the data block
        begin_ = reinterpret_cast<value_type*>(ptr+idx_size);
        end_   = begin_ + numel;

        // Recursively fills out the index
        data_ = link( ptr, begin_ - boost::fusion::at_c<0>(bss)
                    , szs , bss, p
                    , boost::mpl::int_<Dimensions>()
                    );
      }
    }

    //==========================================================================
    /**
      * Constructs a Iliffe buffer from an existing data block without any transfer
      * of ownership. In this case, the only memory allocated and deallocated are
      * the indexing tables. The actual data are shared and neither require allocation
      * nor deallocation.
      *
      * \param szs FusionRandomAccessSequence containing the dimensions of the
      *            buffer
      * \param bss FusionRandomAccessSequence containing the base indices of the
      *            buffer
      * \param p   Padding strategy of the buffer
      * \param shared Memory block to share
      * \param a   Allocator instance used by the buffer
     **/
    //==========================================================================
    template<typename Sizes, typename Bases>
    void initialize ( Sizes const&      szs
                    , Bases const&      bss
                    , Padding const&    p
                    , value_type*       data
                    )

    {
      // Stores the outer base index required for proper deallocation
      idx_ = boost::fusion::at_c<Dimensions-1>(bss);

      // Computes the number of values to store
      size_type numel = slice<1>(szs,p);

      // If non-empty and if we dont try to share empty data
      if(data && numel)
      {
        // Setup other pointer and size information
        numel_ = index_size(szs,p);
        begin_ = data;
        end_   = begin_ + numel;

        // Recursively fills out the index
        data_ = link( alloc_.allocate(numel_)
                    , begin_ - boost::fusion::at_c<0>(bss)
                    , szs, bss, p
                    , boost::mpl::int_<Dimensions>()
                    );
      }
    }

    //==========================================================================
    /**
      * Destructs a iliffe_buffer by deallocating its data segment if it actually
      * owns it and its indexing tables.
     **/
    //==========================================================================
    ~iliffe_buffer()
    {
      if(data_)
        alloc_.deallocate(reinterpret_cast<memory::byte*>(data_ + idx_), numel_);
    }

    //==========================================================================
    /**
      * Random access operator to the underlying indexed values.
      * \param i outer dimension index to access.
      * \return Current sub-index table at offset i.
     **/
    //==========================================================================
    sub_data_type       operator[](std::ptrdiff_t i)       { return data_[i]; }
    const_sub_data_type operator[](std::ptrdiff_t i) const { return data_[i]; }

    //==========================================================================
    /**
      * Give access to the beginning of the values stored in the buffer.
      * begin() and end() are both returning un-biased pointer, making them
      * suitable for a classical, STL like treatment.
      *
      * \return A pointer pointing to the beginning of the buffer segment
      * holding values.
     **/
    //==========================================================================
    pointer       begin()       { return begin_; }
    const_pointer begin() const { return begin_; }

    //==========================================================================
    /**
      * Give access to the end of the values stored in the buffer.
      * \return A pointer pointing past the last element of the buffer segment
      * holding values.
     **/
    //==========================================================================
    pointer       end()         { return end_; }
    const_pointer end() const   { return end_; }

    protected:

    //==========================================================================
    /*
     * index_size computes the number of bytes required to store the index table
     * of the Iliffe vector
     */
    //==========================================================================
    template<class Seq> inline std::size_t
    index_size(Seq const& s, Padding const& p) const
    {
      // The index section is the sum of all required index aligned
      // globally on the boundary value provided by p
      return align_on( index_size(s,boost::mpl::size_t<2>()), p.value() );
    }

    template<class Seq,std::size_t Index> inline std::size_t
    index_size(Seq const& s, boost::mpl::size_t<Index> const&) const
    {
        return  slice<Index>(s,no_padding()) * sizeof(void*)
              + index_size(s,boost::mpl::size_t<Index+1>());
    }

    template<class Seq> inline std::size_t
    index_size(Seq const& s, boost::mpl::size_t<Dimensions> const&) const
    {
      return slice<Dimensions>(s,no_padding()) * sizeof(void*);
    }

    //==========================================================================
    /*
     * link performs the indexing of the Iliffe vector
     */
    //==========================================================================
    template<typename Sizes, typename Bases, int D>
    typename meta::add_pointers<Type,D>::type
    link( memory::byte*   p
        , value_type*     base
        , Sizes const&    szs
        , Bases const&    bss
        , Padding const&  pd
        , boost::mpl::int_<D> const&
        )
    {
      // Retrieve the current pointer in the index
      typedef typename meta::add_pointers<Type,D>::type ptr_type;
      ptr_type ptr = reinterpret_cast<ptr_type>(p);

      // Retrieve the underlying indexed part
      size_type offset = slice<D>(szs,pd)*sizeof(void*);
      ptr[0] = link(p+offset,base,szs,bss,pd,boost::mpl::int_<D-1>());

      // Fill out the remaining indices
      size_type local_size = stride<D-1>(szs,pd);
      for(std::size_t i=1; i < slice<D>(szs,pd);++i)
        ptr[i] = ptr[i-1] + local_size;

      // Rebase the index
      ptr -= boost::fusion::at_c<D-1>(bss);
      return ptr;
    }

    template<typename Sizes, typename Bases>
    typename meta::add_pointers<Type,2>::type
    link( memory::byte*   p
        , value_type*     base
        , Sizes const&    szs
        , Bases const&    bss
        , Padding const&  pd
        , boost::mpl::int_<2> const&
        )
    {
      // Retrieve the current pointer in the index
      typedef typename meta::add_pointers<Type,2>::type ptr_type;
      ptr_type ptr = reinterpret_cast<ptr_type>(p);

      // Points to the beginning of the data block
      ptr[0] = base;

      // Fill out the remaining indices
      std::size_t local_size = stride<1>(szs,pd);
      for(std::size_t i=1; i < slice<2>(szs,pd);++i)
        ptr[i] = ptr[i-1] + local_size;

      // Rebase the index
      ptr -= boost::fusion::at_c<1>(bss);
      return ptr;
    }

    private:
    data_type       data_;
    pointer         begin_, end_;
    std::ptrdiff_t  idx_;
    std::size_t     numel_;
    allocator       alloc_;
  };

  //============================================================================
  /**
   * iliffe_buffer is specialized for 1D case to not allocate any indexing table
   **/
  //============================================================================
  template< typename Type
          , typename Padding
          , typename Allocator
          >
  struct iliffe_buffer<1,Type,Padding,Allocator>
  {
    typedef typename Allocator::template rebind<memory::byte>::other  allocator;
    typedef typename Allocator::value_type      value_type;
    typedef typename Allocator::pointer         iterator;
    typedef typename Allocator::const_pointer   const_iterator;
    typedef typename Allocator::reference       reference;
    typedef typename Allocator::const_reference const_reference;
    typedef typename Allocator::size_type       size_type;
    typedef typename Allocator::difference_type difference_type;
    typedef value_type*                         data_type;

    iliffe_buffer(Allocator const&  a = Allocator())
    : data_(0), begin_(0), end_(0), sharing_(false),  alloc_(a) {}

    template<typename Sizes, typename Bases>
    void initialize ( Sizes const&      szs
                    , Bases const&      bss
                    , Padding const&    p
                    )
    {
      size_type numel = slice<1>(szs,p);
      if(numel != 0)
      {
        begin_  = alloc_.allocate( numel );
        end_    = begin_ + numel;
        data_   = begin_ - boost::fusion::at_c<0>(bss);
      }
    }

    template<typename Sizes, typename Bases>
    void initialize ( Sizes const&      szs
                    , Bases const&      bss
                    , Padding const&    p
                    , iterator const& data
                    )
    {
      size_type numel = slice<1>(szs,p);
      if(numel != 0 && data)
      {
        begin_  = data;
        end_    = begin_ + numel;
        data_   = data - boost::fusion::at_c<0>(bss);
        sharing_ = true;
      }
    }

    ~iliffe_buffer()
    {
      if(!sharing_) alloc_.deallocate( begin(), end() - begin() );
    }

    reference       operator[](std::ptrdiff_t i)       { return data_[i]; }
    const_reference operator[](std::ptrdiff_t i) const { return data_[i]; }

    iterator        begin()       { return begin_;  }
    iterator        end()         { return end_;    }

    const_iterator  begin() const { return begin_;  }
    const_iterator  end()   const { return end_;    }

    private:
    data_type data_,begin_,end_;
    bool      sharing_;
    Allocator alloc_;
  };
} }

#endif
