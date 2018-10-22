/*========================================================================
 *
 * File:      $RCSfile: i_rel.hh,v $
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

#ifndef I_REL_HH
#define I_REL_HH


#ifdef OLD_FILE_NAMES
#include <U_id.hh>
#include <DBU_string.hh>
#else
#include <u_id.hh>
#include <u_desc.hh>
#endif


class I_Related_Object_Pair;




class I_Relationship : public SerializableObject
{
public:

	static mc_dbms_typespec * get_mc_dbms_typespec();

	static I_Relationship * create( mc_dbms_database * p_db_ptr,
		const Description& p_number  = Description::Default);

	virtual	~I_Relationship ();

	void relate_R2003( I_Related_Object_Pair * );

	// Class-extent finds follow

	static I_Relationship*
		find_Relationship_by_relationship_ID(
			mc_dbms_database * p_db_ptr,
			const Id& p_relationship_ID );

	static mc_dbms_Set< I_Relationship * > *
		find_Relationship_by_number(
			mc_dbms_database * p_db_ptr,
			const Description& p_number );

	// Contained collection's finds follow

	// Return pointers to contained collections

	mc_dbms_List< I_Related_Object_Pair * > *
		get_Related_Object_Pair_R2003_coll_ptr()
			{ return( & m_Related_Object_Pair_R2003_coll.getvalue() ); }

	// get/set functions

	const Id& get_relationship_ID () const
		{ return m_relationship_ID; }

	const Description& get_number () const
		{ return m_number; }

	void set_number (const Description& p_input)
		{ m_number = p_input; }

	static mc_dbms_List< I_Relationship * > *
		get_class_extent_ptr( mc_dbms_database * p_db_ptr );

public:

	long persist() {
		long bytesWritten = 0;

		bytesWritten += writeBlob((char*)&m_relationship_ID, sizeof(Id));
		bytesWritten += m_number.persist();

		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
		return bytesWritten;
	}
	
	void restore() {
		readBlob((char*)&m_relationship_ID);
		m_number.restore();
		
		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
	}
	
	static char* create() {
		I_Relationship* inst = new I_Relationship();
		inst->restore();
		return (char*)inst;
	}

private:

	Id m_relationship_ID;
	Description m_number;

	mc_dbms_relationship_m_1(I_Relationship,m_Related_Object_Pair_R2003_coll,I_Related_Object_Pair,m_Relationship_R2003_ptr,mc_dbms_List<I_Related_Object_Pair*>) m_Related_Object_Pair_R2003_coll;

	// Helping functions follow

	I_Relationship (
		const Description& p_number );

	/**
	 * This is used only for serialization.
	 */
	I_Relationship() { }
};

#endif
