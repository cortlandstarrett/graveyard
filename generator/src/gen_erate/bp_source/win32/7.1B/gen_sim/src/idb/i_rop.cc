/*========================================================================
 *
 * File:      $RCSfile: i_rop.cc,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:41:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifdef OLD_FILE_NAMES
#include <L_log_trace.hh>
#include <L_log_error.hh>
#include <DBU_utility.hh>
#else
#include <u_trace.hh>
#include <u_error.hh>
#include <u_util.hh>
#endif


#include <i_rop.hh>
#include <i_obj.hh>
#include <i_obj.hh>
#include <i_rel.hh>
#include <i_roip.hh>





I_Related_Object_Pair *
I_Related_Object_Pair::create( mc_dbms_database * p_db_ptr
,
		int p_ONE_side_is_conditional,
		int p_ONE_side_is_many,
		int p_OTH_side_is_conditional,
		int p_OTH_side_is_many )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Pair::create()" ));

I_Related_Object_Pair * ptr = new( p_db_ptr, I_Related_Object_Pair::get_mc_dbms_typespec() )
	I_Related_Object_Pair(
		p_ONE_side_is_conditional,
		p_ONE_side_is_many,
		p_OTH_side_is_conditional,
		p_OTH_side_is_many );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Pair::create()" ));

return( ptr );

}


I_Related_Object_Pair::I_Related_Object_Pair (
		int p_ONE_side_is_conditional,
		int p_ONE_side_is_many,
		int p_OTH_side_is_conditional,
		int p_OTH_side_is_many )
		:
		m_ONE_side_is_conditional( p_ONE_side_is_conditional ),
		m_ONE_side_is_many( p_ONE_side_is_many ),
		m_OTH_side_is_conditional( p_OTH_side_is_conditional ),
		m_OTH_side_is_many( p_OTH_side_is_many )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Pair::I_Related_Object_Pair()" ));

m_Object_R2006_ptr.relate( 0, this );
m_Object_R2005_ptr.relate( 0, this );
m_Relationship_R2003_ptr.relate( 0, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Pair::I_Related_Object_Pair()" ));

}


I_Related_Object_Pair::~I_Related_Object_Pair ()
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Pair::~I_Related_Object_Pair()" ));

operator delete( this, ""); // Remove from InstanceTracker

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Pair::~I_Related_Object_Pair()" ));

}




void
I_Related_Object_Pair::relate_R2006( I_Object * p_Object_R2006_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Pair::relate_R2006()" ));

m_Object_R2006_ptr.relate( p_Object_R2006_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Pair::relate_R2006()" ));

}

void
I_Related_Object_Pair::relate_R2005( I_Object * p_Object_R2005_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Pair::relate_R2005()" ));

m_Object_R2005_ptr.relate( p_Object_R2005_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Pair::relate_R2005()" ));

}

void
I_Related_Object_Pair::relate_R2003( I_Relationship * p_Relationship_R2003_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Pair::relate_R2003()" ));

m_Relationship_R2003_ptr.relate( p_Relationship_R2003_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Pair::relate_R2003()" ));

}

void
I_Related_Object_Pair::relate_R2004( I_Related_Object_Instance_Pair * p_Related_Object_Instance_Pair_R2004_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Related_Object_Pair::relate_R2004()" ));

m_Related_Object_Instance_Pair_R2004_coll.insert( p_Related_Object_Instance_Pair_R2004_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Related_Object_Pair::relate_R2004()" ));

}




mc_dbms_relationship_1_m_body(I_Related_Object_Pair,m_Object_R2006_ptr,I_Object,m_Related_Object_Pair_R2006_coll);

mc_dbms_relationship_1_m_body(I_Related_Object_Pair,m_Object_R2005_ptr,I_Object,m_Related_Object_Pair_R2005_coll);

mc_dbms_relationship_1_m_body(I_Related_Object_Pair,m_Relationship_R2003_ptr,I_Relationship,m_Related_Object_Pair_R2003_coll);

mc_dbms_relationship_m_1_body(I_Related_Object_Pair,m_Related_Object_Instance_Pair_R2004_coll,I_Related_Object_Instance_Pair,m_Related_Object_Pair_R2004_ptr);

