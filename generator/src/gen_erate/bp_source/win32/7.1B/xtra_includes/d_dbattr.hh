/*========================================================================
 *
 * File:      $RCSfile: d_dbattr.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:04 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_DERIVED_BASE_ATTR_HH
#define D_DERIVED_BASE_ATTR_HH


// Include those header files that are DIRECTLY needed by this one.


#include <d_battr.hh>

class New_base_attribute;

/*
#include <u_id.hh>
#include <u_string.hh>
#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include "u_typdef.hh"
#include "d_domain.hh"
#include "d_entity.hh"
#include "d_im_oam.hh"
#include <d_exespec.hh>
#include <d_typdef.hh>

// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class Object;
class Imported_object;
class Attribute;
class Object_identifier;
class Object_identifier_attribute;
class Base_attribute;
class Referential_attribute;
class Derived_base_attribute;
class New_base_attribute;
class Attr_ref_in_object;

// Also declare classes in other subsystem that we reference, but don't
// include there header file (due to cyclic dependency).

// from Data Domain Subsystem

// from Relationship Subsystem

class Relationship;
class Object_in_relationship;
class Object_referred_to;
class Object_referring;
class Referred_to_ident_attr;

// from Associative Relationship Subsystem

class One_side_ident_attr;
class Other_side_ident_attr;
class Associator_ident_attr;
class Associated_ident_attr;
class Object_as_associator;
class Object_as_ass_one_side;
class Object_as_ass_other_side;

class D_subsys;
class D_transformer;
class D_im_ocm_oam;
class D_cp_sm_spt_pm;

class IE_export_sql;
*/


//
// CLASS: Derived_base_attribute
//
// DESCRIPTION:
//
//		This defines the derived base attribute, which is a subtype of
//		Attribute and is derived, not a root/base.
//
// RELATIONSHIP PARTICIPATION:
//
//		R5 - Inheritance with Derived_base_attribute being a subtype of
//			 Base_attribute.
//		R6 - Is the attribute that has a relationship with the deriving process.
//
// REMARKS:
//
//		An example of a derived attribute would be point code, derived from
//		network, cluster, and member attributes.
//

class Derived_base_attribute : public Base_attribute
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		Derived_base_attribute( Object *p_object_ptr, const vchar *p_root = Description::null_string,
			t_prefix_derive_mode p_prefix_derive_mode = USE_NO_PREFIX,
			const vchar *p_prefix = Description::null_string,
	  	const Description & p_description = Description::Default );

		Derived_base_attribute( Object *p_object_ptr, const Id &p_id,
			const vchar *p_root = Description::null_string,
			t_prefix_derive_mode p_prefix_derive_mode = USE_NO_PREFIX,
			const vchar *p_prefix = Description::null_string,
	  	const Description & p_description = Description::Default );

		~Derived_base_attribute () {}

		// IMPLEMENTOR functions

		New_base_attribute *migrate_to_new_base_attr();

		// ACCESS functions

		virtual Derived_base_attribute *get_derived_base_attribute_ptr()
			{ return this; }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		// HELPING functions
	};


#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
