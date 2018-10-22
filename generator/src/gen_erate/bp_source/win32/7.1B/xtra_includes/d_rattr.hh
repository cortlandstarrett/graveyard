/*========================================================================
 *
 * File:      $RCSfile: d_rattr.hh,v $
 * Version:   $Revision: 1.9 $
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

#ifndef D_REF_ATTR_HH
#define D_REF_ATTR_HH


// Include those header files that are DIRECTLY needed by this one.


#include <d_attr.hh>

//
// CLASS: Referential_attribute
//
// DESCRIPTION:
//
//		This defines the referential attribute, which is a subtype of Attribute.
//
// RELATIONSHIP PARTICIPATION:
//
//		R4 - Inheritance with Referential_attribute being a subtype of the
//			 supertype Attribute.
//		R11 - 1-side of 1:M relationship with Attr_ref_in_object.
//		R14 - Many-side of 1:cM relationship with Base_attribute.
//
// REMARKS:
//
//		None.
//

class visited_class
{
public:
    t_boolean visited_name;
    t_boolean visited_base;
    Base_attribute *navigate_base_attr_ptr;
    visited_class() { visited_name = FALSE; visited_base = FALSE; navigate_base_attr_ptr = 0; }
	static mc_dbms_typespec *get_mc_dbms_typespec();
};

class Referential_attribute : public Attribute
	{
	friend Domain;				// for base attribute navigation
	friend Attr_ref_in_object;	// same

	public:
		enum t_root_derive_mode { USE_LOCAL_ROOT, USE_REFERRED_TO_ROOT,
			USE_REFERRED_TO_ATTR_NAME };

		enum t_base_attr_navigate_error_type { NAV_NO_ERROR, NAV_NO_BASE,
			NAV_MORE_THAN_ONE_BASE, NAV_ORPHANED };

		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Referential_attribute ( Object *p_object_ptr,
			t_prefix_derive_mode p_prefix_derive_mode = USE_REFERRED_TO_PREFIX,
			const vchar *p_prefix = Description::null_string,
			t_root_derive_mode p_root_derive_mode = USE_REFERRED_TO_ROOT,
			const vchar *p_root = Description::null_string, 
	  	const Description & p_description = Description::Default );

		Referential_attribute ( Object *p_object_ptr, const Id &p_id,
			t_prefix_derive_mode p_prefix_derive_mode = USE_REFERRED_TO_PREFIX,
			const vchar *p_prefix = Description::null_string,
			t_root_derive_mode p_root_derive_mode = USE_REFERRED_TO_ROOT,
			const vchar *p_root = Description::null_string, 
	  	const Description & p_description = Description::Default );

		virtual ~Referential_attribute();

		// IMPLEMENTOR functions

		virtual Base_attribute *navigate_to_base_attr();
		virtual Base_attribute *global_navigate_to_base_attr();

		New_base_attribute *migrate_to_new_base_attr();

		Attribute *get_referred_to_attr();

		t_uint get_number_of_attr_ref_in_objects();

		// Audit to determine if attr refs navigate to same base.

		t_boolean attr_ref_in_objects_navigate_to_same_base();

		// remove_all_attr_ref_in_objects removes all existing
		// attr_ref_in_objects and results in an empty attr_ref_in_object
		// list. Can be used prior to re-ordering using following functions.
		// It is IMPORTANT for the User to make sure they already have pointers
		// to these instances or else they will be lost FOREVER.

		void remove_all_attr_ref_in_objects();

		// remove_attr_ref_in_object_from_list removes the given
		// Attr_ref_in_object from the list, but does not delete it.

		void remove_attr_ref_in_object_from_list(
			Attr_ref_in_object *p_ario_ptr );

		// add Attr_ref_in_object to end of list

		void add_attr_ref_in_object_to_end_of_list(
			Attr_ref_in_object *p_ario_ptr );

		Attr_ref_in_object *find_attr_ref_in_object( const Id &p_id );

		// ACCESS functions

		virtual Description get_prefix();
		virtual void set_prefix( const vchar *p_prefix )
			{ prefix_derive_mode = USE_LOCAL_PREFIX; prefix = p_prefix; }

		t_root_derive_mode get_root_derive_mode()
			{ return root_derive_mode; }
		void set_root_derive_mode( t_root_derive_mode p_root_derive_mode )
			{ root_derive_mode = p_root_derive_mode; }

		virtual Description get_root();
		virtual void set_root( const vchar *p_root )
			{ root_derive_mode = USE_LOCAL_ROOT; root = p_root; }

		Attr_ref_in_object *get_primary_ario_ptr()
			{ return attr_ref_in_objects.retrieve_first(); }

		virtual Referential_attribute *get_referential_attribute_ptr()
			{ return this; }

		mc_dbms_List< Attr_ref_in_object * > *get_attr_ref_in_obj_coll_ptr()
			{ return &attr_ref_in_objects.getvalue(); }
  
    // The following audit function makes sure all referential attributes
    // in this domain navigate to a base attribute. TRUE is returned
    // if everything cool and legitimate; FALSE if at least one
    // referential attribute doesn't navigate to a base. If FALSE is
    // returned, then the passed in p_err_msg String specifies what the
    // exact error/problem is.
  
    static t_boolean navigate_for_all_referential_attrs( D_dd_srm_scm_sam *,
                                                         Description &p_err_msg );

    DELETE_DOWN_DECL_SUBTYPE()

	private:

		t_root_derive_mode root_derive_mode;

		static const vchar *const PREFIX_LOOP_STRING;
		static const vchar *const ROOT_LOOP_STRING;

		// Following used for global base attribute navigation.

		static void clear_all_already_visited_name_base(D_dd_srm_scm_sam *p_dd_ptr);
		static void clear_all_already_visited_base(D_dd_srm_scm_sam *p_dd_ptr);

		static void clear_base_attr_navigate_error_type()
			{ base_attr_navigate_error_type = NAV_NO_ERROR; }

        visited_class* get_visited_ptr() const;

		t_boolean already_visited_name() const;
		void set_already_visited_name();
		void clear_already_visited_name();
		void clear_already_visited_name_base();

		t_boolean already_visited_base() const;
		void set_already_visited_base();
		void clear_already_visited_base();


		t_boolean already_navigated_to_base() const ;
		void clear_already_navigated_to_base();

		Base_attribute *get_navigate_base_attr_ptr();
		void set_navigate_base_attr_ptr(Base_attribute *);

		static t_base_attr_navigate_error_type
			get_base_attr_navigate_error_type()
			{ return( base_attr_navigate_error_type ); }

		mc_dbms_Cursor< Attr_ref_in_object * >  *navigate_ario_cursor_ptr;

		static t_base_attr_navigate_error_type base_attr_navigate_error_type;

		// "first_visited_navigate_ptr" is for controlling TRACE and ERROR
		// logging when navigating to base attribute.

		static Referential_attribute *first_visited_navigate_ptr;

		// For R11, maintain set of Attr_ref_in_object instances that
		// this particular Referential_attribute refers to. In other words,
		// a given referential attribute may participate in many relationships.

		mc_dbms_relationship_m_1(Referential_attribute,attr_ref_in_objects,Attr_ref_in_object,ref_attr_ptr,mc_dbms_List< Attr_ref_in_object * >) attr_ref_in_objects;

		// HELPING functions

		Attr_ref_in_object *first_nav_attr_ref_in_object();
		Attr_ref_in_object *next_nav_attr_ref_in_object();
		void done_with_nav_attr_ref_in_object();

		void delete_attr_ref_in_objects();
	};


#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
