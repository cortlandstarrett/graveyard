/*========================================================================
 *
 * File:      $RCSfile: d_parm.hh,v $
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

#ifndef D_PARM_HH
#define D_PARM_HH



//
// FILE: d_parm.hh  AUTHOR: David E. Solomon	 CREATION DATE: 7/25/94
//
// CONTENTS: Specification of a general-purpose OOA parameter which can be
//	used as the base class of a specific type parameter (eg - a transformer
//  or bridge parameter).
//
// REMARKS: This class is conceptually virtual since we do not allow it to
//	be created by itself.
//


// Include those header files that are DIRECTLY needed by this one.


#include <u_id.hh>
#include <u_string.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include <d_tfmr.hh>
#include <d_synchs.hh>
#include <d_object.hh>
#include <d_bridge.hh>
#include <d_entity.hh>


// Classes we reference only

class D_transformer;
class D_bridge;
class D_core_data_type;
class D_dd_srm_scm_sam;
class D_synchronous_service;


class D_parameter
{
public:

	// MANAGER functions

	virtual ~D_parameter();

	// ACCESS functions

	const Id & get_id() const
		{ return( m_id ); }

	const Description & get_name() const
		{ return( m_name ); }
	void set_name( const vchar * p_name )
		{ m_name = p_name; }

	const Id & get_data_type_id() const
		{ return( m_data_type_id ); }
	void set_data_type_id( const Id & p_id )
		{ m_data_type_id = p_id; }

	D_core_data_type* get_core_data_type_ptr ();
	D_user_data_type* get_user_data_type_ptr ();
	D_enum_data_type* get_enum_data_type_ptr ();
	t_uint get_core_data_type_type ();
	virtual D_dd_srm_scm_sam* get_dd_srm_scm_sam_ptr () = 0;

    t_boolean is_by_reference()
       { return m_by_ref; }
    t_boolean is_by_value()
       { return m_by_ref ? FALSE : TRUE ; }

    void set_by_reference( t_boolean p_by_ref )
       { m_by_ref = p_by_ref; }

    DELETE_DOWN_DECL_SUPERTYPE()


protected:

	Id m_id;

    virtual Id_assigner &id_assigner() = 0;

	D_parameter( const Description & p_name,
		const Id & p_data_type_id, t_boolean p_by_ref );

	D_parameter( const Id & p_my_id, const Description & p_name,
		const Id & p_data_type_id, t_boolean p_by_ref );

private:

	Description m_name;
	Id m_data_type_id;
    t_boolean m_by_ref;

	// Helping functions

};



class D_transformer_parm : public D_parameter
{
public:

	// MANAGER functions

	static D_transformer_parm * create( D_transformer * p_trans_ptr,
		const Description & p_name = Description::Default,
        t_boolean p_by_ref = FALSE,
		const Id & p_data_type_id = Id::Default );

	static D_transformer_parm * create( D_transformer * p_trans_ptr,
		const Id & p_id,
		const Description & p_name = Description::Default,
        t_boolean p_by_ref = FALSE,
		const Id & p_data_type_id = Id::Default );

	virtual ~D_transformer_parm();

	// ACCESS functions

	D_transformer * get_transformer_ptr()
		{ return( m_transformer_ptr ); }

	D_im_ocm_oam* get_im_ocm_oam_ptr ()
	{
	    return m_transformer_ptr->get_object_ptr ()->
		get_im_ocm_oam_ptr ();
	}
    D_dd_srm_scm_sam* get_dd_srm_scm_sam_ptr ()
    {
        return get_im_ocm_oam_ptr()->get_dd_srm_scm_sam_ptr();
    }


    DELETE_DOWN_DECL_SUBTYPE()


protected:

	D_transformer_parm( D_transformer * p_trans_ptr, const Description & p_name,
		const Id & p_data_type_id, t_boolean p_by_ref );

	D_transformer_parm( D_transformer * p_trans_ptr, const Id & p_id,
		const Description & p_name, const Id & p_data_type_id, t_boolean p_by_ref );

private:

	mc_dbms_relationship_1_m(D_transformer_parm,m_transformer_ptr,D_transformer,m_parameter_coll,D_transformer *) m_transformer_ptr;

	// Helping functions

	Id_assigner &id_assigner()
		{ return get_im_ocm_oam_ptr()->get_assigners()->tfmr_parm_id_assigner(); }

	Id assign_id()
		{
		Id id( id_assigner().assign_next_id() );
		id.set_class_type( TRANSFORMER_PARM_TYPE );
		return( id );
		}

	static mc_dbms_typespec * get_mc_dbms_typespec();
};



class D_bridge_parm : public D_parameter
{
public:

	// MANAGER functions

	static D_bridge_parm * create( D_bridge * p_bridge_ptr,
		const Description & p_name = Description::Default,
        t_boolean p_by_ref = FALSE,
		const Id & p_data_type_id = Id::Default );

	static D_bridge_parm * create( D_bridge * p_bridge_ptr, const Id & p_id,
		const Description & p_name = Description::Default,
        t_boolean p_by_ref = FALSE,
		const Id & p_data_type_id = Id::Default );

	virtual ~D_bridge_parm();

	// ACCESS functions

	D_bridge * get_bridge_ptr()
		{ return( m_bridge_ptr ); }

	D_dd_srm_scm_sam* get_dd_srm_scm_sam_ptr ()
	{
	    return m_bridge_ptr->get_external_entity_ptr ()->
		get_dd_srm_scm_sam_ptr ();
	}

   DELETE_DOWN_DECL_SUBTYPE()


protected:

	D_bridge_parm( D_bridge * p_bridge_ptr, const Description & p_name,
		const Id & p_data_type_id, t_boolean p_by_ref );

	D_bridge_parm( D_bridge * p_bridge_ptr, const Id & p_id,
		const Description & p_name, const Id & p_data_type_id, t_boolean p_by_ref );

private:

	mc_dbms_relationship_1_m(D_bridge_parm,m_bridge_ptr,D_bridge,m_parameter_coll,D_bridge *) m_bridge_ptr;

	// Helping functions

	Id_assigner &id_assigner()
		{ return get_dd_srm_scm_sam_ptr()->get_assigners()->parameter_id_assigner(); }

	Id assign_id()
		{
		Id id( id_assigner().assign_next_id() );
		id.set_class_type( BRIDGE_PARM_TYPE );
		return( id );
		}

	static mc_dbms_typespec * get_mc_dbms_typespec();
};

class D_synchronous_service_parm : public D_parameter
{
public:

	// MANAGER functions

	static D_synchronous_service_parm * create( D_synchronous_service * p_synch_service_ptr,
		const Description & p_name = Description::Default,
        t_boolean p_by_ref = FALSE,
		const Id & p_data_type_id = Id::Default );

	static D_synchronous_service_parm * create( D_synchronous_service * p_synch_service_ptr, 
		const Id & p_id,
		const Description & p_name = Description::Default,
        t_boolean p_by_ref = FALSE,
		const Id & p_data_type_id = Id::Default );

	virtual ~D_synchronous_service_parm();

	// ACCESS functions

	D_synchronous_service * get_synch_service_ptr()
		{ return( m_synch_service_ptr ); }

	D_dd_srm_scm_sam* get_dd_srm_scm_sam_ptr ()
	{
	    return m_synch_service_ptr->get_dd_srm_scm_sam_ptr ();
	}

   DELETE_DOWN_DECL_SUBTYPE()


protected:

	D_synchronous_service_parm( D_synchronous_service * p_synch_service_ptr, const Description & p_name,
		const Id & p_data_type_id, t_boolean p_by_ref );

	D_synchronous_service_parm( D_synchronous_service * p_synch_service_ptr, const Id & p_id,
		const Description & p_name, const Id & p_data_type_id, t_boolean p_by_ref );

private:

	mc_dbms_relationship_1_m(D_synchronous_service_parm,m_synch_service_ptr,D_synchronous_service,m_parameter_coll,D_synchronous_service *) m_synch_service_ptr;

	// Helping functions

	Id_assigner &id_assigner()
		{ return get_dd_srm_scm_sam_ptr()->get_assigners()->parameter_id_assigner(); }

	Id assign_id()
		{
		Id id( id_assigner().assign_next_id() );
		id.set_class_type( SYNCH_SERVICE_PARM_TYPE );
		return( id );
		}

	static mc_dbms_typespec * get_mc_dbms_typespec();
};

#endif
