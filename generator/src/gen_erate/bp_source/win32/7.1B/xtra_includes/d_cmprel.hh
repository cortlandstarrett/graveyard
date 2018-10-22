/*========================================================================
 *
 * File:      $RCSfile: d_cmprel.hh,v $
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

#ifndef D_COMPOSITION_RELATIONSHIP_HH
#define D_COMPOSITION_RELATIONSHIP_HH


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

class Composition_relationship;
class Object_as_comp_one_end;
class Object_as_comp_other_end;

// declare classes from other subsystems that are referenced

// from Domain Subsystem

class D_im_ocm_oam;

// for migration

class Simple_relationship;
class Associative_relationship;


//
// CLASS: Composition_relationship
//
// DESCRIPTION:
//
//		This defines a composition relationship, which is a sub-type of
//		Relationship.
//
// RELATIONSHIP PARTICIPATION:
//
// REMARKS:
//
//		None.
//

class Composition_relationship : public Relationship
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Composition_relationship( D_im_ocm_oam *p_im_ptr,
			t_uint p_rel_num = 0,
   		const Description & p_rel_description = Description::Default,
	  	const char *p_comp_description = "" );

		Composition_relationship( D_im_ocm_oam *p_im_ptr,
			t_uint p_rel_num, Id p_id, 
  		const Description & p_rel_description = Description::Default,
	  	const char *p_comp_description = "" );

		virtual ~Composition_relationship() {}
		virtual void copy_relationship();

		// IMPLEMENTOR functions

		Object_as_comp_one_end *create_object_as_comp_one_end(
			const Id &p_obj_id );
		Object_as_comp_one_end *create_object_as_comp_one_end(
			const Id &p_obj_id, const Id & p_id );

		Object_as_comp_other_end *create_object_as_comp_other_end(
			const Id &p_obj_id );
		Object_as_comp_other_end *create_object_as_comp_other_end(
			const Id &p_obj_id, const Id & p_id );

		// i2760.1.4 deleted
		Associative_relationship *migrate_to_assoc_rel( const Id &p_obj_id );

		virtual Composition_relationship *get_composition_relationship_ptr()
			{ return this; }

		// ACCESS functions.

		String &composition_loop_string() { return comp_loop_string; }

		Object_as_comp_one_end *get_object_as_comp_one_end_ptr()
			{ return object_as_comp_one_end_ptr; }

		void set_object_as_comp_one_end_ptr( Object_as_comp_one_end *
			p_one_end_ptr ) { object_as_comp_one_end_ptr = p_one_end_ptr; }

		Object_as_comp_other_end *get_object_as_comp_other_end_ptr()
			{ return object_as_comp_other_end_ptr; }

		void set_object_as_comp_other_end_ptr( Object_as_comp_other_end *
			p_other_end_ptr ) { object_as_comp_other_end_ptr = p_other_end_ptr;}

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		String comp_loop_string;

		Object_as_comp_one_end *object_as_comp_one_end_ptr;

		Object_as_comp_other_end *object_as_comp_other_end_ptr;

		// HELPING functions
	};


//
// CLASS: Object_as_comp_one_end
//
// DESCRIPTION:
//
//		This defines an object that is one end in a composition relationship.
//
// RELATIONSHIP PARTICIPATION:
//
// REMARKS:
//
//		None.
//

class Object_as_comp_one_end : public Object_in_non_inh_relationship
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_as_comp_one_end( const Id &p_obj_id,
			Composition_relationship *p_comp_rel_ptr,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		Object_as_comp_one_end( const Id &p_obj_id,
			Composition_relationship *p_comp_rel_ptr,
			const Id & p_id,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		~Object_as_comp_one_end() {}

		// IMPLEMENTOR functions

		virtual Object_as_comp_one_end *
			get_object_as_comp_one_end_ptr() { return this; }

		// ACCESS functions.

		Composition_relationship *get_composition_relationship_ptr() const
		  { return get_relationship_ptr()->get_composition_relationship_ptr(); }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		// HELPING functions
	};


//
// CLASS: Object_as_comp_other_end
//
// DESCRIPTION:
//
//		This defines an object that is other end in a composition relationship.
//
// RELATIONSHIP PARTICIPATION:
//
// REMARKS:
//
//		None.
//

class Object_as_comp_other_end : public Object_in_non_inh_relationship
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_as_comp_other_end( const Id &p_obj_id,
			Composition_relationship *p_comp_rel_ptr,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		Object_as_comp_other_end( const Id &p_obj_id,
			Composition_relationship *p_comp_rel_ptr,
			const Id & p_id,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		~Object_as_comp_other_end() {}

		// IMPLEMENTOR functions

		virtual Object_as_comp_other_end *
			get_object_as_comp_other_end_ptr() { return this; }

		// ACCESS functions.

		Composition_relationship *get_composition_relationship_ptr() const
		  { return get_relationship_ptr()->get_composition_relationship_ptr(); }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

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
