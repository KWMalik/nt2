//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_BSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_BSXFUN_HPP_INCLUDED

#include <nt2/core/functions/bsxfun.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/functions/extent.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates from a 2ary thing and 2 expressions
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::bsxfun_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (ast_<A1>)
                              (ast_<A2>)
                            )
  {
    typedef typename A1::extent_type     ext1t_t;
    typedef typename A2::extent_type     ext2t_t;
    typedef typename meta::strip<ext1t_t>::type  ext1_t;
    typedef typename meta::strip<ext2t_t>::type  ext2_t;
    typedef typename make_size< !(ext1_t::static_size <= ext2_t::static_size)
                              ? ext1_t::static_size
                              : ext2_t::static_size
                              >::type                     ext_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::bsxfun_
                                          , container::domain
                                          , A1 const&
                                          , A2 const&
                                          , box<A0>
                                          , box<ext_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {

      ext_t s1 = nt2::extent(a1);
      ext_t s2 = nt2::extent(a2);
      ext_t sizee ;
      for(size_t i = 0; i < sizee.size(); ++i)
        {
          sizee[i] = s1[i];
          if (s1[i] == 1) sizee[i] = s2[i];
          if (s2[i] == 1) sizee[i] = s1[i];
          BOOST_ASSERT_MSG
          ( (s1[i] == s2[i]) || (s1[i] == 1) || (s2[i] == 1)
          , "Error using bsxfun:\n"
            "Non-singleton dimensions of the two input arrays "
            "must match each other."
          );
        }
      return  boost::proto::
              make_expr<nt2::tag::bsxfun_, container::domain>
              ( boost::cref(a1)
              , boost::cref(a2)
              , boxify(a0)
              , boxify(sizee)
              );
    }
  };

  //============================================================================
  // Generates from a 2ary thing, an expression and a scalar
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::bsxfun_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (ast_<A1>)
                              (scalar_< unspecified_<A2> >)
                            )
  {
    typedef typename A1::extent_type     ext1t_t;
    typedef typename meta::strip<ext1t_t>::type  ext_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::bsxfun_
                                          , container::domain
                                          , A1 const&
                                          , A2 const&
                                          , box<A0>
                                          , box<ext_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      return  boost::proto::
              make_expr<nt2::tag::bsxfun_, container::domain>
              ( boost::cref(a1)
              , boost::cref(a2)
              , boxify(a0)
              , boxify(nt2::extent(a1))
              );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::bsxfun_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (scalar_< unspecified_<A1> >)
                              (ast_<A2>)
                            )
  {
    typedef typename A2::extent_type     ext1t_t;
    typedef typename meta::strip<ext1t_t>::type  ext_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::bsxfun_
                                          , container::domain
                                          , A1 const&
                                          , A2 const&
                                          , box<A0>
                                          , box<ext_t>
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& a1,
                                             A2 const& a2) const
    {
      return  boost::proto::
              make_expr<nt2::tag::bsxfun_, container::domain>
              ( boost::cref(a1)
              , boost::cref(a2)
              , boxify(a0)
              , boxify(nt2::extent(a2))
              );
    }
  };
} }

#endif
