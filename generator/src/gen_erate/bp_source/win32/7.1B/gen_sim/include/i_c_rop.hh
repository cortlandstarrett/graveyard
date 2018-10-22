/*========================================================================
 *
 * File:      $RCSfile: i_c_rop.hh,v $
 * Version:   $Revision: 1.10 $
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

#ifndef I_C_ROP_HH
#define I_C_ROP_HH


#ifdef OLD_FILE_NAMES
#include <DBU_string.hh>
#else
#include <u_desc.hh>
#endif


#include <i_rop.hh>




class I_Chain_Rel_Obj_Pair : public I_Related_Object_Pair
{
public:
	static mc_dbms_typespec * get_mc_dbms_typespec();

	static I_Chain_Rel_Obj_Pair * create( mc_dbms_database * p_db_ptr,
		int p_ONE_side_is_conditional  = 0,
		int p_ONE_side_is_many  = 0,
		int p_OTH_side_is_conditional  = 0,
		int p_OTH_side_is_many  = 0 );

	virtual	~I_Chain_Rel_Obj_Pair ();

	// get/set functions

	Description get_ONE_side_chain_equiv () const
		{ return m_ONE_side_chain_equiv; }

	void set_ONE_side_chain_equiv (Description p_input)
		{ m_ONE_side_chain_equiv = p_input; }

	Description get_OTH_side_chain_equiv () const
		{ return m_OTH_side_chain_equiv; }

	void set_OTH_side_chain_equiv (Description p_input)
		{ m_OTH_side_chain_equiv = p_input; }

	virtual I_Chain_Rel_Obj_Pair* get_Chain_Rel_Obj_Pair_ptr ()
		{ return this; }

public:

	virtual long persist() {
		long bytesWritten = 0;

		// Force parent class to serialize its data		
		bytesWritten += I_Related_Object_Pair::persist();
		
		m_ONE_side_chain_equiv.persist();
		m_OTH_side_chain_equiv.persist();
		
		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
		
		return bytesWritten;
	}
	
	virtual void restore() {
		// Force the parent to restore it's data
		I_Related_Object_Pair::restore();
		
		m_ONE_side_chain_equiv.restore();	
		m_OTH_side_chain_equiv.restore();	
		
		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
	}

	static char* create() {
		I_Chain_Rel_Obj_Pair* inst = new I_Chain_Rel_Obj_Pair(0, 0, 0, 0);
		inst->restore();
		return (char*)inst;
	}

private:
	Description m_ONE_side_chain_equiv;
	Description m_OTH_side_chain_equiv;


	// Helping functions follow

	I_Chain_Rel_Obj_Pair (
		int p_ONE_side_is_conditional,
		int p_ONE_side_is_many,
		int p_OTH_side_is_conditional,
		int p_OTH_side_is_many );

};




#endif
