/*========================================================================
 *
 * File:      $RCSfile: d_nevttn.hh,v $
 * Version:   $Revision: 1.10 $
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

#ifndef D_no_event_transition_HH
#define D_no_event_transition_HH




#include <d_tns.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros


//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_state;
class D_sm_event;



class D_no_event_transition : public D_transition
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_no_event_transition (Domain*, D_sm_spt_pm*);
    D_no_event_transition (Domain*, D_sm_spt_pm*, Id);

    virtual ~D_no_event_transition ();



    //  IMPLEMENTOR functions
    //

    void delete_no_event_transition ();

	virtual void copy_transition();


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

    virtual D_no_event_transition* get_no_event_transition_ptr ()
        { return this; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }


    Domain* get_domain_ptr ();

    D_new_state_transition* migrate_to_new_state_transition (D_sm_event*);

    DELETE_DOWN_DECL_SUBTYPE()



private:

    mc_dbms_relationship_1_m(D_no_event_transition,m_sm_state_ptr,D_sm_state,m_no_event_transition_coll,D_sm_state*) m_sm_state_ptr;
};



#endif

