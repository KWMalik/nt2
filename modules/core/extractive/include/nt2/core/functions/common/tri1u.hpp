//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_TRI1U_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_TRI1U_HPP_INCLUDED

#include <nt2/core/functions/tri1u.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <nt2/include/functions/eq.hpp>
#include <nt2/include/functions/lt.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::tri1u_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::dispatch::meta::
            call<nt2::tag::run_ ( typename  boost::proto::result_of::
                                            child_c<A0&, 0>::type
                                , State&, Data&
                                )
                >::type                                        base_type;

    typedef typename meta::strip<base_type>::type              result_type;
    typedef typename meta::as_index<result_type>::type              i_t;
    typedef typename meta::
                     call<nt2::tag::enumerate_(State,meta::as_<i_t>)>::type p_t;
    typedef typename meta::call<nt2::tag::ind2sub_(_2D,p_t)>::type          s_t;
    typedef typename s_t::value_type                                        sp_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Retrieve 2D position from the linear index
      s_t const  pos = ind2sub(_2D(a0.extent()),nt2::enumerate<i_t>(p));
      sp_t const is  = pos[0];
      sp_t const js  = pos[1];

      // Return the upper triangular section with 1 on the diagonal
      return nt2::if_else ( nt2::eq(is, js)
                          , One<result_type>()
                          , nt2::if_else( nt2::lt(is, js)
                                        , nt2::run( boost::proto::child_c<0>(a0)
                                                  , p
                                                  , t
                                                  )
                                        , Zero<result_type>()
                                        )
                          );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::offset_tri1u_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::dispatch::meta::
            call<nt2::tag::run_ ( typename  boost::proto::result_of::
                                            child_c<A0&, 0>::type
                                , State&, Data&
                                )
                >::type                                        base_type;

    typedef typename meta::strip<base_type>::type              result_type;;
    typedef typename meta::as_index<result_type>::type              i_t;
    typedef typename meta::
                     call<nt2::tag::enumerate_(State,meta::as_<i_t>)>::type p_t;
    typedef typename meta::call<nt2::tag::ind2sub_(_2D,p_t)>::type          s_t;
    typedef typename s_t::value_type                                        sp_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Retrieve 2D position from the linear index
      s_t const  pos = ind2sub(_2D(a0.extent()),nt2::enumerate<i_t>(p));
      sp_t const is  = pos[0];
      sp_t const js  = pos[1] - boost::proto::value(boost::proto::child_c<1>(a0));

      // Return the shifted upper triangular section with 1 on the diagonal
      return nt2::if_else ( nt2::eq(is, js)
                          , One<result_type>()
                          , nt2::if_else( nt2::lt(is, js)
                                        , nt2::run( boost::proto::child_c<0>(a0)
                                                  , p
                                                  , t
                                                  )
                                        , Zero<result_type>()
                                        )
                          );
    }
  };
} }

#endif
