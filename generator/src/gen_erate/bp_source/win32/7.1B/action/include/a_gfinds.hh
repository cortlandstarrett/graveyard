/*========================================================================
 *
 * File:      $RCSfile: a_gfinds.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:39 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>
#ifndef AL_GENERIC_FINDS_HH
#define AL_GENERIC_FINDS_HH

// AL_generic_finds.hh


// Classes we define in this header file

class AL_Generic_finds;

// Other classes we reference

class Domain;
class Object;
class Attribute;
class Relationship;
class Object_in_relationship;
class D_sm_event;
class D_sm_event_data_item;
class D_transformer;
class D_transformer_parm;
class D_synchronous_service;
class D_synchronous_service_parm;
class D_bridge;
class D_bridge_parm;
class D_data_type;
class D_core_data_type;
class D_enum_data_type;
class D_enumerator;
class D_external_entity;
class D_external_entity_event;
class D_external_entity_event_data_item;


class AL_Generic_finds
{
public:

	AL_Generic_finds();

	~AL_Generic_finds();

	// Generic find functions (collection variety).
	// IMPORTANT: The caller of these functions must delete the returned
	// collection pointer.

	static mc_dbms_Bag< Object * > * find_object_by_key_letters(
		Domain * p_domain_ptr, const vchar * p_object_key_letters );

	static mc_dbms_Bag< Relationship * > * find_relationship_by_number(
		Domain * p_domain_ptr, const char * p_rel_num );

	static mc_dbms_Bag< D_sm_event * > * find_sm_event_by_label(
		Domain * p_domain_ptr, const vchar * p_label );

	static mc_dbms_Bag< D_external_entity * > *
		find_external_entity_by_name( Domain * p_domain_ptr,
		const vchar * p_ee );

	static mc_dbms_Bag< D_external_entity * > *
		find_external_entity_by_key_letters( Domain * p_domain_ptr,
		const vchar * p_ee );

	static mc_dbms_Bag< D_external_entity_event * > *
		find_external_entity_event_by_label( Domain * p_domain_ptr,
		const vchar * p_label );

	// Collection finds not currently implemented

	static mc_dbms_Bag< D_sm_event_data_item * >
		find_sm_event_data_item_by_name( Domain * p_domain_ptr,
		const vchar * p_event_data_item_name );

	// Generic find functions (single instance variety)
 
	static D_external_entity *
		find_external_entity_by_id( const Domain * p_domain_ptr,
		const Id & p_id );

	static D_external_entity_event *
		find_external_entity_event_by_id( const Domain * p_domain_ptr,
		const Id & p_id );

	static D_external_entity_event_data_item *
		find_external_entity_event_data_item_by_id( const Domain * p_domain_ptr,
		const Id & p_id );

	static Object *
		find_object_by_id( const Domain * p_domain_ptr, const Id & p_id );

	static Attribute *
		find_attribute_by_id( const Domain * p_domain_ptr, const Id & p_id );

	static Relationship *
		find_relationship_by_id( const Domain * p_domain_ptr, const Id & p_id );

	static D_sm_event *
		find_sm_event_by_id( const Domain * p_domain_ptr, const Id & p_id );

	static D_sm_event_data_item *
		find_sm_event_data_item_by_id( const Domain * p_domain_ptr,
		const Id & p_id );

	static Object_in_relationship *
		find_object_in_relationship_by_id( const Domain * p_domain_ptr,
		const Id & p_id );

	static D_transformer *
		find_transformer_by_id( const Domain * p_domain_ptr, const Id & p_id );

	static D_transformer *
		find_transformer_by_name( const Domain * p_domain_ptr,
		const vchar * p_name );

	static D_synchronous_service *
		find_synch_service_by_id( const Domain * p_domain_ptr, const Id & p_id );

	static D_bridge *
		find_bridge_by_id( const Domain * p_domain_ptr, const Id & p_id );

	static D_bridge *
		find_bridge_by_name( const Domain * p_domain_ptr,
		const vchar * p_name );

	static D_transformer_parm *
		find_transformer_parm_by_id( const Domain * p_domain_ptr,
		const Id & p_id );

	static D_transformer_parm *
		find_transformer_parm_by_name( const Domain * p_domain_ptr,
		const vchar * p_name );

	static D_synchronous_service_parm *
		find_synch_service_parm_by_id( const Domain * p_domain_ptr,
		const Id & p_id );

	static D_bridge_parm *
		find_bridge_parm_by_id( const Domain * p_domain_ptr, const Id & p_id );

	static D_bridge_parm *
		find_bridge_parm_by_name( const Domain * p_domain_ptr,
		const vchar * p_name );

	static D_data_type *
		find_data_type_by_id( const Domain * p_domain_ptr, const Id & p_id );

	static D_core_data_type *
		find_core_data_type_by_id( const Domain * p_domain_ptr,
		const Id & p_id );

	static D_enumerator *
		find_enumerator_by_id( const Domain * p_domain_ptr,
		const Id & p_id );


	// Attribute field ids

	static const int OBJECT_KEY_LETTERS_FIELD;
	static const int RELATIONSHIP_NUMBER_FIELD;
	static const int EVENT_LABEL_FIELD;
	static const int SM_EVENT_DATA_ITEM_NAME_FIELD;
	static const int EE_EVENT_DATA_ITEM_NAME_FIELD;
	static const int EXTERNAL_ENTITY_KL_FIELD;
	static const int EVENT_MEANING_FIELD;
	static const int EVENT_MEANING_TICKED_FIELD;
	static const int ATTRIBUTE_FIELD;
	static const int RELATIONSHIP_PHRASE_FIELD;
	static const int TRANSFORMER_FIELD;
	static const int TRANSFORMER_PARM_FIELD;
	static const int BRIDGE_FIELD;
	static const int BRIDGE_PARM_FIELD;
  // Not used: static const int EXTERNAL_ENTITY_NAME_FIELD;
	static const int SYNCH_SERVICE_FIELD;
	static const int SYNCH_SERVICE_PARM_FIELD;
	static const int ENUMERATION_FIELD;
	static const int ENUMERATOR_FIELD;

private:

};

#endif
