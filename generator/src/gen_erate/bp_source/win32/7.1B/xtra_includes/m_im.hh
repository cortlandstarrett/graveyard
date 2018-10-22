/*========================================================================
 *
 * File:      $RCSfile: m_im.hh,v $
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
#include <mc_dbms/mc_dbms.hh>

#ifndef M_IM_HH
#define M_IM_HH




#include <m_model.hh>

#include <d_typdef.hh>
#include <d_im_oam.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros


class D_im_ocm_oam;
class Domain_id;
class Relationship;
class Object;

class M_im : public M_model
{
public:
    static M_im*	create_im (D_im_ocm_oam*);
    virtual		~M_im ();

    virtual void	render_graphical_element_data (CE_model_glue*, Id);

    virtual t_boolean	audit_data (Description  &p_err_msg);

    CE_model_glue::ShapeMeaning GetShapeMeaning(Id p_id_type,
                                                Description &err_msg);

    virtual t_boolean	shape_created
			    (Id* created_object_id_ptr,
			    CE_model_glue::ShapeMeaning,
			    Id p_id_type,
			    Description &p_err_msg);
    virtual t_boolean	connector_created__shape_shape
			    (Id* created_simple_rel_id_ptr,
			    Id one_side_obj_id, Id other_side_obj_id,
			    Description &p_err_msg);
    virtual t_boolean	connector_created__shape_connector
			    (Id assoc_obj_id, Id rel_id,
			    Description &p_err_msg);
    virtual t_boolean	connector_created__shape_dot__primary
			    (Id* created_inh_rel_id_ptr,
			    Id supertype_obj_id,
			    Description &p_err_msg);
    virtual t_boolean	connector_created__shape_dot__secondary
			    (Id subtype_obj_id, Id inh_rel_id,
			    Description &p_err_msg);

    virtual t_boolean	get_warning_msg_for_cut_shape
			    (Id cut_obj_id, t_boolean is_delete,
			    Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_shape
			    (Id cut_rel_id, Id obj1_id, Id obj2_id, t_boolean is_delete,
			    Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_connector
			    (Id cut_assoc_rel_id, Id assoc_obj_id, t_boolean is_delete,
			    Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_dot__primary
			    (Id cut_inh_rel_id, Id subtype_obj_id, t_boolean is_delete,
			    Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_dot__secondary
			    (Id cut_inh_rel_id, Id subtype_obj_id, t_boolean is_delete,
			    Description &p_warning_msg);

    virtual t_boolean	cut_shape
			    (Id cut_obj_id);
    virtual t_boolean	cut_connector__shape_shape
			    (Id cut_rel_id, Id obj1_id, Id obj2_id);
    virtual t_boolean	cut_connector__shape_connector
			    (Id cut_assoc_rel_id, Id assoc_obj_id);
    virtual t_boolean	cut_connector__shape_dot__primary
			    (Id cut_inh_id, Id supertype_obj_id);
    virtual t_boolean	cut_connector__shape_dot__secondary
			    (Id cut_inh_id, Id subtype_obj_id);

    virtual t_boolean	copy_shape
			    (Id copy_obj_id);
    virtual t_boolean	copy_connector__shape_shape
			    (Id copy_rel_id, Id obj1_id, Id obj2_id);
    virtual t_boolean	copy_connector__shape_connector
			    (Id copy_assoc_rel_id, Id assoc_obj_id);
    virtual t_boolean	copy_connector__shape_dot__primary
			    (Id copy_inh_id, Id supertype_obj_id);
    virtual t_boolean	copy_connector__shape_dot__secondary
			    (Id copy_inh_id, Id subtype_obj_id);

    virtual t_boolean	export_shape (Id cut_shape_id, IE_export_sql *);
    virtual t_boolean	export_connector__shape_shape
			    (Id copy_rel_id, IE_export_sql *, Id obj1_id, Id obj2_id);
    virtual t_boolean	export_connector__shape_connector
			    (Id copy_assoc_rel_id, IE_export_sql *, Id assoc_obj_id);
    virtual t_boolean	export_connector__shape_dot__primary
			    (Id copy_inh_id, IE_export_sql *, Id supertype_obj_id);
    virtual t_boolean	export_connector__shape_dot__secondary
			    (Id copy_inh_id, IE_export_sql *, Id subtype_obj_id);

	virtual Id paste_obj_shape (Object* p_obj_ptr);
	virtual Id paste_iobj_shape (D_cp_o_iobj* p_obj_ptr);
	virtual Id paste_rel_connector (D_cp_r_rel* p_rel_ptr);
    virtual void fix_ref_attrs(D_cp_r_rel* p_rel_ptr);

    void		create_flattened_oval_in_ocm (Id, Id, t_boolean);
    void		cut_flattened_oval_from_ocm (Id);
    void		create_flattened_oval_in_oam (Id, Id, t_boolean);
    void		cut_flattened_oval_from_oam (Id);
    void		cut_orig_access_paths_from_oam (Id);


    Id			create_object
			    (int number, const vchar* name, const vchar* keyletter);

    Id			create_attribute
			    (Id object_id, const vchar* name);

    void		make_attribute_identifying
			    (Id attribute_id, int id_number);

    void		make_attribute_referential
			    (Id attribute_id, int rel_number);

    Id			create_simple_relationship
			    (int rel_number, Id one_side_obj_id,
			    Id other_side_obj_id, 
			    t_multiplicity one_side_multiplicity,
			    t_conditionality one_side_conditionality,
			    t_multiplicity other_side_multiplicity,
			    t_conditionality other_side_conditionality);

    Id			create_associative_relationship
			    (int rel_number, Id one_side_obj_id,
			    Id other_side_obj_id, Id assoc_obj_id,
			    t_multiplicity one_side_multiplicity,
			    t_conditionality one_side_conditionality,
			    t_multiplicity other_side_multiplicity,
			    t_conditionality other_side_conditionality,
			    t_multiplicity assoc_multiplicity);

    Id			create_inheritance_relationship
			    (int rel_number, Id supertype_obj_id);

    t_boolean		append_inheritance_relationship
			    (Id inh_rel_id, Id subtype_obj_id);


    Domain_id		get_domain_id ();
    Id			get_im_ocm_oam_id ();
    D_im_ocm_oam*	get_im_ocm_oam_ptr () { return im_ocm_oam_ptr; }

	virtual		Domain * get_domain_ptr ()
					{ return im_ocm_oam_ptr->get_domain_ptr (); }

    // i2778.1.2 deleted

    virtual Id assign_next_ce_id()
    {
      return get_im_ocm_oam_ptr ()->      // i2778.1.1 changed
        get_assigners()->ce_id_assigner().assign_next_id();
    }

    // i2778.3.2.2 begin
    virtual void update_ce_id(const Id& p_id)
    {
        get_im_ocm_oam_ptr()->get_assigners()->
	       ce_id_assigner().update_next_value(p_id.get_value_id()); 
    }
    // i2778.3.2.2 end

    void		toggle_view_object_numbers ();
    void		toggle_view_object_key_letters ();
    void		toggle_view_object_attributes ();
    void		toggle_view_relationship_text_phrases ();

	virtual t_model_type get_model_type()
		{ return IM_TYPE; }

	virtual M_Paint_Window* get_state_model(t_model_type p_type, Id id, Id& sm_id);
	virtual void create_state_model_config(t_model_type p_type, Id new_object_id);

    DELETE_DOWN_DECL_SUBTYPE()


protected:
			M_im (D_im_ocm_oam*);



private:

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
  

    static mc_dbms_typespec*	get_mc_dbms_typespec();

    void		render_relationship_data_SM
			    (CE_model_glue*, Relationship*);
    void		render_relationship_data_UML
			    (CE_model_glue*, Relationship*);

    mc_dbms_relationship_1_1(M_im,im_ocm_oam_ptr,D_im_ocm_oam,m_M_im_ptr,D_im_ocm_oam*)im_ocm_oam_ptr;


    t_boolean		view_object_numbers;
    t_boolean		view_object_key_letters;
    t_boolean		view_object_attributes;
    t_boolean		view_relationship_text_phrases;

		
};



#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
