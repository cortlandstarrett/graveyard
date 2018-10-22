/*========================================================================
 *
 * File:      $RCSfile: d_levt.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:08 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_local_event_HH
#define D_local_event_HH




#include <d_sevt.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros



//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_spt_pm;
class D_creation_transition;

class D_local_event: public D_sem_event
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_local_event (Domain*, D_sm_spt_pm*, t_boolean p_create_supp_data = TRUE );
    D_local_event (Domain*, D_sm_spt_pm*, const Id & p_id,
				t_boolean p_create_supp_data = TRUE);

    virtual ~D_local_event ();



    //  IMPLEMENTOR functions
    //

    void delete_local_event ( t_boolean p_check_comm_path = FALSE );


    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    D_creation_transition* get_creation_transition_ptr () const
        { return m_creation_transition_ptr; }
    void set_creation_transition_ptr (D_creation_transition* p_creation_transition_ptr)
        { m_creation_transition_ptr = p_creation_transition_ptr; }


    virtual D_local_event* get_local_event_ptr ()
		{ return this; }

    virtual t_boolean is_local_event()
		{ return TRUE; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }


    DELETE_DOWN_DECL_SUBTYPE()



private:

    mc_dbms_relationship_1_1(D_local_event,m_creation_transition_ptr,D_creation_transition,m_local_event_ptr,D_creation_transition*) m_creation_transition_ptr;


};

#endif
