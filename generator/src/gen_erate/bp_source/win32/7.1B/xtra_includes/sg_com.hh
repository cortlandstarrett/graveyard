/*========================================================================
 *
 * File:      $RCSfile: sg_com.hh,v $
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
#ifndef W_GUI_DRIVERS_HH
#define W_GUI_DRIVERS_HH

#include <vresource.h>

#include <u_string.hh>
#include <u_desc.hh>



// Pointer to Galaxy resource
//
extern vresource simulator_resource;


// Global scratch area for character strings returned from gui functions.
//
#define RETURN_STRING_SIZE 16384
extern char return_char [RETURN_STRING_SIZE];
extern vchar return_vchar [RETURN_STRING_SIZE];

#define CLEAR_RETURN_CHAR return_char[0] = '\0';

#define CLEAR_RETURN_VCHAR return_vchar[0] = '\0';


class W_gui_drivers
{
public:
    enum t_gui_window_type {BASE, POPUP};

	enum t_push_pin_state {PIN_IN, PIN_OUT};

    void		set_gui_window_ptr(void * p_window_ptr, t_gui_window_type);

	void		gui_set_push_pin_state (t_push_pin_state);

    void		gui_post_ok_notice (GS_string &message_string);
    t_boolean	gui_post_yes_no_notice (const Description &message_string);
    int			gui_post_cancel_notice (GS_string &message_string);

    void		gui_set_window_label (GS_string &label_string);
    void		gui_set_window_label (Description &label_string);

    void		gui_display_info (GS_string &);
    void		gui_display_error (GS_string &);
    void		gui_display_error (Description &);
    void		gui_display_error (String &);
    void		gui_clear_window_footer ();

    void		gui_show_window ();
    void                close();

    void		gui_window_update__quit ();


protected:
			W_gui_drivers ();
    virtual		~W_gui_drivers ();


private:
    void *		gui_window_object_ptr;
    t_gui_window_type	gui_window_type;
};



#endif
