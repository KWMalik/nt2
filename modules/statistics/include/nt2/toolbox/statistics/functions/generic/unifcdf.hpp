/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_UNIFCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_UNIFCDF_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/unifcdf.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/is_ngt.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  namespace details
  {
    template < class A0, class A1, class A2 > struct unifcdf_1 // at least 2 ast 
    {
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::minus_>,const A2&,const A1&)>::type            T;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::minus_>,const A0&,const A1&)>::type           T0;
      typedef typename meta::call<tag::is_lez_(T)>::type                                                       T2;
      typedef typename meta::call<tag::if_allbits_else_(T2, T)>::type                                          T3;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::divides_>, T0, T3)>::type                     T4;
      typedef typename meta::call<tag::is_less_equal_(const A0&,const A2&)>::type                              T5;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::if_else_>, T5, T4)>::type                     T6; 
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::is_less_equal_>,const A0&,const A1&)>::type   T7;
      typedef typename meta::call<tag::if_else_(T7, T6, T4)>::type                                                 T8; 
      typedef typename meta::call<tag::if_zero_else_(T8, A0)>::type                                   result_type; 
      static inline result_type doit(const A0& a0,  const A1& a1,  const A2& a2) 
      {
        T z = nt2::bsxfun(nt2::functor<tag::minus_>(),a2,a1); // must be scheduled
        return nt2::if_zero_else(nt2::bsxfun(nt2::functor<tag::is_less_equal_>(),a0,a1),
                                 nt2::if_else(nt2::bsxfun(nt2::functor<tag::is_less_equal_>(),a0,a2),
                                              nt2::bsxfun(nt2::functor<tag::divides_>(),
                                                          nt2::bsxfun(nt2::functor<tag::minus_>(),a0,a1),
                                                          nt2::if_allbits_else(is_lez(z), z)),
                                              One<A0>())
                                 ); 
      }
    };
    
    template < class A0, class A1, class A2 > struct unifcdf_2// no more than 1 ast 
    {
      typedef typename meta::call<tag::minus_(const A2&,const A1&)>::type             T;
      typedef typename meta::call<tag::minus_(const A0&,const A1&)>::type            T0;
      typedef typename meta::call<tag::is_lez_(T)>::type                             T2;
      typedef typename meta::call<tag::if_allbits_else_(T2, T)>::type                T3;
      typedef typename meta::call<tag::divides_(T0, T3)>::type                       T4;
      typedef typename meta::call<tag::is_less_equal_(const A0&,const A1&)>::type    T5;
      typedef typename meta::call<tag::if_else_(T5, T4)>::type                     T6; 
      typedef typename meta::call<tag::is_less_equal_(const A0&,const A2&)>::type        T7;
      typedef typename meta::call<tag::if_else_(T7, T6)>::type                                                 T8; 
      typedef typename meta::call<tag::if_zero_else_(T8, A0)>::type                                   result_type; 
      static inline result_type doit(const A0& a0,  const A1& a1,  const A2& a2) 
      {
        T z = a2-a1; // must be scheduled
        return nt2::if_zero_else(nt2::lt(a0,a1),
                                 nt2::if_else(boost::simd::is_ngt(a0,a2),
                                              (a0-a1)/nt2::if_allbits_else(is_lez(z), z),
                                              One<A0>())
                                 ); 
      }
    };
  }    

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        return nt2::if_zero_else(nt2::is_ltz(a0),
                                 nt2::if_else(boost::simd::is_ngt(a0,One<A0>()),
                                              a0,
                                              One<A0>()
                                              )
                                 ); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)  
                              )
  {
    typedef A0 result_type;     
    NT2_FUNCTOR_CALL(3)
      {
        A0 z = a2-a1;
        return nt2::if_allbits_else(is_lez(z),
                                    nt2::if_zero_else(lt(a0,a1),
                                                      nt2::if_else(boost::simd::is_ngt(a0,a2),
                                                                   (a0-a1)/z,
                                                                   One<A0>()
                                                                   )
                                                      )
                                    ); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< floating_<A0> >)
                              (ast_< floating_<A1> >)
                              (ast_< floating_<A2> >)  
                              )
  {
    typedef details::unifcdf_1<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3) { return inner::doit(a0, a1, a2); }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)  
                              )
  {
    typedef details::unifcdf_2<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){ return inner::doit(a0, a1, a2);  }
    
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (ast_< floating_<A1> >)
                              (generic_< floating_<A2> >)  
                              )
  {
    typedef details::unifcdf_2<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){ return inner::doit(a0, a1, a2);  }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (ast_< floating_<A2> >)  
                              )
  {
    typedef details::unifcdf_2<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){ return inner::doit(a0, a1, a2);  }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< floating_<A0> >)
                              (ast_< floating_<A1> >)
                              (generic_< floating_<A2> >)  
                              )
  {
    typedef details::unifcdf_1<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){return inner::doit(a0, a1, a2);  }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (ast_< floating_<A2> >)  
                              )
  {
    typedef details::unifcdf_1<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){return inner::doit(a0, a1, a2);  }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (ast_< floating_<A1> >)
                              (ast_< floating_<A2> >)  
                              )
  {
    typedef details::unifcdf_1<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){return inner::doit(a0, a1, a2);  }
  };
  
} }

#endif
