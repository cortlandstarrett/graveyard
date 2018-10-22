/*========================================================================
 *
 * File:      $RCSfile: i_oinst.hh,v $
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

#ifndef I_OINST_HH
#define I_OINST_HH


#include <u_typdef.hh>
#include <u_id.hh>
#include <u_string.hh>
#include <d_typdef.hh>
#include <u_desc.hh>

class I_Attribute_Instance;
class I_Object;
class I_Related_Object_Instance_Pair;
class I_SM_Evt_Inst;
class I_object_inst_ref_var;
class I_object_inst_ref_set_var;




class I_Object_Instance

{
public:
	static mc_dbms_typespec * get_mc_dbms_typespec  ();

	static I_Object_Instance * create (mc_dbms_segment * p_seg_ptr,
		t_uint p_related_flag = 0 );

	virtual	~I_Object_Instance ();

	void relate_R2002( I_Attribute_Instance * );

	void relate_R2001( I_Object * );

	void relate_R2001A( I_Object * );

	void relate_R2010( I_Related_Object_Instance_Pair * );

	void relate_R2011( I_Related_Object_Instance_Pair * );

	void relate_R2031( I_SM_Evt_Inst * );

	void relate_R2032( I_SM_Evt_Inst * );

	// Class-extent finds follow

	static I_Object_Instance * 
		find_Object_Instance_by_object_instance_ID(
			mc_dbms_database * p_db_ptr,
			const Id& p_object_instance_ID );

	// Contained collection's finds follow

	I_Attribute_Instance*
		find_Attribute_Instance_R2002_by_attribute_ID(
			const Id& p_attribute_ID ) const;

	I_Attribute_Instance*
		find_Attribute_Instance_R2002_by_core_data_type(
			t_core_data_type p_core_data_type ) const;

	// Return pointers to single cardinality relationships

	I_Object * get_Object_R2001_ptr()
		{ return( m_Object_R2001_ptr ); }

	I_Object * get_Object_R2001A_ptr()
		{ return( m_Object_R2001A_ptr ); }

	// Return pointers to contained collections

	mc_dbms_List< I_Attribute_Instance * > *
		get_Attribute_Instance_R2002_coll_ptr()
			{ return( /*m_Attribute_Instance_R2002_coll.getvalue()? */
                      & m_Attribute_Instance_R2002_coll.getvalue()/* : 0 */); }

	mc_dbms_List< I_Related_Object_Instance_Pair * > *
		get_Related_Object_Instance_Pair_R2010_coll_ptr()
			{ return( & m_Related_Object_Instance_Pair_R2010_coll.getvalue() ); }

	mc_dbms_List< I_Related_Object_Instance_Pair * > *
		get_Related_Object_Instance_Pair_R2011_coll_ptr()
			{ return( & m_Related_Object_Instance_Pair_R2011_coll.getvalue() ); }

	mc_dbms_List< I_SM_Evt_Inst * > *
		get_SM_Evt_Inst_R2031_coll_ptr()
			{ return( & m_SM_Evt_Inst_R2031_coll.getvalue() ); }

	mc_dbms_List< I_SM_Evt_Inst * > *
		get_SM_Evt_Inst_R2032_coll_ptr()
			{ return( & m_SM_Evt_Inst_R2032_coll.getvalue() ); }

	// get/set functions

	const Id& get_object_instance_ID () const
		{ return m_object_instance_ID; }

	t_uint get_related_flag () const
		{ return m_related_flag; }

	void set_related_flag (t_uint p_input)
		{ m_related_flag = p_input; }

	static mc_dbms_List< I_Object_Instance * > *
		get_class_extent_ptr( mc_dbms_database * p_db_ptr );

	virtual t_class_type get_class_type() const
		{ return OBJECT_INST_TYPE; }

    //display functions
    void appendObjectIdAttributes(Description &str);

    void toString(Description &str);


private:

	Id m_object_instance_ID;

	unsigned int m_related_flag;

	mc_dbms_relationship_m_1(I_Object_Instance,m_Attribute_Instance_R2002_coll,I_Attribute_Instance,m_Object_Instance_R2002_ptr,mc_dbms_List<I_Attribute_Instance*>) m_Attribute_Instance_R2002_coll;

	mc_dbms_relationship_1_m(I_Object_Instance,m_Object_R2001_ptr,I_Object,m_Object_Instance_R2001_coll,I_Object*) m_Object_R2001_ptr;

	mc_dbms_relationship_1_1(I_Object_Instance,m_Object_R2001A_ptr,I_Object,m_Object_Instance_R2001A_ptr,I_Object*) m_Object_R2001A_ptr;

	mc_dbms_relationship_m_1(I_Object_Instance,m_Related_Object_Instance_Pair_R2010_coll,I_Related_Object_Instance_Pair,m_Object_Instance_R2010_ptr,mc_dbms_List<I_Related_Object_Instance_Pair*>) m_Related_Object_Instance_Pair_R2010_coll;

	mc_dbms_relationship_m_1(I_Object_Instance,m_Related_Object_Instance_Pair_R2011_coll,I_Related_Object_Instance_Pair,m_Object_Instance_R2011_ptr,mc_dbms_List<I_Related_Object_Instance_Pair*>) m_Related_Object_Instance_Pair_R2011_coll;

	mc_dbms_relationship_m_1(I_Object_Instance,m_SM_Evt_Inst_R2031_coll,I_SM_Evt_Inst,m_Object_Instance_R2031_ptr,mc_dbms_List<I_SM_Evt_Inst*>) m_SM_Evt_Inst_R2031_coll;

	mc_dbms_relationship_m_1(I_Object_Instance,m_SM_Evt_Inst_R2032_coll,I_SM_Evt_Inst,m_Object_Instance_R2032_ptr,mc_dbms_List<I_SM_Evt_Inst*>) m_SM_Evt_Inst_R2032_coll;

//    mc_dbms_relationship_m_1(I_Object_Instance,m_object_inst_ref_var_coll,I_object_inst_ref_var,m_oinst_ptr,mc_dbms_List<I_object_inst_ref_var*>) m_object_inst_ref_var_coll;

	// Helping functions follow

	I_Object_Instance (t_uint p_related_flag);

};

#endif
