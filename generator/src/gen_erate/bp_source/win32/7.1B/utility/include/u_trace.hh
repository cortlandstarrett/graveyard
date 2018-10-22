/*========================================================================
 *
 * File:      $RCSfile: u_trace.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_TRACE_HH
#define U_TRACE_HH


#include <u_log.hh>
#include <u_typdef.hh>
#include <u_string.hh>
#include <u_print.hh>

#include "vchar.h"



enum L_trace_flag_names

{
    L_D_DATA = 0,
    L_FIRST_TRACE_FLAG = L_D_DATA,
    L_M_MODEL,
    L_N_PROJ_NB,

    L_W_WINDOWS,
    L_W_STATES,
    L_W_GUI_DRIVERS,
    L_W_GUI_STUBS,

    L_IE_IMPORT_EXPORT,

    L_CE_STATES,

    L_RENDER,

    L_ERROR_OR_REPORT,

    L_AL,

    L_XLATE,

    L_LAST_TRACE_FLAG	//  Do NOT delete - must stay as the last one -
			//    the 'L_trace_flag' array is declared with
			//    this as it's size.
};




//  Default Trace Flag Masks - notice that these are lined up according to
//    how often they will be  "hit"  or how often they will be printed.
//
#define L_ERROR_OR_REPORT_MASK			0x00000001
#define L_FUNCTION_BEGIN			0x00000001
#define L_FUNCTION_END				0x00000002
#define L_FUNCTION_STEP_LO			0x00000004
#define L_FUNCTION_STEP_HI			0x00000008
#define L_IN_LOOP_BEGIN				0x00000010
#define L_IN_LOOP_END				0x00000020
#define L_IN_LOOP_STEP_LO			0x00000040
#define L_IN_LOOP_STEP_HI			0x00000080
#define L_HI_FUNCTION_BEGIN			0x00000100
#define L_HI_FUNCTION_END			0x00000200
#define L_HI_FUNCTION_STEP_LO			0x00000400
#define L_HI_FUNCTION_STEP_HI			0x00000800




#define LOG_TRACE(trace_flag_name, trace_flag_mask, sprintf_parameters)	\
if ((L_log_trace::flag [trace_flag_name] & trace_flag_mask) > 0)	\
  {									\
    vchar *l_buf_xxx = U_print::vcsprintf sprintf_parameters;		\
    L_log::log_trace(l_buf_xxx);					\
  }




class L_log_trace

{
public:
    static void			set_flag
				    (enum L_trace_flag_names trace_flag_name,
				    unsigned long new_flag);

    static void			clear_all_flags ();

    static void			set_all_flags_full_blast ();

    static unsigned long	get_flag
				    (enum L_trace_flag_names trace_flag_name);
				    
    static int			trace_active ();

    static unsigned long	flag [L_LAST_TRACE_FLAG];

    static void			set_system_test_flag (t_boolean p_flag)
				    { system_test_flag = p_flag; }
    static t_boolean		get_system_test_flag ()
				    { return system_test_flag; }


    static void			start_system_test
				    (String p_file, String p_title);
    static void			stop_system_test ();
    static void*		system_test_output;

private:
    static t_boolean		system_test_flag;
};




#endif
