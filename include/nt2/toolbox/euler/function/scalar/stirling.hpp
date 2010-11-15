//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_EULER_FUNCTION_SCALAR_STIRLING_HPP_INCLUDED
#define NT2_TOOLBOX_EULER_FUNCTION_SCALAR_STIRLING_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/real.hpp>

#include <nt2/include/functions/polevl.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/toolbox/euler/function/scalar/constants.hpp>
#include <nt2/toolbox/trigonometric/function/scalar/impl/constants.hpp>

namespace nt2 { namespace functors
{

  //  no special validate for stirling

  /////////////////////////////////////////////////////////////////////////////
  // Compute stirling(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////
  // Gamma function computed by Stirling's formula,
  //  sqrt(2 pi) x^(x-.5) exp(-x) (1 + 1/x P(1/x))
  //  The polynomial STIR is valid for 33 <= x <= 172.
  //   template<class Info>
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<stirling_,tag::scalar_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      if (is_nan(a0)) return Nan<A0>(); 
      if (a0 > Stirlinglargelim<A0>()) return Inf<A0>(); 
//       static const boost::array<A0, 3 > stirpoly = {{
// 	  -2.705194986674176E-003f,
// 	  3.473255786154910E-003f,
// 	  8.333331788340907E-002f,
// 	}};
      A0 w = rec(a0);
      w = fma(w, polevl(w, stirpol<A0, A0>::sp()), One<A0>());
      A0 y = exp(-a0);
      if(is_eqz(y)) return Inf<A0>(); 
      if( a0 > Stirlingsplitlim<A0>() )
	{ /* Avoid overflow in pow() */
	  const A0 v = pow(a0,fma(Half<A0>(),a0,-Quarter<A0>()));
	  y *= v;
	  y *= v;
	}
      else
	{
	  y *= pow( a0, a0 - Half<A0>() );
	}
      y *= Sqrt_2pi<A0>()*w;
      return y;
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<stirling_,tag::scalar_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      boost::result_of<meta::floating(A0)>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename NT2_CALL_RETURN_TYPE(1)::type type;
      return stirling(type(a0));
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
