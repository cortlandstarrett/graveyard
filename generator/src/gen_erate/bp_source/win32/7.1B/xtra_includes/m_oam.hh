/*========================================================================
 *
 * File:      $RCSfile: m_oam.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:05 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef M_OAM_HH
#define M_OAM_HH




#include <m_model.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros


class D_im_ocm_oam;
class Domain_id;
class D_access_path;



class M_oam : public M_model
{
public:
    static M_oam*	create_oam (D_im_ocm_oam*);
    virtual		~M_oam ();

    virtual void	render_graphical_element_data (CE_model_glue*, Id);
	virtual void	render_unidentified_connector_data
				(CE_model_glue*, Id, Id, Id);

    virtual t_boolean	audit_data (Description &p_err_msg);

    CE_model_glue::ShapeMeaning GetShapeMeaning(Id p_id_type,
                                                Description &err_msg);

    virtual t_boolean	shape_created
			    (Id* created_imported_object_id,
			    CE_model_glue::ShapeMeaning,
			    Id p_id_type,
			    Description &p_err_msg);
    virtual t_boolean	connector_created__shape_shape
			    (Id* created_access_path_id_ptr,
			    Id one_side_id, Id other_side_id,
			    Description &p_err_msg);

    virtual t_boolean	get_warning_msg_for_cut_shape
			    (Id p_cut_obj_id, t_boolean is_delete,
			    Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_shape
			    (Id p_cut_evt_access_id, Id p_obj1_id,
			    Id p_obj2_id, t_boolean is_delete, Description &p_warning_msg);

    virtual t_boolean	cut_shape
			    (Id p_cut_obj_id);
    virtual t_boolean	cut_connector__shape_shape
			    (Id p_cut_evt_access_id, Id p_obj1_id,
			    Id p_obj2_id);

    Domain_id		get_domain_id ();
    Id			get_im_ocm_oam_id ();
    D_im_ocm_oam*	get_im_ocm_oam_ptr () { return im_ocm_oam_ptr; }

	virtual		Domain * get_domain_ptr ()
					{ return im_ocm_oam_ptr->get_domain_ptr (); }

    // i2778.1.2 deleted

	virtual Id assign_next_ce_id()
			{ return get_im_ocm_oam_ptr ()->        // i2778.1.1 changed
				get_assigners()->ce_id_assigner().assign_next_id(); }

    // i2778.3.2.2 begin
	virtual void update_ce_id(const Id& p_id)
			{ get_im_ocm_oam_ptr ()->
				get_assigners()->ce_id_assigner().update_next_value(p_id.get_value_id()); }
    // i2778.3.2.2 end

    void		toggle_view_object_numbers ();
    void		toggle_view_object_key_letters ();

    t_boolean		get_auto_mode () { return auto_mode; }
    void		set_auto_mode (t_boolean p_mode) { auto_mode = p_mode; }

    DELETE_DOWN_DECL_SUBTYPE()



protected:
			M_oam (D_im_ocm_oam*);



private:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

  void		render_object_data_SM
    (CE_model_glue*, Object*, Id,
     t_boolean p_view_object_numbers = FALSE,
     t_boolean p_view_object_key_letters = FALSE,
     t_boolean p_view_attributes = FALSE,
     t_boolean p_assigner_flag = FALSE);
  void		render_object_data_UML
    (CE_model_glue*, Object*, Id,
     t_boolean p_view_object_numbers = FALSE,
     t_boolean p_view_object_key_letters = FALSE,
     t_boolean p_view_attributes = FALSE,
     t_boolean p_assigner_flag = FALSE);
  
  void		render_imported_object_data_SM
    (CE_model_glue*, Imported_object*,
     t_boolean p_view_object_numbers = FALSE,
     t_boolean p_view_object_key_letters = FALSE,
     t_boolean p_view_attributes = FALSE);
  void		render_imported_object_data_UML
    (CE_model_glue*, Imported_object*,
     t_boolean p_view_object_numbers = FALSE,
     t_boolean p_view_object_key_letters = FALSE,
     t_boolean p_view_attributes = FALSE);

    void		render_access_path_data_SM
			    (CE_model_glue*, D_access_path*);
    void		render_access_path_data_UML
			    (CE_model_glue*, D_access_path*);

    mc_dbms_relationship_1_1(M_oam,im_ocm_oam_ptr,D_im_ocm_oam,m_M_oam_ptr,D_im_ocm_oam*)im_ocm_oam_ptr;


    t_boolean		view_object_numbers;
    t_boolean		view_object_key_letters;
	
    t_boolean		auto_mode;

};



#endif
