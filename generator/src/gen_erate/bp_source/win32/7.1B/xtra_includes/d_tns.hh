/*========================================================================
 *
 * File:      $RCSfile: d_tns.hh,v $
 * Version:   $Revision: 1.10 $
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

#ifndef D_transition_HH
#define D_transition_HH




#include <u_id.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include <d_domain.hh>
#include <d_sm_pm.hh>

//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_spt_pm;
class D_sm_state;
class D_mealy_sm;
class D_mealy_action_home;
class D_no_event_transition;
class D_creation_transition;
class D_new_state_transition;



class D_transition
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_transition (Domain*, D_sm_spt_pm*);
    D_transition (Domain*, D_sm_spt_pm*, Id p_id);

    virtual ~D_transition ();



    //  IMPLEMENTOR functions
    //

    void delete_transition ();

    t_uint get_number_of_mealy_action_homes ()
        { if ( get_mealy_action_home_coll_ptr () != 0 ) 
		    return (t_uint) get_mealy_action_home_coll_ptr ()->cardinality ();
		  else
		    return 0;
	    }

	virtual void copy_transition()
		{ /* DO NOTHING */ }

    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    Id get_id () const
        { return m_id; }

    D_sm_spt_pm* get_sm_spt_pm_ptr () const
        { return m_sm_spt_pm_ptr; }
    void set_sm_spt_pm_ptr (D_sm_spt_pm* p_sm_spt_pm_ptr)
        { m_sm_spt_pm_ptr.relate( p_sm_spt_pm_ptr, this ); }

    D_sm_state* get_new_sm_state_ptr () const
        { return m_new_sm_state_ptr; }
    void set_new_sm_state_ptr (D_sm_state* p_new_sm_state_ptr)
        { m_new_sm_state_ptr.relate( p_new_sm_state_ptr, this ); }

    mc_dbms_List<D_mealy_action_home*>*
        get_mealy_action_home_coll_ptr ()
        { return &(m_mealy_action_home_coll.getvalue ()); }

    virtual D_no_event_transition* get_no_event_transition_ptr ()
        { return 0; }

    virtual D_creation_transition* get_creation_transition_ptr ()
        { return 0; }

    virtual D_new_state_transition* get_new_state_transition_ptr ()
        { return 0; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    Domain* get_domain_ptr ();

    void create_mealy_action_homes_for_constructor ();

    t_boolean was_exported()
        { return m_exported; }

    void set_exported(t_boolean p_exp)
        { m_exported = p_exp; }


    DELETE_DOWN_DECL_SUPERTYPE()


private:

    Id m_id;
    t_boolean m_exported;

    mc_dbms_relationship_1_m(D_transition,m_sm_spt_pm_ptr,D_sm_spt_pm,m_transition_coll,D_sm_spt_pm*) m_sm_spt_pm_ptr;

    mc_dbms_relationship_1_m(D_transition,m_new_sm_state_ptr,D_sm_state,m_new_transition_coll,D_sm_state*) m_new_sm_state_ptr;

    mc_dbms_relationship_m_1(D_transition,m_mealy_action_home_coll,D_mealy_action_home,m_transition_ptr,mc_dbms_List<D_mealy_action_home*>) m_mealy_action_home_coll;

	Id_assigner &id_assigner()
		{ return get_sm_spt_pm_ptr()->get_assigners()->transition_id_assigner(); }

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
