
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

#include <boost/simd/toolbox/operator/functions/logical_and.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>
#include <boost/simd/include/functions/genmask.hpp>
#include <boost/simd/include/functions/mask2logical.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( logical_and_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A1>,X>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return mask2logical(b_and(genmask(a0), genmask(a1)));
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( logical_and_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<logical_<A0>,X>))
                              ((simd_<logical_<A1>,X>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return mask2logical(b_and(genmask(a0), genmask(a1)));
    }
  };

  //TODO why the assert is never taken ?
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( logical_and_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<fundamental_<A0>,X>))
                              ((simd_<fundamental_<A1>,X>))
                            )
  {
    typedef A0 result_type;
    inline A0 operator()(const A0 &,  const A1&) const
    {
       BOOST_ASSERT_MSG( (true),
                    "you cannot logical_and a standard simd vector and a simd logical vector"
                        );
       return Zero<result_type>(); 
    }
  };    
} } }


#endif
