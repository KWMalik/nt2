/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_STATISTICS_FUNCTIONS_SCALAR_CAURND_HPP_INCLUDED
#define NT2_TOOLBOX_STATISTICS_FUNCTIONS_SCALAR_CAURND_HPP_INCLUDED

// #include <nt2/core/functions/caurnd.hpp>
// #include <nt2/core/functions/rand.hpp>
// #include <nt2/core/container/dsl.hpp>
// #include <nt2/core/utility/box.hpp>
// #include <nt2/core/functions/of_size.hpp>
// #include <nt2/core/functions/details/generative_preprocessor.hpp>

// namespace nt2 { namespace ext
// {
//   //============================================================================
//   // Generates all integral set + types overload
//   //============================================================================
//   BOOST_PP_REPEAT_FROM_TO ( 2
//                           , BOOST_PP_INC(NT2_MAX_DIMENSIONS)
//                           , NT2_PP_GENERATIVE_MAKE_FROM_SIZE
//                           , (nt2::tag::caurnd_,nt2::tag::Nan)
//                           )

//   NT2_PP_GENERATIVE_MAKE_FROM_SINGLE( (nt2::tag::caurnd_,nt2::tag::Nan) )

//   //============================================================================
//   // Generates nans from fusion sequence (support of_size calls)
//   //============================================================================
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
//                             , (Seq)
//                             , (fusion_sequence_<Seq>)
//                             )
//   {
//     typedef typename meta::strip<Seq>::type seq_t;
//     typedef typename  boost::proto::
//                       result_of::make_expr< nt2::tag::caurnd_
//                                           , container::domain
//                                           , box<seq_t>
//                                           , box<meta::constant_<nt2::tag::Nan> >
//                                           , meta::as_<double>
//                                           >::type             result_type;

//     BOOST_FORCEINLINE result_type operator()(Seq const& seq) const
//     {
// q      return  boost::proto::
//               make_expr < nt2::tag::caurnd_
//                         , container::domain
//                         > ( boxify(seq)
//                           , boxify(meta::constant_<nt2::tag::Nan>())
//                           , meta::as_<double>()
//                           );
//     }
//   };

//   //============================================================================
//   // Generates nans from fusion sequence + types (support of_size calls)
//   //============================================================================
//   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caurnd_, tag::cpu_
//                             , (Seq)(T)
//                             , (fusion_sequence_<Seq>)
//                               (target_< scalar_< unspecified_<T> > >)
//                             )
//   {
//     typedef typename meta::strip<Seq>::type seq_t;
//     typedef typename  boost::proto::
//                       result_of::make_expr< nt2::tag::caurnd_
//                                           , container::domain
//                                           , box<seq_t>
//                                           , box< meta::constant_<nt2::tag::Nan> >
//                                           , T
//                                           >::type             result_type;

//     BOOST_FORCEINLINE result_type operator()(Seq const& seq, T const& tgt) const
//     {
//       return  boost::proto::
//               make_expr<  nt2::tag::caurnd_
//                         , container::domain
//                         > ( boxify(seq)
//                           , boxify(meta::constant_<nt2::tag::Nan>())
//                           , tgt
//                           );
//     }
//   };
// } }

#endif
