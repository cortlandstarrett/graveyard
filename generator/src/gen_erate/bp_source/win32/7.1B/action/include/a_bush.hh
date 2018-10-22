/*========================================================================
 *
 * File:      $RCSfile: a_bush.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:42:39 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>
#ifndef AL_BUSH_HH
#define AL_BUSH_HH

// AL_bush.hh


#include <vchar.h>

#include "u_id.hh"

#include <u_string.hh>
#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

#include "d_typdef.hh"
#include "d_domain.hh"
#include "d_exespec.hh"

#include "a_stmtyp.hh"

// Includes for the PCCTS parser
#include "myAST.h"


// Classes we define in this header file

class AL_Bush_action;
class AL_Bush_statement;
class AL_Bush_statement_component;
class AL_Bush_literal;
class AL_Bush_relocatable;

// Classes defined elsewhere that we only need to reference
class P;
class P_error;
class D_dd_srm_scm_sam;

class AL_Bush_action
{
public:

	static AL_Bush_action * create( D_execution_spec *p_action_ptr,
                                  const vchar *p_action_desc,
								  Description &p_err_msg,
                                  long int &p_bad_line_num,
                                  long int &p_err_start,
                                  long int &p_err_end );

	static void create_bushes(P* parser, P_error* er,
	                          const vchar *p_action_desc,
                              const char *action_desc_ASCII,
							  AL_Bush_action * new_bush_action_ptr);

	~AL_Bush_action();

	// IMPLEMENTOR functions

	// render returns the  resultant relocatable form with "#"'s for undefined
	// symbols UNLESS the p_encode_reloc argument is TRUE, which means to
	// encode the relocatable for such things as export, etc.

	Description render( t_boolean p_encode_reloc = FALSE ) const;

	void derive_comm_path( AST* event_label );

	void derive_access_path( AST* attribute );

	// resolved returns TRUE if no undefined symbols; FALSE otherwise.

	t_boolean resolved() const;

	// OOA objects we may need to reference

	Domain * get_domain_ptr() const
		{ return( get_D_execution_spec_ptr()->get_domain_ptr() ); }

	mc_dbms_database * get_db_ptr() const
		{ return( get_domain_ptr()->get_db_ptr() ); }

    void mark_referenced_datatypes(D_dd_srm_scm_sam*);

	// ACCESS functions

	D_execution_spec * get_D_execution_spec_ptr() const
		{ return( m_D_execution_spec_ptr ); }
	void set_D_execution_spec_ptr( D_execution_spec * p_D_execution_spec_ptr )
		{ m_D_execution_spec_ptr = p_D_execution_spec_ptr; }

	mc_dbms_List< AL_Bush_statement * > *
		get_statement_coll_ptr() const
		{
		return( ( mc_dbms_List< AL_Bush_statement * > * )
			& m_statement_coll.getvalue() );
		}
  
	mc_dbms_List< AL_Bush_statement_component * > *
		get_component_coll_ptr() const
		{
		return( ( mc_dbms_List< AL_Bush_statement_component * > * )
			& m_component_coll.getvalue() );
		}
  
    DELETE_DOWN_DECL_SUBTYPE()


private:

	mc_dbms_relationship_1_1(AL_Bush_action,m_D_execution_spec_ptr,D_execution_spec,m_AL_Action_ptr,D_execution_spec *) m_D_execution_spec_ptr;

	mc_dbms_relationship_m_1(AL_Bush_action,m_statement_coll,AL_Bush_statement,m_action_ptr,mc_dbms_List< AL_Bush_statement * > ) m_statement_coll;

	mc_dbms_relationship_m_1(AL_Bush_action,m_component_coll,AL_Bush_statement_component,m_action_ptr,mc_dbms_List< AL_Bush_statement_component * > ) m_component_coll;

	void * spare1;
	void * spare2;
	void * spare3;
	long spare4;

	// Helping functions

	AL_Bush_action();

	static mc_dbms_typespec * get_mc_dbms_typespec();

	void clear_persistent_ptrs();
};


class AL_Bush_statement
{
public:

	static AL_Bush_statement * create( AL_Bush_action * p_action_ptr );

	~AL_Bush_statement();

	Description render( t_boolean p_encode_reloc ) const;

    void mark_referenced_datatypes(D_dd_srm_scm_sam*);

	// OOA objects we may need to reference

	Domain * get_domain_ptr() const
		{ return( get_action_ptr()->get_domain_ptr() ); }

	mc_dbms_database * get_db_ptr()
		{ return( get_action_ptr()->get_db_ptr() ); }

	// Access functions

	Id get_id() const
		{ return( m_id ); }

	int get_type() const
		{ return( m_type ); }
	void set_type( int p_type )
		{ m_type = p_type; }

	AL_Bush_action * get_action_ptr() const
		{ return( m_action_ptr ); }

	mc_dbms_List< AL_Bush_statement_component * > *
		get_component_coll_ptr() const
		{
		return( ( mc_dbms_List< AL_Bush_statement_component * > * )
			& m_component_coll.getvalue() );
		}

	const mc_dbms_List< AL_Bush_statement_component * > *
		get_ro_component_coll_ptr() const
		{
		return( ( const mc_dbms_List< AL_Bush_statement_component * > * )
			& m_component_coll.getvalue() );
		}

    DELETE_DOWN_DECL_SUBTYPE()


private:

	const Id m_id;
	int m_type;	// used to be of type t_statement_type

	mc_dbms_relationship_1_m(AL_Bush_statement,m_action_ptr,AL_Bush_action,m_statement_coll,AL_Bush_action *) m_action_ptr;

	mc_dbms_relationship_m_m(AL_Bush_statement,m_component_coll,AL_Bush_statement_component,m_statement_coll,mc_dbms_List< AL_Bush_statement_component * > ) m_component_coll;

	// Helping functions

	void * spare1;
	void * spare2;
	void * spare3;
	long spare4;

	static mc_dbms_typespec * get_mc_dbms_typespec();

	AL_Bush_statement( AL_Bush_action * p_action_ptr );

};


class AL_Bush_statement_component
{
public:

	virtual ~AL_Bush_statement_component();

	virtual void delete_if_last_reference()
		{ delete this; }

	virtual Description render( t_boolean p_encode_reloc ) const = 0;

    virtual void mark_referenced_datatypes(D_dd_srm_scm_sam*) const = 0;

	virtual t_boolean resolved() const = 0;

	virtual void clear_persistent_ptrs()
		{}

	// OOA objects we may need to reference

	Domain * get_domain_ptr() const
		{ return( get_action_ptr()->get_domain_ptr() ); }

	mc_dbms_database * get_db_ptr()
		{ return( get_action_ptr()->get_db_ptr() ); }

	// Derived class pointers

	virtual AL_Bush_literal * get_literal_ptr()
		{ return( 0 ); }
	virtual AL_Bush_relocatable * get_relocatable_ptr()
		{ return( 0 ); }

	// Access functions

	AL_Bush_action * get_action_ptr() const
		{ return( m_action_ptr ); }

	AL_Bush_statement * get_statement_ptr()
		{ return( m_statement_coll.pick() ); }

	mc_dbms_List< AL_Bush_statement * > * get_statement_coll_ptr() const
		{
		return( ( mc_dbms_List< AL_Bush_statement * > * )
			& m_statement_coll.getvalue() );
		}

    DELETE_DOWN_DECL_SUPERTYPE()


protected:

	AL_Bush_statement_component();

	void set_action_ptr(AL_Bush_action *p_action_ptr)
		{ m_action_ptr.relate( p_action_ptr, this ); }


private:

	mc_dbms_relationship_1_m(AL_Bush_statement_component,m_action_ptr,AL_Bush_action,m_component_coll,AL_Bush_action *) m_action_ptr;

	mc_dbms_relationship_m_m(AL_Bush_statement_component,m_statement_coll,AL_Bush_statement,m_component_coll,mc_dbms_List< AL_Bush_statement * >) m_statement_coll;

	void * spare1;
	void * spare2;
	void * spare3;
	long spare4;

	// Helping functions

	static mc_dbms_typespec * get_mc_dbms_typespec();
};


class AL_Bush_literal : public AL_Bush_statement_component
{
public:

	static AL_Bush_literal * create( const vchar *p_lit,
		const AL_Bush_statement * p_stmt_ptr );

	virtual ~AL_Bush_literal();

	virtual Description render(  t_boolean /* p_encode_reloc */ ) const
		{ return( m_string ); }

	virtual t_boolean resolved() const
		{ return( TRUE ); }

    virtual void mark_referenced_datatypes(D_dd_srm_scm_sam*) const
        { /* do nothing */ }

	// Derived class pointers

	virtual AL_Bush_literal * get_literal_ptr()
		{ return( this ); }

	// Access functions

	const Description & get_string() const
		{ return( m_string ); }

    DELETE_DOWN_DECL_SUBTYPE()


