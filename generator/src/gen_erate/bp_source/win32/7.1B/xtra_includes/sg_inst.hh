/*========================================================================
 *
 * File:      $RCSfile: sg_inst.hh,v $
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
#ifndef SG_INST_HH
#define SG_INST_HH


#include <sw_com.hh>


class W_inst_window;
class Object;
class GS_string;
class Description;
class I_Attribute_Instance;




class W_inst_gui_drivers : public W_window

{
public:
    virtual W_inst_window*
			get_inst_window_ptr () = 0;


    enum                inst_widget_type
                            { OINST_LIST, AINST_LIST, EINST_LIST, ESDII_LIST,
			      OINST_CREATE, OINST_DELETE,
			      AINST_APPLY,  AINST_RESET,
			      EINST_CREATE, EINST_DELETE, EINST_DEQUEUE, EINST_CREATION_CREATE,
			      ESDII_APPLY,  ESDII_RESET,
			      AINST_VALUE,  ESDII_VALUE,
			      OINST_ST_MACH };

			W_inst_gui_drivers (Object *);
    virtual		~W_inst_gui_drivers ();

    void		gui_set_icon_label (const vchar*);
    void		gui_set_notation();
    void        gui_populate_change_state(I_Attribute_Instance* selected_ainst_ptr);

    void		gui_activate		(inst_widget_type);
    void		gui_inactivate		(inst_widget_type);
    void		gui_hide		(inst_widget_type);
    void		gui_show		(inst_widget_type);

    void		gui_sort_list		(inst_widget_type);
    void		gui_clear_list		(inst_widget_type);
    void		gui_update_item_in_list	(inst_widget_type, int, const vchar *);
    void		gui_delete_remaining_items (inst_widget_type, int);
    void		gui_select_item_in_list	(inst_widget_type, int);
    void		gui_cut_item_from_list	(inst_widget_type, int);
    int			gui_get_rows_in_list	(inst_widget_type);
    int			gui_get_selected_row	(inst_widget_type);
    vchar *		gui_get_list_name_string (inst_widget_type, int );
    
    void		gui_set_value_str	(inst_widget_type, const vchar*);
    vchar *		gui_get_value_str	(inst_widget_type);
    void		gui_move_caret_to_value_str (inst_widget_type);

    void		gui_clear_einst_create_menu ();
    void		gui_einst_create_menu_add_item
				    (const Description& menu_item_str);

    void		gui_clear_einst_create_creation_menu ();
    void		gui_einst_create_creation_menu_add_item
				    (const Description& menu_item_str);

private:

    void *		gui_window_ptr;

};




#endif
