/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_NT2_SDK_ERRORS_DETAILS_WARNING_HPP_INCLUDED
#define NT2_NT2_SDK_ERRORS_DETAILS_WARNING_HPP_INCLUDED

#include <nt2/sdk/sys/string.hpp>
#include <nt2/sdk/sys/timestamp.hpp>
#include <nt2/sdk/errors/details/message.hpp>
#include <nt2/sdk/errors/details/exception.hpp>

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // warning infos type
  //////////////////////////////////////////////////////////////////////////////
  namespace details { NT2_ERROR_INFO(warning_,char const*); }

  //////////////////////////////////////////////////////////////////////////////
  // warning_exception is defined if warning are upgraded to errors
  //////////////////////////////////////////////////////////////////////////////
  struct NT2_EXCEPTION_BASE(warning_exception)
  {
    #if !defined(BOOST_NO_EXCEPTIONS)
    virtual void display(std::ostream& os) const throw()
    {
      os  << " NT2 Warning: "
          << *boost::get_error_info<details::warning_>(*this) << "\n";
    }
    #endif
  };
}

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Build a warning string from warning/assertion info
  //////////////////////////////////////////////////////////////////////////////
  inline sys::string
  warning ( const char* msg, const char* fn, const char* file, int line )
  {
    return message("NT2 WARNING", msg, fn, file, line);
  }

  //////////////////////////////////////////////////////////////////////////////
  // Forward a warning string to the proper default or user-defined logger
  //////////////////////////////////////////////////////////////////////////////
  inline void emit_warning( const char* msg )
  {
    #if !defined(NT2_WARNING_HANDLER)
    fprintf(stderr,"%s\n",msg);
    #else
    nt2::ext::emit_warning(msg);
    #endif
  }

  template<class String>
  inline void emit_warning( String const& msg ) { emit_warning(msg.c_str()); }
} }

#endif
