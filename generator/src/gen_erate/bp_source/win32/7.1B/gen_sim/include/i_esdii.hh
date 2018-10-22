/*========================================================================
 *
 * File:      $RCSfile: i_esdii.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:18 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef I_ESDII_HH
#define I_ESDII_HH


#ifdef OLD_FILE_NAMES
#include <U_id.hh>
#include <DBU_string.hh>
#include <D_typedefs.hh>
#else
#include <u_id.hh>
#include <u_string.hh>
#include <d_typdef.hh>
#endif


class I_SM_Evt_Supp_DI;
class I_SM_Evt_Inst;
class I_var;




class I_SM_Evt_Supp_DI_Inst
{
public:
	static mc_dbms_typespec* get_mc_dbms_typespec ();

	static I_SM_Evt_Supp_DI_Inst* create (mc_dbms_database* p_db_ptr,
		t_core_data_type p_core_data_type,
		t_user_data_type p_user_data_type);

	virtual	~I_SM_Evt_Supp_DI_Inst ();

	void relate_R2023 (I_SM_Evt_Inst*);

	void relate_R2023 (I_SM_Evt_Supp_DI*);

	// Return pointers to single cardinality relationships

	I_SM_Evt_Inst* get_SM_Evt_Inst_R2023_ptr ()
		{ return (m_SM_Evt_Inst_R2023_ptr); }

	I_SM_Evt_Supp_DI* get_SM_Evt_Supp_DI_R2023_ptr ()
		{ return (m_SM_Evt_Supp_DI_R2023_ptr); }

	// Return pointers to contained collections

	// get/set functions

	const Id& get_SM_esdi_ID () const
		{ return m_SM_esdi_ID; }

	void set_SM_esdi_ID (const Id& p_input)
		{ m_SM_esdi_ID = p_input; }

	virtual t_core_data_type get_core_data_type ();

	virtual t_user_data_type get_user_data_type ();

	I_var* get_var_ptr ();

private:

	Id m_SM_esdi_ID;
	I_var* m_var_ptr;

	mc_dbms_relationship_1_m(I_SM_Evt_Supp_DI_Inst,m_SM_Evt_Inst_R2023_ptr,I_SM_Evt_Inst,m_SM_Evt_Supp_DI_Inst_R2023_coll,I_SM_Evt_Inst*) m_SM_Evt_Inst_R2023_ptr;

	mc_dbms_relationship_1_m(I_SM_Evt_Supp_DI_Inst,m_SM_Evt_Supp_DI_R2023_ptr,I_SM_Evt_Supp_DI,m_SM_Evt_Supp_DI_Inst_R2023_coll,I_SM_Evt_Supp_DI*) m_SM_Evt_Supp_DI_R2023_ptr;

	// Helping functions follow

	I_SM_Evt_Supp_DI_Inst ();
};




#endif
