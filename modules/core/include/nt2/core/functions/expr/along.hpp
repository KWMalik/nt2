//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ALONG_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ALONG_HPP_INCLUDED

#include <nt2/core/functions/along.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/reshape.hpp>
//#include <nt2/include/functions/alongsstride.hpp>
#include <nt2/table.hpp>

// TO DO return properly an expression !
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::along_, tag::cpu_,
                              (A0)(A1)(A2),
                              (ast_<A0>)
                              (scalar_<arithmetic_<A1> > )
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename A0::extent_type                extt_t;
    typedef typename A0::value_type             value_type;
    typedef typename A0::index_type             index_type; 
    typedef typename meta::strip<extt_t>::type       ext_t;
    typedef table <value_type, index_type> result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& ind, A2 const& dim) const
     {
      ext_t sizee = a0.extent();     
      sizee[dim-1] = 1;
       switch(dim)
         {
         case 1 : return nt2::reshape(a0(ind, nt2::_), sizee);
         case 2 : return nt2::reshape(a0(nt2::_, ind, nt2::_), sizee);
         case 3 : return nt2::reshape(a0(nt2::_, nt2::_, ind, nt2::_), sizee);        
//          case 4 : return nt2::reshape(a0(nt2::_, nt2::_, nt2::_, ind, nt2::_), sizee);        
//          case 5 : return nt2::reshape(a0(nt2::_, nt2::_, nt2::_, nt2::_, ind), sizee);
         default : return a0;  
         }; 
     }
  }; 

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::along_, tag::cpu_,
                              (A0)(A1)(A2),
                              (ast_<A0>)
                              (ast_<A1>)
                              (scalar_<integer_<A2> > )
                              )
  {
    typedef typename A0::extent_type                extt_t;
    typedef typename A0::value_type             value_type;
    typedef typename A0::index_type             index_type; 
    typedef typename meta::strip<extt_t>::type       ext_t;
    typedef table <value_type, index_type> result_type; 
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& inds, A2 const& dim) const
     {
      ext_t sizee = a0.extent();     
      sizee[dim-1] = numel(inds);
       switch(dim)
         {
         case 1 : return nt2::reshape(a0(inds, nt2::_), sizee);
         case 2 : return nt2::reshape(a0(nt2::_, inds, nt2::_), sizee);
         case 3 : return nt2::reshape(a0(nt2::_, nt2::_, inds, nt2::_), sizee);        
//          case 4 : return nt2::reshape(a0(nt2::_, nt2::_, nt2::_, ind, nt2::_), sizee);        
//          case 5 : return nt2::reshape(a0(nt2::_, nt2::_, nt2::_, nt2::_, ind), sizee);
         default : return a0;  
         }; 
     }
  }; 
} }

#endif
