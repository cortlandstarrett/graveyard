/*========================================================================
 *
 * File:      $RCSfile: d_action.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:13 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_action_HH
#define D_action_HH




#include <d_domain.hh>
#include <d_sm_pm.hh>

#include <d_exespec.hh>

#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_action_home;
class D_derived_path_item;



class D_action : public D_execution_spec
{
public:
	// Constants and enums

    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_action (Domain*, D_sm_spt_pm*);

    virtual ~D_action ();



    //  IMPLEMENTOR functions
    //

	void delete_action();

    const Description & get_description()
	   { return m_descrip; }
    void set_description( const Description& p_descrip)
	   { m_descrip = p_descrip; }


    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    const Id & get_id () const
        { return m_id; }
	void set_id (const Id & p_id)
		{ m_id = p_id; }

    D_sm_spt_pm* get_sm_spt_pm_ptr () const
        { return m_sm_spt_pm_ptr; }
    void set_sm_spt_pm_ptr (D_sm_spt_pm* p_sm_spt_pm_ptr)
        { m_sm_spt_pm_ptr.relate( p_sm_spt_pm_ptr, this ); }

    D_action_home* get_action_home_ptr () const
        { return m_action_home_ptr; }
    void set_action_home_ptr (D_action_home* p_action_home_ptr)
        { m_action_home_ptr = p_action_home_ptr; }

	D_action* get_action_ptr ()
	    { return this; }

	int get_spec_type ();    // implemented in a_bush.cc to avoid excessive #includes

	void	add_derived_communication_path
				(const Id &evt_id, const Id &dest_id);
	void	add_derived_access_path
				(const Id &data_id, const Id &dest_id);

	void	remove_action_from_derived_paths ();

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    DELETE_DOWN_DECL_SUBTYPE()



private:

    Id m_id;

	Description m_descrip;

    mc_dbms_relationship_1_m(D_action,m_sm_spt_pm_ptr,D_sm_spt_pm,m_action_coll,D_sm_spt_pm*) m_sm_spt_pm_ptr;

    mc_dbms_relationship_1_1(D_action,m_action_home_ptr,D_action_home,m_action_ptr,D_action_home*) m_action_home_ptr;

	// Helping functions

	Id_assigner & id_assigner()
		{ return get_sm_spt_pm_ptr()->get_assigners()->action_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}
};


#endif
