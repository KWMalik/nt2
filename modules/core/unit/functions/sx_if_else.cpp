/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sx_if_else function"

#include <nt2/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/sx_if_else.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL( sx, NT2_REAL_TYPES )
{
  using nt2::_; 
  nt2::table<T> a = nt2::reshape(nt2::_(T(1), T(9)), 3, 3);
  nt2::table<T> b =              nt2::_(T(4), T(6));
  nt2::table<T> c =              nt2::_(T(6), T(-1), T(4));
  NT2_DISPLAY(a);
  NT2_DISPLAY(b);
  NT2_DISPLAY(c);
  //  NT2_DISPLAY( nt2::sx_if_else(le(b, c), a, a+a)); //nt2::Zero<T>()));
  NT2_DISPLAY( nt2::sx_if_else(le(b, c), nt2::Zero<T>(), a)); //nt2::Zero<T>()));

}

