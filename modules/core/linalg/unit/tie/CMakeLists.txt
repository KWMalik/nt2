##############################################################################
###   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
###   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
###
###          Distributed under the Boost Software License, Version 1.0
###                 See accompanying file LICENSE.txt or copy at
###                     http://www.boost.org/LICENSE_1_0.txt
##############################################################################

SET( SOURCES
     chol.cpp
     lu.cpp
     qr.cpp
     svd.cpp
     schur.cpp
     symeig.cpp
     balance.cpp
     rref.cpp
     planerot.cpp
     linsolve.cpp
     full_qr_solve.cpp
     full_lu_solve.cpp
     svd_solve.cpp
     tr_solve.cpp
     lsq_lse_solve.cpp
   )

nt2_module_add_tests(core.linalg.tie.unit ${SOURCES})

