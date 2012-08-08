/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_CAUINV_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_CAUINV_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/cauinv.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/proper_tanpi.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/globalall.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauinv_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        return nt2::proper_tanpi(a0-Half<A0>());
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauinv_, tag::cpu_
                              , (A0)(A1)
                              , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                              )
  {
    typedef A0 result_type;     
    NT2_FUNCTOR_CALL(2) {
      return nt2::proper_tanpi(a0-Half<A0>())+a1;
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauinv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)  
                              )
  {
    typedef A0 result_type;     
    NT2_FUNCTOR_CALL(3) {      
      BOOST_ASSERT_MSG(nt2::is_gtz(a2), "scale parameter must be positive"); 
      return nt2::proper_tanpi(a0-Half<A0>())/nt2::sqrt(a2)+a1;
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauinv_, tag::cpu_
                              , (A0)(A1)
                              , (ast_<A0>)
                              (ast_<A1>)
                              )
  {
    typedef typename meta::scalar_of<A0>::type                                                     sA0;
    typedef typename meta::call<tag::minus_(const A0&, sA0)>::type                                  T0; 
    typedef typename meta::call<tag::proper_tanpi_(T0)>::type                                       T1;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::plus_>,T1,const A1&)>::type result_type; 
    
    NT2_FUNCTOR_CALL(2)
      { //std::cout << 4 << std::endl; 

      return bsxfun(nt2::functor<tag::plus_>(), nt2::proper_tanpi(a0-Half<sA0>()), a1); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauinv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_<A0>)
                              (ast_<A1>)
                              (ast_<A2>) 
                             )
  {
    typedef typename meta::scalar_of<A0>::type                                                      sA0;
    typedef typename meta::call<tag::minus_(const A0&, sA0)>::type                                   T0; 
    typedef typename meta::call<tag::proper_tanpi_(T0)>::type                                               T1;
    typedef typename meta::call<tag::sqrt_(const A2&)>::type                                         T2;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::divides_>,T1,T2)>::type               T3;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::plus_>,T3, const A1&)>::type result_type;
    
    NT2_FUNCTOR_CALL(3)
    {   //std::cout << 5 << std::endl; 

      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a2)), "scale parameter must be positive"); 
      return bsxfun(nt2::functor<tag::plus_>(),
                    bsxfun(nt2::functor<tag::divides_>(),
                           nt2::proper_tanpi(a0-Half<sA0>()),
                           nt2::sqrt(a2))
                    , a1); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauinv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_<A0>)
                              (ast_<A1>)
                              (generic_< floating_<A2> >) 
                             )
  {
    typedef typename meta::scalar_of<A0>::type                                                      sA0;
    typedef typename meta::call<tag::minus_(const A0&, sA0)>::type                                   T0; 
    typedef typename meta::call<tag::proper_tanpi_(T0)>::type                                        T1;
    typedef typename meta::call<tag::sqrt_(const A2&)>::type                                         T2;
    typedef typename meta::call<tag::divides_(T1,T2)>::type                                          T3;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::plus_>,T3, const A1&)>::type result_type;
    
    NT2_FUNCTOR_CALL(3)
    {   //std::cout << 6 << std::endl; 

      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a2)), "scale parameter must be positive"); 
      return bsxfun(nt2::functor<tag::plus_>(),
                    nt2::proper_tanpi(a0-Half<sA0>())/nt2::sqrt(a2), 
                    a1); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauinv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_<A0>)
                              (generic_< floating_<A1> >)
                              (ast_<A2>)
                              
                             )
  {
    typedef typename meta::scalar_of<A0>::type                                                      sA0;
    typedef typename meta::call<tag::minus_(const A0&, sA0)>::type                                   T0; 
    typedef typename meta::call<tag::proper_tanpi_(T0)>::type                                        T1;
    typedef typename meta::call<tag::sqrt_(const A2&)>::type                                         T2;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::divides_>,T1,T2)>::type               T3;
    typedef typename meta::call<tag::plus_(T3, const A1&)>::type result_type;
    
    NT2_FUNCTOR_CALL(3)
    {   //std::cout << 7 << std::endl; 

      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a2)), "scale parameter must be positive"); 
      return bsxfun(nt2::functor<tag::divides_>(),
                    nt2::proper_tanpi(a0-Half<sA0>()), nt2::sqrt(a2))+a1; 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauinv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (ast_<A1>)
                              (ast_<A2>)
                              
                             )
  {
    typedef typename meta::scalar_of<A0>::type                                                      sA0;
    typedef typename meta::call<tag::minus_(const A0&, sA0)>::type                                   T0; 
    typedef typename meta::call<tag::proper_tanpi_(T0)>::type                                        T1;
    typedef typename meta::call<tag::sqrt_(const A2&)>::type                                         T2;
    typedef typename meta::call<nt2::functor<tag::divides_>(T1,T2)>::type                            T3;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::plus_>,T3, const A1&)>::type result_type;
    
    NT2_FUNCTOR_CALL(3)
    {   //std::cout << 8 << std::endl; 

      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a2)), "scale parameter must be positive"); 
      return bsxfun(nt2::functor<tag::plus_>(),
                    nt2::proper_tanpi(a0-Half<sA0>())/nt2::sqrt(a2), 
                    a1); 
    }
  };
} }

#endif
