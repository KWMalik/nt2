//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_CORE_SETTINGS_SETTINGS_HPP_INCLUDED
#define BOOST_DISPATCH_CORE_SETTINGS_SETTINGS_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  //===========================================================================
  /*! 
   * settings is a seed type that allow contruction of multiple options pack.
   * If a given container needs to have options A and B set, settings(A,B) will
   * perform such a task. 
   **/
  //============================================================================
  struct settings {};
}

namespace nt2 { namespace meta
{
  //============================================================================
  // empty settings list returns default for any option
  //============================================================================
  template<class Option, class Default>
  struct option<settings(),Option,Default> { typedef Default type; };

  //============================================================================
  // settings list of one argument return the argument option value
  //============================================================================
  template<class S0, class Option, class Default>
  struct  option< settings(S0), Option, Default >
        : option<S0,Option,Default>
  {};

  //============================================================================
  // Non-empty settings lists are recursively inspected
  //============================================================================
  #define M0(z,n,t)                                                       \
  template< BOOST_PP_ENUM_PARAMS(n,class S), class Option, class Default> \
  struct option < settings(BOOST_PP_ENUM_PARAMS(n,S)), Option, Default >  \
  {                                                                       \
    typedef typename                                                      \
            option< settings(BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(n),S))     \
                  , Option, Default>::type                  base_type;    \
    typedef typename                                                      \
            option< BOOST_PP_CAT(S,BOOST_PP_DEC(n))                       \
                  , Option,base_type>::type                 type;         \
  };                                                                      \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,NT2_META_MAX_OPTIONS_NB,M0,~)
  
  #undef M0
} }

#endif
