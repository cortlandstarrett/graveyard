/*========================================================================
 *
 * File:      $RCSfile: sg_index.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:12 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef SG_INDEX_HH
#define SG_INDEX_HH

#include <sw_com.hh>
#include <u_desc.hh>
struct vmenu;
class BreakpointLocation;
 

class RM_file;




class W_index_gui_drivers : public W_window
{
public:

    enum		t_list_type
			    { DATABASE, SUBSYSTEM, OBJECT, EINST };

			W_index_gui_drivers ();
    virtual		~W_index_gui_drivers ();

    static void		gui_set_timer_control ();
    static void		gui_set_run_mode_slider (int p_value);

    static void		gui_inactivate_sim_load_create_file_menu_items ();
    static void     gui_activate_sim_load_create_file_menu_items ();
    static void		gui_update_most_recent_files_list();
   
    static void     gui_set_notation();
    
    static void		gui_show_support_properties_button (t_boolean);

    static void		gui_show_version_control_all ();
    static void		gui_hide_version_control_all ();
    static void		gui_show_object_version_control ();
    static void		gui_hide_object_version_control ();
    static void		gui_inactivate_version_control (t_list_type);
    static void		gui_activate_version_control (t_list_type);

    static void		gui_inactivate_list (t_list_type);
    static void		gui_activate_list (t_list_type);

    static void		gui_inactivate_dequeue ();
    static void		gui_activate_dequeue ();

    static void		gui_inactivate_show ();
    static void		gui_activate_show ();

    static void		gui_show_panel_list (t_list_type);
    static void		gui_hide_panel_list (t_list_type);

    static void		gui_delete_remaining_items (t_list_type, int row);
    static void		gui_update_item_in_list
			    (t_list_type, int row, const vchar* name_string);

    static void		gui_select_item_in_list (t_list_type, int row);
    static void		gui_sort_panel_list (t_list_type);
    static int		gui_get_rows_in_list (t_list_type);
    static int		gui_get_selected_row (t_list_type);
    static vchar*	gui_get_list_name_string (t_list_type, int row);


    static void		gui_set_selected_domain_message (const char*);
    static void		gui_set_loaded_sim_file_message (const char*);
    static void		gui_set_log_file_name
			    (const GS_string& p_path_name_str,
			    const GS_string& p_sim_name_str);

    static void		gui_clear_domain_version_stack ();
    static void		gui_select_domain_version (int);
    static void		gui_set_domain_version_stack_item
      (int row, const Description &p_branch_name, const float p_version_num);
    static t_boolean gui_get_domain_version_stack_item
      (Description &p_branch_name, float &p_version_num);

    static void		gui_clear_subsystem_version_stack ();
    static void		gui_select_subsystem_version (int);
    static void		gui_set_subsystem_version_stack_item
      (int row, const Description &p_branch_name, const float p_version_num);
    static t_boolean gui_get_subsystem_version_stack_item
      (Description &p_branch_name, float &p_version_num);

    static void		gui_clear_object_version_stack ();
    static void		gui_clear_breakpoint_menu ();
    static void     gui_add_object_breakpoint_state_item(Description &d,BreakpointLocation *bpl,t_boolean);
 
    static void		gui_select_object_version (int);
    static void		gui_set_object_version_stack_item
      (int row, const Description &p_branch_name, const float p_version_num);
    static t_boolean gui_get_object_version_stack_item
      (Description &p_branch_name, float &p_version_num);

    static void		gui_write_log (const Description&);
    static void		gui_set_system_clock_value
			    (const Description& p_clock_value_str);
	static void     gui_get_clock_times();
    static void		gui_set_clock_times
			    (t_ulong p_tick_us,
           t_ulong p_action_us,
           t_ulong p_select_related_by_us,
           t_ulong p_select_from_instances_of_us,
           t_ulong p_for_initial_us,
           t_ulong p_for_iteration_us,
           t_ulong p_while_initial_us,
           t_ulong p_while_iteration_us,
           t_ulong p_break_us,
           t_ulong p_continue_us,
           t_ulong p_return_us,
           t_ulong p_create_object_instance_us,
           t_ulong p_delete_object_instance_us,
           t_ulong p_relate_us,
           t_ulong p_unrelate_us,
           t_ulong p_generate_us,
           t_ulong p_create_event_instance_us,
           t_ulong p_assign_us,
           t_ulong p_transformation_us,
           t_ulong p_if_us,
           t_ulong p_elif_us,
           t_ulong p_bridge_us,
		   t_ulong p_synch_service_us);

    static void*	filechsr_window_ptr;

    static void*	gui_window_ptr;
    static void*	gui_clock_window_ptr;
    static void*	gui_timer_ptr;

    static void closeLogFile();

protected:



private:
    //static vmenu *menu_bp_Event;   //setup for editing the breakpoint menus
    //static vmenu *menu_bp_Trans; //removed for now until BreakPoint's are complete
	static vmenu *menu_bp_States;

    static GS_string	log_full_file_name_str;
    static RM_file*	log_file_ptr;
};




#endif
