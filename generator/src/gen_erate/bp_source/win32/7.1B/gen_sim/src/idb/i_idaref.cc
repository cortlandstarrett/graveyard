/*========================================================================
 *
 * File:      $RCSfile: i_idaref.cc,v $
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


#include <i_idaref.hh>
#include <i_attr.hh>
#include <i_ir_rop.hh>


I_ID_Attribute_Reference *
I_ID_Attribute_Reference::create( mc_dbms_database * p_db_ptr
 )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_ID_Attribute_Reference::create()" ));

I_ID_Attribute_Reference * ptr = new( p_db_ptr, I_ID_Attribute_Reference::get_mc_dbms_typespec() )
	I_ID_Attribute_Reference(
 );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_ID_Attribute_Reference::create()" ));

return( ptr );

}


I_ID_Attribute_Reference::I_ID_Attribute_Reference (
 )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_ID_Attribute_Reference::I_ID_Attribute_Reference()" ));

m_Attribute_R2009_ptr.relate( 0, this );
m_Attribute_R2008_ptr.relate( 0, this );
m_ID_REF_Rel_Obj_Pair_R2007_ptr.relate( 0, this );


LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_ID_Attribute_Reference::I_ID_Attribute_Reference()" ));

}


I_ID_Attribute_Reference::~I_ID_Attribute_Reference ()
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_ID_Attribute_Reference::~I_ID_Attribute_Reference()" ));

operator delete( this, ""); // Remove from InstanceTracker

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_ID_Attribute_Reference::~I_ID_Attribute_Reference()" ));

}

void
I_ID_Attribute_Reference::relate_R2009( I_Attribute * p_Attribute_R2009_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_ID_Attribute_Reference::relate_R2009()" ));

m_Attribute_R2009_ptr.relate( p_Attribute_R2009_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_ID_Attribute_Reference::relate_R2009()" ));

}

void
I_ID_Attribute_Reference::relate_R2008( I_Attribute * p_Attribute_R2008_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_ID_Attribute_Reference::relate_R2008()" ));

m_Attribute_R2008_ptr.relate( p_Attribute_R2008_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_ID_Attribute_Reference::relate_R2008()" ));

}

void
I_ID_Attribute_Reference::relate_R2007( I_ID_REF_Rel_Obj_Pair * p_ID_REF_Rel_Obj_Pair_R2007_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_ID_Attribute_Reference::relate_R2007()" ));

m_ID_REF_Rel_Obj_Pair_R2007_ptr.relate( p_ID_REF_Rel_Obj_Pair_R2007_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_ID_Attribute_Reference::relate_R2007()" ));

}



mc_dbms_relationship_1_m_body(I_ID_Attribute_Reference,m_Attribute_R2009_ptr,I_Attribute,m_ID_Attribute_Reference_R2009_coll);

mc_dbms_relationship_1_m_body(I_ID_Attribute_Reference,m_Attribute_R2008_ptr,I_Attribute,m_ID_Attribute_Reference_R2008_coll);

mc_dbms_relationship_1_m_body(I_ID_Attribute_Reference,m_ID_REF_Rel_Obj_Pair_R2007_ptr,I_ID_REF_Rel_Obj_Pair,m_ID_Attribute_Reference_R2007_coll);

