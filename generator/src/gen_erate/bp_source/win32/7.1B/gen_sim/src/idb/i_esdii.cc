/*========================================================================
 *
 * File:      $RCSfile: i_esdii.cc,v $
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


#include <i_esdii.hh>
#include <i_einst.hh>
#include <i_esdi.hh>
#include <i_clock.hh>





I_var*
I_SM_Evt_Supp_DI_Inst::get_var_ptr ()

{
    return m_var_ptr;
}




I_SM_Evt_Supp_DI_Inst*
I_SM_Evt_Supp_DI_Inst::create (mc_dbms_database* p_db_ptr,
    t_core_data_type p_core_data_type, t_user_data_type p_user_data_type)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Supp_DI_Inst::create (p_db_ptr=0x%08x, p_core_data_type=%d, p_user_data_type=%d).",
	p_db_ptr, p_core_data_type, p_user_data_type));


    I_SM_Evt_Supp_DI_Inst* esdii_ptr
	= new (p_db_ptr, I_SM_Evt_Supp_DI_Inst::get_mc_dbms_typespec ())
	    I_SM_Evt_Supp_DI_Inst ();
    

    I_var* transient_var_ptr
	= I_var::create_in_transient (p_core_data_type, p_user_data_type);
    esdii_ptr->m_var_ptr = transient_var_ptr->clone_to_persistent ();
    delete transient_var_ptr;
    if (esdii_ptr->m_var_ptr)
    {
	esdii_ptr->m_var_ptr->increment_reference_count ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Supp_DI_Inst::create (esdii_ptr=0x%08x).",
	esdii_ptr));
    return (esdii_ptr);
}





I_SM_Evt_Supp_DI_Inst::I_SM_Evt_Supp_DI_Inst ()
{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Supp_DI_Inst::I_SM_Evt_Supp_DI_Inst ()."));

    m_SM_esdi_ID.set_class_type( EVENT_DATA_ITEM_TYPE );


    m_SM_Evt_Inst_R2023_ptr.relate( 0, this );
    m_SM_Evt_Supp_DI_R2023_ptr.relate( 0, this );


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Supp_DI_Inst::I_SM_Evt_Supp_DI_Inst ()."));
}





I_SM_Evt_Supp_DI_Inst::~I_SM_Evt_Supp_DI_Inst ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Supp_DI_Inst::~I_SM_Evt_Supp_DI_Inst ()."));


    if ((m_var_ptr) && (m_var_ptr->decrement_reference_count () == 0))
    {
	delete m_var_ptr;
    }

    operator delete( this, ""); // Remove from InstanceTracker

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Supp_DI_Inst::~I_SM_Evt_Supp_DI_Inst ()."));
}





void
I_SM_Evt_Supp_DI_Inst::relate_R2023 (I_SM_Evt_Inst* p_SM_Evt_Inst_R2023_ptr)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Supp_DI_Inst::relate_R2023 ()."));


    m_SM_Evt_Inst_R2023_ptr.relate( p_SM_Evt_Inst_R2023_ptr, this );


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Supp_DI_Inst::relate_R2023 ()."));
}





void
I_SM_Evt_Supp_DI_Inst::relate_R2023
    (I_SM_Evt_Supp_DI* p_SM_Evt_Supp_DI_R2023_ptr)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Supp_DI_Inst::relate_R2023 ()."));


    m_SM_Evt_Supp_DI_R2023_ptr.relate( p_SM_Evt_Supp_DI_R2023_ptr, this );


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Supp_DI_Inst::relate_R2023 ()."));
}





t_core_data_type
I_SM_Evt_Supp_DI_Inst::get_core_data_type ()

{
    LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Supp_DI_Inst::get_core_data_type ()."));


    t_core_data_type return_core_data_type = VOID_DATATYPE;
    if (get_SM_Evt_Supp_DI_R2023_ptr ())
    {
	return_core_data_type
	    = get_SM_Evt_Supp_DI_R2023_ptr ()->get_core_data_type ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Supp_DI_Inst::get_core_data_type ()."));
    return return_core_data_type;
}





t_user_data_type
I_SM_Evt_Supp_DI_Inst::get_user_data_type ()

{
    LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Supp_DI_Inst::get_user_data_type ()."));


    t_user_data_type return_user_data_type = USER_DEFINED_USERDATATYPE;
    if (get_SM_Evt_Supp_DI_R2023_ptr ())
    {
	return_user_data_type
	    = get_SM_Evt_Supp_DI_R2023_ptr ()->get_user_data_type ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Supp_DI_Inst::get_user_data_type ()."));
    return return_user_data_type;
}






mc_dbms_relationship_1_m_body(I_SM_Evt_Supp_DI_Inst,m_SM_Evt_Inst_R2023_ptr,I_SM_Evt_Inst,m_SM_Evt_Supp_DI_Inst_R2023_coll);

mc_dbms_relationship_1_m_body(I_SM_Evt_Supp_DI_Inst,m_SM_Evt_Supp_DI_R2023_ptr,I_SM_Evt_Supp_DI,m_SM_Evt_Supp_DI_Inst_R2023_coll);

