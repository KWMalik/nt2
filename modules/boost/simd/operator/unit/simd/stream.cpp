//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::memory::stream"

#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/stream.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/simd/sdk/memory/aligned_type.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <exception>

////////////////////////////////////////////////////////////////////////////////
// Test store behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(stream, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::stream;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             n_t;
  static const std::size_t card = cardinal_of<n_t>::value;

  BOOST_SIMD_ALIGNED_TYPE(T) data[3*card];
  for(std::size_t i=0;i<card;++i)
    data[i] = T(1+i);

  n_t v = load<n_t>(&data[0],0);
  stream(v,&data[0],card);

  for(std::size_t j=0;j<card;++j)
  {
    NT2_TEST_EQUAL( data[j], data[j+card] );
  }

#ifdef NT2_ASSERTS_AS_EXCEPTIONS
  NT2_TEST_NO_THROW( v = stream<n_t>(v,&data[0],card) );
  NT2_TEST_THROW( v = stream<n_t>(v,&data[0]+1,card), nt2::assert_exception);
#endif
}
