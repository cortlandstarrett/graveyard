/*========================================================================
 *
 * File:      $RCSfile: gs_ui.cc,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:43:05 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>


#ifdef OLD_FILE_NAMES
#include <L_log_trace.hh>
#include <L_log_error.hh>
#else
#include <u_trace.hh>
#include <u_error.hh>
#endif


#include <u_string.hh>
#include <gs_ui.hh>


t_ui_information_level GS_information_level = UI_INFORM__SYS;

GS_string GS_ui::s_name_str = "";
t_uint GS_ui::s_line_num = 0;
const char* GS_ui::s_fileNamePtr = GS_ui::s_name_str.char_ptr();

extern t_boolean s_quit_on_error;
extern t_int s_number_of_errors;

ofstream log_file;
static t_boolean use_stdio = TRUE;



void
GS_ui::set_name_str (const GS_string& p_name_str)
{ 
	s_name_str = p_name_str;
	setFileNamePtr();
}



void
GS_ui::init (const GS_string& p_log_file_name_str,
    t_ui_information_level p_ui_information_level)

{
    LOG_TRACE (L_W_WINDOWS, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_ui::init (p_log_file_name_str=\"%S\", p_ui_information_level=%d).",
	vcharScribeASCII(p_log_file_name_str.char_ptr ()),
  p_ui_information_level));


    GS_information_level = p_ui_information_level;


    if (p_log_file_name_str != "")
    {
	log_file.open (p_log_file_name_str.char_ptr (), ios::app);
	if (! log_file.good ())
	{
	    cerr << "Unable to open file '"
		 << p_log_file_name_str.char_ptr ()
		 << "' for writing - using stderr instead."
		 << endl;
	    LOG_TRACE (L_W_WINDOWS, L_FUNCTION_END, (L_log_string,
		"End #1:  GS_ui::init ():  exit (1) since log file can not be opended"));
	}
	else
	{
	    use_stdio = FALSE;

	    cerr << "Log file is '"
		 << p_log_file_name_str.char_ptr ()
		 << "'."
		 << endl;
	}
    }


    LOG_TRACE (L_W_WINDOWS, L_FUNCTION_END, (L_log_string,
	"End #2:  GS_ui::init ()."));
}




void
GS_ui::inform (t_ui_information_level p_information_level,
    const GS_string& p_information_str)

{
    LOG_TRACE (L_W_WINDOWS, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_ui::inform #1 (p_information_level=%d, p_information_str=\"%S\").",
	p_information_level,
  vcharScribeASCII(p_information_str.char_ptr ()) ));

	GS_ui::inform( p_information_level,
		Description(p_information_str.char_ptr()) );
    LOG_TRACE (L_W_WINDOWS, L_FUNCTION_END, (L_log_string,
	"End #1:  GS_ui::inform ()."));
}

void
GS_ui::inform (t_ui_information_level p_information_level,
    const Description& p_information_str)

{
    LOG_TRACE (L_W_WINDOWS, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_ui::inform #2 (p_information_level=%d, p_information_str=\"%s\").",
	p_information_level,
  p_information_str.char_ptr ()));


    switch (p_information_level)
    {
    case UI_INFORM__ERROR:
	if (use_stdio)
	{
	    cerr << file_name_ptr ()
		 << ": "
		 << s_line_num
		 << ":  ERROR:  "
		 << p_information_str.char_ptr ()
		 << endl;
	}
	else
	{
	    log_file << file_name_ptr ()
		 << ": "
		 << s_line_num
		 << ":  ERROR:  "
		 << p_information_str.char_ptr ()
		 << endl;
	}
	s_number_of_errors++;
	if (s_quit_on_error)
	{
	    exit (1);
	}
	break;

    case UI_INFORM__WARNING:
	if (use_stdio)
	{
	    cout << file_name_ptr ()
		 << ": "
		 << s_line_num
		 << ":  WARNING:  "
		 << p_information_str.char_ptr ()
		 << endl;
	}
	else
	{
	    log_file << file_name_ptr ()
		 << ": "
		 << s_line_num
		 << ":  WARNING:  "
		 << p_information_str.char_ptr ()
		 << endl;
	}
	break;

    case UI_INFORM__SYS:
	if (use_stdio)
	{
	    cout << file_name_ptr ()
		 << ": "
		 << s_line_num
		 << ":  INFO:  "
		 << p_information_str.char_ptr ()
		 << endl;
	}
	else
	{
	    log_file << file_name_ptr ()
		 << ": "
		 << s_line_num
		 << ":  INFO:  "
		 << p_information_str.char_ptr ()
		 << endl;
	}
	break;

    case UI_INFORM__ACTN:
	if (GS_information_level >= UI_INFORM__ACTN)
	{
	    if (use_stdio)
	    {
		cout << file_name_ptr ()
		     << ": "
		     << s_line_num
		     << ":  ACTION INFO:  "
		     << p_information_str.char_ptr ()
		     << endl;
	    }
	    else
	    {
		log_file << file_name_ptr ()
		     << ": "
		     << s_line_num
		     << ":  ACTION INFO:  "
		     << p_information_str.char_ptr ()
		     << endl;
	    }
	}
	break;

    case UI_INFORM__STMT:
	if (GS_information_level >= UI_INFORM__STMT)
	{
	    if (use_stdio)
	    {
		cout << file_name_ptr ()
		     << ": "
		     << s_line_num
		     << ":  STMT INFO:  "
		     << p_information_str.char_ptr ()
		     << endl;
	    }
	    else
	    {
		log_file << file_name_ptr ()
		     << ": "
		     << s_line_num
		     << ":  STMT INFO:  "
		     << p_information_str.char_ptr ()
		     << endl;
	    }
	}
	break;

    case UI_INFORM__COMP:
	if (GS_information_level >= UI_INFORM__COMP)
	{
	    if (use_stdio)
	    {
		cout << file_name_ptr ()
		     << ": "
		     << s_line_num
		     << ":  STMT COMP INFO:  "
		     << p_information_str.char_ptr ()
		     << endl;
	    }
	    else
	    {
		log_file << file_name_ptr ()
		     << ": "
		     << s_line_num
		     << ":  STMT COMP INFO:  "
		     << p_information_str.char_ptr ()
		     << endl;
	    }
	}
	break;


    default:
	if (use_stdio)
	{
	    cout << file_name_ptr ()
		 << ": "
		 << s_line_num
		 << ":  MISC INFO:  "
		 << p_information_str.char_ptr ()
		 << endl;
	}
	else
	{
	    log_file << file_name_ptr ()
		 << ": "
		 << s_line_num
		 << ":  MISC INFO:  "
		 << p_information_str.char_ptr ()
		 << endl;
	}
	break;
    }


    LOG_TRACE (L_W_WINDOWS, L_FUNCTION_END, (L_log_string,
	"End #1:  GS_ui::inform ()."));
}




t_ui_prompt_response
GS_ui::prompt (int p_legal_responses,
    const Description& p_question_str)

{
    LOG_TRACE (L_W_WINDOWS, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_ui::prompt (p_legal_responses=0x%08x, p_question_str=\"%s\").",
	p_legal_responses, p_question_str.char_ptr ()));


    LOG_ERROR ((L_log_string,
	"End #1:  GS_ui::prompt (UI_RESPONSE__NO) - Do not support p_legal_responses combination 0x%08x.",
	p_legal_responses));
    return UI_RESPONSE__NO;
}
