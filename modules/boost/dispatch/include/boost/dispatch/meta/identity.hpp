//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_IDENTITY_HPP_INCLUDED
#define BOOST_DISPATCH_META_IDENTITY_HPP_INCLUDED

#include <boost/dispatch/meta/as_ref.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace dispatch
{
  struct identity
  {
    template<class Sig>
    struct result;
    
    template<class This, class A0>
    struct result<This(A0)> : meta::as_ref<A0>
    {
    };
    
    template<class A0>
    BOOST_DISPATCH_FORCE_INLINE
    A0& operator()(A0& a0) const
    {
      return a0;
    }
  };
} }

#endif
