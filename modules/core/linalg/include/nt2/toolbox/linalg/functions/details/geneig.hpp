/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_GENEIG_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_GENEIG_HPP_INCLUDED

#include <nt2/include/functions/abs.hpp>
#include <nt2/toolbox/linalg/details/utility/workspace.hpp>
#include <nt2/toolbox/linalg/details/lapack/gges.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/issquare.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <nt2/table.hpp>

namespace nt2 { namespace details
{
  template<class T,
           class CPLX = typename nt2::details::is_complex<typename meta::strip<T>::type::value_type >::type>
  struct geneig_result
  {
    typedef typename meta::strip<T>::type                   source_t;
    typedef typename source_t::value_type                     type_t;
    typedef typename meta::as_integer<type_t, signed>::type  itype_t;
    typedef typename source_t::index_type                    index_t;
    typedef typename meta::as_real<type_t>::type              base_t;
    typedef T                                                 data_t;
    typedef nt2::table<type_t,nt2::matlab_index_>              tab_t;
    typedef nt2::table<base_t,nt2::matlab_index_>             btab_t;
    typedef nt2::table<itype_t,nt2::matlab_index_>            itab_t; 
    typedef nt2::details::workspace<type_t>              workspace_t;
    typedef nt2::table<nt2_la_int,nt2::matlab_index_>         ibuf_t;
    typedef nt2::table<type_t,index_t>                   result_type;
    
    template<class Input1, class Input2>
    geneig_result ( Input1& xpr1,Input2& xpr2, 
                    const char & jobvsl/* = 'V'*/,
                    const char & jobvsr/* = 'V'*/,
                    const char & sort  /* = 'N'*/)
      : jobvsl_(jobvsl)
      , jobvsr_(jobvsr)
      , sort_ (sort)
      , a_(xpr1)
      , aa_(xpr1)
      , lda_(a_.leading_size())
      , b_(xpr2)
      , bb_(xpr2)
      , ldb_(b_.leading_size())
      , sdim_(0) 
      , n_(height(a_))
      , alpha_(of_size(1, n_))
      , beta_(of_size(1, n_))
      , vsl_(jobvsl_ == 'V'?of_size(n_, n_):of_size(1, 1))
      , ldvsl_(vsl_.leading_size())
      , vsr_(jobvsr_ == 'V'?of_size(n_, n_):of_size(1, 1))
      , ldvsr_(vsr_.leading_size())
      , info_(0) 
    {
      BOOST_ASSERT_MSG(nt2::issquare(a_), "inputs  must be squares matrix"); 
      BOOST_ASSERT_MSG(nt2::issquare(b_), "inputs  must be squares matrix");
      BOOST_ASSERT_MSG(n_ = height(b_), "inputs  must be of same size");
      nt2::details::gges(&jobvsl_, &jobvsr_, &sort_, &nt2::details::selectall, &n_, 
                         aa_.raw(), &lda_, bb_.raw(), &ldb_,
                         &sdim_, alpha_.raw(), beta_.raw(),
                         vsl_.raw(), &ldvsl_, vsr_.raw(), &ldvsr_, &info_, wrk_); 
    }
    
    geneig_result& operator=(geneig_result const& src)
    {
      jobvsl_ = src.jobvsl_;  
      jobvsr_ = src.jobvsr_;  
      sort_ = src.sort_;  
      a_ = src.a_;  
      aa_ = src.aa_;  
      lda_ = src.lda_;  
      b_ = src.b_;  
      bb_ = src.bb_;  
      ldb_ = src.ldb_;  
      sdim_ = src.sdim_;  
      n_ = src.n_;  
      alpha_ = src.alpha;  
      beta_ = src.beta_;  
      vsl_ = src.vsl_;  
      ldvsl_ = src.ldvsl_;  
      vsr_ = src.vsr_;  
      ldvsr_ = src.ldvsr_;  
      info_ = src.info_;  
      wrk_ = src.wrk_;  
      return *this;
    }

    geneig_result(geneig_result const& src)
      :  jobvsl_ ( src.jobvsl_),  
         jobvsr_ ( src.jobvsr_),  
         sort_ ( src.sort_),  
         a_ ( src.a_),  
         aa_ ( src.aa_),  
         lda_ ( src.lda_),  
         b_ ( src.b_),  
         bb_ ( src.bb_),  
         ldb_ ( src.ldb_),  
         sdim_ ( src.sdim_),  
         n_ ( src.n_),  
         alpha_ ( src.alpha),  
         beta_ ( src.beta_),  
         vsl_ ( src.vsl_),  
         ldvsl_ ( src.ldvsl_),  
         vsr_ ( src.vsr_),  
         ldvsr_ ( src.ldvsr_),  
         info_ ( src.info_),  
         wrk_ ( src.wrk_)  
    {}
    
