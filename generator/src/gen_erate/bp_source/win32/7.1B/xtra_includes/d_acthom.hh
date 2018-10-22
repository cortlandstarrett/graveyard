/*========================================================================
 *
 * File:      $RCSfile: d_acthom.hh,v $
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

#ifndef D_action_home_HH
#define D_action_home_HH




#include <d_domain.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros


//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_action;
class D_moore_action_home;
class D_mealy_action_home;



class D_action_home
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_action_home (Domain*);

    virtual ~D_action_home ();



    //  IMPLEMENTOR functions
    //

    void delete_action_home ();



    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    D_action* get_action_ptr () const
        { return m_action_ptr; }
    void set_action_ptr (D_action* p_action_ptr)
        { m_action_ptr = p_action_ptr; }

    virtual D_moore_action_home* get_moore_action_home_ptr ()
        { return 0; }

    virtual D_mealy_action_home* get_mealy_action_home_ptr ()
        { return 0; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }


    Domain* get_domain_ptr ();


    //  CUSTOM functions
    //

    DELETE_DOWN_DECL_SUPERTYPE()


private:

    mc_dbms_relationship_1_1(D_action_home,m_action_ptr,D_action,m_action_home_ptr,D_action*) m_action_ptr;
};



#endif
