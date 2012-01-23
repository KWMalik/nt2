//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_SIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_SIZE_HPP_INCLUDED

#include <nt2/table.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/functions/extent.hpp>
#include <nt2/core/container/category.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::size_, tag::cpu_
                            , (A0)(T)
                            , ((expr_ < unspecified_<A0>
                                      , nt2::container::domain, T
                                      >
                              ))
                            )
  {
    typedef typename meta::call<tag::extent_(A0)>::type base;
    typedef typename meta::strip<base>::type            ext_t;

    typedef table < std::size_t
                  , settings(automatic_,of_size_<1,ext_t::static_size>)
                  >                                         result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(const A0& a0) const
    {
      result_type that( of_size_< 1, ext_t::static_size>()
                      , nt2::extent(a0).begin()
                      , nt2::extent(a0).end()
                      );
      return that;
    }
  };
} }

#endif
