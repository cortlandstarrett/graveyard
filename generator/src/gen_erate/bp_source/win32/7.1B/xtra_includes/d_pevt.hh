/*========================================================================
 *
 * File:      $RCSfile: d_pevt.hh,v $
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

#ifndef D_polymorphic_event_HH
#define D_polymorphic_event_HH




#include <d_smevt.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros



//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//

class D_non_local_event;

class D_polymorphic_event: public D_sm_event
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_polymorphic_event (Domain*, D_sm_spt_pm*, t_boolean p_create_supp_data = TRUE );
    D_polymorphic_event (Domain*, D_sm_spt_pm*, const Id & p_id,
				t_boolean p_create_supp_data = TRUE);

    virtual ~D_polymorphic_event ();



    //  IMPLEMENTOR functions
    //

    void delete_polymorphic_event ( t_boolean p_check_comm_path = FALSE );

    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    virtual Description get_derived_event_label ();

    void get_subtype_list (mc_dbms_List<D_sm_spt_pm*>& sm_references);

    virtual D_polymorphic_event* get_polymorphic_event_ptr ()
        { return this; }

    virtual t_boolean is_polymorphic_event()
		{ return TRUE; }

    void get_non_local_event_coll ( mc_dbms_List<D_non_local_event*>& );

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    DELETE_DOWN_DECL_SUBTYPE()



private:

};

#endif
