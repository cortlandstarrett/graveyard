/*========================================================================
 *
 * File:      $RCSfile: sg_about.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:14 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef W_ABOUT_GUI_DRIVERS_HH
#define W_ABOUT_GUI_DRIVERS_HH

#include <sw_com.hh>


#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#else
#include <u_typdef.hh>
#endif




class W_about_gui_drivers : public W_window
{
public:

				W_about_gui_drivers ();
	virtual		~W_about_gui_drivers ();

	static void		gui_set_version_string (char *);

	static void *		gui_window_ptr;


private:

};



#endif
