/*========================================================================
 *
 * File:      $RCSfile: d_mealhm.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:10 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_mealy_action_home_HH
#define D_mealy_action_home_HH




#include <d_acthom.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros



//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_transition;
class D_mealy_sm;



class D_mealy_action_home : public D_action_home
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();

    static D_mealy_action_home* create_mealy_action_home
        (D_transition*, D_mealy_sm*);
    D_mealy_action_home (Domain*, D_transition*, D_mealy_sm*);

    virtual ~D_mealy_action_home ();



    //  IMPLEMENTOR functions
    //

    void delete_mealy_action_home ();



    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    D_transition* get_transition_ptr () const
        { return m_transition_ptr; }
    void set_transition_ptr (D_transition* p_transition_ptr)
	{ m_transition_ptr.relate( p_transition_ptr, this ); }

    D_mealy_sm* get_mealy_sm_ptr () const
        { return m_mealy_sm_ptr; }

    virtual D_mealy_action_home* get_mealy_action_home_ptr ()
        { return this; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    Domain* get_domain_ptr ();

    DELETE_DOWN_DECL_SUBTYPE()


private:

    mc_dbms_relationship_1_m(D_mealy_action_home,m_transition_ptr,D_transition,m_mealy_action_home_coll,D_transition*) m_transition_ptr;

    mc_dbms_relationship_1_m(D_mealy_action_home,m_mealy_sm_ptr,D_mealy_sm,m_mealy_action_home_coll,D_mealy_sm*) m_mealy_sm_ptr;
};



#endif
