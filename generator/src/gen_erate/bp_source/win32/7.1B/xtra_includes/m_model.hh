/*========================================================================
 *
 * File:      $RCSfile: m_model.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:14 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef M_MODEL_HH
#define M_MODEL_HH




#include <r_lang.hh>
#include <ce_glue/ce_mdglu.hh>
#include <ce/c_coord.hh>

#include <u_typdef.hh>
#include <u_id.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros



class Domain;
class CE_persistent_glue;
class Subsystem;
class D_external_entity;
class D_external_entity_in_model;
class D_cp_state;
class D_cp_transition;
class D_cp_r_rel;
class D_cp_o_iobj;
class Object;
class Imported_object;
class Description;
class M_Paint_Window;
class D_sm_event;
class IE_export_sql;

class M_model
{
public:

  virtual CE_model_glue::ShapeMeaning GetShapeMeaning(Id p_id_type,
                                                      Description &err_msg)=0;
  Shape *create_shape (Paint_Window *pw,
                       Coordinate nw,
                       Coordinate se,
                       Id p_id_type,
                       Description &err_msg);
  
  virtual void	fm_ce_render_graphical_element_data
    (CE_model_glue*, Id);
  virtual void	fm_ce_render_unidentified_connector_data
    (CE_model_glue*, Id p_CE_based_connector_id,
     Id p_one_shape_id, Id p_other_shape_id);


  t_boolean		fm_ce_audit_data (Description &p_err_msg);


  t_boolean		fm_ce_shape_created
    (Id* created_shape_id_ptr,
     CE_model_glue::ShapeMeaning,
     Id p_id_type,
     Description &p_err_msg);
  t_boolean		fm_ce_connector_created__shape_shape
    (Id* created_shape_id_ptr,
     Id shape1_id, Id shape2_id,
     Description &p_err_msg);
  t_boolean		fm_ce_connector_created__shape_connector
    (Id shape_id, Id connector_id,
     Description &p_err_msg);
  t_boolean		fm_ce_connector_created__shape_dot__primary
    (Id* created_shape_id_ptr,
     Id shape_id,
     Description &p_err_msg);
  t_boolean		fm_ce_connector_created__shape_dot__secondary
    (Id shape_id, Id connector_id,
     Description &p_err_msg);

  t_boolean		fm_ce_get_warning_msg_for_cut_shape
    (Id cut_shape_id, t_boolean is_delete,
     Description &p_warning_msg);
  t_boolean		fm_ce_get_warning_msg_for_cut_connector__shape_shape
    (Id cut_connector_id, Id shape1_id, Id shape2_id, t_boolean is_delete,
     Description &p_warning_msg);
  t_boolean		fm_ce_get_warning_msg_for_cut_connector__shape_connector
    (Id cut_connector_id, Id shape_id, t_boolean is_delete,
     Description &p_warning_msg);
  t_boolean		fm_ce_get_warning_msg_for_cut_connector__shape_dot__primary
    (Id cut_connector_id, Id shape_id, t_boolean is_delete,
     Description &p_warning_msg);
  t_boolean		fm_ce_get_warning_msg_for_cut_connector__shape_dot__secondary
    (Id cut_connector_id, Id shape_id, t_boolean is_delete,
     Description &p_warning_msg);

  t_boolean		fm_ce_cut_shape
    (Id cut_shape_id);
  t_boolean		fm_ce_cut_connector__shape_shape
    (Id cut_connector_id, Id shape1_id, Id shape2_id);
  t_boolean		fm_ce_cut_connector__shape_connector
    (Id cut_connector_id, Id shape_id);
  t_boolean		fm_ce_cut_connector__shape_dot__primary
    (Id cut_connector_id, Id shape_id);
  t_boolean		fm_ce_cut_connector__shape_dot__secondary
    (Id cut_connector_id, Id shape_id);

  t_boolean		fm_ce_copy_shape
    (Id cut_shape_id);
  t_boolean		fm_ce_copy_connector__shape_shape
    (Id cut_connector_id, Id shape1_id, Id shape2_id);
  t_boolean		fm_ce_copy_connector__shape_connector
    (Id cut_connector_id, Id shape_id);
  t_boolean		fm_ce_copy_connector__shape_dot__primary
    (Id cut_connector_id, Id shape_id);
  t_boolean		fm_ce_copy_connector__shape_dot__secondary
    (Id cut_connector_id, Id shape_id);

  t_boolean		fm_ce_export_shape  
    (Id cut_shape_id, IE_export_sql * p_export_ptr);
  t_boolean		fm_ce_export_connector__shape_shape
    (Id cut_connector_id, IE_export_sql * p_export_ptr, Id shape1_id, Id shape2_id);
  t_boolean		fm_ce_export_connector__shape_connector
    (Id cut_connector_id, IE_export_sql * p_export_ptr, Id shape_id);
  t_boolean		fm_ce_export_connector__shape_dot__primary
    (Id cut_connector_id, IE_export_sql * p_export_ptr, Id shape_id);
  t_boolean		fm_ce_export_connector__shape_dot__secondary
    (Id cut_connector_id, IE_export_sql * p_export_ptr, Id shape_id);

  Id fm_ce_paste_shape(Object*);
  Id fm_ce_paste_shape(D_cp_o_iobj*);
  Id fm_ce_paste_shape(D_cp_state*);
  Id fm_ce_paste_connector(D_cp_r_rel*);
  Id fm_ce_paste_connector(D_cp_transition*, int);

  void fm_ce_fix_ref_attrs(D_cp_r_rel*);

  int fm_ce_query_num_events();

  void set_current_zoom(double zoom);
  void set_current_scroll_position(t_int x, t_int y);
  void set_grid_visible(t_boolean grid_visible);
	   
  double get_current_zoom();
  t_int get_scroll_x();
  t_int get_scroll_y();
  t_boolean get_grid_visible();

  CE_persistent_glue*	get_persistent_glue_ptr ()
    { return persistent_glue_ptr; }

  virtual		Domain * get_domain_ptr () = 0;

  // i2778.1.2 deleted

  virtual Id assign_next_ce_id() = 0;

  // i2778.3.2.1 begin
  virtual void update_ce_id(const Id&)
    { /* do nothing */ }
  // i2778.3.2.1 end

  e_diagram_display_mode get_diagram_display_mode() const;

  t_model_type fm_ce_get_model_type();

  virtual t_model_type get_model_type()
    { return NO_TYPE; }

  M_Paint_Window* fm_ce_get_state_model(t_model_type p_type, Id id, Id& sm_id);

  virtual M_Paint_Window* get_state_model(t_model_type p_type, Id id, Id& sm_id)
    { return 0; }
  
  void fm_ce_create_state_model_config( t_model_type p_type, Id new_obj_id );
  virtual void create_state_model_config( t_model_type p_type, Id new_obj_id )
    { /* do nothing */ }

  DELETE_DOWN_DECL_SUPERTYPE()

