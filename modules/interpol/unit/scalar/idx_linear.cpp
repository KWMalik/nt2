/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::sum1 function"

#include <nt2/table.hpp>
#include <nt2/include/functions/idx_linear.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/trans.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

// NT2_TEST_CASE_TPL( idx_linear_scalar, (float)(double))//NT2_TYPES )
// {
//   T x = nt2::idx_linear(T(42));
//   NT2_TEST_EQUAL( x, T(42) );

//   x = nt2::idx_linear(T(42),1);
//   NT2_TEST_EQUAL( x, T(42) );

//   x = nt2::idx_linear(T(42),0);
//   NT2_TEST_EQUAL( x, T(42) );

// }

NT2_TEST_CASE_TPL( idx_linear, (float))//(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::linspace(T(1),  T(4), 4); 
  nt2::table<T> xi=  nt2::linspace(T(0),  T(5), 11);
  NT2_DISPLAY(x);
  NT2_DISPLAY(xi); 
  nt2::table<T> yi =nt2::idx_linear(x, xi); 
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl; 
  NT2_DISPLAY(yi); 
  yi =nt2::idx_linear(x, xi, false); 
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl; 
  NT2_DISPLAY(yi); 
  std::cout << "extrap " <<  true <<  " extrapval " << "-" << std::endl; 
  yi =nt2::idx_linear(x, xi, true); 
  NT2_DISPLAY(yi);
  T z =  T(33); 
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl; 
  yi =nt2::idx_linear(x, xi, z); 
  NT2_DISPLAY(yi); 
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl; 
  yi =nt2::idx_linear(x, xi, T(33)); 
  NT2_DISPLAY(yi); 
}

NT2_TEST_CASE_TPL( idx_linear1, (float))//(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::reshape(nt2::linspace(T(1),  T(16), 16), 4, 4); 
  nt2::table<T> xi=  nt2::linspace(T(1),  T(3), 11);
  NT2_DISPLAY(x);
  NT2_DISPLAY(xi); 
  nt2::table<T> yi =nt2::idx_linear(x, xi); 
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl; 
  NT2_DISPLAY(yi); 
  yi =nt2::idx_linear(x, xi, false); 
  std::cout << "extrap " <<  false <<  " extrapval " << "-" << std::endl; 
  NT2_DISPLAY(yi); 
  std::cout << "extrap " <<  true <<  " extrapval " << "-" << std::endl; 
  yi =nt2::idx_linear(x, xi, true); 
  NT2_DISPLAY(yi);
  T z =  T(33); 
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl; 
  yi =nt2::idx_linear(x, xi, z); 
  NT2_DISPLAY(yi); 
  std::cout << "extrap " <<  "-" <<  " extrapval " << "33" << std::endl; 
  yi =nt2::idx_linear(x, xi, T(33)); 
  NT2_DISPLAY(yi); 
}
NT2_TEST_CASE_TPL( idx_linear2, (float))//(double))//NT2_TYPES )
{
  using nt2::_;
  nt2::table<T> x =  nt2::reshape(nt2::linspace(T(1),  T(16), 16), 4, 4); 
  nt2::table<T> xi=  nt2::linspace(T(0),  T(4), 11);
  NT2_DISPLAY(x);
  NT2_DISPLAY(xi); 
  nt2::table<T> yi; 
 //  yi =nt2::idx_linear(x, xi, _, 2lu); 
  std::cout << "1 extrap " <<  false <<  " extrapval " << "-" <<  " dim " << "2" << std::endl; 
  NT2_DISPLAY(yi); 
  yi =nt2::idx_linear(x, nt2::trans(xi), _, 1lu); 
  std::cout << "2 extrap " <<  false <<  " extrapval " << "-" <<  " dim " << "1" << std::endl; 
  NT2_DISPLAY(yi);
  yi =nt2::idx_linear(x, xi, _, 1lu); 
  std::cout << "3 extrap " <<  false <<  " extrapval " << "-" << std::endl; 
  NT2_DISPLAY(yi);
  
   yi =nt2::idx_linear(x, xi, false); 
   std::cout << "4 extrap " <<  false <<  " extrapval " << "-" << std::endl; 
   NT2_DISPLAY(yi);

   yi =nt2::idx_linear(x, xi, false, _, 1); 
   std::cout << "5 extrap " <<  false <<  " extrapval " << "-" << std::endl; 
   NT2_DISPLAY(yi);
   
   std::cout << "6 extrap " <<  true <<  " extrapval " << "-" << std::endl; 
   yi =nt2::idx_linear(x, xi, true, _, 1); 
   NT2_DISPLAY(yi);
 
  std::cout << "7 extrap " <<  "-" <<  " extrapval1 " << "33" <<  " extrapval2 " << "42" << std::endl; 
  yi =nt2::idx_linear(x, xi, T(33), T(42), 1); 
  NT2_DISPLAY(yi); 
 }
