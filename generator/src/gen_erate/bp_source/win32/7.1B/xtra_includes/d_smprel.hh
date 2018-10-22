/*========================================================================
 *
 * File:      $RCSfile: d_smprel.hh,v $
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

#ifndef D_SIMPLE_RELATIONSHIP_HH
#define D_SIMPLE_RELATIONSHIP_HH

//
// FILE: D_simple_relationship.hh		AUTHOR: David E. Solomon
// CREATION DATE: 9/9/92
//
// CONTENTS:
//
//		This file describes the C++ classes that define the Simple Relationship
//		Subsystem.
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

class Simple_relationship;
class Object_as_simple_participant;
class Object_as_simple_formalizer;

// declare classes from other subsystems that are referenced

// from Object Subsystem

class Object;
class Object_identifier;
class Object_identifier_attribute;
class Attr_ref_in_object;

// from Domain Subsystem

class D_im_ocm_oam;

// for migration types

class Composition_relationship;
class Associative_relationship;


//
// CLASS: Simple_relationship
//
// DESCRIPTION:
//
//		This defines a simple relationship, which is a sub-type of Relationship.
//
// RELATIONSHIP PARTICIPATION:
//
//		R102 - Subtype of Relationship
//		R111 - 1:1 relationship with Object_as_simple_participant
//		R112 - 1:1 relationship with Object_as_simple_formalizer
//
// REMARKS:
//
//		None.
//

class Simple_relationship : public Relationship
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Simple_relationship( D_im_ocm_oam *p_im_ptr,
			t_uint p_rel_num = 0,
	  	const Description & p_description = Description::Default );

		Simple_relationship( D_im_ocm_oam *p_im_ptr,
			t_uint p_rel_num, Id p_id, 
	  	const Description & p_description = Description::Default );

		virtual ~Simple_relationship() {}

		// IMPLEMENTOR functions

		virtual t_boolean is_reflexive();
		virtual void copy_relationship();

		Object_as_simple_formalizer *create_object_as_simp_form(
			const Id &p_obj_id );
		Object_as_simple_formalizer *create_object_as_simp_form(
			const Id &p_obj_id, const Id & p_id );

		Object_as_simple_participant *create_object_as_simp_part(
			const Id &p_obj_id );
		Object_as_simple_participant *create_object_as_simp_part(
			const Id &p_obj_id, const Id & p_id );

		Object_in_non_inh_relationship *create_object_in_non_inh_rel(
			const Id &p_obj_id );
		Object_in_non_inh_relationship *create_object_in_non_inh_rel(
			const Id &p_obj_id, const Id & p_id );

		Associative_relationship *migrate_to_assoc_rel( const Id &p_obj_id );
        // i2760.1.3 deleted

		virtual Simple_relationship *get_simple_relationship_ptr()
			{ return this; }

		// ACCESS functions.

		Object_as_simple_participant *get_object_as_simple_part_ptr()
			{ return object_as_simple_part_ptr; }

		void set_object_as_simple_part_ptr( Object_as_simple_participant
			*p_part_ptr ) { object_as_simple_part_ptr = p_part_ptr; }

		Object_as_simple_formalizer *get_object_as_simple_form_ptr()
			{ return object_as_simple_form_ptr; }

		void set_object_as_simple_form_ptr( Object_as_simple_formalizer
			*p_form_ptr ) { object_as_simple_form_ptr = p_form_ptr; }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		Object_as_simple_participant *object_as_simple_part_ptr;

		Object_as_simple_formalizer *object_as_simple_form_ptr;

		// HELPING functions
	};


//
// CLASS: Object_as_simple_participant
//
// DESCRIPTION:
//
//		This defines an object that is a simple participant in a simple
//		relationship.
//
// RELATIONSHIP PARTICIPATION:
//
//		R103 - Subtype of Object_in_relationship
//		R111 - 1:1 relationship with Simple_relationship
//		R113 - cM:1 relationship with Object_identifier
//		R114 - M:M relationship with Object_identifier_attribute
//
// REMARKS:
//
//		A simple participant is the object whose attributes are referred to
//		in another object. It is also important to note that none of the
//		constructors take the Object_identifier as an argument. This can
//		be set later via the add_ref() function, which resides in the
//		Object_referred_to base class.
//

#pragma warning( push )
#pragma warning( disable : 4250 )

class Object_as_simple_participant : public Object_in_non_inh_relationship,
	public Object_referred_to
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_as_simple_participant( const Id &p_obj_id,
			Simple_relationship *p_simp_rel_ptr,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		Object_as_simple_participant( const Id &p_obj_id,
			Simple_relationship *p_simp_rel_ptr,
			const Id & p_id,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		virtual ~Object_as_simple_participant();

		// IMPLEMENTOR functions

		virtual Object_as_simple_participant *
			get_object_as_simp_part_ptr() { return this; }

		// ACCESS functions.

		Simple_relationship *get_simple_relationship_ptr() const
			{ return get_relationship_ptr()->get_simple_relationship_ptr(); }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		// HELPING functions
	};

#pragma warning( pop )

//
// CLASS: Object_as_simple_formalizer
//
// DESCRIPTION:
//
//		This defines an object that formalizes a simple relationship.
//		relationship.
//
// RELATIONSHIP PARTICIPATION:
//
//		R103 - Subtype of Object_in_relationship
//		R112 - 1:1 relationship with Simple_relationship
//		R115 - 1:M relationship with Participant_identifier_attribute
//
// REMARKS:
//
//		None.
//

#pragma warning( push )
#pragma warning( disable : 4250 )

class Object_as_simple_formalizer : public Object_in_non_inh_relationship,
	public Object_referring
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_as_simple_formalizer( const Id &p_obj_id,
			Simple_relationship *p_simp_rel_ptr,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		Object_as_simple_formalizer( const Id &p_obj_id,
			Simple_relationship *p_simp_rel_ptr,
			const Id & p_id,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		virtual ~Object_as_simple_formalizer();

		// IMPLEMENTOR functions

		virtual Object_as_simple_formalizer *
			get_object_as_simp_form_ptr() { return this; }

		// ACCESS functions.

		Simple_relationship *get_simple_relationship_ptr() const
			{ return get_relationship_ptr()->get_simple_relationship_ptr(); }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		// HELPING functions

	};

#pragma warning( pop )

#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
