/*========================================================================
 *
 * File:      $RCSfile: m_scm.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:11 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef M_SCM_HH
#define M_SCM_HH




#include <m_model.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros


class D_dd_srm_scm_sam;
class Domain_id;



class M_scm : public M_model
{
public:
    static M_scm*	create_scm (D_dd_srm_scm_sam*);

    CE_model_glue::ShapeMeaning GetShapeMeaning(Id p_id_type,
                                                Description &err_msg);

    virtual void	render_graphical_element_data (CE_model_glue*, Id);
    virtual void	render_unidentified_connector_data
			    (CE_model_glue*, Id, Id, Id);

    virtual t_boolean	get_warning_msg_for_cut_shape
			    (Id p_cut_subsystem_id, t_boolean is_delete, Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_shape
			    (Id cut_conn_id, Id subsystem1_id, Id subsystem2_id,
			    t_boolean is_delete, Description &p_warning_msg);

    virtual t_boolean	cut_shape
			    (Id p_cut_subsystem_id);
    virtual t_boolean	cut_connector__shape_shape
			    (Id cut_conn_id,
			    Id subsystem1_id, Id subsystem2_id);

    virtual t_boolean	audit_data (Description &p_err_msg);

    Domain_id   	get_domain_id ();
    Id         		get_dd_srm_scm_sam_id ();
    D_dd_srm_scm_sam*	get_dd_srm_scm_sam_ptr () { return dd_srm_scm_sam_ptr; }

    virtual		Domain * get_domain_ptr ()
					{ return dd_srm_scm_sam_ptr->get_domain_ptr (); }

    // i2778.1.2 deleted

    virtual Id assign_next_ce_id()
			{ return get_dd_srm_scm_sam_ptr()->get_assigners()->
				ce_id_assigner().assign_next_id(); }

    DELETE_DOWN_DECL_SUBTYPE()


protected:
			M_scm (D_dd_srm_scm_sam*);
    virtual		~M_scm ();



private:
    static mc_dbms_typespec*	get_mc_dbms_typespec();

  void		render_subsystem_data_SM  (CE_model_glue*, D_subsys*);
  void		render_subsystem_data_UML (CE_model_glue*, D_subsys*);

  void    render_external_entity_in_model_data_SM
    (CE_model_glue*, D_external_entity_in_model*);
  void    render_external_entity_in_model_data_UML
    (CE_model_glue*, D_external_entity_in_model*);
  

    mc_dbms_relationship_1_1(M_scm,dd_srm_scm_sam_ptr,D_dd_srm_scm_sam,scm_ptr,D_dd_srm_scm_sam *) dd_srm_scm_sam_ptr;

};



#endif
