/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_UNIFINV_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_UNIFINV_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/unifinv.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/tsxfun.hpp>
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
    template < class A0, class A1, class A2 > struct unifinv_1 // at least 2 ast 
    {
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::minus_ >,const A2&,const A1&)>::type                  T;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::is_greater_>,const A0&,const A2&)>::type             T0;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::is_less_>,const A0&,const A1&)>::type                T1;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::logical_or_>,T0,T1)>::type                           T2;
      typedef typename meta::call<tag::is_lez_(T)>::type                                                              T3;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::logical_or_>,T3, T2)>::type                          T4;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::if_allbits_else_>,T4, T)>::type                      T5;
      typedef typename meta::call<tag::tsxfun_(nt2::functor<tag::fma_>,const A0&, T5, const A1&)>::type      result_type;
      static inline result_type doit(const A0& a0,  const A1& a1,  const A2& a2) 
      {
        T z = nt2::bsxfun(nt2::functor<tag::minus_>(), a2, a1);//to schedule                                            // T 
        return nt2::tsxfun(nt2::functor<tag::fma_>(),                                                                   // A0, T5, A1 -> result_type
                           a0,                                                                                          // A0
                           nt2::bsxfun(nt2::functor<tag::if_allbits_else_>(),                                           // T4, T  -> T5
                                       nt2::bsxfun(nt2::functor<tag::logical_or_>(),                                    // T3, T2 -> T4
                                                   nt2::is_lez(z),                                                      // T -> T3
                                                   nt2::bsxfun(nt2::functor<tag::logical_or_>(),                        // T0, T1 -> T2
                                                               nt2::bsxfun(nt2::functor<tag::is_greater_>(), a0, a2),   // A0,  A2 -> T0
                                                               nt2::bsxfun(nt2::functor<tag::is_less_>(), a0, a1)       // A0,  A1 -> T1
                                                               ) 
                                                   ), 
                                       z),                                                                              // T
                           a1);                                                                                         // A1
      }
    };
    
 
  }    
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        return if_else(logical_and(is_gez(a0), le(a0, One<A0>())), a0, Nan<A0> ()); 
      }
  };

 NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
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
        z = if_allbits_else(logical_or(is_lez(z), logical_or(gt(a0, a2), lt(a0, a1))), z); 
        return fma(a0, z, a1); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< A0 >)
                              (ast_< A1 >)
                              (ast_< A2 >)  
                              )
  {
    typedef details::unifinv_1<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3) {
      return inner::doit(a0, a1, a2);
    }
  };
  

  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< A0 >)
                              (ast_< A1 >)
                              (generic_< floating_<A2> >)  
                              )
    {
      typedef details::unifinv_1<A0, A1, A2> inner; 
      typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){return inner::doit(a0, a1, a2);  }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< A0 >)
                              (generic_< floating_<A1> >)
                              (ast_< A2 >)  
                              )
  {
    typedef details::unifinv_1<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){return inner::doit(a0, a1, a2);  }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (ast_< A1 >)
                              (ast_< A2 >)  
                              )
  {
    typedef details::unifinv_1<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){return inner::doit(a0, a1, a2);  }
  };
  
} }

#endif
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
//                               , (A0)(A1)(A2)
//                               , (ast_< A0 >)
//                               (generic_< floating_<A1> >)
//                               (generic_< floating_<A2> >)  
//                               )
//   {
//     typedef details::unifinv_2<A0, A1, A2> inner; 
//     typedef typename inner::result_type result_type; 
//     NT2_FUNCTOR_CALL(3){ return inner::doit(a0, a1, a2);  }
    
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
//                               , (A0)(A1)(A2)
//                               , (generic_< floating_<A0> >)
//                               (ast_< A1 >)
//                               (generic_< floating_<A2> >)  
//                               )
//   {
//     typedef details::unifinv_2<A0, A1, A2> inner; 
//     typedef typename inner::result_type result_type; 
//     NT2_FUNCTOR_CALL(3){ return inner::doit(a0, a1, a2);  }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
//                               , (A0)(A1)(A2)
//                               , (generic_< floating_<A0> >)
//                               (generic_< floating_<A1> >)
//                               (ast_< A2 >)  
//                               )
//   {
//     typedef details::unifinv_2<A0, A1, A2> inner; 
//     typedef typename inner::result_type result_type; 
//     NT2_FUNCTOR_CALL(3){ return inner::doit(a0, a1, a2);  }
//   };  
  

     //     template < class A0, class A1, class A2 > struct unifinv_2// no more than 1 ast 
    //     {
    //       typedef typename meta::call<tag::minus_(const A2&,const A1&)>::type                   T;
    //       typedef typename meta::call<tag::is_greater_(const A0&,const A2&)>::type             T0;
    //       typedef typename meta::call<tag::is_less_(const A0&,const A1&)>::type                T1;
    //       typedef typename meta::call<tag::logical_or_(T0, T1)>::type                          T2;
    //       typedef typename meta::call<tag::is_lez_(T)>::type                                   T3;
    //       typedef typename meta::call<tag::logical_or_(T, T3)>::type                           T4;
    //       typedef typename meta::call<tag::if_allbits_else_(T4, T)>::type                      T5;
    //       typedef typename meta::call<tag::fma_(const A0&, T5, const A1&)>::type      result_type; 
    //       static inline result_type doit(const A0& a0,  const A1& a1,  const A2& a2) 
    //       {
    //         T z = a2-a1;
    //         return fma(a0, if_allbits_else(logical_or(is_lez(z), logical_or(gt(a0, a2), lt(a0, a1))), z), a1); 
    //       }
    //     };
