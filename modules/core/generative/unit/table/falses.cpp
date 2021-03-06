/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::falses function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/falses.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

template<class T, int N> struct hierarchy_impl
{
  typedef typename hierarchy_impl<T,N-1>::type base;
  typedef typename base::parent           type;
};

template<class T> struct hierarchy_impl<T,0>
{
  typedef typename nt2::meta::hierarchy_of<T>::type type;
};

template<class T, class N>
struct hierarchy : hierarchy_impl<T,N::value>
{};

NT2_TEST_CASE( falses_hierarchy )
{
  using boost::mpl::_;
  using boost::mpl::int_;

  NT2_TEST_EXPR_TYPE( (nt2::tag::falses_() )
                    , (hierarchy<_,int_<0> >)
                    , (nt2::tag::falses_)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::falses_() )
                    , (hierarchy<_,int_<1> >)
                    , (nt2::ext::generative_< nt2::tag::falses_ >
                      )
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::falses_() )
                    , (hierarchy<_,int_<2> >)
                    , (nt2::ext::elementwise_<nt2::tag::falses_>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::tag::falses_() )
                    , (hierarchy<_,int_<3> >)
                    , (nt2::ext::unspecified_<nt2::tag::falses_>)
                    );
}

NT2_TEST_CASE_TPL( falses_value_type, NT2_TYPES )
{
  using boost::mpl::_;
  using nt2::meta::value_type_;

  NT2_TEST_EXPR_TYPE( (nt2::falses(nt2::of_size(4,4)))
                    , (value_type_<_>)
                    , (nt2::logical<double>)
                    );

  NT2_TEST_EXPR_TYPE( (nt2::falses(nt2::of_size(4,4),nt2::meta::as_<T>()))
                    , (value_type_<_>)
                    , (nt2::logical<T>)
                    );
}

NT2_TEST_CASE( falses_size )
{
  NT2_TEST_EQUAL( nt2::extent( nt2::falses(nt2::of_size(4,5)) ), nt2::of_size(4,5 ) );
  NT2_TEST_EQUAL( nt2::size( nt2::falses(nt2::of_size(4,5)), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::falses(nt2::of_size(4,5)), 2 ), 5u );

  NT2_TEST_EQUAL( nt2::extent( nt2::falses(nt2::of_size(4,5,6)) ), nt2::of_size(4,5,6 ) );
  NT2_TEST_EQUAL( nt2::size( nt2::falses(nt2::of_size(4,5,6)), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::falses(nt2::of_size(4,5,6)), 2 ), 5u );
  NT2_TEST_EQUAL( nt2::size( nt2::falses(nt2::of_size(4,5,6)), 3 ), 6u );

  NT2_TEST_EQUAL( nt2::extent( nt2::falses(nt2::of_size(4,5,6,7)) ), nt2::of_size(4,5,6,7 ) );
  NT2_TEST_EQUAL( nt2::size( nt2::falses(nt2::of_size(4,5,6,7)), 1 ), 4u );
  NT2_TEST_EQUAL( nt2::size( nt2::falses(nt2::of_size(4,5,6,7)), 2 ), 5u );
  NT2_TEST_EQUAL( nt2::size( nt2::falses(nt2::of_size(4,5,6,7)), 3 ), 6u );
  NT2_TEST_EQUAL( nt2::size( nt2::falses(nt2::of_size(4,5,6,7)), 4 ), 7u );
}

NT2_TEST_CASE( falses_nd_untyped )
{
  nt2::table< nt2::logical<double> > x1 = nt2::falses(8);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x1(i) );

  nt2::table< nt2::logical<double> > x2 = nt2::falses(8,8);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x2(i) );

  nt2::table< nt2::logical<double> > x3 = nt2::falses(8,4,2);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x3(i) );

  nt2::table< nt2::logical<double> > x4 = nt2::falses(4,4,2,2);
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x4(i) );
}

NT2_TEST_CASE_TPL( falses_nd_typed, NT2_TYPES )
{
  nt2::table< nt2::logical<T> > x1 = nt2::falses(8, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x1(i) );

  nt2::table< nt2::logical<T> > x2 = nt2::falses(8,8, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x2(i) );

  nt2::table< nt2::logical<T> > x3 = nt2::falses(8,4,2, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x3(i) );

  nt2::table< nt2::logical<T> > x4 = nt2::falses(4,4,2,2, nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x4(i) );
}

NT2_TEST_CASE( falses_of_size )
{
  nt2::table< nt2::logical<double> > x2 = nt2::falses(nt2::of_size(8,8) );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x2(i) );

  nt2::table< nt2::logical<double> > x3 = nt2::falses(nt2::of_size(8,4,2) );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x3(i) );

  nt2::table< nt2::logical<double> > x4 = nt2::falses(nt2::of_size(4,4,2,2) );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x4(i) );
}

NT2_TEST_CASE_TPL( falses_typed_of_size, NT2_TYPES )
{
  nt2::table< nt2::logical<T> > x2 = nt2::falses(nt2::of_size(8,8), nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x2(i) );

  nt2::table< nt2::logical<T> > x3 = nt2::falses(nt2::of_size(8,4,2), nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x3(i) );

  nt2::table< nt2::logical<T> > x4 = nt2::falses(nt2::of_size(4,4,2,2), nt2::meta::as_<T>() );
  for(int i=1;i<=64;++i) NT2_TEST_EQUAL( false, x4(i) );
}

NT2_TEST_CASE( falses_expr )
{
  nt2::table<int> a( nt2::of_size(4,5) );

  nt2::table< nt2::logical<double> > x1 = nt2::falses( nt2::size(a) );
  for(int i=1;i<=20;++i) NT2_TEST_EQUAL( false, x1(i) );

  NT2_TEST_ASSERT( x1 = nt2::falses(a) );
}

NT2_TEST_CASE_TPL( falses_typed_expr, NT2_TYPES )
{
  nt2::table<int> a( nt2::of_size(4,5) );

  nt2::table< nt2::logical<T> > x1 = nt2::falses( nt2::size(a), nt2::meta::as_<T>() );
  for(int i=1;i<=20;++i) NT2_TEST_EQUAL( false, x1(i) );

  NT2_TEST_ASSERT( x1 = nt2::falses(a, nt2::meta::as_<T>()) );
}
