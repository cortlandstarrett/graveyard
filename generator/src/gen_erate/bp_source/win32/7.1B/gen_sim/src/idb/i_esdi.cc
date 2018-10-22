/*========================================================================
 *
 * File:      $RCSfile: i_esdi.cc,v $
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


#include <i_esdi.hh>
#include <i_evt.hh>
#include <i_esdii.hh>
#include <i_idaref.hh>
#include <i_idaref.hh>





I_SM_Evt_Supp_DI *
I_SM_Evt_Supp_DI::create (mc_dbms_database* p_db_ptr,
    const Description& p_name, t_core_data_type p_core_data_type,
    t_user_data_type p_user_data_type)

{
LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt_Supp_DI::create()" ));

I_SM_Evt_Supp_DI * ptr = new( p_db_ptr, I_SM_Evt_Supp_DI::get_mc_dbms_typespec() )
	I_SM_Evt_Supp_DI( p_name, p_core_data_type, p_user_data_type );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt_Supp_DI::create()" ));

return( ptr );

}


I_SM_Evt_Supp_DI::I_SM_Evt_Supp_DI
    (const Description& p_name, t_core_data_type p_core_data_type,
    t_user_data_type p_user_data_type)
    :
    m_name (p_name),
    m_core_data_type (p_core_data_type),
    m_user_data_type (p_user_data_type)

{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt_Supp_DI::I_SM_Evt_Supp_DI()" ));

    unsigned int entire_value = assign_next_id_value( mc_dbms_database::of (this) );
    m_SM_esdi_ID.set_entire_value( entire_value );
    m_SM_esdi_ID.set_class_type( EVENT_DATA_ITEM_TYPE );

m_SM_Evt_R2021_ptr.relate( 0, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt_Supp_DI::I_SM_Evt_Supp_DI()" ));

}


I_SM_Evt_Supp_DI::~I_SM_Evt_Supp_DI ()
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt_Supp_DI::~I_SM_Evt_Supp_DI()" ));

operator delete( this, ""); // Remove from InstanceTracker

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt_Supp_DI::~I_SM_Evt_Supp_DI()" ));

}

void
I_SM_Evt_Supp_DI::relate_R2021( I_SM_Evt * p_SM_Evt_R2021_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt_Supp_DI::relate_R2021()" ));

m_SM_Evt_R2021_ptr.relate( p_SM_Evt_R2021_ptr, this );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt_Supp_DI::relate_R2021()" ));

}

void
I_SM_Evt_Supp_DI::relate_R2023( I_SM_Evt_Supp_DI_Inst * p_SM_Evt_Supp_DI_Inst_R2023_ptr )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt_Supp_DI::relate_R2023()" ));

m_SM_Evt_Supp_DI_Inst_R2023_coll.insert( p_SM_Evt_Supp_DI_Inst_R2023_ptr );

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt_Supp_DI::relate_R2023()" ));

}




mc_dbms_relationship_1_m_body(I_SM_Evt_Supp_DI,m_SM_Evt_R2021_ptr,I_SM_Evt,m_SM_Evt_Supp_DI_R2021_coll);

mc_dbms_relationship_m_1_body(I_SM_Evt_Supp_DI,m_SM_Evt_Supp_DI_Inst_R2023_coll,I_SM_Evt_Supp_DI_Inst,m_SM_Evt_Supp_DI_R2023_ptr);

