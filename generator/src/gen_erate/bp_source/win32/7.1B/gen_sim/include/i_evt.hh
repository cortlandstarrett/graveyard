/*========================================================================
 *
 * File:      $RCSfile: i_evt.hh,v $
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

#ifndef I_EVT_HH
#define I_EVT_HH


#include <u_id.hh>
#include <u_desc.hh>
#include <d_typdef.hh>


class I_SM_Evt_Supp_DI;
class I_SM_Evt_Inst;




class I_SM_Evt
{
public:

	static mc_dbms_typespec * get_mc_dbms_typespec();

	static I_SM_Evt * create( mc_dbms_database * p_db_ptr,
		const Description& p_label  = Description::Default );

	virtual	~I_SM_Evt ();

	void relate_R2021( I_SM_Evt_Supp_DI * );

	void relate_R2022( I_SM_Evt_Inst * );

	// Class-extent finds follow

	static I_SM_Evt*
		find_SM_Evt_by_SM_evt_ID(
			mc_dbms_database * p_db_ptr,
			const Id& p_SM_evt_ID );

	static mc_dbms_Set< I_SM_Evt * > *
		find_SM_Evt_by_label(
			mc_dbms_database * p_db_ptr,
			const Description& p_label );

	// Contained collection's finds follow

	I_SM_Evt_Supp_DI*
		find_SM_Evt_Supp_DI_R2021_by_SM_esdi_ID(
			const Id& p_SM_esdi_ID ) const;

	mc_dbms_Set< I_SM_Evt_Supp_DI * > *
		find_SM_Evt_Supp_DI_R2021_by_name(
			const Description& p_name ) const;

	I_SM_Evt_Inst*
		find_SM_Evt_Inst_R2022_by_evt_inst_ID(
			const Id& p_evt_inst_ID ) const;

	// Return pointers to contained collections

	mc_dbms_List< I_SM_Evt_Supp_DI * > *
		get_SM_Evt_Supp_DI_R2021_coll_ptr()
			{ return( & m_SM_Evt_Supp_DI_R2021_coll.getvalue() ); }

	mc_dbms_List< I_SM_Evt_Inst * > *
		get_SM_Evt_Inst_R2022_coll_ptr()
			{ return( & m_SM_Evt_Inst_R2022_coll.getvalue() ); }

	static mc_dbms_List< I_SM_Evt * > *
		get_class_extent_ptr( mc_dbms_database * p_db_ptr );

	// get/set functions

	const Id& get_SM_evt_ID () const
		{ return m_SM_evt_ID; }

	void set_SM_evt_ID (const Id& p_id) 
		{ m_SM_evt_ID = p_id; }

	const Description& get_label () const
		{ return m_label; }

	void set_label (const Description& p_input)
		{ m_label = p_input; }


private:

	Id m_SM_evt_ID;
	Description m_label;

	mc_dbms_relationship_m_1(I_SM_Evt,m_SM_Evt_Supp_DI_R2021_coll,I_SM_Evt_Supp_DI,m_SM_Evt_R2021_ptr,mc_dbms_List<I_SM_Evt_Supp_DI*>) m_SM_Evt_Supp_DI_R2021_coll;

	mc_dbms_relationship_m_1(I_SM_Evt,m_SM_Evt_Inst_R2022_coll,I_SM_Evt_Inst,m_SM_Evt_R2022_ptr,mc_dbms_List<I_SM_Evt_Inst*>) m_SM_Evt_Inst_R2022_coll;

	// Helping functions follow

	I_SM_Evt ( const Description& p_label );
};

#endif
