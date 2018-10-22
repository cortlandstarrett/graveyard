/*========================================================================
 *
 * File:      $RCSfile: d_tfmr.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:07 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_TFMR_HH
#define D_TFMR_HH



#include "u_id.hh"

#include <u_desc.hh>
#include <u_string.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include "d_dd_sam.hh"
#include "d_object.hh"
#include <d_exespec.hh>
#include <d_typdef.hh>

// Classes we reference only

class Object;
class D_transformer_parm;


class D_transformer: public D_execution_spec
{
public:

	// MANAGER functions

	static D_transformer * create( Object * p_object_ptr,
		const Description & p_name = Description::Default,
		const Id & p_return_type_id = Id::Default,
		const Description & p_description = Description::Default );

	static D_transformer * create( Object * p_object_ptr, const Id & p_id,
		const Description & p_name = Description::Default,
		const Id & p_return_type_id = Id::Default,
		const Description & p_description = Description::Default );

	virtual ~D_transformer();


	// IMPLEMENTOR functions

	D_transformer_parm * find_parameter_by_id( const Id & p_id ) const;
	D_transformer_parm * find_parameter_by_name( const Description & p_name ) const;

	void delete_parameters();


	// ACCESS functions

	const Id & get_id() const
		{ return( m_id ); }

	const Description & get_name() const
		{ return( m_name ); }
	void set_name( const vchar * p_name )
		{ m_name = p_name; }

	const Id & get_return_type_id() const
		{ return( m_return_type_id ); }
	void set_return_type_id( const Id & p_id )
		{ m_return_type_id = p_id; }

	D_core_data_type * get_return_core_data_type_ptr();
	D_user_data_type * get_return_user_data_type_ptr();
	D_enum_data_type * get_return_enum_data_type_ptr ();

	Description & get_description()
		{ return( m_description ); }
	void set_description( const Description & p_description )
		{ m_description = p_description; }

	t_boolean is_instance_based() const
		{ return( m_instance_based ); }
	void set_instance_based( t_boolean p_instance_based )
		{ m_instance_based = p_instance_based; }

	Object * get_object_ptr()
		{ return( m_object_ptr ); }

	D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
		{ return get_object_ptr()->get_dd_srm_scm_sam_ptr(); }

	D_im_ocm_oam *get_im_ocm_oam_ptr()
		{ return get_object_ptr()->get_im_ocm_oam_ptr(); }

	mc_dbms_List< D_transformer_parm * > * get_parameter_coll_ptr()
		{ return( & m_parameter_coll.getvalue() ); }

	const mc_dbms_List< D_transformer_parm * > *
		get_ro_parameter_coll_ptr() const
			{ return( ( const mc_dbms_List< D_transformer_parm * > * )
				& m_parameter_coll.getvalue() ); }

	Domain * get_domain_ptr()
		{ return( get_object_ptr()->get_domain_ptr() ); }

	D_transformer* get_transformer_ptr ()
	    { return this; }

	int get_spec_type ();   // implemented in a_bush.cc to avoid excessive #includes

	D_data_type* get_return_type ();

    DELETE_DOWN_DECL_SUBTYPE()


protected:

	D_transformer( Object * p_object_ptr, const Description & p_name,
		const Id & p_return_type_id, const Description & p_description );

	D_transformer( Object * p_object_ptr, const Id & p_id,
		const Description & p_name, const Id & p_return_type_id,
		const Description & p_description );

private:

	Id m_id;
	Description	m_name;
	Id m_return_type_id;
	Description m_description;
	t_boolean m_instance_based;

	// Helping functions

	Id_assigner &id_assigner()
		{ return get_im_ocm_oam_ptr()->get_assigners()->transformer_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}

	static mc_dbms_typespec * get_mc_dbms_typespec();

	mc_dbms_relationship_1_m(D_transformer,m_object_ptr,Object,transformers,Object *) m_object_ptr;

	mc_dbms_relationship_m_1(D_transformer,m_parameter_coll,D_transformer_parm,m_transformer_ptr,mc_dbms_List< D_transformer_parm * >) m_parameter_coll;

};

#endif
