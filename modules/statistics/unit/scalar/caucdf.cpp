//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 statistics toolbox - caucdf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
/// 
#include <nt2/include/functions/caucdf.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( caucdf_1,  (float))//NT2_REAL_TYPES)
{
  
  using nt2::caucdf;
  using nt2::tag::caucdf_;
  using nt2::_; 
  

  // specific values tests
  NT2_TEST_ULP_EQUAL(caucdf(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(caucdf(nt2::One<T>()), 3*nt2::One<T>()/4, 0);
  NT2_TEST_ULP_EQUAL(caucdf(nt2::Zero<T>()), nt2::Half<T>(), 0);
  NT2_TEST_ULP_EQUAL(caucdf(nt2::Inf<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(caucdf(nt2::Minf<T>()), nt2::Zero<T>(), 0);

  nt2::table<T> a = _(T(-5), T(1), T(5));
  NT2_DISPLAY(a); 
  NT2_DISPLAY(caucdf(a)); 
} // end of test for floating_
 
NT2_TEST_CASE_TPL ( caucdf_2,  NT2_REAL_TYPES)
{
  
  using nt2::caucdf;
  using nt2::tag::caucdf_;
  using nt2::_; 
  

  // specific values tests
  NT2_TEST_ULP_EQUAL(caucdf(nt2::Nan<T>(), nt2::Mone<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(caucdf(nt2::Zero<T>(), nt2::Mone<T>() ), 3*nt2::One<T>()/4, 0);
  NT2_TEST_ULP_EQUAL(caucdf(nt2::Mone<T>(), nt2::Mone<T>()), nt2::Half<T>(), 0);
  NT2_TEST_ULP_EQUAL(caucdf(nt2::Inf<T>(), nt2::Mone<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(caucdf(nt2::Minf<T>(), nt2::Mone<T>()), nt2::Zero<T>(), 0);

  nt2::table<T> a = _(T(-5), T(1), T(5));
  NT2_DISPLAY(a); 
  NT2_DISPLAY(caucdf(a, nt2::One<T>()));
  NT2_DISPLAY(caucdf(nt2::One<T>(), a)); 
  a = nt2::reshape(_(T(1), T(16)), 4, 4);
  NT2_DISPLAY(caucdf(a, a)); 
  NT2_DISPLAY(caucdf(a, a(_, 1)));
  NT2_DISPLAY(caucdf(a, a(1, _)));
  NT2_DISPLAY(caucdf(a, a, a));
  NT2_DISPLAY(caucdf(a, nt2::Zero<T>(),  a(_, 1)));        
    NT2_DISPLAY(caucdf(a, a(1, _), a(_, 1)));
} // end of test for floating_
 
