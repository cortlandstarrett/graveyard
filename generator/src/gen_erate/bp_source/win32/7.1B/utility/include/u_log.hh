/*========================================================================
 *
 * File:      $RCSfile: u_log.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:33 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_LOG_HH
#define U_LOG_HH


#include <vstdio.h>

#include "vchar.h"

extern vchar L_log_string [];




class L_log

{
public:
    static void log_error (const char*);
    static void log_report (const char*);
    static void log_trace (const char*);

    static void log_error (const vchar*);
    static void log_report (const vchar*);
    static void log_common (const char *prefix, const vchar *message, bool isError = false);
    static void log_trace (const vchar*, bool isError = false);

    static void log_email ();
    static void close_log_files ();

private:
    static FILE*	log_file_ptr;
    static FILE*	trace_file_ptr;

    static char		user_machine_processid_string [256];
};




#endif
