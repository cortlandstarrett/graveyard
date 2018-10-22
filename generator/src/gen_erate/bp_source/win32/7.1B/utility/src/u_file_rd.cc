/*========================================================================
 *
 * File:      $RCSfile: u_file_rd.cc,v $
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
#include <vprint.h>

#include <r_galp.hh>
#include <r_cursor.hh>

#include <u_env.hh>
#include <u_error.hh>
#include <u_file.hh>
#include <u_trace.hh>

static void RM_file_print_file_notify( vprint* printer_ptr, int flag )
{
	if ( !flag )
	{
		return;
	}

	LOG_TRACE( L_RENDER, L_FUNCTION_BEGIN,
	( L_log_string, "Entered RM_file::print_file()"));

	t_boolean change_cursor = RL_Cursor::is_cursor_busy ();
	if (change_cursor)
      {
		RL_Cursor::SetUnBusyMCursor ();
      }

	RM_file *file_ptr = (RM_file *) vprintGetData(printer_ptr);

	file_ptr->RM_close_media ("");

	RL_GalaxyPrint::print_text( printer_ptr, 
		file_ptr->get_file_name_string().char_ptr () );
	
	RM_file::RM_static_remove_media(
		(char *)file_ptr->get_file_name_string().char_ptr () );

	if (change_cursor)
      {
		RL_Cursor::SetBusyMCursor ();
      }

	LOG_TRACE( L_RENDER, L_FUNCTION_END,
	( L_log_string, "Exitted RM_file::print_file()"));

}

void
RM_file::RM_flush_media_to_printer (void *printer_ptr )
{
	extern char default_print_file[];

	LOG_TRACE (L_RENDER, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  RM_file::RM_flush_media_to_printer\n\t()."));


	if (file_ptr != 0)
	{
      vchar titleBuffer[128];
      vchar *p = &titleBuffer[0];
      vcharCopyFromLiteral( "Notebook Model Descriptions", p );
      vprintSetDocumentTitle((vprint*) printer_ptr, p );

      vprintSetData((vprint*)printer_ptr, this);

      vprintSetJobNotify((vprint*) printer_ptr,
                         RM_file_print_file_notify );

      t_boolean change_cursor = RL_Cursor::is_cursor_busy ();
      if (change_cursor)
        {
          RL_Cursor::SetUnBusyMCursor ();
        }

      vexWITH_HANDLING
        {
          vprintConfirmJob((vprint*) printer_ptr);
        }
      vexON_EXCEPTION
        {
          vprintJobCanceledException *jc_exc = vprintGetJobCanceledException();
          vprintNoDefaultPrinterException *ndp_exc =
            vprintGetNoDefaultPrinterException();
          if (jc_exc)
            {
              // job cancelled
            }
          else if (ndp_exc)
            {
              // no default printer exception
              const char *err_msg = "No default printer is defined.\n\nPrinting cancelled.";
              LOG_ERROR ((L_log_string,
                          "RM_file::RM_flush_media_to_printer(): %S",
                          vcharScribeLiteral(err_msg) ));
            }
          else
            {
              // Invalid or missing file name
              const char *err_msg = "Invalid or missing file name.\n\nPrinting cancelled.";
              LOG_ERROR ((L_log_string,
                          "RM_file::RM_flush_media_to_printer(): %S",
                          vcharScribeLiteral(err_msg) ));
            }
        }
      vexEND_HANDLING;

      if (change_cursor)
        {
          RL_Cursor::SetBusyMCursor ();
        }
	}


	if (U_env_var::put_env_var (default_print_file))
	{
		LOG_ERROR ((L_log_string, "RM_file::RM_flush_media_to_printer(): putenv default_print_file = %S failed.",
                vcharScribeASCII(default_print_file) ));
	}
	
	LOG_TRACE (L_RENDER, L_FUNCTION_END, (L_log_string,
	"End RM_file::RM_flush_media_to_printer ()."));
}
