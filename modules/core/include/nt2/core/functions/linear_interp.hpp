//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_LINEAR_INTERP_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_LINEAR_INTERP_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core linear_interp
 *
 * \par Description
 * Returns the sum of absolute values of the elements matrix along the selected direction,
 * i.e. the 1-norm linear_interp(a0, n))
 * by default n is the first non-singleton dimension of a0
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/linear_interp.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class A1, class A2>
 *     meta::call<tag::linear_interp_(A0, A1, A2)>::type
 *     linear_interp(const A0 & dx,onst A1 & a,  onst A2 & b);
 * }
 * \endcode
 *
**/


namespace nt2
{
  namespace tag
  {
    struct linear_interp_ : tag::formal_
    {
      typedef tag::formal_ parent;
    };
  }

  //============================================================================
  /*!
   * sum of absolute squares of a table
   *
   * \param xpr  table
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::linear_interp_       , linear_interp, 3)

}


#endif
