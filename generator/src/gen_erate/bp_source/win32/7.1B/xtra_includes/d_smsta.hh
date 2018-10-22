/*========================================================================
 *
 * File:      $RCSfile: d_smsta.hh,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:41:09 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_sm_state_HH
#define D_sm_state_HH




#include <d_domain.hh>
#include <d_sm_pm.hh>

#include <u_id.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros


//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_spt_pm;
class D_transition;
class D_no_event_transition;
class D_sm_event;
class D_sm_event_data_item;
class D_state_event_matrix_entry;
class D_moore_sm;
class D_moore_action_home;



class D_sm_state
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_sm_state (Domain*, D_sm_spt_pm*);
    D_sm_state (Domain*, D_sm_spt_pm*, const Id & p_id);

    virtual ~D_sm_state ();



    //  IMPLEMENTOR functions
    //

    void delete_sm_state ();

	void copy_sm_state();

    t_uint get_number_of_new_transitions ()
        { return (t_uint) get_new_transition_coll_ptr ()->cardinality (); }

    D_transition* find_new_transition_by_id (Id);

    t_uint get_number_of_no_event_transitions ()
        { return (t_uint) get_no_event_transition_coll_ptr ()->cardinality (); }

    t_uint get_number_of_event_assigned_transitions ();

    D_no_event_transition* find_no_event_transition_by_id (Id);

    t_uint get_number_of_state_event_matrix_entrys ()
        { return (t_uint) get_state_event_matrix_entry_coll_ptr ()->cardinality (); }

    t_uint get_number_of_moore_action_homes ()
        { return (t_uint) get_moore_action_home_coll_ptr ()->cardinality (); }

    
    t_boolean audit_same_data_rule();   // i2801.3a.1

    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    const Id & get_id () const
        { return m_id; }

    int get_state_number () const
        { return m_state_number; }
    void set_state_number (int p_state_number)
        { m_state_number = p_state_number; }

    Description get_state_name () const
        { return m_state_name; }
    void set_state_name (Description p_state_name)
        { m_state_name = p_state_name; }

    t_boolean get_deletion_final_state () const
        { return m_deletion_final_state; }
    void set_deletion_final_state (t_boolean p_deletion_final_state)
        { m_deletion_final_state = p_deletion_final_state; }

    D_sm_spt_pm* get_sm_spt_pm_ptr () const
        { return m_sm_spt_pm_ptr; }
    void set_sm_spt_pm_ptr (D_sm_spt_pm* p_sm_spt_pm_ptr)
        { m_sm_spt_pm_ptr.relate( p_sm_spt_pm_ptr, this ); }

    mc_dbms_Set<D_transition*>*
        get_new_transition_coll_ptr ()
        { return &(m_new_transition_coll.getvalue ()); }

    mc_dbms_Set<D_no_event_transition*>*
        get_no_event_transition_coll_ptr ()
        { return &(m_no_event_transition_coll.getvalue ()); }

    mc_dbms_Set<D_state_event_matrix_entry*>*
        get_state_event_matrix_entry_coll_ptr ()
        { return &(m_state_event_matrix_entry_coll.getvalue ()); }

    mc_dbms_List<D_moore_action_home*>*
        get_moore_action_home_coll_ptr ()
        { return &(m_moore_action_home_coll.getvalue ()); }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    Domain* get_domain_ptr ();

    void create_state_event_matrix_entrys_for_constructor ();

    void create_moore_action_homes_for_constructor ();

    DELETE_DOWN_DECL_SUBTYPE()


private:

    Id m_id;

    int m_state_number;

    Description m_state_name;

    t_boolean m_deletion_final_state;


    mc_dbms_relationship_1_m(D_sm_state,m_sm_spt_pm_ptr,D_sm_spt_pm,m_sm_state_coll,D_sm_spt_pm*) m_sm_spt_pm_ptr;

    // Removed for i2751.1.4

    mc_dbms_relationship_m_1(D_sm_state,m_new_transition_coll,D_transition,m_new_sm_state_ptr,mc_dbms_Set<D_transition*>) m_new_transition_coll;

    mc_dbms_relationship_m_1(D_sm_state,m_no_event_transition_coll,D_no_event_transition,m_sm_state_ptr,mc_dbms_Set<D_no_event_transition*>) m_no_event_transition_coll;

    mc_dbms_relationship_m_1(D_sm_state,m_state_event_matrix_entry_coll,D_state_event_matrix_entry,m_sm_state_ptr,mc_dbms_Set<D_state_event_matrix_entry*>) m_state_event_matrix_entry_coll;

    mc_dbms_relationship_m_1(D_sm_state,m_moore_action_home_coll,D_moore_action_home,m_sm_state_ptr,mc_dbms_List<D_moore_action_home*>) m_moore_action_home_coll;

	Id_assigner &id_assigner()
		{ return get_sm_spt_pm_ptr()->get_assigners()->sm_state_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}
};

#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
