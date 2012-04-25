//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_LOGICAL_AND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_LOGICAL_AND_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( logical_and_, boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>, boost::simd::tag::sse_>))
                              ((simd_<arithmetic_<A1>, boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_cast<result_type>(b_and(genmask(a0), genmask(a1)));
    }
  }; 
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( logical_and_, boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_<logical_<A0>, boost::simd::tag::sse_>))
                              ((simd_<logical_<A1>, boost::simd::tag::sse_>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename A0::type type;
      return bitwise_cast<result_type>(b_and(bitwise_cast<type>(a0), bitwise_cast<type>(a1)));
    }
  };
} } }


#endif
#endif
