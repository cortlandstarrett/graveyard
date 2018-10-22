/*========================================================================
 *
 * File:      $RCSfile: d_object.hh,v $
 * Version:   $Revision: 1.9 $
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

#ifndef D_OBJECT_HH
#define D_OBJECT_HH

// CONTENTS:
//
//		This file describes the C++ classes relating to the Object Subsystem.
//
// REMARKS:
//
//		We will use Mentor Graphics MC_DBMS as the
//		object-oriented database. Consequently, MC_DBMS primitives will appear
//		within these class definitions. Additionally, we will use MC_DBMS's
//		Library Interface (LI) with parameterized types/class templates.
//


// Include those header files that are DIRECTLY needed by this one.


#include <d_entity.hh>
#include <u_id.hh>
#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

class Attr_ref_in_object;
class Object_identifier;

class Referential_attribute;
class New_base_attribute;
class D_transformer;
class D_cp_sm_spt_pm;
class Relationship;

class IE_export_sql;

const unsigned int	NUM_OBJECT_IDENTIFIERS 		= 		3;

//
// CLASS: Object
//
// DESCRIPTION:
//
//		This defines the basic "object".
//
// RELATIONSHIP PARTICIPATION:
//
//		R1 - One-side of 1:cM relationship with Attribute.
//		R2 - One-side of 1:cM relationship with Object_identifier
//		R101 - One endpoint of the 1-M:M associative object
//			   Object_in_relationship with the other end being Relationship.
//
// REMARKS:
//
//		None.
//

class Object : public D_entity
	{
	public:

		// The following data and member functions are needed by the
		// first/next_/resolved/unresolved_attr_ref_in_object()
		// functions.

		enum t_fsm_attr_state { IDLE, ACTIVE };

		enum t_fsm_attr_evt { EVT_GET_FIRST_REFERRING_OIR,
			EVT_GET_FIRST_ATTR_FROM_REFERRING_OIR,
			EVT_GET_NEXT_ATTR_FROM_REFERRING_OIR,
			EVT_GET_NEXT_REFERRING_OIR };
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		static void init();

		Object( D_im_ocm_oam *p_im_ptr,
			const vchar *p_name = Description::null_string, t_uint p_number = 0,
			const vchar *p_key_letters = Description::null_string, 
	  	const Description & p_description = Description::Default );

		Object( D_im_ocm_oam *p_im_ptr, const Id & p_id,
			const vchar *p_name = Description::null_string, t_uint p_number = 0,
			const vchar *p_key_letters = Description::null_string, 
	  	const Description & p_description = Description::Default );

		Object( D_im_ocm_oam *p_im_ptr,
			const Description &p_name, t_uint p_number = 0 );

		Object( D_im_ocm_oam *p_im_ptr,
			const Description &p_name, t_uint p_number, const Description &p_key_letters);

		Object( D_im_ocm_oam *p_im_ptr,
			const Description &p_name, t_uint p_number,
			const Description &p_key_letters, const Description &p_description );

		// This constructor is for an orphaned object that belongs to nothing.

		Object( const vchar *p_name = Description::null_string, t_uint p_number = 0,
				const vchar *p_key_letters = Description::null_string, 
  	  	const Description & p_description = Description::Default );

		~Object();

		// IMPLEMENTOR functions

		New_base_attribute *create_new_base_attr();
		New_base_attribute *create_new_base_attr( const Id & p_id );
		Referential_attribute *create_referential_attr();
		Referential_attribute *create_referential_attr( const Id & p_id );

		// delete_object deletes this Object and any affected relationships
		// it is a part of.

        void export(IE_export_sql * p_export_ptr);

        t_boolean can_delete_affected_relationships(Description &p_warning_msg);
        void delete_all_affected_relationships();

		void delete_object();

		void copy_object();
		Id paste_object(D_im_ocm_oam*);

		t_uint get_number_of_attributes();
		t_uint get_number_of_object_in_relationships();
		t_uint get_number_of_imported_objects();

        t_boolean verify_all_imported_objects_rw( Description & );

		// Iterator and find functions

		// for Attribute set

		Attribute *find_attribute( const Id &p_id );

		// for D_transformer set

		D_transformer *find_transformer_by_id( const Id &p_id ) const;
		D_transformer *find_transformer_by_name( const Description &p_name ) const;

		// for Object_identifier set

		Object_identifier *find_object_identifier( t_uint p_id_id );
		Imported_object *find_imported_object( const Id &p_id );

		// for Object_in_relationship set

		Object_in_relationship *find_object_in_relationship(
			const Id &p_oir_id );

		Object_in_relationship *find_first_oir_by_rel( const Id &p_rel_id );

		// Navigational iterator to return Attr_ref_in_object
		// instances via Relationships.

		Attr_ref_in_object *first_attr_ref_in_object();
		Attr_ref_in_object *next_attr_ref_in_object();
		void done_with_attr_ref_in_object();

		Attr_ref_in_object *first_unresolved_attr_ref_in_object();
		Attr_ref_in_object *next_unresolved_attr_ref_in_object();
		void done_with_unresolved_attr_ref_in_object();

		Attr_ref_in_object *first_resolved_attr_ref_in_object();
		Attr_ref_in_object *next_resolved_attr_ref_in_object();
		void done_with_resolved_attr_ref_in_object();

		// The following are used to manipulate the ordering of the Attributes.
		// They will probably be used by the "Presentation Domain" to manipulate
		// attributes in a consistent manner with which they appear on the user
		// screen.

		// remove_all_attributes removes all existing attributes and results
		// in an empty attribute list. Can be used prior to re-ordering using
		// following functions. It is IMPORTANT for the User to make sure
		// they already have pointers to these instances or else they will
		// be lost FOREVER.

		void remove_all_attributes();

		// remove_attribute removes the given attribute from the list, but
		// does not delete the Attribute instance.

		void remove_attr_from_list( Attribute *p_attr_ptr );

		// add attribute to end of list

		void add_attr_to_end_of_list( Attribute *p_attr_ptr );

		void delete_ternary_object_in_rels( Relationship *p_rel_ptr, t_boolean p_delete_all );

		// ACCESS functions. Note that a reference (ie - & ) allows the
		// corresponding field/attribute to be an l-value or r-value.
		// However, prefixing a "const" restricts usage to an r-value,
		// something we want to do when we access a field in another class.

		const Id & get_object_id() const { return id; }
		Description get_object_name() const { return name; }
		const vchar *get_object_name_char_ptr() const { return name.char_ptr(); }
		void set_object_name( const vchar *p_char_ptr );
		void set_object_name( const Description &p_string );
		unsigned int get_object_number() const { return number; }
		void set_object_number( unsigned int p_num )
			{ number = p_num; }
		Description &object_key_letters() { return key_letters; }
		Description &object_description() { return description; }

        t_boolean search_supertype_for_subtype( Object* p_obj_ptr );
        Relationship *search_supertype_for_relationship( Object* p_obj_ptr );
        void get_active_subtype_list( mc_dbms_List<D_sm_spt_pm*> &sm_references );

		virtual Object *get_object_ptr() { return this; }

		static Object *get_orphaned_object_ptr()
			{ return orphaned_object_ptr; }
		 t_boolean is_orphaned() const
			{ return( this == orphaned_object_ptr ? TRUE : FALSE ); }

		Id get_instance_sm_spt_pm_id() const { return instance_sm_spt_pm_id; }
		void set_instance_sm_spt_pm_id( Id p_id )
			{ instance_sm_spt_pm_id = p_id; }
		Id get_assigner_sm_spt_pm_id() const { return assigner_sm_spt_pm_id; }
		void set_assigner_sm_spt_pm_id( Id p_id )
			{ assigner_sm_spt_pm_id = p_id; }

		void create_current_state_attribute ();
		t_boolean delete_current_state_attribute ();

		Domain *get_domain_ptr() const
			{ return (im_ocm_oam_ptr ? im_ocm_oam_ptr->get_domain_ptr() : 0); }
		Domain_id get_domain_id() const
			{ return get_domain_ptr()->get_domain_id(); }
		mc_dbms_database *get_db_ptr() const
			{ return get_domain_ptr()->get_db_ptr(); }

		D_sm_spt_pm *get_assigner_sm_spt_pm_ptr() const
			{
			return get_domain_ptr()->get_current_sm_spt_pm_by_id(
				get_assigner_sm_spt_pm_id() );
			}
		D_sm_spt_pm *get_instance_sm_spt_pm_ptr() const
			{
			return get_domain_ptr()->get_current_sm_spt_pm_by_id(
				get_instance_sm_spt_pm_id() );
			}

		void set_assigner_cp_sm_spt_pm_ptr(D_cp_sm_spt_pm *p_cp_ptr)
			{
			cp_assigner_cp_sm_spt_pm = p_cp_ptr;
			}
		void set_instance_cp_sm_spt_pm_ptr(D_cp_sm_spt_pm *p_cp_ptr)
			{
			cp_instance_cp_sm_spt_pm = p_cp_ptr;
			}

		D_cp_sm_spt_pm *get_assigner_cp_sm_spt_pm_ptr() const
			{
			return cp_assigner_cp_sm_spt_pm;
			}
		D_cp_sm_spt_pm *get_instance_cp_sm_spt_pm_ptr() const
			{
			return cp_instance_cp_sm_spt_pm;
			}
    D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
      { return get_im_ocm_oam_ptr()->get_dd_srm_scm_sam_ptr(); }

		D_im_ocm_oam *get_im_ocm_oam_ptr() const
			{ return im_ocm_oam_ptr; }
		D_subsys *get_dd_subsystem_ptr() const
			{ return get_im_ocm_oam_ptr()->get_dd_subsystem_ptr(); }
		Subsystem *get_im_subsystem_ptr() const
			{ return get_im_ocm_oam_ptr()->get_im_subsystem_ptr(); }

		// return pointers to contained collections

		mc_dbms_List< Attribute * > *get_attr_coll_ptr()
			{ return &attributes.getvalue(); }

		mc_dbms_List< Object_identifier * > *get_obj_id_coll_ptr()
			{ return &object_identifiers.getvalue(); }

		mc_dbms_List< Imported_object * > *get_imported_object_coll_ptr();

		mc_dbms_Set< Object_in_relationship *> *get_obj_in_rel_coll_ptr();

		mc_dbms_List< D_transformer * > *get_transformer_coll_ptr()
			{ return &transformers.getvalue(); }

		const mc_dbms_List< D_transformer * > *
			get_ro_transformer_coll_ptr() const
				{ return ( const mc_dbms_List< D_transformer * > * )
					&transformers.getvalue(); }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

		void set_ocm_instance_derived (t_boolean p_value)
			{ ocm_instance_derived = p_value; }
		t_boolean get_ocm_instance_derived ()
			{ return ocm_instance_derived; }

		void set_ocm_assigner_derived (t_boolean p_value)
			{ ocm_assigner_derived = p_value; }
		t_boolean get_ocm_assigner_derived ()
			{ return ocm_assigner_derived; }

		void set_oam_instance_derived (t_boolean p_value)
			{ oam_instance_derived = p_value; }
		t_boolean get_oam_instance_derived ()
			{ return oam_instance_derived; }

		void set_oam_assigner_derived (t_boolean p_value)
			{ oam_assigner_derived = p_value; }
		t_boolean get_oam_assigner_derived ()
			{ return ocm_assigner_derived; }

		void * get_audit_ptr() { return audit_ptr; }
		void set_audit_ptr( void * p_audit_ptr )
			{ audit_ptr = p_audit_ptr; }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		Description name;
		unsigned int number;
		Description key_letters;
		Description description;

		void * audit_ptr;	// for auditing; use as handle/wrapper to data

		D_cp_sm_spt_pm* cp_assigner_cp_sm_spt_pm;
		D_cp_sm_spt_pm* cp_instance_cp_sm_spt_pm;

		static Object *orphaned_object_ptr;

		Id instance_sm_spt_pm_id;
		Id assigner_sm_spt_pm_id;

		t_boolean ocm_instance_derived;
		t_boolean ocm_assigner_derived;
		t_boolean oam_instance_derived;
		t_boolean oam_assigner_derived;

		mc_dbms_relationship_1_m(Object,im_ocm_oam_ptr,D_im_ocm_oam,objects,D_im_ocm_oam *) im_ocm_oam_ptr;

		mc_dbms_relationship_m_1(Object,attributes,Attribute,object_ptr,mc_dbms_List< Attribute * >) attributes;

		mc_dbms_relationship_m_1(Object,object_identifiers,Object_identifier,object_ptr,mc_dbms_List< Object_identifier * >) object_identifiers;

		mc_dbms_relationship_m_1(Object,transformers,D_transformer,m_object_ptr,mc_dbms_List< D_transformer * >) transformers;

		// R202 is implemented by the data member Object_in_relationship.m_object_id

		// We need a transient collection for iterating thru the Relationships
		// this Object participates in.

		static mc_dbms_Cursor< Relationship *> *rel_cursor_ptr;
		static mc_dbms_Set< Relationship * > *relationships_ptr;

		// HELPING functions

		Id_assigner &id_assigner()
			{ return get_im_ocm_oam_ptr()->get_assigners()->object_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}

		void construct_init();	// common constructor init function

		void delete_affected_relationships();

		// delete all contained instances in these collections

		void delete_attributes();
		void delete_object_ids();
		void delete_object_in_relationships();
		void delete_relationships();
		void delete_transformers();

		// Navigational iterator to return Relationship instances via
		// Object_in_relationships. The Relationships will be unique( even
		// though you can have a Relationship to yourself).

		Relationship *first_relationship();
		Relationship *next_relationship();
		void done_with_relationship();

		Object_in_relationship *first_fsm_oir();
		Object_in_relationship *next_fsm_oir();
		void done_with_fsm_oir();

		// The four variables are used in resolving/navigating to the
		// Attr_ref_in_objects associated with this Object. We use a
		// finite-state-machine(fsm) to do this ( thus the prefix ).

		static t_fsm_attr_state fsm_attr_state;
		static Object_in_relationship *fsm_oir_ptr;
		static mc_dbms_Cursor< Object_in_relationship *> *fsm_oir_cursor_ptr;
		static mc_dbms_Set< Object_in_relationship *> *fsm_oir_coll_ptr;

		Attr_ref_in_object *all_attr_fsm( t_fsm_attr_evt
			p_all_attr_evt );

		Attr_ref_in_object *resolved_attr_fsm( t_fsm_attr_evt
			p_resolved_attr_evt );

		Attr_ref_in_object *unresolved_attr_fsm( t_fsm_attr_evt
			p_unresolved_attr_evt );
	};
	
#define FOR_ALL_ATTRIBUTES( object_ptr, attr_ptr, cursor_name )	\
	mc_dbms_Cursor< Attribute * > cursor_name( *object_ptr->get_attr_coll_ptr(), \
		mc_dbms_cursor::safe ); \
	for ( attr_ptr = cursor_name.first(); \
		  attr_ptr != 0;	\
		  attr_ptr = cursor_name.next() )	

//
// CLASS: Imported_object
//
// DESCRIPTION: This defines an Object that resides in another Subsystem, but
//	we refer to via a spanning relationship.
//
// REMARKS: None.
//

class Imported_object : public D_entity
	{
	friend class Object;   // initialize UNASSIGNED_IMPORTED_OBJECT_NAME
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Imported_object( D_im_ocm_oam *p_im_ptr,
                     const Id &p_obj_id,
                     t_model_type p_model_type = IM_TYPE );

		Imported_object( D_im_ocm_oam *p_im_ptr,
                     const Id &p_obj_id,
                     const Id & p_imp_obj_id,
                     t_model_type p_model_type = IM_TYPE );

		virtual ~Imported_object();

		// IMPLEMENTOR functions

        void export(IE_export_sql * p_export_ptr);
		void delete_imported_object(t_boolean p_delete_all);

        t_boolean can_delete_affected_relationships(Description &p_warning_msg);

		void copy_imported_object();
		Id paste_imported_object(D_im_ocm_oam*);

		virtual Imported_object *get_imported_object_ptr() { return this; }

		t_uint get_number_of_object_in_relationships();

		Object_in_relationship *find_object_in_relationship( const Id &p_id );

		// ACCESS functions. Note that a reference (ie - & ) allows the
		// corresponding field/attribute to be an l-value or r-value.
		// However, prefixing a "const" restricts usage to an r-value,
		// something we want to do when we access a field in another class.

        Id get_assigned_obj_id() { return obj_id; }

		// IMPORTANT: Even though we are calling this the "assigned" object
		// pointer, it may not be assigned and the User must check to see
		// if the returned value is 0. The subsequent member functions
		// return the read-only values of the Object attributes if assigned
		// and some null/default value otherwise; thus the User does NOT
		// have to check the get_assigned_object_ptr() each time he/she
		// wants to access the Object data.
		
		Object *get_assigned_object_ptr();
		void set_assigned_object_ptr( Object *p_object_ptr );

		static const Description& get_orphaned_imported_object_name();
		const Description& get_unknown_imported_object_name();

		t_model_type get_resident_model_type() const
			{ return (t_model_type) model_type; }
		void set_resident_model_type( t_model_type p_model_type )
			{ model_type = p_model_type; }

		D_im_ocm_oam *get_im_ocm_oam_ptr()
			{ return im_ocm_oam_ptr; }
		D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
			{ return get_im_ocm_oam_ptr()->get_dd_srm_scm_sam_ptr(); }

		mc_dbms_List< Object_in_relationship *> *get_obj_in_rel_coll_ptr()
			{ return &object_in_relationships.getvalue(); }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		Id obj_id;    // Implements R101 of OOA of OOA

		t_int model_type;

		static Description UNASSIGNED_IMPORTED_OBJECT_NAME;
		static Description ORPHANED_IMPORTED_OBJECT_NAME;
		static Description UNASSIGNED_IMPORTED_CLASS_NAME;
		static Description ORPHANED_IMPORTED_CLASS_NAME;
		static const t_uint UNASSIGNED_IMPORTED_OBJECT_NUMBER;  

		mc_dbms_relationship_1_m(Imported_object,im_ocm_oam_ptr,D_im_ocm_oam,imported_objects,D_im_ocm_oam *) im_ocm_oam_ptr;

		mc_dbms_relationship_m_1(Imported_object,object_in_relationships,Object_in_relationship,imported_object_ptr,mc_dbms_List< Object_in_relationship *>) object_in_relationships;

		// Helping functions

		Id_assigner &id_assigner()
			{ return get_im_ocm_oam_ptr()->get_assigners()->imported_object_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}
	};


#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
