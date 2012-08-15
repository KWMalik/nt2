//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_LINEAR_INTERP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_LINEAR_INTERP_HPP_INCLUDED

#include <nt2/core/functions/linear_interp.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sx_multiplies.hpp>
#include <nt2/include/functions/sx_plus.hpp>
#include <nt2/include/functions/sx_fma.hpp>
#include <nt2/include/functions/fma.hpp> 

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linear_interp_, tag::cpu_,
                              (A0)(A1)(A2),
                              (generic_<floating_<A0> >)
                              (generic_<floating_<A1> >)
                              (generic_<floating_<A2> >)
                              )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& dx, A1 const& a, A2 const& b ) const
    {
      return fma(dx, a, oneminus(dx)*b);
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linear_interp_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                              )
  {
    typedef typename meta::call<tag::oneminus_(const A0&)>::type                       T0;
    typedef typename meta::call<tag::sx_multiplies_(T0,const A2&)>::type               T1;
    typedef typename meta::call<tag::sx_fma_(const A0&,const A1&, T1)>::type  result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& dx, A1 const& a, A2 const& b) const
    {
      return sx_fma(dx, a, sx_multiplies(oneminus(dx), b));
    }
  };

   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::linear_interp_, tag::cpu_,
                              (A0)(A1)(A2),
                              (generic_<floating_<A0> >)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                              )
  { 
    typedef typename meta::call<tag::oneminus_(const A0&)>::type                        T0;
    typedef typename meta::call<tag::multiplies_(T0,const A2&)>::type                   T1;
    typedef typename meta::call<tag::multiplies_(const A0&,const A1&)>::type            T2;
    typedef typename meta::call<tag::sx_plus_(T2,T1)>::type                    result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& dx, A1 const& a, A2 const& b) const
    {
      return sx_plus(dx*a, oneminus(dx)*b);
    }
  };
 
} }

#endif
