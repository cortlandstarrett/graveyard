/*========================================================================
 *
 * File:      $RCSfile: sg_suprp.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:10 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef W_SUP_PROP_GUI_DRIVERS_HH
#define W_SUP_PROP_GUI_DRIVERS_HH

#include <sw_com.hh>

#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#else
#include <u_typdef.hh>
#endif




#define MAX_SLIDER_VALUE 12
#define MIN_SLIDER_VALUE 0

class W_support_prop_gui_drivers : public W_window
{
public:

	enum t_slider_type {D_DATA, M_MODEL, N_PROJ_NB, L_ACTION, L_XLATOR,
			W_WINDOWS, W_STATES, W_GUI_DRIVERS, W_GUI_STUBS, IE_IMPORT_EXPORT,
			CE_STATES, RENDER};

				W_support_prop_gui_drivers ();
	virtual		~W_support_prop_gui_drivers ();

	static int		gui_get_catagory_setting ();

	static void		gui_show_trace_log ();
	static void		gui_show_system_test ();

	static void		gui_toggle_all_sliders ();
	static void		gui_set_slider_value (t_slider_type, int);
	static int		gui_get_slider_value (t_slider_type);

	static void		gui_set_test_file (char *);
	static char *	gui_get_test_file ();
	static void		gui_set_test_file_number (int);
	static int		gui_get_test_file_number ();
	static char *	gui_get_test_description ();
	static void		gui_show_test_message ();
	static void		gui_hide_test_message ();

	static void *		gui_window_ptr;


private:

	static t_boolean	gui_sliders_toggle;

};



#endif
