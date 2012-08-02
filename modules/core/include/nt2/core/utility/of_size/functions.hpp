//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_OF_SIZE_FUNCTIONS_HPP_INCLUDED
#define NT2_CORE_UTILITY_OF_SIZE_FUNCTIONS_HPP_INCLUDED

#include <nt2/core/utility/of_size.hpp>

namespace nt2
{
  namespace result_of
  {
    template< class S1, class S2> struct max;

    template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t A)
            , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t B)
            >
    struct max< of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, A)>
              , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, B)>
              >
    {
      #define M0(z,n,t)                                           \
      ((BOOST_PP_CAT(A,n)==-1) || (BOOST_PP_CAT(B,n)==-1))  ? -1  \
                  : ((BOOST_PP_CAT(A,n) >= BOOST_PP_CAT(B,n)) ?   \
                      BOOST_PP_CAT(A,n) : BOOST_PP_CAT(B,n)       \
                    )                                             \
      /**/
      typedef of_size_<BOOST_PP_ENUM(NT2_MAX_DIMENSIONS, M0,~)> type;
      #undef M0

      typedef of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, A)> a_t;
      typedef of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, B)> b_t;

      template<int N>
      static void call( type& that
                      , a_t const& a, b_t const& b
                      , boost::mpl::int_<N> const&
                      )
      {
        std::size_t sa = boost::fusion::at_c<N-1>(a);
        std::size_t sb = boost::fusion::at_c<N-1>(b);
        boost::fusion::at_c<N-1>(that) = std::max(sa,sb);

        call(that,a,b,boost::mpl::int_<N-1>());
      }

      static void call(type&,a_t const&,b_t const&,boost::mpl::int_<0> const&)
      {}

      static void call(type& that, a_t const& a, b_t const& b)
      {
        call(that,a,b,boost::mpl::int_<type::static_size>());
      }
    };
  }

  template< BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t A)
          , BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, std::ptrdiff_t B)
          >
  BOOST_FORCEINLINE
  typename  result_of::max
            < of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, A)>
            , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, B)>
            >::type
  max ( of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, A)> const& a
      , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, B)> const& b
      )
  {

    typedef  result_of::max
              < of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, A)>
              , of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, B)>
              > max_t;

    typename max_t::type that;
    max_t::call(that,a,b);
    return that;
  }
}

#endif
