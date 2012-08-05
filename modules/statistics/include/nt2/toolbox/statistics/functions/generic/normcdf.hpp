/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_NORMCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_NORMCDF_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/normcdf.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/atanpi.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/erfc.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1){ return Half<A0>()*nt2::erfc(-Sqrt_2o_2<A0>()*a0); }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
                              , (A0)(A1)
                              , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                              )
  {
    typedef A0 result_type;     
    NT2_FUNCTOR_CALL(2){ return Half<A0>()*nt2::erfc(Sqrt_2o_2<A0>()*(a1-a0)); }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
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
        return Half<A0>()*nt2::erfc(Sqrt_2o_2<A0>*(a1-a0)/a2); 
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
                              , (A0)(A1)
                              , (ast_<A0>)
                              (ast_<A1>)
                             )
  {
    typedef typename meta::scalar_of<A0>::type                                                     sA0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::minus_>,const A1&,const A0&)>::type  T1;
    typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
    typedef typename meta::call<tag::erfc_(T2)>::type                                               T3;
    typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                          result_type;
    
    NT2_FUNCTOR_CALL(2)
    {
      return Half<sA0>()*nt2::erfc(Sqrt_2o_2<sA0>()*(nt2::bsxfun(nt2::functor<tag::minus_>(), a1, a0))); 
    }
  };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
//                              , (A0)(A1)
//                              , (ast_<A0>)
//                              (generic_< floating_<A1> >)
//                              )
//   {
//     typedef typename meta::scalar_of<A0>::type                                                     sA0;
//     typedef typename meta::call<tag::minus_(const A1&,const A0&)>::type                             T1;
//     typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
//     typedef typename meta::call<tag::erfc_(T2)>::type                                               T3;
//     typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                          result_type;
//     NT2_FUNCTOR_CALL(2)
//     {
//       return Half<sA0>()*nt2::erfc(Sqrt_2o_2<sA0>()*(a1-a0)); 
//     }
//   };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
//                              , (A0)(A1)
//                              , (generic_< floating_<A0> >)
//                               (ast_<A1>)
//                              )
//   {
//     typedef typename meta::scalar_of<A0>::type                                                     sA0;
//     typedef typename meta::call<tag::minus_(const A1&,const A0&)>::type                             T1;
//     typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
//     typedef typename meta::call<tag::erfc_(T2)>::type                                               T3;
//     typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                          result_type;
//     NT2_FUNCTOR_CALL(2)
//     {
//       return Half<sA0>()*nt2::erfc(Sqrt_2o_2<sA0>()*(a1-a0)); 
//     }
//   };
  


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_<A0>)
                              (ast_<A1>)
                              (ast_<A2>)  
                              )
  {
    typedef typename meta::scalar_of<A0>::type                                                     sA0;
    typedef typename meta::as_logical<sA0>::type                                                  bsA0; 
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::minus_>,const A1&,const A0&)>::type  T0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::divides_>,T0,const A2&)>::type       T1;
    typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
    typedef typename meta::call<tag::erfc_(T2)>::type                                               T3;
    typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                          result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(nt2::colvect(a2))), "sigma(s) must be positive"); 
      return Half<sA0>()*nt2::erfc(Sqrt_2o_2<sA0>()*nt2::bsxfun(nt2::functor<tag::divides_>(),
                                                        nt2::bsxfun(nt2::functor<tag::minus_>(), a1, a0),
                                                        a2)); 
    }
  };

