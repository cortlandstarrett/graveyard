/*========================================================================
 *
 * File:      $RCSfile: i_ainst.hh,v $
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

#ifndef I_AINST_HH
#define I_AINST_HH


#include <u_typdef.hh>
#include <u_id.hh>
#include <d_typdef.hh>
#include <u_util.hh>


class I_Attribute;
class I_Object_Instance;
class I_var;
class Description;

#define UNKNOWN_DOMAIN 16


class I_Attribute_Instance : public SerializableObject

{
public:
	static mc_dbms_typespec* get_mc_dbms_typespec();

	static I_Attribute_Instance* create (mc_dbms_segment* p_seg_ptr,
		t_core_data_type p_core_data_type,
		t_user_data_type p_user_data_type,
        int domain_code);

	virtual	~I_Attribute_Instance ();

	void relate_R2002( I_Object_Instance * );

	void relate_R2002( I_Attribute * );

	// Return pointers to single cardinality relationships

	I_Object_Instance * get_Object_Instance_R2002_ptr()
		{ return( m_Object_Instance_R2002_ptr ); }

	I_Attribute * get_Attribute_R2002_ptr()
		{ return( m_Attribute_R2002_ptr ); }

	// get/set functions

	const Id& get_attribute_ID () const
		{ return m_attribute_ID; }

	void set_attribute_ID (const Id& p_input)
		{ m_attribute_ID = p_input; }

	t_core_data_type get_core_data_type ();

	t_user_data_type get_user_data_type ();

	I_var* get_var_ptr ();

public:

	virtual long persist();
	virtual void restore();
	static char* create();

private:

	I_var* m_var_ptr;
	Id m_attribute_ID;

	mc_dbms_relationship_1_m(I_Attribute_Instance,m_Object_Instance_R2002_ptr,I_Object_Instance,m_Attribute_Instance_R2002_coll,I_Object_Instance*) m_Object_Instance_R2002_ptr;

	mc_dbms_relationship_1_m(I_Attribute_Instance,m_Attribute_R2002_ptr,I_Attribute,m_Attribute_Instance_R2002_coll,I_Attribute*) m_Attribute_R2002_ptr;

	// Helping functions follow
	I_Attribute_Instance (int domain_code);

	/**
	 * This constructor is used only by the serialization mechanism.
	 */
	I_Attribute_Instance() : m_var_ptr(0) { }

	t_boolean ____get_var_ptr (I_var*& p_var_ptr, Description& p_var_str);

};




#endif
