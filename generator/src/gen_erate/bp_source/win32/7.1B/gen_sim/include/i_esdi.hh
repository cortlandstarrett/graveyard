/*========================================================================
 *
 * File:      $RCSfile: i_esdi.hh,v $
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

#ifndef I_ESDI_HH
#define I_ESDI_HH


#ifdef OLD_FILE_NAMES
#include <U_id.hh>
#include <DBU_string.hh>
#include <D_typedefs.hh>
#else
#include <u_id.hh>
#include <u_desc.hh>
#include <d_typdef.hh>
#endif


class I_SM_Evt;
class I_SM_Evt_Supp_DI_Inst;




class I_SM_Evt_Supp_DI
{
public:

	static mc_dbms_typespec * get_mc_dbms_typespec();

	static I_SM_Evt_Supp_DI * create( mc_dbms_database * p_db_ptr,
		const Description& p_name  = Description::Default,
		t_core_data_type p_core_data_type = VOID_DATATYPE,
		t_user_data_type p_user_data_type = USER_DEFINED_USERDATATYPE);

	virtual	~I_SM_Evt_Supp_DI ();

	void relate_R2021( I_SM_Evt * );

	void relate_R2023( I_SM_Evt_Supp_DI_Inst * );

	// Return pointers to single cardinality relationships

	I_SM_Evt * get_SM_Evt_R2021_ptr()
		{ return( m_SM_Evt_R2021_ptr ); }

	// Return pointers to contained collections

	mc_dbms_List< I_SM_Evt_Supp_DI_Inst * > *
		get_SM_Evt_Supp_DI_Inst_R2023_coll_ptr()
			{ return( & m_SM_Evt_Supp_DI_Inst_R2023_coll.getvalue() ); }

	// get/set functions

	const Id& get_SM_esdi_ID () const
		{ return m_SM_esdi_ID; }

	void set_SM_esdi_ID (const Id& p_input)
		{ m_SM_esdi_ID = p_input; }

	const Description& get_name () const
		{ return m_name; }

	void set_name (const Description& p_input)
		{ m_name = p_input; }

	t_core_data_type get_core_data_type () const
		{ return (t_core_data_type) m_core_data_type; }

	void set_core_data_type (t_core_data_type p_input)
		{ m_core_data_type = (t_uint) p_input; }

	t_user_data_type get_user_data_type () const
		{ return (t_user_data_type) m_user_data_type; }

	void set_user_data_type (t_user_data_type p_input)
		{ m_user_data_type = (t_uint) p_input; }

private:

	Id m_SM_esdi_ID;
	Description m_name;
	t_uint m_core_data_type;
	t_uint m_user_data_type;

	mc_dbms_relationship_1_m(I_SM_Evt_Supp_DI,m_SM_Evt_R2021_ptr,I_SM_Evt,m_SM_Evt_Supp_DI_R2021_coll,I_SM_Evt*) m_SM_Evt_R2021_ptr;

	mc_dbms_relationship_m_1(I_SM_Evt_Supp_DI,m_SM_Evt_Supp_DI_Inst_R2023_coll,I_SM_Evt_Supp_DI_Inst,m_SM_Evt_Supp_DI_R2023_ptr,mc_dbms_List<I_SM_Evt_Supp_DI_Inst*>) m_SM_Evt_Supp_DI_Inst_R2023_coll;

	// Helping functions follow

	I_SM_Evt_Supp_DI
	    (const Description& p_name, t_core_data_type p_core_data_type,
	    t_user_data_type p_user_data_type);

};

#endif
