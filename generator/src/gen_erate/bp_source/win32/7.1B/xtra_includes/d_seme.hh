/*========================================================================
 *
 * File:      $RCSfile: d_seme.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:11 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_state_event_matrix_entry_HH
#define D_state_event_matrix_entry_HH




#include <u_typdef.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include <d_domain.hh>

//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_state;
class D_sem_event;
class D_new_state_transition;
class D_event_ignored;
class D_cant_happen;



class D_state_event_matrix_entry
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();

    static D_state_event_matrix_entry* create_state_event_matrix_entry
        (D_sm_state*, D_sem_event*);
    D_state_event_matrix_entry (Domain*, D_sm_state*, D_sem_event*);

    virtual ~D_state_event_matrix_entry ();



    //  IMPLEMENTOR functions
    //

    void delete_state_event_matrix_entry (t_boolean p_migrate_transitions);



    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    D_sm_state* get_sm_state_ptr () const
        { return m_sm_state_ptr; }
    void set_sm_state_ptr (D_sm_state* p_sm_state_ptr)
        { m_sm_state_ptr.relate( p_sm_state_ptr, this ); }

    D_sem_event* get_sm_event_ptr () const
        { return m_sem_event_ptr; }
    void set_sm_event_ptr (D_sem_event* p_sem_event_ptr)
        { m_sem_event_ptr.relate( p_sem_event_ptr, this ); }

    virtual D_new_state_transition* get_new_state_transition_ptr ()
        { return 0; }

    virtual D_event_ignored* get_event_ignored_ptr ()
        { return 0; }

    virtual D_cant_happen* get_cant_happen_ptr ()
        { return 0; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    Domain* get_domain_ptr ();

    DELETE_DOWN_DECL_SUPERTYPE()


private:

    mc_dbms_relationship_1_m(D_state_event_matrix_entry,m_sm_state_ptr,D_sm_state,m_state_event_matrix_entry_coll,D_sm_state*) m_sm_state_ptr;

    mc_dbms_relationship_1_m(D_state_event_matrix_entry,m_sem_event_ptr,D_sem_event,m_state_event_matrix_entry_coll,D_sem_event*) m_sem_event_ptr;
};



#endif
