/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_UNIFPDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_GENERIC_UNIFPDF_HPP_INCLUDED
#include <nt2/toolbox/statistics/functions/unifpdf.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  namespace details
  {
    template < class A0, class A1, class A2 > struct unifpdf_1 // at least 2 ast 
    {
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::minus_>,const A2&,const A1&)>::type             T;
      typedef typename meta::call<tag::is_lez_(T)>::type                                                       T1a;
      typedef typename meta::call<tag::is_nan_(const A0&)>::type                                               T1b;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::logical_or_ >,T1a, T1b)>::type                 T1;
      typedef typename meta::call<tag::rec_(T)>::type                                                           T3;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::is_less_>,const A0&,const A1&)>::type          T4;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::is_greater_>,const A0&,const A2&)>::type       T5;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::logical_or_>, T4, T5)>::type                   T6;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::if_zero_else_>, T6, T3)>::type                 T7;
      typedef typename meta::call<tag::bsxfun_(nt2::functor<tag::if_allbits_else_>, T1, T7)>::type     result_type; 


      static inline result_type doit(const A0& x,  const A1& a,  const A2& b) 
      {
        T z = nt2::bsxfun(nt2::functor<tag::minus_>(),b,a); //this must be scheduled
        return nt2::bsxfun(nt2::functor<tag::if_allbits_else_>(),
                           nt2::bsxfun(nt2::functor<tag::logical_or_>(), is_lez(z), is_nan(x)),
                           nt2::bsxfun(nt2::functor<tag::if_zero_else_>(),
                                       nt2::bsxfun(nt2::functor<tag::logical_or_>(), lt(x,a),gt(x,b)),
                                       nt2::rec(z)
                                       )
                           ); 
        
      }
    };
    
 //    template < class A0, class A1, class A2 > struct unifpdf_2// no more than 1 ast 
//     {

//       typedef typename meta::call<tag::minus_(const A2&,const A1&)>::type                              T;
//       typedef typename meta::call<tag::is_lez_(T)>::type                                             T1a;
//       typedef typename meta::call<tag::is_nan_(const A0&)>::type                                     T1b;
//       typedef typename meta::call<tag::logical_or_(T1a, T1b)>::type                                   T1;
//       typedef typename meta::call<tag::rec_(T)>::type                                                 T3;
//       typedef typename meta::call<tag::is_less_(const A0&,const A1&)>::type                           T4;
//       typedef typename meta::call<tag::is_greater_(const A0&,const A2&)>::type                        T5;
//       typedef typename meta::call<tag::logical_or_(T4, T5)>::type                                     T6;
//       typedef typename meta::call<tag::if_zero_else_(T6, T3)>::type                                   T7;
//       typedef typename meta::call<tag::if_allbits_else_(T1, T7)>::type                     result_type; 
 
//       static inline result_type doit(const A0& a0,  const A1& a1,  const A2& a2) 
//       {
//         T z = a2-a1; //this must be scheduled
//         return nt2::if_allbits_else(logical_or(is_lez(z), is_nan(a0)),
//                                     nt2::if_zero_else(logical_or(lt(a0,a1),gt(a0,a2)),
//                                                       nt2::rec(z)
//                                                       )
//                                     ); 
//       }
//     };
  }    

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifpdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type; 
    NT2_FUNCTOR_CALL(1)
      {
        return if_else(is_nan(a0), a0,if_else_zero(logical_and(is_gez(a0), le(a0, One<A0>())), One<A0>()));
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifpdf_, tag::cpu_
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
        return nt2::if_allbits_else(logical_or(is_lez(z), is_nan(a0)),
                                    nt2::if_zero_else(logical_or(lt(a0,a1),gt(a0,a2)),
                                                      nt2::rec(z)
                                                      )
                                    ); 
      }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifpdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< A0 >)
                              (ast_< A1 >)
                              (ast_< A2 >)  
                              )
  {
    typedef details::unifpdf_1<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3) { return inner::doit(a0, a1, a2); }
  };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifpdf_, tag::cpu_
//                               , (A0)(A1)(A2)
//                               , (ast_< A0 >)
//                               (generic_< floating_<A1> >)
//                               (generic_< floating_<A2> >)  
//                               )
//   {
//     typedef details::unifpdf_2<A0, A1, A2> inner; 
//     typedef typename inner::result_type result_type; 
//     NT2_FUNCTOR_CALL(3){ return inner::doit(a0, a1, a2);  }
    
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifpdf_, tag::cpu_
//                               , (A0)(A1)(A2)
//                               , (generic_< floating_<A0> >)
//                               (ast_< A1 >)
//                               (generic_< floating_<A2> >)  
//                               )
//   {
//     typedef details::unifpdf_2<A0, A1, A2> inner; 
//     typedef typename inner::result_type result_type; 
//     NT2_FUNCTOR_CALL(3){ return inner::doit(a0, a1, a2);  }
//   };
  
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifpdf_, tag::cpu_
//                               , (A0)(A1)(A2)
//                               , (generic_< floating_<A0> >)
//                               (generic_< floating_<A1> >)
//                               (ast_< A2 >)  
//                               )
//   {
//     typedef details::unifpdf_2<A0, A1, A2> inner; 
//     typedef typename inner::result_type result_type; 
//     NT2_FUNCTOR_CALL(3){ return inner::doit(a0, a1, a2);  }
//   };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifpdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< floating_<A0> >)
                              (ast_< floating_<A1> >)
                              (generic_< floating_<A2> >)  
                              )
  {
    typedef details::unifpdf_1<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){return inner::doit(a0, a1, a2);  }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifpdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (ast_< A0 >)
                              (generic_< floating_<A1> >)
                              (ast_< A2 >)  
                              )
  {
    typedef details::unifpdf_1<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){return inner::doit(a0, a1, a2);  }
  };
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifpdf_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (ast_< A1 >)
                              (ast_< A2 >)  
                              )
  {
    typedef details::unifpdf_1<A0, A1, A2> inner; 
    typedef typename inner::result_type result_type; 
    NT2_FUNCTOR_CALL(3){return inner::doit(a0, a1, a2);  }
  };
  
} }

#endif
