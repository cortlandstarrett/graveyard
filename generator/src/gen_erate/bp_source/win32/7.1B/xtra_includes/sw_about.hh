/*========================================================================
 *
 * File:      $RCSfile: sw_about.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:15 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef W_ABOUT_WINDOW_HH
#define W_ABOUT_WINDOW_HH

#include <sg_about.hh>




class W_about_window : public W_about_gui_drivers

{
public:

				W_about_window ();
	virtual		~W_about_window ();

	static void		show ();

    static void		show_data_in_window ();

private:

	static W_about_window * about_window_ptr;
};

#endif
