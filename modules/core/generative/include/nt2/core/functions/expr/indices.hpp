//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_INDICES_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_INDICES_HPP_INCLUDED

#include <nt2/core/functions/indices.hpp>
#include <nt2/include/functions/isrow.hpp>
#include <nt2/include/functions/ndims.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/core/functions/details/indices.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/utility/box.hpp>
#include <nt2/core/utility/of_size.hpp>
#include <nt2/sdk/memory/copy.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef meta::constant_<nt2::tag::indices_,double> constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::indices_
                                          , container::domain
                                          , box<of_size_max>
                                          , box<constant_t>
                                          , meta::as_<double>
                                          >::type             result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const & dim) const
    {
      // Expression must be a row vector
      BOOST_ASSERT_MSG
      ( nt2::isrow(a0) && (nt2::ndims(a0) <= 2)
      , "Error using indices: Size vector must be a 2D row vector."
      );

      of_size_max sizee;
      std::size_t sz = std::min(of_size_max::size(),nt2::length(a0));
      nt2::memory::cast_copy(a0.raw(), a0.raw()+sz, &sizee[0]);

      return boost::proto::make_expr< nt2::tag::indices_
                                    , container::domain
                                    > ( boxify(sizee)
                                      , boxify(constant_t(dim))
                                      , meta::as_<double>()
                                      );
    }
  };

  ///INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                            , (A0)(A1)(T)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename T::type                                    value_t;
    typedef meta::constant_<nt2::tag::indices_,value_t>  constant_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::indices_
                                          , container::domain
                                          , box<of_size_max>
                                          , box<constant_t>
                                          , T
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const & dim, T const& tgt) const
    {
      // Expression must be a row vector
      BOOST_ASSERT_MSG
      ( nt2::isrow(a0) && (nt2::ndims(a0) <= 2)
      , "Error using indices: Size vector must be a 2D row vector."
      );

      of_size_max sizee;
      std::size_t sz = std::min(of_size_max::size(),nt2::length(a0));
      nt2::memory::cast_copy(a0.raw(), a0.raw()+sz, &sizee[0]);

      return boost::proto::make_expr< nt2::tag::indices_
                                    , container::domain
                                    > ( boxify(sizee)
                                      , boxify(constant_t(dim))
                                      , tgt
                                      );
    }
  };
} }

#endif
