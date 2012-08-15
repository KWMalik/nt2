//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_RATIO_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_RATIO_HPP_INCLUDED

#include <nt2/core/functions/ratio.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/sx.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ratio_, tag::cpu_,
                              (A0)(A1)(A2),
                              (generic_<floating_<A0> >)
                              (generic_<floating_<A1> >)
                              (generic_<floating_<A2> >)
                              )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& x, A1 const& a, A2 const& b ) const
    {
      return (b-x)/(b-a); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ratio_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (unspecified_<A1>)
                              (unspecified_<A2>)
                              )
  {
    typedef typename meta::call<tag::sx_(nt2::tag::minus_, const A2&,const A0&)>::type N;
    typedef typename meta::call<tag::sx_(nt2::tag::minus_, const A2&,const A1&)>::type D;
    typedef typename meta::call<tag::sx_(nt2::tag::divides_, N, D)>::type   result_type;
    
    BOOST_FORCEINLINE result_type operator()(A0 const& x, A1 const& a, A2 const& b) const
    {
      return sx<nt2::tag::divides_>(sx<nt2::tag::minus_>(b, x), sx<nt2::tag::minus_>(b, a));
    }
  };

 
} }

#endif
