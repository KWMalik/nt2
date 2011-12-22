//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 r_mathlib toolbox - qbeta/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of r_mathlib components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 02/03/2011
/// 
#include <nt2/toolbox/r_mathlib/include/functions/qbeta.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/floating.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>

NT2_TEST_CASE_TPL ( qbeta_real__1_0,  NT2_REAL_TYPES)
{
  using nt2::r_mathlib::qbeta;
  using nt2::r_mathlib::tag::qbeta_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<qbeta_(T, T, T, iT, iT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  //put your tests here
  
} // end of test for floating_
