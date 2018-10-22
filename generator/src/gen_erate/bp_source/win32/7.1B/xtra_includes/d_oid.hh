/*========================================================================
 *
 * File:      $RCSfile: d_oid.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:13 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_OBJECT_IDENTIFIER_HH
#define D_OBJECT_IDENTIFIER_HH


// Include those header files that are DIRECTLY needed by this one.


#include <u_deldwn.hh>     // For DELETE_DOWN macros
#include <u_desc.hh>
#include <u_id.hh>
#include <u_typdef.hh>

#include <d_object.hh>

class Object_identifier_attribute;
class Object_referred_to;
class Referred_to_ident_attr;

//
// CLASS: Object_identifier
//
// DESCRIPTION:
//
//		This defines an object identifier, which is a set of attributes.
//		Remember an object can have more than one identifier and the same
//		attribute can be a member of more than one identifier.
//
// RELATIONSHIP PARTICIPATION:
//
//		R104 - M:1 relationship with Object
//		R105 - One endpoint of the 1-M:M associative object
//			 Object_identifier_attribute with the other end being Attribute.
//		R109 - 1:cM relationship with Object_referred_to
//
// REMARKS:
//
//		An Object will always be allocated exactly NUM_OBJECT_IDENTIFIERS
//		Object_identifier instances when the Object is created. The
//		Object_identifier Id's within each given object will be numbered
//		from 0 to NUM_OBJECT_IDENTIFIERS - 1, accordingly.
//

class Object_identifier
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_identifier( Object *p_object_ptr, t_uint p_identifier_id = 0 );

		~Object_identifier ();

		// IMPLEMENTOR functions

		t_uint get_number_of_object_id_attrs();
		t_uint get_number_of_object_referred_tos();

		// ACCESS functions

		Id object_id() { return object_ptr->get_object_id(); }
		Description object_name() { return object_ptr->get_object_name();}
		t_uint &object_identifier_id() { return identifier_id; }

		Object *get_object_ptr() const { return object_ptr; }

		// Get pointers to collections

		mc_dbms_Set< Object_identifier_attribute * >
			*get_obj_id_attr_coll_ptr()
			{ return &object_identifier_attributes.getvalue(); }

		mc_dbms_Set< Object_referred_to * > *get_obj_referred_to_coll_ptr();

        mc_dbms_segment* get_config_ptr ()
			{ return get_object_ptr()->get_config_ptr(); }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		// For R104, keep pointer to object this identifier is associated with.
		mc_dbms_relationship_1_m(Object_identifier,object_ptr,Object,object_identifiers,Object *) object_ptr;

		// For implementation reasons, instead of using the common Id class
		// to represent the identifier id, use unsigned integers ranging from
		// 0 to NUM_OBJECT_IDENTIFIERS - 1(Admittedly kludgey and contrary to
		// domain separation).

		t_uint identifier_id;

		// For R105, maintain a set of all Object_identifier_attribute instances
		// associated with this Object_identifier.

		mc_dbms_relationship_m_1(Object_identifier,object_identifier_attributes,Object_identifier_attribute,ident_ptr,mc_dbms_Set< Object_identifier_attribute * >) object_identifier_attributes;

        // R109 is implemented by id attributes in the Object_referred_to class

		// HELPING functions

		void delete_object_id_attrs();
		void delete_object_referred_tos();
	};


#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
