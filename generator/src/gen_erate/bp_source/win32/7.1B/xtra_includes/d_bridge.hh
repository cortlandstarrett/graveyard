/*========================================================================
 *
 * File:      $RCSfile: d_bridge.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:08 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_BRIDGE_HH
#define D_BRIDGE_HH



#include "u_typdef.hh"
#include "u_id.hh"

#include <u_desc.hh>
#include <u_string.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include "d_dd_sam.hh"
#include "d_entity.hh"
#include "d_typdef.hh"

#include <d_exespec.hh>

// Classes we declare

class D_bridge;

// Classes we reference only

class D_external_entity;
class D_bridge_parm;


class D_bridge: public D_execution_spec
{
public:

	// MANAGER functions

	static D_bridge * create( D_external_entity * p_ee_ptr,
		const Description & p_name = Description::Default,
		const Id & p_return_type_id = Id::Default,
		t_boolean p_general_service_mapping = FALSE,
		const Description & p_description = Description::Default );

	static D_bridge * create( D_external_entity * p_ee_ptr, const Id & p_id,
		const Description & p_name = Description::Default,
		const Id & p_return_type_id = Id::Default,
		t_boolean p_general_service_mapping = FALSE,
		const Description & p_description = Description::Default );

	virtual ~D_bridge();


	// IMPLEMENTOR functions

	D_bridge_parm * find_parameter_by_id( const Id & p_id ) const;
	D_bridge_parm * find_parameter_by_name( const Description & p_name ) const;

	void delete_parameters();


	// ACCESS functions

	const Id & get_id() const
		{ return( m_id ); }

	const Description & get_name() const
		{ return( m_name ); }
	void set_name( const Description & p_name )
		{ m_name = p_name; }

	const Id & get_return_type_id() const
		{ return( m_return_type_id ); }
	void set_return_type_id( const Id & p_id )
		{ m_return_type_id = p_id; }

	D_core_data_type * get_return_core_data_type_ptr ();
	D_user_data_type * get_return_user_data_type_ptr ();
	D_enum_data_type * get_return_enum_data_type_ptr ();

	Description & get_description()
		{ return( m_description ); }
	void set_description( const Description & p_description )
		{ m_description = p_description; }

	const t_boolean & get_general_service_mapping() const
		{ return( m_general_service_mapping ); }
	void set_general_service_mapping( t_boolean p_mapping )
		{ m_general_service_mapping = p_mapping; }

	D_external_entity * get_external_entity_ptr()
		{ return( m_external_entity_ptr ); }

	D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
		{ return get_external_entity_ptr()->get_dd_srm_scm_sam_ptr(); }

	mc_dbms_List< D_bridge_parm * > * get_parameter_coll_ptr()
		{ return( & m_parameter_coll.getvalue() ); }

	const mc_dbms_List< D_bridge_parm * > *
		get_ro_parameter_coll_ptr() const
		{ return( ( const mc_dbms_List< D_bridge_parm * > * )
		& m_parameter_coll.getvalue() ); }

	Domain * get_domain_ptr()
		{
		return( get_dd_srm_scm_sam_ptr()->get_domain_ptr() );
		}

	D_bridge* get_bridge_ptr ()
	    { return this; }

	int get_spec_type ();   // implemented in a_bush.cc to avoid excessive #includes

	D_data_type* get_return_type ();

    DELETE_DOWN_DECL_SUBTYPE()


protected:

	D_bridge( D_external_entity * p_ee_ptr, const Description & p_name,
		const Id & p_return_type_id, t_boolean p_general_service_mapping,
		const Description & p_description );

	D_bridge( D_external_entity * p_ee_ptr, const Id & p_id,
		const Description & p_name,
		const Id & p_return_type_id, t_boolean p_general_service_mapping,
		const Description & p_description );

private:

	Id m_id;
	Description	m_name;
	Id m_return_type_id;
	Description m_description;
	t_boolean m_general_service_mapping;

	mc_dbms_relationship_1_m(D_bridge,m_external_entity_ptr,D_external_entity,bridge_coll,D_external_entity *) m_external_entity_ptr;

	mc_dbms_relationship_m_1(D_bridge,m_parameter_coll,D_bridge_parm,m_bridge_ptr,mc_dbms_List< D_bridge_parm * >) m_parameter_coll;

	// Helping functions

	Id_assigner &id_assigner()
		{ return get_dd_srm_scm_sam_ptr()->get_assigners()->bridge_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}

	static mc_dbms_typespec * get_mc_dbms_typespec();
};

#endif
