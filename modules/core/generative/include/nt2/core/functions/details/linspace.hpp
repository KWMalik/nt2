//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_DETAILS_LINSPACE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_DETAILS_LINSPACE_HPP_INCLUDED

#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/sdk/meta/constant_adaptor.hpp>

namespace nt2 { namespace tag { struct linspace_; }}

namespace nt2 { namespace meta
{
  //============================================================================
  // linspace actual functor : precompute step and just iterate over
  //============================================================================
  template<class T>
  struct constant_<tag::linspace_,T>
  {
    typedef T                                          result_type;
    constant_() {}
    constant_( T const& l, T const& u, std::size_t n )
            : n_(n-1), lower_(l), step_((u-l)/(n-1)), upper_(u)
    {}

    template<class Pos, class Size, class Target>
    typename Target::type
    operator()(Pos const& p, Size const&, Target const&) const
    {
      typedef typename Target::type type;
      type en = nt2::enumerate<type>(p);
      return nt2::if_else ( eq(en, nt2::splat<type>(n_))
                          , nt2::splat<type>(upper_)
                          , nt2::fma ( en
                                     , nt2::splat<type>(step_)
                                     , nt2::splat<type>(lower_)
                                     )
                          );
    }

    std::size_t n_;
    T lower_, step_, upper_;
  };
} }

#endif
