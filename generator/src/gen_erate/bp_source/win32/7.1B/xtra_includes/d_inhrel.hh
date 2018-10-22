/*========================================================================
 *
 * File:      $RCSfile: d_inhrel.hh,v $
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
#include <mc_dbms/mc_dbms.hh>

#ifndef D_INHERITANCE_RELATIONSHIP_HH
#define D_INHERITANCE_RELATIONSHIP_HH

//
// FILE: D_inheritance_relationship.hh		AUTHOR: David E. Solomon
// CREATION DATE: 11/24/92
//
// CONTENTS:
//
//		This file describes the C++ classes that define the Inheritance
//		Relationship Subsystem.
//
// REMARKS:
//
//		None.
//


// Include those header files that are DIRECTLY needed by this one.


#include "u_typdef.hh"
#include "u_id.hh"

#include <u_string.hh>
#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include "d_typdef.hh"
#include "d_object.hh"
#include "d_rel.hh"

// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class Inheritance_relationship;
class Object_as_supertype;
class Object_as_subtype;

// declare classes from other subsystems that are referenced

// from Domain Subsystem

class D_im_ocm_oam;

//
// CLASS: Inheritance_relationship
//
// DESCRIPTION:
//
//		This defines an inheritance relationship, which is a sub-type of
//		Relationship.
//
// RELATIONSHIP PARTICIPATION:
//
// REMARKS:
//
//		None.
//

class Inheritance_relationship : public Relationship
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Inheritance_relationship( D_im_ocm_oam *p_im_ptr,
			t_uint p_rel_num = 0, 
	  	const Description & p_description = Description::Default );

		Inheritance_relationship( D_im_ocm_oam *p_im_ptr,
			t_uint p_rel_num, Id p_id, 
	  	const Description & p_description = Description::Default );

		virtual ~Inheritance_relationship() {}

		// IMPLEMENTOR functions

		Object_as_subtype *create_object_as_subtype( const Id &p_obj_id,
			t_boolean p_create_referential_data = TRUE );

		Object_as_subtype *create_object_as_subtype( const Id &p_obj_id,
			const Id & p_id, t_boolean p_create_referential_data = TRUE );

		Object_as_subtype *create_object_as_subtype( const Id &p_obj_id,
			String &p_err_msg, t_boolean p_create_referential_data = TRUE );

		Object_as_supertype *create_object_as_supertype( const Id &p_obj_id );
		Object_as_supertype *create_object_as_supertype(
			const Id &p_obj_id, const Id & p_id );

		virtual void copy_relationship();   // supertype
		void copy_relationship(const Id &p_obj_id );   // subtype
		void remove_object_as_subtype( const Id &p_obj_id );

        void export_subtype(IE_export_sql * p_export_ptr, Object* subtype);

		virtual t_boolean is_binary() { return FALSE; }

		t_uint get_number_of_object_as_subtypes();

		t_boolean audit_before_committing( Object *p_subtype_object_ptr,
			String &p_err_msg );

		virtual Inheritance_relationship *get_inheritance_relationship_ptr()
			{ return this; }

		// ACCESS functions.

		Object_as_supertype *get_object_as_supertype_ptr()
			{ return object_as_supertype_ptr; }

		mc_dbms_List< Object_as_subtype *> *get_obj_as_subtype_coll_ptr()
			{ return &object_as_subtypes.getvalue(); }

		void * get_audit_ptr() { return audit_ptr; }
		void set_audit_ptr( void * p_audit_ptr ) { audit_ptr = p_audit_ptr; }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		void * audit_ptr;	// for inheritance audit

		mc_dbms_relationship_1_1(Inheritance_relationship,object_as_supertype_ptr,Object_as_supertype,inh_rel_ptr,Object_as_supertype *) object_as_supertype_ptr;

		mc_dbms_relationship_m_1(Inheritance_relationship,object_as_subtypes,Object_as_subtype,inh_rel_ptr,mc_dbms_List< Object_as_subtype *>) object_as_subtypes;

		// HELPING functions
	};


//
// CLASS: Object_as_supertype
//
// DESCRIPTION:
//
//		This defines a supertype object in an inheritance relationship.
//
// REMARKS:
//
//		None.
//

class Object_as_supertype : public Object_referred_to
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_as_supertype( const Id &p_obj_id,
			Inheritance_relationship *p_inh_rel_ptr,
			const char *p_text_phrase = "" );

		Object_as_supertype( const Id &p_obj_id,
			Inheritance_relationship *p_inh_rel_ptr,
			const Id & p_id,
			const char *p_text_phrase = "" );

		virtual ~Object_as_supertype();

		// IMPLEMENTOR functions

		virtual Object_as_supertype *
			get_object_as_supertype_ptr() { return this; }

		// ACCESS functions.

		Inheritance_relationship *get_inh_rel_ptr() { return inh_rel_ptr; }

		void * get_audit_ptr() { return audit_ptr; }
		void set_audit_ptr( void * p_audit_ptr ) { audit_ptr = p_audit_ptr; }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		void * audit_ptr;	// for inheritance audit

		mc_dbms_relationship_1_1(Object_as_supertype,inh_rel_ptr,Inheritance_relationship,object_as_supertype_ptr,Inheritance_relationship *) inh_rel_ptr;

		// HELPING functions
	};


//
// CLASS: Object_as_subtype
//
// DESCRIPTION:
//
//		This defines an object that's a subtype of an inheritance relationship.
//
// REMARKS:
//
//		None.
//

class Object_as_subtype : public Object_referring
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_as_subtype( const Id &p_obj_id,
			Inheritance_relationship *p_inh_rel_ptr,
			t_boolean p_create_referential_data );

		Object_as_subtype( const Id &p_obj_id,
			Inheritance_relationship *p_inh_rel_ptr,
			const Id & p_id, 
			t_boolean p_create_referential_data );

		~Object_as_subtype() {}

		virtual t_boolean is_primary() { return FALSE; }

		// IMPLEMENTOR functions

		virtual Object_as_subtype *
			get_object_as_subtype_ptr() { return this; }

		// ACCESS functions.

		Inheritance_relationship *get_inh_rel_ptr() { return inh_rel_ptr; }

		void * get_audit_ptr() { return audit_ptr; }
		void set_audit_ptr( void * p_audit_ptr ) { audit_ptr = p_audit_ptr; }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		void * audit_ptr;	// for inheritance audit

		mc_dbms_relationship_1_m(Object_as_subtype,inh_rel_ptr,Inheritance_relationship,object_as_subtypes,Inheritance_relationship *) inh_rel_ptr;

		// HELPING functions
	};

#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
