/*========================================================================
 *
 * File:      $RCSfile: sw_index.hh,v $
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
#ifndef SW_INDEX_HH
#define SW_INDEX_HH

#include <sg_index.hh>
#include <sw_ctrl.hh>
#include <u_string.hh>




class Sim_reference;
class I_SM_Evt_Inst;




class W_index_window : public W_index_gui_drivers

{
public:
    static W_index_window*	get_index_window_ptr ()
				    { return index_window_ptr; }

				W_index_window ();
    virtual			~W_index_window ();

    static GS_string		copyright_str;

    static void			audit_sim_db ();

    static void			system_clock_tick_occurred ();
    static void			start_system_clock_tick (t_boolean);    // i2844.1.2.1 changed
    static void			stop_system_clock_tick ();

    static Domain_id		get_selected_domain_id ()
				    { return selected_domain_id; }

    static t_boolean		load_domain_ooa_db
				    (Domain_id domain_id, GS_string &p_err_msg);

    static t_boolean		load_sim_db
				    (mc_dbms_database*, GS_string &p_err_msg);
    static t_boolean		new_sim_db
				    (mc_dbms_database*, GS_string &p_err_msg);

    static void			show (t_boolean show_support_properties);
    static void			show ();
    static void			show_objinst_window ();
    static void			show_synch_service_window ();
    static void			window_done_event ();

    static void			update_database_file_list ();
    static void			update_subsystem_list ();
    static void			update_object_list ();

    static int			select_domain (int);
    static void			deselect_domain (int);
    static void			select_subsystem (int);
    static void			deselect_subsystem (int);
    static void			select_object (int);
    static void			deselect_object (int);

    static void			update_domain_based_model_version ();
    static void         update_subsystem_based_model_version ();
    static void			update_object_based_model_version ();


    virtual void		window_update__rerender ();
    virtual void		window_update__processing_event ();

    static void			populate_domain_version_stack ();
    static void			populate_subsystem_version_stack ();
    static void			populate_object_version_stack ();
    static void			populate_object_breakpoint_menu ();
    
    static void			dd_srm_scm_sam_version_update ();
    static void			im_ocm_oam_version_update ();
    static void			sm_spt_pm_version_update ();


    static void			write_log (const Description& p_log_str);

    static void			einst_dequeue ();
    static void         einst_delete ();
    static void			update_einst_list ();
    static I_SM_Evt_Inst*	get_selected_einst_ptr ();

	static void		refresh_clock_times();
    static void			set_clock_times
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


    static W_index_window*	index_window_ptr;

    static Sim_reference* get_selected_simref() {return selected_simref;}
private:
    static void			domain_deselected ();
    static void			subsystem_deselected ();
    static void			object_deselected ();

    static Domain_id		selected_domain_id;
    static Id			selected_dd_srm_scm_sam_id;
    static Id			selected_im_ocm_oam_id;
    static Id			selected_object_id;
    static Id			selected_sm_spt_pm_id;
    static Sim_reference*	selected_simref;

};

 



inline
void
W_index_window::dd_srm_scm_sam_version_update ()

{
    update_database_file_list ();
    W_control::all_window_update__version
	(selected_domain_id, selected_dd_srm_scm_sam_id);
}



inline
void
W_index_window::im_ocm_oam_version_update ()

{
    update_subsystem_list ();
    W_control::all_window_update__version
	(selected_domain_id, selected_im_ocm_oam_id);
}


inline
void
W_index_window::sm_spt_pm_version_update ()

{
    update_object_list ();
    W_control::all_window_update__version
	(selected_domain_id, selected_sm_spt_pm_id);
}

 


#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
