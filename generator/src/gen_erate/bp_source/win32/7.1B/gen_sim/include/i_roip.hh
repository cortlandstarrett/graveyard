/*========================================================================
 *
 * File:      $RCSfile: i_roip.hh,v $
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

#ifndef I_ROIP_HH
#define I_ROIP_HH


#ifdef OLD_FILE_NAMES
#include <U_id.hh>
#include <DBU_string.hh>
#include <D_typedefs.hh>
#else
#include <u_id.hh>
#include <u_string.hh>
#include <u_desc.hh>
#include <d_typdef.hh>
#endif


class I_Related_Object_Pair;
class I_Object_Instance;


class I_Related_Object_Instance_Pair : public SerializableObject
{
public:

	static mc_dbms_typespec * get_mc_dbms_typespec();

	static I_Related_Object_Instance_Pair * create( mc_dbms_database * p_db_ptr);

	virtual	~I_Related_Object_Instance_Pair ();

	void relate_R2004( I_Related_Object_Pair * );

	void relate_R2010( I_Object_Instance * );

	void relate_R2011( I_Object_Instance * );

	// Class-extent finds follow

	static mc_dbms_List< I_Related_Object_Instance_Pair * > *
		find_Related_Object_Instance_Pair_by_relationship_ID(
			mc_dbms_database * p_db_ptr,
			const Id& p_relationship_ID );

	static mc_dbms_List< I_Related_Object_Instance_Pair * > *
		find_Related_Object_Instance_Pair_by_rel_inst_ID(
			mc_dbms_database * p_db_ptr,
			const Id& p_rel_inst_ID );

	// Return pointers to single cardinality relationships

	I_Related_Object_Pair * get_Related_Object_Pair_R2004_ptr()
		{ return( m_Related_Object_Pair_R2004_ptr ); }

	I_Object_Instance * get_Object_Instance_R2010_ptr()
		{ return( m_Object_Instance_R2010_ptr ); }

	I_Object_Instance * get_Object_Instance_R2011_ptr()
		{ return( m_Object_Instance_R2011_ptr ); }

	// Return pointers to contained collections

	// get/set functions

	t_boolean get_R2010_is_audited () const
		{ return ((m_consolidated_flag & 0x000001) == 0x000001); }

	void set_R2010_is_audited (t_boolean p_input)
		{
		    if (p_input)
			m_consolidated_flag |= 0x000001;
		    else
			m_consolidated_flag &= 0xfffff7;
		}

	t_boolean get_R2011_is_audited () const
		{ return ((m_consolidated_flag & 0x000010) == 0x000010); }

	void set_R2011_is_audited (t_boolean p_input)
		{
		    if (p_input)
			m_consolidated_flag |= 0x000010;
		    else
			m_consolidated_flag &= 0xffff7f;
		}

	int get_num_with_equal_ids ()
		{ return m_num_with_equal_ids; }

	void set_num_with_equal_ids (int p_num)
		{ m_num_with_equal_ids = p_num; }

	const Id& get_relationship_ID () const
		{ return m_relationship_ID; }

	void set_relationship_ID (const Id& p_input)
		{ m_relationship_ID = p_input; }

	const Id& get_rel_inst_ID () const
		{ return m_rel_inst_ID; }

	void set_rel_inst_ID (const Id& p_input);

	const Description& get_Rnum_str () const
		{ return m_Rnum_str; }

	void set_Rnum_str (const Description& p_input)
		{ m_Rnum_str = p_input; }

	const Id& get_R2010_obj_in_rel_ID () const
		{ return m_R2010_obj_in_rel_ID; }

	void set_R2010_obj_in_rel_ID (const Id& p_input)
		{ m_R2010_obj_in_rel_ID = p_input; }

	t_boolean get_R2010_is_conditional () const
		{ return ((m_consolidated_flag & 0x000100) == 0x000100); }

	void set_R2010_is_conditional (t_boolean p_input)
		{
		    if (p_input)
			m_consolidated_flag |= 0x000100;
		    else
			m_consolidated_flag &= 0xfff7ff;
		}

	t_boolean get_R2010_is_many () const
		{ return ((m_consolidated_flag & 0x001000) == 0x001000); }

	void set_R2010_is_many (t_boolean p_input)
		{
		    if (p_input)
			m_consolidated_flag |= 0x001000;
		    else
			m_consolidated_flag &= 0xff7fff;
		}

	const Description& get_R2010_phrase () const
		{ return m_R2010_phrase; }

	void set_R2010_phrase (const Description& p_input)
		{ m_R2010_phrase = p_input; }

	const Id& get_R2011_obj_in_rel_ID () const
		{ return m_R2011_obj_in_rel_ID; }

	void set_R2011_obj_in_rel_ID (const Id& p_input)
		{ m_R2011_obj_in_rel_ID = p_input; }

	t_boolean get_R2011_is_conditional () const
		{ return ((m_consolidated_flag & 0x010000) == 0x010000); }

	void set_R2011_is_conditional (t_boolean p_input)
		{
		    if (p_input)
			m_consolidated_flag |= 0x010000;
		    else
			m_consolidated_flag &= 0xf7ffff;
		}

	t_boolean get_R2011_is_many () const
		{ return ((m_consolidated_flag & 0x100000) == 0x100000); }

	void set_R2011_is_many (t_boolean p_input)
		{
		    if (p_input)
			m_consolidated_flag |= 0x100000;
		    else
			m_consolidated_flag &= 0x7fffff;
		}

	const Description& get_R2011_phrase () const
		{ return m_R2011_phrase; }

	void set_R2011_phrase (const Description& p_input)
		{ m_R2011_phrase = p_input; }

	static mc_dbms_List< I_Related_Object_Instance_Pair * > *
		get_class_extent_ptr( mc_dbms_database * p_db_ptr );

public:

	long persist() {
		long bytesWritten = 0;

		bytesWritten += writeLong(m_num_with_equal_ids);
		bytesWritten += writeLong(m_consolidated_flag);
		bytesWritten += writeBlob((char*)&m_relationship_ID, sizeof(Id));
		bytesWritten += writeBlob((char*)&m_rel_inst_ID, sizeof(Id));		
		bytesWritten += m_Rnum_str.persist();
		bytesWritten += writeBlob((char*)&m_R2010_obj_in_rel_ID, sizeof(Id));
		bytesWritten += m_R2010_phrase.persist();
		bytesWritten += writeBlob((char*)&m_R2011_obj_in_rel_ID, sizeof(Id));
		bytesWritten += m_R2011_phrase.persist();
		
		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
		return bytesWritten;
	}
	
	void restore() {	
		m_num_with_equal_ids = readLong();
		m_consolidated_flag = readLong();
		readBlob((char*)&m_relationship_ID);
		readBlob((char*)&m_rel_inst_ID);
		m_Rnum_str.restore();
		readBlob((char*)&m_R2010_obj_in_rel_ID);
		
		m_R2010_phrase.restore();
		readBlob((char*)&m_R2011_obj_in_rel_ID);
		m_R2011_phrase.restore();
		
		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
	}
	
	static char* create() {
		I_Related_Object_Instance_Pair* inst = new I_Related_Object_Instance_Pair(true);
		inst->restore();
		return (char*)inst;
	}
private:
	int m_num_with_equal_ids;
	int m_consolidated_flag;
	Id m_relationship_ID;
	Id m_rel_inst_ID;
	Description m_Rnum_str;
	Id m_R2010_obj_in_rel_ID;
	Description m_R2010_phrase;
	Id m_R2011_obj_in_rel_ID;
	Description m_R2011_phrase;


	mc_dbms_relationship_1_m(I_Related_Object_Instance_Pair,m_Related_Object_Pair_R2004_ptr,I_Related_Object_Pair,m_Related_Object_Instance_Pair_R2004_coll,I_Related_Object_Pair*) m_Related_Object_Pair_R2004_ptr;

	mc_dbms_relationship_1_m(I_Related_Object_Instance_Pair,m_Object_Instance_R2010_ptr,I_Object_Instance,m_Related_Object_Instance_Pair_R2010_coll,I_Object_Instance*) m_Object_Instance_R2010_ptr;

	mc_dbms_relationship_1_m(I_Related_Object_Instance_Pair,m_Object_Instance_R2011_ptr,I_Object_Instance,m_Related_Object_Instance_Pair_R2011_coll,I_Object_Instance*) m_Object_Instance_R2011_ptr;

	// Helping functions follow

	I_Related_Object_Instance_Pair (bool  isBeingRestored = false);

};

#endif
