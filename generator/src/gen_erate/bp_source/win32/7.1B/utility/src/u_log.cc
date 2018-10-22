/*========================================================================
 *
 * File:      $RCSfile: u_log.cc,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:58 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <vstdlib.h>
#include <vstdio.h>
#include <vstring.h>
#include <vtime.h>
#include <vsystypes.h>
#include <vchar.h>
#include <vstr.h>
  
#include <u_sysnet.hh>
#include <u_log.hh>
#include <u_trace.hh>
#include <u_cmd.hh>
#include <u_env.hh>

#include <u_userid.hh>
#include "u_print.hh"


#ifndef MAXHOSTNAMELEN
#define MAXHOSTNAMELEN 64
#endif


vchar                L_log_string [32768];

char  L_log::user_machine_processid_string [256] = "";
FILE* L_log::log_file_ptr = 0;
FILE* L_log::trace_file_ptr = 0;

extern char* process_name_char_ptr;


void
L_log::log_common (const char *prefix, const vchar *message, bool isError)
{
  if (user_machine_processid_string [0] == '\0')
    {
      //  The string which identifies the user, machine, and processid has
      //    not been specified yet.
      //

      char hostname [MAXHOSTNAMELEN + 1];
      if (my_gethostname (hostname, MAXHOSTNAMELEN) == 0)
        {
          sprintf (user_machine_processid_string,
                   "user='%s' ::: hostname='%s' ::: pid='%d'",
                   get_userid(), hostname, getpid ());
        }
      else
        {
          //  Problem getting the hostname.
          //
          sprintf (user_machine_processid_string,
                     "user='%s' ::: hostname='%s' ::: pid='%d'",
                     get_userid(), "UNKNOWN HOSTNAME", getpid ());
        }
    }

  FILE*  originalFP = log_file_ptr;  
  if (log_file_ptr == 0)
  {
      //  log_file_ptr is not opened yet - open it.
      //
      if (! process_name_char_ptr)
      {
          process_name_char_ptr = "PT_TOOL???";
      }
      
      char* pt_log_dir_char_ptr = getenv ("PT_LOG_DIR");
      if ((pt_log_dir_char_ptr)
          &&
          (strlen (pt_log_dir_char_ptr) > 0))
      {
          //  A directory has been specified to hold the log file - open
          //    the log file for append.
          //
          char log_file_name [256];
          strcpy (log_file_name, pt_log_dir_char_ptr);
          strcat (log_file_name, PATH_DELIM_STR);
          strcat (log_file_name, process_name_char_ptr);
          strcat (log_file_name, ".log");
          log_file_ptr = fopen (log_file_name, "a");
      }
      else
      {
          // By default output will go to stdout.
          log_file_ptr = stdout;
      }

      originalFP = log_file_ptr;
      
      if (log_file_ptr)
      {
          fprintf (log_file_ptr,
                     "\n++++++++++++++++++++++++++++++++++++++++++++++++++\n++++++++++++++++++++++++++++++++++++++++++++++++++\n++++++++++++++++++++++++++++++++++++++++++++++++++\n");
          time_t current_time = time (0);
          
          fprintf (log_file_ptr,
	                 "Starting %s at %s\n  %s\n\n",
	                 process_name_char_ptr,
	                 ctime (&current_time),
	                 user_machine_processid_string);
          fflush (log_file_ptr);
      }
  }
  
  // If this message is an error, then send it to stderr instead of stdout.
  if ( isError && (log_file_ptr == stdout) ) 
  {
    log_file_ptr = stderr;
  }
  
  if (L_log_trace::trace_active())
  {
    log_trace (message, isError);
  }
  
  
  if (log_file_ptr)
  {
      time_t current_time = time (0);
      void *cmsg = vcharExportAlloc(vcharScribeSystemExport(message));
      fprintf (log_file_ptr,
               "\n\ntime=%s%s\n%s%s\n",
               ctime (&current_time),
               user_machine_processid_string,
               prefix,
               cmsg);
      vcharExportFree(cmsg);
      if (log_file_ptr != stderr)
      {
          fflush (log_file_ptr);
      }
  }
  
  log_file_ptr = originalFP;
}



void
L_log::log_error (const char* error_string)
{
  vscribe *vs = vcharScribeASCII(error_string);
  vstr *ves = vstrCloneScribed( vs );
  log_common ("LOG ERROR:  ", ves, true);
  vstrDestroy(ves);
}

void
L_log::log_error (const vchar* error_string)

{
  log_common ("LOG ERROR:  ", error_string, true);
}



void
L_log::log_report (const char* report_string)
{
  vscribe *rs = vcharScribeASCII(report_string);
  vstr *vrs = vstrCloneScribed( rs );
  log_common ("LOG REPORT:  ", vrs);
  vstrDestroy(vrs);
}
void
L_log::log_report (const vchar* report_string)
{
  log_common ("LOG REPORT:  ", report_string);
}



void
L_log::log_trace (const char* trace_string )

{
  vscribe *ts = vcharScribeASCII(trace_string);
  vstr *vts = vstrCloneScribed( ts );
  log_trace(vts);
  vstrDestroy(vts);
}

void
L_log::log_trace (const vchar* trace_string, bool isError)

{
    if (L_log_trace::get_system_test_flag ())
    {
          trace_file_ptr = (FILE*) L_log_trace::system_test_output;
    }
    else
    {
          if (trace_file_ptr == 0)
          {
              //  trace_file_ptr is not opened yet - open it.
              //
              if (! process_name_char_ptr)
                {
                  process_name_char_ptr = "PT_TOOL???";
                }
              char* pt_log_dir_char_ptr = getenv ("PT_LOG_DIR");
              if ((pt_log_dir_char_ptr)
                    &&
                    (strlen (pt_log_dir_char_ptr) > 0))
              {
                    //  A directory has been specified to hold the log file - open
                    //    the log file for append.
                    //
                    char trace_file_name [256];
                    strcpy (trace_file_name, pt_log_dir_char_ptr);
                    strcat (trace_file_name, PATH_DELIM_STR);
                    strcat (trace_file_name, process_name_char_ptr);
                    strcat (trace_file_name, "_");
                    strcat (trace_file_name, get_userid());
                    strcat (trace_file_name, ".log");
                    trace_file_ptr = fopen (trace_file_name, "a");
              }
              else
              {
                    trace_file_ptr = stdout;
              }
          }
    }
    
	FILE*  originalFP = trace_file_ptr; 
    // If this message is an error, then send it to stderr instead of stdout.
    if ( isError && (trace_file_ptr == stdout) ) 
    {
      trace_file_ptr = stderr;
    }

    if (trace_file_ptr)
    {
      void *ts = vcharExportAlloc(vcharScribeSystemExport(trace_string));
      fprintf (trace_file_ptr, "LOG TRACE (%ld):  %s\n",
               clock (), ts);
      vcharExportFree(ts);
      fflush (trace_file_ptr);
    }
    
    trace_file_ptr = originalFP;
}



void
L_log::close_log_files ()
{
  if (log_file_ptr)
    {
      time_t current_time = time (0);
      fprintf (log_file_ptr,
               "Ending %s at %s\n  %s\n\n",
               process_name_char_ptr,
               ctime (&current_time),
               user_machine_processid_string);
      fprintf (log_file_ptr,
               "\n++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
      fflush (log_file_ptr);
      fclose (log_file_ptr);
    }
  if (trace_file_ptr)
    {
      fclose (trace_file_ptr);
    }
}



//
//  FUNCTION:
//      log_email()
//
//  PURPOSE:
//      This function is called when the user presses the Email
//      button on the support properties window.  This function
//      will call the bin/log_email shell script with a parameter
//      of this user's login name.
//

void
L_log::log_email ()

{
    char  email_command [1024];
          
    String email_shell_script = U_env_var::get_value_str ( "PT_EMAIL_CMD" );
    if (email_shell_script != "")
    {
          //  A directory has been specified to hold the log file - open
          //    the log file for append.
          //
          strcpy (email_command, email_shell_script.char_ptr());
          strcat (email_command, " ");
          strcat (email_command, get_userid());
          U_shell_cmd::exec_shell_cmd (email_command);
    }
}
