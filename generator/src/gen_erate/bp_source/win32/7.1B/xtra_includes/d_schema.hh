/*========================================================================
 *
 * File:      $RCSfile: d_schema.hh,v $
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

//
// FILE: schema.cc
//
// CONTENTS:
//
// 	This file contains the schema (ie - class definitions) used by the
// 	MC_DBMS application. When a user MC_DBMS uses the Library Interface (LI) as
//	opposed to Data Manipulation Language (DML), all classes declared by
//	the application must appear in this file, in addition to being in
//	their normal header file.
//
// REMARKS:
//
// 	Also note that the "dummy" function is not called from anywhere; this
// 	file must simply be compiled via the "ss7_schema_standin" directive
// 	in the corresponding Makefile.
//



//  From common
//
#include "d_invoct.hh"
#include "d_domain.hh"
#include "d_vertag.hh"
#include "d_itratr.hh"
#include "d_dattyp.hh"


//  From dd_srm_scm_sam
//
#include "d_dd_sam.hh"
#include "d_subsys.hh"
#include "d_ddasnr.hh"
#include "d_dd_ver.hh"

//  From im_ocm_oam
//
#include "d_im_oam.hh"
#include "d_entity.hh"
#include "d_object.hh"
#include "d_attr.hh"
#include "d_nbattr.hh"
#include "d_dbattr.hh"
#include "d_rattr.hh"
#include "d_ario.hh"
#include "d_oid.hh"
#include "d_oida.hh"
#include "d_rel.hh"
#include "d_smprel.hh"
#include "d_assrel.hh"
#include "d_inhrel.hh"
#include "d_cmprel.hh"
#include "d_tfmr.hh"
#include "d_bridge.hh"
#include "d_parm.hh"
#include "d_synchs.hh"
#include "d_ss.hh"
#include "d_imasnr.hh"
#include "d_im_ver.hh"


//  From sm_spt_pm
//
#include "d_action.hh"
#include "d_acthom.hh"
#include "d_cnthap.hh"
#include "d_crttns.hh"
#include "d_evtign.hh"
#include "d_mealhm.hh"
#include "d_mealsm.hh"
#include "d_moorhm.hh"
#include "d_moorsm.hh"
#include "d_nwsttn.hh"
#include "d_nevttn.hh"
#include "d_sm.hh"
#include "d_smevt.hh"
#include "d_smedi.hh"
#include "d_suppdt.hh"
#include "d_suppdi.hh"
#include "d_sm_pm.hh"
#include "d_smsta.hh"
#include "d_seme.hh"
#include "d_tns.hh"
#include "d_drvpth.hh"
#include "d_sevt.hh"
#include "d_levt.hh"
#include "d_pevt.hh"
#include "d_nlevt.hh"
#include "d_exespec.hh"
#include "d_smasnr.hh"
#include "d_sm_ver.hh"

#include "d_cp_im.hh"
#include "d_cp_sm.hh"

#include "m_ce/m_gphelm.hh"

//  From common
//

// from D_invocation.hh
MC_DBMS_MARK_SCHEMA_TYPE( Invocation );

// from D_domain.hh
MC_DBMS_MARK_SCHEMA_TYPE( Domain );

// from D_version_tag.hh
MC_DBMS_MARK_SCHEMA_TYPE( D_version_tag );

// from D_iterators.hh
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_data_type> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_enumerator> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_synchronous_service> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_synchronous_service_parm> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_external_entity> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_subsys> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_bridge> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_bridge_parm> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_external_entity_in_model> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_external_entity_event_data_item> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_external_entity_event> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<Object> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<Relationship> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_communication_path> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_access_path> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_transformer> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_transformer_parm> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<Imported_object> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<Object_in_relationship> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<Object_as_subtype> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_sm_event_data_item> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_supplemental_data> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_sm_state> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<D_sm_event> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<M_Graphical_Element> );
MC_DBMS_MARK_SCHEMA_TYPE( D_ordered_element<Object_as_supertype> );

// from D_data_type.hh
MC_DBMS_MARK_SCHEMA_TYPE( D_data_type );
MC_DBMS_MARK_SCHEMA_TYPE( D_core_data_type );
MC_DBMS_MARK_SCHEMA_TYPE( D_user_data_type );
MC_DBMS_MARK_SCHEMA_TYPE( D_enum_data_type );
MC_DBMS_MARK_SCHEMA_TYPE( D_enumerator );



//  From dd_im
//

// from D_dd_srm_scm_sam.hh
MC_DBMS_MARK_SCHEMA_TYPE( D_dd_srm_scm_sam );
MC_DBMS_MARK_SCHEMA_TYPE( D_dd_assigners );
MC_DBMS_MARK_SCHEMA_TYPE( D_dd_version_info );

// from D_subsystem.hh
MC_DBMS_MARK_SCHEMA_TYPE( D_subsys );
MC_DBMS_MARK_SCHEMA_TYPE( Subsystem );

// from D_im_ocm_oam.hh
MC_DBMS_MARK_SCHEMA_TYPE( D_im_ocm_oam );
MC_DBMS_MARK_SCHEMA_TYPE( D_im_assigners );
MC_DBMS_MARK_SCHEMA_TYPE( D_im_version_info );

// from D_entity.hh
MC_DBMS_MARK_SCHEMA_TYPE( D_entity );
MC_DBMS_MARK_SCHEMA_TYPE( D_access_path );
MC_DBMS_MARK_SCHEMA_TYPE( D_communication_path );
MC_DBMS_MARK_SCHEMA_TYPE( D_external_entity );
MC_DBMS_MARK_SCHEMA_TYPE( D_external_entity_in_model );
MC_DBMS_MARK_SCHEMA_TYPE( D_external_entity_event );
MC_DBMS_MARK_SCHEMA_TYPE( D_external_entity_event_data_item );
MC_DBMS_MARK_SCHEMA_TYPE( D_external_entity_event_data );

// from D_object.hh
MC_DBMS_MARK_SCHEMA_TYPE( Object );
MC_DBMS_MARK_SCHEMA_TYPE( Imported_object );
MC_DBMS_MARK_SCHEMA_TYPE( Attribute );
MC_DBMS_MARK_SCHEMA_TYPE( Object_identifier );
MC_DBMS_MARK_SCHEMA_TYPE( Object_identifier_attribute );
MC_DBMS_MARK_SCHEMA_TYPE( Base_attribute );
MC_DBMS_MARK_SCHEMA_TYPE( Referential_attribute );
MC_DBMS_MARK_SCHEMA_TYPE( Derived_base_attribute );
MC_DBMS_MARK_SCHEMA_TYPE( New_base_attribute );
MC_DBMS_MARK_SCHEMA_TYPE( Attr_ref_in_object );

// from D_relationship.hh
MC_DBMS_MARK_SCHEMA_TYPE( Relationship );
MC_DBMS_MARK_SCHEMA_TYPE( Object_in_relationship );
MC_DBMS_MARK_SCHEMA_TYPE( Object_in_non_inh_relationship );
MC_DBMS_MARK_SCHEMA_TYPE( Object_referred_to );
MC_DBMS_MARK_SCHEMA_TYPE( Object_referring );
MC_DBMS_MARK_SCHEMA_TYPE( Referred_to_ident_attr );

// from D_simple_relationship.hh
MC_DBMS_MARK_SCHEMA_TYPE( Simple_relationship );
MC_DBMS_MARK_SCHEMA_TYPE( Object_as_simple_participant );
MC_DBMS_MARK_SCHEMA_TYPE( Object_as_simple_formalizer );

// from D_composition_relationship.hh
MC_DBMS_MARK_SCHEMA_TYPE( Composition_relationship );
MC_DBMS_MARK_SCHEMA_TYPE( Object_as_comp_one_end );
MC_DBMS_MARK_SCHEMA_TYPE( Object_as_comp_other_end );

// from D_associative_relationship.hh
MC_DBMS_MARK_SCHEMA_TYPE( Associative_relationship );
MC_DBMS_MARK_SCHEMA_TYPE( Object_as_assoc_one_side );
MC_DBMS_MARK_SCHEMA_TYPE( Object_as_assoc_other_side );
MC_DBMS_MARK_SCHEMA_TYPE( Object_as_associator );

// from D_inheritance_relationship.hh
MC_DBMS_MARK_SCHEMA_TYPE( Inheritance_relationship );
MC_DBMS_MARK_SCHEMA_TYPE( Object_as_supertype );
MC_DBMS_MARK_SCHEMA_TYPE( Object_as_subtype );

// from D_transformer.hh
MC_DBMS_MARK_SCHEMA_TYPE( D_transformer );

// from D_bridge.hh
MC_DBMS_MARK_SCHEMA_TYPE( D_bridge );

// from D_synchs.hh
MC_DBMS_MARK_SCHEMA_TYPE( D_synchronous_service );

// from D_parameter.hh
MC_DBMS_MARK_SCHEMA_TYPE( D_parameter );
MC_DBMS_MARK_SCHEMA_TYPE( D_transformer_parm );
MC_DBMS_MARK_SCHEMA_TYPE( D_bridge_parm );
MC_DBMS_MARK_SCHEMA_TYPE( D_synchronous_service_parm );



//  From sm_pm
//

MC_DBMS_MARK_SCHEMA_TYPE( D_action );
MC_DBMS_MARK_SCHEMA_TYPE( D_action_home );
MC_DBMS_MARK_SCHEMA_TYPE( D_cant_happen );
MC_DBMS_MARK_SCHEMA_TYPE( D_creation_transition );
MC_DBMS_MARK_SCHEMA_TYPE( D_event_ignored );
MC_DBMS_MARK_SCHEMA_TYPE( D_mealy_action_home );
MC_DBMS_MARK_SCHEMA_TYPE( D_mealy_sm );
MC_DBMS_MARK_SCHEMA_TYPE( D_moore_action_home );
MC_DBMS_MARK_SCHEMA_TYPE( D_moore_sm );
MC_DBMS_MARK_SCHEMA_TYPE( D_new_state_transition );
MC_DBMS_MARK_SCHEMA_TYPE( D_no_event_transition );
MC_DBMS_MARK_SCHEMA_TYPE( D_sm );
MC_DBMS_MARK_SCHEMA_TYPE( D_sm_event );
MC_DBMS_MARK_SCHEMA_TYPE( D_sm_version_info );
MC_DBMS_MARK_SCHEMA_TYPE( D_sm_event_data_item );
MC_DBMS_MARK_SCHEMA_TYPE( D_supplemental_data );
MC_DBMS_MARK_SCHEMA_TYPE( D_supplemental_data_item );
MC_DBMS_MARK_SCHEMA_TYPE( D_sm_spt_pm );
MC_DBMS_MARK_SCHEMA_TYPE( D_sm_state );
MC_DBMS_MARK_SCHEMA_TYPE( D_state_event_matrix_entry );
MC_DBMS_MARK_SCHEMA_TYPE( D_transition );
MC_DBMS_MARK_SCHEMA_TYPE( D_derived_communication_path );
MC_DBMS_MARK_SCHEMA_TYPE( D_derived_access_path );
MC_DBMS_MARK_SCHEMA_TYPE( D_derived_path_item );
MC_DBMS_MARK_SCHEMA_TYPE( D_sm_assigners );
MC_DBMS_MARK_SCHEMA_TYPE( D_sm_version_info );

MC_DBMS_MARK_SCHEMA_TYPE( D_sem_event );
MC_DBMS_MARK_SCHEMA_TYPE( D_polymorphic_event );
MC_DBMS_MARK_SCHEMA_TYPE( D_local_event );
MC_DBMS_MARK_SCHEMA_TYPE( D_non_local_event );

MC_DBMS_MARK_SCHEMA_TYPE( D_execution_spec );

MC_DBMS_MARK_SCHEMA_TYPE( D_cp_o_obj );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_o_attr );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_o_iobj );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_o_rattr );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_o_ref );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_o_rtida );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_rel );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_oir );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_rto );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_rgo );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_simp );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_part );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_form );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_assoc );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_aone );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_aoth );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_assr );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_subsup );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_super );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_sub );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_comp );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_cone );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_coth );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_r_oinir );

MC_DBMS_MARK_SCHEMA_TYPE( D_cp_sm_spt_pm );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_event_data_item );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_supplemental_data );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_supplemental_data_item );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_state );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_event );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_event_ignored );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_cant_happen );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_state_event_matrix_entry );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_new_state_transition );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_no_event_transition );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_creation_transition );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_transition );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_moore_action_home );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_mealy_action_home );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_action_home );
MC_DBMS_MARK_SCHEMA_TYPE( D_cp_action );

MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Attr_ref_in_object*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Attribute*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_access_path*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_action*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_bridge*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_bridge_parm*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_communication_path*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_action*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_action_home*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_cant_happen*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_creation_transition*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_event*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_event_data_item*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_event_ignored*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_mealy_action_home*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_moore_action_home*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_new_state_transition*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_no_event_transition*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_o_attr*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_o_iobj*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_o_obj*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_o_rattr*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_o_ref*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_o_rtida*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_aone*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_aoth*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_assoc*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_assr*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_comp*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_cone*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_coth*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_form*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_oinir*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_oir*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_part*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_rel*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_rgo*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_rto*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_simp*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_sub*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_subsup*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_r_super*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_sm_spt_pm*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_state*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_state_event_matrix_entry*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_supplemental_data*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_supplemental_data_item*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_cp_transition*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_data_type*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Collection<D_dd_srm_scm_sam*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_dd_srm_scm_sam*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_derived_access_path*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_derived_communication_path*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_derived_path_item*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_enumerator*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_external_entity*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_external_entity_event*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_external_entity_event_data_item*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_external_entity_in_model*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_im_ocm_oam*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_mealy_action_home*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_moore_action_home*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_non_local_event*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_sm_event*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_sm_event_data_item*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_sm_spt_pm*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_sm_state*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_sm_version_info*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_subsys*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_supplemental_data*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_synchronous_service*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_synchronous_service_parm*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_transformer*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_transformer_parm*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_transition*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<D_user_data_type*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Description*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Domain_reference*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Id*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Imported_object*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Object*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Object_as_subtype*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Object_as_supertype*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Object_identifier*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Object_in_relationship*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Referred_to_ident_attr*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_List<Relationship*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<Attr_ref_in_object*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<D_external_entity_event_data*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<D_no_event_transition*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<D_state_event_matrix_entry*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<D_supplemental_data_item*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<D_transition*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<Object_identifier_attribute*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<Object_in_relationship*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<Object_referred_to*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<Referred_to_ident_attr*> );
// From the action directory
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Bag< Object*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Bag< Relationship*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Bag< D_sm_event*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Bag< D_external_entity*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Bag< D_external_entity_event*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Bag< D_sm_event_data_item*> );
// From the gen_sim directory
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set <D_synchronous_service*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<D_external_entity*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<D_external_entity_event*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<D_sm_event*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<Object*> );
MC_DBMS_MARK_SCHEMA_TYPE( mc_dbms_Set<Relationship*> );



//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
