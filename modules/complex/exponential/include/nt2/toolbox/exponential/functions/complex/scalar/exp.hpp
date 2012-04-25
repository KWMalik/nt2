//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_SCALAR_EXP_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_SCALAR_EXP_HPP_INCLUDED
#include <nt2/include/functions/exp.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <complex>
#include <cmath>

namespace nt2 { namespace ext
{
//   NT2_FUNCTOR_IMPLEMENTATION( exp_, tag::cpu_
//                             , (A0)
//                             , (scalar_< complex_<floating_<A0> > >)
//                             )
//   {
//     typedef A0 result_type;
//     NT2_FUNCTOR_CALL(1)
//     {
//       return static_cast<result_type>(std::exp(a0));
//     }
//   };
  NT2_FUNCTOR_IMPLEMENTATION( exp_, tag::cpu_
                            , (A0)
                            , (scalar_< imaginary_<floating_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type             rtype; 
    typedef typename meta::as_complex<rtype>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 c, s;
      sincos(a0, s, c); 
      return result_type(c, s); 
    }
  };
} }


#endif
