/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::settings of_size helper"

#include <boost/type_traits/is_same.hpp>
#include <nt2/core/settings/settings.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test of_size initializations
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( init_of_size )
{
  using nt2::of_size_;
  using nt2::memory::is_aligned;

  of_size_<-1>     spec1;
  NT2_TEST( is_aligned( &spec1[0] ));
  NT2_TEST_EQUAL( spec1.size(), 1 );
  NT2_TEST_EQUAL( spec1[0], 0 );

  of_size_<-1,-1>     spec2;
  NT2_TEST( is_aligned( &spec2[0] ));
  NT2_TEST_EQUAL( spec2.size(), 2 );
  NT2_TEST_EQUAL( spec2[0], 0 );
  NT2_TEST_EQUAL( spec2[1], 1 );

  of_size_<-1,-1,-1>     spec3;
  NT2_TEST( is_aligned( &spec3[0] ));
  NT2_TEST_EQUAL( spec3.size(), 3 );
  NT2_TEST_EQUAL( spec3[0], 0 );
  NT2_TEST_EQUAL( spec3[1], 1 );
  NT2_TEST_EQUAL( spec3[2], 1 );

  of_size_<-1,-1,-1,-1>     spec4;
  NT2_TEST( is_aligned( &spec4[0] ));
  NT2_TEST_EQUAL( spec4.size(), 4 );
  NT2_TEST_EQUAL( spec4[0], 0 );
  NT2_TEST_EQUAL( spec4[1], 1 );
  NT2_TEST_EQUAL( spec4[2], 1 );
  NT2_TEST_EQUAL( spec4[2], 1 );
}

////////////////////////////////////////////////////////////////////////////////
// Test of_size pre-initializations in case of static sizes
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE( pre_init_of_size )
{
  using nt2::of_size_;
  using nt2::memory::is_aligned;

  of_size_<42>     spec1;
  NT2_TEST( is_aligned( &spec1[0] ));
  NT2_TEST_EQUAL( spec1.size(), 1 );
  NT2_TEST_EQUAL( spec1[0], 42 );

  of_size_<6,9>     spec2;
  NT2_TEST( is_aligned( &spec2[0] ));
  NT2_TEST_EQUAL( spec2.size(), 2 );
  NT2_TEST_EQUAL( spec2[0], 6 );
  NT2_TEST_EQUAL( spec2[1], 9 );

  of_size_<4,2,6>     spec3;
  NT2_TEST( is_aligned( &spec3[0] ));
  NT2_TEST_EQUAL( spec3.size(), 3 );
  NT2_TEST_EQUAL( spec3[0], 4 );
  NT2_TEST_EQUAL( spec3[1], 2 );
  NT2_TEST_EQUAL( spec3[2], 6 );

  of_size_<1,3,5,7>     spec4;
  NT2_TEST( is_aligned( &spec4[0] ));
  NT2_TEST_EQUAL( spec4.size(), 4 );
  NT2_TEST_EQUAL( spec4[0], 1 );
  NT2_TEST_EQUAL( spec4[1], 3 );
  NT2_TEST_EQUAL( spec4[2], 5 );
  NT2_TEST_EQUAL( spec4[3], 7 );
}
