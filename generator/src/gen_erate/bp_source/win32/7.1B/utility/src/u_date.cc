/*========================================================================
 *
 * File:      $RCSfile: u_date.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:59 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <vdate.h>
#include <vtimestamp.h>
#include <u_trace.hh>
#include <u_date.hh>





t_ulong
RM_date::get_current_time_in_milliseconds ()

{
    LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin RM_date::get_current_time_in_milliseconds ()."));


    vtimestamp current_time = vtimestampGetNow ();

    t_ulong return_value = 0;


    LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End RM_date::get_current_time_in_milliseconds (return_value=%u).",
	return_value));
    return return_value;
}





Description
RM_date::get_current_time_as_string ()

{
    LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin RM_date::get_current_time_as_string ()."));


    Description return_string;

    vdate* date_ptr = vdateCreate ();

    vdateSetCurrent (date_ptr);

    vscribe* scribe_ptr =
      vdateScribeFormatted (date_ptr, vdateGetNormalFormat ());

    vchar date_string [256];
    date_string [0] = vcharFromASCII('\0');
    vcharExport (scribe_ptr, date_string);
    return_string = date_string;

    vdateDestroy (date_ptr);


    LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End RM_date::get_current_time_as_string (return_string='%s').",
	return_string.char_ptr ()));
    return return_string;
}
