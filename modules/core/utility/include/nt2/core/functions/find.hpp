//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_FIND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_FIND_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the find function
**/

#include <nt2/include/functor.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/sdk/memory/container_shared_ref.hpp>

namespace nt2
{
  namespace tag
  {
    /*!
      @brief Tag for the find functor
    **/
    struct find_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  /*!
    @brief

    @param
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 1)

  /*!
    @brief

    @param
    @param
  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::find_, find, 2)
}

#endif
