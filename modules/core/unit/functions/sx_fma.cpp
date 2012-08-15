/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sx_fma function"

#include <nt2/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/sx_multiplies.hpp>
#include <nt2/include/functions/sx_plus.hpp>
#include <nt2/include/functions/sx_fma.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL( sx, NT2_TYPES )
{
  using nt2::_; 
  nt2::table<T> a = nt2::reshape(nt2::_(T(1), T(9)), 3, 3);
  NT2_TEST( nt2::isequal(nt2::sx_fma(a, a, a), a*a+a));
  NT2_TEST( nt2::isequal(nt2::sx_fma(a, a(1, _), a(_, 1)), sx_plus(sx_multiplies(a, a(1, _)), a(_, 1)))); 
}

