/*========================================================================
 *
 * File:      $RCSfile: d_evtign.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:06 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_event_ignored_HH
#define D_event_ignored_HH




#include <d_seme.hh>

#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros



class D_event_ignored : public D_state_event_matrix_entry
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_event_ignored (Domain*, D_sm_state*, D_sem_event*);

    virtual ~D_event_ignored ();



    //  IMPLEMENTOR functions
    //

    void delete_event_ignored ();



    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    virtual D_event_ignored* get_event_ignored_ptr ()
        { return this; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }
    
    Description &description() { return m_description; }
    
    Domain* get_domain_ptr ();
    
    D_cant_happen * migrate_to_event_cant_happen ();
    
    DELETE_DOWN_DECL_SUBTYPE()


private:

	Description m_description;

};



#endif
