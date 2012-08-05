/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_NORMINV_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_NORMINV_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/norminv.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/erfcinv.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/sqrt_2.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norminv_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return  -Sqrt_2<A0>().*erfcinv(Two<A0>()*a0);
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norminv_, tag::cpu_
                              , (A0)(A1)
                              , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                             )
  {
    typedef A0 result_type;     
    NT2_FUNCTOR_CALL(2)
    {
      return norminv(a0)+a1; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norminv_, tag::cpu_
                            , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                               (generic_< floating_<A1> >)
                               (generic_< floating_<A2> >)  
                            )
  {
    typedef A0 result_type;     

    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(nt2::colvect(a2))), "sigma(s) must be positive"); 
      return fma(norminv(a0), a2, a1); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norminv_, tag::cpu_
                             , (A0)(A1)
                             , (unspecified_<A0>)
                             (unspecified_<A1>)
                             )
  {
    typedef typename meta::scalar_of<A0>::type                                                     sA0;
    typedef typename meta::call<tag::norminv_(const A0&)>::type                                     T1;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::plus_>,T1,const A1&)>::type result_type;
    
    NT2_FUNCTOR_CALL(2)
    {
      return bsxfun(nt2::functor<tag::plus_>(), norminv(a0), a1); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norminv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (unspecified_<A0>)
                              (unspecified_<A1>)
                              (unspecified_<A2>) 
                             )
  {
    typedef typename meta::scalar_of<A0>::type                                                      sA0;
    typedef typename meta::call<tag::erfcinv_(const A0&)>::type                                      T1;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::multiplies_>,T1,const A2&)>::type     T3;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::plus_>,T3, const A1&)>::type result_type;
    
    NT2_FUNCTOR_CALL(3)
    {
      return bsxfun(nt2::functor<tag::plus_>(),
                    bsxfun(nt2::functor<tag::multiplies_>(),
                           nt2:erfcinv(a0),
                           a2)
                    , a1); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::norminv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (unspecified_<A0>)
                              (generic_<floating_<A1> >)
                              (generic_<floating_<A2> >) 
                             )
  {
    typedef typename meta::scalar_of<A0>::type                                                      sA0;
    typedef typename meta::call<tag::minus_(const A0&, sA0)>::type                                   T0; 
    typedef typename meta::call<tag::proper_tanpi_(T0)>::type                                        T1;
    typedef typename meta::call<tag::sqrt_(const A2&)>::type                                         T2;
    typedef typename meta::call<tag::divides_(T1,T2)>::type                                          T3;
    typedef typename meta::call<tag::plus_(T3, const A1&)>::type                            result_type;
    
    NT2_FUNCTOR_CALL(3)
    {
      return fma(nt2::erfcinv(a0), a2, a1); 
    }
  };  
} }

#endif
