/*========================================================================
 *
 * File:      $RCSfile: d_sevt.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:13 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_sem_event_HH
#define D_sem_event_HH




#include <d_smevt.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros



//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_spt_pm;
class D_state_event_matrix_entry;
class D_local_event;
class D_non_local_event;

class D_sem_event: public D_sm_event
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_sem_event (Domain*, D_sm_spt_pm*, t_boolean p_create_supp_data = TRUE );
    D_sem_event (Domain*, D_sm_spt_pm*, const Id & p_id,
				t_boolean p_create_supp_data = TRUE);

    virtual ~D_sem_event ();



    //  IMPLEMENTOR functions
    //

    void delete_sem_event ( t_boolean p_check_comm_path = FALSE );

    t_uint get_number_of_state_event_matrix_entrys ()
        { return (t_uint) get_state_event_matrix_entry_coll_ptr ()->cardinality (); }


    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    virtual D_sem_event* get_sem_event_ptr ()
		{ return this; }

    virtual D_local_event* get_local_event_ptr ()
		{ return 0; }
    virtual D_non_local_event* get_non_local_event_ptr ()
		{ return 0; }

    virtual t_boolean is_sem_event()
		{ return TRUE; }

    mc_dbms_Set<D_state_event_matrix_entry*>*
        get_state_event_matrix_entry_coll_ptr ()
        { return &(m_state_event_matrix_entry_coll.getvalue ()); }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }


    void create_state_event_matrix_entrys_for_constructor ();

    DELETE_DOWN_DECL_SUPERTYPE()



private:


    mc_dbms_relationship_m_1(D_sem_event,m_state_event_matrix_entry_coll,D_state_event_matrix_entry,m_sem_event_ptr,mc_dbms_Set<D_state_event_matrix_entry*>) m_state_event_matrix_entry_coll;

};

#endif
