/*========================================================================
 *
 * File:      $RCSfile: d_ario.hh,v $
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

#ifndef D_ATTR_REF_IN_OBJ_HH
#define D_ATTR_REF_IN_OBJ_HH

// Include those header files that are DIRECTLY needed by this one.


#include <d_oida.hh>
#include <d_rattr.hh>
#include <d_rel.hh>


//
// CLASS: Attr_ref_in_object
//
// DESCRIPTION:
//
//		Defines a referential attribute for each relationship it is involved in.
//
// RELATIONSHIP PARTICIPATION:
//
//		R11 - Many-side of M:1 relationship with Referential_attribute.
//		R12 - Supertype for Attr_ref_in_formal, Attr_ref_in_assoc,
//			  Attr_ref_in_subtype
//		R13 - cM:1 relationship with Object_identifier_attribute
//
// REMARKS:
//
//		This is an abstract base class.
//

class Attr_ref_in_object
	{
	friend Domain;					// for base attribute navigation
	friend Referential_attribute;	// same

	public:
		// MANAGER functions

		static mc_dbms_typespec *get_mc_dbms_typespec();

		static Attr_ref_in_object *create(
			Referred_to_ident_attr *p_referred_to_ident_attr,
			Object_referring *p_object_referring_ptr,
			Referential_attribute *p_ref_attr_ptr );

		static Attr_ref_in_object *create( const Id & p_id,
                                       const Id & p_robj_id,
                                       const t_uint p_roid_id,
                                       const Id & p_rattr_id,
                                       const Id & p_roir_id,
                                       const Id & p_obj_id,
                                       const Id & p_rel_id,
                                       const Id & p_oir_id,
                                       Referential_attribute *p_ref_attr_ptr );

		static Attr_ref_in_object *create( const Id & p_id,
			Referred_to_ident_attr *p_referred_to_ident_attr,
			Object_referring *p_object_referring_ptr,
			Referential_attribute *p_ref_attr_ptr );

		Attr_ref_in_object( Referred_to_ident_attr *p_referred_to_ident_attr,
			Object_referring *p_object_referring_ptr,
			Referential_attribute *p_ref_attr_ptr );

		Attr_ref_in_object( const Id & p_id,
			Referred_to_ident_attr *p_referred_to_ident_attr,
			Object_referring *p_object_referring_ptr,
			Referential_attribute *p_ref_attr_ptr );

		Attr_ref_in_object( const Id & p_id,
                        const Id & p_robj_id,
                        const t_uint p_roid_id,
                        const Id & p_rattr_id,
                        const Id & p_roir_id,
                        const Id & p_obj_id,
                        const Id & p_rel_id,
                        const Id & p_oir_id,
                        Referential_attribute *p_ref_attr_ptr );

		virtual ~Attr_ref_in_object();

		// IMPLEMENTOR functions

		Base_attribute *navigate_to_base_attr();
		Base_attribute *global_navigate_to_base_attr();

		// Functions to add referentials to other objects

		// ACCESS functions

		const Id & get_attr_ref_in_object_id() { return id; }
		Id containing_object_id() { return ref_attr_ptr->
			containing_object_id(); }
		Description containing_object_name() { return ref_attr_ptr->
			containing_object_name(); }
		Id containing_attr_id () { return ref_attr_ptr->
			containing_attr_id(); }
		Description containing_attr_name () { return ref_attr_ptr->
			get_attr_name(); }
		Id relationship_id () const;	// cannot be inline

		void set_is_constrained( t_boolean p_is_constrained )
			{ is_constrained = p_is_constrained; }
		t_boolean get_is_constrained() { return is_constrained; }

		Description &reference_description() { return ref_desc; }

		Id referred_to_object_id () const { return m_robj_id; }
		Id referred_to_attr_id () const { return m_rattr_id; }
		const t_uint &referred_to_object_ident_id() const { return m_roid_id; }
		Id referred_to_object_in_relationship_id() const { return m_roir_id; }


    // Note these functions will return something appropriate when
    // the referred to object is not present due to dangling ids

		Description get_referred_to_object_name() const;
		Attribute::t_prefix_derive_mode get_referred_to_prefix_derive_mode();
		Description get_referred_to_prefix() const;
		Description get_referred_to_root() const;
		Description get_referred_to_attr_name() const;

		t_uint get_rel_number(); 	// cannot be inline

		Referential_attribute *get_ref_attr_ptr() const { return ref_attr_ptr; }
		void set_ref_attr_ptr( Referential_attribute *p_ref_attr_ptr );

		Referred_to_ident_attr *get_referred_to_ident_attr_ptr() const;
		Object_referring *get_object_referring_ptr();

		Id get_referring_object_id() const
            { return m_obj_id; }
		Id get_object_referring_id() const
            { return m_oir_id; }
		Id get_referring_relationship_id() const
            { return m_rel_id; }

		D_im_ocm_oam *get_im_ocm_oam_ptr() const
			{ return im_ocm_oam_ptr; }

    mc_dbms_segment* get_config_ptr ()
			{ return im_ocm_oam_ptr->get_config_ptr(); }

    DELETE_DOWN_DECL_SUBTYPE()


	private:

		Id id;
		t_boolean is_constrained;
		Description ref_desc;

		// For R108, maintain pointer to the Referential_attribute this instance
		// is associated with. This navigates us to the containing object id and
		// the containing attribute id.

		mc_dbms_relationship_1_m(Attr_ref_in_object,ref_attr_ptr,Referential_attribute,attr_ref_in_objects,Referential_attribute *) ref_attr_ptr;

        // R111 one side - use id
		Id m_robj_id;
		t_uint m_roid_id;
		Id m_rattr_id;
		Id m_roir_id;

        // R111 other side - use id
		Id m_obj_id;
		Id m_rel_id;   // used for formalizing both sides of relationship
		Id m_oir_id;

    // The D_IM_OCM_OAM class needs to keep a collection of all of these
    //  for when relationships are being reconstructed.
		mc_dbms_relationship_1_m(Attr_ref_in_object,im_ocm_oam_ptr,D_im_ocm_oam,attr_ref_in_objects,D_im_ocm_oam *) im_ocm_oam_ptr;

		// HELPING functions

		Id_assigner &id_assigner()
			{ return get_im_ocm_oam_ptr()->get_assigners()->
				attr_ref_in_object_id_assigner(); }

		Id assign_id()
			{
			return ( id_assigner().assign_next_id() );
			}

		Object_identifier_attribute *get_referred_to_obj_id_attr_ptr() const;
	};

#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
