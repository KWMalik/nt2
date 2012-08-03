//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 statistics toolbox - expcdf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
/// 
#include <nt2/include/functions/expcdf.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( expcdf_1,  (float))//NT2_REAL_TYPES)
{
  
  using nt2::expcdf;
  using nt2::tag::expcdf_;
  using nt2::_; 
  

  // specific values tests
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::One<T>()),  T(0.63212055882855766598), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Zero<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Inf<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Minf<T>()), nt2::Zero<T>(), 0);

  nt2::table<T> a = _(T(-5), T(1), T(5));
  NT2_DISPLAY(a); 
  NT2_DISPLAY(expcdf(a)); 
} // end of test for floating_
 
NT2_TEST_CASE_TPL ( expcdf_2,  (float))//NT2_REAL_TYPES)
{
  
  using nt2::expcdf;
  using nt2::tag::expcdf_;
  using nt2::_; 
  

  // specific values tests
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Zero<T>(), nt2::One<T>() ), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::One<T>(), nt2::One<T>()),  T(0.63212055882855766598), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Inf<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(expcdf(nt2::Minf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0);

   nt2::table<T> a = _(T(-5), T(1), T(5));
   NT2_DISPLAY(a); 
   NT2_DISPLAY(expcdf(a, nt2::One<T>()));
   NT2_DISPLAY(expcdf(nt2::One<T>(), a));
   a = nt2::reshape(_(T(1), T(16)), 4, 4);
   nt2::table<T> z = expcdf(a, a); 
   NT2_DISPLAY(z);
   NT2_DISPLAY(expcdf(a, a)); 
   NT2_DISPLAY(expcdf(a, a(_, 1)));
   NT2_DISPLAY(expcdf(a, a(1, _)));
} // end of test for floating_
 