    //==========================================================================
    // Return raw values
    //==========================================================================
    result_type values() const { return aa_; }
    nt2_la_int status()  const {return info_; }
    //==========================================================================
    // return left eigen vectors
    //==========================================================================
    tab_t vl () const
    {
      BOOST_ASSERT_MSG(jobvsl_ == 'V', "use jobvsl =  'V' to get eigenvectors"); 
      return vsl_;
    }
    //==========================================================================
    // return right eigen vectors
    //==========================================================================
    tab_t vr () const
    {
      BOOST_ASSERT_MSG(jobvsl_ == 'V', "use jobvsr =  'V' to get eigenvectors"); 
      return vsr_;
    }
    
    //==========================================================================
    // return left generalized eigenvalues
    //==========================================================================
    tab_t alpha () const
    {
      BOOST_ASSERT_MSG(jobvsl_ == 'V', "use jobvsl =  'V' to get eigenvectors"); 
      return alpha_;
    }
    
    //==========================================================================
    // return right generalized eigenvalues
    //==========================================================================
    tab_t beta () const
    {
      BOOST_ASSERT_MSG(jobvsl_ == 'V', "use jobvsr =  'V' to get eigenvectors"); 
      return beta_;
    }
    
    //==========================================================================
    // return  eigenvalues
    //==========================================================================
    tab_t eigen () const
    {
      BOOST_ASSERT_MSG(jobvsl_ == 'V', "use jobvsr =  'V' to get eigenvectors"); 
      return alpha_/beta_;
    }
    
     //==========================================================================
    // return  eigenvalues
    //==========================================================================
    tab_t w () const
    {
      BOOST_ASSERT_MSG(jobvsl_ == 'V', "use jobvsr =  'V' to get eigenvectors"); 
      return from_diag(alpha_/beta_);
    }
    
  private:
    char          jobvsl_;
    char          jobvsr_;
    char            sort_; 
    data_t             a_;
    tab_t             aa_;
    nt2_la_int       lda_;
    data_t             b_;
    tab_t             bb_;
    nt2_la_int       ldb_;
    nt2_la_int      sdim_; 
    nt2_la_int         n_;
    tab_t   alpha_, beta_; 
    tab_t            vsl_;
    nt2_la_int     ldvsl_;
    tab_t            vsr_;
    nt2_la_int     ldvsr_;
    nt2_la_int      info_; 
    workspace_t      wrk_;
  };
  
  template<class T> 
  struct geneig_result < T, boost::mpl::false_ >  
  {
    typedef typename meta::strip<T>::type                   source_t;
    typedef typename source_t::value_type                     type_t;
    typedef typename nt2::meta::as_complex<type_t>::type     ctype_t; 
    typedef typename meta::as_integer<type_t, signed>::type  itype_t;
    typedef typename source_t::index_type                    index_t;
    typedef typename meta::as_real<type_t>::type              base_t;
    typedef T                                                 data_t;
    typedef nt2::table<type_t,nt2::matlab_index_>              tab_t;
    typedef nt2::table<base_t,nt2::matlab_index_>             btab_t;
    typedef nt2::table<itype_t,nt2::matlab_index_>            itab_t;
    typedef nt2::table<ctype_t,nt2::matlab_index_>            ctab_t;
    typedef nt2::details::workspace<type_t>              workspace_t;
    typedef nt2::table<nt2_la_int,nt2::matlab_index_>         ibuf_t;
    typedef nt2::table<type_t,index_t>                   result_type;
    typedef nt2::table<ctype_t,index_t>                 cresult_type;  
    
    template<class Input1, class Input2>
    geneig_result ( Input1& xpr1,Input2 xpr2, 
                    const char & jobvsl  /*= 'V'*/,
                    const char & jobvsr  /*= 'V'*/,
                    const char & sort  /*= 'S'*/)
      : jobvsl_(jobvsl)
      , jobvsr_(jobvsr)
      , sort_ (sort)
      , a_(xpr1)
      , aa_(xpr1)
      , lda_(a_.leading_size())
      , b_(xpr2)
      , bb_(xpr2)
      , ldb_(b_.leading_size())
      , sdim_(0)
      , n_(height(a_))
      , alphar_(of_size(1, n_))
      , alphai_(of_size(1, n_))
      , beta_(of_size(1, n_))
      , vsl_(jobvsl_ == 'V'?of_size(n_, n_):of_size(1, 1))
      , ldvsl_(vsl_.leading_size())
      , vsr_(jobvsr_ == 'V'?of_size(n_, n_):of_size(1, 1))
      , ldvsr_(vsr_.leading_size())
      , info_(0)
    {
      BOOST_ASSERT_MSG(nt2::issquare(a_), "inputs  must be squares matrix");
      BOOST_ASSERT_MSG(nt2::issquare(b_), "inputs  must be squares matrix");
      BOOST_ASSERT_MSG(n_ = height(b_), "inputs  must be of same size");
      nt2::details::gges(&jobvsl_, &jobvsr_, &sort_, &nt2::details::selectall2, &n_,
                         aa_.raw(), &lda_,  bb_.raw(), &ldb_,
                         &sdim_, alphar_.raw(), alphai_.raw(), beta_.raw(),
                         vsl_.raw(), &ldvsl_, vsr_.raw(), &ldvsr_, &info_, wrk_);
    }
    
