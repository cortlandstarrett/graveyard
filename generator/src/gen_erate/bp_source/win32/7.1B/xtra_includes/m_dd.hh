/*========================================================================
 *
 * File:      $RCSfile: m_dd.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:07 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef M_DD_HH
#define M_DD_HH




#include <m_model.hh>

#include <u_deldwn.hh>     // For delete_down() macros

#include <ce_glue/ce_mdglu.hh>

class D_dd_srm_scm_sam;
class Domain_id;
class IE_export_sql;


class M_dd : public M_model
{
public:
    static M_dd*	create_dd (D_dd_srm_scm_sam*);


    virtual void	render_graphical_element_data (CE_model_glue*, Id);

    virtual t_boolean	audit_data (Description &p_err_msg);


    virtual CE_model_glue::ShapeMeaning GetShapeMeaning(Id p_id_type,
                                                        Description &err_msg);

    virtual t_boolean	shape_created
			    (Id* created_state_id_ptr,
			    CE_model_glue::ShapeMeaning,
			    Id p_id_type,
			    Description &p_err_msg);

    virtual t_boolean	get_warning_msg_for_cut_shape
			    (Id p_cut_state_id, t_boolean is_delete, 
			    Description &p_warning_msg);

    virtual t_boolean	cut_shape
			    (Id p_cut_state_id);

    void		create_rectangle_in_srm_scm_sam (Id);
    void		cut_rectangle_from_srm_scm_sam (Id);


    Domain_id   	get_domain_id ();
    D_dd_srm_scm_sam*	get_dd_srm_scm_sam_ptr () { return dd_srm_scm_sam_ptr; }
    Id         		get_dd_srm_scm_sam_id ();

    virtual		Domain * get_domain_ptr ()
					{ return dd_srm_scm_sam_ptr->get_domain_ptr (); }

    // i2778.1.2 deleted

    virtual Id assign_next_ce_id()
			{ return get_dd_srm_scm_sam_ptr()->get_assigners()->
				ce_id_assigner().assign_next_id(); }

    DELETE_DOWN_DECL_SUBTYPE()


protected:
			M_dd (D_dd_srm_scm_sam*);
    virtual		~M_dd ();



private:
    t_boolean export_shape (Id export_shape_id, IE_export_sql *);

  void		render_subsystem_data_SM  (CE_model_glue*, D_subsys*);
  void		render_subsystem_data_UML (CE_model_glue*, D_subsys*);

  void		render_external_entity_data_SM  (CE_model_glue*, D_external_entity*);
  void		render_external_entity_data_UML (CE_model_glue*, D_external_entity*);

    static mc_dbms_typespec*	get_mc_dbms_typespec();


    mc_dbms_relationship_1_1(M_dd,dd_srm_scm_sam_ptr,D_dd_srm_scm_sam,dd_ptr,D_dd_srm_scm_sam *) dd_srm_scm_sam_ptr;

};



#endif
