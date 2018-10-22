/*========================================================================
 *
 * File:      $RCSfile: d_suppdi.hh,v $
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

#ifndef D_supplemental_data_item_HH
#define D_supplemental_data_item_HH




#include <u_deldwn.hh>     // For DELETE_DOWN macros


class D_sm_event_data_item;
class D_supplemental_data;


//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//


class D_supplemental_data_item
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();

    static D_supplemental_data_item * create
			(D_sm_event_data_item *, D_supplemental_data *);

    virtual ~D_supplemental_data_item ();



    //  IMPLEMENTOR functions
    //

    void delete_supplemental_data_item ();


    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //
	D_sm_event_data_item * get_sm_event_data_item_ptr ()
		{ return m_sm_event_data_item_ptr; }
 
	D_supplemental_data * get_supplemental_data_ptr ()
		{ return m_supplemental_data_ptr; }
 
    t_boolean was_exported()
        { return m_exported; }

    void set_exported(t_boolean p_exp)
        { m_exported = p_exp; }

    DELETE_DOWN_DECL_SUBTYPE()


private:

    t_boolean m_exported;

	mc_dbms_relationship_1_m(D_supplemental_data_item,m_sm_event_data_item_ptr,D_sm_event_data_item,m_supplemental_data_item_coll,D_sm_event_data_item*) m_sm_event_data_item_ptr;
 
	mc_dbms_relationship_1_m(D_supplemental_data_item,m_supplemental_data_ptr,D_supplemental_data,m_supplemental_data_item_coll,D_supplemental_data*) m_supplemental_data_ptr;
 

	// Helping functions follow
 
	D_supplemental_data_item (D_sm_event_data_item *, D_supplemental_data *);

};


#endif
