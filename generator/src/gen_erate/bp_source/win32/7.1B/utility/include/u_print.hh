/*========================================================================
 *
 * File:      $RCSfile: u_print.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef		U_PRINT_HH
#define		U_PRINT_HH

#include "vstdarg.h"
#include "vchar.h"

class U_print
{
public:

  static vchar *vcsprintf(vchar *s, const char *format, ...);
  static vchar *vcvsprintf(vchar *s, const char *format, va_list *ap);
  static vscribe *vprintfScribe(const char *fornat, va_list *ap);
  
};


#endif

