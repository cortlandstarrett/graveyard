/*========================================================================
 *
 * File:      $RCSfile: d_nlevt.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:14 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_non_local_event_HH
#define D_non_local_event_HH




#include <d_sevt.hh>

#include <u_deldwn.hh>     // For DELETE_DOWN macros



//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_spt_pm;
class D_polymorphic_event;
class Relationship;

class D_non_local_event: public D_sem_event
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_non_local_event (Domain*, D_sm_spt_pm*, t_boolean p_create_supp_data = TRUE );
    D_non_local_event (Domain*, D_sm_spt_pm*, const Id & p_id,
				t_boolean p_create_supp_data = TRUE);

    virtual ~D_non_local_event ();



    //  IMPLEMENTOR functions
    //

    void delete_non_local_event ( t_boolean p_check_comm_path = FALSE );



    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //
    virtual Description get_derived_event_label ();
    virtual Description get_event_meaning ();
	virtual Description get_supplemental_data_string ();

	Description get_local_meaning () const
		{ return m_local_meaning; }
	void set_local_meaning( const Description& p_local_meaning )
		{ m_local_meaning = p_local_meaning; }

    D_polymorphic_event* get_aliased_polymorphic_event_ptr ();
    void set_aliased_polymorphic_event_ptr (D_polymorphic_event* p_polymorphic_event_ptr);

    Relationship* get_relationship_ptr ();

    virtual D_non_local_event* get_non_local_event_ptr ()
		{ return this; }

    virtual t_boolean is_non_local_event()
		{ return TRUE; }

    t_boolean has_polymorphic_event_id();

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    void set_poly_sm_evt_id(const Id& p_id)
	  { m_poly_sm_evt_id = p_id; }
    void set_poly_sm_id(const Id& p_id)
	  { m_poly_sm_id = p_id; }
    // i2822.2.2 deleted

    Id get_poly_sm_evt_id()
	  { return m_poly_sm_evt_id; }
    Id get_poly_sm_id()
	  { return m_poly_sm_id; }
    // i2822.2.2 deleted

    DELETE_DOWN_DECL_SUBTYPE()



private:

    Id m_poly_sm_evt_id;
    Id m_poly_sm_id;
    // i2822.2.2 deleted
	Description m_local_meaning;

};

#endif
