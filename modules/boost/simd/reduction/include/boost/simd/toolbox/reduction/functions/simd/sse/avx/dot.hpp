//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_DOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_DOT_HPP_INCLUDED

#include <boost/simd/toolbox/reduction/functions/dot.hpp>
#include <boost/simd/include/functions/simd/sum.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>

// /////////////////////////////////////////////////////////////////////////////
// // Implementation when type  is arithmetic_
// /////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::dot_, boost::simd::tag::avx_,
                                    (A0),
                                    ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                    ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
      {
        A0 r = _mm256_dp_pd(a0, a1, 0x3); 
        return r[0]; 
      }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::dot_, boost::simd::tag::avx_,
                                    (A0),
                                    ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                    ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type; 
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
      {
        A0 r = _mm256_dp_ps(a0, a1, 0xFF); 
        return r[0]+r[4]; 
      }
  };

} } }
#endif
