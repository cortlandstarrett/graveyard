/*========================================================================
 *
 * File:      $RCSfile: d_dataud.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:15 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef D_DATA_AUDIT_HH
#define D_DATA_AUDIT_HH

//
// FILE: D_data_audit.hh	AUTHOR: R. C. Morman    CREATION DATE: 9/14/93
//
// CONTENTS:
//
//	This file contains functions that will audit the uderlining OOA data.
//
// REMARKS:
//



#include "u_typdef.hh"

#include <u_string.hh>
#include <u_desc.hh>

class D_dd_srm_scm_sam;
class D_im_ocm_oam;
class D_sm_spt_pm;
class D_synchronous_service;
class D_subsys;
class Object;
class Attribute;
class Relationship;
class D_sm_event;
class D_sm_event_data_item;
class D_sm_state;
class D_external_entity;
class D_external_entity_event;
class D_external_entity_event_data_item;
class D_enum_data_type;

class RM_file;

class Data_audit
{
public:
  Data_audit ();
  ~Data_audit ();

  static String	get_audit_file_name();
  static void		audit_data (D_dd_srm_scm_sam *, String &);
  static void		audit_data (D_im_ocm_oam *, String &);
  static void		audit_data (D_sm_spt_pm *, String &);
  static void		audit_dd (D_dd_srm_scm_sam *, String &);
  static void		audit_im (D_im_ocm_oam *, String &);
  static void		audit_sm (D_sm_spt_pm *, String &);

private:

  void		collect_subsystem_data (D_dd_srm_scm_sam *);
  void		collect_enumerator_data (D_dd_srm_scm_sam *);
  void		collect_relationship_data (D_dd_srm_scm_sam *);
  void		collect_relationship_data (D_im_ocm_oam *);
  void		collect_event_data (D_dd_srm_scm_sam *);
  void		collect_event_data (D_im_ocm_oam *);
  void		collect_event_data (D_sm_spt_pm *);
  void		collect_state_data (D_sm_spt_pm *);
  void		collect_ext_ent_data (D_dd_srm_scm_sam *);
  void		collect_ee_event_data (D_dd_srm_scm_sam *);
  void		collect_synch_service_data (D_dd_srm_scm_sam *);
  void		collect_object_data (D_dd_srm_scm_sam *);
  void		collect_object_data (D_im_ocm_oam *);

  void		audit_subsystem_data ();
  void		audit_object_data (t_boolean p_object_only);
  void		audit_relationship_data ();
  void		audit_event_data ();
  void		audit_polymorphic_event_data (D_sm_event*);
  void		audit_state_data ();
  void		audit_state_model_data (D_sm_spt_pm *);

  void      output_undef_datatype_errors();
  void      output_dangling_ids_errors();
  void		output_subsystem_name_errors();
  void		output_subsystem_desc_errors();
  void		output_enumerator_name_errors();
  void		output_enumerator_desc_errors();
  void		output_attribute_name_errors();
  void		output_relationship_number_errors();
  void		output_relationship_formalized_errors();
  void		output_relationship_desc_errors();
  void		output_event_label_errors();
  void		output_polymorphic_event_errors();
  void		output_event_desc_errors();
  void		output_event_data_desc_errors();
  void		output_state_name_errors();
  void		output_state_number_errors();
  void		output_state_model_desc_errors();
  void		output_external_entity_desc_errors();
  void		output_ext_ent_event_desc_errors();
  void		output_ext_ent_event_data_desc_errors();
  void		output_bridge_desc_errors();
  void		output_attribute_desc_errors();
  void		output_reference_desc_errors();
  void		output_action_spec_errors();
  void		output_action_desc_errors();
  void		output_unparsed_action_errors();
  void		output_action_with_errors_errors();
  void		output_action_with_undefines_errors();
  void		output_synch_service_name_errors();
  void		output_synch_service_desc_errors();
  void		output_object_name_errors();
  void		output_object_number_errors();
  void		output_object_keyletter_errors();
  void		output_object_identifier_errors();
  void		output_object_desc_errors();
  void		output_transformer_desc_errors();
  void      output_same_data_rule_errors();  // i2801.3.1 added

  mc_dbms_List<D_subsys *>					*subsystem_collection;
  mc_dbms_List<D_enum_data_type*>			*enumerator_collection;
  mc_dbms_List<Relationship *>				*relationship_collection;
  mc_dbms_List<D_sm_event *>					*event_collection;
  mc_dbms_List<D_sm_state*>					*state_collection;
  mc_dbms_List<D_external_entity_event *>	*ext_evt_collection;
  mc_dbms_List<D_external_entity *>			*ext_ent_collection;
  mc_dbms_List<D_synchronous_service*>		*synch_service_collection;
  mc_dbms_List<Object *>						*object_collection;


  static RM_file *		audit_results;

  static t_boolean		errors_found;


  // Following are the names the entities are known by (SM vs. UML mode)
  String	synch_service_title;
  String	object_title;
  String	transformer_title;
  String    assigner_title;

  String	synch_service_all_caps_title;
  String	object_all_caps_title;
  String	transformer_all_caps_title;
  static String assigner_all_caps_title;


  String	subsystem_names_title;
  String	subsystem_desc_title;

  String	enumerator_names_title;
  String	enumerator_desc_title;

  String	attribute_names_title;

  String	relationship_numbers_title;
  String	relationship_formalized_title;
  String	relationship_desc_title;

  String	event_labels_title;
  String	polymorphic_events_title;
  String	event_desc_title;
  String	event_data_desc_title;

  String	state_names_title;
  String	state_numbers_title;
  String	state_model_desc_title;

  String	external_entity_desc_title;
  String	ext_ent_event_desc_title;
  String	ext_ent_event_data_desc_title;

  String	bridge_desc_title;

  String	attribute_desc_title;
  String	reference_desc_title;

  String	action_spec_title;
  String	action_desc_title;
  String	unparsed_actions_title;
  String	actions_with_errors_title;
  String	actions_with_undefines_title;

  String	synch_service_names_title;
  String	synch_service_desc_title;

  String	object_names_title;
  String	object_numbers_title;
  String	object_keyletters_title;
  String	object_identifiers_title;
  String	object_desc_title;

  String	transformer_desc_title;

  String    undef_datatypes_title;
  String    dangling_ids_title;

  String    same_data_rule_title;  // i2801.3.1 added

  mc_dbms_List<Description *> *subsystem_names;
  mc_dbms_List<Description *> *subsystem_desc;

  mc_dbms_List<Description *> *enumerator_names;
  mc_dbms_List<Description *> *enumerator_desc;

  mc_dbms_List<Description *> *attribute_names;

  mc_dbms_List<Description *> *relationship_numbers;
  mc_dbms_List<Description *> *relationship_formalized;
  mc_dbms_List<Description *> *relationship_desc;

  mc_dbms_List<Description *> *event_labels;
  mc_dbms_List<Description *> *polymorphic_events;
  mc_dbms_List<Description *> *event_desc;
  mc_dbms_List<Description *> *event_data_desc;

  mc_dbms_List<Description *> *state_names;
  mc_dbms_List<Description *> *state_numbers;
  mc_dbms_List<Description *> *state_model_desc;

  mc_dbms_List<Description *> *external_entity_desc;
  mc_dbms_List<Description *> *ext_ent_event_desc;
  mc_dbms_List<Description *> *ext_ent_event_data_desc;

  mc_dbms_List<Description *> *bridge_desc;

  mc_dbms_List<Description *> *attribute_desc;
  mc_dbms_List<Description *> *reference_desc;

  mc_dbms_List<Description *> *action_spec;
  mc_dbms_List<Description *> *action_desc;
  mc_dbms_List<Description *> *unparsed_actions;
  mc_dbms_List<Description *> *actions_with_errors;
  mc_dbms_List<Description *> *actions_with_undefines;

  mc_dbms_List<Description *> *synch_service_names;
  mc_dbms_List<Description *> *synch_service_desc;

  mc_dbms_List<Description *> *object_names;
  mc_dbms_List<Description *> *object_numbers;
  mc_dbms_List<Description *> *object_keyletters;
  mc_dbms_List<Description *> *object_identifiers;
  mc_dbms_List<Description *> *object_desc;

  mc_dbms_List<Description *> *transformer_desc;
  mc_dbms_List<Description *> *undef_datatypes;
  mc_dbms_List<Description *> *dangling_ids;

  mc_dbms_List<Description *> *same_data_rule;  // i2801.3.1 added

  t_boolean open_output_file (String & p_err_msg);
  String output_filename;
  
};


#endif
