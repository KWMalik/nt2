//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_LOGICAL_XOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_LOGICAL_XOR_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/toolbox/arithmetic/functions/logical_xor.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/include/functions/bitwise_xor.hpp>
#include <boost/simd/include/functions/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( logical_xor_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                              ((simd_<arithmetic_<A1>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_cast<result_type>(b_xor(genmask(a0), genmask(a1)));
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( logical_xor_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>,boost::simd::tag::avx_>))
                              ((simd_<logical_<A1>,boost::simd::tag::avx_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_cast<result_type>(b_xor(bitwise_cast<typename A0::type>(a0), bitwise_cast<typename A1::type>(a1)));
    }
  };  
} } }


#endif
#endif
