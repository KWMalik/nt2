/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_EXPINV_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_EXPINV_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/expinv.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/uminus.hpp>
#include <iostream>

namespace nt2 { namespace ext
{
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expinv_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        std::cout << 1 << std::endl; 
        return  -nt2::log(oneminus(if_allbits_else(is_ltz(a0), a0)));
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expinv_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              )
  {
    typedef A0 result_type;     
    NT2_FUNCTOR_CALL(2)
      {
        std::cout << 2 << std::endl; 
        BOOST_ASSERT_MSG(nt2::is_gtz(a1), "mu parameter must be positive"); 
        return  -a1*nt2::log(nt2::oneminus(nt2::if_allbits_else(nt2::is_ltz(a0), a0)));
      }
  };

  


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expinv_, tag::cpu_
                              , (A0)(A1)
                              , (ast_<A0 >)
                              (ast_<A1>)
                              )
  {
    typedef typename meta::call<tag::is_ltz_(const A0 &)>::type                                 T00; 
    typedef typename meta::call<tag::if_allbits_else_(T00, const A0&)>::type                     T0; 
    typedef typename meta::call<tag::oneminus_(T0)>::type                                        T1;
    typedef typename meta::call<tag::log_(T1)>::type                                             T2;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::multiplies_>,const A1&,T2)>::type T3;
    typedef typename meta::call<tag::uminus_(T3)>::type                                 result_type;
    NT2_FUNCTOR_CALL(2)
      {
        std::cout << 3 << std::endl; 
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a1)), "mu parameter(s) must be positive"); 
        return  -bsxfun(nt2::functor<tag::multiplies_>(), a1, nt2::log(oneminus(if_allbits_else(is_ltz(a0), a0))));
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expinv_, tag::cpu_
                              , (A0)(A1)
                              , (ast_< A0 >)
                              (generic_< floating_<A1> >)
                              )
  {
    typedef typename meta::call<tag::is_ltz_(const A0 &)>::type                                 T00; 
    typedef typename meta::call<tag::if_allbits_else_(T00, const A0&)>::type                     T0; 
    typedef typename meta::call<tag::oneminus_(T0)>::type                                        T1;
    typedef typename meta::call<tag::log_(T1)>::type                                             T2;
    typedef typename meta::call<tag::multiplies_(const A1&,T2)>::type                            T3;
    typedef typename meta::call<tag::uminus_(T3)>::type                                 result_type;
    NT2_FUNCTOR_CALL(2)
      {
        std::cout << 4 << std::endl; 
        BOOST_ASSERT_MSG(nt2::is_gtz(a1), "mu parameter(s) must be positive"); 
        return  -(a1*nt2::log(oneminus(if_allbits_else(is_ltz(a0), a0))));
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expinv_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< floating_<A0> >)
                              (ast_< A1 >)
                              )
  {
    typedef typename meta::call<tag::is_ltz_(const A0 &)>::type                                  T00; 
    typedef typename meta::call<tag::if_allbits_else_(T00, const A0&)>::type                     T0; 
    typedef typename meta::call<tag::oneminus_(T0)>::type                                        T1;
    typedef typename meta::call<tag::log_(T1)>::type                                             T2;
    typedef typename meta::call<tag::multiplies_(const A1&,T2)>::type                            T3;
    typedef typename meta::call<tag::uminus_(T3)>::type                                 result_type;
    NT2_FUNCTOR_CALL(2)
      {
        std::cout << 5 << std::endl; 
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a1)), "mu parameter(s) must be positive"); 
        return  -(a1*nt2::log(oneminus(if_allbits_else(is_ltz(a0), a0))));
      }
  };
} }

#endif
