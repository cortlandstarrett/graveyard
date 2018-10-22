/*========================================================================
 *
 * File:      $RCSfile: d_usrprp.hh,v $
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
#ifndef D_USER_PROPERTIES_HH
#define D_USER_PROPERTIES_HH

//
// FILE: D_user_properties.hh	AUTHOR: R. C. Morman    CREATION DATE: 3/6/93
//
// CONTENTS:
//
//	This file describes the C++ classes for a maintaining user
//	properties across invocations.
//
// REMARKS:
//



#include "u_typdef.hh"
#include "d_typdef.hh"

#include <u_desc.hh>
#include <u_string.hh>

#include "r_lang.hh"

class User_properties
{
public:
    static void		user_init ();
    static t_boolean	user_save ();

    static void		proj_init ();
    static t_boolean	proj_save ();


	// Printing Properties
	//
	static t_int	&print_output_medium () { return _print_output_medium; }
	static String	&print_file_name ()
				{ return _print_file_name; }
	static t_int	&print_rows () { return _print_rows; }
	static t_int	&print_columns () { return _print_columns; }
	static t_float	&paper_width () { return _paper_width; }
	static t_float	&paper_height () { return _paper_height; }
	static RL_Render_Language::t_paper_orientation
					&paper_orientation () { return _paper_orientation; }
	static RL_Render_Language::t_render_language
					&print_language () { return _print_language; }

    static String	&default_model_print_command ()
			    { return _default_model_print_command; }
    static String	&default_description_print_command ()
			    { return _default_description_print_command; }
	static String   &default_print_file_directory ()
				{ return _default_print_file_directory; }


    static t_int	&auto_obj_number ()	{ return _auto_obj_number; }
    static t_int	&auto_rel_number ()	{ return _auto_rel_number; }
    static t_int	&auto_sta_number ()	{ return _auto_sta_number; }
    static t_int	&auto_evt_number ()	{ return _auto_evt_number; }

	static Description	&default_font_type ()
				{ return _default_font_type; }
	static Description	&application_font ()
				{ return _application_font; }
    static t_int	normal_font_only ()	
                { if ( diagram_display_mode() == DISPLAY_MODE_UML ) 
                    return FALSE; 
                  else 
                    return _normal_font_only; }
    static void  set_normal_font_only (t_int p_normal_only)
                { _normal_font_only = p_normal_only; }

	static t_int	&unapplied_edits () { return _unapplied_edits; }
	static t_int	&parse_on_import () { return _parse_on_import; }

	static String	&project_properties_file ()
				{ return _project_properties_file; }
				
    static String   &default_template_file ()
                { return _default_template_file; }
 
 
	static t_int	&do_automatic_backup () { return _do_automatic_backup; }
	static t_int	&number_of_backups () { return _number_of_backups; }
	static String	&backup_directory ()
				{ return _backup_directory; }


	static t_int	&dd_bg_red () { return _dd_bg_red; }
	static t_int	&dd_bg_green () { return _dd_bg_green; }
	static t_int	&dd_bg_blue () { return _dd_bg_blue; }

	static t_int	&dd_fg_red () { return _dd_fg_red; }
	static t_int	&dd_fg_green () { return _dd_fg_green; }
	static t_int	&dd_fg_blue () { return _dd_fg_blue; }

	static t_int	&srm_bg_red () { return _srm_bg_red; }
	static t_int	&srm_bg_green () { return _srm_bg_green; }
	static t_int	&srm_bg_blue () { return _srm_bg_blue; }

	static t_int	&srm_fg_red () { return _srm_fg_red; }
	static t_int	&srm_fg_green () { return _srm_fg_green; }
	static t_int	&srm_fg_blue () { return _srm_fg_blue; }

	static t_int	&scm_bg_red () { return _scm_bg_red; }
	static t_int	&scm_bg_green () { return _scm_bg_green; }
	static t_int	&scm_bg_blue () { return _scm_bg_blue; }

	static t_int	&scm_fg_red () { return _scm_fg_red; }
	static t_int	&scm_fg_green () { return _scm_fg_green; }
	static t_int	&scm_fg_blue () { return _scm_fg_blue; }

	static t_int	&sam_bg_red () { return _sam_bg_red; }
	static t_int	&sam_bg_green () { return _sam_bg_green; }
	static t_int	&sam_bg_blue () { return _sam_bg_blue; }

	static t_int	&sam_fg_red () { return _sam_fg_red; }
	static t_int	&sam_fg_green () { return _sam_fg_green; }
	static t_int	&sam_fg_blue () { return _sam_fg_blue; }

	static t_int	&oim_bg_red () { return _oim_bg_red; }
	static t_int	&oim_bg_green () { return _oim_bg_green; }
	static t_int	&oim_bg_blue () { return _oim_bg_blue; }

	static t_int	&oim_fg_red () { return _oim_fg_red; }
	static t_int	&oim_fg_green () { return _oim_fg_green; }
	static t_int	&oim_fg_blue () { return _oim_fg_blue; }

	static t_int	&ocm_bg_red () { return _ocm_bg_red; }
	static t_int	&ocm_bg_green () { return _ocm_bg_green; }
	static t_int	&ocm_bg_blue () { return _ocm_bg_blue; }

	static t_int	&ocm_fg_red () { return _ocm_fg_red; }
	static t_int	&ocm_fg_green () { return _ocm_fg_green; }
	static t_int	&ocm_fg_blue () { return _ocm_fg_blue; }

	static t_int	&oam_bg_red () { return _oam_bg_red; }
	static t_int	&oam_bg_green () { return _oam_bg_green; }
	static t_int	&oam_bg_blue () { return _oam_bg_blue; }

	static t_int	&oam_fg_red () { return _oam_fg_red; }
	static t_int	&oam_fg_green () { return _oam_fg_green; }
	static t_int	&oam_fg_blue () { return _oam_fg_blue; }

	static t_int	&ism_bg_red () { return _ism_bg_red; }
	static t_int	&ism_bg_green () { return _ism_bg_green; }
	static t_int	&ism_bg_blue () { return _ism_bg_blue; }

	static t_int	&ism_fg_red () { return _ism_fg_red; }
	static t_int	&ism_fg_green () { return _ism_fg_green; }
	static t_int	&ism_fg_blue () { return _ism_fg_blue; }

	static t_int	&asm_bg_red () { return _asm_bg_red; }
	static t_int	&asm_bg_green () { return _asm_bg_green; }
	static t_int	&asm_bg_blue () { return _asm_bg_blue; }

	static t_int	&asm_fg_red () { return _asm_fg_red; }
	static t_int	&asm_fg_green () { return _asm_fg_green; }
	static t_int	&asm_fg_blue () { return _asm_fg_blue; }

	static t_int	&sub_bg_red () { return _sub_bg_red; }
	static t_int	&sub_bg_green () { return _sub_bg_green; }
	static t_int	&sub_bg_blue () { return _sub_bg_blue; }

	static t_int	&ee_bg_red () { return _ee_bg_red; }
	static t_int	&ee_bg_green () { return _ee_bg_green; }
	static t_int	&ee_bg_blue () { return _ee_bg_blue; }

	static t_int	&obj_bg_red () { return _obj_bg_red; }
	static t_int	&obj_bg_green () { return _obj_bg_green; }
	static t_int	&obj_bg_blue () { return _obj_bg_blue; }

	static t_int	&iobj_bg_red () { return _iobj_bg_red; }
	static t_int	&iobj_bg_green () { return _iobj_bg_green; }
	static t_int	&iobj_bg_blue () { return _iobj_bg_blue; }

	static t_int	&state_bg_red () { return _state_bg_red; }
	static t_int	&state_bg_green () { return _state_bg_green; }
	static t_int	&state_bg_blue () { return _state_bg_blue; }


	// The following properties are set from a centeralize project
	// properties file.


    static String	&prolog_filename_string ()
			    { return _prolog_filename_string; }
    static Description	&report_begin_string ()
			    { return _report_begin_string; }
    static Description	&report_title_before_string ()
			    { return _report_title_before_string; }
    static Description	&report_title_after_string ()
			    { return _report_title_after_string; }
    static Description	&section_title_before_string ()
			    { return _section_title_before_string; }
    static Description	&section_title_after_string ()
			    { return _section_title_after_string; }
    static Description	&prim_desc_number_before_string ()
			    { return _prim_desc_number_before_string; }
    static Description	&prim_desc_number_after_string ()
			    { return _prim_desc_number_after_string; }
    static Description	&prim_desc_title_before_string ()
			    { return _prim_desc_title_before_string; }
    static Description	&prim_desc_title_after_string ()
			    { return _prim_desc_title_after_string; }
    static Description	&sec_desc_title_before_string ()
			    { return _sec_desc_title_before_string; }
    static Description	&sec_desc_title_after_string ()
			    { return _sec_desc_title_after_string; }
    static Description	&description_header_before_string ()
			    { return _description_header_before_string; }
    static Description	&description_header_after_string ()
			    { return _description_header_after_string; }
    static Description	&description_body_before_string ()
			    { return _description_body_before_string; }
    static Description	&description_body_after_string ()
			    { return _description_body_after_string; }
    static Description	&description_newline_substitution ()
			    { return _description_newline_substitution; }
	static t_boolean &description_word_wrap ()
				{ return _description_word_wrap; }
    static Description	&report_end_string ()
			    { return _report_end_string; }
	static String	&format_type_name ()
				{ return _format_type_name; }
	static t_int	&default_format_type ()
				{ return _default_format_type; }
	static t_int	&number_of_format_types ()
				{ return _number_of_format_types; }
	static t_int	&currently_loaded_format_type ()
				{ return _currently_loaded_format_type; }

    static Description	&domain_description_template ()
			    { return _domain_description_template; }
    static Description	&data_type_description_template ()
			    { return _data_type_description_template; }
    static Description	&subsystem_description_template ()
			    { return _subsystem_description_template; }
    static Description	&external_entity_description_template ()
			    { return _external_entity_description_template; }
    static Description	&ext_ent_event_description_template ()
			    { return _ext_ent_event_description_template; }
    static Description	&ee_evt_data_description_template ()
			    { return _ee_evt_data_description_template; }
    static Description	&bridge_description_template ()
			    { return _bridge_description_template; }
    static Description	&object_description_template ()
			    { return _object_description_template; }
    static Description	&relationship_description_template ()
			    { return _relationship_description_template; }
    static Description	&attribute_description_template ()
			    { return _attribute_description_template; }
    static Description	&reference_description_template ()
			    { return _reference_description_template; }
    static Description	&transformer_description_template ()
			    { return _transformer_description_template; }
    static Description	&state_model_description_template ()
			    { return _state_model_description_template; }
    static Description	&event_description_template ()
			    { return _event_description_template; }
    static Description	&evt_data_description_template ()
			    { return _evt_data_description_template; }
    static Description	&action_description_template ()
			    { return _action_description_template; }
    static Description	&cant_happen_description_template ()
			    { return _cant_happen_description_template; }
    static Description	&event_ignored_description_template ()
			    { return _event_ignored_description_template; }
    static Description	&synch_service_description_template ()
			    { return _synch_service_description_template; }
    static Description	&enumerator_description_template ()
			    { return _enumerator_description_template; }

    static Description	&domain_description ()
			    { return _domain_description; }
    static Description	&data_type_description ()
			    { return _data_type_description; }
    static Description	&subsystem_description ()
			    { return _subsystem_description; }
    static Description	&external_entity_description ()
			    { return _external_entity_description; }
    static Description	&ext_ent_event_description ()
			    { return _ext_ent_event_description; }
    static Description	&ee_evt_data_description ()
			    { return _ee_evt_data_description; }
    static Description	&bridge_description ()
			    { return _bridge_description; }
    static Description	&object_description ()
			    { return _object_description; }
    static Description	&relationship_description ()
			    { return _relationship_description; }
    static Description	&attribute_description ()
			    { return _attribute_description; }
    static Description	&reference_description ()
			    { return _reference_description; }
    static Description	&transformer_description ()
			    { return _transformer_description; }
    static Description	&state_model_description ()
			    { return _state_model_description; }
    static Description	&event_description ()
			    { return _event_description; }
    static Description	&evt_data_description ()
			    { return _evt_data_description; }
    static Description	&action_description ()
			    { return _action_description; }
    static Description	&cant_happen_description ()
			    { return _cant_happen_description; }
    static Description	&event_ignored_description ()
			    { return _event_ignored_description; }
    static Description	&synch_service_description ()
			    { return _synch_service_description; }
    static Description	&enumerator_description ()
			    { return _enumerator_description; }


    static t_int	&audit_subsystem_names ()
				{ return _audit_subsystem_names; }
	static t_int	&audit_synch_service_names ()
				{ return _audit_synch_service_names; }
	static t_int	&audit_enumerator_names ()
				{ return _audit_enumerator_names; }
    static t_int	&audit_object_names ()
				{ return _audit_object_names; }
    static t_int	&audit_object_numbers ()
				{ return _audit_object_numbers; }
    static t_int	&audit_object_keyletters ()
				{ return _audit_object_keyletters; }
    static t_int	&audit_object_identifiers ()
				{ return _audit_object_identifiers; }
    static t_int	&audit_attribute_names ()
				{ return _audit_attribute_names; }
    static t_int	&audit_relationship_labels ()
				{ return _audit_relationship_labels; }
    static t_int	&audit_unformal_relationships ()
				{ return _audit_unformal_relationships; }
    static t_int	&audit_event_labels ()
				{ return _audit_event_labels; }
    static t_int	&audit_state_names ()
				{ return _audit_state_names; }
    static t_int	&audit_state_numbers ()
				{ return _audit_state_numbers; }
    static t_int	&audit_subsystem_desc ()
				{ return _audit_subsystem_desc; }
    static t_int	&audit_external_entity_desc ()
				{ return _audit_external_entity_desc; }
    static t_int	&audit_external_entity_event_desc ()
				{ return _audit_external_entity_event_desc; }
    static t_int	&audit_external_entity_event_data_desc ()
				{ return _audit_external_entity_event_data_desc; }
    static t_int	&audit_bridge_desc ()
				{ return _audit_bridge_desc; }
    static t_int	&audit_object_desc ()
				{ return _audit_object_desc; }
    static t_int	&audit_attribute_desc ()
				{ return _audit_attribute_desc; }
    static t_int	&audit_reference_desc ()
				{ return _audit_reference_desc; }
    static t_int	&audit_transformer_desc ()
				{ return _audit_transformer_desc; }
    static t_int	&audit_relationship_desc ()
				{ return _audit_relationship_desc; }
    static t_int	&audit_state_model_desc ()
				{ return _audit_state_model_desc; }
    static t_int	&audit_event_desc ()
				{ return _audit_event_desc; }
    static t_int	&audit_event_data_desc ()
				{ return _audit_event_data_desc; }
    static t_int	&audit_unparsed_actions ()
				{ return _audit_unparsed_actions; }
    static t_int	&audit_actions_with_errors ()
				{ return _audit_actions_with_errors; }
    static t_int	&audit_polymorphic_events ()
				{ return _audit_polymorphic_events; }
    static t_int	&audit_synch_service_desc ()
				{ return _audit_synch_service_desc; }
    static t_int	&audit_enumerator_desc ()
				{ return _audit_enumerator_desc; }
    static t_int	&audit_action_desc ()
				{ return _audit_action_desc; }
    static t_int	&audit_action_specifications ()
				{ return _audit_action_specifications; }
    static t_int	&audit_data_types ()
				{ return _audit_data_types; }
    static t_int	&audit_dangling_ids ()
				{ return _audit_dangling_ids; }
    // i2801.1.2 begin
    static t_int	&audit_same_data_rule ()
				{ return _audit_same_data_rule; }
    // i2801.1.2 end

    static t_int	&init_event_ignored ()
				{ return _init_event_ignored; }

    static e_diagram_display_mode	&diagram_display_mode ()
				{ return _diagram_display_mode; }
    static t_int	&init_parse_on_apply ()
				{ return _init_parse_on_apply; }


    static String	&sql_create_string ()
			    { return _sql_create_string; }
    static String	&sql_int_string ()
			    { return _sql_int_string; }
    static String	&sql_8_char_string ()
			    { return _sql_8_char_string; }
    static String	&sql_64_char_string ()
			    { return _sql_64_char_string; }
    static String	&sql_128_char_string ()
			    { return _sql_128_char_string; }
    static String	&sql_description_string ()
			    { return _sql_description_string; }


    static String	&ver_mgmt_cmds_directory ()
			    { return _ver_mgmt_cmds_directory; }

    static String	&notebook_model_defaults ()
			    { return _notebook_model_defaults; }
    static String	&notebook_text_defaults ()
			    { return _notebook_text_defaults; }
    static t_boolean	&notebook_use_print_zoom ()
			    { return _notebook_use_print_zoom; }
    static t_uint	&notebook_print_zoom_font_size ()
			    { return _notebook_print_zoom_font_size; }
    static t_uint	&display_zoom_font_size ()
			    { return _display_zoom_font_size; }
    
    //Model Verifier
    static int      recent_sim_workspace_actual_count ();
    static int      recent_sim_workspace_max_count ();
    static void     set_recent_sim_workspace_max_count (int cnt);
    static const String	&recent_sim_workspace (int index);
    static void     add_recent_sim_workspace (const String &fileName);

    //Model Builder
    static int      recent_ooa_workspace_actual_count ();
    static int      recent_ooa_workspace_max_count ();
    static void     set_recent_ooa_workspace_max_count (int cnt);
    static const String	&recent_ooa_workspace (int index);
    static void     add_recent_ooa_workspace (const String &fileName);


private:
	static t_int	_print_output_medium;
	static String	_print_file_name;
	static t_int	_print_rows;
	static t_int	_print_columns;
	static t_float	_paper_width;
	static t_float	_paper_height;
	static RL_Render_Language::t_paper_orientation	_paper_orientation;
	static RL_Render_Language::t_render_language	_print_language;

    static String	_default_model_print_command;
    static String	_default_description_print_command;
    static String	_default_print_file_directory;


    static t_int	_auto_obj_number;
    static t_int	_auto_rel_number;	
    static t_int	_auto_sta_number;
    static t_int	_auto_evt_number;


	static Description	_default_font_type;
	static Description	_application_font;
    static t_int	_normal_font_only;


	static t_int	_unapplied_edits;
	static t_int	_parse_on_import;


	static String	_project_properties_file;
	
    static String   _default_template_file;
    static String   *default_template_file_bogey; //since this changes per installation it must be constructed at run time


	static t_int	_do_automatic_backup;
	static t_int	_number_of_backups;
	static String	_backup_directory;


	static t_int	_dd_bg_red;
	static t_int	_dd_bg_green;
	static t_int	_dd_bg_blue;

	static t_int	_dd_fg_red;
	static t_int	_dd_fg_green;
	static t_int	_dd_fg_blue;

	static t_int	_srm_bg_red;
	static t_int	_srm_bg_green;
	static t_int	_srm_bg_blue;

	static t_int	_srm_fg_red;
	static t_int	_srm_fg_green;
	static t_int	_srm_fg_blue;

	static t_int	_scm_bg_red;
	static t_int	_scm_bg_green;
	static t_int	_scm_bg_blue;

	static t_int	_scm_fg_red;
	static t_int	_scm_fg_green;
	static t_int	_scm_fg_blue;

	static t_int	_sam_bg_red;
	static t_int	_sam_bg_green;
	static t_int	_sam_bg_blue;

	static t_int	_sam_fg_red;
	static t_int	_sam_fg_green;
	static t_int	_sam_fg_blue;

	static t_int	_oim_bg_red;
	static t_int	_oim_bg_green;
	static t_int	_oim_bg_blue;

	static t_int	_oim_fg_red;
	static t_int	_oim_fg_green;
	static t_int	_oim_fg_blue;

	static t_int	_ocm_bg_red;
	static t_int	_ocm_bg_green;
	static t_int	_ocm_bg_blue;

	static t_int	_ocm_fg_red;
	static t_int	_ocm_fg_green;
	static t_int	_ocm_fg_blue;

	static t_int	_oam_bg_red;
	static t_int	_oam_bg_green;
	static t_int	_oam_bg_blue;

	static t_int	_oam_fg_red;
	static t_int	_oam_fg_green;
	static t_int	_oam_fg_blue;

	static t_int	_ism_bg_red;
	static t_int	_ism_bg_green;
	static t_int	_ism_bg_blue;

	static t_int	_ism_fg_red;
	static t_int	_ism_fg_green;
	static t_int	_ism_fg_blue;

	static t_int	_asm_bg_red;
	static t_int	_asm_bg_green;
	static t_int	_asm_bg_blue;

	static t_int	_asm_fg_red;
	static t_int	_asm_fg_green;
	static t_int	_asm_fg_blue;

	static t_int	_sub_bg_red;
	static t_int	_sub_bg_green;
	static t_int	_sub_bg_blue;

	static t_int	_ee_bg_red;
	static t_int	_ee_bg_green;
	static t_int	_ee_bg_blue;

	static t_int	_obj_bg_red;
	static t_int	_obj_bg_green;
	static t_int	_obj_bg_blue;

	static t_int	_iobj_bg_red;
	static t_int	_iobj_bg_green;
	static t_int	_iobj_bg_blue;

	static t_int	_state_bg_red;
	static t_int	_state_bg_green;
	static t_int	_state_bg_blue;


    static String	_prolog_filename_string;
    static Description	_report_begin_string;
    static Description	_report_title_before_string;
    static Description	_report_title_after_string;
    static Description	_section_title_before_string;
    static Description	_section_title_after_string;
    static Description	_prim_desc_number_before_string;
    static Description	_prim_desc_number_after_string;
    static Description	_prim_desc_title_before_string;
    static Description	_prim_desc_title_after_string;
    static Description	_sec_desc_title_before_string;
    static Description	_sec_desc_title_after_string;
    static Description	_description_header_before_string;
    static Description	_description_header_after_string;
    static Description	_description_body_before_string;
    static Description	_description_body_after_string;
    static Description	_description_newline_substitution;
	static t_boolean    _description_word_wrap;
    static Description	_report_end_string;
    static String	_format_type_name;
	static t_int	_default_format_type;
	static t_int	_number_of_format_types;
	static t_int	_currently_loaded_format_type;

    static Description	_domain_description_template;
    static Description	_data_type_description_template;
    static Description	_subsystem_description_template;
    static Description	_external_entity_description_template;
    static Description	_ext_ent_event_description_template;
    static Description	_ee_evt_data_description_template;
    static Description	_bridge_description_template;
    static Description	_object_description_template;
    static Description	_relationship_description_template;
    static Description	_attribute_description_template;
    static Description	_reference_description_template;
    static Description	_transformer_description_template;
	static Description	_state_model_description_template;
	static Description	_event_description_template;
	static Description	_evt_data_description_template;
	static Description	_action_description_template;
	static Description	_cant_happen_description_template;
	static Description	_event_ignored_description_template;
    static Description	_synch_service_description_template;
    static Description	_enumerator_description_template;

    static Description	_domain_description;
    static Description	_data_type_description;
    static Description	_subsystem_description;
    static Description	_external_entity_description;
    static Description	_ext_ent_event_description;
    static Description	_ee_evt_data_description;
    static Description	_bridge_description;
    static Description	_object_description;
    static Description	_attribute_description;
    static Description	_reference_description;
    static Description	_transformer_description;
    static Description	_relationship_description;
	static Description	_state_model_description;
	static Description	_event_description;
    static Description	_evt_data_description;
	static Description	_action_description;
	static Description	_cant_happen_description;
	static Description	_event_ignored_description;
    static Description	_synch_service_description;
    static Description	_enumerator_description;

    static t_int	_audit_subsystem_names;
    static t_int	_audit_object_names;
    static t_int	_audit_object_numbers;
    static t_int	_audit_object_keyletters;
    static t_int	_audit_object_identifiers;
    static t_int	_audit_attribute_names;
    static t_int	_audit_relationship_labels;
    static t_int	_audit_unformal_relationships;
    static t_int	_audit_event_labels;
    static t_int	_audit_state_names;
    static t_int	_audit_state_numbers;
    static t_int	_audit_subsystem_desc;
    static t_int	_audit_external_entity_desc;
    static t_int	_audit_external_entity_event_desc;
    static t_int	_audit_external_entity_event_data_desc;
    static t_int	_audit_action_specifications;
    static t_int	_audit_bridge_desc;
    static t_int	_audit_object_desc;
    static t_int	_audit_attribute_desc;
    static t_int	_audit_reference_desc;
    static t_int	_audit_transformer_desc;
    static t_int	_audit_relationship_desc;
    static t_int	_audit_state_model_desc;
    static t_int	_audit_event_desc;
    static t_int	_audit_event_data_desc;
    static t_int	_audit_unparsed_actions;
    static t_int	_audit_actions_with_errors;
    static t_int	_audit_polymorphic_events;
	static t_int	_audit_synch_service_names;
	static t_int	_audit_synch_service_desc;
    static t_int	_audit_action_desc;
	static t_int	_audit_enumerator_desc;
	static t_int	_audit_enumerator_names;
    static t_int    _audit_data_types;
    static t_int    _audit_dangling_ids;
    static t_int    _audit_same_data_rule;    // i2801.1.2 added

    static String	_sql_create_string;
    static String	_sql_int_string;
    static String	_sql_8_char_string;
    static String	_sql_64_char_string;
    static String	_sql_128_char_string;
    static String	_sql_description_string;

    static String	_ver_mgmt_cmds_directory;

	static String   _notebook_model_defaults;
    static String	_notebook_text_defaults;
    static t_boolean _notebook_use_print_zoom;
    static t_uint   _notebook_print_zoom_font_size;
    static t_uint   _display_zoom_font_size;

    static t_int	_init_event_ignored;
    static e_diagram_display_mode	_diagram_display_mode;
    static t_int	_init_parse_on_apply;

    static t_int	_recent_ooa_workspace_max_count;
    static t_int	_recent_sim_workspace_max_count;
    static t_int	_recent_ooa_workspace_actual_count;
    static t_int	_recent_sim_workspace_actual_count;


	static void		init_description_formats_to_default ();
};

class Description_Format
{
public:
			Description_Format ();
	virtual	~Description_Format ();

	static Description_Format * get_first_desc_format_ptr ()
				{ return first_desc_format_ptr; }
	static void	set_first_desc_format_ptr (Description_Format * p_desc_form_ptr)
				{ first_desc_format_ptr = p_desc_form_ptr; }

    String	&prolog_filename_string ()
			    { return _prolog_filename_string; }
    Description	&report_begin_string ()
			    { return _report_begin_string; }
    Description	get_report_begin_string () const
			    { return _report_begin_string; }
    Description	&report_title_before_string ()
			    { return _report_title_before_string; }
    Description	&report_title_after_string ()
			    { return _report_title_after_string; }
    Description	&section_title_before_string ()
			    { return _section_title_before_string; }
    Description	&section_title_after_string ()
			    { return _section_title_after_string; }
    Description	&prim_desc_number_before_string ()
			    { return _prim_desc_number_before_string; }
    Description	&prim_desc_number_after_string ()
			    { return _prim_desc_number_after_string; }
    Description	&prim_desc_title_before_string ()
			    { return _prim_desc_title_before_string; }
    Description	&prim_desc_title_after_string ()
			    { return _prim_desc_title_after_string; }
    Description	&sec_desc_title_before_string ()
			    { return _sec_desc_title_before_string; }
    Description	&sec_desc_title_after_string ()
			    { return _sec_desc_title_after_string; }
    Description	&description_header_before_string ()
			    { return _description_header_before_string; }
    Description	&description_header_after_string ()
			    { return _description_header_after_string; }
    Description	&description_body_before_string ()
			    { return _description_body_before_string; }
    Description	&description_body_after_string ()
			    { return _description_body_after_string; }
    Description	&description_newline_substitution ()
			    { return _description_newline_substitution; }
    Description	&report_end_string ()
			    { return _report_end_string; }
	String	&format_type_name ()
				{ return _format_type_name; }

	t_boolean word_wrap ()
				{ return _word_wrap_description; }
	void set_word_wrap ( t_boolean p_word_wrap )
				{ _word_wrap_description = p_word_wrap; }
								  
	Description_Format * get_next_desc_format_ptr ()
				{ return next_desc_format_ptr; }
	void	set_next_desc_format_ptr (Description_Format * p_desc_form_ptr)
				{ next_desc_format_ptr = p_desc_form_ptr; }

private:
	static Description_Format *		first_desc_format_ptr;

    String	_prolog_filename_string;
    Description	_report_begin_string;
    Description	_report_title_before_string;
    Description	_report_title_after_string;
    Description	_section_title_before_string;
    Description	_section_title_after_string;
    Description	_prim_desc_number_before_string;
    Description	_prim_desc_number_after_string;
    Description	_prim_desc_title_before_string;
    Description	_prim_desc_title_after_string;
    Description	_sec_desc_title_before_string;
    Description	_sec_desc_title_after_string;
    Description	_description_header_before_string;
    Description	_description_header_after_string;
    Description	_description_body_before_string;
    Description	_description_body_after_string;
    Description	_description_newline_substitution;
    Description	_report_end_string;
    String	_format_type_name;
	t_boolean _word_wrap_description;

	Description_Format * next_desc_format_ptr;
};



#endif