    geneig_result& operator=(geneig_result const& src)
    {
      jobvsl_ = src.jobvsl_;
      jobvsr_ = src.jobvsr_;
      sort_ = src.sort_;
      a_ = src.a_;
      aa_ = src.aa_;
      lda_ = src.lda_;
      b_ = src.b_;
      bb_ = src.bb_;
      ldb_ = src.ldb_;
      sdim_ = src.sdim_;
      n_ = src.n_;
      alphar_ = src.alphar_;
      alphai_ = src.alphai_;
      beta_ = src.beta_;
      vsl_ = src.vsl_;
      ldvsl_ = src.ldvsl_;
      vsr_ = src.vsr_;
      ldvsr_ = src.ldvsr_;
      info_ = src.info_;
      wrk_ = src.wrk_;
      return *this;
    }
    
    geneig_result(geneig_result const& src)
      :  jobvsl_ ( src.jobvsl_),  
         jobvsr_ ( src.jobvsr_),  
         sort_ ( src.sort_),  
         a_ ( src.a_),  
         aa_ ( src.aa_),  
         lda_ ( src.lda_),  
         b_ ( src.b_),  
         bb_ ( src.bb_),  
         ldb_ ( src.ldb_),  
         sdim_ ( src.sdim_),  
         n_ ( src.n_),  
         alphar_ ( src.alphar_),  
         alphai_ ( src.alphai_),  
         beta_ ( src.beta_),  
         vsl_ ( src.vsl_),  
         ldvsl_ ( src.ldvsl_),  
         vsr_ ( src.vsr_),  
         ldvsr_ ( src.ldvsr_),  
         info_ ( src.info_),  
         wrk_ ( src.wrk_)  
    {}
    //==========================================================================
    // Return raw values
    //==========================================================================
    result_type values() const { return aa_; }
    
    //==========================================================================
    // return left eigen vectors
    //==========================================================================
    result_type vl () const
    {
      BOOST_ASSERT_MSG(jobvsl_ == 'V', "use jobvsl =  'V' to get eigenvectors");
      return vsl_;
    }
    //==========================================================================
    // return right eigen vectors
    //==========================================================================
    result_type vr () const
    {
      BOOST_ASSERT_MSG(jobvsl_ == 'V', "use jobvsr =  'V' to get eigenvectors");
      return vsr_;
    }
    result_type s () const
    {
      return aa_;
    }
    result_type t () const
    {
      return bb_;
    }

    //==========================================================================
    // return left generalized eigenvalues
    //==========================================================================
    result_type  alphar () const
    {
      return alphar_;
    }
    result_type  alphai () const
    {
      return alphai_;
    }
    cresult_type alpha () const
    {
      ctab_t al(alphar_, alphai_);
      return al; 
    }
    
    //==========================================================================
    // return right generalized eigenvalues
    //==========================================================================
    result_type beta () const
    {
      return beta_;
    }

    //==========================================================================
    // return  eigenvalues
    //==========================================================================
    result_type wr () const
    {
      BOOST_ASSERT_MSG(jobvsl_ == 'V', "use jobvsr =  'V' to get eigenvectors");
      return alphar_/beta_;
    }
    result_type wi () const
    {
      BOOST_ASSERT_MSG(jobvsl_ == 'V', "use jobvsr =  'V' to get eigenvectors");
      return alphai_/beta_;
    }
    cresult_type w () const
    {
      BOOST_ASSERT_MSG(jobvsl_ == 'V', "use jobvsr =  'V' to get eigenvectors");
      return alpha()/beta_;
    }
    
  private:
    char          jobvsl_;
    char          jobvsr_;
    char            sort_;
    data_t             a_;
    tab_t             aa_;
    nt2_la_int       lda_;
    data_t             b_;
    tab_t             bb_;
    nt2_la_int       ldb_;
    nt2_la_int      sdim_;
    nt2_la_int         n_;
    btab_t        alphar_;
    btab_t        alphai_;
    btab_t          beta_;
    tab_t            vsl_;
    nt2_la_int     ldvsl_;
    tab_t            vsr_;
    nt2_la_int     ldvsr_;
    nt2_la_int      info_;
    workspace_t      wrk_;
  };

} }
  
  
#endif
  
