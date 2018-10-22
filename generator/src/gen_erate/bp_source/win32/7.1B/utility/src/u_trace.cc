/*========================================================================
 *
 * File:      $RCSfile: u_trace.cc,v $
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
#include "vstdio.h"

#include <u_trace.hh>
#include <u_date.hh>



unsigned long	L_log_trace::flag [L_LAST_TRACE_FLAG];

t_boolean	L_log_trace::system_test_flag = FALSE;
void*		L_log_trace::system_test_output = 0;





void
L_log_trace::set_flag
    (enum L_trace_flag_names trace_flag_name, unsigned long new_flag)

{
  int i = trace_flag_name;
  if (i < L_LAST_TRACE_FLAG)
    {
      flag [trace_flag_name] = new_flag;
    }
}

 



void
L_log_trace::clear_all_flags ()

{
  for (int i = L_FIRST_TRACE_FLAG;
       i < L_LAST_TRACE_FLAG;
       i++)
    {
      set_flag ((enum L_trace_flag_names)i, 0x0);
    }
}





void
L_log_trace::set_all_flags_full_blast ()

{
  for (int i = L_FIRST_TRACE_FLAG;
       i < L_LAST_TRACE_FLAG;
       i++)
    {
      set_flag ((enum L_trace_flag_names)i, 0xffffffff);
    }
}





unsigned long
L_log_trace::get_flag (enum L_trace_flag_names trace_flag_name)

{
    return (flag [trace_flag_name]);
}




//
// FUNCTION: trace_active
//
// PURPOSE:  Determine if any trace flags are on.
//
// RETURNS:  0 - No trace flags are on
//	     1 - There exists a trace flag that is on
//

int
L_log_trace::trace_active()

{
  for (int i = L_FIRST_TRACE_FLAG;
       i < L_LAST_TRACE_FLAG;
       i++)
    {
    	if (flag[(enum L_trace_flag_names)i] != 0)
        {
          return 1;
        }
    }
    
  return 0;
}





//
// FUNCTION: start_system_test, stop_system_test
//
// PURPOSE:  
//

void
L_log_trace::start_system_test (String p_file, String p_title)

{
    system_test_output = 0;
    FILE * tmp_file_ptr = fopen ((char *)p_file.char_ptr (), "w");

    if (tmp_file_ptr != 0)
    {
		system_test_output = (void *)tmp_file_ptr;

		Description title_message = "\n\nModel Builder "
#include <platform.str>
		"  Version "
#include <version.str>
    " Test Description:\n\n";
		title_message += p_title.char_ptr();
		title_message += "\n\nDate: ";
		title_message += RM_date::get_current_time_as_string ();
		title_message += "\n\ni******************************************************************************\n\n",

		vcharDump (title_message.char_ptr (), tmp_file_ptr);
    }
}





void
L_log_trace::stop_system_test ()

{
    fclose ((FILE*) system_test_output);
    system_test_output = 0;
}
