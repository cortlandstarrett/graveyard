/*========================================================================
 *
 * File:      $RCSfile: d_moorhm.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:05 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_moore_action_home_HH
#define D_moore_action_home_HH




#include <d_acthom.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros



//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_state;
class D_moore_sm;



class D_moore_action_home : public D_action_home
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();

    static D_moore_action_home* create_moore_action_home
        (D_sm_state*, D_moore_sm*);
    D_moore_action_home (Domain*, D_sm_state*, D_moore_sm*);

    virtual ~D_moore_action_home ();



    //  IMPLEMENTOR functions
    //

    void delete_moore_action_home ();



    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    D_sm_state* get_sm_state_ptr () const
        { return m_sm_state_ptr; }

    D_moore_sm* get_moore_sm_ptr () const
        { return m_moore_sm_ptr; }

    virtual D_moore_action_home* get_moore_action_home_ptr ()
        { return this; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    Domain* get_domain_ptr ();

    DELETE_DOWN_DECL_SUBTYPE()


private:

    mc_dbms_relationship_1_m(D_moore_action_home,m_sm_state_ptr,D_sm_state,m_moore_action_home_coll,D_sm_state*) m_sm_state_ptr;

    mc_dbms_relationship_1_m(D_moore_action_home,m_moore_sm_ptr,D_moore_sm,m_moore_action_home_coll,D_moore_sm*) m_moore_sm_ptr;
};



#endif
