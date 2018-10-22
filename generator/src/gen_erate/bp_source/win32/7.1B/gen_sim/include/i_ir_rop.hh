/*========================================================================
 *
 * File:      $RCSfile: i_ir_rop.hh,v $
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

#ifndef I_IR_ROP_HH
#define I_IR_ROP_HH


#ifdef OLD_FILE_NAMES
#include <DBU_string.hh>
#else
#include <u_string.hh>
#endif


#include <i_rop.hh>

class I_ID_Attribute_Reference;




class I_ID_REF_Rel_Obj_Pair : public I_Related_Object_Pair
{
public:

	static mc_dbms_typespec * get_mc_dbms_typespec();

	static I_ID_REF_Rel_Obj_Pair * create( mc_dbms_database * p_db_ptr,
		int p_ONE_side_is_conditional  = 0,
		int p_ONE_side_is_many  = 0,
		int p_OTH_side_is_conditional  = 0,
		int p_OTH_side_is_many  = 0 );

	virtual	~I_ID_REF_Rel_Obj_Pair ();

	void relate_R2007( I_ID_Attribute_Reference * );

	// Return pointers to contained collections

	mc_dbms_List< I_ID_Attribute_Reference * > *
		get_ID_Attribute_Reference_R2007_coll_ptr()
			{ return( & m_ID_Attribute_Reference_R2007_coll.getvalue() ); }

	// get/set functions

	virtual I_ID_REF_Rel_Obj_Pair* get_ID_REF_Rel_Obj_Pair_ptr ()
		{ return this; }

public:

	virtual long persist() {
		long bytesWritten = 0;

		// Force parent class to serialize its data		
		bytesWritten += I_Related_Object_Pair::persist();
		
		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
		
		return bytesWritten;
	}
	
	virtual void restore() {
		// Force the parent to restore it's data
		I_Related_Object_Pair::restore();
		
		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
	}

	static char* create() {
		I_ID_REF_Rel_Obj_Pair* inst = new I_ID_REF_Rel_Obj_Pair(0, 0, 0, 0);
		inst->restore();
		return (char*)inst;
	}

private:


	mc_dbms_relationship_m_1(I_ID_REF_Rel_Obj_Pair,m_ID_Attribute_Reference_R2007_coll,I_ID_Attribute_Reference,m_ID_REF_Rel_Obj_Pair_R2007_ptr,mc_dbms_List<I_ID_Attribute_Reference*>) m_ID_Attribute_Reference_R2007_coll;

	// Helping functions follow

	I_ID_REF_Rel_Obj_Pair (
		int p_ONE_side_is_conditional,
		int p_ONE_side_is_many,
		int p_OTH_side_is_conditional,
		int p_OTH_side_is_many );

};

#endif
