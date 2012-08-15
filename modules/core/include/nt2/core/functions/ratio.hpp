//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_RATIO_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_RATIO_HPP_INCLUDED

#include <nt2/include/functor.hpp>

/*!
 * \ingroup core
 * \defgroup core ratio
 *
 * \par Description
 * compute sx-panded (b-x)/(b-a)
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/ratio.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0, class A1, class A2>
 *     meta::call<tag::ratio_(A0, A1, A2)>::type
 *     ratio(const A0 & x,const A1 & a,  onst A2 & b);
 * }
 * \endcode
 *
**/


namespace nt2
{
  namespace tag
  {
    struct ratio_ : tag::formal_
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
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::ratio_       , ratio, 3)

}


#endif
