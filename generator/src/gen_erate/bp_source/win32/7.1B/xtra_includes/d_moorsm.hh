/*========================================================================
 *
 * File:      $RCSfile: d_moorsm.hh,v $
 * Version:   $Revision: 1.9 $
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

#ifndef D_moore_sm_HH
#define D_moore_sm_HH





#include <d_sm.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros



//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_state;
class D_moore_action_home;



class D_moore_sm : public D_sm
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_moore_sm (Domain*, D_sm_spt_pm*);

    virtual ~D_moore_sm ();



    //  IMPLEMENTOR functions
    //

    void delete_moore_sm ();

    t_uint get_number_of_moore_action_homes ()
        { return (t_uint) get_moore_action_home_coll_ptr ()->cardinality (); }



    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    mc_dbms_List<D_moore_action_home*>*
        get_moore_action_home_coll_ptr ()
        { return &(m_moore_action_home_coll.getvalue ()); }

    virtual D_moore_sm* get_moore_sm_ptr ()
        { return this; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    Domain* get_domain_ptr ();

    DELETE_DOWN_DECL_SUBTYPE()


private:

    mc_dbms_relationship_m_1(D_moore_sm,m_moore_action_home_coll,D_moore_action_home,m_moore_sm_ptr,mc_dbms_List<D_moore_action_home*>) m_moore_action_home_coll;
};



#endif
