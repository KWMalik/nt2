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
#ifndef NT2_TOOLBOX_STATISTICS_DISTRIBUTIONS_CAUCDF_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_DISTRIBUTIONS_CAUCDF_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup statistics
 * \defgroup statistics_exp2 exp2
 *
 * \par Description
 * cauchy cumulative distribution
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/caucdf.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::caucdf_(A0)>::type
 *     caucdf(const A0 & a0, const A1 & a1, const A2 & a2);
 * }
 * \endcode
 *
 *   p = betacdf(x,m, l) finds the cauchy cdf with
 *   median  m, and scale l. remenber that the cauchy distribution
 *   have no mean value (nor finite variance)
 *
 *   the size of p is the common size of the input arguments. A scalar input  
 *   functions as a constant matrix of the same size as the other inputs.    
 *
 *   default values for m and l are 0 and 1 respectively. 
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag caucdf_ of functor caucdf 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct caucdf_ : ext::elementwise_<caucdf_> { typedef ext::elementwise_<caucdf_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::caucdf_, caucdf, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::caucdf_, caucdf, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::caucdf_, caucdf, 3)  
}

#endif
