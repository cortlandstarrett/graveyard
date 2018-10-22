/*========================================================================
 *
 * File:      $RCSfile: i_clock.cc,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <sys/types.h>
#include <time.h>


#ifdef OLD_FILE_NAMES
#include <L_log_trace.hh>
#include <L_log_error.hh>
#else
#include <u_trace.hh>
#include <u_error.hh>
#endif


#include <i_clock.hh>


extern mc_dbms_database* GS_gen_sim_db_ptr;





I_Clock*
I_Clock::find_ptr ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin I_Clock::find_ptr ()."));


    if (! GS_gen_sim_db_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #1:  I_Clock::find_ptr (0):  GS_gen_sim_db_ptr == 0."));
	return 0;
    }


    I_Clock* clock_ptr = 0;
    mc_dbms_database_root* root_ptr
	= GS_gen_sim_db_ptr->find_root ("I_Clock_class_extent");
    if (! root_ptr)
    {
	root_ptr = GS_gen_sim_db_ptr->create_root ("I_Clock_class_extent");
	root_ptr->set_value (0);
    }
    if (! root_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #2:  I_Clock::find_ptr (0):  root_ptr == 0."));
	return 0;
    }


    clock_ptr = (I_Clock*) root_ptr->get_value ();
    if (! clock_ptr)
    {
	clock_ptr = new (GS_gen_sim_db_ptr, I_Clock::get_mc_dbms_typespec ())
	    I_Clock ();
	root_ptr->set_value (clock_ptr);
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End #3:  I_Clock::find (clock_ptr=0x%08x)",
	clock_ptr));
    return (clock_ptr);
}





I_Clock::I_Clock ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_Clock::I_Clock ()."));

    m_timestamp.reset ();


    m_tick_us					= 100000;

    m_actn_us					= 10000;

    m_stmt_us__select_related_by		= 5000;
    m_stmt_us__select_from_instances_of		= 5000;
    m_stmt_us__for_initial			= 5000;
    m_stmt_us__for_iteration			= 5000;
    m_stmt_us__while_initial			= 5000;
    m_stmt_us__while_iteration                  = 5000;
    m_stmt_us__break    			= 5000;
    m_stmt_us__continue  			= 5000;
    m_stmt_us__return   			= 5000;
    m_stmt_us__create_object_instance		= 5000;
    m_stmt_us__delete_object_instance		= 5000;
    m_stmt_us__relate				= 5000;
    m_stmt_us__unrelate				= 5000;
    m_stmt_us__generate				= 5000;
    m_stmt_us__create_event_instance		= 5000;
    m_stmt_us__assign				= 5000;
    m_stmt_us__transformer			= 5000;
    m_stmt_us__if				= 5000;
    m_stmt_us__elif				= 5000;
    m_stmt_us__bridge				= 5000;
    m_stmt_us__synch_service		= 5000;


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End  I_Clock::I_Clock ()."));
}





I_Clock::~I_Clock ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_Clock::~I_Clock ()."));


    mc_dbms_database_root* root_ptr
	= GS_gen_sim_db_ptr->find_root ("I_Clock_class_extent");
    if (! root_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "I_Clock::~I_Clock ():  root does not exist!."));
    }
    else
    {
	I_Clock* clock_ptr = (I_Clock*) root_ptr->get_value ();
	if (clock_ptr != this)
	{
	    LOG_ERROR ((L_log_string,
		"I_Clock::~I_Clock ():  pointer in root does not match destructor! - leaving pointer alone in root."));
	}
	else
	{
	    root_ptr->set_value (0);
	}
    }

    operator delete( this, ""); // Remove from InstanceTracker

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End  I_Clock::~I_Clock ()."));
}
