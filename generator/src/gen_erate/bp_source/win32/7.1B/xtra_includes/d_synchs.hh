/*========================================================================
 *
 * File:      $RCSfile: d_synchs.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:12 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>


#ifndef D_SYNCHS_HH
#define D_SYNCHS_HH



#include "u_typdef.hh"
#include "u_id.hh"

#include <u_desc.hh>
#include <u_string.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include "d_dd_sam.hh"
#include "d_entity.hh"
#include <d_exespec.hh>
#include <d_typdef.hh>

// Classes we declare

class D_synchronous_service;

// Classes we reference only

class Domain;
class D_dd_srm_scm_sam;
class D_synchronous_service_parm;


class D_synchronous_service: public D_execution_spec
{
public:

	// MANAGER functions

	static D_synchronous_service * create( D_dd_srm_scm_sam * p_dd_srm_scm_sam_ptr,
		const Description & p_name = Description::Default,
		const Id & p_return_type_id = Id::Default,
		const Description & p_description = Description::Default );

	static D_synchronous_service * create( D_dd_srm_scm_sam * p_dd_srm_scm_sam_ptr, 
		const Id & p_id,
		const Description & p_name = Description::Default,
		const Id & p_return_type_id = Id::Default,
		const Description & p_description = Description::Default );

	virtual ~D_synchronous_service();


	// IMPLEMENTOR functions

	D_synchronous_service_parm * find_parameter_by_id( const Id & p_id ) const;
	D_synchronous_service_parm * find_parameter_by_name( const Description & p_name ) const;

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

	D_dd_srm_scm_sam *get_dd_srm_scm_sam_ptr()
		{ return m_dd_srm_scm_sam_ptr; }

	mc_dbms_List< D_synchronous_service_parm * > * get_parameter_coll_ptr()
		{ return( & m_parameter_coll.getvalue() ); }

	const mc_dbms_List< D_synchronous_service_parm * > *
		get_ro_parameter_coll_ptr() const
		{ return( ( const mc_dbms_List< D_synchronous_service_parm * > * )
		& m_parameter_coll.getvalue() ); }

	Domain * get_domain_ptr()
		{
		return( get_dd_srm_scm_sam_ptr()->get_domain_ptr() );
		}

	D_synchronous_service* get_synch_service_ptr ()
	    { return this; }

	int get_spec_type ();   // implemented in a_bush.cc to avoid excessive #includes

	D_data_type* get_return_type ();

    DELETE_DOWN_DECL_SUBTYPE()


protected:

	D_synchronous_service( D_dd_srm_scm_sam * p_dd_srm_scm_sam_ptr,
		const Description & p_name,
		const Id & p_return_type_id, 
		const Description & p_description );

	D_synchronous_service( D_dd_srm_scm_sam * p_dd_srm_scm_sam_ptr, 
		const Id & p_id,
		const Description & p_name,
		const Id & p_return_type_id,
		const Description & p_description );

private:

	Id m_id;
	Description	m_name;
	Id m_return_type_id;
	Description m_description;

	mc_dbms_relationship_1_m(D_synchronous_service,m_dd_srm_scm_sam_ptr,D_dd_srm_scm_sam,synch_service_coll,D_dd_srm_scm_sam *) m_dd_srm_scm_sam_ptr;

	mc_dbms_relationship_m_1(D_synchronous_service,m_parameter_coll,D_synchronous_service_parm,m_synch_service_ptr,mc_dbms_List< D_synchronous_service_parm * >) m_parameter_coll;

	// Helping functions

	Id_assigner &id_assigner()
		{ return get_dd_srm_scm_sam_ptr()->get_assigners()->synch_service_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}

	static mc_dbms_typespec * get_mc_dbms_typespec();
};

#endif
