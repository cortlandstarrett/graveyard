/*========================================================================
 *
 * File:      $RCSfile: d_suppdt.hh,v $
 * Version:   $Revision: 1.10 $
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

#ifndef D_supplemental_data_HH
#define D_supplemental_data_HH




#include <u_id.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include <d_sm_pm.hh>

class D_supplemental_data_item;
class D_sm_state;
class D_sm_event;
class D_sm_spt_pm;


//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//

class D_supplemental_data
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();

    static D_supplemental_data * create (D_sm_spt_pm *, t_boolean);
    static D_supplemental_data * create (D_sm_spt_pm *, const Id & p_id, t_boolean);

    virtual ~D_supplemental_data ();



    //  IMPLEMENTOR functions
    //

    t_boolean compare_signature( D_supplemental_data* );   // i2801.6.1 added

    void delete_supplemental_data ();


    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    D_sm_spt_pm* get_sm_spt_pm_ptr () const
        { return m_sm_spt_pm_ptr; }
    void set_sm_spt_pm_ptr (D_sm_spt_pm* p_sm_spt_pm_ptr)
        { m_sm_spt_pm_ptr.relate( p_sm_spt_pm_ptr, this ); }

	mc_dbms_Set< D_supplemental_data_item * > *
		get_supplemental_data_item_coll_ptr()
		{ return &m_supplemental_data_item_coll.getvalue(); }

    // Removed function get_sm_state_coll_ptr() for i2751.1.3
 
	mc_dbms_List< D_sm_event * > *
		get_sm_event_coll_ptr()
		{ return &m_sm_event_coll.getvalue(); }
 

	void add_event_data_item (const Id &p_id);
	void remove_event_data_item (const Id &p_id);

	void remove_event_from_supp_data (D_sm_event *);

    const Id & get_id () const
	{ return m_id; }

    t_boolean is_non_local () const
	{ return m_non_local; }

    t_boolean was_exported()
        { return m_exported; }

    void set_exported(t_boolean p_exp)
        { m_exported = p_exp; }

    DELETE_DOWN_DECL_SUBTYPE()


private:

    Id m_id;
	t_boolean m_non_local;
    t_boolean m_exported;

    mc_dbms_relationship_1_m(D_supplemental_data,m_sm_spt_pm_ptr,D_sm_spt_pm,m_supplemental_data_coll,D_sm_spt_pm*) m_sm_spt_pm_ptr;

	mc_dbms_relationship_m_1(D_supplemental_data,m_supplemental_data_item_coll,D_supplemental_data_item,m_supplemental_data_ptr,mc_dbms_Set<D_supplemental_data_item*>) m_supplemental_data_item_coll;
 
  // Removed for i2751.1.4
 
	mc_dbms_relationship_m_1(D_supplemental_data,m_sm_event_coll,D_sm_event,m_supplemental_data_ptr,mc_dbms_List<D_sm_event*>) m_sm_event_coll;

	// Helping functions follow
 
	D_supplemental_data (D_sm_spt_pm *, t_boolean);
	D_supplemental_data (D_sm_spt_pm *, const Id & p_id, t_boolean);

	Id_assigner &id_assigner()
		{ return get_sm_spt_pm_ptr()->get_assigners()->supp_data_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}
};


#endif
