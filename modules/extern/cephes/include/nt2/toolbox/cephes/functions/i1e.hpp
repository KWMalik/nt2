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
#ifndef NT2_TOOLBOX_CEPHES_FUNCTIONS_I1E_HPP_INCLUDED
#define NT2_TOOLBOX_CEPHES_FUNCTIONS_I1E_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup cephes
 * \defgroup cephes_i1e i1e
 *
 * \par Description
 * Please for details consult the proper documentation of the external
 * library cephes.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/toolbox/cephes/include/functions/i1e.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   namespace cephes
 *   {
 *     template <class A0>
 *       meta::call<tag::i1e_(A0)>::type
 *       i1e(const A0 & a0);
 *   }
 * }
 * \endcode
 *
 * \param a0 the unique parameter of i1e
 * 
 * \return an integer value
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * When calling external library, nt2 simply encapsulates the
 * original proper call to provide easy use.
 * \par
 * Remenber that SIMD implementation is therefore merely
 * mapping the scalar function to each SIMD vectors elements
 * and will not provide acceleration, but ease.
 * \par
 * cephes library defines functions for float and double entries.
 * \par
 * As they are written in C the original name of the float version is
 * generally terminated by and extra 'f',
 * this is not the case for the nt2 version which dispatch to
 * the correct function according to the inputs types.
 *  
**/

namespace nt2 { namespace cephes { namespace tag
  {         
    /*!
     * \brief Define the tag i1e_ of functor i1e 
     *        in namespace nt2::cephes::tag for toolbox cephes
    **/
    struct i1e_ : ext::elementwise_<i1e_> { typedef ext::elementwise_<i1e_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(cephes::tag::i1e_, i1e, 1)
  } }

#include <nt2/toolbox/cephes/functions/scalar/i1e.hpp>
// #include <nt2/toolbox/cephes/functions/simd/all/i1e.hpp> 

#endif

// modified by jt the 29/12/2010
