/*========================================================================
 *
 * File:      $RCSfile: i_attr.cc,v $
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


#include <i_attr.hh>
#include <i_obj.hh>
#include <i_ainst.hh>
#include <i_idaref.hh>
#include <i_idaref.hh>





I_Attribute *
I_Attribute::create( mc_dbms_database * p_db_ptr,
	const Description& p_name, t_core_data_type p_core_data_type,
	t_user_data_type p_user_data_type )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Attribute::create()" ));

I_Attribute * ptr = new( p_db_ptr, I_Attribute::get_mc_dbms_typespec() )
	I_Attribute( p_name, p_core_data_type, p_user_data_type );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Attribute::create()" ));

return( ptr );

}


I_Attribute::I_Attribute (const Description& p_name, t_core_data_type p_core_data_type,
    t_user_data_type p_user_data_type)
    :
    m_name (p_name),
    m_core_data_type (p_core_data_type),
    m_user_data_type (p_user_data_type)

{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Attribute::I_Attribute()" ));

    unsigned int entire_value = assign_next_id_value( mc_dbms_database::of (this) );
    m_attribute_ID.set_entire_value( entire_value );
    m_attribute_ID.set_class_type( ATTRIBUTE_TYPE );


m_Object_R102_ptr.relate( 0, this);
m_Object_R102A_ptr = 0;

m_is_referential_attr = FALSE;
m_is_identifier_attr = FALSE;
m_is_primary_identifier_attr = FALSE;
m_highest_unique_id_value = (t_ulong) 0;


LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Attribute::I_Attribute()" ));

}


I_Attribute::~I_Attribute ()
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Attribute::~I_Attribute()" ));


operator delete( this, ""); // Remove from InstanceTracker

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Attribute::~I_Attribute()" ));

}


void
I_Attribute::relate_R102( I_Object * p_Object_R102_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Attribute::relate_R102()" ));

m_Object_R102_ptr.relate( p_Object_R102_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Attribute::relate_R102()" ));

}


void
I_Attribute::relate_R102A( I_Object * p_Object_R102A_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Attribute::relate_R102A()" ));

m_Object_R102A_ptr = p_Object_R102A_ptr;

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Attribute::relate_R102A()" ));

}

void
I_Attribute::relate_R2002( I_Attribute_Instance * p_Attribute_Instance_R2002_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Attribute::relate_R2002()" ));

m_Attribute_Instance_R2002_coll.insert( p_Attribute_Instance_R2002_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Attribute::relate_R2002()" ));

}

void
I_Attribute::relate_R2009( I_ID_Attribute_Reference * p_ID_Attribute_Reference_R2009_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Attribute::relate_R2009()" ));

m_ID_Attribute_Reference_R2009_coll.insert( p_ID_Attribute_Reference_R2009_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Attribute::relate_R2009()" ));

}

void
I_Attribute::relate_R2008( I_ID_Attribute_Reference * p_ID_Attribute_Reference_R2008_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Attribute::relate_R2008()" ));

m_ID_Attribute_Reference_R2008_coll.insert( p_ID_Attribute_Reference_R2008_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Attribute::relate_R2008()" ));

}




mc_dbms_relationship_1_m_body(I_Attribute,m_Object_R102_ptr,I_Object,m_Attribute_R102_coll);

mc_dbms_relationship_1_1_body(I_Attribute,m_Object_R102A_ptr,I_Object,m_Attribute_R102A_ptr);

mc_dbms_relationship_m_1_body(I_Attribute,m_Attribute_Instance_R2002_coll,I_Attribute_Instance,m_Attribute_R2002_ptr);

mc_dbms_relationship_m_1_body(I_Attribute,m_ID_Attribute_Reference_R2009_coll,I_ID_Attribute_Reference,m_Attribute_R2009_ptr);

mc_dbms_relationship_m_1_body(I_Attribute,m_ID_Attribute_Reference_R2008_coll,I_ID_Attribute_Reference,m_Attribute_R2008_ptr);

