/*========================================================================
 *
 * File:      $RCSfile: d_dattyp.hh,v $
 * Version:   $Revision: 1.10 $
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

#ifndef D_DATA_TYPE_HH
#define D_DATA_TYPE_HH


#include <u_desc.hh>
#include <u_string.hh>
#include <u_deldwn.hh>     // For delete_down() macros


#include "d_typdef.hh"
#include "d_dd_sam.hh"

class D_core_data_type;
class D_user_data_type;
class D_enum_data_type;
class D_enumerator;

class D_data_type_referent
{
public:
    t_class_type m_referent_type;
    void* m_referent;
    t_boolean m_read_only;
};

class D_data_type
	{
	public:
		virtual ~D_data_type();

	virtual	D_core_data_type * get_core_data_type_ptr () { return 0; }
	virtual	D_user_data_type * get_user_data_type_ptr () { return 0; } 
	virtual	D_enum_data_type * get_enum_data_type_ptr () { return 0; } 

	static mc_dbms_typespec* get_mc_dbms_typespec ();

	void	delete_data_type ();

	D_dd_srm_scm_sam * get_dd_srm_scm_sam_ptr ()
		{ return m_dd_srm_scm_sam_ptr; }

	Domain * get_domain_ptr ()
		{ return get_dd_srm_scm_sam_ptr ()->get_domain_ptr (); }

	const Id & get_id () const { return m_id; }

	Description &name () { return m_name; }

	Description &description () { return m_description; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    int find_all_data_type_references(mc_dbms_List<D_data_type_referent*>&);

    t_boolean was_referenced()
        { return m_referenced; }

    void set_referenced(t_boolean p_exp)
        { m_referenced = p_exp; }

   DELETE_DOWN_DECL_SUPERTYPE()

	protected:
				 D_data_type (D_dd_srm_scm_sam *);
				 D_data_type (D_dd_srm_scm_sam *, const Id & p_id);


	private:

		Description	m_name;
		Id 		m_id;
		Description m_description;

        t_boolean m_referenced;    // only used internally for export

		mc_dbms_relationship_1_m(D_data_type,m_dd_srm_scm_sam_ptr,D_dd_srm_scm_sam,m_data_type_coll,D_dd_srm_scm_sam*) m_dd_srm_scm_sam_ptr;

	Id_assigner &id_assigner()
		{ return get_dd_srm_scm_sam_ptr()->get_assigners()->data_type_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}
	};


class D_core_data_type : public D_data_type
	{
	public:
		D_core_data_type (D_dd_srm_scm_sam *);
		virtual ~D_core_data_type();

		virtual D_core_data_type * get_core_data_type_ptr () { return this; }

		static mc_dbms_typespec* get_mc_dbms_typespec ();

		mc_dbms_List< D_user_data_type * > *get_user_data_type_coll_ptr ()
			{ return &(m_user_data_type_coll.getvalue ()); }

		t_uint get_core_data_type_type ()
			{ return core_type; }
		void set_core_data_type_type (t_uint p_type)
			{ core_type = p_type; }

      DELETE_DOWN_DECL_SUBTYPE()

	private:

		t_uint core_type;

	mc_dbms_relationship_m_1(D_core_data_type,m_user_data_type_coll,D_user_data_type,m_core_data_type_ptr,mc_dbms_List< D_user_data_type * >) m_user_data_type_coll;

	};


class D_user_data_type : public D_data_type
	{
	public:
		D_user_data_type (D_dd_srm_scm_sam *,
			t_user_data_type p_mapping = USER_DEFINED_USERDATATYPE);

		D_user_data_type (D_dd_srm_scm_sam *, const Id & p_id,
			t_user_data_type p_mapping = USER_DEFINED_USERDATATYPE);

		virtual ~D_user_data_type();

		virtual D_user_data_type * get_user_data_type_ptr () { return this; }

		static mc_dbms_typespec* get_mc_dbms_typespec ();

		D_core_data_type * get_core_data_type_ptr ()
			{ return m_core_data_type_ptr; }
		void set_core_data_type_ptr (D_core_data_type * p_ptr)
			{ m_core_data_type_ptr.relate( p_ptr, this ); }

		t_uint get_general_service_mapping ()
			{ return m_general_service_mapping; }
		void set_general_service_mapping (t_user_data_type p_mapping)
			{ m_general_service_mapping = (t_uint)p_mapping; }

		static D_enum_data_type* migrate_to_enum_data_type(D_user_data_type*);

      DELETE_DOWN_DECL_SUBTYPE()

	private:

		t_uint m_general_service_mapping;

		mc_dbms_relationship_1_m(D_user_data_type,m_core_data_type_ptr,D_core_data_type,m_user_data_type_coll,D_core_data_type*) m_core_data_type_ptr;

	};


class D_enum_data_type : public D_data_type
	{
	public:
		D_enum_data_type (D_dd_srm_scm_sam *);
		D_enum_data_type (D_dd_srm_scm_sam *, const Id & p_id);

		virtual ~D_enum_data_type();

		virtual D_enum_data_type * get_enum_data_type_ptr () { return this; }

		static mc_dbms_typespec* get_mc_dbms_typespec ();

		static D_user_data_type* migrate_to_user_data_type(D_enum_data_type*);

		D_enumerator* find_enumerator_by_id( const Id& );
		D_enumerator* find_enumerator_by_name( const vchar* p_name );
		D_enumerator* create_enumerator (const vchar *p_name);
		D_enumerator* create_enumerator (const vchar *p_name, const Id &p_id);

		mc_dbms_List< D_enumerator * > *get_enumerator_coll_ptr ()
			{ return &(m_enumerator_coll.getvalue ()); }

      DELETE_DOWN_DECL_SUBTYPE()

	private:

	mc_dbms_relationship_m_1(D_enum_data_type,m_enumerator_coll,D_enumerator, m_enum_data_type_ptr,mc_dbms_List< D_enumerator * >) m_enumerator_coll;

	};

class D_enumerator
	{
	public:
		D_enumerator (D_enum_data_type *);
		D_enumerator (D_enum_data_type *, const Id & p_id);

		virtual ~D_enumerator();

		D_enum_data_type * get_enum_data_type_ptr ()
			{ return m_enum_data_type_ptr; }
		void set_enum_data_type_ptr (D_enum_data_type * p_ptr)
			{ m_enum_data_type_ptr.relate( p_ptr, this ); }

		const Id & get_id () const { return m_id; }

		Description &name () { return m_name; }

		Description &description () { return m_description; }

		static mc_dbms_typespec* get_mc_dbms_typespec ();

      DELETE_DOWN_DECL_SUBTYPE()

	private:

		Description	m_name;
		Id 		m_id;
		Description m_description;

		mc_dbms_relationship_1_m(D_enumerator,m_enum_data_type_ptr,D_enum_data_type,m_enumerator_coll,D_enum_data_type*) m_enum_data_type_ptr;

	Id_assigner &id_assigner()
		{ return get_enum_data_type_ptr()->get_dd_srm_scm_sam_ptr()->get_assigners()->enumerator_id_assigner(); }

	Id assign_id()
		{
		return ( id_assigner().assign_next_id() );
		}

	};


#endif
