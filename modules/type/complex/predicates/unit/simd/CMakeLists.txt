##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

set( SOURCES
  is_nan.cpp
  is_equal.cpp
  is_eqz.cpp
  is_imag.cpp
  is_inf.cpp
  is_finite.cpp
  is_invalid.cpp
  is_not_equal.cpp
  is_not_finite.cpp
  is_not_infinite.cpp
   )

nt2_module_add_tests(type.complex.predicates.simd.unit ${SOURCES})
