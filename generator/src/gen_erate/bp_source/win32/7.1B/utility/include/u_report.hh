/*========================================================================
 *
 * File:      $RCSfile: u_report.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:33 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_REPORT_HH
#define U_REPORT_HH


#include <u_log.hh>
#include "u_print.hh"
#include "vstdio.h"



#define LOG_REPORT(sprintf_parameters)      \
  {                                         \
    U_print::vcsprintf sprintf_parameters;  \
    L_log::log_report (L_log_string);       \
  }




#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