//     NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
//                                 , (A0)(A1)(A2)
//                                 , (ast_<A0>)
//                                 (generic_< floating_<A1> >)
//                                 (generic_< floating_<A2> >)  
//                                 )
//       {
//     typedef typename meta::scalar_of<A0>::type                                                     sA0;
//     typedef typename meta::call<tag::minus_(const A1&,const A0&)>::type                             T0;
//     typedef typename meta::call<tag::divides_(T0,const A2&)>::type                                  T1;
//     typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
//     typedef typename meta::call<tag::erfc_(T2)>::type                                               T3;
//     typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                          result_type;
//     NT2_FUNCTOR_CALL(3)
//     {
//       BOOST_ASSERT_MSG(nt2::all(nt2::is_gez(nt2::colvect(a2))), "sigma(s) must be positive"); 
//       return Half<sA0>()*nt2::erfc(Sqrt_2o_2<sA0>()*(a1-a0)/a2); 
//     }
//   };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
//                             , (A0)(A1)(A2)
//                               , (generic_< floating_<A0> >)
//                                (ast_<A1>)
//                                (generic_< floating_<A2> >)  
//                             )
//   {
//     typedef typename meta::scalar_of<A0>::type                                                     sA0;
//     typedef typename meta::call<tag::minus_(const A1&,const A0&)>::type                             T0;
//     typedef typename meta::call<tag::divides_(T0,const A2&)>::type                                  T1;
//     typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
//     typedef typename meta::call<tag::erfc_(T2)>::type                                               T3;
//     typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                          result_type;
//     NT2_FUNCTOR_CALL(3)
//     {
//       BOOST_ASSERT_MSG(nt2::all(nt2::is_gez(nt2::colvect(a2))), "sigma(s) must be positive"); 
//       return Half<sA0>()*nt2::erfc(Sqrt_2o_2<sA0>()*(a1-a0)/a2); 
//     }
//   };

//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
//                             , (A0)(A1)(A2)
//                               , (generic_< floating_<A0> >)
//                                (generic_< floating_<A1> >)
//                                (ast_<A2>)  
//                             )
//   {
//     typedef typename meta::scalar_of<A0>::type                                                     sA0;
//     typedef typename meta::call<tag::minus_(const A1&,const A0&)>::type                             T0;
//     typedef typename meta::call<tag::divides_(T0,const A2&)>::type                                  T1;
//     typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
//     typedef typename meta::call<tag::erfc_(T2)>::type                                               T3;
//     typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                          result_type;
//     NT2_FUNCTOR_CALL(3)
//     {
//       BOOST_ASSERT_MSG(nt2::all(nt2::is_gez(nt2::colvect(a2))), "sigma(s) must be positive"); 
//       return Half<sA0>()*nt2::erfc(Sqrt_2o_2<sA0>()*(a1-a0)/a2); 
//     }
//   };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_<A0>)
                              (ast_<A1>)
                              (generic_< floating_<A2> >)  
                              )
  {
    typedef typename A0::value_type                                                                sA0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::minus_>,const A1&,const A0&)>::type  T0;
    typedef typename meta::call<tag::divides_(T0,const A2&)>::type                                  T1;
    typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
    typedef typename meta::call<tag::erfc_(T2)>::type                                               T3;
    typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                           result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(nt2::colvect(a2))), "sigma(s) must be positive"); 
      return Half<sA0>()*nt2::erfc(Sqrt_2o_2<sA0>()*nt2::bsxfun(nt2::functor<tag::minus_>(), a1, a0)/a2); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_<A0>)
                              (generic_< floating_<A1> >)
                              (ast_<A2>)  
                              )
  {
    typedef typename meta::scalar_of<A0>::type                                                     sA0;
    typedef typename meta::call<tag::minus_(const A1&,const A0&)>::type                             T0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::divides_>,T0,const A2&)>::type       T1;
    typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
    typedef typename meta::call<tag::erfc_(T2)>::type                                               T3;
    typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                          result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(nt2::colvect(a2))), "sigma(s) must be positive"); 
      return Half<sA0>()*nt2::erfc(Sqrt_2o_2<sA0>()*nt2::bsxfun(nt2::functor<tag::divides_>(),a1-a0,a2)); 
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (ast_<A1>)
                              (ast_<A2>)  
                              )
  {
    typedef typename meta::scalar_of<A0>::type                                                     sA0;
    typedef typename meta::call<tag::minus_(const A1&,const A0&)>::type                             T0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::divides_>,T0,const A2&)>::type       T1;
    typedef typename meta::call<tag::multiplies_(sA0, T1)>::type                                    T2; 
    typedef typename meta::call<tag::erfc_(T2)>::type                                               T3;
    typedef typename meta::call<tag::multiplies_(sA0, T3)>::type                          result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(nt2::colvect(a2))), "sigma(s) must be positive"); 
      return Half<sA0>()*nt2::erfc(Sqrt_2o_2<sA0>()*nt2::bsxfun(nt2::functor<tag::divides_>(),a1-a0,a2)); 
    }
  };

} }

#endif
