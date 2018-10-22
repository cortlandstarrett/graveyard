/*========================================================================
 *
 * File:      $RCSfile: w_ctrl.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:13 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef W_CONTROL_HH
#define W_CONTROL_HH


#include <d_domain.hh>

#include <u_id.hh>

class Domain;
class D_data_type;
class D_synchronous_service;
class D_bridge;
class D_transformer;
class D_dd_srm_scm_sam;
class D_im_ocm_oam;
class D_sm_spt_pm;
class D_subsys;
class D_external_entity;
class Object;
class Imported_object;
class Relationship;
class Attribute;
class Attr_ref_in_object;
class D_sm_state;
class D_transition;
class D_action;
class D_communication_path;
class D_access_path;
class D_external_entity_in_model;
class D_sm_event;
class D_sm_event_data_item;
class D_external_entity_event;
class D_external_entity_event_data_item;
class D_cant_happen;
class D_event_ignored;
class D_enumerator;

class W_window;
class W_model_gui_drivers;

class CE_model_glue;

enum t_control_type {
	INDEX_WINDOW			= 0,
	ABOUT_WINDOW			= 1,
	PRINT_SETUP_WINDOW		= 2,
	PRINT_OPTIONS_WINDOW	= 3,
	MODEL_PRINT_OPTIONS_WINDOW	= 4,
	NOTEBOOK_WINDOW			= 5,
	EXPORT_WINDOW			= 6,
	SUPPORT_WINDOW			= 7,
	USER_WINDOW				= 8,
	PROJECT_WINDOW			= 9,
	MESSAGE_LIST_WINDOW		= 10
};


class W_control
{
public:
	static t_boolean			freeze_control;


	// Control Functions
	//
	static void					insert_window (W_window *);
	static void					delete_window (W_window *);

	static W_window*			get_cursor_established_window_ptr ();
	static Domain *				get_cursor_established_window_domain_ptr ();
	static D_dd_srm_scm_sam*	get_cursor_established_window_dd_ptr ();
	static D_im_ocm_oam*		get_cursor_established_window_im_ptr ();
	static D_sm_spt_pm*			get_cursor_established_window_sm_ptr ();

	static void			set_cursor_established_window_type (t_model_type p_type)
							{ cursor_established_window_type = p_type; }
	static t_model_type	get_cursor_established_window_type ()
							{ return cursor_established_window_type; }
	static t_boolean	get_all_window_quit () { return all_window_quit; }

	static void					establish_cursor (W_window *);
	static void					deestablish_cursor ();

	static void			all_window_update__quit ();
	static void			all_window_update__deselect ();
	static void			all_window_update__select (Domain_id, Id, t_boolean);

	static void			all_window_update__rerender (Domain_id);
	static void			all_window_close (Domain_id);
	static void			all_window_update__rerender_data__class
							(Domain_id, t_class_type);
	static void			all_window_update__rerender_data__item (Domain_id, Id, t_boolean);

	static void			all_window_update__version (Domain_id, Id);

	static void			all_window_save_display_info (Domain_id, Id);

	static void			all_window_update__edit_menu_paste ();

	static Domain_id	get_id_of_domain_under_update ()
							{ return id_of_domain_under_update; }
 

	static Id			get_selected_item_id () { return selected_item_id; }
	static Id			get_deselected_item_id () { return deselected_item_id; }

	static D_external_entity*		get_selected_external_entity_ptr ();
	static D_subsys*				get_selected_dd_subsystem_ptr ();
	static Object*					get_selected_object_ptr ();
	static D_sm_spt_pm*				get_selected_object_sm_ptr ();
	static Imported_object*			get_selected_imported_object_ptr ();
	static Relationship*			get_selected_relationship_ptr ();
	static D_communication_path*	get_selected_communication_path_ptr ();
	static D_access_path*			get_selected_access_path_ptr ();
	static D_sm_state*				get_selected_state_ptr ();      
	static D_transition*			get_selected_transition_ptr ();
	static D_external_entity_in_model*
			get_selected_external_entity_in_model_ptr ();


	static t_boolean			parse_dd_action_specs (D_dd_srm_scm_sam *, t_boolean p_set_title);
	static t_boolean			parse_all_dd_action_specs (D_dd_srm_scm_sam *, t_boolean p_set_title);
	static t_boolean			parse_oim_action_specs (D_im_ocm_oam *, t_boolean p_set_title);
	static t_boolean			parse_all_oim_action_specs (D_im_ocm_oam *, t_boolean p_set_title);
	static t_boolean			parse_all_sm_action_specs (D_sm_spt_pm *, t_boolean p_set_title);


	// Drawing Window accessors
	//
	static void			show_drawing_window (D_dd_srm_scm_sam *, t_model_type);
	static void			show_drawing_window (D_im_ocm_oam *, t_model_type);
	static void			show_drawing_window (D_sm_spt_pm *, t_model_type);

	static t_boolean	print_drawing_window
						(D_dd_srm_scm_sam *, t_model_type,
                            t_boolean use_print_zoom, int print_zoom_font_size, String &p_err_msg);
	static t_boolean	print_drawing_window
						(D_im_ocm_oam *, t_model_type,
                            t_boolean use_print_zoom, int print_zoom_font_size,  String &p_err_msg);
	static t_boolean	print_drawing_window
						(D_sm_spt_pm *, t_model_type,
                            t_boolean use_print_zoom, int print_zoom_font_size,  String &p_err_msg);


	// Text Window accessors
	//
	static void			show_text_window (t_class_type);
	static void			show_text_window (D_dd_srm_scm_sam *);
	static void			show_text_window (D_data_type *);
	static void			show_text_window (D_synchronous_service *);
	static void			show_text_window (D_subsys *);
	static void			show_text_window (D_external_entity *);
	static void			show_text_window (D_external_entity_event *);
	static void			show_text_window (D_external_entity_event_data_item *);
	static void			show_text_window (Object *);
	static void			show_text_window (Relationship *);
	static void			show_text_window (Attribute *);
	static void			show_text_window (Attr_ref_in_object *);
	static void			show_text_window (D_sm_spt_pm *);
	static void			show_text_window (D_sm_event *);
	static void			show_text_window (D_sm_event_data_item *);
	static void			show_text_window (D_action *);
	static void			show_text_window (D_bridge *);
	static void			show_text_window (D_transformer *);
	static void			show_text_window (D_cant_happen *);
	static void			show_text_window (D_event_ignored *);
	static void			show_text_window (D_enumerator *);

	static t_boolean    print_text_window (D_action *, void* printer_ptr, Description& error_msg);
	static t_boolean    print_text_window (D_synchronous_service *, void* printer_ptr, Description& error_msg);
	static t_boolean    print_text_window (D_transformer *, void* printer_ptr, Description& error_msg);
	static t_boolean    print_text_window (D_bridge *, void* printer_ptr, Description& error_msg);
	static t_boolean    print_text_window (Attribute *, void* printer_ptr, Description& error_msg);

	// Editing Window accessors
	//
	static void			show_editing_window (t_class_type);

	static void			clear_editing_window (t_class_type);
	static void			clear_all_editing_windows ();

	static t_boolean	check_for_unapplied_edits (t_boolean p_clear_flag);

	static void			show_matrix_window (D_sm_spt_pm *);


	// Control Window accessors
	static void			show_control_window (t_control_type, t_boolean = FALSE);
	static void			show_control_window (t_control_type, D_dd_srm_scm_sam *, t_class_type);
	static void			show_control_window (t_control_type, D_external_entity *, t_class_type);
	static void			show_control_window (t_control_type, D_im_ocm_oam *, t_class_type, CE_model_glue*);
	static void			show_control_window (t_control_type, D_sm_spt_pm *, t_class_type, CE_model_glue*);
	static void			show_control_window (t_control_type, W_model_gui_drivers *);

	static void			create_control_window (t_control_type);


private:
	static mc_dbms_List<W_window*>* window_collection_ptr;

	static W_window *	cursor_established_window_ptr;
	static t_model_type	cursor_established_window_type;

	static Id			selected_item_id;
	static Id			deselected_item_id;
	static W_window *	previous_cursor_established_window_ptr;

	static Domain_id	id_of_domain_under_update;

	static t_boolean        all_window_quit;

};

#endif