protected:

 	AL_Bush_literal( const vchar * p_string );

private:

	Description m_string;

	void * spare1;
	void * spare2;
	void * spare3;
	long spare4;

	// Helping functions

	static mc_dbms_typespec * get_mc_dbms_typespec();

};


class AL_Bush_relocatable : public AL_Bush_statement_component
{
public:

  static const Description UNRESOLVED_SYMBOL;
	static const Description LEADING_DELIMITER;

	static AL_Bush_relocatable * create( const vchar *p_string,
		const Id & p_object_id, int p_field_id,
		AL_Bush_statement * p_stmt_ptr );

	static t_boolean get_mapped_string( Domain * p_domain_ptr,
                                      int p_id_class_type,
                                      unsigned long p_id_entire_value,
                                      int p_field_id,
                                      const vchar *orig_string,
                                      Description & mapped_string );

	virtual ~AL_Bush_relocatable();

	virtual Description render( t_boolean p_encode_reloc ) const;

    virtual void mark_referenced_datatypes(D_dd_srm_scm_sam*) const;

	virtual t_boolean resolved() const;

	// Derived class pointers

	virtual AL_Bush_relocatable * get_relocatable_ptr()
		{ return( this ); }

	// Access functions

	const Description & get_orig_relocatable() const
		{ return m_orig_relocatable; }

	const Id & get_object_id() const
		{ return( m_object_id ); }

	int get_field_id() const
		{ return( m_field_id ); }

	// IMPORTANT: spare1 is now UNAVAILABLE since used for encoded relocatable.

    DELETE_DOWN_DECL_SUBTYPE()


protected:

	AL_Bush_relocatable( const vchar * p_orig_reloc, const Id & p_object_id,
		int p_field_id );

private:

	Description m_orig_relocatable;
	const Id m_object_id;
	const int m_field_id;

	Description m_encoded_reloc;

	void * spare1;
	void * spare2;
	void * spare3;
	long spare4;

	// Helping functions

	static mc_dbms_typespec * get_mc_dbms_typespec();

	const Description & get_encoded_reloc() const
		{ return m_encoded_reloc; }

};


#endif
