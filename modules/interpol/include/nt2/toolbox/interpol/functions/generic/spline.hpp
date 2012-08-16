/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_INTERPOL_FUNCTIONS_GENERIC_SPLINE_HPP_INCLUDED
#define NT2_TOOLBOX_INTERPOL_FUNCTIONS_GENERIC_SPLINE_HPP_INCLUDED
#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/ppval.hpp>
#include <nt2/include/functions/is_nge.hpp>
#include <nt2/include/functions/is_nle.hpp>
#include <nt2/include/functions/issorted.hpp>
#include <nt2/include/functions/bsearch.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/arereal.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/simd/logical.hpp>
#include <nt2/sdk/meta/type_id.hpp>

namespace nt2 { namespace ext
{
  namespace details
  {
    /* plain gauss elimination, only not bothering with the zeroes
     *
     *       diag(0)  abovediag(0)             0   .....
     *  belowdiag(0)       diag(1)  abovediag(1)   .....
     *             0  belowdiag(1)       diag(2)
     *             0             0  belowdiag(2)   .....
     */
    template < class T > 
    void solve_sym_tridiag(const nt2::table < T_> & diag,
                           const nt2::table < T > & abovediag,
                           const nt2::table < T > & rhs,
                           nt2::table < T > & x)
    {
      const size_t N =  nt2::numel(diag); 
      nt2::table < T, nt2::C_index > alpha = diag, z = rhs, above = abovediag ; 
      size_t i, j;
      
      alpha(0) = diag(0);
      z(0) = rhs(0);
      
      for (i = 0; i < last_index<2>(alpha); i++)
        {
          const double t = abovediag((i))/alpha(i);
          alpha(i+1) -= t*abovediag((i));
          z(i+1) -= t*z(i);
          /* FIXME!!! */
            BOOST_ASSERT_MSG(alpha(i+1) == 0, "singular spline system"); 
        }
      
      /* backsubstitution */
      x.resize(of_size(1, N)); 
      x((N - 1)) = z(N - 1)/alpha(N - 1);
      if (N >= 2)
        {
          for (i = N - 2, j = 0; j <= N - 2; j++, i--)
            {
              x(i) = (z(i) - abovediag(i) * x((i + 1)))/alpha(i);
            }
        }
      
    }
   
  }
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N1)
                              , (ast_<A0>)
                              ((node_<A1,nt2::tag::spline_,N1>))
                              )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::type        child0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::type        child1;
    typedef typename boost::proto::result_of::child_c<A1&,2>::type        child2;
    typedef typename meta::scalar_of<child0>::type               cref_value_type;
    typedef typename meta::strip<cref_value_type>::type               value_type; 
    typedef typename meta::as_integer<value_type>::type               index_type;      
    typedef table<value_type>                                             vtab_t;
    typedef table<index_type>                                             itab_t;
    typedef A0&                                                      result_type;
    
    
    result_type operator()(A0& yi, A1& inputs) const
    {
       const child0 & x   =  boost::proto::child_c<0>(inputs);
       BOOST_ASSERT_MSG(issorted(x, 'a'), "for 'spline' interpolation x values must be sorted in ascending order"); 
       const child1 & y   =  boost::proto::child_c<1>(inputs);
       const child2 & xi  =  boost::proto::child_c<2>(inputs);
       bool extrap = false;
       value_type extrapval = Nan<value_type>();
       choices(inputs, extrap, extrapval, N1());
       vtab_t h  =  nt2::diff(x,1,2);
       vtab_t del = nt2::diff(y,1,2)/h;
       splineslopes(x,y,del, yi);
       ppval <value_type> pp(x,y,yi,h,del);
       yi =pp.eval(xi); 
       if (!extrap) yi = nt2::if_else(nt2::logical_or(boost::simd::is_nge(xi, x(begin_)), boost::simd::is_nle(xi, x(end_))),
                                      extrapval,
                                      yi);
       return yi;
    } 
  private :
    static void choices(const A1&, bool &,  value_type&, boost::mpl::long_<3> const &)
      { }
    static void choices(const A1& inputs, bool & extrap,  value_type& extrapval, boost::mpl::long_<4> const &)
      {
        typedef typename boost::proto::result_of::child_c<A1&,3>::type             child3;
        typedef typename meta::scalar_of<child3>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type; 
        get(inputs, extrap, extrapval, param_type());         
      }
    static void get(const A1& inputs, bool & extrap,  value_type&,  const bool &)
      {
        extrap =  boost::proto::child_c<3>(inputs);
      }
    static void get(const A1& inputs, bool &,  value_type& extrapval,  const value_type &)
      {
        extrapval =  boost::proto::child_c<3>(inputs);
      }
  }; 
} }




