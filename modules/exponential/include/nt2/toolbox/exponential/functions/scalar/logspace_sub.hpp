//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_LOGSPACE_SUB_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_FUNCTIONS_SCALAR_LOGSPACE_SUB_HPP_INCLUDED
#include <nt2/include/functions/logspace_sub.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/constants/log_2.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( logspace_sub_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)(scalar_< arithmetic_<A0> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::logspace_sub(result_type(a0), result_type(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( logspace_sub_, tag::cpu_
                            , (A0)
                            , (scalar_< floating_<A0> >)(scalar_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A0 x =  a1-a0; 
      A0 tmp = gt(x, -Log_2<A0>()) ? nt2::log(-expm1(x)) : nt2::log1p(-exp(x)); 
      return a0 + tmp; 
    }
  };
} }

#endif