protected:
  M_model ();
  virtual		~M_model ();

private:
    virtual void	render_graphical_element_data  (CE_model_glue*, Id) = 0;
    virtual void	render_unidentified_connector_data
			    (CE_model_glue*, Id, Id, Id);

    virtual t_boolean	audit_data (Description &p_err_msg) = 0;

    virtual t_boolean	shape_created
			    (Id* created_shape_id_ptr,
			    CE_model_glue::ShapeMeaning,
			    Id p_id_type,
			    Description &p_err_msg);
    virtual t_boolean	connector_created__shape_shape
			    (Id* created_shape_id_ptr,
			    Id shape1_id, Id shape2_id,
			    Description &p_err_msg);
    virtual t_boolean	connector_created__shape_connector
			    (Id shape_id, Id connector_id,
			    Description &p_err_msg);
    virtual t_boolean	connector_created__shape_dot__primary
			    (Id* created_shape_id_ptr,
			    Id shape_id,
			    Description &p_err_msg);
    virtual t_boolean	connector_created__shape_dot__secondary
			    (Id shape_id, Id connector_id,
			    Description &p_err_msg);

    virtual t_boolean	get_warning_msg_for_cut_shape
			    (Id cut_shape_id, t_boolean is_delete,
			    Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_shape
			    (Id cut_connector_id, Id shape1_id, Id shape2_id, t_boolean is_delete,
			    Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_connector
			    (Id cut_connector_id, Id shape_id, t_boolean is_delete,
			    Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_dot__primary
			    (Id cut_connector_id, Id shape_id, t_boolean is_delete,
			    Description &p_warning_msg);
    virtual t_boolean	get_warning_msg_for_cut_connector__shape_dot__secondary
			    (Id cut_connector_id, Id shape_id, t_boolean is_delete,
			    Description &p_warning_msg);

    virtual t_boolean	cut_shape
			    (Id cut_shape_id);
    virtual t_boolean	cut_connector__shape_shape
			    (Id cut_connector_id, Id shape1_id, Id shape2_id);
    virtual t_boolean	cut_connector__shape_connector
			    (Id cut_connector_id, Id shape_id);
    virtual t_boolean	cut_connector__shape_dot__primary
			    (Id cut_connector_id, Id shape_id);
    virtual t_boolean	cut_connector__shape_dot__secondary
			    (Id cut_connector_id, Id shape_id);

    virtual t_boolean	copy_shape
			    (Id cut_shape_id);
    virtual t_boolean	copy_connector__shape_shape
			    (Id cut_connector_id, Id shape1_id, Id shape2_id);
    virtual t_boolean	copy_connector__shape_connector
			    (Id cut_connector_id, Id shape_id);
    virtual t_boolean	copy_connector__shape_dot__primary
			    (Id cut_connector_id, Id shape_id);
    virtual t_boolean	copy_connector__shape_dot__secondary
			    (Id cut_connector_id, Id shape_id);

    virtual Id paste_obj_shape(Object*);
    virtual Id paste_iobj_shape(D_cp_o_iobj*);
    virtual Id paste_state_shape(D_cp_state*);
    virtual Id paste_rel_connector(D_cp_r_rel*);
	virtual Id paste_trans_connector(D_cp_transition*, int);
    virtual void fix_ref_attrs(D_cp_r_rel*);
	virtual int query_num_events();

    virtual t_boolean	export_shape
			    (Id cut_shape_id, IE_export_sql * p_export_ptr);
    virtual t_boolean	export_connector__shape_shape
			    (Id cut_connector_id, IE_export_sql * p_export_ptr, Id shape1_id, Id shape2_id);
    virtual t_boolean	export_connector__shape_connector
			    (Id cut_connector_id, IE_export_sql * p_export_ptr, Id shape_id);
    virtual t_boolean	export_connector__shape_dot__primary
			    (Id cut_connector_id, IE_export_sql * p_export_ptr, Id shape_id);
    virtual t_boolean	export_connector__shape_dot__secondary
			    (Id cut_connector_id, IE_export_sql * p_export_ptr, Id shape_id);

    mc_dbms_relationship_1_1(M_model,persistent_glue_ptr,CE_persistent_glue,m_model_ptr,CE_persistent_glue*)persistent_glue_ptr;

};



#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
