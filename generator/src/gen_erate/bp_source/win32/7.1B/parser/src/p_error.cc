/*========================================================================
 *
 * File:      $RCSfile: p_error.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:21 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "p_error.hh"
#include <stdio.h>
#include <stdarg.h>
#include "vstr.h"

void
P_error::stmt_error( long int linenum,
                     long int start,
                     long int end,
                     const char *fmtstr, ... )
{
  {
    if ( !number_errors )
      {
        first_error_linenum = linenum;
        first_error_start = start;
        first_error_end = end;
      }
    if ( !error_this_stmt )
      {
        error_this_stmt = TRUE;
        number_errors++;
        va_list ap;
        va_start(ap, fmtstr);
        vprint_string(&ap, fmtstr);
        va_end(ap);
      }
  }
}

void
P_error::severe_error( const char *msg, ... )
{
  error_this_stmt = FALSE;
  number_errors++;
  va_list ap;
  va_start(ap, msg);
  vprint_string(&ap, msg);
  va_end(ap);
}

void
P_error::print_string( const char *fmtstr, ...)
{
  va_list ap;
  va_start(ap, fmtstr);
  vprint_string(&ap, fmtstr);
  va_end(ap);
}

void
P_error::vprint_string( va_list *ap, const char *fmtstr )
{
  // Note: this function assumes that no message is longer
  //       than PRINTBUFLIMIT.
  vchar *s1 = &error_messages[lng_error_messages];
  switch(status)
    {
    case OK:
      if (lng_error_messages + PRINTBUFLIMIT > PRINTBUFSIZE)
        {
          status = PRINTBUFFULL;
          vchar *s2 =
            vcharCopyScribed( vcharScribeFormatLiteral(
                  "\n*** Maximum number of errors exceeded.\n" ),
                              s1 );
          lng_error_messages += s2 - s1;
          break;
        }
      else
        {
          vstr *vfmtstr = vstrCloneScribed( vcharScribeASCII( fmtstr ) );
          vchar *s2 =
            vcharCopyScribed( vcharScribeFormatVarargs ( vfmtstr, *ap ),
                              s1 );
          lng_error_messages += s2 - s1;
          vstrDestroy(vfmtstr);
        }
      break;
    case PRINTBUFFULL:
      break;
    case PRINTERROR:
      break;
    }
}
