/*========================================================================
 *
 * File:      $RCSfile: d_assrel.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:11 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_ASSOCIATIVE_RELATIONSHIP_HH
#define D_ASSOCIATIVE_RELATIONSHIP_HH

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

class Associative_relationship;
class Object_as_assoc_one_side;
class Object_as_assoc_other_side;
class Object_as_associator;

// declare classes from other subsystems that are referenced

// from Domain Subsystem

class D_im_ocm_oam;

// for migration

class Simple_relationship;


//
// CLASS: Associative_relationship
//
// DESCRIPTION:
//
//		This defines an associative relationship, which is a sub-type of
//		Relationship.
//
// RELATIONSHIP PARTICIPATION:
//
// REMARKS:
//
//		None.
//

class Associative_relationship : public Relationship
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Associative_relationship( D_im_ocm_oam *p_im_ptr,
			t_uint p_rel_num = 0,
      const Description & p_description = Description::Default );


		Associative_relationship( D_im_ocm_oam *p_im_ptr,
			t_uint p_rel_num, Id p_id,
      const Description & p_description = Description::Default );


		virtual ~Associative_relationship() {}

		// IMPLEMENTOR functions

		virtual t_boolean is_reflexive();

		Object_as_assoc_one_side *create_object_as_assoc_one_side(
			const Id &p_obj_id );
		Object_as_assoc_one_side *create_object_as_assoc_one_side(
			const Id &p_obj_id, const Id & p_id );

		Object_as_assoc_other_side *create_object_as_assoc_other_side(
			const Id &p_obj_id );
		Object_as_assoc_other_side *create_object_as_assoc_other_side(
			const Id &p_obj_id, const Id & p_id );

		Object_as_associator *create_object_as_associator(
			const Id &p_obj_id );
		Object_as_associator *create_object_as_associator(
			const Id &p_obj_id, const Id & p_id );

		Simple_relationship *migrate_to_simple_rel();
		virtual void copy_relationship();
		void copy_as_simple_relationship();

		void export_as_simple_relationship(IE_export_sql * p_export_ptr);

		virtual Associative_relationship *get_associative_relationship_ptr()
			{ return this; }

		virtual t_boolean is_binary() { return FALSE; }

		// ACCESS functions.

		Object_as_assoc_one_side *get_object_as_assoc_one_side_ptr() const
			{ return object_as_assoc_one_side_ptr; }

		Object_as_assoc_other_side *get_object_as_assoc_other_side_ptr() const
			{ return object_as_assoc_other_side_ptr; }

		Object_as_associator *get_object_as_associator_ptr()
			{ return object_as_associator_ptr; }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		mc_dbms_relationship_1_1(Associative_relationship,object_as_assoc_one_side_ptr,Object_as_assoc_one_side,assoc_rel_ptr,Object_as_assoc_one_side *) object_as_assoc_one_side_ptr;

		mc_dbms_relationship_1_1(Associative_relationship,object_as_assoc_other_side_ptr,Object_as_assoc_other_side,assoc_rel_ptr,Object_as_assoc_other_side *) object_as_assoc_other_side_ptr;

		mc_dbms_relationship_1_1(Associative_relationship,object_as_associator_ptr,Object_as_associator,assoc_rel_ptr,Object_as_associator *) object_as_associator_ptr;

		// HELPING functions
	};


//
// CLASS: Object_as_assoc_one_side
//
// DESCRIPTION:
//
//		This defines an object that is one of the sides of an associative
// 		relationship.
//
// RELATIONSHIP PARTICIPATION:
//
// REMARKS:
//
//		None.
//
#pragma warning( push )
#pragma warning( disable : 4250 )

class Object_as_assoc_one_side : public Object_in_non_inh_relationship,
	public Object_referred_to
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_as_assoc_one_side( const Id &p_obj_id,
			Associative_relationship *p_assoc_rel_ptr,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = MANY,
			const vchar *p_text_phrase = Description::null_string);

		Object_as_assoc_one_side( const Id &p_obj_id,
			Associative_relationship *p_assoc_rel_ptr,
			const Id & p_id,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = MANY,
			const vchar *p_text_phrase = Description::null_string );

		virtual ~Object_as_assoc_one_side();

		// IMPLEMENTOR functions

		virtual Object_as_assoc_one_side *
			get_object_as_assoc_one_side_ptr() { return this; }

		// ACCESS functions.

		Associative_relationship *get_assoc_rel_ptr() { return assoc_rel_ptr; }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		mc_dbms_relationship_1_1(Object_as_assoc_one_side,assoc_rel_ptr,Associative_relationship,object_as_assoc_one_side_ptr,Associative_relationship *) assoc_rel_ptr;
		// HELPING functions
	};

#pragma warning( pop )

//
// CLASS: Object_as_assoc_other_side
//
// DESCRIPTION:
//
//		This defines an object that is other of the sides of an associative
// 		relationship.
//
// RELATIONSHIP PARTICIPATION:
//
// REMARKS:
//
//		None.
//

#pragma warning( push )
#pragma warning( disable : 4250 )

class Object_as_assoc_other_side : public Object_in_non_inh_relationship,
	public Object_referred_to
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_as_assoc_other_side( const Id &p_obj_id,
			Associative_relationship *p_assoc_rel_ptr,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = MANY,
			const vchar *p_text_phrase = Description::null_string );

		Object_as_assoc_other_side( const Id &p_obj_id,
			Associative_relationship *p_assoc_rel_ptr,
			const Id & p_id,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = MANY,
			const vchar *p_text_phrase = Description::null_string );

		virtual ~Object_as_assoc_other_side();

		// IMPLEMENTOR functions

		virtual Object_as_assoc_other_side *
			get_object_as_assoc_other_side_ptr() { return this; }

		// ACCESS functions.

		Associative_relationship *get_assoc_rel_ptr() { return assoc_rel_ptr; }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		mc_dbms_relationship_1_1(Object_as_assoc_other_side,assoc_rel_ptr,Associative_relationship,object_as_assoc_other_side_ptr,Associative_relationship *) assoc_rel_ptr;
		// HELPING functions
	};

#pragma warning( pop )

//
// CLASS: Object_as_associator
//
// DESCRIPTION:
//
//		This defines the Associative Object itself.
//
// RELATIONSHIP PARTICIPATION:
//
// REMARKS:
//
//		We will use Object_in_non_inh_relationship as a base class even
//		though an associative object really doesn't have conditionality.
//		In this regard we will set conditionality to UNCONDITIONAL in
//		the base class member initialization list.
//

#pragma warning( push )
#pragma warning( disable : 4250 )

class Object_as_associator : public Object_in_non_inh_relationship,
	public Object_referring
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_as_associator( const Id &p_obj_id,
			Associative_relationship *p_assoc_rel_ptr,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		Object_as_associator( const Id &p_obj_id,
			Associative_relationship *p_assoc_rel_ptr,
			const Id & p_id,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		virtual ~Object_as_associator();

		virtual t_boolean is_primary() { return FALSE; }

		// IMPLEMENTOR functions

		virtual Object_as_associator *
			get_object_as_associator_ptr() { return this; }

		// ACCESS functions.

		Associative_relationship *get_assoc_rel_ptr() { return assoc_rel_ptr; }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		mc_dbms_relationship_1_1(Object_as_associator,assoc_rel_ptr,Associative_relationship,object_as_associator_ptr,Associative_relationship *) assoc_rel_ptr;
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
