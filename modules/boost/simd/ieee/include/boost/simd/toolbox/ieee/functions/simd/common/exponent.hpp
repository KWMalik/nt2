//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_EXPONENT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_SIMD_COMMON_EXPONENT_HPP_INCLUDED
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/include/functions/shri.hpp>
#include <boost/simd/include/functions/exponentbits.hpp>
#include <boost/simd/include/functions/is_nez.hpp>
#include <boost/simd/include/functions/is_invalid.hpp>
#include <boost/simd/include/constants/maxexponent.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/functions/bitwise_and.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( exponent_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename dispatch::meta::as_integer<A0, signed>::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type             s_type;
      typedef typename meta::scalar_of<result_type>::type sint_type;
      const int nmb= int(Nbmantissabits<s_type>());
      const result_type x = shri(exponentbits(a0), nmb);
      return if_zero_else( is_invalid(a0), x-if_else_zero(is_nez(a0), Maxexponent<A0>())); 
    }
  };
} } }


#endif
