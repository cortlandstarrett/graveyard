/*========================================================================
 *
 * File:      $RCSfile: i_rop.hh,v $
 * Version:   $Revision: 1.10 $
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

#ifndef I_ROP_HH
#define I_ROP_HH


#include <u_desc.hh>


class I_Object;
class I_Relationship;
class I_Related_Object_Instance_Pair;
class I_Chain_Rel_Obj_Pair;
class I_ID_REF_Rel_Obj_Pair;




class I_Related_Object_Pair : public SerializableObject
{
public:

	static mc_dbms_typespec * get_mc_dbms_typespec();

	static I_Related_Object_Pair * create( mc_dbms_database * p_db_ptr,
		int p_ONE_side_is_conditional  = 0,
		int p_ONE_side_is_many  = 0,
		int p_OTH_side_is_conditional  = 0,
		int p_OTH_side_is_many  = 0 );

	virtual	~I_Related_Object_Pair ();

	void relate_R2006( I_Object * );

	void relate_R2005( I_Object * );

	void relate_R2003( I_Relationship * );

	void relate_R2004( I_Related_Object_Instance_Pair * );

	// Return pointers to single cardinality relationships

	I_Object * get_Object_R2006_ptr()
		{ return( m_Object_R2006_ptr ); }

	I_Object * get_Object_R2005_ptr()
		{ return( m_Object_R2005_ptr ); }

	I_Relationship * get_Relationship_R2003_ptr()
		{ return( m_Relationship_R2003_ptr ); }

	// Return pointers to contained collections

	mc_dbms_List< I_Related_Object_Instance_Pair * > *
		get_Related_Object_Instance_Pair_R2004_coll_ptr()
			{ return( & m_Related_Object_Instance_Pair_R2004_coll.getvalue() ); }

	// get/set functions

	int get_ONE_side_is_conditional () const
		{ return m_ONE_side_is_conditional; }

	void set_ONE_side_is_conditional (int p_input)
		{ m_ONE_side_is_conditional = p_input; }

	int get_ONE_side_is_many () const
		{ return m_ONE_side_is_many; }

	void set_ONE_side_is_many (int p_input)
		{ m_ONE_side_is_many = p_input; }

	const Description& get_ONE_side_phrase () const
		{ return m_ONE_side_phrase; }

	void set_ONE_side_phrase (const Description& p_input)
		{ m_ONE_side_phrase = p_input; }

	int get_OTH_side_is_conditional () const
		{ return m_OTH_side_is_conditional; }

	void set_OTH_side_is_conditional (int p_input)
		{ m_OTH_side_is_conditional = p_input; }

	int get_OTH_side_is_many () const
		{ return m_OTH_side_is_many; }

	void set_OTH_side_is_many (int p_input)
		{ m_OTH_side_is_many = p_input; }

	const Description& get_OTH_side_phrase () const
		{ return m_OTH_side_phrase; }

	void set_OTH_side_phrase (const Description& p_input)
		{ m_OTH_side_phrase = p_input; }

	virtual I_Chain_Rel_Obj_Pair* get_Chain_Rel_Obj_Pair_ptr ()
		{ return 0; }
	virtual I_ID_REF_Rel_Obj_Pair* get_ID_REF_Rel_Obj_Pair_ptr ()
		{ return 0; }

public:

	virtual long persist() {
		long bytesWritten = 0;
			
		bytesWritten += writeLong( m_ONE_side_is_conditional );
		bytesWritten += writeLong( m_ONE_side_is_many );
		m_ONE_side_phrase.persist();
		bytesWritten += writeLong( m_OTH_side_is_conditional );
		bytesWritten += writeLong( m_OTH_side_is_many );
		m_OTH_side_phrase.persist();
		
		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.

		return bytesWritten;
	}
	
	virtual void restore() {
		m_ONE_side_is_conditional = readLong();	
		m_ONE_side_is_many = readLong();	
		m_ONE_side_phrase.restore();	
		m_OTH_side_is_conditional = readLong();	
		m_OTH_side_is_many = readLong();	
		m_OTH_side_phrase.restore();	
		
		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
	}

private:

	int m_ONE_side_is_conditional;
	int m_ONE_side_is_many;
	Description m_ONE_side_phrase;
	int m_OTH_side_is_conditional;
	int m_OTH_side_is_many;
	Description m_OTH_side_phrase;

	mc_dbms_relationship_1_m(I_Related_Object_Pair,m_Object_R2006_ptr,I_Object,m_Related_Object_Pair_R2006_coll,I_Object*) m_Object_R2006_ptr;

	mc_dbms_relationship_1_m(I_Related_Object_Pair,m_Object_R2005_ptr,I_Object,m_Related_Object_Pair_R2005_coll,I_Object*) m_Object_R2005_ptr;

	mc_dbms_relationship_1_m(I_Related_Object_Pair,m_Relationship_R2003_ptr,I_Relationship,m_Related_Object_Pair_R2003_coll,I_Relationship*) m_Relationship_R2003_ptr;

	mc_dbms_relationship_m_1(I_Related_Object_Pair,m_Related_Object_Instance_Pair_R2004_coll,I_Related_Object_Instance_Pair,m_Related_Object_Pair_R2004_ptr,mc_dbms_List<I_Related_Object_Instance_Pair*>) m_Related_Object_Instance_Pair_R2004_coll;

	// Helping functions follow

protected:

	I_Related_Object_Pair (
		int p_ONE_side_is_conditional,
		int p_ONE_side_is_many,
		int p_OTH_side_is_conditional,
		int p_OTH_side_is_many );

};

#endif
