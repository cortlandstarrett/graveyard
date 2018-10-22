/*========================================================================
 *
 * File:      $RCSfile: d_drvpth.hh,v $
 * Version:   $Revision: 1.10 $
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

#ifndef D_derived_paths_HH
#define D_derived_paths_HH




#include <u_typdef.hh>
#include <u_id.hh>

#include <d_sm_pm.hh>

//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class D_sm_spt_pm;
class D_derived_path_item;
class D_action;
class Attribute;
class D_sm_event;
class D_external_entity_event;


class D_derived_access_path
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_derived_access_path (D_sm_spt_pm*);

    virtual ~D_derived_access_path ();



    //  IMPLEMENTOR functions
    //



    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    Id get_id () const
        { return id; }

	void set_dest_id (Id p_id)
		{ dest_id = p_id; }
	Id get_dest_id ()
		{ return dest_id; }

	void set_spanning_path (t_boolean p_flag) { spanning_flag = p_flag; }
	t_boolean is_spanning_path () { return spanning_flag; }

    D_sm_spt_pm* get_sm_spt_pm_ptr ()
        { return m_sm_spt_pm_ptr; }

	Domain * get_domain_ptr()
		{ return get_sm_spt_pm_ptr()->get_domain_ptr(); }

    mc_dbms_Set<D_derived_path_item *>* get_data_coll_ptr ()
        { return &(m_data_coll.getvalue ()); }

	void add_data_to_path (const Id &p_id, D_action *);

	Attribute * find_object_data_by_id (const Id &p_id);

private:

    Id id;

    Id dest_id;

	t_boolean spanning_flag;

    mc_dbms_relationship_1_m(D_derived_access_path,m_sm_spt_pm_ptr,D_sm_spt_pm,m_derived_access_path_coll,D_sm_spt_pm*) m_sm_spt_pm_ptr;

	mc_dbms_relationship_m_1(D_derived_access_path,m_data_coll,D_derived_path_item,m_derived_access_path_ptr,mc_dbms_Set<D_derived_path_item*>) m_data_coll;

	Id_assigner &id_assigner()
		{ return get_sm_spt_pm_ptr()->get_assigners()->drv_access_path_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}
};



class D_derived_communication_path
{
public:
    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_derived_communication_path (D_sm_spt_pm*);

    virtual ~D_derived_communication_path ();



    //  IMPLEMENTOR functions
    //



    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    Id get_id () const
        { return id; }

	void set_dest_id (const Id &p_id)
		{ dest_id = p_id; }
	Id get_dest_id ()
		{ return dest_id; }

	void set_spanning_path (t_boolean p_flag) { spanning_flag = p_flag; }
	t_boolean is_spanning_path () { return spanning_flag; }

    D_sm_spt_pm* get_sm_spt_pm_ptr ()
        { return m_sm_spt_pm_ptr; }

	Domain * get_domain_ptr()
		{ return get_sm_spt_pm_ptr()->get_domain_ptr(); }

    mc_dbms_Set<D_derived_path_item *>* get_event_coll_ptr ()
        { return &(m_event_coll.getvalue ()); }

	void add_event_to_path (const Id &p_id, D_action *);

	D_sm_event * find_sm_event_by_id (const Id &p_id);
	D_external_entity_event * find_external_entity_event_by_id (const Id &p_id);

private:

    Id id;

    Id dest_id;

	t_boolean spanning_flag;

    mc_dbms_relationship_1_m(D_derived_communication_path,m_sm_spt_pm_ptr,D_sm_spt_pm,m_derived_communication_path_coll,D_sm_spt_pm*) m_sm_spt_pm_ptr;

	mc_dbms_relationship_m_1(D_derived_communication_path,m_event_coll,D_derived_path_item,m_derived_comm_path_ptr,mc_dbms_Set<D_derived_path_item*>) m_event_coll;

	Id_assigner &id_assigner()
		{ return get_sm_spt_pm_ptr()->get_assigners()->drv_comm_path_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}
};

class D_derived_path_item
{
public:

    static mc_dbms_typespec* get_mc_dbms_typespec ();

	virtual ~D_derived_path_item ();


	static D_derived_path_item * create (const Id &p_id, D_action *,
		D_derived_communication_path *);

	static D_derived_path_item * create (const Id &p_id, D_action *,
		D_derived_access_path *);

	void set_derived_comm_path_ptr (D_derived_communication_path * p_ptr)
		{ m_derived_comm_path_ptr.relate( p_ptr, this ); }
	D_derived_communication_path * get_derived_comm_path_ptr ()
		{ return m_derived_comm_path_ptr; }

	void set_derived_access_path_ptr (D_derived_access_path * p_ptr)
		{ m_derived_access_path_ptr.relate( p_ptr, this ); }
	D_derived_access_path * get_derived_access_path_ptr ()
		{ return m_derived_access_path_ptr; }

    mc_dbms_Set<D_action *>* get_action_coll_ptr ()
        { return &(m_action_coll.getvalue ()); }

	Id get_item_id () { return item_id; }

private:

	D_derived_path_item (const Id &p_id);

	Id item_id;

    mc_dbms_relationship_1_m(D_derived_path_item,m_derived_comm_path_ptr,D_derived_communication_path,m_event_coll,D_derived_communication_path*) m_derived_comm_path_ptr;

    mc_dbms_relationship_1_m(D_derived_path_item,m_derived_access_path_ptr,D_derived_access_path,m_data_coll,D_derived_access_path*) m_derived_access_path_ptr;

};

#endif
