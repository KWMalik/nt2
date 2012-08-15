/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_FUNCTIONS_DETAILS_SXIFY_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_SXIFY_HPP_INCLUDED
#include <nt2/include/functions/sx.hpp>


#define NT2_BSXIFY(Tag)                                                 \
  namespace nt2 {                                                       \
    namespace tag {                                                     \
      struct sx_##Tag##_ : tag::formal_{                                \
        typedef tag::formal_ parent;                                    \
      };                                                                \
    }                                                                   \
    NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sx_##Tag##_, sx_##Tag, 2)     \
    namespace ext {                                                     \
      NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sx_##Tag##_, tag::cpu_,     \
                                  (A0)(A1), (ast_<A0>)(ast_<A1>)        \
                                  )                                     \
      {                                                                 \
        typedef typename meta::call                                     \
          <tag::sx_(tag::Tag##_,                                        \
                    const A0&,                                          \
                    const A1&)>::type                                   \
                    result_type;                                        \
      BOOST_FORCEINLINE result_type operator()(A0 const& a0,            \
                                               A1 const& a1) const      \
      {                                                                 \
        return nt2::sx(tag::Tag##_(), a0, a1);                          \
      }                                                                 \
    };                                                                  \
  }                                                                     \
  /**/
#define NT2_TSXIFY(Tag)                                                 \
  namespace nt2 {                                                       \
    namespace tag {                                                     \
      struct sx_##Tag##_ : tag::formal_{                                \
        typedef tag::formal_ parent;                                    \
      };                                                                \
    }                                                                   \
    NT2_FUNCTION_IMPLEMENTATION(nt2::tag::sx_##Tag##_, sx_##Tag, 3)     \
    namespace ext {                                                     \
      NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sx_##Tag##_, tag::cpu_,     \
                                  (A0)(A1)(A2),                         \
                                  (ast_<A0>)(ast_<A1>)(ast_<A2>)        \
                                  )                                     \
      {                                                                 \
        typedef typename meta::call                                     \
          <tag::sx_(tag::Tag##_,                                        \
                    const A0&,                                          \
                    const A1&,                                          \
                    const A2&)>::type                                   \
                    result_type;                                        \
      BOOST_FORCEINLINE result_type operator()(A0 const& a0,            \
                                               A1 const& a1,            \
                                               A2 const& a2) const      \
      {                                                                 \
        return nt2::sx(tag::Tag##_(), a0, a1, a2);                      \
      }                                                                 \
    };                                                                  \
  }                                                                     \
  /**/


#endif

