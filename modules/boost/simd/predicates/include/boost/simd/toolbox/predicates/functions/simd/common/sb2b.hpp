//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_COMMON_SB2B_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_SIMD_COMMON_SB2B_HPP_INCLUDED
#include <boost/simd/toolbox/predicates/functions/sb2b.hpp>
#include <boost/simd/include/functions/if_else_zero.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <nt2/sdk/details/type_id.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(sb2b_, tag::cpu_,
                       (A0)(X),
                       ((simd_<fundamental_<A0>,X>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return if_else_zero(a0, One<A0>());
    }
  };

   BOOST_SIMD_FUNCTOR_IMPLEMENTATION(sb2b_, tag::cpu_,
                       (A0)(X),
                       ((simd_<logical_<A0>,X>))
                      )
  {
    typedef typename A0::type result_type;
    
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      std::cout << "nt2::type_id<A0>() " << nt2::type_id<A0>() << std::endl;
      std::cout << "nt2::type_id<result_type>() " << nt2::type_id<result_type>() << std::endl;
      //      return result_type(); 
      return if_else_zero(a0, boost::simd::One<result_type>());
    }
  }; 
} } }
#endif
