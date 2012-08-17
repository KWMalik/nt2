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
#include <nt2/include/functions/sx_if_else.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/last_index.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>
#include <nt2/include/functions/linear_interp.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/floor.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/along.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/simd/logical.hpp>
namespace nt2 {
  template<class T, class N> inline
  typename nt2::meta::as_integer<N, signed>::type  fi(const T& x,  const N& i)
  {
    switch (i)
      {
      case 2 : return nt2::first_index<2>(x);
      case 3 : return nt2::first_index<3>(x);
      case 4 : return nt2::first_index<4>(x);  
      default : return nt2::first_index<1>(x); 
      }
  }
  template<class T, class N> inline
  typename nt2::meta::as_integer<N, signed>::type li(const T& x,  const N& i)
  {
    
    switch (i)
      {
      case 2 : return nt2::last_index<2>(x);
      case 3 : return nt2::last_index<3>(x);
      case 4 : return nt2::last_index<4>(x);  
      default : return nt2::last_index<1>(x); 
      }
  }
  
}
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
      std::cout << 1 << std::endl;
      bool extrap = false;
      std::cout << 2 << std::endl;
      std::size_t dim =nt2::firstnonsingleton(xi); 
      value_type extrapval = Nan<value_type>();
      choices(inputs, extrap, extrapval, dim, N1());
      std::cout << 3 << std::endl;
      nt2::of_size_max sizee;
      for(std::size_t i=0; i < sizee.size(); ++i) {sizee[i] = 1;  }
      std::cout << 4 << std::endl;
      std::cout << dim  << std::endl; 
      std::cout << sizee<< std::endl; 
      sizee[dim-1] = numel(xi);
      const value_type f = value_type(nt2::fi(y, dim));
      const value_type l = value_type(nt2::minusone(nt2::li(y, dim)));
      table<value_type>   index = nt2::min(nt2::max(f, nt2::floor(nt2::reshape(xi, sizee))), l);
      table<index_type>   i_index = nt2::toint(index);    
      table<value_type>  dx    =  sx<nt2::tag::minus_>(nt2::reshape(xi, sizee), index);
  
      yi =  linear_interp(dx, along(y, i_index, dim), along(y, oneplus(i_index), dim));
      NT2_DISPLAY(yi);           
//       if (!extrap) {
//         typedef typename nt2::meta::as_logical<value_type>::type         b_type;       
//         table<b_type> test = nt2::logical_or(boost::simd::is_nge(xi, value_type(first_index<2>(y))),
//                                              boost::simd::is_nle(xi, value_type(last_index<2>(y))));
//         NT2_DISPLAY(test); 
//         table<value_type> yy = yi;
//         table<value_type> yyy = nt2::tsxfun(nt2::functor<nt2::tag::if_else_>(), test,extrapval, yy);
//         NT2_DISPLAY(yy); 
//         std::cout << "icitte" << std::endl; 
//       }
      return yi;
    } 
  private :
    static void choices(const A1&, bool &,  value_type&,
                        std::size_t&, boost::mpl::long_<2> const &)
      { }
    static void choices(const A1& inputs,
                        bool & extrap, value_type& extrapval,
                        std::size_t& dim, boost::mpl::long_<3> const &)
      {
        typedef typename boost::proto::result_of::child_c<A1&,2>::type             child2;
        typedef typename meta::scalar_of<child2>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type;
        std::cout << type_id<nt2::meta::as_<param_type> >() << std::endl; 
        get(inputs, extrap, extrapval, nt2::meta::as_<param_type>());         
      }
    static void get(const A1& inputs, bool & extrap,
                    value_type&,  const nt2::meta::as_<bool> &)
      {
        extrap =  boost::proto::child_c<2>(inputs);
      }
    static void get(const A1& inputs, bool &,  value_type& extrapval,
                    const nt2::meta::as_<value_type> &)
      {
        extrapval =  boost::proto::child_c<2>(inputs);
      }
    static void get(const A1& inputs, bool &,  value_type& extrapval,
                    const nt2::meta::as_<nt2::container::colon_> &)
      {
      }

    static void choices(const A1& inputs,
                        bool & extrap, value_type& extrapval,
                        std::size_t& dim, boost::mpl::long_<4> const &)
      {
        dim =  boost::proto::child_c<3>(inputs);
        typedef typename boost::proto::result_of::child_c<A1&,2>::type             child2;
        typedef typename meta::scalar_of<child2>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type;
        get(inputs, extrap, extrapval,nt2::meta::as_<param_type>());         
      }
    
  }; 
} }


#endif
