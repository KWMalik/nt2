//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 fdlibm toolbox - modf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of fdlibm components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 03/03/2011
///
#include <nt2/toolbox/fdlibm/include/functions/modf.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/max.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/include/functions/frac.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>


NT2_TEST_CASE_TPL ( modf_double_1_0,  (double))
{

  using nt2::fdlibm::modf;
  using nt2::fdlibm::tag::modf_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<modf_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef boost::fusion::vector<T,T> wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, T(-10), T(10));
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    T a0;
    for(nt2::uint32_t j =0; j < NR; ++j )
      {
        std::cout << "for param "
                  << "  a0 = "<< u_t(a0 = tab_a0[j])
                  << std::endl;
        r_t r = nt2::fdlibm::modf(a0);
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,0>::type>::type r_t0;
        typedef typename nt2::meta::strip<typename boost::fusion::result_of::at_c<r_t,1>::type>::type r_t1;
        r_t0 r0 = boost::fusion::get<0>(r);
        r_t1 r1 = boost::fusion::get<1>(r);
        NT2_TEST_ULP_EQUAL( r0, nt2::frac(a0), 1);
        if (ulpd>ulp0) ulp0=ulpd;
        NT2_TEST_ULP_EQUAL( r1, nt2::trunc(a0), 1);
        if (ulpd>ulp0) ulp0=ulpd;
     }
     std::cout << "max ulp found is: " << ulp0 << std::endl;
   }
} // end of test for double
