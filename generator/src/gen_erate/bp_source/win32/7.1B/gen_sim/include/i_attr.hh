/*========================================================================
 *
 * File:      $RCSfile: i_attr.hh,v $
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

#ifndef I_ATTR_HH
#define I_ATTR_HH


#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#include <U_id.hh>
#include <DBU_string.hh>
#include <D_typedefs.hh>
#else
#include <u_typdef.hh>
#include <u_id.hh>
#include <u_desc.hh>
#include <d_typdef.hh>
#endif


class I_Object;
class I_Attribute_Instance;
class I_ID_Attribute_Reference;


class I_Attribute : public SerializableObject
{
public:
	static mc_dbms_typespec * get_mc_dbms_typespec ();

	static I_Attribute * create( mc_dbms_database * p_db_ptr,
		const Description& p_name, t_core_data_type p_core_data_type,
		t_user_data_type p_user_data_type = USER_DEFINED_USERDATATYPE);

	virtual	~I_Attribute ();

	void relate_R102( I_Object * );

	void relate_R102A( I_Object * );

	void relate_R2002( I_Attribute_Instance * );

	void relate_R2009( I_ID_Attribute_Reference * );

	void relate_R2008( I_ID_Attribute_Reference * );

	// Return pointers to single cardinality relationships

	I_Object * get_Object_R102_ptr()
		{ return( m_Object_R102_ptr ); }

	I_Object * get_Object_R102A_ptr()
		{ return( m_Object_R102A_ptr ); }


	// Return pointers to contained collections

	mc_dbms_List< I_Attribute_Instance * > *
		get_Attribute_Instance_R2002_coll_ptr()
			{ return( & m_Attribute_Instance_R2002_coll.getvalue() ); }

	mc_dbms_List< I_ID_Attribute_Reference * > *
		get_ID_Attribute_Reference_R2009_coll_ptr()
			{ return( & m_ID_Attribute_Reference_R2009_coll.getvalue() ); }

	mc_dbms_List< I_ID_Attribute_Reference * > *
		get_ID_Attribute_Reference_R2008_coll_ptr()
			{ return( & m_ID_Attribute_Reference_R2008_coll.getvalue() ); }

	// get/set functions

	const Id& get_attribute_ID () const
		{ return m_attribute_ID; }

	void set_attribute_ID (const Id& p_input)
		{ m_attribute_ID = p_input; }

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

	t_boolean get_is_referential_attr () const
		{ return m_is_referential_attr; }

	void set_is_referential_attr (t_boolean p_input)
		{ m_is_referential_attr = p_input; }

	t_boolean get_is_identifier_attr () const
		{ return m_is_identifier_attr; }

	void set_is_identifier_attr (t_boolean p_input)
		{ m_is_identifier_attr = p_input; }

	t_boolean get_is_primary_identifier_attr () const
		{ return m_is_primary_identifier_attr; }

	void set_is_primary_identifier_attr (t_boolean p_input)
		{ m_is_primary_identifier_attr = p_input; }

	t_ulong get_highest_unique_id_value () const
		{ return m_highest_unique_id_value; }

	void increment_highest_unique_id_value ()
		{ m_highest_unique_id_value++; }

public:

	long persist() {
		long bytesWritten = 0;

		bytesWritten += writeBlob((char*)&m_attribute_ID, sizeof(Id));
		bytesWritten += m_name.persist();
		bytesWritten += writeLong(m_core_data_type);
		bytesWritten += writeLong(m_user_data_type);
		bytesWritten += writeLong(m_is_referential_attr);
		bytesWritten += writeLong(m_is_identifier_attr);
		bytesWritten += writeLong(m_is_primary_identifier_attr);
		bytesWritten += writeLong(m_highest_unique_id_value);
		
		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
		return bytesWritten;
	}
	
	void restore() {
		readBlob((char*)&m_attribute_ID);
		m_name.restore();
		m_core_data_type = readLong();
		m_user_data_type = readLong();
		m_is_referential_attr = readLong();
		m_is_identifier_attr = readLong();
		m_is_primary_identifier_attr = readLong();
		m_highest_unique_id_value = readLong();

		// Note that the embedded collections are handled at a higher-level,
		// we don't need to deal with them here.
	}
	
	static char* create() {
		I_Attribute* inst = new I_Attribute();
		inst->restore();
		return (char*)inst;
	}

private:
	Id m_attribute_ID;
	Description m_name;
	t_uint m_core_data_type;
	t_uint m_user_data_type;
	t_boolean m_is_referential_attr;
	t_boolean m_is_identifier_attr;
	t_boolean m_is_primary_identifier_attr;
	t_ulong m_highest_unique_id_value;

	mc_dbms_relationship_1_m(I_Attribute,m_Object_R102_ptr,I_Object,m_Attribute_R102_coll,I_Object*) m_Object_R102_ptr;

	mc_dbms_relationship_1_1(I_Attribute,m_Object_R102A_ptr,I_Object,m_Attribute_R102A_ptr,I_Object*) m_Object_R102A_ptr;

	mc_dbms_relationship_m_1(I_Attribute,m_Attribute_Instance_R2002_coll,I_Attribute_Instance,m_Attribute_R2002_ptr,mc_dbms_List<I_Attribute_Instance*>) m_Attribute_Instance_R2002_coll;

	mc_dbms_relationship_m_1(I_Attribute,m_ID_Attribute_Reference_R2009_coll,I_ID_Attribute_Reference,m_Attribute_R2009_ptr,mc_dbms_List<I_ID_Attribute_Reference*>) m_ID_Attribute_Reference_R2009_coll;

	mc_dbms_relationship_m_1(I_Attribute,m_ID_Attribute_Reference_R2008_coll,I_ID_Attribute_Reference,m_Attribute_R2008_ptr,mc_dbms_List<I_ID_Attribute_Reference*>) m_ID_Attribute_Reference_R2008_coll;

	// Helping functions follow

	I_Attribute ( const Description& p_name, t_core_data_type p_core_data_type,
	    t_user_data_type p_user_data_type );

	/**
	 * This is used only by serialization
	 */	
	I_Attribute() { }
};




#endif