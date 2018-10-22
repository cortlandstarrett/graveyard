/*========================================================================
 *
 * File:      $RCSfile: d_mealsm.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:12 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_mealy_sm_HH
#define D_mealy_sm_HH




#include <d_sm.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros


//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_transition;
class D_mealy_action_home;



class D_mealy_sm : public D_sm
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_mealy_sm (Domain*, D_sm_spt_pm*);

    virtual ~D_mealy_sm ();



    //  IMPLEMENTOR functions
    //

    void delete_mealy_sm ();

    t_uint get_number_of_mealy_action_homes ()
        { if ( get_mealy_action_home_coll_ptr () != 0 ) 
		    return (t_uint) get_mealy_action_home_coll_ptr ()->cardinality ();
		  else
		    return 0;
	    }



    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    mc_dbms_List<D_mealy_action_home*>*
        get_mealy_action_home_coll_ptr ()
        { return &(m_mealy_action_home_coll.getvalue ()); }

    virtual D_mealy_sm* get_mealy_sm_ptr ()
        { return this; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }


    Domain* get_domain_ptr ();

    DELETE_DOWN_DECL_SUBTYPE()



private:

    mc_dbms_relationship_m_1(D_mealy_sm,m_mealy_action_home_coll,D_mealy_action_home,m_mealy_sm_ptr,mc_dbms_List<D_mealy_action_home*>) m_mealy_action_home_coll;
};



#endif
