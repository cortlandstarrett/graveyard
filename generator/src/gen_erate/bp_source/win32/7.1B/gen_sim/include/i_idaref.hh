/*========================================================================
 *
 * File:      $RCSfile: i_idaref.hh,v $
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

#ifndef I_IDAREF_HH
#define I_IDAREF_HH


#ifdef OLD_FILE_NAMES
#include <DBU_string.hh>
#else
#include <u_string.hh>
#endif


class I_Attribute;
class I_ID_REF_Rel_Obj_Pair;




class I_ID_Attribute_Reference
{
public:

	static mc_dbms_typespec * get_mc_dbms_typespec();

	static I_ID_Attribute_Reference * create( mc_dbms_database * p_db_ptr );

	virtual	~I_ID_Attribute_Reference ();

	void relate_R2009( I_Attribute * );

	void relate_R2008( I_Attribute * );

	void relate_R2007( I_ID_REF_Rel_Obj_Pair * );

	// Return pointers to single cardinality relationships

	I_Attribute * get_Attribute_R2009_ptr()
		{ return( m_Attribute_R2009_ptr ); }

	I_Attribute * get_Attribute_R2008_ptr()
		{ return( m_Attribute_R2008_ptr ); }

	I_ID_REF_Rel_Obj_Pair * get_ID_REF_Rel_Obj_Pair_R2007_ptr()
		{ return( m_ID_REF_Rel_Obj_Pair_R2007_ptr ); }

	// Return pointers to contained collections

	// get/set functions

private:


	mc_dbms_relationship_1_m(I_ID_Attribute_Reference,m_Attribute_R2009_ptr,I_Attribute,m_ID_Attribute_Reference_R2009_coll,I_Attribute*) m_Attribute_R2009_ptr;

	mc_dbms_relationship_1_m(I_ID_Attribute_Reference,m_Attribute_R2008_ptr,I_Attribute,m_ID_Attribute_Reference_R2008_coll,I_Attribute*) m_Attribute_R2008_ptr;

	mc_dbms_relationship_1_m(I_ID_Attribute_Reference,m_ID_REF_Rel_Obj_Pair_R2007_ptr,I_ID_REF_Rel_Obj_Pair,m_ID_Attribute_Reference_R2007_coll,I_ID_REF_Rel_Obj_Pair*) m_ID_REF_Rel_Obj_Pair_R2007_ptr;

	// Helping functions follow

	I_ID_Attribute_Reference (
 );

};

#endif
