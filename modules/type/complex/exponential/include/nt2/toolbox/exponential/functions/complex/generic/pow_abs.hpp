//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_POW_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_COMPLEX_GENERIC_POW_ABS_HPP_INCLUDED
#include <nt2/toolbox/exponential/functions/pow_abs.hpp>
#include <nt2/include/functions/pow_abs.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/arg.hpp>
#include <nt2/include/functions/pure.hpp>
#include <nt2/include/functions/logical_not.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/sdk/simd/logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)
                            , (generic_< complex_<floating_<A0> > >)
                              (generic_< complex_<floating_<A0> > >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return exp(a1*log(nt2::abs(a0))); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< complex_<floating_<A0> > >)
                                (generic_< floating_<A1> >)
                            )
  { 
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::pow_abs(nt2::abs(a0), a1); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< complex_<floating_<A0> > >)
                                (generic_< dry_<floating_<A1> > >)
                            )
  { 
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return pow_abs(a0, nt2::real(a1)); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< floating_<A0> >)
                                (generic_< complex_<floating_<A1> > >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        typedef typename meta::as_dry<A0>::type dtype; 
        return nt2::exp(a1*nt2::log(dtype(nt2::abs(a0)))); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< dry_ < floating_<A0> > > )
                                (generic_< complex_<floating_<A1> > >)
                            )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return nt2::exp(a1*nt2::log(nt2::abs(a0))); 
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< complex_<floating_<A0> > >)
                              (generic_< imaginary_<floating_<A1> > >)
                              )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return nt2::exp(a1*nt2::log(nt2::abs(a0))); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< imaginary_<floating_<A0> > >)
                              (generic_< complex_<floating_<A1> > >)
                              )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return nt2::exp(a1*nt2::log(nt2::abs(a0))); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< imaginary_<floating_<A0> > >)
                              (generic_< floating_<A1> >)
                              )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return nt2::exp(a1*nt2::log(nt2::abs(a0))); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< imaginary_<floating_<A0> > >)
                              (generic_< dry_ < floating_<A1> > >)
                              )
  {
    typedef typename meta::as_dry<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return nt2::exp(nt2::real(a1)*nt2::log(nt2::abs(a0))); 
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                              ,  (generic_< floating_<A0> >)
                              (generic_< imaginary_<floating_<A1> > >)
                              )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    typedef typename meta::as_dry<A0>::type dtype; 
    NT2_FUNCTOR_CALL(2)
      {
        return nt2::exp(a1*nt2::log(dtype(nt2::abs(a0)))); 
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                              ,  (generic_< dry_ < floating_<A0> > > )
                              (generic_< imaginary_<floating_<A1> > >)
                              )
  {
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return nt2::exp(a1*nt2::log(nt2::abs(a0))); 
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_abs_, tag::cpu_
                              , (A0)(A1)
                              ,  (generic_< dry_ < floating_<A0> > > )
                              (generic_< dry_<floating_<A1> > >)
                              )
  {
    typedef typename meta::as_dry<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return nt2::exp(a1*nt2::log(nt2::abs(a0))); 
      }
  };     
} }


#endif
