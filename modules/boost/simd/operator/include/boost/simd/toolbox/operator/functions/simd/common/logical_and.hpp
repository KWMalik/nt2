//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_LOGICAL_AND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_LOGICAL_AND_HPP_INCLUDED

#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::logical_and_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A1>,X>))
                            )
  {
    typedef typename meta::boolean<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return is_nez(a0) & is_nez(a1);
    }
  };
} } }


#endif
