/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPR_CAURND_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_EXPR_CAURND_HPP_INCLUDED


#include <nt2/toolbox/statistics/functions/caurnd.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/cauinv.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/size.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                              , (A0)(A0b)
                              , (unspecified_<A0> )
                              (unspecified_<A0b> )
                            )
  {
    typedef typename meta::scalar_of<A0>::type                                          sA0; 
    typedef meta::as_<sA0>                                                              TGT; 
    typedef nt2::table<sA0>                                                           tab_t; 
    typedef typename meta::call<tag::cauinv_(tab_t,A0 const&,A0b const&)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& m, A0b const& l) const
    {
//       std::cout << nt2::type_id(nt2::max(nt2::size(m), nt2::size(l))) << std::endl;
//       std::cout << nt2::size(m) <<  "   " << nt2::size(l) << std::endl;
       nt2::table<unsigned long> s = nt2::max(nt2::size(m), nt2::size(l));
//       std::cout << "s " << s << std::endl; 
      tab_t r = nt2::rand(s, meta::as_<sA0>()); 
      return nt2::cauinv(r, m, l); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                              , (A0)(A0b)(A1)
                              , (unspecified_<A0> )
                              (unspecified_<A0b> )
                              (unspecified_<A1>)
                            )
  {
    typedef typename meta::scalar_of<A0>::type                                          sA0; 
    typedef meta::as_<sA0>                                                              TGT;
    typedef nt2::table<sA0>                                                           tab_t; 
    typedef typename meta::call<tag::cauinv_(tab_t,A0 const&,A0b const&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A0b const& l, A1 const& a1) const
    {
      nt2::table<sA0> pipo(a1); 
      nt2::table<sA0> r = nt2::rand(nt2::max(nt2::size(pipo), nt2::max(nt2::size(l), nt2::size(m))), meta::as_<sA0>()); 
      return nt2::cauinv(r, m, l); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                              , (A0)(A0b)(A1)
                              , (unspecified_<A0> )
                              (unspecified_<A0b> )
                              (scalar_<integer_<A1> >)
                              )
  {
    typedef nt2::of_size_<-1l, -1l, 1l, 1l>                                           T1; 
    typedef typename meta::call<tag::caurnd_(T1,A0 const&,A0b const&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A0b const& l,
                                             A1 const& a1) const
    {
      return nt2::caurnd(nt2::of_size(a1, a1), m, l); 
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                              , (A0)(A0b)(A1)(A2)
                              , (unspecified_<A0> )
                              (unspecified_<A0b> )
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                              )
  {
    typedef nt2::of_size_<-1l, -1l, 1l, 1l>                                           T1; 
    typedef typename meta::call<tag::caurnd_(T1,A0 const&,A0b const&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A0b const& l,
                                             A1 const& a1, A2 const& a2) const
    {
      return nt2::caurnd(nt2::of_size(a1, a2), m, l); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                              , (A0)(A0b)(A1)(A2)(A3)
                              , (unspecified_<A0> )
                              (unspecified_<A0b> )
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                              (scalar_<integer_<A3> >)
                              )
  {
    typedef nt2::of_size_<-1l, -1l, -1l, 1l>                                          T1; 
    typedef typename meta::call<tag::caurnd_(T1,A0 const&,A0b const&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A0b const& l,
                                             A1 const& a1, A2 const& a2, 
                                             A3 const& a3) const
    {
      return nt2::caurnd(nt2::of_size(a1, a2, a3), m, l); 
    }
  };
  
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
                              , (A0)(A0b)(A1)(A2)(A3)(A4)
                              , (unspecified_<A0> )
                              (unspecified_<A0b> )
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                              (scalar_<integer_<A3> >)
                              (scalar_<integer_<A4> >)
                              )
  {
    typedef nt2::of_size_<-1l, -1l, -1l, -1l>                                         T1; 
    typedef typename meta::call<tag::caurnd_(T1,A0 const&,A0b const&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A0b const& l,
                                             A1 const& a1, A2 const& a2, 
                                             A3 const& a3, A4 const& a4) const
    {
      return nt2::caurnd(nt2::of_size(a1, a2, a3, a4), m, l); 
    }
  };
  
 

} }

#endif
