//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_TYPED_BOOL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_SCALAR_TYPED_BOOL_HPP_INCLUDED

#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/include/constants/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::typed_bool_ , tag::cpu_ , (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              (target_< scalar_< fundamental_<A1> > >)
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&) const
    {
      return a0 ? Allbits<A1>() : Zero<A1>();
    }
  }; 
} } }

#endif
