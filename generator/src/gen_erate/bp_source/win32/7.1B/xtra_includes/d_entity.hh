/*========================================================================
 *
 * File:      $RCSfile: d_entity.hh,v $
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

#ifndef D_ENTITY_HH
#define D_ENTITY_HH



#include "u_typdef.hh"
#include "u_id.hh"

#include <u_id.hh>
#include <u_string.hh>
#include <u_string.hh>
#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include "d_typdef.hh"
#include "d_domain.hh"
#include "d_dd_sam.hh"
#include "d_im_oam.hh"

// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class D_entity;
class D_access_path;
class D_communication_path;
class D_external_entity;
class D_external_entity_in_model;
class D_external_entity_event;
class D_external_entity_event_data_item;
class D_external_entity_event_data;

// Also declare classes in other subsystem that we reference, but don't
// include there header file (due to cyclic dependency).

class D_dd_srm_scm_sam;
class D_im_ocm_oam;
class Object;
class Attribute;
class Imported_object;
class D_external_entity;
class D_external_entity_in_model;
class D_sm_event;
class D_core_data_type;
class D_bridge;



//
// CLASS: D_entity
//
// DESCRIPTION: None.
//
// REMARKS: None.
//

class D_entity
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		D_entity();

		virtual ~D_entity();

		// IMPLEMENTOR functions

		void delete_entity();

		t_uint get_number_of_dest_access_paths();

		// find functions

		D_access_path *find_org_access_path( const Id &p_id );
		D_access_path *find_dest_access_path( const Id &p_id );

		D_communication_path *find_org_comm_path( const Id &p_id );
		D_communication_path *find_dest_comm_path( const Id &p_id );

		virtual Object *get_object_ptr() { return 0; }
		virtual Imported_object *get_imported_object_ptr() { return 0; }
		virtual D_external_entity *get_external_entity_ptr() { return 0; }
		virtual D_external_entity_in_model *get_external_entity_in_model_ptr()
			{ return 0; }

		// ACCESS functions. Note that a reference (ie - & ) allows the
		// corresponding field/attribute to be an l-value or r-value.
		// However, prefixing a "const" restricts usage to an r-value,
		// something we want to do when we access a field in another class.

		Domain *get_domain_ptr() { return m_domain_ptr; }
		Id get_id() { return id; }

		void get_org_access_path_coll(mc_dbms_List< D_access_path *>&);
		void get_dest_access_path_coll(mc_dbms_List< D_access_path *>&);

		void get_org_comm_path_coll(mc_dbms_List< D_communication_path *>& );
		void get_dest_comm_path_coll(mc_dbms_List< D_communication_path *>& );

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

      DELETE_DOWN_DECL_SUPERTYPE()



	protected:

		Id id;   // derived classes will initialize this
        Domain * m_domain_ptr;   // only used in destructor

	private:


		// HELPING functions
	};


//
// CLASS: D_access_path
//
// DESCRIPTION: None.
//
// REMARKS: None.
//

class D_access_path
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		static D_access_path *create( D_im_ocm_oam *p_im_ptr, const Id& imp_obj, t_boolean );

		static D_access_path *create( D_im_ocm_oam *p_im_ptr, const Id& imp_obj, t_boolean,
			const Id & p_id );

		D_access_path( D_im_ocm_oam *p_im_ptr, const Id& imp_obj, t_boolean );

		D_access_path( D_im_ocm_oam *p_im_ptr, const Id& imp_obj, t_boolean,
			const Id & p_id );

		~D_access_path();

		// IMPLEMENTOR functions

		void delete_access_path();

		// ACCESS functions. Note that a reference (ie - & ) allows the
		// corresponding field/attribute to be an l-value or r-value.
		// However, prefixing a "const" restricts usage to an r-value,
		// something we want to do when we access a field in another class.

		const Id & get_id() const { return id; }

		int get_entity_data_item_class_type()
			{ return entity_data_item_class_type; }
		void set_entity_data_item_class_type( int p_class_type )
			{ entity_data_item_class_type = p_class_type; }

		void set_orig_sm_id (Id p_id) { orig_sm_id = p_id; }
		Id get_orig_sm_id () { return orig_sm_id; }

		void set_dest_id (Id p_id) { dest_id = p_id; }
		Id get_dest_id () { return dest_id; }

		mc_dbms_List< Id * > *get_entity_data_item_id_coll_ptr()
			{ return entity_data_item_id_coll_ptr; }

		void add_id_to_entity_data_item_coll( const Id &p_id );
		void remove_id_from_entity_data_item_coll( const Id &p_id );
		void remove_all_ids_from_entity_data_item_coll();

		Attribute *find_attribute_by_id( const Id &p_id );

		D_im_ocm_oam *get_im_ocm_oam_ptr() { return im_ocm_oam_ptr; }
		D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
			{ return get_im_ocm_oam_ptr()->get_dd_srm_scm_sam_ptr(); }

		D_entity *get_org_entity_ptr();
		D_entity *get_dest_entity_ptr();

        t_boolean imp_obj_is_orig ()
           { return m_imp_obj_src && m_imp_obj_id != Id::Default; }
        t_boolean imp_obj_is_dest ()
           { return m_imp_obj_src == FALSE && m_imp_obj_id != Id::Default; }
        const Id& get_imported_obj_id()
           { return m_imp_obj_id; }

		Domain *get_domain_ptr()
			{ return get_dd_srm_scm_sam_ptr()->get_domain_ptr(); }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

      DELETE_DOWN_DECL_SUBTYPE()



	private:

		Id id;

		Id orig_sm_id;    // R416
		Id dest_id;       // R417, R421

        t_boolean m_imp_obj_src;
        Id m_imp_obj_id;   // R420, R425

		int entity_data_item_class_type;
        
		mc_dbms_List< Id * > *entity_data_item_id_coll_ptr;   // R418, R422

		mc_dbms_relationship_1_m(D_access_path,im_ocm_oam_ptr,D_im_ocm_oam,access_path_coll,D_im_ocm_oam *) im_ocm_oam_ptr;

		// HELPING functions

		Id_assigner &id_assigner()
			{ return get_im_ocm_oam_ptr()->get_assigners()->access_path_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}
	};


//
// CLASS: D_communication_path
//
// DESCRIPTION: None.
//
// REMARKS: None.
//

class D_communication_path
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		static D_communication_path *create( D_im_ocm_oam *p_im_ptr,
            t_class_type src, t_class_type dst, const Id& imp_obj, t_boolean );

		static D_communication_path *create( D_im_ocm_oam *p_im_ptr,
            t_class_type src, t_class_type dst, const Id& imp_obj, t_boolean,
			const Id & p_id );

		D_communication_path( D_im_ocm_oam *p_im_ptr,
            t_class_type src, t_class_type dst, const Id& imp_obj, t_boolean imp_src );

		D_communication_path( D_im_ocm_oam *p_im_ptr,
            t_class_type src, t_class_type dst, const Id& imp_obj, t_boolean imp_src,
			const Id & p_id );

		~D_communication_path();

		// IMPLEMENTOR functions

		void delete_communication_path();

		// ACCESS functions. Note that a reference (ie - & ) allows the
		// corresponding field/attribute to be an l-value or r-value.
		// However, prefixing a "const" restricts usage to an r-value,
		// something we want to do when we access a field in another class.

		const Id & get_id() const { return id; }

		int get_event_class_type()
			{ return event_class_type; }
		void set_event_class_type( int p_class_type )
			{ event_class_type = p_class_type; }

		mc_dbms_List< Id * > *get_event_id_coll_ptr()
			{ return event_id_coll_ptr; }

		void add_id_to_event_coll( const Id &p_id );
		void remove_id_from_event_coll( const Id &p_id );
		void remove_all_ids_from_event_coll();

		D_sm_event *find_sm_event_by_id( const Id &p_id );
		D_external_entity_event* find_external_entity_event_by_id(
			const Id &p_id );

		D_im_ocm_oam *get_im_ocm_oam_ptr() { return im_ocm_oam_ptr; }
		D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
			{ return im_ocm_oam_ptr->get_dd_srm_scm_sam_ptr(); }

        t_class_type get_org_type()
           { return m_org_type; }

        t_class_type get_dest_type()
           { return m_dest_type; }

        t_boolean imp_obj_is_orig ()
           { return m_imp_obj_src && m_imp_obj_id != Id::Default; }
        t_boolean imp_obj_is_dest ()
           { return m_imp_obj_src == FALSE && m_imp_obj_id != Id::Default; }
        const Id& get_imported_obj_id()
           { return m_imp_obj_id; }

		D_entity *get_org_entity_ptr();
		D_entity *get_dest_entity_ptr();

		Domain *get_domain_ptr()
			{ return get_im_ocm_oam_ptr()->get_domain_ptr(); }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

		void set_orig_sm_or_ee_id (Id p_id) { orig_sm_or_ee_id = p_id; }
		Id get_orig_sm_or_ee_id () { return orig_sm_or_ee_id; }

		void set_dest_sm_or_ee_id (Id p_id) { dest_sm_or_ee_id = p_id; }
		Id get_dest_sm_or_ee_id () { return dest_sm_or_ee_id; }

      DELETE_DOWN_DECL_SUBTYPE()



	private:

		Id id;

		Id orig_sm_or_ee_id;  // R402, R406, R410
		Id dest_sm_or_ee_id;  // R403, R407, R411

        t_class_type m_org_type;    // R401
        t_class_type m_dest_type;   // R401

        t_boolean m_imp_obj_src;
        Id m_imp_obj_id;   // R414, R424

		int event_class_type;

		mc_dbms_List< Id * > *event_id_coll_ptr;   // R405, R409, R413

		mc_dbms_relationship_1_m(D_communication_path,im_ocm_oam_ptr,D_im_ocm_oam,comm_path_coll,D_im_ocm_oam *) im_ocm_oam_ptr;

		// HELPING functions

		Id_assigner &id_assigner()
			{ return get_im_ocm_oam_ptr()->get_assigners()->comm_path_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}
	};


//
// CLASS: D_external_entity
//
// DESCRIPTION: None.
//
// REMARKS: None.
//

class D_external_entity : public D_entity
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		static D_external_entity *create( D_dd_srm_scm_sam *p_dd_ptr );
		static D_external_entity *create( D_dd_srm_scm_sam *p_dd_ptr,
				const Id & p_id );

		D_external_entity( D_dd_srm_scm_sam *p_dd_ptr );
		D_external_entity( D_dd_srm_scm_sam *p_dd_ptr, const Id & p_id );

		~D_external_entity();

		// IMPLEMENTOR functions

        void export();

		void delete_external_entity();

		D_external_entity *get_external_entity_ptr()
                  { return this; }

		// Find functions

		D_external_entity_event *find_external_entity_event( const Id &p_id );
		D_external_entity_event_data_item *find_external_entity_event_data_item(
			const Id &p_id );

		D_bridge *find_bridge_by_id( const Id &p_id ) const;
		D_bridge *find_bridge_by_name( const Description &p_name ) const;

		// ACCESS functions. Note that a reference (ie - & ) allows the
		// corresponding field/attribute to be an l-value or r-value.
		// However, prefixing a "const" restricts usage to an r-value,
		// something we want to do when we access a field in another class.

		Description &external_entity_name() { return name; }
		Description &external_entity_key_letters() { return key_letters; }
		Description &external_entity_desc() { return description; }

        static D_external_entity* get_orphaned_ee_ptr()
           { if ( orphaned_ee_ptr == 0 )
                orphaned_ee_ptr = new D_external_entity( 0, Id::Default );
             return orphaned_ee_ptr; }

		D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
			{ return dd_srm_scm_sam_ptr; }

		mc_dbms_List< D_external_entity_event * > *
			get_external_entity_event_coll_ptr()
			{ return &external_entity_event_coll.getvalue(); }

		mc_dbms_List< D_external_entity_event_data_item * > *
			get_external_entity_event_data_item_coll_ptr()
			{ return &external_entity_event_data_item_coll.getvalue(); }

		mc_dbms_List< D_bridge * > *
			get_bridge_coll_ptr()
			{ return &bridge_coll.getvalue(); }

		const mc_dbms_List< D_bridge * > *
			get_ro_bridge_coll_ptr() const
			{ return ( const mc_dbms_List< D_bridge * > * )
				&bridge_coll.getvalue(); }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

      DELETE_DOWN_DECL_SUBTYPE()



	private:

		Description name;
		Description key_letters;
		Description description;

        static D_external_entity *orphaned_ee_ptr;

		mc_dbms_relationship_m_1(D_external_entity,external_entity_event_coll,D_external_entity_event,external_entity_ptr,mc_dbms_List< D_external_entity_event * >) external_entity_event_coll;

		mc_dbms_relationship_m_1(D_external_entity,bridge_coll,D_bridge,m_external_entity_ptr,mc_dbms_List< D_bridge * >) bridge_coll;

		mc_dbms_relationship_1_m(D_external_entity,dd_srm_scm_sam_ptr,D_dd_srm_scm_sam,external_entity_coll,D_dd_srm_scm_sam *) dd_srm_scm_sam_ptr;

		mc_dbms_relationship_m_1(D_external_entity,external_entity_event_data_item_coll,D_external_entity_event_data_item,external_entity_ptr,mc_dbms_List< D_external_entity_event_data_item * >) external_entity_event_data_item_coll;

		// HELPING functions

		Id_assigner &id_assigner()
			{ return get_dd_srm_scm_sam_ptr()->get_assigners()->ext_entity_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}
	};


//
// CLASS: D_external_entity_in_model
//
// DESCRIPTION: None.
//
// REMARKS: None.
//

class D_external_entity_in_model : public D_entity
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		static D_external_entity_in_model *create( D_im_ocm_oam *p_im_ptr,
			const Id& p_ext_ent_id = Id::Default,
			t_model_type p_model_type = IM_TYPE );

		static D_external_entity_in_model *create( D_im_ocm_oam *p_im_ptr,
			const Id & p_id,
			const Id& p_ext_ent_id = Id::Default,
			t_model_type p_model_type = IM_TYPE );

		D_external_entity_in_model( D_im_ocm_oam *p_im_ptr,
			const Id& p_ext_ent_id = Id::Default,
			t_model_type p_model_type = IM_TYPE );

		D_external_entity_in_model( D_im_ocm_oam *p_im_ptr,
			const Id & p_id,
			const Id& p_ext_ent_id = Id::Default,
			t_model_type p_model_type = IM_TYPE );

		~D_external_entity_in_model();

		// IMPLEMENTOR functions

		void delete_external_entity_in_model();

		D_external_entity_in_model *get_external_entity_in_model_ptr()
			{ return this; }

		// ACCESS functions. Note that a reference (ie - & ) allows the
		// corresponding field/attribute to be an l-value or r-value.
		// However, prefixing a "const" restricts usage to an r-value,
		// something we want to do when we access a field in another class.

		Id get_ee_id() { return m_ee_id; }
		void set_ee_id(const Id& p_ee_id)
           { m_ee_id = p_ee_id; }

		D_im_ocm_oam *get_im_ocm_oam_ptr()
			{ return im_ocm_oam_ptr; }
		D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
			{ return im_ocm_oam_ptr->get_dd_srm_scm_sam_ptr(); }

        static const char *get_orphaned_name()
            { return m_orphaned_name; }

		D_external_entity *get_external_entity_ptr();

		t_model_type get_resident_model_type() const
		    { return (t_model_type) model_type; }
		void set_resident_model_type( t_model_type p_model_type )
		 	{ model_type = p_model_type; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

      DELETE_DOWN_DECL_SUBTYPE()



	private:

        Id m_ee_id;   // R9

		t_int model_type;

        static char * m_orphaned_name;

		mc_dbms_relationship_1_m(D_external_entity_in_model,im_ocm_oam_ptr,D_im_ocm_oam,external_entity_in_model_coll,D_im_ocm_oam *) im_ocm_oam_ptr;

		// HELPING functions

		Id_assigner &id_assigner()
			{ return get_im_ocm_oam_ptr()->get_assigners()->
				ext_entity_in_model_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}
	};


//
// CLASS: D_external_entity_event
//
// DESCRIPTION: None.
//
// REMARKS: None.
//

class D_external_entity_event
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		static D_external_entity_event *create(
			D_external_entity *p_ext_ent_ptr );

		static D_external_entity_event *create(
			D_external_entity *p_ext_ent_ptr, const Id & p_id );

		D_external_entity_event( D_external_entity *p_ext_ent_ptr );
		D_external_entity_event( D_external_entity *p_ext_ent_ptr,
			const Id & p_id );

		void delete_external_entity_event();

		~D_external_entity_event();

		// IMPLEMENTOR functions

		// ACCESS functions. Note that a reference (ie - & ) allows the
		// corresponding field/attribute to be an l-value or r-value.
		// However, prefixing a "const" restricts usage to an r-value,
		// something we want to do when we access a field in another class.

		mc_dbms_Set< D_external_entity_event_data * > *
			get_external_entity_event_data_coll_ptr()
			{ return &external_entity_event_data_coll.getvalue(); }

		D_external_entity_event_data_item *
			find_external_entity_event_data_item_by_id( const Id &p_id );

		void add_event_data_item( const Id &p_id );
		void remove_event_data_item( const Id &p_id );

		const Id & get_id() { return id; }

		Description get_event_label () const
			{ return m_event_label; }
		void set_event_label (Description p_event_label)
			{ m_event_label = p_event_label; }

		Description get_event_meaning () const
			{ return m_event_meaning; }
		void set_event_meaning (Description p_event_meaning)
			{ m_event_meaning = p_event_meaning; }

		int get_event_number () const
			{ return m_event_number; }
		void set_event_number (int p_event_number)
			{ m_event_number = p_event_number; }

		t_boolean get_event_label_is_unique () const
			{ return m_event_label_is_unique; }
		void set_event_label_is_unique (t_boolean p_event_label_is_unique)
			{ m_event_label_is_unique = p_event_label_is_unique; }

		D_external_entity *get_external_entity_ptr() const
			{ return external_entity_ptr; }

		Description get_derived_event_label () const;
		Description get_supplemental_data_string ();

		Domain *get_domain_ptr()
			{ return get_external_entity_ptr()->get_domain_ptr(); }
		D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
			{ return get_external_entity_ptr()->get_dd_srm_scm_sam_ptr(); }

		Description &description() { return _description; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

      DELETE_DOWN_DECL_SUBTYPE()



	private:

		Id id;
		Description _description;

		Description m_event_label;

		Description m_event_meaning;

		int m_event_number;

		t_boolean m_event_label_is_unique;

		mc_dbms_relationship_1_m(D_external_entity_event,external_entity_ptr,D_external_entity,external_entity_event_coll,D_external_entity *) external_entity_ptr;

		mc_dbms_relationship_m_1(D_external_entity_event,external_entity_event_data_coll,D_external_entity_event_data,external_entity_event_ptr,mc_dbms_Set<D_external_entity_event_data*>) external_entity_event_data_coll;

		// HELPING functions

		Id_assigner &id_assigner()
			{ return get_dd_srm_scm_sam_ptr()->get_assigners()->ext_entity_event_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}
	};



//
// CLASS: D_external_entity_event_data_item
//
// DESCRIPTION: None.
//
// REMARKS: None.
//

class D_external_entity_event_data_item
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		static D_external_entity_event_data_item *create(
			D_external_entity *p_ext_ent_ptr );

		static D_external_entity_event_data_item *create(
			D_external_entity *p_ext_ent_ptr, const Id & p_id );

		~D_external_entity_event_data_item();

		// IMPLEMENTOR functions

		void delete_external_entity_event_data_item();

		// ACCESS functions. Note that a reference (ie - & ) allows the
		// corresponding field/attribute to be an l-value or r-value.
		// However, prefixing a "const" restricts usage to an r-value,
		// something we want to do when we access a field in another class.

		mc_dbms_Set< D_external_entity_event_data * > *
			get_external_entity_event_data_coll_ptr ()
			{ return &external_entity_event_data_coll.getvalue (); }

		const Id & get_id() { return id; }
		Description &name() { return _name; }

		Description &description() { return _description; }

		D_external_entity *get_external_entity_ptr()
			{ return external_entity_ptr; }

		Domain *get_domain_ptr()
			{ return get_external_entity_ptr()->get_domain_ptr(); }

		D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
			{ return get_external_entity_ptr()->get_dd_srm_scm_sam_ptr(); }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

		D_core_data_type * get_core_data_type_ptr ();

		void set_data_type_id (Id p_id)
			{ m_data_type_id = p_id; }
		Id get_data_type_id ()
			{ return m_data_type_id; } 

      DELETE_DOWN_DECL_SUBTYPE()



	private:

		Id id;
		Description _name;
		Description _description;
		Id m_data_type_id;

		mc_dbms_relationship_1_m(D_external_entity_event_data_item,external_entity_ptr,D_external_entity,external_entity_event_data_item_coll,D_external_entity *) external_entity_ptr;

		mc_dbms_relationship_m_1(D_external_entity_event_data_item,external_entity_event_data_coll,D_external_entity_event_data,external_entity_event_data_item_ptr,mc_dbms_Set<D_external_entity_event_data*>) external_entity_event_data_coll;


		// HELPING functions

		Id_assigner &id_assigner()
			{ return get_dd_srm_scm_sam_ptr()->get_assigners()->ext_entity_edi_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}

		D_external_entity_event_data_item( D_external_entity *p_ext_ent_ptr );
		D_external_entity_event_data_item( D_external_entity *p_ext_ent_ptr,
			const Id & p_id );
	};

//
// CLASS: D_external_entity_event_data
//
// DESCRIPTION: None.
//
// REMARKS: None.
//

class D_external_entity_event_data
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		static D_external_entity_event_data *create(
			D_external_entity_event *p_ext_ent_evt_ptr,
			D_external_entity_event_data_item *p_evt_di_ptr );

		~D_external_entity_event_data();

		// IMPLEMENTOR functions

		D_external_entity_event *get_external_entity_event_ptr() const
			{ return external_entity_event_ptr; }

		D_external_entity_event_data_item *
			get_external_entity_event_data_item_ptr() const
			{ return external_entity_event_data_item_ptr; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

      DELETE_DOWN_DECL_SUBTYPE()



	private:

		mc_dbms_relationship_1_m(D_external_entity_event_data,external_entity_event_data_item_ptr,D_external_entity_event_data_item,external_entity_event_data_coll,D_external_entity_event_data_item*) external_entity_event_data_item_ptr;
 
		mc_dbms_relationship_1_m(D_external_entity_event_data,external_entity_event_ptr,D_external_entity_event,external_entity_event_data_coll,D_external_entity_event*) external_entity_event_ptr;



		// HELPING functions

		D_external_entity_event_data (
			D_external_entity_event * p_ee_evt_ptr,
			D_external_entity_event_data_item * p_evt_di_ptr );
	};


#endif /* D_ENTITY_HH */
