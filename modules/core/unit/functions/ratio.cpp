/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::ratio function"

#include <nt2/table.hpp>
#include <nt2/include/functions/ratio.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL( ratio_scalar, NT2_REAL_TYPES )
{
  T x = nt2::ratio(nt2::Half<T>(), T(42), T(43));
  NT2_TEST_EQUAL( x, T(42.5) );

}

NT2_TEST_CASE_TPL( ratio, (float)(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> dx, a, b;
  a = nt2::rif(5, 3, nt2::meta::as_<T>());
  b =  a+nt2::One<T>();
  dx = nt2::reshape(nt2::linspace(T(0), T(1), 15), 5, 3); 
  NT2_DISPLAY(a); 
  NT2_DISPLAY(b); 
  NT2_DISPLAY(dx); 
  NT2_TEST(nt2::isequal(nt2::ratio(nt2::Half<T>(), a, b), a+nt2::Half<T>()));
  nt2::table<T> z = nt2::ratio(dx, a, b);
  NT2_DISPLAY(z); 
  NT2_TEST(nt2::isequal(nt2::ratio(dx, a, b), a+oneminus(dx)));
  NT2_DISPLAY(nt2::ratio(dx, a, b));
  NT2_DISPLAY(nt2::ratio(dx, a, b)-z); 
}

