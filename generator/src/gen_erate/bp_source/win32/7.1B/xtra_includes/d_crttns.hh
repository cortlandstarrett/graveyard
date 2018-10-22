/*========================================================================
 *
 * File:      $RCSfile: d_crttns.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:09 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_creation_transition_HH
#define D_creation_transition_HH




#include <d_tns.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros


//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_local_event;



class D_creation_transition : public D_transition
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_creation_transition (Domain*, D_sm_spt_pm*);
    D_creation_transition (Domain*, D_sm_spt_pm*, Id);

    virtual ~D_creation_transition ();



    //  IMPLEMENTOR functions
    //

    void delete_creation_transition ();

	virtual void copy_transition();


    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    D_local_event* get_sm_event_ptr () const
        { return m_local_event_ptr; }
    void set_sm_event_ptr (D_local_event* p_local_event_ptr);

    virtual D_creation_transition* get_creation_transition_ptr ()
        { return this; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }


    Domain* get_domain_ptr ();

    DELETE_DOWN_DECL_SUBTYPE()


private:

    mc_dbms_relationship_1_1(D_creation_transition,m_local_event_ptr,D_local_event,m_creation_transition_ptr,D_local_event*) m_local_event_ptr;
};



#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
