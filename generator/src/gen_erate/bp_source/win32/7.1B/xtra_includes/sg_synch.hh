/*========================================================================
 *
 * File:      $RCSfile: sg_synch.hh,v $
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
#ifndef SG_SYNCH_HH
#define SG_SYNCH_HH


#include <sw_com.hh>


class W_synch_service_window;
class Domain;




class W_synch_service_gui_drivers : public W_window

{
public:
    virtual W_synch_service_window*
			get_synch_service_window_ptr () = 0;


    enum                synch_widget_type
                            { SYNCH_LIST, PARM_LIST,
			      SYNCH_INVOKE, SYNCH_INVOKE_DEQUEUE,
			      PARM_APPLY,  PARM_RESET, PARM_VALUE
			      };

			W_synch_service_gui_drivers (Domain *);
    virtual		~W_synch_service_gui_drivers ();

    void		gui_set_icon_label (const vchar*);
    void        gui_set_notation();
    
    void		gui_activate		(synch_widget_type);
    void		gui_inactivate		(synch_widget_type);
    void		gui_hide		(synch_widget_type);
    void		gui_show		(synch_widget_type);

    void		gui_sort_list		(synch_widget_type);
    void		gui_clear_list		(synch_widget_type);
    void		gui_update_item_in_list	(synch_widget_type, int, const vchar *);
    void		gui_delete_remaining_items (synch_widget_type, int);
    void		gui_select_item_in_list	(synch_widget_type, int);
    void		gui_cut_item_from_list	(synch_widget_type, int);
    int			gui_get_rows_in_list	(synch_widget_type);
    int			gui_get_selected_row	(synch_widget_type);
    vchar *		gui_get_list_name_string (synch_widget_type, int );
    
    void		gui_set_value_str	(synch_widget_type, const vchar*);
    vchar *		gui_get_value_str	(synch_widget_type);
    void		gui_move_caret_to_value_str (synch_widget_type);

    void *		gui_window_ptr;

};




#endif
