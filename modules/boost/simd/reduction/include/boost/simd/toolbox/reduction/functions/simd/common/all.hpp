//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_ALL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_SIMD_COMMON_ALL_HPP_INCLUDED
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/toolbox/reduction/functions/all.hpp>
#include <boost/simd/include/functions/genmask.hpp>
#include <boost/simd/include/functions/hmsb.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( all_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::scalar_of<A0>::type sA0;
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return result_type(hmsb(genmask(a0)) == (1ull << meta::cardinal_of<A0>::value)-1);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( all_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<logical_<A0>,X>))
                            )
  {
    typedef typename meta::scalar_of<typename A0::type>::type sA0; 
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename A0::type type; 
      return result_type(hmsb(genmask(a0)) == (1ull << meta::cardinal_of<type>::value)-1);
    }
  };
} } }

#endif
