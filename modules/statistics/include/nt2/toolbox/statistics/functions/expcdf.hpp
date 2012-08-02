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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPCDF_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_exp expcdf
 *
 * \par Description
 * extonential  cumulative distribution
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/expcdf.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::expcdf_(A0)>::type
 *     expcdf(const A0 & a0, const A1 & a1, const A2 & a2);
 * }
 * \endcode
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag expcdf_ of functor expcdf 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct expcdf_ : ext::elementwise_<expcdf_> { typedef ext::elementwise_<expcdf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::expcdf_, expcdf, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::expcdf_, expcdf, 2)
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of expcdf.hpp
// /////////////////////////////////////////////////////////////////////////////
