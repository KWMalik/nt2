//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SX_FMA_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SX_FMA_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/functions/details/sxify.hpp>
#include <nt2/include/functions/fma.hpp>

//============================================================================
/*!
 * sx-ification of operator *
 *
 * \param xpr  table
 */
//============================================================================
//   NT2_TSXIFY(fma)

  namespace nt2 {                                                       
    namespace tag {                                                     
      struct sx_fma_ : tag::formal_{                                
        typedef tag::formal_ parent;                                    
      };                                                                
    }                                                                   
    NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sx_fma_, sx_fma, 3)     
    namespace ext {                                                     
      NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sx_fma_, tag::cpu_,     
                                  (A0)(A1)(A2),                         
                                  (ast_<A0>)(ast_<A1>)(ast_<A2>)        
                                  )                                     
      {                                                                 
        typedef typename meta::call                                     
          <tag::sx_(tag::fma_,                                        
                    const A0&,                                          
                    const A1&,                                          
                    const A2&)>::type                                   
                    result_type;                                        
      BOOST_FORCEINLINE result_type operator()(A0 const& a0,            
                                               A1 const& a1,            
                                               A2 const& a2) const      
      {                                                                 
        return nt2::tsxfun(nt2::functor<nt2::tag::fma_>(), a0, a1, a2);                      
      }                                                                 
    };                                                                  
  }     
      
}


#endif
