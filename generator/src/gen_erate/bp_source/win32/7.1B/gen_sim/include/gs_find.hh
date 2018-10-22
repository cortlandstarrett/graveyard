/*========================================================================
 *
 * File:      $RCSfile: gs_find.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:18 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef GS_FIND_HH
#define GS_FIND_HH






// Other classes we reference
//
class Domain;
class Domain;
class D_external_entity;
class D_external_entity_event;
class Object;
class Attribute;
class Relationship;
class D_sm_event;
class String;
class D_synchronous_service;
class D_enum_data_type;



class GS_find

{
public:
    //
    //  IMPORTANT: The caller of these functions must delete the returned
    //      collection pointer.
    //
    static mc_dbms_Bag<D_enum_data_type*>*
	find_enum_data_type_by_name
	(const Description& p_key_letters_str, const Domain* p_domain_ptr = 0);

    static mc_dbms_Bag<D_external_entity*>*
	find_external_entity_by_key_letters
	(const Description& p_key_letters_str, const Domain* p_domain_ptr = 0);

    static mc_dbms_Bag<D_external_entity_event*>*
	find_external_entity_event_by_label
	(const Description& p_label_str, const Domain* p_domain_ptr = 0);

    static mc_dbms_Bag<Object*>*
	find_object_by_key_letters
	(const Description& p_key_letters_str, const Domain* p_domain_ptr = 0);

    static mc_dbms_Bag<Relationship*>*
	find_relationship_by_number
	(const Description& p_number_str, const Domain* p_domain_ptr = 0);

    static mc_dbms_Bag<D_sm_event*>*
	find_sm_event_by_label
	(const Description& p_label_str, const Domain* p_domain_ptr = 0);

    static mc_dbms_Bag <D_synchronous_service*>*
	find_synch_service_by_name
	(const Description& p_func, const Domain* p_domain_ptr = 0);


    static Object*
	find_object_by_id
	(const Id& p_id, const Domain* p_domain_ptr = 0);

    static Attribute*
	find_attribute_by_id
	(const Id& p_id, const Domain* p_domain_ptr = 0);

    static Relationship*
	find_relationship_by_id
	(const Id& p_id, const Domain* p_domain_ptr = 0);

    static D_sm_event*
	find_sm_event_by_id
	(const Id& p_id, const Domain* p_domain_ptr = 0);
};




#endif
