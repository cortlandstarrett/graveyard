/*========================================================================
 *
 * File:      $RCSfile: i_einst.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:17 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef I_EINST_HH
#define I_EINST_HH


#include <u_typdef.hh>
#include <u_id.hh>
#include <u_desc.hh>
#include <d_typdef.hh>
#include <u_util.hh>

#include <i_var.hh>

class I_SM_Evt_Supp_DI_Inst;
class I_SM_Evt;
class I_Object_Instance;




class I_SM_Evt_Inst
{
public:

	static mc_dbms_typespec * get_mc_dbms_typespec();

	static I_SM_Evt_Inst * create (mc_dbms_database * p_db_ptr);

	virtual	~I_SM_Evt_Inst ();

    t_boolean	operator== (const I_SM_Evt_Inst& p_einst) const;

	void relate_R2023( I_SM_Evt_Supp_DI_Inst * );

	void relate_R2022( I_SM_Evt * );

	void relate_R2031( I_Object_Instance * );

	void relate_R2032( I_Object_Instance * );

	// Class-extent finds follow

	static I_SM_Evt_Inst*
		find_SM_Evt_Inst_by_evt_inst_ID
		    (mc_dbms_database* p_db_ptr, const Id& p_evt_inst_ID);

	// Contained collection's finds follow

	I_SM_Evt_Supp_DI_Inst*
		find_SM_Evt_Supp_DI_Inst_R2023_by_SM_esdi_ID(
			const Id& p_SM_esdi_ID ) const;

	// Return pointers to single cardinality relationships

	I_SM_Evt * get_SM_Evt_R2022_ptr()
		{ return( m_SM_Evt_R2022_ptr ); }

	I_Object_Instance * get_Object_Instance_R2031_ptr()
		{ return( m_Object_Instance_R2031_ptr ); }

	I_Object_Instance * get_Object_Instance_R2032_ptr()
		{ return( m_Object_Instance_R2032_ptr ); }

	// Return pointers to contained collections

	mc_dbms_List< I_SM_Evt_Supp_DI_Inst * > *
		get_SM_Evt_Supp_DI_Inst_R2023_coll_ptr()
			{ return( & m_SM_Evt_Supp_DI_Inst_R2023_coll.getvalue() ); }

	// get/set functions

	const Id& get_evt_inst_ID () const
		{ return m_evt_inst_ID; }

	static mc_dbms_List< I_SM_Evt_Inst * > *
		get_class_extent_ptr( mc_dbms_database * p_db_ptr );

	static t_class_type get_class_type()
		{ return EVENT_INST_TYPE; }

	I_timestamp_var get_expiration_time ()
		{ return m_expiration_timestamp; }

	void set_expiration_time (const I_timestamp_var& p_time);

	void set_expiration_time_to_infinity ();

	t_boolean is_expiration_time_infinity ();

	t_boolean& is_creation_event ()
		{ return m_is_creation_event; }

	const Id& get_creation_Object_ID () const
		{ return m_creation_Object_ID; }

	void set_creation_Object_ID (const Id& p_creation_Object_ID)
		{ m_creation_Object_ID = p_creation_Object_ID; }

	t_long get_recurring_microseconds ()
		{ return m_recurring_microseconds; }

	void set_recurring_microseconds (t_long p_recurring_microseconds)
		{ m_recurring_microseconds = p_recurring_microseconds; }

	t_boolean is_polymorphic_delivery ()
		{ return m_is_polymorphic_delivery; }

	void set_polymorphic_delivery (t_boolean p_is_polymorphic_delivery)
		{ m_is_polymorphic_delivery = p_is_polymorphic_delivery; }

	const Id& get_polymorphic_relationship ()
		{ return m_poly_relationship_ID; }

	void set_polymorphic_relationship (const Id& p_rel_id)
		{ m_poly_relationship_ID = p_rel_id; }

	static I_SM_Evt_Inst* copy__I_SM_Evt_Inst
	    (I_SM_Evt_Inst* p_orig_einst_ptr);

	static t_boolean delete__I_SM_Evt_Inst (I_SM_Evt_Inst* p_einst_ptr,
	    t_boolean p_delete__I_SM_Evt__flag = TRUE);

	Description format();

private:

	Id m_evt_inst_ID;

	I_timestamp_var m_expiration_timestamp;
	t_long m_recurring_microseconds;
	t_boolean m_is_creation_event;
	Id m_creation_Object_ID;
	t_boolean m_is_polymorphic_delivery;

    // The id of the relationship this polymorphic event 'follows'
    // If it is Id::Default, then we need to check for multiple state machines
	Id m_poly_relationship_ID;

	mc_dbms_relationship_m_1(I_SM_Evt_Inst,m_SM_Evt_Supp_DI_Inst_R2023_coll,I_SM_Evt_Supp_DI_Inst,m_SM_Evt_Inst_R2023_ptr,mc_dbms_List<I_SM_Evt_Supp_DI_Inst*>) m_SM_Evt_Supp_DI_Inst_R2023_coll;

	mc_dbms_relationship_1_m(I_SM_Evt_Inst,m_SM_Evt_R2022_ptr,I_SM_Evt,m_SM_Evt_Inst_R2022_coll,I_SM_Evt*) m_SM_Evt_R2022_ptr;

	mc_dbms_relationship_1_m(I_SM_Evt_Inst,m_Object_Instance_R2031_ptr,I_Object_Instance,m_SM_Evt_Inst_R2031_coll,I_Object_Instance*) m_Object_Instance_R2031_ptr;

	mc_dbms_relationship_1_m(I_SM_Evt_Inst,m_Object_Instance_R2032_ptr,I_Object_Instance,m_SM_Evt_Inst_R2032_coll,I_Object_Instance*) m_Object_Instance_R2032_ptr;

	// Helping functions follow

	I_SM_Evt_Inst ();
};

#endif
