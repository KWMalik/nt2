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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMINV_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMINV_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_norm norminv
 *
 * \par Description
 * normal cumulative distribution
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/norminv.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::norminv_(A0)>::type
 *     norminv(const A0 & a0, const A1 & m = 0, const A2 & sig = 1);
 * }
 * \endcode
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag norminv_ of functor norminv 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct norminv_ : ext::elementwise_<norminv_> { typedef ext::elementwise_<norminv_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::norminv_, norminv, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::norminv_, norminv, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::norminv_, norminv, 3)  
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of norminv.hpp
// /////////////////////////////////////////////////////////////////////////////
