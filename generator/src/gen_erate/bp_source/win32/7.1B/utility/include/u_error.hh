/*========================================================================
 *
 * File:      $RCSfile: u_error.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_ERROR_HH
#define U_ERROR_HH


#include <u_log.hh>
#include "vstdio.h"
#include "u_print.hh"

#ifdef WIN32
#include <windows.h>

#define UI_ERROR_OUTPUT(_MSG_) MessageBox ( 0, _MSG_, 0, MB_OK );
#define UI_INFO_OUTPUT(_MSG_,_CAPTION_) MessageBox ( 0, _MSG_, _CAPTION_, MB_OK );
#else
#define UI_ERROR_OUTPUT(_MSG_) fprintf( stderr,  _MSG_ );
#define UI_INFO_OUTPUT(_MSG_,_CAPTION_) fprintf( stdout,  _MSG_ );
#endif



#define LOG_ERROR(sprintf_parameters)		\
  {                                         \
    U_print::vcsprintf sprintf_parameters;	\
    L_log::log_error (L_log_string);        \
  }

#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
