/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_NORMPDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_NORMPDF_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/normpdf.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/atanpi.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/invsqrt_2pi.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::exp(Mhalf<A0>()*nt2::sqr(a0))*Invsqrt_2pi<A0>();
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
                              , (A0)(A1)
                              , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                              )
  {
    typedef A0 result_type;     
    NT2_FUNCTOR_CALL(2)
      {
        return nt2::exp(Mhalf<A0>()*nt2::sqr(a0-a1))*Invsqrt_2pi<A0>();
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
                            , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)  
                            )
  {
    typedef A0 result_type;     
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gez(a2)), "sigma(s) must be positive"); 
      return nt2::exp(Mhalf<A0>()*nt2::sqr((a0-a1)/a2))*Invsqrt_2pi<A0>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
                              , (A0)(A1)
                              , (ast_<A0>)
                              (ast_<A1>)
                             )
  {
    typedef typename meta::scalar_of<A0>::type                                                     sA0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::minus_>,const A0&,const A1&)>::type  T0;
    typedef typename meta::call<tag::sqr_(T0)>::type                                                 T1;
    typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
    typedef typename meta::call<tag::exp_(T2)>::type                                                T3;
    typedef typename meta::call<tag::multiplies_(T3, sA0)>::type                           result_type;
    
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::exp(Mhalf<sA0>()*nt2::sqr(nt2::bsxfun(nt2::functor<tag::minus_>(), a0, a1)))*Invsqrt_2pi<sA0>();
    }
  };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
//                              , (A0)(A1)
//                              , (ast_<A0>)
//                              (generic_< floating_<A1> >)
//                              )
//   {
//     typedef typename meta::scalar_of<A0>::type                                                     sA0;
//     typedef typename meta::call<tag::minus_(const A0&,const A1&)>::type                             T0;
//     typedef typename meta::call<tag::sqr_(T0)>::type                                                 T1;
//     typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
//     typedef typename meta::call<tag::exp_(T2)>::type                                                T3;
//     typedef typename meta::call<tag::multiplies_(T3, sA0)>::type                           result_type;
//     NT2_FUNCTOR_CALL(2)
//     {
//       return nt2::exp(Mhalf<sA0>()*sqr(a0-a1))*Invsqrt_2pi<sA0>();
//     }
//   };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
//                              , (A0)(A1)
//                              , (generic_< floating_<A0> >)
//                               (ast_<A1>)
//                              )
//   {
//     typedef typename meta::scalar_of<A0>::type                                                     sA0;
//     typedef typename meta::call<tag::minus_(const A0&,const A1&)>::type                             T0;
//     typedef typename meta::call<tag::sqr_(T0)>::type                                                 T1;
//     typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
//     typedef typename meta::call<tag::exp_(T2)>::type                                                T3;
//     typedef typename meta::call<tag::multiplies_(T3, sA0)>::type                           result_type;
//     NT2_FUNCTOR_CALL(2)
//     {
//       return nt2::exp(Mhalf<sA0>()*sqr(a0-a1))*Invsqrt_2pi<sA0>();
//     }
//   };
  

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< A0 >)
                              (ast_< A1 >)
                              (ast_< A2 >)  
                              )
  {
    typedef typename meta::scalar_of<A0>::type                                                     sA0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::minus_>,const A0&,const A1&)>::type  T0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::divides_>,T0,const A2&)>::type       T1;
    typedef typename meta::call<tag::sqr_(T1)>::type                                                 T2;
    typedef typename meta::call<tag::multiplies_(sA0, T2)>::type                                    T3; 
    typedef typename meta::call<tag::exp_(T3)>::type                                                T4;
    typedef typename meta::call<tag::multiplies_(T4, sA0)>::type                           result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gez(a2)), "sigma(s) must be positive"); 
      return nt2::exp(Mhalf<A0>()*
                      nt2::sqr(nt2::bsxfun(nt2::functor<tag::divides_>(),
                                           nt2::bsxfun(nt2::functor<tag::minus_>(), a0, a1),
                                           a2))
                      )*Invsqrt_2pi<A0>();

    }
  };

