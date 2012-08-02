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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_NORMCDF_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_norm normcdf
 *
 * \par Description
 * normal cumulative distribution
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/normcdf.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::normcdf_(A0)>::type
 *     normcdf(const A0 & a0, const A1 & m = 0, const A2 & sig = 1);
 * }
 * \endcode
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag normcdf_ of functor normcdf 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct normcdf_ : ext::elementwise_<normcdf_> { typedef ext::elementwise_<normcdf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::normcdf_, normcdf, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::normcdf_, normcdf, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::normcdf_, normcdf, 3)  
}

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of normcdf.hpp
// /////////////////////////////////////////////////////////////////////////////
