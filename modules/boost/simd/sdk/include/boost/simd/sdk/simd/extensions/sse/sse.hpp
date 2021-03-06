/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_EXTENSIONS_SSE_SSE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_EXTENSIONS_SSE_SSE_HPP_INCLUDED

#if defined(__SSE__) || defined(_M_X64) || _M_IX86_FP >= 1
#  ifndef BOOST_SIMD_HAS_SSE_SUPPORT
#    define BOOST_SIMD_HAS_SSE_SUPPORT
#  endif
#elif defined(BOOST_SIMD_HAS_SSE_SUPPORT) && !defined(_MSC_VER)
#  undef BOOST_SIMD_HAS_SSE_SUPPORT
#endif

#if !defined(BOOST_SIMD_DETECTED) && defined(BOOST_SIMD_HAS_SSE_SUPPORT)

////////////////////////////////////////////////////////////////////////////////
// SSE2 extensions flags
////////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_DETECTED
#define BOOST_SIMD_SSE
#define BOOST_SIMD_SSE_FAMILY
#define BOOST_SIMD_STRING             "SSE"
#define BOOST_SIMD_STRING_LIST        "SSE"
#define BOOST_SIMD_BYTES              16
#define BOOST_SIMD_BITS               128
#define BOOST_SIMD_CARDINALS          (4)
#define BOOST_SIMD_TAG_SEQ            (::boost::simd::tag::sse_)
#define BOOST_SIMD_DEFAULT_EXTENSION  ::boost::simd::tag::sse_
#define BOOST_SIMD_DEFAULT_SITE       ::boost::simd::tag::sse_

#include <emmintrin.h>

#include <boost/simd/sdk/simd/extensions/meta/sse.hpp>

#endif
#endif
