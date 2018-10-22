/*========================================================================
 *
 * File:      $RCSfile: d_rel.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:10 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_RELATIONSHIP_HH
#define D_RELATIONSHIP_HH

//
// FILE: D_relationship.hh		AUTHOR: David E. Solomon
// CREATION DATE: 10/13/92
//
// CONTENTS:
//
//		This file contains the higher level relationship classes that are
//		common to all relationship subsystems(generic).
//
// REMARKS:
//
//		The classes in this file are either base classes or "general_purpose"
//		classes.
//


// Include those header files that are DIRECTLY needed by this one.


#include "u_typdef.hh"
#include "u_id.hh"

#include <u_string.hh>
#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include "d_typdef.hh"
#include "d_object.hh"
#include <d_oid.hh>
#include <d_oida.hh>
#include "d_domain.hh"
#include "d_im_oam.hh"

// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class Relationship;
class Object_in_relationship;
class Object_in_non_inh_relationship;
class Object_referred_to;
class Object_referring;
class Referred_to_ident_attr;

// declare classes from other subsystems that are referenced

// from Domain and Subsystem Subsystem

// from Object Subsystem

class Object;
class Object_identifier;
class Object_identifier_attribute;
class Attr_ref_in_object;

// from Simple Relationship Subsystem

class Simple_relationship;
class Object_as_simple_participant;
class Object_as_simple_formalizer;

// from Associative Relationship Subsystem

class Associative_relationship;
class Object_as_assoc_one_side;
class Object_as_assoc_other_side;
class Object_as_associator;

// from Inheritance Relationship Subsystem

class Inheritance_relationship;
class Object_as_supertype;
class Object_as_subtype;

// from Composition Relationship Subsystem

class Composition_relationship;
class Object_as_comp_one_end;
class Object_as_comp_other_end;



//
// CLASS: Relationship
//
// DESCRIPTION:
//
//		This defines the basic high-level relationship.
//
// RELATIONSHIP PARTICIPATION:
//
//		R201 - cM:M relationship with Object resulting in 1-cM:M associative
//			object Object_in_relationship
//
// REMARKS:
//
//		It is important to note that this class serves as an abstract base
//		class; this is enforced via constructors in the protected section.
//

class Relationship
	{
	public:
		// MANAGER functions

		virtual ~Relationship();

		static mc_dbms_typespec *get_mc_dbms_typespec();
        static t_uint orphaned_rel_number;

		virtual t_boolean is_binary() { return TRUE; }
		virtual t_boolean is_reflexive() { return FALSE; }

		// IMPLEMENTOR functions

        t_boolean can_copy_relationship();
		virtual void copy_relationship();

		void delete_relationship();

		void remove_object_from_relationship( const Id &p_obj_id );

        void export(IE_export_sql * p_export_ptr);

		t_uint get_number_of_object_in_relationships();

		// Iterator and find functions

		// "n" starts at 1, not 0
		Object_in_non_inh_relationship *get_nth_obj_in_non_inh_rel( t_uint n );

		Object_in_relationship *find_object_in_relationship(
			const Id &p_oir_id );

		Object_in_relationship *find_first_oir_by_object( const Id &p_obj_id );

		// find/query functions.
		
		// function to delete ALL contained Object_in_relationship instances.
		// Will also delete all objects associated with each Object_in_-
		// relationship(ie - delete propagation).

        // this subsystem only
		void delete_objects_in_relationship();

		t_boolean can_delete_all_objects_in_relationship(Description &p_err_msg);
		void delete_all_objects_in_relationship();

		// The following virtual functions return a pointer to the
		// derived relationship. They, in essence, kind-of serve as a
		// "type" indicator, but are implemented with virtual functions
		// so we can adhere to sound OO techniques. Each class should
		// re-define its own function.

		virtual Simple_relationship *get_simple_relationship_ptr()
			{ return 0; }
		virtual Associative_relationship *get_associative_relationship_ptr()
			{ return 0; }
		virtual Composition_relationship *get_composition_relationship_ptr()
			{ return 0; }
		virtual Inheritance_relationship *get_inheritance_relationship_ptr()
			{ return 0; }

		// ACCESS functions. Note that a reference (ie - & ) allows the
		// corresponding field/attribute to be an l-value or r-value.
		// However, prefixing a "const" restricts usage to an r-value,
		// something we want to do when we access a field in another class.
		// We must use "set" and "get" for indexable members.

		const Id & get_relationship_id() const { return id; }
		t_uint get_rel_number() const { return rel_num; }
		void set_rel_number( t_uint p_rel_num ) { rel_num = p_rel_num; }
		Description &description() { return desc; }

		D_im_ocm_oam *get_im_ocm_oam_ptr()
			{ return im_ocm_oam_ptr; }
		D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
			{ return get_im_ocm_oam_ptr()->get_dd_srm_scm_sam_ptr(); }

		Domain *get_domain_ptr()
			{ return im_ocm_oam_ptr->get_domain_ptr(); }
		Domain_id get_domain_id()
			{ return get_domain_ptr()->get_domain_id(); }
		mc_dbms_database *get_db_ptr()
			{ return get_domain_ptr()->get_db_ptr(); }

		mc_dbms_Set< Object_in_relationship * > *get_obj_in_rel_coll_ptr()
			{ return &object_relationships.getvalue(); }

        mc_dbms_segment* get_config_ptr ()
            { return mc_dbms_segment::of (this); }

        t_boolean was_exported()
            { return m_exported; }

        void set_exported(t_boolean p_exp)
            { m_exported = p_exp; }

    DELETE_DOWN_DECL_SUPERTYPE()


	protected:

		Relationship( D_im_ocm_oam *p_dd_ptr, t_uint p_rel_num );

		Relationship( D_im_ocm_oam *p_dd_ptr, t_uint p_rel_num, Id p_id );

		Relationship( D_im_ocm_oam *p_dd_ptr, t_uint p_rel_num,
			const Description &p_desc );

		Relationship( D_im_ocm_oam *p_dd_ptr, t_uint p_rel_num,
			const Description &p_desc, Id p_id );

		unsigned int rel_num;

		Description desc;

		// For R201, maintain a collection of associative objects Object_in_-
		// relationship that pertain to this one Relationship instance.

		mc_dbms_relationship_m_1(Relationship,object_relationships,Object_in_relationship,relationship_ptr,mc_dbms_Set< Object_in_relationship * >) object_relationships;

        // R4
		mc_dbms_relationship_1_m(Relationship,im_ocm_oam_ptr,D_im_ocm_oam,relationships,D_im_ocm_oam *) im_ocm_oam_ptr;

	private:

		Id id;
        t_boolean m_exported;

		// The following cursors are used to iterate over the corresponding
		// collection using the above public member functions first_...() and
		// next_...(). Doing so hides the MC_DBMS implementation of collection
		// iteration. Note that these are instance specific.

		// HELPING functions

		Id_assigner &id_assigner()
			{ return get_im_ocm_oam_ptr()->get_assigners()->relationship_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}

		void construct_init();	// common constructor init function

	};


//
// CLASS: Object_in_relationship
//
// DESCRIPTION:
//
//		This defines the associative object between Object and Relationship.
//
// RELATIONSHIP PARTICIPATION:
//
//		R101 - 1-M:cM associative object between Object and Relationship.
//		R103 - Supertype
//
// REMARKS:
//
//		Although conceptually this is an abstract base class, we will
//		allow creations via the constructor so that this can be used
//		to migrate between different Object_in_relationship's.
//

class Object_in_relationship
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_in_relationship( const Id &p_obj_id, Relationship *p_rel_ptr );

		// This constructor needed for migration between different types
		// of relationships to keep same Object_in_relationship id.

		Object_in_relationship( const Id &p_obj_id, Relationship *p_rel_ptr,
			const Id & p_id );

		virtual ~Object_in_relationship();

		void delete_object_in_relationship();

		virtual t_boolean is_primary() { return TRUE; }

		// IMPLEMENTOR functions

		// The following determine what derived class we are in. Each derived
		// class should only re-define its own function.

		virtual Object_in_non_inh_relationship *
			get_object_in_non_inh_relationship_ptr() { return 0; }

		virtual Object_referred_to *
			get_object_referred_to_ptr() { return 0; }

		virtual Object_referring *
			get_object_referring_ptr() { return 0; }

		virtual Object_as_simple_participant *
			get_object_as_simp_part_ptr() { return 0; }

		virtual Object_as_simple_formalizer *
			get_object_as_simp_form_ptr() { return 0; }

		virtual Object_as_comp_one_end *
			get_object_as_comp_one_end_ptr() { return 0; }

		virtual Object_as_comp_other_end *
			get_object_as_comp_other_end_ptr() { return 0; }

		virtual Object_as_assoc_one_side *
			get_object_as_assoc_one_side_ptr() { return 0; }

		virtual Object_as_assoc_other_side *
			get_object_as_assoc_other_side_ptr() { return 0; }

		virtual Object_as_associator *
			get_object_as_associator_ptr() { return 0; }

		virtual Object_as_supertype *
			get_object_as_supertype_ptr() { return 0; }

		virtual Object_as_subtype *
			get_object_as_subtype_ptr() { return 0; }

		// ACCESS functions.

		const Id & get_id() const { return id; }
		Object *get_related_object_ptr() const;
		Relationship *get_relationship_ptr() const { return relationship_ptr; }
		Id object_id() const { return m_object_id; }
		Id relationship_id() const { return relationship_ptr->
			get_relationship_id();}

		Imported_object *get_imported_object_ptr()
			{ return imported_object_ptr; }
		void set_imported_object_ptr( Imported_object *p_io_ptr )
			{ imported_object_ptr.relate( p_io_ptr, this ); }

		mc_dbms_segment *get_config_ptr()
			{ return get_relationship_ptr()->get_config_ptr(); }

    DELETE_DOWN_DECL_SUPERTYPE()


	protected:

		Id id;
        Id m_object_id;   // R201 to O_OBJ

		// For R201, maintain pointers to the Relationship this
		// particular associative object instance is associated with.

		mc_dbms_relationship_1_m(Object_in_relationship,relationship_ptr,Relationship,object_relationships,Relationship *) relationship_ptr;

        //  R202
		mc_dbms_relationship_1_m(Object_in_relationship,imported_object_ptr,Imported_object,object_in_relationships,Imported_object *) imported_object_ptr;


		// HELPING functions

		Id_assigner &id_assigner()
			{ return relationship_ptr->get_im_ocm_oam_ptr()->get_assigners()->
				obj_in_rel_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}
	};


//
// CLASS: Object_in_non_inh_relationship
//
// DESCRIPTION:
//
//		This defines any Object_in_relationship that has the additional
//		charactersistics of multiplicity and conditionality.
//
// REMARKS:
//
//		Per S/M, only inheritance relationships do NOT possess these
//		characteristics.
//

class Object_in_non_inh_relationship : public virtual Object_in_relationship
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Object_in_non_inh_relationship( const Id &p_obj_id,
			Relationship *p_rel_ptr,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		Object_in_non_inh_relationship( const Id &p_obj_id,
			Relationship *p_rel_ptr,
			const Id & p_id,
			t_conditionality p_cond = UNCONDITIONAL,
			t_multiplicity p_mult = ONE,
			const vchar *p_text_phrase = Description::null_string );

		virtual ~Object_in_non_inh_relationship() {}

		// IMPLEMENTOR functions

		virtual Object_in_non_inh_relationship
			*get_object_in_non_inh_relationship_ptr() { return this; }

		// ACCESS functions.

		t_conditionality &conditionality() { return cond; }
		t_multiplicity &multiplicity() { return mult; }
		Description &text_phrase() { return phrase; }

    DELETE_DOWN_DECL_SUPERTYPE()


	protected:

		t_conditionality cond;
		t_multiplicity mult;
		Description phrase;

		// HELPING functions
	};


//
// CLASS: Object_referred_to
//
// DESCRIPTION:
//
//		This defines an S/M object that contains the attributes that another
//		object refers to via referential attributes.
//
// RELATIONSHIP PARTICIPATION:
//
// REMARKS:
//
//		This is a type of Object_in_relationship.
//

class Object_referred_to : public virtual Object_in_relationship
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		virtual ~Object_referred_to();

		// IMPLEMENTOR functions

		virtual Object_referred_to
			*get_object_referred_to_ptr() { return this; }

		void add_ref_and_ref_attrs( Object_identifier *p_object_id_ptr,
			Object_referring *p_object_referring_ptr, t_uint p_call_num = 1 );

		void add_ref_and_ref_attrs( t_uint p_object_ident_id,
			Object_referring *p_object_referring_ptr, t_uint p_call_num = 1 );

		void remove_referred_to_object_ident();

		t_uint get_number_of_rtias();

		// ACCESS functions.

		t_uint get_object_ident_id() { return m_obj_ident_id; }
		void set_object_ident_id( t_uint p_object_ident_id )
            { m_obj_ident_id = p_object_ident_id; }

        t_boolean is_relationship_formalized()
            { return  m_object_id != Id::Default && m_obj_ident_id != -1; }

		mc_dbms_List< Referred_to_ident_attr * >
			*get_referred_to_id_attr_coll_ptr();

    DELETE_DOWN_DECL_SUPERTYPE()


	protected:

		Object_referred_to( const Id &p_obj_id, Relationship *p_rel_ptr );

        // R109  -- m_object_id is in the Object_in_relationship class
		t_uint m_obj_ident_id;

	private:

		// HELPING functions

		void delete_referred_to_ident_attrs();
	};


//
// CLASS: Object_referring
//
// DESCRIPTION:
//
//		This defines an S/M object that refers to the attributes in another
//		object (Object_referrred_to). This object actually contains the
//		referential attributes with relationship numbers themselves.
//
// RELATIONSHIP PARTICIPATION:
//
// REMARKS:
//
//		This is a type of Object_in_relationship.
//

class Object_referring : public virtual Object_in_relationship
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		virtual ~Object_referring();

		// IMPLEMENTOR functions

		virtual Object_referring
			*get_object_referring_ptr() { return this; }

		// The following three iterators are used exclusively by Object for
		// navigating to resolved/unresolved Attr_ref_in_object's.

		Attr_ref_in_object *first_fsm_ario();
		Attr_ref_in_object *next_fsm_ario();
		void done_with_fsm_ario();

		Attr_ref_in_object *first_fsm_resolved_ario();
		Attr_ref_in_object *next_fsm_resolved_ario();
		void done_with_fsm_resolved_ario();

		Attr_ref_in_object *first_fsm_unresolved_ario();
		Attr_ref_in_object *next_fsm_unresolved_ario();
		void done_with_fsm_unresolved_ario();

		// ACCESS functions.

		mc_dbms_List< Attr_ref_in_object * > *get_attr_ref_in_obj_coll_ptr();

    DELETE_DOWN_DECL_SUPERTYPE()


	protected:

		Object_referring( const Id &p_obj_id, Relationship *p_rel_ptr );

        //R111 - uses id's in Attr_ref_in_object

		static mc_dbms_Cursor< Attr_ref_in_object *> *fsm_ario_cursor_ptr;
		static mc_dbms_List< Attr_ref_in_object *> *fsm_ario_coll_ptr;

		// HELPING functions

		void delete_attr_ref_in_objects();

	};


//
// CLASS: Referred_to_ident_attr
//
// DESCRIPTION:
//
//		This defines an identifying attribute that another object uses
//		to identify instances in a relationship.
//
// REMARKS:
//
//		Any Object_referred_to instance will contain a collection of these.
//

class Referred_to_ident_attr
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		static Referred_to_ident_attr *create(
			Object_identifier_attribute *p_object_id_attr_ptr,
            const Id &p_rel_id,
            const Id &p_rto_id );

		Referred_to_ident_attr(
			Object_identifier_attribute *p_object_id_attr_ptr,
            const Id &p_rel_id,
            const Id &p_rto_id );

		virtual ~Referred_to_ident_attr();

		// ACCESS functions.

		Id referred_to_object_id() { return object_id_attr_ptr->
			object_id(); }
		Id referred_to_attr_id() { return object_id_attr_ptr->
			attribute_id(); }
		const t_uint &referred_to_object_ident_id() { return
			object_id_attr_ptr->object_identifier_id(); }
		Id relationship_id() { return m_rel_id; }
        Id object_in_relationship_id() { return m_oir_id; }

		Object_identifier_attribute *get_object_id_attr_ptr()
			{ return object_id_attr_ptr; }
		Object_referred_to *get_object_referred_to_ptr();
			
		mc_dbms_Set< Attr_ref_in_object * > *get_attr_ref_in_obj_coll_ptr();

		mc_dbms_segment *get_config_ptr()
			{ return this->get_config_ptr(); }

    	void delete_all_attr_ref_in_objects();

    DELETE_DOWN_DECL_SUBTYPE()


	protected:

		// Maintain pointer to the Object_identifier_attribute we are
		// associated with.   (R110)

		mc_dbms_relationship_1_m(Referred_to_ident_attr,object_id_attr_ptr,Object_identifier_attribute,referred_to_ident_attrs,Object_identifier_attribute *) object_id_attr_ptr;


		// HELPING functions

	private:

		void delete_attr_ref_in_objects();

        // R110    id values for R_RTO
        Id m_obj_id;
        t_uint m_oid_id;
        Id m_rel_id;
        Id m_oir_id;

	};

#endif /* D_RELATIONSHIP_H */

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
