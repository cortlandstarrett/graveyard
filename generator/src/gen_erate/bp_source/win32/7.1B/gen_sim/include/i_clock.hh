/*========================================================================
 *
 * File:      $RCSfile: i_clock.hh,v $
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

#ifndef I_CLOCK_HH
#define I_CLOCK_HH


#ifdef OLD_FILE_NAMES
#include <DBU_string.hh>
#include <U_typedefs.hh>
#else
#include <u_string.hh>
#include <u_typdef.hh>
#endif


#include <i_var.hh>

class D_sm_state;
class I_SM_Evt;




class I_Clock
{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

    ///Access to the filename of the OOA file that the 
    // simulation is based on (kuldge, this should be in it own class)
    static const char *	get_ooaFilename ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
                                    return clock_ptr->ooaFilename.char_ptr();
			    }
			    return NULL;
			}

    static void	        set_ooaFilename (const char * ooaFilename_)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
                                    clock_ptr->ooaFilename=ooaFilename_;
			    }
			}


	// presistant Access to the breakpoints (kuldge, this should be in it own class)
    static mc_dbms_Set<D_sm_state*> *get_breakpoint_state(){
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr) return &(clock_ptr->state);
			    return NULL;
			}


    ///persistant access to the information that should logically be placed in this class
    static Description	get_value_str ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    Description return_str;
			    if (clock_ptr)
			    {
				return_str = clock_ptr->m_timestamp.
				    get_var_ptr ()->get_value_str ();
			    }
			    return return_str;
			}


    static I_timestamp_var&
			current_time ()
			{
			    return find_ptr ()->m_timestamp;
			}

    static void		reset_time ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp.reset ();
			    }
			}


    static void		add_exec_time__tick ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->m_tick_us;
			    }
			}


    static void		add_exec_time__actn ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->m_actn_us;
			    }
			}


    static void		add_exec_time__stmt__select_related_by ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__select_related_by;
			    }
			}


    static void		add_exec_time__stmt__select_from_instances_of ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__select_from_instances_of;
			    }
			}


    static void		add_exec_time__stmt__for_initial ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__for_initial;
			    }
			}


    static void		add_exec_time__stmt__for_iteration ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__for_iteration;
			    }
			}

    static void		add_exec_time__stmt__while_initial ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__while_initial;
			    }
			}


    static void		add_exec_time__stmt__while_iteration ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__while_iteration;
			    }
			}

    static void		add_exec_time__stmt__break ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__break;
			    }
			}

    static void		add_exec_time__stmt__continue ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__continue;
			    }
			}

    static void		add_exec_time__stmt__return ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__return;
			    }
			}


    static void		add_exec_time__stmt__create_object_instance ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__create_object_instance;
			    }
			}


    static void		add_exec_time__stmt__delete_object_instance ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__delete_object_instance;
			    }
			}


    static void		add_exec_time__stmt__relate ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__relate;
			    }
			}


    static void		add_exec_time__stmt__unrelate ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__unrelate;
			    }
			}


    static void		add_exec_time__stmt__generate ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__generate;
			    }
			}


    static void		add_exec_time__stmt__create_event_instance ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__create_event_instance;
			    }
			}


    static void		add_exec_time__stmt__assign ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__assign;
			    }
			}


    static void		add_exec_time__stmt__transformation ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__transformer;
			    }
			}


    static void		add_exec_time__stmt__if ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__if;
			    }
			}

    static void		add_exec_time__stmt__elif ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__elif;
			    }
			}


    static void		add_exec_time__stmt__bridge ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__bridge;
			    }
			}

    static void		add_exec_time__stmt__synch_service ()
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_timestamp += clock_ptr->
				    m_stmt_us__synch_service;
			    }
			}



    static void		set_time__tick (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_tick_us = p_us;
			    }
			}


    static void		set_time__actn (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_actn_us = p_us;
			    }
			}


    static void		set_time__stmt__select_related_by (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__select_related_by = p_us;
			    }
			}


    static void		set_time__stmt__select_from_instances_of (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__select_from_instances_of
				    = p_us;
			    }
			}


    static void		set_time__stmt__for_initial (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__for_initial = p_us;
			    }
			}


    static void		set_time__stmt__for_iteration (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__for_iteration = p_us;
			    }
			}


    static void		set_time__stmt__while_initial (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__while_initial = p_us;
			    }
			}


    static void		set_time__stmt__while_iteration (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__while_iteration = p_us;
			    }
			}


    static void		set_time__stmt__break (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__break = p_us;
			    }
			}


    static void		set_time__stmt__continue (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__continue = p_us;
			    }
			}


    static void		set_time__stmt__return (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__return = p_us;
			    }
			}


     static void	set_time__stmt__create_object_instance (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__create_object_instance
				    = p_us;
			    }
			}


    static void		set_time__stmt__delete_object_instance (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__delete_object_instance
				    = p_us;
			    }
			}


    static void		set_time__stmt__relate (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__relate = p_us;
			    }
			}


    static void		set_time__stmt__unrelate (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__unrelate = p_us;
			    }
			}


    static void		set_time__stmt__generate (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__generate = p_us;
			    }
			}


    static void		set_time__stmt__create_event_instance (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__create_event_instance
				    = p_us;
			    }
			}


    static void		set_time__stmt__assign (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__assign = p_us;
			    }
			}


    static void		set_time__stmt__transformation (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__transformer = p_us;
			    }
			}


    static void		set_time__stmt__if (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__if = p_us;
			    }
			}


    static void		set_time__stmt__elif (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__elif = p_us;
			    }
			}


    static void		set_time__stmt__bridge (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__bridge = p_us;
			    }
			}

    static void		set_time__stmt__synch_service (t_ulong p_us)
			{
			    I_Clock* clock_ptr = find_ptr ();
			    if (clock_ptr)
			    {
				clock_ptr->m_stmt_us__synch_service = p_us;
			    }
			}

    static void		get_times
      (t_ulong& p_tick_us,
       t_ulong& p_action_us,
       t_ulong& p_select_related_by_us,
       t_ulong& p_select_from_instances_of_us,
       t_ulong& p_for_initial_us,
       t_ulong& p_for_iteration_us,
       t_ulong& p_while_initial_us,
       t_ulong& p_while_iteration_us,
       t_ulong& p_break_us,
       t_ulong& p_continue_us,
       t_ulong& p_return_us,
       t_ulong& p_create_object_instance_us,
       t_ulong& p_delete_object_instance_us,
       t_ulong& p_relate_us,
       t_ulong& p_unrelate_us,
       t_ulong& p_generate_us,
       t_ulong& p_create_event_instance_us,
       t_ulong& p_assign_us,
       t_ulong& p_transformer_us,
       t_ulong& p_if_us,
       t_ulong& p_elif_us,
       t_ulong& p_bridge_us,
       t_ulong& p_synch_service_us)
    {
      I_Clock* clock_ptr = find_ptr ();
      if (clock_ptr)
        {
          p_tick_us                     = clock_ptr->m_tick_us;
          p_action_us                   = clock_ptr->m_actn_us;
          p_select_related_by_us        = clock_ptr->m_stmt_us__select_related_by;
          p_select_from_instances_of_us = clock_ptr->m_stmt_us__select_from_instances_of;
          p_for_initial_us              = clock_ptr->m_stmt_us__for_initial;
          p_for_iteration_us            = clock_ptr->m_stmt_us__for_iteration;
          p_while_initial_us            = clock_ptr->m_stmt_us__while_initial;
          p_while_iteration_us          = clock_ptr->m_stmt_us__while_iteration;
          p_break_us                    = clock_ptr->m_stmt_us__break;
          p_continue_us                 = clock_ptr->m_stmt_us__continue;
          p_return_us                   = clock_ptr->m_stmt_us__return;
          p_create_object_instance_us   = clock_ptr->m_stmt_us__create_object_instance;
          p_delete_object_instance_us   = clock_ptr->m_stmt_us__delete_object_instance;
          p_relate_us                   = clock_ptr->m_stmt_us__relate;
          p_unrelate_us                 = clock_ptr->m_stmt_us__unrelate;
          p_generate_us                 = clock_ptr->m_stmt_us__generate;
          p_create_event_instance_us    = clock_ptr->m_stmt_us__create_event_instance;
          p_assign_us                   = clock_ptr->m_stmt_us__assign;
          p_transformer_us              = clock_ptr->m_stmt_us__transformer;
          p_if_us                       = clock_ptr->m_stmt_us__if;
          p_elif_us                     = clock_ptr->m_stmt_us__elif;
          p_bridge_us                   = clock_ptr->m_stmt_us__bridge;
          p_synch_service_us            = clock_ptr->m_stmt_us__synch_service;
        }
    }



private:
    String ooaFilename; 
    //see the note in BreakPoint::BreakPoint()
    //mc_dbms_Set<D_sm_state*> creation;  		      
    mc_dbms_Set<D_sm_state*> state;  		  
    // five of these things are not like the other (SeameStreet) but for now
    // the above listed elements will do for persistant storage
 	    
    
    I_timestamp_var	m_timestamp;


    t_ulong		m_tick_us;

    t_ulong		m_actn_us;

    t_ulong		m_stmt_us__select_related_by;
    t_ulong		m_stmt_us__select_from_instances_of;
    t_ulong		m_stmt_us__for_initial;
    t_ulong		m_stmt_us__for_iteration;
    t_ulong		m_stmt_us__while_initial;
    t_ulong		m_stmt_us__while_iteration;
    t_ulong		m_stmt_us__break;
    t_ulong		m_stmt_us__continue;
    t_ulong		m_stmt_us__return;
    t_ulong		m_stmt_us__create_object_instance;
    t_ulong		m_stmt_us__delete_object_instance;
    t_ulong		m_stmt_us__relate;
    t_ulong		m_stmt_us__unrelate;
    t_ulong		m_stmt_us__generate;
    t_ulong		m_stmt_us__create_event_instance;
    t_ulong		m_stmt_us__assign;
    t_ulong		m_stmt_us__transformer;
    t_ulong		m_stmt_us__if;
    t_ulong		m_stmt_us__elif;
    t_ulong		m_stmt_us__bridge;
	t_ulong		m_stmt_us__synch_service;


    static I_Clock*	find_ptr ();
    			I_Clock ();
    virtual		~I_Clock ();
};




#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
