/*========================================================================
 *
 * File:      $RCSfile: d_attr.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:06 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_ATTRIBUTE_HH
#define D_ATTRIBUTE_HH


// Include those header files that are DIRECTLY needed by this one.


#include <d_object.hh>

class Object_identifier_attribute;
class Referential_attribute;
class Base_attribute;

//
// CLASS: Attribute
//
// DESCRIPTION:
//
//		Defines a given object attribute.
//
// RELATIONSHIP PARTICIPATION:
//
//		R1 - Many-side of 1:cM relationship with Object.
//		R3 - Endoint along with Object_identifier for 1-M:M associative
//			 object Object_identifier_attribute
//		R4 - Supertype for Base_attribute and Referential_attribute
//		R7 - Both sides of c1:c1 relationship with self
//		R14 - One-side of 1:c1 of relationship with Referential_attribute-
//			  _constraint
//
// REMARKS:
//
//		This class will serve as an abstract base class for Base_attribute
//		and Referential_attribute.
//

class Attribute
	{
	public:
		enum t_prefix_derive_mode { USE_NO_PREFIX, USE_LOCAL_PREFIX,
			USE_REFERRED_TO_PREFIX };

		// MANAGER functions

		virtual ~Attribute();

		static mc_dbms_typespec *get_mc_dbms_typespec();

		void delete_attribute();
		Attribute* copy_attribute(Object* p_obj, Attribute* p_prev_attr);
		Attribute* paste_attribute(Object* p_obj);

		// This function will tear down and delete all associations for which
		// this attribute participates in (eg - an identifier or a referred to
		// identifier).

		void delete_ids_and_refs_and_ref_attrs(t_boolean p_delete_all);

		// IMPLEMENTOR functions

		t_uint get_number_of_object_id_attrs();

		t_boolean is_an_identifier();

		Object_identifier_attribute *create_object_id_attr( t_uint p_id_id );
		void delete_object_id_attr( t_uint p_id_id );

		t_boolean ok_to_delete_attribute();

		virtual Base_attribute *navigate_to_base_attr() = 0;
		virtual Base_attribute *global_navigate_to_base_attr() = 0;

		// Functions to add referentials to other objects

		// R3
		void add_ref( Object_identifier_attribute *p_object_id_attr_ptr )
			{ object_identifier_attributes.insert( p_object_id_attr_ptr ); }

		// find/query functions.

		Object_identifier_attribute *find_object_id_attr( t_uint p_id_id );

		// ACCESS functions

		Id containing_object_id() { return object_ptr->get_object_id(); }
		Description containing_object_name() { return object_ptr->get_object_name();}
		const Id & containing_attr_id() { return id; }
		const Id & get_id() { return id; }

		t_prefix_derive_mode get_prefix_derive_mode()
			{ return prefix_derive_mode; }
		void set_prefix_derive_mode( t_prefix_derive_mode p_prefix_derive_mode )
			{ prefix_derive_mode = p_prefix_derive_mode; }

		virtual Description get_prefix() = 0;
		virtual void set_prefix( const vchar *p_prefix ) = 0;

		virtual Description get_root() = 0;
		virtual void set_root( const vchar *p_root ) = 0;

		virtual Description get_attr_name() { Description temp = get_prefix();
		  temp += get_root(); return temp;}

		Description &attribute_description() { return description; }

		Object *get_object_ptr() const { return object_ptr; }
		D_im_ocm_oam *get_im_ocm_oam_ptr() const { return im_ocm_oam_ptr; }

		Domain *get_domain_ptr()
			{ return get_im_ocm_oam_ptr()->get_domain_ptr(); }
		Domain_id get_domain_id()
			{ return get_im_ocm_oam_ptr()->get_domain_id(); }

		virtual Base_attribute *get_base_attribute_ptr() { return 0; }
		virtual Referential_attribute *get_referential_attribute_ptr()
			{ return 0; }

		mc_dbms_Set< Object_identifier_attribute * >
			*get_obj_id_attr_coll_ptr()
			{ return &object_identifier_attributes.getvalue(); }

                mc_dbms_segment* get_config_ptr ()
			{ return get_object_ptr()->get_config_ptr(); }

		D_core_data_type * get_core_data_type_ptr ();
		D_enum_data_type * get_enum_data_type_ptr ();

		void set_data_type_id (Id p_id)
			{ m_data_type_id = p_id; }
		Id get_data_type_id ()
			{ return m_data_type_id; }

    DELETE_DOWN_DECL_SUPERTYPE()


	protected:

		Attribute( Object *p_object_ptr,
			t_prefix_derive_mode p_prefix_derive_mode, const vchar *p_prefix,
			const vchar *p_root, 
	  	const Description & p_description );

		Attribute( Object *p_object_ptr, const Id &p_id,
			t_prefix_derive_mode p_prefix_derive_mode, const vchar *p_prefix,
			const vchar *p_root, const Description & p_description );

		Description prefix;
		Description root;

		t_prefix_derive_mode prefix_derive_mode;

		Description description;

		// For R1, use pointer to Object we are associated with. We will use
		// OS's relationships to maintain integrity.

		mc_dbms_relationship_1_m(Attribute,object_ptr,Object,attributes,Object *) object_ptr;

		mc_dbms_relationship_1_m(Attribute,im_ocm_oam_ptr,D_im_ocm_oam,attributes,D_im_ocm_oam *) im_ocm_oam_ptr;

		// For R3, maintain set of all Object_identifier_attribute instances
		// this Attribute participates in (ie - an attribute can be a part of
		// more than one identifier).

		mc_dbms_relationship_m_1(Attribute,object_identifier_attributes,Object_identifier_attribute,attr_ptr,mc_dbms_Set< Object_identifier_attribute * >) object_identifier_attributes;

		// HELPING functions

	private:

		Id id;

		Id m_data_type_id;

		// HELPING functions

		Id_assigner &id_assigner()
			{ return get_im_ocm_oam_ptr()->get_assigners()->attr_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}

		void delete_object_id_attrs(t_boolean);
	};


#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
