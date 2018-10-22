/*========================================================================
 *
 * File:      $RCSfile: i_einst.cc,v $
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
#include <u_cursor.hh>
#include <u_trace.hh>
#include <u_error.hh>
#include <u_util.hh>

#include <i_einst.hh>
#include <i_oinst.hh>
#include <i_esdi.hh>
#include <i_esdii.hh>
#include <i_evt.hh>
#include <i_roip.hh>
#include <i_roip.hh>
#include <i_clock.hh>

#include <d_smevt.hh>
#include <gs_find.hh>

extern mc_dbms_database*		GS_gen_sim_db_ptr;




I_SM_Evt_Inst*
I_SM_Evt_Inst::create (mc_dbms_database* p_db_ptr)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered  I_SM_Evt_Inst::create ()."));


    I_SM_Evt_Inst* ptr
	= new (p_db_ptr, I_SM_Evt_Inst::get_mc_dbms_typespec ()) I_SM_Evt_Inst ();


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted  I_SM_Evt_Inst::create ()."));
    return (ptr);
}


I_SM_Evt_Inst::I_SM_Evt_Inst ()
    :
    m_expiration_timestamp (I_Clock::current_time ()),
    m_recurring_microseconds ((t_ulong) 0),
    m_is_creation_event (0),
    m_is_polymorphic_delivery (FALSE),
    m_poly_relationship_ID (Id::Default)

{
    LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_SM_Evt_Inst::I_SM_Evt_Inst()" ));


    unsigned int entire_value = 0;
    {
	Id_assigner* id_assigner_ptr;
	mc_dbms_database_root* root_ptr
	    = GS_gen_sim_db_ptr->find_root ("EINST_Id_assigner");

	if (root_ptr)
	{
	    id_assigner_ptr = (Id_assigner*) root_ptr->get_value ();
	}
	else
	{
	    mc_dbms_typespec* id_assigner_type = new mc_dbms_typespec ("Id_assigner",sizeof(Id_assigner));
	    id_assigner_ptr = new (GS_gen_sim_db_ptr, id_assigner_type)
		Id_assigner (0,0,0,0);
	    GS_gen_sim_db_ptr->create_root ("EINST_Id_assigner")->
		set_value (id_assigner_ptr);
	}
	Id new_id = id_assigner_ptr->assign_next_id();
	entire_value = new_id.get_entire_value ();
    }
    m_evt_inst_ID.set_entire_value (entire_value);
    m_evt_inst_ID.set_class_type (EVENT_INST_TYPE);


    m_SM_Evt_R2022_ptr.relate( 0, this );
    m_Object_Instance_R2031_ptr.relate( 0, this );
    m_Object_Instance_R2032_ptr.relate( 0, this );


    mc_dbms_List<I_SM_Evt_Inst*>* einst_coll_ptr =
	get_class_extent_ptr (mc_dbms_database::of (this));
    t_boolean inserted = FALSE;
    for (t_uint curr_einst_pos = 0;
	((! inserted) && (curr_einst_pos < einst_coll_ptr->cardinality ()));
	curr_einst_pos++)
    {
        I_SM_Evt_Inst* curr_einst_ptr
	    = einst_coll_ptr->retrieve (curr_einst_pos);
	if (curr_einst_ptr->get_expiration_time () > m_expiration_timestamp)
	{
	    einst_coll_ptr->insert_before (this, curr_einst_pos);
	    inserted = TRUE;
	}
    }
    if (! inserted)
    {
	einst_coll_ptr->insert_last (this);
    }


    LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_SM_Evt_Inst::I_SM_Evt_Inst()" ));
}


I_SM_Evt_Inst::~I_SM_Evt_Inst ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Inst::~I_SM_Evt_Inst ()."));


    get_class_extent_ptr (mc_dbms_database::of (this))->remove (this);

    operator delete( this, ""); // Remove from InstanceTracker

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Inst::~I_SM_Evt_Inst ()."));
}

t_boolean
I_SM_Evt_Inst::operator== (const I_SM_Evt_Inst& p_einst) const
{
    if ( m_expiration_timestamp == p_einst.m_expiration_timestamp &&
	     m_recurring_microseconds == p_einst.m_recurring_microseconds &&
	     m_is_creation_event == p_einst.m_is_creation_event &&
	     m_creation_Object_ID == p_einst.m_creation_Object_ID &&
         m_is_polymorphic_delivery == p_einst.m_is_polymorphic_delivery &&
         m_poly_relationship_ID == p_einst.m_poly_relationship_ID &&
         get_SM_Evt_R2022_ptr == get_SM_Evt_R2022_ptr &&
         get_Object_Instance_R2031_ptr == get_Object_Instance_R2031_ptr &&
         get_Object_Instance_R2032_ptr == get_Object_Instance_R2032_ptr 
       )
    {
        // check if supp data values are the same
        mc_dbms_Cursor<I_SM_Evt_Supp_DI_Inst*> cursor1 (m_SM_Evt_Supp_DI_Inst_R2023_coll);

        t_boolean values_match = TRUE;

        I_SM_Evt_Supp_DI_Inst* SM_esdii_ptr1 = cursor1.first ();
        while (SM_esdii_ptr1 && values_match)
        {
            mc_dbms_Cursor<I_SM_Evt_Supp_DI_Inst*> cursor2 (p_einst.m_SM_Evt_Supp_DI_Inst_R2023_coll);
    
            I_SM_Evt_Supp_DI_Inst* SM_esdii_ptr2 = cursor2.first ();
            while (SM_esdii_ptr2 && values_match)
            {
                I_SM_Evt_Supp_DI *supp_di_ptr1 = SM_esdii_ptr1->get_SM_Evt_Supp_DI_R2023_ptr();
                I_SM_Evt_Supp_DI *supp_di_ptr2 = SM_esdii_ptr2->get_SM_Evt_Supp_DI_R2023_ptr();
                if ( supp_di_ptr1 == supp_di_ptr2 )
                {
                    I_var* var1_ptr = SM_esdii_ptr1->get_var_ptr();
                    I_var* var2_ptr = SM_esdii_ptr2->get_var_ptr();
                    if ( ! (*var1_ptr == *var2_ptr) )
                    {
                        values_match = FALSE;
                    }
                    break;
                }

                SM_esdii_ptr2 = cursor2.next();
            }

            SM_esdii_ptr1 = cursor1.next();
        }

        return values_match;
    }

    return FALSE;

}

mc_dbms_List<I_SM_Evt_Inst*>*
I_SM_Evt_Inst::get_class_extent_ptr (mc_dbms_database* p_db_ptr)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Inst::get_class_extent_ptr ()."));


    mc_dbms_List<I_SM_Evt_Inst*>* class_extent_ptr;
    mc_dbms_database_root* root_ptr
	= p_db_ptr->find_root ("I_SM_Evt_Inst_class_extent");

    if (root_ptr)
    {
	class_extent_ptr
	    = (mc_dbms_List<I_SM_Evt_Inst*>*) root_ptr->get_value ();
    }
    else
    {
	class_extent_ptr = &mc_dbms_List<I_SM_Evt_Inst*>::create
	    (p_db_ptr);

	p_db_ptr->create_root ("I_SM_Evt_Inst_class_extent")->
	    set_value (class_extent_ptr);
    }

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted  I_SM_Evt_Inst::get_class_extent_ptr ()."));

    return (class_extent_ptr);
}


void
I_SM_Evt_Inst::relate_R2023
    (I_SM_Evt_Supp_DI_Inst* p_SM_Evt_Supp_DI_Inst_R2023_ptr)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Inst::relate_R2023 ()."));

    m_SM_Evt_Supp_DI_Inst_R2023_coll.insert (p_SM_Evt_Supp_DI_Inst_R2023_ptr);

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Inst::relate_R2023 ()."));
}





void
I_SM_Evt_Inst::relate_R2022 (I_SM_Evt* p_SM_Evt_R2022_ptr)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Inst::relate_R2022 ()."));

    m_SM_Evt_R2022_ptr.relate( p_SM_Evt_R2022_ptr, this );

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Inst::relate_R2022 ()."));
}





void
I_SM_Evt_Inst::relate_R2031 (I_Object_Instance* p_Object_Instance_R2031_ptr)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Inst::relate_R2031 ()."));

    m_Object_Instance_R2031_ptr.relate( p_Object_Instance_R2031_ptr, this );

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Inst::relate_R2031 ()."));
}





void
I_SM_Evt_Inst::relate_R2032 (I_Object_Instance* p_Object_Instance_R2032_ptr)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Inst::relate_R2032 ()."));

    m_Object_Instance_R2032_ptr.relate( p_Object_Instance_R2032_ptr, this );

    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Inst::relate_R2032 ()."));
}





I_SM_Evt_Inst*
I_SM_Evt_Inst::find_SM_Evt_Inst_by_evt_inst_ID
    (mc_dbms_database* p_db_ptr, const Id& p_evt_inst_ID)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Inst::find_SM_Evt_Inst_by_evt_inst_ID ()"));


    mc_dbms_Cursor< I_SM_Evt_Inst * > cursor
	(*I_SM_Evt_Inst::get_class_extent_ptr (p_db_ptr));


    I_SM_Evt_Inst* found_einst_ptr = 0;
    I_SM_Evt_Inst* einst_ptr = cursor.first ();
    while (einst_ptr)
    {
	if (einst_ptr->get_evt_inst_ID () == p_evt_inst_ID)
	{
	    if (! found_einst_ptr)
	    {
		found_einst_ptr = einst_ptr;
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "More than one I_SM_Evt_Inst with same ID exists in GEN/SIM DB."));
	    }
	}
	einst_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Inst::find_SM_Evt_Inst_by_evt_inst_ID ()"));


    return (found_einst_ptr);
}




I_SM_Evt_Supp_DI_Inst*
I_SM_Evt_Inst::find_SM_Evt_Supp_DI_Inst_R2023_by_SM_esdi_ID
    (const Id& p_SM_esdi_ID) const

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_SM_Evt_Inst::find_SM_Evt_Supp_DI_Inst_R2023_by_SM_esdi_ID ()"));


    mc_dbms_Cursor<I_SM_Evt_Supp_DI_Inst*> cursor (m_SM_Evt_Supp_DI_Inst_R2023_coll);


    I_SM_Evt_Supp_DI_Inst* found_SM_esdii_ptr = 0;
    I_SM_Evt_Supp_DI_Inst* SM_esdii_ptr = cursor.first ();
    while (SM_esdii_ptr)
    {
	if (SM_esdii_ptr->get_SM_esdi_ID () == p_SM_esdi_ID)
	{
	    if (! found_SM_esdii_ptr)
	    {
		found_SM_esdii_ptr = SM_esdii_ptr;
	    }
	    else
	    {
		LOG_ERROR ((L_log_string,
		    "More than one Event Supp Data Item Instance with same ID related to same Event Instance exists in OOA DB."));
	    }
	}
	SM_esdii_ptr = cursor.next ();
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_SM_Evt_Inst::find_SM_Evt_Supp_DI_Inst_R2023_by_SM_esdi_ID ()"));


    return (found_SM_esdii_ptr);
}






void
I_SM_Evt_Inst::set_expiration_time (const I_timestamp_var& p_timestamp)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_SM_Evt_Inst::set_expiration_timer ()"));


    m_expiration_timestamp = p_timestamp;


    //  Re-insert the event in the class extent according to the
    //    expiration time.  Once at correct expire time, check for event to
    //    self acceleration.
    //
    mc_dbms_List<I_SM_Evt_Inst*>* einst_coll_ptr =
	get_class_extent_ptr (mc_dbms_database::of (this));
    einst_coll_ptr->remove (this);
    t_boolean inserted = FALSE;
    if ((m_Object_Instance_R2031_ptr) && (m_Object_Instance_R2032_ptr)
	&&
	(m_Object_Instance_R2031_ptr == m_Object_Instance_R2032_ptr)
	&&
	(m_expiration_timestamp <= I_Clock::current_time ()))
    {
	//  Event to self which is NOT a timer.  Place the event in the
	//    queue as to accelerate its processing.
	//
	for (t_uint curr_einst_pos = 0;
	    ((! inserted) && (curr_einst_pos < einst_coll_ptr->cardinality ()));
	    curr_einst_pos++)
	{
	    I_SM_Evt_Inst* curr_einst_ptr
		= einst_coll_ptr->retrieve (curr_einst_pos);
	    if (curr_einst_ptr->get_expiration_time ()
		<= I_Clock::current_time ())
	    {
		if ((m_Object_Instance_R2032_ptr
		    == curr_einst_ptr->m_Object_Instance_R2032_ptr)
		    &&
		    (curr_einst_ptr->m_Object_Instance_R2031_ptr
		    != curr_einst_ptr->m_Object_Instance_R2032_ptr))
		{
		    //  Current event NOT an event to self but IS destine to
		    //    same object instance as event being queued.  Want
		    //    to accelerate the event being queued to BEFORE the
		    //    current event.  Modify the expire time of the event
		    //    being queued to match the current event.
		    //
		    einst_coll_ptr->insert_before (this, curr_einst_pos);
		    m_expiration_timestamp
			= curr_einst_ptr->get_expiration_time ();
		    inserted = TRUE;
		}
	    }
	}
    }
    if (! inserted)
    {
	for (t_uint curr_einst_pos = 0;
	    ((! inserted) && (curr_einst_pos < einst_coll_ptr->cardinality ()));
	    curr_einst_pos++)
	{
	    I_SM_Evt_Inst* curr_einst_ptr
		= einst_coll_ptr->retrieve (curr_einst_pos);
	    if (curr_einst_ptr->get_expiration_time () > m_expiration_timestamp)
	    {
		einst_coll_ptr->insert_before (this, curr_einst_pos);
		inserted = TRUE;
	    }
	}
    }
    if (! inserted)
    {
	einst_coll_ptr->insert_last (this);
    }


    if (m_Object_Instance_R2031_ptr)
    {
	I_Object_Instance* oinst_ptr = m_Object_Instance_R2031_ptr;
	oinst_ptr->get_SM_Evt_Inst_R2031_coll_ptr ()->remove (this);
	t_boolean inserted = FALSE;
	if ((m_Object_Instance_R2031_ptr == m_Object_Instance_R2032_ptr)
	    &&
	    (m_expiration_timestamp <= I_Clock::current_time ()))
	{
	    //  Event to self which is NOT a timer.  Place the event in the
	    //    queue as to accelerate its processing.
	    //
	    for (t_uint curr_einst_pos = 0;
		((! inserted) && (curr_einst_pos < oinst_ptr->
		    get_SM_Evt_Inst_R2031_coll_ptr ()->cardinality ()));
		curr_einst_pos++)
	    {
		I_SM_Evt_Inst* curr_einst_ptr = oinst_ptr->
		    get_SM_Evt_Inst_R2031_coll_ptr ()->
		    retrieve (curr_einst_pos);
		if (curr_einst_ptr->get_expiration_time ()
		    <= I_Clock::current_time ())
		{
		    if ((m_Object_Instance_R2032_ptr
			== curr_einst_ptr->m_Object_Instance_R2032_ptr)
			&&
			(curr_einst_ptr->m_Object_Instance_R2031_ptr
			!= curr_einst_ptr->m_Object_Instance_R2032_ptr))
		    {
			//  Current event NOT an event to self but IS destine to
			//    same object instance as event being queued.  Want
			//    to accelerate the event being queued to BEFORE the
			//    current event.  Modify the expire time of the
			//    event being queued to match the current event.
			//
			oinst_ptr->get_SM_Evt_Inst_R2031_coll_ptr ()->
			    insert_before (this, curr_einst_pos);
			m_expiration_timestamp
			    = curr_einst_ptr->get_expiration_time ();
			inserted = TRUE;
		    }
		}
	    }
	}
	if (! inserted)
	{
	    for (t_uint curr_einst_pos = 0;
		((! inserted) && (curr_einst_pos < oinst_ptr->
		    get_SM_Evt_Inst_R2031_coll_ptr ()->cardinality ()));
		curr_einst_pos++)
	    {
		I_SM_Evt_Inst* curr_einst_ptr = oinst_ptr->
		    get_SM_Evt_Inst_R2031_coll_ptr ()->
		    retrieve (curr_einst_pos);
		if (curr_einst_ptr->get_expiration_time ()
		    > m_expiration_timestamp)
		{
		    oinst_ptr->get_SM_Evt_Inst_R2031_coll_ptr ()->insert_before
			(this, curr_einst_pos);
		    inserted = TRUE;
		}
	    }
	}
	if (! inserted)
	{
	    oinst_ptr->get_SM_Evt_Inst_R2031_coll_ptr ()->insert_last (this);
	}
    }


    if (m_Object_Instance_R2032_ptr)
    {
	I_Object_Instance* oinst_ptr = m_Object_Instance_R2032_ptr;
	oinst_ptr->get_SM_Evt_Inst_R2032_coll_ptr ()->remove (this);
	t_boolean inserted = FALSE;
	if ((m_Object_Instance_R2031_ptr == oinst_ptr)
	    &&
	    (m_expiration_timestamp <= I_Clock::current_time ()))
	{
	    //  Event to self which is NOT a timer.  Place the event in the
	    //    queue as to accelerate its processing.
	    //
	    for (t_uint curr_einst_pos = 0;
		((! inserted) && (curr_einst_pos < oinst_ptr->
		    get_SM_Evt_Inst_R2032_coll_ptr ()->cardinality ()));
		curr_einst_pos++)
	    {
		I_SM_Evt_Inst* curr_einst_ptr = oinst_ptr->
		    get_SM_Evt_Inst_R2032_coll_ptr ()->
		    retrieve (curr_einst_pos);
		if (curr_einst_ptr->get_expiration_time ()
		    <= I_Clock::current_time ())
		{
		    if ((oinst_ptr
			== curr_einst_ptr->m_Object_Instance_R2032_ptr)
			&&
			(curr_einst_ptr->m_Object_Instance_R2031_ptr
			!= curr_einst_ptr->m_Object_Instance_R2032_ptr))
		    {
			//  Current event NOT an event to self but IS destine to
			//    same object instance as event being queued.  Want
			//    to accelerate the event being queued to BEFORE the
			//    current event.  Modify the expire time of the
			//    event being queued to match the current event.
			//
			oinst_ptr->get_SM_Evt_Inst_R2032_coll_ptr ()->
			    insert_before (this, curr_einst_pos);
			m_expiration_timestamp
			    = curr_einst_ptr->get_expiration_time ();
			inserted = TRUE;
		    }
		}
	    }
	}
	if (! inserted)
	{
	    for (t_uint curr_einst_pos = 0;
		((! inserted) && (curr_einst_pos < oinst_ptr->
		    get_SM_Evt_Inst_R2032_coll_ptr ()->cardinality ()));
		curr_einst_pos++)
	    {
		I_SM_Evt_Inst* curr_einst_ptr = oinst_ptr->
		    get_SM_Evt_Inst_R2032_coll_ptr ()->
		    retrieve (curr_einst_pos);
		if (curr_einst_ptr->get_expiration_time ()
		    > m_expiration_timestamp)
		{
		    oinst_ptr->get_SM_Evt_Inst_R2032_coll_ptr ()->insert_before
			(this, curr_einst_pos);
		    inserted = TRUE;
		}
	    }
	}
	if (! inserted)
	{
	    oinst_ptr->get_SM_Evt_Inst_R2032_coll_ptr ()->insert_last (this);
	}
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End  I_SM_Evt_Inst::set_expiration_timer ()"));
}





void
I_SM_Evt_Inst::set_expiration_time_to_infinity ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_SM_Evt_Inst::set_expiration_timer_to_infinity ()"));


    m_expiration_timestamp.set_microsecond (999999);
    m_expiration_timestamp.set_second (0xffffffff);


    mc_dbms_List<I_SM_Evt_Inst*>* einst_coll_ptr =
	get_class_extent_ptr (mc_dbms_database::of (this));
    if (einst_coll_ptr)
    {
	einst_coll_ptr->remove (this);
	einst_coll_ptr->insert_last (this);
    }


    if (m_Object_Instance_R2031_ptr)
    {
	I_Object_Instance* oinst_ptr = m_Object_Instance_R2031_ptr;
	oinst_ptr->get_SM_Evt_Inst_R2031_coll_ptr ()->remove (this);
	oinst_ptr->get_SM_Evt_Inst_R2031_coll_ptr ()->insert_last (this);
    }


    if (m_Object_Instance_R2032_ptr)
    {
	I_Object_Instance* oinst_ptr = m_Object_Instance_R2032_ptr;
	oinst_ptr->get_SM_Evt_Inst_R2032_coll_ptr ()->remove (this);
	oinst_ptr->get_SM_Evt_Inst_R2032_coll_ptr ()->insert_last (this);
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End  I_SM_Evt_Inst::set_expiration_timer_to_infinity ()"));
}





t_boolean
I_SM_Evt_Inst::is_expiration_time_infinity ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_SM_Evt_Inst::is_expiration_time_infinity ()."));


    t_boolean rv = FALSE;
    if ((m_expiration_timestamp.get_microsecond () == 999999) &&
	(m_expiration_timestamp.get_second () == 0xffffffff))
    {
	rv = TRUE;
    }


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End  I_SM_Evt_Inst::is_expiration_time_infinity (rv=%d).", rv));
    return rv;
}





I_SM_Evt_Inst*
I_SM_Evt_Inst::copy__I_SM_Evt_Inst (I_SM_Evt_Inst* p_orig_einst_ptr)

{
  LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	 "Begin  I_SM_Evt_Inst::copy__I_SM_Evt_Inst (p_orig_einst_ptr=0x%08x).",
    p_orig_einst_ptr));
  
  
  I_SM_Evt* sim_evt_ptr = p_orig_einst_ptr->get_SM_Evt_R2022_ptr ();
  
  
  if (! sim_evt_ptr)
    {
      LOG_ERROR ((L_log_string,
        "End #1:  I_SM_Evt_Inst::copy__I_SM_Evt_Inst (0):  sim_evt_ptr == 0."));
      return 0;
    }
  
  
  I_SM_Evt_Inst* new_einst_ptr = I_SM_Evt_Inst::create (GS_gen_sim_db_ptr);
  if (! new_einst_ptr)
    {
      LOG_ERROR ((L_log_string,
	     "End #3:  I_SM_Evt_Inst::copy__I_SM_Evt_Inst (0):  new_einst_ptr == 0."));
      return 0;
    }
  sim_evt_ptr->relate_R2022 (new_einst_ptr);
  
  
  //  Loop through all supplemental data items and create the supplemental
  //    data item instances and set up the initial values.
  //
  I_SM_Evt_Supp_DI_Inst* orig_esdii_ptr;
  FOR_ALL_ELEMENTS_SAFE
    (orig_esdii_ptr,
     I_SM_Evt_Supp_DI_Inst,
     p_orig_einst_ptr->get_SM_Evt_Supp_DI_Inst_R2023_coll_ptr (),
     orig_esdii_cursor)
      {
        I_SM_Evt_Supp_DI_Inst* new_esdii_ptr = I_SM_Evt_Supp_DI_Inst::create
          (GS_gen_sim_db_ptr, orig_esdii_ptr->get_core_data_type (),
           orig_esdii_ptr->get_user_data_type ());
        if (! new_esdii_ptr)
          {
            delete new_einst_ptr;
            LOG_ERROR ((L_log_string,
              "End #4:  I_SM_Evt_Inst::copy__I_SM_Evt_Inst ():  Unable to create I_SM_Evt_Supp_DI_Inst instance."));
            return 0;
          }
        
        new_esdii_ptr->relate_R2023
          (orig_esdii_ptr->get_SM_Evt_Supp_DI_R2023_ptr ());
        new_esdii_ptr->set_SM_esdi_ID (orig_esdii_ptr->
                                       get_SM_Evt_Supp_DI_R2023_ptr ()->get_SM_esdi_ID ());
        new_esdii_ptr->relate_R2023 (new_einst_ptr);
        new_esdii_ptr->get_var_ptr ()->
          reassign (orig_esdii_ptr->get_var_ptr ());
      }
  
  I_Object_Instance* orig_oinst_ptr = 
	  p_orig_einst_ptr->get_Object_Instance_R2031_ptr ();
  if ( orig_oinst_ptr )
  {
	orig_oinst_ptr->relate_R2031(new_einst_ptr);
  }

  new_einst_ptr->is_creation_event() = p_orig_einst_ptr->is_creation_event();
  if ( ! p_orig_einst_ptr->is_creation_event() )
  {
    p_orig_einst_ptr->get_Object_Instance_R2032_ptr ()->relate_R2032
      (new_einst_ptr);
  }
  else
  {
    new_einst_ptr->set_creation_Object_ID
      (p_orig_einst_ptr->get_creation_Object_ID ());
  }
  
  new_einst_ptr->set_expiration_time
    (p_orig_einst_ptr->get_expiration_time ());
  
  new_einst_ptr->set_polymorphic_delivery
    (p_orig_einst_ptr->is_polymorphic_delivery ());
  
  new_einst_ptr->set_polymorphic_relationship
    (p_orig_einst_ptr->get_polymorphic_relationship ());
  
  LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
    "End #5:  I_SM_Evt_Inst::copy__I_SM_Evt_Inst (return new_einst_ptr=0x%08x).",
    new_einst_ptr));
  return new_einst_ptr;
}





t_boolean
I_SM_Evt_Inst::delete__I_SM_Evt_Inst (I_SM_Evt_Inst* p_einst_ptr,
    t_boolean p_delete__I_SM_Evt__flag)

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  I_SM_Evt_Inst::delete__I_SM_Evt_Inst (p_einst_ptr=0x%08x, p_delete__I_SM_Evt__flag=%d).",
	p_einst_ptr, p_delete__I_SM_Evt__flag));


    if (! p_einst_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #1:  I_SM_Evt_Inst::delete__I_SM_Evt_Inst (return FALSE):  p_einst_ptr == 0."));
	return FALSE;
    }


    //  Delete the supplemental data item instance instances.
    //
    I_SM_Evt_Supp_DI_Inst* esdii_ptr;
    FOR_ALL_ELEMENTS_SAFE
        (esdii_ptr,
        I_SM_Evt_Supp_DI_Inst,
	p_einst_ptr->get_SM_Evt_Supp_DI_Inst_R2023_coll_ptr (),
        esdii_cursor)
    {
	delete esdii_ptr;
    }


    if (p_delete__I_SM_Evt__flag)
    {
	//  Delete the I_SM_Evt.
	//
	I_SM_Evt* sim_evt_ptr = p_einst_ptr->get_SM_Evt_R2022_ptr ();
	delete p_einst_ptr;
	if (! sim_evt_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"End #2:  I_SM_Evt_Inst::delete__I_SM_Evt_Inst (return FALSE):  sim_evt_ptr == 0."));
	    return FALSE;
	}

	mc_dbms_List <I_SM_Evt_Inst*>* einst_coll_ptr
	    = sim_evt_ptr->get_SM_Evt_Inst_R2022_coll_ptr ();
	if (! einst_coll_ptr)
	{
	    LOG_ERROR ((L_log_string,
		"End #3:  I_SM_Evt_Inst::delete__I_SM_Evt_Inst (return FALSE):  einst_coll_ptr == 0."));
	    return FALSE;
	}

	if (einst_coll_ptr->cardinality () < 1)
	{
	    //  The last instance to use this I_SM_Evt has been deleted -
	    //    delete this instance of I_SM_Evt and all of its related
	    //    I_SM_Evt_Supp_DI's.
	    //
	    I_SM_Evt_Supp_DI* sim_esdi_ptr;
	    FOR_ALL_ELEMENTS_SAFE
		(sim_esdi_ptr,
		I_SM_Evt_Supp_DI,
		sim_evt_ptr->get_SM_Evt_Supp_DI_R2021_coll_ptr (),
		sim_esdi_cursor)
	    {
		I_SM_Evt_Supp_DI_Inst* esdii_ptr;
		FOR_ALL_ELEMENTS_SAFE
		    (esdii_ptr,
		    I_SM_Evt_Supp_DI_Inst,
		    sim_esdi_ptr->get_SM_Evt_Supp_DI_Inst_R2023_coll_ptr (),
		    esdii_cursor2)
		{
		    LOG_ERROR ((L_log_string,
			"I_SM_Evt_Inst::delete__I_SM_Evt_Inst ():  I_SM_Evt_Supp_DI has related I_SM_Evt_Supp_DI_Inst(s) when I_SM_Evt has NO related I_SM_Evt_Inst(s) - cleaning up left over I_SM_Evt_Supp_DI_Inst(s) & continuing execution."));
		    delete esdii_ptr;
		}
	    }
	    delete sim_evt_ptr;
	}
    }
    else
    {
	delete p_einst_ptr;
    }


    return TRUE;
}


Description
I_SM_Evt_Inst::format()
{
    //  Go to the Originating Object Instance and print the primary ID
	//    values.
	//
	Description einst_display_str;
    
	if (I_Clock::current_time () < this->get_expiration_time ())
	{
	    einst_display_str += "Timer Expires: ";
	    einst_display_str += this->get_expiration_time ().
		    get_var_ptr ()->get_value_str ().char_ptr ();
	    einst_display_str += "    ";
	}
    I_SM_Evt* sm_evt =this->get_SM_Evt_R2022_ptr ();
	if (sm_evt)
	{
        einst_display_str += sm_evt->get_label ();
        D_sm_event* e = GS_find::find_sm_event_by_id (sm_evt->get_SM_evt_ID ());
        if(e){
            einst_display_str += ":'";
            einst_display_str += e->get_event_meaning ();
            einst_display_str += "'";
        }    
	}
	einst_display_str += ":";
	char buffer [32];
	sprintf (buffer, "%06x",
	this->get_evt_inst_ID ().get_entire_value ());
	einst_display_str += buffer;
	einst_display_str += "    ";
	
	I_Object_Instance* orig_oinst_ptr =	get_Object_Instance_R2031_ptr ();
    I_Object_Instance* dest_oinst_ptr = get_Object_Instance_R2032_ptr ();
    
    einst_display_str += "From:";
	if (orig_oinst_ptr) orig_oinst_ptr->toString(einst_display_str);
	else                einst_display_str += "User Created";
	
    einst_display_str += "    To:";
	if (dest_oinst_ptr) dest_oinst_ptr->toString(einst_display_str);
	else                einst_display_str += "Unknown";
        
	if (is_creation_event()) einst_display_str += " (Creation)";
	
	return einst_display_str;
}




mc_dbms_relationship_m_1_body(I_SM_Evt_Inst,m_SM_Evt_Supp_DI_Inst_R2023_coll,I_SM_Evt_Supp_DI_Inst,m_SM_Evt_Inst_R2023_ptr);

mc_dbms_relationship_1_m_body(I_SM_Evt_Inst,m_SM_Evt_R2022_ptr,I_SM_Evt,m_SM_Evt_Inst_R2022_coll);

mc_dbms_relationship_1_m_body(I_SM_Evt_Inst,m_Object_Instance_R2031_ptr,I_Object_Instance,m_SM_Evt_Inst_R2031_coll);

mc_dbms_relationship_1_m_body(I_SM_Evt_Inst,m_Object_Instance_R2032_ptr,I_Object_Instance,m_SM_Evt_Inst_R2032_coll);
