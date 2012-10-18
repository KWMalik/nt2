/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_VANDERMONDE_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_GALLERY_VANDERMONDE_HPP_INCLUDED
#include <nt2/toolbox/linalg/functions/vandermonde.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/colvect.hpp>

namespace nt2 {namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vandermonde_, tag::cpu_,
                              (A0)(A1),
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                              )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call<tag::colvect_(A0)>::type  T0;
    typedef typename meta::call<tag::colon_ ( value_type
                                            , value_type
                                            , value_type
                                            )>::type      T1;
    typedef typename meta::call<tag::bsxfun_( nt2::functor<tag::pow_>
                                            , T0
                                            , T1
                                            )>::type      result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return nt2::bsxfun( nt2::functor<tag::pow_>()
                          , colvect(a0)
                          , colon ( value_type(a1-1)
                                  , value_type(-1)
                                  , value_type(0)
                                  )
                          );
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::vandermonde_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename A0::value_type value_type;
    typedef typename meta::call<tag::colvect_(A0)>::type  T0;
    typedef typename meta::call<tag::colon_ ( value_type
                                            , value_type
                                            , value_type
                                            )>::type      T1;
    typedef typename meta::call<tag::bsxfun_( nt2::functor<tag::pow_>
                                            , T0
                                            , T1)>::type  result_type;
    NT2_FUNCTOR_CALL(1)
      {
        return nt2::bsxfun( nt2::functor<tag::pow_>()
                          , colvect(a0)
                          , colon ( value_type( numel(a0) - 1)
                                  , value_type(-1)
                                  , value_type(0)
                                  )
                          );
      }
  };
} }

#endif
