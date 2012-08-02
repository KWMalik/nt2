/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPINV_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPINV_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_exp expinv
 *
 * \par Description
 * exponential inverse cumulative distribution
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/expinv.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::expinv_(A0)>::type
 *     expinv(const A0 & a0, const A1 & m = 1);
 * }
 * \endcode
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag expinv_ of functor expinv 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct expinv_ : ext::elementwise_<expinv_> { typedef ext::elementwise_<expinv_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::expinv_, expinv, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::expinv_, expinv, 2)
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of expinv.hpp
// /////////////////////////////////////////////////////////////////////////////
