//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_R_MATHLIB_FUNCTIONS_SCALAR_PPOIS_HPP_INCLUDED
#define NT2_TOOLBOX_R_MATHLIB_FUNCTIONS_SCALAR_PPOIS_HPP_INCLUDED
#include <nt2/sdk/meta/upgrade.hpp>

extern "C"{
  extern double ppois ( double,double,int,int );
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::r_mathlib::tag::ppois_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_<arithmetic_<A0> >)(scalar_<arithmetic_<A1> >)(scalar_<arithmetic_<A2> >)(scalar_<arithmetic_<A3> >)
                            )
  {
    typedef typename meta::result_of<meta::floating(A0)>::type result_type;
    inline result_type
    operator()(A0 const& a0, A1 const& a1, A2 const& a2, A3 const& a3)  const 
    {
      typedef result_type                         base;
      typedef typename meta::upgrade<base>::type  type;
      return static_cast<result_type>(::ppois(double(a0), double(a1), int(a2), int(a3)));
    }
  };
} }


#endif
