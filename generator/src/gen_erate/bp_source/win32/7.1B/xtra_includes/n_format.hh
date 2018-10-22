/*========================================================================
 *
 * File:      $RCSfile: n_format.hh,v $
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
#ifndef N_FORMAT_NOTEBOOK_HH
#define N_FORMAT_NOTEBOOK_HH



#include <vchar.h>

#include <u_typdef.hh>


#define LINE_SIZE	70
#define NUM_SIZE	16



class D_dd_srm_scm_sam;
class D_data_type;
class Domain;
class D_subsys;
class Object;
class Attribute;
class Attr_ref_in_object;
class D_transformer;
class Relationship;
class D_sm_spt_pm;
class D_action;
class D_external_entity;
class D_external_entity_event;
class D_external_entity_event_data_item;
class D_bridge;
class D_sm_event;
class D_sm_event_data_item;
class D_cant_happen;
class D_event_ignored;
class D_synchronous_service;
class Description;

class RM_file;



class N_format_descriptions
{
public:
			N_format_descriptions (RM_file *);
    virtual		~N_format_descriptions ();


    t_boolean		format_prolog_file ();
    void		format_report_title (Domain*);
    void		format_obj_desc_section_title (D_subsys*);
    void		format_obj_attr_desc_section_title (D_subsys*);
	void		format_state_model_section_header (D_sm_spt_pm*, t_boolean);
    void		format_rel_desc_section_title (D_subsys*);
	void		format_external_entity_section_title (Domain*);
    void		format_event_list_section_title (Domain*);
	void		format_data_type_section_title (Domain*);
	void		format_synch_service_section_title (Domain*, D_synchronous_service* );

    void		format_domain_description (D_dd_srm_scm_sam*, t_boolean);
    void		format_data_type_description (D_data_type*, t_boolean, t_boolean);
    void		format_synch_service_description (D_synchronous_service*, t_boolean, t_boolean);
    void		format_subsystem_description (D_subsys*, t_boolean p_output_descrip);
    void		format_object_description (Object*, t_boolean p_output_descrip);
    void		format_attribute_description (Attribute*, t_boolean, t_boolean, t_boolean);
    void		format_reference_description (Attr_ref_in_object*, t_boolean p_output_descrip);
    void		format_transformer_description (D_transformer*, t_boolean, t_boolean, t_boolean);
	void		format_state_model_description (D_sm_spt_pm*, t_boolean p_output_descrip);
	void		format_action_description (D_action*, t_boolean, t_boolean);
	void		format_event_description (D_sm_event*, t_boolean p_output_descrip);
	void		format_event_data_description (D_sm_event_data_item*, t_boolean p_output_descrip);
    void		format_relationship_description (Relationship*, t_boolean p_output_descrip);
	void		format_external_entity_description (D_external_entity*, t_boolean p_output_descrip);
	void		format_ext_ent_event_description (D_external_entity_event*, t_boolean p_output_descrip);
	void		format_ext_ent_event_data_description (D_external_entity_event_data_item*, t_boolean p_output_descrip);
	void		format_bridge_description (D_bridge*, t_boolean, t_boolean, t_boolean);
	void		format_cant_happen_description (D_cant_happen*, t_boolean p_output_descrip);
	void		format_event_ignored_description (D_event_ignored*, t_boolean p_output_descrip);
    void		format_event_list (D_external_entity*);
    void		format_event_list (D_sm_spt_pm*);
	void		done_with_format ();



protected:



private:
    RM_file *	rm_file_ptr;

	void		output_formatted_description( const Description& p_desc );
    void		output_format_string (const vchar*);
    void		output_format_string (const char*);
};



#endif
