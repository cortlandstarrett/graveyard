/*========================================================================
 *
 * File:      $RCSfile: d_nbattr.hh,v $
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

#ifndef D_NEW_BASE_ATTRIBUTE_HH
#define D_NEW_BASE_ATTRIBUTE_HH

// Include those header files that are DIRECTLY needed by this one.


#include <d_battr.hh>

class Referential_attribute;
class Derived_base_attribute;


//
// CLASS: New_base_attribute
//
// DESCRIPTION:
//
//		This defines a new base attribute, which is basically a "stand-alone"
//		base attribute. It is a subtype of Base_attribute.
//
// RELATIONSHIP PARTICIPATION:
//
//		R5 - Inheritance with New_base_attribute being a subtype of
//			 Base_attribute.
//
// REMARKS:
//
//		This class currently has the same behavior as its supertype,
//		Base_attribute.
//

class New_base_attribute : public Base_attribute
	{
	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		New_base_attribute( Object *p_object_ptr, const vchar *p_root = Description::null_string,
			t_prefix_derive_mode p_prefix_derive_mode = USE_NO_PREFIX,
			const vchar *p_prefix = Description::null_string,
	  	const Description & p_description = Description::Default );

		New_base_attribute( Object *p_object_ptr, const Id &p_id,
			const vchar *p_root = Description::null_string,
			t_prefix_derive_mode p_prefix_derive_mode = USE_NO_PREFIX,
			const vchar *p_prefix = Description::null_string,
	  	const Description & p_description = Description::Default );

		~New_base_attribute () {}

		// IMPLEMENTOR functions

		Referential_attribute *migrate_to_ref_attr();
		Derived_base_attribute *migrate_to_derived_base_attr();

		// ACCESS functions

		virtual New_base_attribute *get_new_base_attribute_ptr()
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
