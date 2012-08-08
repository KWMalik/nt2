/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_CAUPDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_CAUPDF_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/caupdf.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/atanpi.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/globalall.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caupdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1) { return nt2::rec(nt2::oneplus(nt2::sqr(a0)))*Invpi<A0>(); }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caupdf_, tag::cpu_
                              , (A0)(A1)
                              , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                             )
  {
    typedef A0 result_type;     
    NT2_FUNCTOR_CALL(2) { return nt2::rec(nt2::oneplus(nt2::sqr(a0-a1)))*Invpi<A0>(); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caupdf_, tag::cpu_
                            , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                               (generic_< floating_<A1> >)
                               (generic_< floating_<A2> >)  
                            )
  {
    typedef A0 result_type;     
    NT2_FUNCTOR_CALL(3)
      {
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a2)), "scale parameter must be positive"); 
        return a2*caupdf(a0/a2, a1);
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caupdf_, tag::cpu_
                             , (A0)(A1)
                             , (ast_<A0>)
                             (ast_<A1>)
                             )
  {
    typedef typename meta::scalar_of<A0>::type                                                     sA0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::minus_>,const A0&,const A1&)>::type  T1;
    typedef typename meta::call<tag::sqr_(T1)>::type                                                T2;
    typedef typename meta::call<tag::oneplus_(T2)>::type                                            T3;
    typedef typename meta::call<tag::rec_(T3)>::type                                                T4;
    typedef typename meta::call<tag::multiplies_(T4, sA0)>::type                           result_type;
    
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::rec(nt2::oneplus(sqr(nt2::bsxfun(nt2::functor<tag::minus_>(),a0,a1))))*Invpi<sA0>(); 
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caupdf_, tag::cpu_
                            , (A0)(A1)(A2)
                              , (generic_< floating_< A0 > > )
                               (ast_< A1 >)
                               (generic_< floating_< A2 > >)  
                            )
  {
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::multiplies_>,const A0&,const A2&)>::type T0; 
    typedef typename meta::call<tag::caupdf_(T0, const A1&)>::type                                      T1;
    typedef typename meta::call<tag::sqrt_(const A2&)>::type                                            T2;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::multiplies_>,T2,T1)>::type      result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a2)), "scale parameter must be positive"); 
      return nt2::bsxfun(nt2::functor<tag::multiplies_>(),
                         nt2::sqrt(a2),
                         caupdf(nt2::bsxfun(nt2::functor<tag::divides_>(), a0-a1, a2)
                         ); 
    }
  };


} }

#endif
