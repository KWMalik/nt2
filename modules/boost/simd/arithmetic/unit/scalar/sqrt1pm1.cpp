//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - sqrt1pm1/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 01/12/2010
/// modified by jt the 06/04/2011
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/toolbox/arithmetic/include/functions/sqrt1pm1.hpp>

NT2_TEST_CASE_TPL ( sqrt1pm1_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  
  using boost::simd::sqrt1pm1;
  using boost::simd::tag::sqrt1pm1_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<sqrt1pm1_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  // specific values tests
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Inf<T>()), boost::simd::Inf<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Minf<T>()), boost::simd::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Mone<T>()), boost::simd::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Nan<T>()), boost::simd::Nan<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::One<T>()), boost::simd::Sqrt_2<r_t>()-boost::simd::One<r_t>(), 2);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Zero<T>()), boost::simd::Zero<r_t>(), 0);
} // end of test for floating_

NT2_TEST_CASE_TPL ( sqrt1pm1_unsigned_int__1_0,  BOOST_SIMD_UNSIGNED_TYPES)
{
  
  using boost::simd::sqrt1pm1;
  using boost::simd::tag::sqrt1pm1_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<sqrt1pm1_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::One<T>()), boost::simd::Sqrt_2<r_t>()-boost::simd::One<r_t>(), 2);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Zero<T>()), boost::simd::Zero<r_t>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( sqrt1pm1_signed_int__1_0,  BOOST_SIMD_INTEGRAL_SIGNED_TYPES)
{
  
  using boost::simd::sqrt1pm1;
  using boost::simd::tag::sqrt1pm1_;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef typename boost::dispatch::meta::call<sqrt1pm1_(T)>::type r_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type u_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 

  // specific values tests
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Mone<T>()), boost::simd::Mone<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::One<T>()), boost::simd::Sqrt_2<r_t>()-boost::simd::One<r_t>(), 2);
  NT2_TEST_ULP_EQUAL(sqrt1pm1(boost::simd::Zero<T>()), boost::simd::Zero<r_t>(), 0);
} // end of test for signed_int_