// template < class T > class spline{
// public:
//   typedef T                                                type_t;
//   typedef typename ttt::float_promotion< type_t >::type_t float_t;
//   template < class XPR1,  class XPR2 > spline(const XPR1 & x,  const XPR2 & y):
//     x_array(x), y_array(y), 
//     num_points(x.numel()), max_index(num_points-1), sys_size(max_index-1), c(ofSize(1, num_points))
    
//                                              //       off_diag(1, sys_size), diag(1, sys_size), g(1, sys_size)
//   {
//     init();
//   }
// private:
//   nt2::table < float_t > x_array;
//   nt2::table < float_t > y_array;
//   size_t num_points, max_index, sys_size; 
//   nt2::table < float_t > c;
//   nt2::table < float_t > off_diag;
//   nt2::table < float_t > diag;
//   nt2::table < float_t > g;
  
//   void init()
//   {
//     nt2::table < float_t > dx = diff(x_array, 1, 2);
//     nt2::table < float_t > dy = diff(y_array, 1, 2);
//     off_diag = dx(Range(Begin()+1, End()));
    
//     nt2::table < float_t >  h        = dx(0, Range(Begin(), End()-1)); 
//     diag    =  2.0*(off_diag + h);
//     g       =  3.0*( div(dy(0, Range(Begin()+1, End())), off_diag)-
//                      div(dy(0, Range(Begin(), End()-1)), h));
//     if (sys_size == 1)
//       {
//         c(Begin()+1) = g(Begin())/diag(Begin());
//         return; 
//       }
//     else
//       {
//         nt2::table <float_t > sol(ofSize(1, num_points)); 
//         solve_sym_tridiag(diag, off_diag, g, sol);
//         c(Range(Begin()+1, End()-1)) = sol; 
//       }
//   }
  
//   /* function for common coefficient determination
//    */
//   void coeff_calc (const nt2::table < float_t > &  dy,
//                    const nt2::table < float_t > &  dx,
//                    const nt2::table < ptrdiff_t > & index,  
//                    nt2::table < float_t >  & bi,
//                    nt2::table < float_t > & ci,
//                    nt2::table < float_t > & di)const
//   {
//     ci = c(0, index);
//     const nt2::table < float_t > c_ip1 = c(0, index + 1);
//     bi = div(dy,dx) - mul(dx, (c_ip1 + 2.0 * ci)) / 3.0;
//     di = div((c_ip1 - ci),  (3.0 * dx));
//   }
  
// public:
//   template < typename XPR3> 
//   nt2::table < float_t >   eval (const XPR3 & x, bool extrap = false)const{
//     nt2::table < ptrdiff_t > index = bsearch (x_array, x);
//     nt2::table < float_t >  x_hi = x_array(0, index + 1);
//     nt2::table < float_t >  x_lo = x_array(0, index);
//     nt2::table < float_t >  dx   = x_hi - x_lo;
//     nt2::table < float_t >  y_lo = y_array(0, index);
//     nt2::table < float_t >  dy   = y_array(0, index + 1)-y_lo;
//     nt2::table < float_t >  b_i, c_i, d_i; 
//     coeff_calc(dy, dx, index,  b_i, c_i, d_i);
//     nt2::table < float_t >  delx  = x - x_lo;
//     nt2::table < float_t >  y  = y_lo + mul(delx,  (b_i + mul(delx,  (c_i + mul(delx,  d_i)))));
//     if(!extrap) y(x < float(x_array(Begin())) || x >  float(x_array(End()))) = NaN < float_t > (); 
//     return y; 
//   }
  
// };


// /////////////////////////////////////////////////////////////////////
// /// End of spline1.hh
// /////////////////////////////////////////////////////////////////////

#endif
