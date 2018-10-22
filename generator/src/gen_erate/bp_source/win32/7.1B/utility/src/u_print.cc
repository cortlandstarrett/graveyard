/*========================================================================
 *
 * File:      $RCSfile: u_print.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:00 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "u_print.hh"
#include <vstr.h>

vchar *U_print::vcsprintf(vchar *s, const char *format, ...)
{
  va_list ap;
  va_start(ap, format);

  vstr *vformat = vstrCloneScribed( vcharScribeASCII( format ) );
  vscribe *vs = vcharScribeFormatVarargs (vformat, ap);
  vcharCopyScribed(vs, s);
  vstrDestroy(vformat);

  va_end(ap);
  return s;
}

vchar *U_print::vcvsprintf(vchar *s, const char *format, va_list *ap)
{
  vstr *vformat = vstrCloneScribed( vcharScribeASCII( format ) );
  vscribe *vs = vcharScribeFormatVarargs (vformat, *ap);
  vcharCopyScribed(vs, s);
  vstrDestroy(vformat);

  return s;
}
