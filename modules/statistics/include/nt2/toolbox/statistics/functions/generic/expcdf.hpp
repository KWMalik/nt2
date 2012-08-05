/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_EXPCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_EXPCDF_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/expcdf.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/uminus.hpp>
#include <nt2/sdk/meta/type_id.hpp>
//#include <nt2/table.hpp>
#include <iostream>

namespace nt2 { namespace ext
{
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        std::cout << 1 << std::endl; 
        return nt2::oneminus(nt2::exp(-nt2::if_zero_else(nt2::is_ltz(a0), a0))); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf_, tag::cpu_
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
        return nt2::oneminus(nt2::exp(-nt2::if_zero_else(nt2::is_ltz(a0/a1), a0))); 
      }
  };

  


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf_, tag::cpu_
                              , (A0)(A1)
                              , (ast_<A0 >)
                              (ast_<A1>)
                              )
  {
    typedef typename meta::call<tag::is_ltz_(const A0&)>::type                                       T0;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::divides_>,const A0&,const A1&)>::type T1;
    typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::if_zero_else_>,T0, T1)>::type         T2;
    typedef typename meta::call<tag::uminus_(T2)>::type                                              T3;
    typedef typename meta::call<tag::exp_(T3)>::type                                                 T4;
    typedef typename meta::call<tag::oneminus_(T4)>::type                                   result_type;
    NT2_FUNCTOR_CALL(2)
      {
        std::cout << 3 << std::endl; 
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a1)), "mu parameter(s) must be positive"); 
        return nt2::oneminus(nt2::exp(-nt2::bsxfun(nt2::functor<tag::if_zero_else_>(),
                                                   nt2::is_ltz(a0),
                                                   nt2::bsxfun(nt2::functor<tag::divides_>(),a0,a1)
                                                   )
                                      )
                             );       
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf_, tag::cpu_
                              , (A0)(A1)
                              , (ast_< A0 >)
                              (generic_< floating_<A1> >)
                              )
  {
    typedef typename meta::call<tag::is_ltz_(const A0&)>::type                     T0;
    typedef typename meta::call<tag::divides_(const A0&,const A1&)>::type          T1;
    typedef typename meta::call<tag::if_zero_else_(T0, T1)>::type                  T2;
    typedef typename meta::call<tag::uminus_(T2)>::type                            T3;
    typedef typename meta::call<tag::exp_(T3)>::type                               T4;
    typedef typename meta::call<tag::oneminus_(T4)>::type                 result_type; 
    NT2_FUNCTOR_CALL(2)
      {
        std::cout << 4 << std::endl; 
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a1)), "mu parameter(s) must be positive"); 
        return nt2::oneminus(nt2::exp(-nt2::if_zero_else(nt2::is_ltz(a0), a0/a1))); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< floating_<A0> >)
                              (ast_< A1 >)
                              )
  {
    typedef typename meta::call<tag::is_ltz_(const A0&)>::type                     T0;
    typedef typename meta::call<tag::divides_(const A0&,const A1&)>::type          T1;
    typedef typename meta::call<tag::if_zero_else_(T0, T1)>::type                  T2;
    typedef typename meta::call<tag::uminus_(T2)>::type                            T3;
    typedef typename meta::call<tag::exp_(T3)>::type                               T4;
    typedef typename meta::call<tag::oneminus_(T4)>::type                 result_type; 
    NT2_FUNCTOR_CALL(2)
      {
        std::cout << 5 << std::endl; 
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a1)), "mu parameter(s) must be positive"); 
        return nt2::oneminus(nt2::exp(-nt2::if_zero_else(nt2::is_ltz(a0), a0/a1))); 
      }
  };
} }

#endif
