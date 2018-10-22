/*========================================================================
 *
 * File:      $RCSfile: d_oida.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:09 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_OBJECT_IDENTIFIER_ATTR_HH
#define D_OBJECT_IDENTIFIER_ATTR_HH


// Include those header files that are DIRECTLY needed by this one.


#include <d_attr.hh>
#include <d_oid.hh>

class Referred_to_ident_attr;


//
// CLASS: Object_identifier_attribute
//
// DESCRIPTION:
//
//		This is the 1-M:M associative object derived between Attribute and
//		Object_identifier.
//
// RELATIONSHIP PARTICIPATION:
//
//		R3 - 1-M:M associative object between Attribute and Object_identifier.
//		R13 - 1:cM relationship with Attr_ref_in_object
//		R125 - M:M relationship with Object_as_ass_one_side resulting in
//			   1-M:M associative object One_side_ident_attr.
//		R127 - M:M relationship with Object_as_ass_other_side resulting in
//			   1-M:M associative object other_side_ident_attr.
//		R129 - M:M relationship with Object_as_associator resulting in
//			   1-M:M associative object Associator_ident_attr.
//
// REMARKS:
//
//		None.
//

class Object_identifier_attribute
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		static Object_identifier_attribute *create( Attribute *p_attr_ptr,
			Object_identifier *p_object_id_ptr );

		Object_identifier_attribute( Attribute *p_attr_ptr, Object_identifier
			*p_object_id_ptr );

        void delete_object_identifier_attribute ( t_boolean p_delete_all );

		// IMPLEMENTOR functions

		t_uint get_number_of_referred_to_ident_attrs();

		// ACCESS functions

		// Use Object_identifier instead of Attribute to get to Object
		// data since the Attribute pointer could interimly be severed
		// from its Object.

		Id object_id() { return ident_ptr->object_id(); }
		Description object_name() { return ident_ptr->object_name(); }
		Id attribute_id() { return attr_ptr->containing_attr_id(); }
		const t_uint &object_identifier_id() { return ident_ptr->
			object_identifier_id(); }

		Attribute *get_attribute_ptr() const { return attr_ptr; }
		Object_identifier *get_object_ident_ptr() const { return ident_ptr; }

        Referred_to_ident_attr* find_rtida_by_id( const Id& p_rel_id,
	        const Id& p_oir_id  );

		mc_dbms_Set< Referred_to_ident_attr *>
			*get_referred_to_id_attr_coll_ptr()
			{ return &referred_to_ident_attrs.getvalue(); }

        mc_dbms_segment* get_config_ptr ()
			{ return get_attribute_ptr()->get_config_ptr(); }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		~Object_identifier_attribute();


		// For R105, keep pointers to both the Attribute and the Object_identifier
		// we are associated with.

		mc_dbms_relationship_1_m(Object_identifier_attribute,attr_ptr,Attribute,object_identifier_attributes,Attribute *) attr_ptr;

		mc_dbms_relationship_1_m(Object_identifier_attribute,ident_ptr,Object_identifier,object_identifier_attributes,Object_identifier *) ident_ptr;

        // R110
		mc_dbms_relationship_m_1(Object_identifier_attribute,referred_to_ident_attrs,Referred_to_ident_attr,object_id_attr_ptr,mc_dbms_Set< Referred_to_ident_attr * >) referred_to_ident_attrs;


		// HELPING functions

		void delete_referred_to_ident_attrs(t_boolean);
	};

#endif

