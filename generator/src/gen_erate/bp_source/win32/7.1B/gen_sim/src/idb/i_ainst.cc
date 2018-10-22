/*========================================================================
 *
 * File:      $RCSfile: i_ainst.cc,v $
 * Version:   $Revision: 1.12 $
 * Modified:  $Date: 2013/01/10 23:41:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <u_trace.hh>
#include <u_error.hh>
#include <u_util.hh>

#include <i_ainst.hh>
#include <i_oinst.hh>
#include <i_attr.hh>
#include <i_var.hh>





I_Attribute_Instance*
I_Attribute_Instance::create (mc_dbms_segment* p_segment_ptr,
    t_core_data_type p_core_data_type, t_user_data_type p_user_data_type,
    int p_domain_code)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Attribute_Instance::create (p_segment_ptr=0x%08x, p_core_data_type=%d, p_user_data_type=%d).",
	p_segment_ptr, p_core_data_type, p_user_data_type));


    I_Attribute_Instance* ainst_ptr
	= new (p_segment_ptr, I_Attribute_Instance::get_mc_dbms_typespec ())
	    I_Attribute_Instance (p_domain_code);
    

    ainst_ptr->m_var_ptr = I_var::create_in_persistent
	(p_segment_ptr, p_core_data_type, p_user_data_type);
    if (ainst_ptr->m_var_ptr)
    {
	ainst_ptr->m_var_ptr->increment_reference_count ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Attribute_Instance::create (ainst_ptr=0x%08x).", ainst_ptr));
    return (ainst_ptr);
}





I_Attribute_Instance::I_Attribute_Instance (int p_domain_code)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Attribute_Instance::I_Attribute_Instance ()."));

	unsigned long attr_inst_id = 0;
    attr_inst_id |= p_domain_code << 28;

    m_attribute_ID.set_entire_value (attr_inst_id);
    m_attribute_ID.set_class_type (ATTRIBUTE_TYPE);
    m_Object_Instance_R2002_ptr.relate( 0, this );
    m_Attribute_R2002_ptr.relate( 0, this );


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Attribute_Instance::I_Attribute_Instance ()."));
}

I_Attribute_Instance::~I_Attribute_Instance ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Attribute_Instance::~I_Attribute_Instance ()."));


    if ((m_var_ptr) && (m_var_ptr->decrement_reference_count () == 0))
    {
	delete m_var_ptr;
    }

    operator delete( this, ""); // Remove from InstanceTracker

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Attribute_Instance::~I_Attribute_Instance ()."));
}


void
I_Attribute_Instance::relate_R2002
    (I_Object_Instance* p_Object_Instance_R2002_ptr)
{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Attribute_Instance::relate_R2002 ()."));


	m_Object_Instance_R2002_ptr.relate( p_Object_Instance_R2002_ptr, this );

	
    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Attribute_Instance::relate_R2002 ()."));
}


void
I_Attribute_Instance::relate_R2002 (I_Attribute* p_Attribute_R2002_ptr)
{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Attribute_Instance::relate_R2002 ()."));


    m_Attribute_R2002_ptr.relate( p_Attribute_R2002_ptr, this );


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Attribute_Instance::relate_R2002 ()."));
}


t_core_data_type
I_Attribute_Instance::get_core_data_type ()
{
	/*
    LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Attribute_Instance::get_core_data_type ()."));
	*/


    t_core_data_type return_core_data_type = VOID_DATATYPE;
    if (get_Attribute_R2002_ptr ())
    {
	return_core_data_type
	    = get_Attribute_R2002_ptr ()->get_core_data_type ();
    }


	/*
    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Attribute_Instance::get_core_data_type ()."));
	*/

    return return_core_data_type;
}


t_user_data_type
I_Attribute_Instance::get_user_data_type ()
{
	/*
    LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Attribute_Instance::get_user_data_type ()."));
	*/


    t_user_data_type return_user_data_type = USER_DEFINED_USERDATATYPE;
    if (get_Attribute_R2002_ptr ())
    {
	return_user_data_type
	    = get_Attribute_R2002_ptr ()->get_user_data_type ();
    }


	/*
    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Attribute_Instance::get_user_data_type ()."));
	*/

    return return_user_data_type;
}


long I_Attribute_Instance::persist() {
	long bytesWritten = 0;
		
	// Write a flag to indicate if the pointer is null or not
	bytesWritten += m_var_ptr ? writeLong(0) : writeLong(1);

	if (m_var_ptr) {
		bytesWritten += InstanceTracker::Instance::persist((char*)m_var_ptr);
	}
	bytesWritten += writeBlob((char*)&m_attribute_ID, sizeof(Id));

	// Note that the embedded collections are handled at a higher-level,
	// we don't need to deal with them here.
	
	return bytesWritten;
}

void I_Attribute_Instance::restore() {
	long ptrIsNull = readLong();

	if ( !ptrIsNull ) {
		m_var_ptr = (I_var*)InstanceTracker::Instance::create()->m_block;
	}
	readBlob((char*)&m_attribute_ID);

	// Note that the embedded collections are handled at a higher-level,
	// we don't need to deal with them here.
}

char* I_Attribute_Instance::create() {
	I_Attribute_Instance* ainst = new I_Attribute_Instance();
	ainst->restore();
	return (char*)ainst;
}

mc_dbms_relationship_1_m_body(I_Attribute_Instance,m_Object_Instance_R2002_ptr,I_Object_Instance,m_Attribute_Instance_R2002_coll);

mc_dbms_relationship_1_m_body(I_Attribute_Instance,m_Attribute_R2002_ptr,I_Attribute,m_Attribute_Instance_R2002_coll);

