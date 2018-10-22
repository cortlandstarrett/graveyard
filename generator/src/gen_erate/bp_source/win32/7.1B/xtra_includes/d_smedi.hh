/*========================================================================
 *
 * File:      $RCSfile: d_smedi.hh,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:41:08 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef D_sm_event_data_item_HH
#define D_sm_event_data_item_HH




#include <d_domain.hh>
#include <d_sm_pm.hh>

#include <u_id.hh>
#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros



//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_core_data_type;


class D_sm_event_data_item
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();

    D_sm_event_data_item (Domain*, D_sm_spt_pm*);
    D_sm_event_data_item (Domain*, D_sm_spt_pm*, const Id & p_id);

    virtual ~D_sm_event_data_item ();



    //  IMPLEMENTOR functions
    //

    void delete_sm_event_data_item ();


    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    const Id & get_id () const
	{ return m_id; }

    Description get_event_data_name () const
        { return m_name; }
    void set_event_data_name (Description p_name)
        { m_name = p_name; }

	Description &description() { return m_description; }

    D_sm_spt_pm* get_sm_spt_pm_ptr () const
        { return m_sm_spt_pm_ptr; }
    void set_sm_spt_pm_ptr (D_sm_spt_pm* p_sm_spt_pm_ptr)
        { m_sm_spt_pm_ptr.relate( p_sm_spt_pm_ptr, this ); }

    Domain* get_domain_ptr ();

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

	D_core_data_type * get_core_data_type_ptr ();
	D_enum_data_type * get_enum_data_type_ptr ();

	void set_data_type_id (Id p_id)
		{ m_data_type_id = p_id; }
	Id get_data_type_id ()
		{ return m_data_type_id; } 

    t_boolean was_exported()
        { return m_exported; }

    void set_exported(t_boolean p_exp)
        { m_exported = p_exp; }

    DELETE_DOWN_DECL_SUBTYPE()



private:

    Id m_id;
    Description m_name;
    Description m_description;
	Id m_data_type_id;

    t_boolean m_exported;

    mc_dbms_relationship_1_m(D_sm_event_data_item,m_sm_spt_pm_ptr,D_sm_spt_pm,m_sm_event_data_item_coll,D_sm_spt_pm*) m_sm_spt_pm_ptr;

	Id_assigner &id_assigner()
		{ return get_sm_spt_pm_ptr()->get_assigners()->sm_edi_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}
};


#endif
