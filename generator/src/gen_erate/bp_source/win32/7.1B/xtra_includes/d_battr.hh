/*========================================================================
 *
 * File:      $RCSfile: d_battr.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:14 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_BASE_ATTRIBUTE_HH
#define D_BASE_ATTRIBUTE_HH


// Include those header files that are DIRECTLY needed by this one.


#include <d_attr.hh>
#include <d_exespec.hh>

class Derived_base_attribute;
class New_base_attribute;

//
// CLASS: Base_attribute
//
// DESCRIPTION:
//
//		This defines the base attribute, which is a subtype of Attribute.
//
// RELATIONSHIP PARTICIPATION:
//
//		R4 - Inheritance with Base_attribute being a subtype of the supertype
//			 Attribute.
//		R5 - Inheritance with Base_attribute being the supertype.
//		R14 - One side of 1:cM relationship with Referential_attribute
//
// REMARKS:
//
//		This class serves as the base class for Derived_base_attribute and
//		New_base_attribute.
//

class Base_attribute : public Attribute, public D_execution_spec
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		virtual ~Base_attribute();

		// IMPLEMENTOR functions

		virtual Base_attribute *navigate_to_base_attr() { return this; }
		virtual Base_attribute *global_navigate_to_base_attr() { return this; }

		// ACCESS functions

		virtual Description get_prefix()
			{
			if ( prefix_derive_mode == USE_LOCAL_PREFIX )
				return prefix;
			else
				return Description::null_string;
			}

		virtual void set_prefix( const vchar *p_prefix )
			{ prefix_derive_mode = USE_LOCAL_PREFIX; prefix = p_prefix; }

		virtual Description get_root() { return root; }
		virtual void set_root( const vchar *p_root ) { root = p_root; }

		virtual Base_attribute *get_base_attribute_ptr() { return this; }
		virtual Derived_base_attribute *get_derived_base_attribute_ptr()
			{ return 0; }
		virtual New_base_attribute *get_new_base_attribute_ptr()
			{ return 0; }

	Base_attribute* get_attribute_ptr ()
	    { return this; }

	int get_spec_type ();   // implemented in a_bush.cc to avoid excessive #includes

	D_data_type* get_return_type ();

    DELETE_DOWN_DECL_SUPERTYPE()


	protected:

		Base_attribute( Object *p_object_ptr, const vchar *p_root,
			t_prefix_derive_mode p_prefix_derive_mode = USE_NO_PREFIX,
			const vchar *p_prefix = Description::null_string, 
	  	const Description & p_description = Description::Default );

		Base_attribute( Object *p_object_ptr, const Id &p_id,
			const vchar *p_root,
			t_prefix_derive_mode p_prefix_derive_mode = USE_NO_PREFIX,
			const vchar *p_prefix = Description::null_string, 
	  	const Description & p_description = Description::Default );

		// HELPING functions

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
