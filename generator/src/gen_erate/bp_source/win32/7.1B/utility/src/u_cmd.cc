/*========================================================================
 *
 * File:      $RCSfile: u_cmd.cc,v $
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
#include <stdlib.h>
#include <errno.h>

#include <u_cmd.hh>
#include <u_string.hh>
#include <u_trace.hh>
#include <u_error.hh>





int
U_shell_cmd::exec_shell_cmd (const String& p_shell_cmd_str)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin U_shell_cmd::exec_shell_cmd (p_shell_cmd_str=\"%S\").",
	vcharScribeASCII(p_shell_cmd_str.char_ptr ()) ));


    int exit_status = system ((char*) (p_shell_cmd_str.char_ptr ()));


    if ((exit_status < 0) && (errno > 0))
    {
	//  Format an error message to the user to alert the user of the
	//    failure.
	//
	extern char* process_name_char_ptr;
	String error_str ("\n\n");
	error_str += process_name_char_ptr;
	error_str += ":  ERROR:  Failed to execute Shell Command:\n\n\t";
	error_str += p_shell_cmd_str;
	error_str += "\n\n";


	switch (errno)
	{
	case EPERM:
	    error_str +=
		"\tbecause you are not super-user.\n";
	    break;


	case ENOENT:
	    error_str +=
		"\tbecause no such file or directory exists.\n";
	    break;


	case ESRCH:
	    error_str +=
		"\tbecause no such process exists.\n";
	    break;


	case EINTR:
	    error_str +=
		"\tbecause system () was interrupted by a signal.\n";
	    break;


	case EIO:
	    error_str +=
		"\tbecause of I/O error.\n";
	    break;


	case ENXIO:
	    error_str +=
		"\tbecause no such device or address exists.\n";
	    break;


	case EAGAIN:
	    error_str +=
		"\tbecause the system-imposed limit on the total number of\n";
	    error_str +=
		"\tprocesses under execution would be exceeded OR the\n";
	    error_str +=
		"\ttotal number of processes under execution by a single\n";
	    error_str +=
		"\tuser would be exceeded.\n";
	    break;


	case ENOMEM:
	    error_str +=
		"\tbecause there is insufficient swap space and/or physical\n";
	    error_str +=
		"\tmemory available in which to create the new process.\n";
	    break;


	case EACCES:
	    error_str +=
		"\tbecause permission denied.\n";
	    break;


	default:
	    {
		char buffer [16];
		sprintf (buffer, "%d", errno);
		error_str += "\twith errno = ";
		error_str += buffer;
		error_str += ".\n";
	    }
	    break;
	}


	error_str +=
	    "\n\tPlease correct the condition before continuing.\n\n\n";


	//  Log the error in the BridgePoint log file.
	//
	LOG_ERROR ((L_log_string,
	    "U_shell_cmd::exec_shell_cmd (errno=%d):\n\n%S",
	    errno,
      vcharScribeASCII(error_str.char_ptr ()) ));


	//  Print an error message directly to the user to alert the user to
	//    the problem.
	//
	UI_ERROR_OUTPUT(error_str.char_ptr ());
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End U_shell_cmd::exec_shell_cmd (exit_status=%d).",
	exit_status));
    return exit_status;
}
