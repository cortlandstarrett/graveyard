/*========================================================================
 *
 * File:      $RCSfile: m_sm.hh,v $
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
#include <mc_dbms/mc_dbms.hh>

#ifndef M_SM_HH
#define M_SM_HH




#include <m_model.hh>

#include <d_sm_pm.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros


class D_sm_spt_pm;
class Domain_id;
class D_sm_state;
class D_transition;



class M_sm : public M_model
{
public:
    static M_sm*	create_sm (D_sm_spt_pm*);

    CE_model_glue::ShapeMeaning GetShapeMeaning(Id p_id_type,
                                                Description &err_msg);

    virtual void	render_graphical_element_data (CE_model_glue*, Id);

    virtual t_boolean	audit_data (Description &p_err_msg);

    virtual t_boolean	shape_created
			    (Id* created_state_id_ptr,
			    CE_model_glue::ShapeMeaning,
			    Id p_id_type,
			    Description &p_err_msg);
    virtual t_boolean	connector_created__shape_shape
			    (Id* created_transition_id_ptr,
			    Id one_side_state_id, Id other_side_state_id,
			    Description &p_err_msg);
    virtual t_boolean	connector_created__shape_dot__primary
			    (Id* created_creation_trans_id,
			    Id initial_state_id,
			    Description &p_err_msg);

    virtual t_boolean	get_warning_msg_for_cut_shape
			    (Id p_cut_state_id, t_boolean is_delete,
			    Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_shape
			    (Id p_cut_tns_id, Id p_state1_id, Id p_state2_id, t_boolean is_delete,
			    Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_dot__primary
			    (Id p_cut_tns_id, Id p_state_id, t_boolean is_delete,
			    Description &p_warning_msg);

    virtual t_boolean	cut_shape
			    (Id p_cut_state_id);
    virtual t_boolean	cut_connector__shape_shape
			    (Id p_cut_tns_id, Id p_state1_id, Id p_state2_id);
    virtual t_boolean	cut_connector__shape_dot__primary
			    (Id p_cut_tns_id, Id p_state_id);

    virtual t_boolean	copy_shape
			    (Id copy_sta_id);
    virtual t_boolean	copy_connector__shape_shape
			    (Id copy_trans_id, Id state1_id, Id state2_id);
    virtual t_boolean	copy_connector__shape_dot__primary
			    (Id copy_trans_id, Id creation_state_id);

	virtual Id paste_state_shape (D_cp_state* p_state_ptr);
	virtual Id paste_trans_connector (D_cp_transition* p_trans_ptr, int);
	virtual int query_num_events();

    virtual t_boolean	export_shape (Id cut_shape_id, IE_export_sql *);
    virtual t_boolean	export_connector__shape_shape
			    (Id copy_tns_id, IE_export_sql *, Id sta1_id, Id sta2_id);
    virtual t_boolean	export_connector__shape_dot__primary
			    (Id copy_tns_id, IE_export_sql *, Id c_state_obj_id);

	Id		create_state (int state_number, const vchar* state_name,
				const vchar * action_description);
	Id		create_transition (Id orig_state_id, Id dest_state_id);


    void		toggle_view_state_numbers ();
    void		toggle_view_action_logic ();
    void		toggle_view_event_data ();
    void		toggle_view_description ();

    Domain_id   	get_domain_id ();
    Id         		get_sm_spt_pm_id ();
    D_sm_spt_pm*	get_sm_spt_pm_ptr () { return m_D_sm_spt_pm_ptr; }
    Object*		get_object_ptr ();

	virtual		Domain * get_domain_ptr ()
					{ return m_D_sm_spt_pm_ptr->get_domain_ptr (); }

    // i2778.1.2 deleted

	virtual Id assign_next_ce_id()
			{ return get_sm_spt_pm_ptr()->get_assigners()->
				ce_id_assigner().assign_next_id(); }

	virtual t_model_type get_model_type()
	{
		if (get_sm_spt_pm_ptr()->get_sm_spt_pm_type () == D_sm_spt_pm::INSTANCE_SM)
		  return ISM_TYPE;
		else
		  return ASM_TYPE;
	}

    DELETE_DOWN_DECL_SUBTYPE()



protected:
			M_sm (D_sm_spt_pm*);
    virtual		~M_sm ();



private:
    static mc_dbms_typespec*	get_mc_dbms_typespec();


    void		render_state_data_SM  (CE_model_glue*, D_sm_state*);
    void		render_state_data_UML (CE_model_glue*, D_sm_state*);

    void		render_transition_data_SM  (CE_model_glue*, D_transition*);
    void		render_transition_data_UML (CE_model_glue*, D_transition*);


    mc_dbms_relationship_1_1(M_sm,m_D_sm_spt_pm_ptr,D_sm_spt_pm,m_M_sm_ptr,D_sm_spt_pm *)m_D_sm_spt_pm_ptr;


    t_boolean		view_state_numbers;
    t_boolean		view_action_logic;
    t_boolean		view_event_data;
    t_boolean		view_description;
};



#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//

