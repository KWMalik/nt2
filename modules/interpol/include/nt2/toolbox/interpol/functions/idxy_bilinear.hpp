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
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_IDXY_BILINEAR_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_IDXY_BILINEAR_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup interpol
 * \defgroupinterpol_idxy_bilinear idxy_bilinear
 *
 * \par Description
 * one dimensional idxy_bilinear interpolation
 * given an array a and a vector idx of "real" indices
 * provides the interpolated values along the a rows
 * by bilinear formula.
 * calls can be idxy_bilinear(a, idx, idy)
 *              idxy_bilinear(a, idx, idy, true) allowing extrapolation
 *              idxy_bilinear(a, idx, idy, val1) putting val1 outside the bounds
 *              idxy_bilinear(a, idx, idy, val1, val2)}, putting val1 under the index bounds val2 ovr
 *              idxy_bilinear(a, idx, idy, val1x val2x, val1y, val2y)
 *              idxy_bilinear(a, idx, idy, _, dim1, dim2) are the dimensions of interpolation firstnonsingleton, secondnonsingleton of a by default
 *              idxy_bilinear(a, idx, idy, val1, dim1, dim2)
 *              idxy_bilinear(a, idx, idy, val1, val2, dim1, dim2)
 *              idxy_bilinear(a, idx, idy,  val1x val2x, val1y, val2y, dim1, dim2) can also be used
 * \par
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/idxy_bilinear.hpp>
 * \endcode
 * 
 *  
**/

namespace nt2 { namespace tag
  {         
    /*!
     * \brief Define the tag idxy_bilinear_ of functor idxy_bilinear 
     *        in namespace nt2::tag for toolbox statistics
    **/
    struct idxy_bilinear_ : ext::unspecified_<idxy_bilinear_> { typedef ext::unspecified_<idxy_bilinear_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 3)  
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 4)
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 5)
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 6)  
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 7)
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 9)
  NT2_FUNCTION_IMPLEMENTATION(tag::idxy_bilinear_, idxy_bilinear, 10)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, class Expr,  int N>
  struct size_of<tag::idxy_bilinear_, Domain, N, Expr>
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 1>::value_type child1;
    typedef typename child1::extent_type                               result_type; 

    result_type operator()(Expr& e) const
    {
      return boost::proto::child_c<1>(e).extent();
    }
  };

 template <class Domain, class Expr,  int N>
 struct value_type < tag::idxy_bilinear_, Domain,N,Expr> {
   typedef typename boost::proto::result_of::child_c<Expr&, 0>::value_type  child1;
   typedef typename nt2::meta::scalar_of<child1>::type                    elt_type;
   typedef typename nt2::meta::strip<elt_type>::type                          type;
 }; 
} } }
#endif

// /////////////////////////////////////////////////////////////////////////////
// End of idxy_bilinear.hpp
// /////////////////////////////////////////////////////////////////////////////
