/*========================================================================
 *
 * File:      $RCSfile: d_smevt.hh,v $
 * Version:   $Revision: 1.11 $
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

#ifndef D_sm_event_HH
#define D_sm_event_HH




#include <d_domain.hh>
#include <d_sm_pm.hh>

#include <u_id.hh>
#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros



//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_spt_pm;
class D_sm_state;
class D_sm_event_data_item;
class D_polymorphic_event;
class D_sem_event;

class D_sm_event
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_sm_event (Domain*, D_sm_spt_pm*, t_boolean p_create_supp_data = TRUE );
    D_sm_event (Domain*, D_sm_spt_pm*, const Id & p_id,
				t_boolean p_create_supp_data = TRUE);

    virtual ~D_sm_event ();



    //  IMPLEMENTOR functions
    //

    void delete_sm_event ( t_boolean p_check_comm_path = FALSE );

	static t_boolean compare_event_signatures( const D_sm_event*, const D_sm_event* );

    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    virtual D_polymorphic_event* get_polymorphic_event_ptr ()
		{ return 0; }

    virtual D_sem_event* get_sem_event_ptr ()
		{ return 0; }

    virtual t_boolean is_sem_event()
		{ return FALSE; }

    virtual t_boolean is_polymorphic_event()
		{ return FALSE; }

    virtual t_boolean is_local_event()
		{ return FALSE; }

    virtual t_boolean is_non_local_event()
		{ return FALSE; }

    const Id & get_id () const
	{ return m_id; }

    Description get_event_label () const
        { return m_event_label; }
    void set_event_label (Description p_event_label)
        { m_event_label = p_event_label; }

    virtual Description get_derived_event_label ();
	virtual Description get_supplemental_data_string ();

    virtual Description get_event_meaning ();
    void set_event_meaning (Description p_event_meaning)
        { m_event_meaning = p_event_meaning; }

    int get_event_number () const
        { return m_event_number; }
    void set_event_number (int p_event_number)
        { m_event_number = p_event_number; }

    t_boolean get_event_label_is_unique () const
        { return m_event_label_is_unique; }
    void set_event_label_is_unique (t_boolean p_event_label_is_unique)
        { m_event_label_is_unique = p_event_label_is_unique; }

	Description &description() { return m_description; }

    D_sm_spt_pm* get_sm_spt_pm_ptr () const
        { return m_sm_spt_pm_ptr; }
    void set_sm_spt_pm_ptr (D_sm_spt_pm* p_sm_spt_pm_ptr)
        { m_sm_spt_pm_ptr.relate( p_sm_spt_pm_ptr, this ); }

    mc_dbms_Set< D_sm_event_data_item * > *get_sm_event_data_item_coll_ptr () 
        { return &m_sm_event_data_item_coll.getvalue (); }

	D_sm_event_data_item * find_sm_event_data_item_by_id (const Id &p_id);

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    t_boolean was_exported()
        { return m_exported; }

    void set_exported(t_boolean p_exp)
        { m_exported = p_exp; }


    Domain* get_domain_ptr ();

    DELETE_DOWN_DECL_SUBTYPE()



private:

    Id m_id;

    Description m_event_label;

    Description m_event_meaning;

    int m_event_number;

    t_boolean m_event_label_is_unique;

    Description m_description;

    t_boolean m_exported;

    mc_dbms_relationship_1_m(D_sm_event,m_sm_spt_pm_ptr,D_sm_spt_pm,m_sm_event_coll,D_sm_spt_pm*) m_sm_spt_pm_ptr;

    mc_dbms_relationship_m_1(D_sm_event,m_sm_event_data_item_coll,D_sm_event_data_item,m_sm_event_ptr,mc_dbms_Set<D_sm_event_data_item*>) m_sm_event_data_item_coll;

	Id_assigner &id_assigner()
		{ return get_sm_spt_pm_ptr()->get_assigners()->sm_event_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}
};

#endif
