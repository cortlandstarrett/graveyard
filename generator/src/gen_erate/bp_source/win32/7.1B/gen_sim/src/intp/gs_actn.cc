/*========================================================================
 *
 * File:      $RCSfile: gs_actn.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:29 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <ctype.h>
#include <gs_actn.hh>

#ifdef OLD_FILE_NAMES
#include <L_log_trace.hh>
#include <L_log_error.hh>
#else
#include <u_trace.hh>
#include <u_error.hh>
#endif





GS_string
GS_action::uncomment_action ()

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_action::uncomment_action ()."));


    GS_string commented_action_str (m_action_str);
    m_action_str = "";


    //  Remove comments from the action statement.
    //
    while (commented_action_str.cursor () < commented_action_str.length ())
    {
	if (commented_action_str [commented_action_str.cursor ()] == '\"')
	{
	    //  Have come across a begin " character - need to find the
	    //    end " character.
	    //
	    t_boolean end_quote_found = FALSE;
	    while ((! end_quote_found) && (commented_action_str.cursor ()
		< commented_action_str.length ()))
	    {
		m_action_str
		    += commented_action_str [commented_action_str.cursor ()];
		commented_action_str++;
		if (commented_action_str [commented_action_str.cursor ()]
		    == '\"')
		{
		    if (commented_action_str
			[commented_action_str.cursor () + 1] == '\"')
		    {
			//  Have come across a repeated " character - increment
			//    the cursor one additional time so it is ignored.
			//
			m_action_str += commented_action_str
			    [commented_action_str.cursor ()];
			commented_action_str++;
		    }
		    else
		    {
			end_quote_found = TRUE;
		    }
		}
	    }
	    m_action_str
		+= commented_action_str [commented_action_str.cursor ()];
	}
	else if (commented_action_str [commented_action_str.cursor ()] == '\'')
	{
	    //  Have come across a begin ' character - need to find the
	    //    end ' character.
	    //
	    t_boolean end_tick_found = FALSE;
	    while ((! end_tick_found) && (commented_action_str.cursor ()
		< commented_action_str.length ()))
	    {
		m_action_str
		    += commented_action_str [commented_action_str.cursor ()];
		commented_action_str++;
		if (commented_action_str [commented_action_str.cursor ()]
		    == '\'')
		{
		    if (commented_action_str
			[commented_action_str.cursor () + 1] == '\'')
		    {
			//  Have come across a repeated ' character - increment
			//    the cursor one additional time so it is ignored.
			//
			m_action_str += commented_action_str
			    [commented_action_str.cursor ()];
			commented_action_str++;
		    }
		    else
		    {
			end_tick_found = TRUE;
		    }
		}
	    }
	    m_action_str
		+= commented_action_str [commented_action_str.cursor ()];
	}
	else if ((commented_action_str [commented_action_str.cursor ()] == '/')
	    &&
	    (commented_action_str [commented_action_str.cursor () + 1] == '/'))
	{
	    commented_action_str.parse_token ('\n');
	}
	else
	{
	    m_action_str
		+= commented_action_str [commented_action_str.cursor ()];
	}

	if (commented_action_str.cursor () < commented_action_str.length ())
	{
	    commented_action_str++;
	}
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #1:  GS_action::uncomment_action (m_action_str=\"%S\").",
	vcharScribeASCII(m_action_str.char_ptr ()) ));
    return m_action_str;
}





t_boolean
GS_action::get_next_stmt ()

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_action::get_next_stmt ()."));


    for (;
	(m_action_str.cursor () < m_action_str.length ());
	m_action_str++)
    {
	t_uint ii = m_action_str.cursor ();
	switch (m_action_str [ii])
	{
	t_boolean end_tick_found;
	t_boolean end_quote_found;
	case '\"':
	    //  Have come across a begin " character - need to find the end "
	    //    character.
	    //
	    end_quote_found = FALSE;
	    while ((! end_quote_found)
		&& (m_action_str.cursor () < m_action_str.length ()))
	    {
		m_action_str++;
		if (m_action_str.curr_char () == '\"')
		{
		    if (m_action_str [m_action_str.cursor () + 1] == '\"')
		    {
			//  Have come across a repeated " character - increment
			//    the cursor one additional time so it is ignored.
			//
			m_action_str++;
		    }
		    else
		    {
			end_quote_found = TRUE;
		    }
		}
	    }
	    break;

	case '\'':
	    //  Have come across a begin ' character - need to find the end '
	    //    character.
	    //
	    end_tick_found = FALSE;
	    while ((! end_tick_found)
		&& (m_action_str.cursor () < m_action_str.length ()))
	    {
		m_action_str++;
		if (m_action_str.curr_char () == '\'')
		{
		    if (m_action_str [m_action_str.cursor () + 1] == '\'')
		    {
			//  Have come across a repeated ' character - increment
			//    the cursor one additional time so it is ignored.
			//
			m_action_str++;
		    }
		    else
		    {
			end_tick_found = TRUE;
		    }
		}
	    }
	    break;

	case 'A':
	case 'a':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		 (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     && ((m_action_str [ii+1] == 'S') || (m_action_str [ii+1] == 's'))
	     && ((m_action_str [ii+2] == 'S') || (m_action_str [ii+2] == 's'))
	     && ((m_action_str [ii+3] == 'I') || (m_action_str [ii+3] == 'i'))
	     && ((m_action_str [ii+4] == 'G') || (m_action_str [ii+4] == 'g'))
	     && ((m_action_str [ii+5] == 'N') || (m_action_str [ii+5] == 'n'))
	     &&                         (isspace (m_action_str [ii+6])))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #1:  GS_action::get_next_stmt (TRUE - ASSIGN)."));
		return TRUE;
	    }
	    break;

	case 'B':
	case 'b':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		 (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     && ((m_action_str [ii+1] == 'R') || (m_action_str [ii+1] == 'r'))
	     && ((m_action_str [ii+2] == 'I') || (m_action_str [ii+2] == 'i'))
	     && ((m_action_str [ii+3] == 'D') || (m_action_str [ii+3] == 'd'))
	     && ((m_action_str [ii+4] == 'G') || (m_action_str [ii+4] == 'g'))
	     && ((m_action_str [ii+5] == 'E') || (m_action_str [ii+5] == 'e'))
	     &&                         (isspace (m_action_str [ii+6])))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #2:  GS_action::get_next_stmt (TRUE - BRIDGE)."));
		return TRUE;
	    }
	    break;

	case 'C':
	case 'c':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		 (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     && ((m_action_str [ii+1] == 'R') || (m_action_str [ii+1] == 'r'))
	     && ((m_action_str [ii+2] == 'E') || (m_action_str [ii+2] == 'e'))
	     && ((m_action_str [ii+3] == 'A') || (m_action_str [ii+3] == 'a'))
	     && ((m_action_str [ii+4] == 'T') || (m_action_str [ii+4] == 't'))
	     && ((m_action_str [ii+5] == 'E') || (m_action_str [ii+5] == 'e'))
	     &&                         (isspace (m_action_str [ii+6])))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #3:  GS_action::get_next_stmt (TRUE - CREATE)."));
		return TRUE;
	    }
	    break;

	case 'D':
	case 'd':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		 (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     && ((m_action_str [ii+1] == 'E') || (m_action_str [ii+1] == 'e'))
	     && ((m_action_str [ii+2] == 'L') || (m_action_str [ii+2] == 'l'))
	     && ((m_action_str [ii+3] == 'E') || (m_action_str [ii+3] == 'e'))
	     && ((m_action_str [ii+4] == 'T') || (m_action_str [ii+4] == 't'))
	     && ((m_action_str [ii+5] == 'E') || (m_action_str [ii+5] == 'e'))
	     &&                         (isspace (m_action_str [ii+6])))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #4:  GS_action::get_next_stmt (TRUE - DELETE)."));
		return TRUE;
	    }
	    break;

	case 'E':
	case 'e':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		   (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     &&
		((((m_action_str [ii+1] == 'N') || (m_action_str [ii+1] == 'n'))
	     &&   ((m_action_str [ii+2] == 'D') || (m_action_str [ii+2] == 'd'))
	     &&                           (isspace (m_action_str [ii+3])))
	     ||
	         (((m_action_str [ii+1] == 'L') || (m_action_str [ii+1] == 'l'))
	     &&   ((m_action_str [ii+2] == 'S') || (m_action_str [ii+2] == 's'))
	     &&   ((m_action_str [ii+3] == 'E') || (m_action_str [ii+3] == 'e'))
	     &&                           (isspace (m_action_str [ii+4])))))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #5:  GS_action::get_next_stmt (TRUE - END or ELSE)."));
		return TRUE;
	    }
	    break;

	case 'F':
	case 'f':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		 (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     && ((m_action_str [ii+1] == 'O') || (m_action_str [ii+1] == 'o'))
	     && ((m_action_str [ii+2] == 'R') || (m_action_str [ii+2] == 'r'))
	     &&                         (isspace (m_action_str [ii+3])))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #6:  GS_action::get_next_stmt (TRUE - FOR)."));
		return TRUE;
	    }
	    break;

	case 'G':
	case 'g':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		 (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     && ((m_action_str [ii+1] == 'E') || (m_action_str [ii+1] == 'e'))
	     && ((m_action_str [ii+2] == 'N') || (m_action_str [ii+2] == 'n'))
	     && ((m_action_str [ii+3] == 'E') || (m_action_str [ii+3] == 'e'))
	     && ((m_action_str [ii+4] == 'R') || (m_action_str [ii+4] == 'r'))
	     && ((m_action_str [ii+5] == 'A') || (m_action_str [ii+5] == 'a'))
	     && ((m_action_str [ii+6] == 'T') || (m_action_str [ii+6] == 't'))
	     && ((m_action_str [ii+7] == 'E') || (m_action_str [ii+7] == 'e'))
	     &&                         (isspace (m_action_str [ii+8])))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #7:  GS_action::get_next_stmt (TRUE - GENERATE)."));
		return TRUE;
	    }
	    break;

	case 'I':
	case 'i':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		 (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     && ((m_action_str [ii+1] == 'F') || (m_action_str [ii+1] == 'f'))
	     && ((m_action_str [ii+2] == '(')
				     || (isspace (m_action_str [ii+2]))))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #8:  GS_action::get_next_stmt (TRUE - IF)."));
		return TRUE;
	    }
	    break;

	case 'R':
	case 'r':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		 (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     && ((m_action_str [ii+1] == 'E') || (m_action_str [ii+1] == 'e'))
	     && ((m_action_str [ii+2] == 'L') || (m_action_str [ii+2] == 'l'))
	     && ((m_action_str [ii+3] == 'A') || (m_action_str [ii+3] == 'a'))
	     && ((m_action_str [ii+4] == 'T') || (m_action_str [ii+4] == 't'))
	     && ((m_action_str [ii+5] == 'E') || (m_action_str [ii+5] == 'e'))
	     &&                         (isspace (m_action_str [ii+6])))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #9:  GS_action::get_next_stmt (TRUE - RELATE)."));
		return TRUE;
	    }
	    break;

	case 'S':
	case 's':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		 (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     && ((m_action_str [ii+1] == 'E') || (m_action_str [ii+1] == 'e'))
	     && ((m_action_str [ii+2] == 'L') || (m_action_str [ii+2] == 'l'))
	     && ((m_action_str [ii+3] == 'E') || (m_action_str [ii+3] == 'e'))
	     && ((m_action_str [ii+4] == 'C') || (m_action_str [ii+4] == 'c'))
	     && ((m_action_str [ii+5] == 'T') || (m_action_str [ii+5] == 't'))
	     &&                         (isspace (m_action_str [ii+6])))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #10:  GS_action::get_next_stmt (TRUE - SELECT)."));
		return TRUE;
	    }
	    break;

	case 'T':
	case 't':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		 (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     && ((m_action_str [ii+1] == 'R') || (m_action_str [ii+1] == 'r'))
	     && ((m_action_str [ii+2] == 'A') || (m_action_str [ii+2] == 'a'))
	     && ((m_action_str [ii+3] == 'N') || (m_action_str [ii+3] == 'n'))
	     && ((m_action_str [ii+4] == 'S') || (m_action_str [ii+4] == 's'))
	     && ((m_action_str [ii+5] == 'F') || (m_action_str [ii+5] == 'f'))
	     && ((m_action_str [ii+6] == 'O') || (m_action_str [ii+6] == 'o'))
	     && ((m_action_str [ii+7] == 'R') || (m_action_str [ii+7] == 'r'))
	     && ((m_action_str [ii+8] == 'M') || (m_action_str [ii+8] == 'm'))
	     &&                         (isspace (m_action_str [ii+9])))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #11:  GS_action::get_next_stmt (TRUE - TRANSFORM)."));
		return TRUE;
	    }
	    break;

	case 'U':
	case 'u':
	    if (((ii < 1) || (isspace (m_action_str [ii-1])) ||
		 (m_action_str [ii-1] == ';') || (m_action_str [ii-1] == ')'))
	     && ((m_action_str [ii+1] == 'N') || (m_action_str [ii+1] == 'n'))
	     && ((m_action_str [ii+2] == 'R') || (m_action_str [ii+2] == 'r'))
	     && ((m_action_str [ii+3] == 'E') || (m_action_str [ii+3] == 'e'))
	     && ((m_action_str [ii+4] == 'L') || (m_action_str [ii+4] == 'l'))
	     && ((m_action_str [ii+5] == 'A') || (m_action_str [ii+5] == 'a'))
	     && ((m_action_str [ii+6] == 'T') || (m_action_str [ii+6] == 't'))
	     && ((m_action_str [ii+7] == 'E') || (m_action_str [ii+7] == 'e'))
	     &&                         (isspace (m_action_str [ii+8])))
	    {
		LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		    "End #12:  GS_action::get_next_stmt (TRUE - UNRELATE)."));
		return TRUE;
	    }
	    break;

	default:
	    break;
	}
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #13:  GS_action::get_next_stmt (return FALSE)."));
    return FALSE;
}
