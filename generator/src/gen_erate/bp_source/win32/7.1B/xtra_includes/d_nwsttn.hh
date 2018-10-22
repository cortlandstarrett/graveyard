/*========================================================================
 *
 * File:      $RCSfile: d_nwsttn.hh,v $
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

#ifndef D_new_state_transition_HH
#define D_new_state_transition_HH




#include <d_seme.hh>
#include <d_tns.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros



class D_new_state_transition : public D_state_event_matrix_entry, public D_transition
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_new_state_transition
	(Domain*, D_sm_state*, D_sem_event*, D_sm_spt_pm*);
    D_new_state_transition
	(Domain*, D_sm_state*, D_sem_event*, D_sm_spt_pm*, Id);

    virtual ~D_new_state_transition ();



    //  IMPLEMENTOR functions
    //

    void delete_new_state_transition ();

	virtual void copy_transition();


    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    virtual D_new_state_transition* get_new_state_transition_ptr ()
        { return this; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    Domain* get_domain_ptr ();

    //  CUSTOM functions
    //

    D_no_event_transition* migrate_to_no_event_transition ();

    DELETE_DOWN_DECL_SUBTYPE()



private:

};



#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
