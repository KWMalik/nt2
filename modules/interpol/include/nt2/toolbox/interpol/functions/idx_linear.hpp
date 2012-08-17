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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_IDX_LINEAR_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_IDX_LINEAR_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup interpol
 * \defgroupinterpol_idx_linear idx_linear
 *
 * \par Description
 * one dimensional idx_linear interpolation
 * given an array a and a vector idx of "real" indices
 * provides the interpolated values along the a rows
 * by linear formula.
 * calls can be idx_linear(x, y)
 *              idx_linear(x, y, true) allowing extrapolation
 *              idx_linear(x, y, val1) putting val1 outside the bounds
 *              idx_linear(x, y, val1, val2)}, putting val1 under the index bounds val2 ovr
 *              idx_linear(x, y, _, dim) dim is the dimension of interpolation firstnonsingletopn of xi by default
 *              idx_linear(x, y, val1, dim)
 *              idx_linear(x, y, val1, val2, dim) can also be used
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/idx_linear.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::idx_linear_(A0)>::type
 *     idx_linear(const A0 & a, const A1 & xi);
 * }
 * \endcode
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag idx_linear_ of functor idx_linear 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct idx_linear_ : ext::unspecified_<idx_linear_> { typedef ext::unspecified_<idx_linear_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 2)  
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 3)  
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::idx_linear_, idx_linear, 5)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct size_of<tag::idx_linear_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 1>::value_type child1;
    typedef typename child1::extent_type                               result_type; 

    result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<1>(e).extent();
    }
  };

 template <class Domain, class Expr,  int N>
 struct value_type < tag::idx_linear_, Domain,N,Expr> {
   typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type  child1;
   typedef typename nt2::meta::scalar_of<child1>::type                    elt_type;
   typedef typename nt2::meta::strip<elt_type>::type                          type;
 }; 
} } }
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of idx_linear.hpp
// /////////////////////////////////////////////////////////////////////////////
