//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NOT_REAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NOT_REAL_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_predicates
 * \defgroup boost_simd_predicates_is_not_real is_not_real
 *
 * \par Description
 * Returns True<A0>() or False<A0>() according a0 is real or not.
 * For non complex numbers it is always false
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/is_not_real.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg is_false
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_not_real_(A0)>::type
 *     is_not_real(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of is_not_real
 * 
 * \return an integer value
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * This is a predicate operation. Such operations return bool in scalar mode,
 * but not in SIMD mode.
 * \par
 * The return type in SIMD mode is the common type of the parameters and is
 * a 'signed boolean' type. This means that in this case True has all its bits
 * sets to one. This is to facilitate masking operations. You are invited to
 * consult the rationale.
 *  
**/

namespace boost { namespace simd { namespace tag
  {         
    /*!
     * \brief Define the tag is_not_real_ of functor is_not_real 
     *        in namespace boost::simd::tag for toolbox boost.simd.predicates
    **/
    struct is_not_real_ : ext::elementwise_<is_not_real_> { typedef ext::elementwise_<is_not_real_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_not_real_, is_not_real,   1)
} }

#endif

// modified by jt the 25/12/2010
