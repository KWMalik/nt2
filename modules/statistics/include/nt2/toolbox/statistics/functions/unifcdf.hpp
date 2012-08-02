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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_UNIFCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_UNIFCDF_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_unif unifcdf
 *
 * \par Description
 * uniform cumulative distribution
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/unifcdf.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::unifcdf_(A0)>::type
 *     unifcdf(const A0 & a0, const A1 & a = 0, const A2 & b = 1);
 * }
 * \endcode
 *
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag unifcdf_ of functor unifcdf 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct unifcdf_ : ext::elementwise_<unifcdf_> { typedef ext::elementwise_<unifcdf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::unifcdf_, unifcdf, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::unifcdf_, unifcdf, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::unifcdf_, unifcdf, 3)  
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of unifcdf.hpp
// /////////////////////////////////////////////////////////////////////////////
