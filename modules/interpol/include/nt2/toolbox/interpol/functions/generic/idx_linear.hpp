/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTERPOL_FUNCTIONS_GENERIC_IDX_LINEAR_HPP_INCLUDED
#define NT2_TOOLBOX_INTERPOL_FUNCTIONS_GENERIC_IDX_LINEAR_HPP_INCLUDED
#include <nt2/core/container/table/table.hpp>

#include <nt2/include/functions/is_nge.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/linear_interp.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/simd/logical.hpp>

namespace nt2 { namespace ext
{
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N1)
                              , (ast_<A0>)
                              ((node_<A1,nt2::tag::idx_linear_,N1>))
                              )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       value_t;
    typedef typename boost::proto::result_of::child_c<A1&,1>::type         idx_t;
    typedef typename meta::scalar_of<value_t>::type              cref_value_type;
    typedef typename meta::strip<cref_value_type>::type               value_type; 
    typedef typename meta::as_integer<value_type>::type               index_type;      
    typedef typename A0::value_type                                    sale_type; 
    typedef A0&                                                      result_type;
    
    result_type operator()(A0& yi, A1& inputs) const
    {
      //      BOOST_ASSERT_MSG(are_sx_compatible(xi, y), "Inputs dimensions are not compatible"); 
      const idx_t & xi   =  boost::proto::child_c<1>(inputs);
      const value_t & y     =  boost::proto::child_c<0>(inputs);
      bool extrap = false;
      value_type extrapval = Nan<value_type>();
      choices(inputs, extrap, extrapval, N1());
      table<value_type>   index = nt2::floor(xi);
      table<index_type>   i_index = toint(index);    
      table<value_type>  dx    =  sx<nt2::tag::minus_>(xi, index); 
      yi =  linear_interp(dx, y(i_index), y(oneplus(i_index)));
      if (!extrap) yi = nt2::if_else(nt2::logical_or(boost::simd::is_nge(xi, value_type(first_index<2>(y))),
                                                     boost::simd::is_nle(xi, value_type(last_index<2>(y)))),
                                     extrapval, yi);
      return yi;
    } 
  private :
    static void choices(const A1&, bool &,  value_type&, boost::mpl::long_<2> const &)
      { }
    static void choices(const A1& inputs, bool & extrap,  value_type& extrapval, boost::mpl::long_<3> const &)
      {
        typedef typename boost::proto::result_of::child_c<A1&,2>::type             child2;
        typedef typename meta::scalar_of<child2>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type; 
        get(inputs, extrap, extrapval, param_type());         
      }
    static void get(const A1& inputs, bool & extrap,  value_type&,  const bool &)
      {
        extrap =  boost::proto::child_c<2>(inputs);
      }
    static void get(const A1& inputs, bool &,  value_type& extrapval,  const value_type &)
      {
        extrapval =  boost::proto::child_c<2>(inputs);
      }
  }; 
} }


#endif
