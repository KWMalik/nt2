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

namespace nt2 { namespace ext
{
  namespace details
  {
    template < class A0, class A1> struct expcdf_1 // at least 2 ast 
    {
      typedef typename meta::call<tag::is_ltz_(const A0&)>::type                                           T0;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::divides_>,const A0&,const A1&)>::type     T1;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::if_zero_else_>,T0,T1)>::type                           T2;
      typedef typename meta::call<tag::exp_(T2)>::type                                                     T3;
      typedef typename meta::call<tag::oneminus_(T3)>::type                                       result_type; 
      static inline result_type doit(const A0& a0,  const A1& a1) 
      {
        return nt2::oneminus(nt2::exp(-nt2::bsxfun(nt2::functor<tag::if_zero_else_>(),
                                                   nt2::is_ltz(a0),
                                                   nt2::bsxfun(nt2::functor<tag::divides_>(), a0, a1)
                                                   )
                                      )
                             ); 
        
      }
    };
    
    template < class A0, class A1> struct expcdf_2// no more than 1 ast 
    {
      typedef typename meta::call<tag::is_ltz_(const A0&)>::type                     T0;
      typedef typename meta::call<tag::divides_(const A0&,const A1&)>::type          T1;
      typedef typename meta::call<tag::if_zero_else_(T0, T1)>::type                  T2;
      typedef typename meta::call<tag::exp_(T2)>::type                               T3;
      typedef typename meta::call<tag::oneminus_(T3)>::type                 result_type; 
      static inline result_type doit(const A0& a0,  const A1& a1) 
      {
        BOOST_ASSERT_MSG(nt2::all(nt2::is_gtz(a1)(nt2::_)), "mu parameter(s) must be positive"); 
        return nt2::oneminus(nt2::exp(-nt2::if_zero_else(nt2::is_ltz(a0), a0/a1))); 
      }
    };
  }    

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
      {
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
        BOOST_ASSERT_MSG(a1 > 0, "mu parameter must be positive"); 
        return nt2::oneminus(nt2::exp(-nt2::if_zero_else(nt2::is_ltz(a0/a1), a0))); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf_, tag::cpu_
                              , (A0)(A1)
                              , (ast_< floating_<A0> >)
                              (ast_< floating_<A1> >)
                              )
  {
    typedef details::expcdf_1<A0, A1> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(2) { return inner::doit(a0, a1); }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf_, tag::cpu_
                              , (A0)(A1)
                              , (ast_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              )
  {
    typedef details::expcdf_2<A0, A1> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(2){ return inner::doit(a0, a1);  }
    
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< floating_<A0> >)
                              (ast_< floating_<A1> >)
                              )
  {
    typedef details::expcdf_2<A0, A1> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(2){ return inner::doit(a0, a1);  }
  };
  

  
} }

#endif
