/*========================================================================
 *
 * File:      $RCSfile: sw_suprp.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:09 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef W_SUP_PROP_WINDOW_HH
#define W_SUP_PROP_WINDOW_HH

#include <sg_suprp.hh>

#ifdef OLD_FILE_NAMES
#include <DBU_string.hh>
#else
#include <u_string.hh>
#endif




class W_support_prop_window : public W_support_prop_gui_drivers

{
public:

	static void		show ();

    static void		show_data_in_window ();
    static void		apply_trace_data_from_window ();
	static void		email_support_log ();

    static void		toggle_trace_log_data_in_window ();

	static void		start_test ();
	static void		stop_test ();

private:
				W_support_prop_window ();
	virtual		~W_support_prop_window ();


	static W_support_prop_window * support_prop_window_ptr;

    static void		set_trace_log_data_in_window ();
	static void		clear_all_trace_values ();

	static String	test_file;
	static int		test_number;
};

#endif