//     NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
//                                 , (A0)(A1)(A2)
//                                 , (ast_< floating_<A0> >)
//                                 (generic_< floating_<A1> >)
//                                 (generic_< floating_<A2> >)  
//                                 )
//       {
//     typedef typename meta::scalar_of<A0>::type                                                     sA0;
//     typedef typename meta::call<tag::minus_(const A0&,const A1&)>::type                             T0;
//     typedef typename meta::call<tag::sqr_(T0)>::type                                                 T1;
//     typedef typename meta::call<tag::multiplies_(A2,T1)>::type                                      T2;
//     typedef typename meta::call<tag::exp_(T2)>::type                                                T4;
//     typedef typename meta::call<tag::multiplies_(T2, sA0)>::type                           result_type;
//     NT2_FUNCTOR_CALL(3)
//     {
//       BOOST_ASSERT_MSG(is_gez(a2), "sigma must be positive");
//       A2 minv2sig2 =  Mhalf<sA0>()/sqr(a2); 
//       return nt2::exp(minv2sig2*sqr(a0-a1))*Invsqrt_2pi<A0>();
//     }
//   };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
//                             , (A0)(A1)(A2)
//                               , (generic_< floating_<A0> >)
//                                (ast_< floating_<A1> >)
//                                (generic_< floating_<A2> >)  
//                             )
//   {
//     typedef typename meta::scalar_of<A0>::type                                                     sA0;
//     typedef typename meta::call<tag::minus_(const A0&,const A1&)>::type                             T0;
//     typedef typename meta::call<tag::sqr_(T0)>::type                                                 T1;
//     typedef typename meta::call<tag::multiplies_(A2,T1)>::type                                      T2;
//     typedef typename meta::call<tag::exp_(T2)>::type                                                T4;
//     typedef typename meta::call<tag::multiplies_(T2, sA0)>::type                           result_type;
//     NT2_FUNCTOR_CALL(3)
//     {
//       BOOST_ASSERT_MSG(is_gez(a2), "sigma must be positive"); 
//       A2 minv2sig2 =  Mhalf<sA0>()/sqr(a2); 
//       return nt2::exp(minv2sig2*sqr(a0-a1))*Invsqrt_2pi<A0>();
//     }
//   };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
//                             , (A0)(A1)(A2)
//                               , (generic_< floating_<A0> >)
//                                (generic_< floating_<A1> >)
//                                (ast_< floating_<A2> >)  
//                             )
//   {
//     typedef typename meta::scalar_of<A0>::type                                                     sA0;
//     typedef typename meta::call<tag::minus_(const A0&,const A1&)>::type                             T0;
//     typedef typename meta::call<tag::sqr_(const A2&)>::type                                         T1;
//     typedef typename meta::call<tag::divides_(T0,T1)>::type                                         T2;
//     typedef typename meta::call<tag::exp_(T2)>::type                                                T3;
//     typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                           result_type;
//     NT2_FUNCTOR_CALL(3)
//     {
//       BOOST_ASSERT_MSG(all(is_gez(a2)), "sigma(s) must be positive");
//       A0 tmp = Mhalf<A0>()*sqr(a0-a1); 
//       return nt2::exp(tmp/sqr(a2))*Invsqrt_2pi<A0>();
//     }
//   };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_<A0 >)
                              (ast_< A1 >)
                              (generic_< floating_<A2> >)  
                              )
  {
    typedef typename A0::value_type                                                                sA0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::minus_>,const A0&,const A1&)>::type  T0;
    typedef typename meta::call<tag::sqr_(T0)>::type                                                T1;
    typedef typename meta::call<tag::multiplies_(A2,T1)>::type                                      T2;
    typedef typename meta::call<tag::exp_(T2)>::type                                                T4;
    typedef typename meta::call<tag::multiplies_(T2, sA0)>::type                           result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(is_gez(a2), "sigma must be positive"); 
      A2 minv2sig2 =  Mhalf<sA0>()/nt2::sqr(a2); 
      return nt2::exp(minv2sig2*nt2::sqr(nt2::bsxfun(nt2::functor<tag::minus_>(),a0,a1)))*Invsqrt_2pi<A0>();
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< A0 >)
                              (generic_< floating_<A1> >)
                              (ast_< A2 >)  
                              )
  {
    typedef typename A0::value_type                                                                sA0;
    typedef typename meta::call<tag::minus_(const A0&,const A1&)>::type                             T0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::divides_ >,T0,const A2&)>::type      T1;
    typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
    typedef typename meta::call<tag::exp_(T2)>::type                                                T3;
    typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                           result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return nt2::exp(Mhalf<A0>()*nt2::sqr(nt2::bsxfun(nt2::functor<tag::divides_>(),a0-a1,a2)))*Invsqrt_2pi<A0>();

    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (ast_<A1>)
                              (ast_<A2>)  
                              )
  {
    typedef typename meta::scalar_of<A0>::type                                                     sA0;
    typedef typename meta::call<tag::minus_(const A0&,const A1&)>::type                             T0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::divides_>,T0,const A2&)>::type       T1;
    typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
    typedef typename meta::call<tag::exp_(T2)>::type                                                T3;
    typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                           result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return nt2::exp(Mhalf<A0>()*nt2::sqr(nt2::bsxfun(nt2::functor<tag::divides_>(),a0-a1,a2)))*Invsqrt_2pi<A0>();

    }
  };

} }

#endif
