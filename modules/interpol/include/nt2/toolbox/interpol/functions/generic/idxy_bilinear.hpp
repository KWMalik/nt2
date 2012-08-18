/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTERPOL_FUNCTIONS_GENERIC_IDXY_BILINEAR_HPP_INCLUDED
#define NT2_TOOLBOX_INTERPOL_FUNCTIONS_GENERIC_IDXY_BILINEAR_HPP_INCLUDED
#include <nt2/core/container/table/table.hpp>

#include <nt2/include/functions/is_nge.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/sx_if_else.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/idx_linear.hpp>
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
#include <boost/fusion/include/make_vector.hpp>

namespace nt2 { namespace ext
{
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N1)
                              , (ast_<A0>)
                              ((node_<A1,nt2::tag::idxy_bilinear_,N1>))
                              )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type       value_t;
    typedef typename boost::proto::result_of::child_c<A1&,1>::type         idx_t;
    typedef typename boost::proto::result_of::child_c<A1&,2>::type         idy_t;
    typedef typename meta::scalar_of<value_t>::type              cref_value_type;
    typedef typename meta::strip<cref_value_type>::type               value_type; 
    typedef typename meta::as_integer<value_type>::type               index_type;      
    typedef typename A0::value_type                                    sale_type; 
    typedef A0&                                                      result_type;
    typedef typename A0::extent_type                                       ext_t;

    typedef boost::fusion::vector<value_type, value_type>                 f_type; 
    
    result_type operator()(A0& r, A1& inputs) const
    {
      //      std::cout << N1::value << std::endl; 
      //      BOOST_ASSERT_MSG(are_sx_compatible(xi, y), "Inputs dimensions are not compatible"); 
      const idx_t & xi   =  boost::proto::child_c<1>(inputs);
      const idx_t & yi   =  boost::proto::child_c<2>(inputs);
      const value_t & y     =  boost::proto::child_c<0>(inputs);
      //       NT2_DISPLAY(y); 
      //       NT2_DISPLAY(xi);
      //       NT2_DISPLAY(yi);
      //       NT2_DISPLAY(inputs.extent());
      bool extrap = false;
      std::size_t dim1 = 2;
      std::size_t dim2 = 1;  
      value_type extrapval1x = Nan<value_type>();
      value_type extrapval2x = extrapval1x;
      value_type extrapval1y = extrapval1x;
      value_type extrapval2y = extrapval1x;
      choices(inputs, extrap, extrapval1x, extrapval2x, extrapval1y, extrapval2y, dim1, dim2, N1());
      ext_t siz;
      siz[0] = 1; 
      siz[dim1-1] = numel(xi);
      siz[dim2-1] = numel(yi);
      r.resize(siz);
      //       std::cout << siz     << std::endl;
      //       std::cout << size(r) << std::endl; 
      r = idx_linear(y,xi,true,nt2::_,dim1);
      //      NT2_DISPLAY(r); 
      r = idx_linear(r,yi,true,nt2::_,dim2);
      //      NT2_DISPLAY(r); 
      if (!extrap) {
        ext sizee; sizee[0] = 1;
        sizee[dim1-1] = numel(xi);
        value_type fx = value_type(nt2::first_index(y, dim1));
        value_type lx = value_type(nt2::minusone(nt2::last_index(y, dim1)));
        r = nt2::tsxfun(nt2::functor<nt2::tag::if_else_>(), nt2::reshape(boost::simd::is_nge(xi, value_type(fx)), sizee),extrapval1x, r);
        r = nt2::tsxfun(nt2::functor<nt2::tag::if_else_>(), nt2::reshape(boost::simd::is_nle(xi, value_type(lx)), sizee),extrapval2x, r); 
        sizee[dim1-1] = 1;
        sizee[dim2-1] = numel(yi);
        value_type fy = value_type(nt2::first_index(y, dim2));
        value_type ly = value_type(nt2::minusone(nt2::last_index(y, dim2)));
        r = nt2::tsxfun(nt2::functor<nt2::tag::if_else_>(), nt2::reshape(boost::simd::is_nge(yi, value_type(fy)), sizee),extrapval1x, r);
        r = nt2::tsxfun(nt2::functor<nt2::tag::if_else_>(), nt2::reshape(boost::simd::is_nle(yi, value_type(ly)), sizee),extrapval2x, r); 
      } 
      return r;
    } 
  private :
    // three inputs y and xi and yi
    // idxy_bilinear(y, xi, yi)
    static void choices(const A1&, bool &,  value_type&, value_type&, value_type&, value_type&,
                        std::size_t&, std::size_t&, boost::mpl::long_<3> const &)  //nothing to get  
      { }
    // Four inputs y and xi yi and a bool or a floating 
    // idxy_bilinear(y, xi, yi, true)
    // idxy_bilinear(y, xi, yi, extrapval)
    static void choices(const A1& inputs,
                        bool & extrap,
                        value_type& extrapval1x, value_type& extrapval2x,
                        value_type& extrapval1y, value_type& extrapval2y,
                        std::size_t& dim1, std::size_t& dim2,
                        boost::mpl::long_<4> const &)
      {
        typedef typename boost::proto::result_of::child_c<A1&,3>::type             child3;
        typedef typename meta::scalar_of<child3>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type;
        get(inputs, extrap, extrapval1x, extrapval2x, extrapval1y, extrapval2y, nt2::meta::as_<param_type>());         
      }
    static void get(const A1& inputs, bool & extrap,
                    value_type&, value_type&,
                    value_type&, value_type&,
                    const nt2::meta::as_<bool> &) //get the bool
      {
        extrap =  boost::proto::child_c<3>(inputs);
      }
    static void get(const A1& inputs, bool &,
                    value_type& extrapval1x, value_type& extrapval2x,
                    value_type& extrapval1y, value_type& extrapval2y,
                    const nt2::meta::as_<value_type> &)                     //get extrapval/1x/2x/1y/2y common value (default Nan)
      {
        extrapval1x =  extrapval2x = extrapval1y = extrapval2y = boost::proto::child_c<3>(inputs);
      }
    
    // Five inputs y and xi yi and two floatings
    static void choices(const A1& inputs,
                        bool & extrap,
                        value_type& extrapval1x, value_type& extrapval2x,
                        value_type& extrapval1y, value_type& extrapval2y,
                        std::size_t& dim1, std::size_t& dim2,
                        boost::mpl::long_<5> const &)                //get extrapval/1x/2x and extrapval/1y/2y commons values 
      {
        extrapval1x = extrapval1y = boost::proto::child_c<3>(inputs);
        extrapval2x = extrapval2y = boost::proto::child_c<4>(inputs);    
      }
    
    // Six inputs y and xi yi,  _ or bool and 2 integers
    static void choices(const A1& inputs,
                        bool & extrap,
                        value_type&, value_type&,
                        value_type&, value_type&,
                        std::size_t& dim1, std::size_t& dim2,
                        boost::mpl::long_<6> const &)                //get extrapval/1x/2x and extrapval/1y/2y commons values 
      {
        typedef typename boost::proto::result_of::child_c<A1&,3>::type             child3;
        typedef typename meta::scalar_of<child3>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type;
        get(inputs, extrap, nt2::meta::as_<param_type>());  
        dim1 = boost::proto::child_c<4>(inputs);
        dim2 = boost::proto::child_c<5>(inputs);    
      }
    static void get(const A1& inputs, bool & extrap,
                    const nt2::meta::as_<bool> &) //get the bool
      {
        extrap =  boost::proto::child_c<2>(inputs);
      }
    static void get(const A1& inputs, bool & extrap,
                    const nt2::meta::as_<nt2::container::colon_> &) //nothing to get
      { }
    
    // Seven inputs y and xi yi and 4 floating 
    // idxy_bilinear(y, xi, yi, extrapval1x, extrapval2x, extrapval1y, extrapval2y)
    
    static void choices(const A1& inputs,
                        bool &,
                        value_type& extrapval1x, value_type& extrapval2x,
                        value_type& extrapval1y, value_type& extrapval2y,
                        std::size_t&, std::size_t&,
                        boost::mpl::long_<7> const &)
      {
        extrapval1x = boost::proto::child_c<3>(inputs);
        extrapval2x = boost::proto::child_c<4>(inputs);
        extrapval1y = boost::proto::child_c<5>(inputs);
        extrapval2y = boost::proto::child_c<6>(inputs);
      }
    
    // eight inputs y and xi, yi, 4 floatings,  _, and 2 integer
    static void choices(const A1& inputs,
                        bool &,
                        value_type& extrapval1x, value_type& extrapval2x,
                        value_type& extrapval1y, value_type& extrapval2y,
                        std::size_t& dim1, std::size_t& dim2,
                        boost::mpl::long_<8> const &) //get extrapval1 and extrapval2 and dimension
      {
        dim1 =  boost::proto::child_c<7>(inputs);
        dim2 =  boost::proto::child_c<8>(inputs);  
        extrapval1x = extrapval1y = boost::proto::child_c<3>(inputs);
        extrapval2x = extrapval2y = boost::proto::child_c<4>(inputs);
      }
    
    // ten inputs y and xi, yi, two flotings,  _, and 2 integer
    static void choices(const A1& inputs,
                        bool & extrap,
                        value_type& extrapval1x, value_type& extrapval2x,
                        value_type& extrapval1y, value_type& extrapval2y,
                        std::size_t& dim1, std::size_t& dim2,
                        boost::mpl::long_<10> const &) //get extrapval1 and extrapval2 and dimension
      {
        dim1 =  boost::proto::child_c<8>(inputs);
        dim2 =  boost::proto::child_c<9>(inputs);  
        extrapval1x = boost::proto::child_c<3>(inputs);
        extrapval2x = boost::proto::child_c<4>(inputs);
        extrapval1y = boost::proto::child_c<5>(inputs);
        extrapval2y = boost::proto::child_c<6>(inputs);
      }
  }; 
} }


#endif
