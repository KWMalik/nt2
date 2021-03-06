//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 bessel toolbox - y1/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bessel components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 16/02/2011
/// 
#include <nt2/toolbox/bessel/include/functions/y1.hpp>
#include <nt2/include/functions/ulpdist.hpp>
extern "C" {long double cephes_y1l(long double);}

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( y1_real__1_0,  NT2_REAL_TYPES)
{
  
  using nt2::y1;
  using nt2::tag::y1_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<y1_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_ULP_EQUAL(y1(nt2::Inf<T>()), nt2::Zero<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(y1(nt2::One<T>()), r_t(-7.812128213002889e-01), 1.5);
  NT2_TEST_ULP_EQUAL(y1(nt2::Zero<T>()), nt2::Minf<r_t>(), 0);
} // end of test for floating_
