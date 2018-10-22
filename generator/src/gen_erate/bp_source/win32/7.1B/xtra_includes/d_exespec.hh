/*========================================================================
 *
 * File:      $RCSfile: d_exespec.hh,v $
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

#ifndef D_EXESPEC_HH
#define D_EXESPEC_HH




#include <d_typdef.hh>
#include <u_desc.hh>
#include <u_deldwn.hh>     // For DELETE_DOWN macros

//  Declare all classes referenced in this file to reduce the
//    need to include the header files.
//
class AL_Bush_action;
class Domain;
class Id;
class D_action;
class D_bridge;
class D_transformer;
class D_synchronous_service;
class Base_attribute;
class D_data_type;
class D_dd_srm_scm_sam;

class D_execution_spec
{
public:
	// Constants and enums

    //  MANAGER functions
    //

    static mc_dbms_typespec* get_mc_dbms_typespec ();
    D_execution_spec (Domain*);

    virtual ~D_execution_spec ();



    //  IMPLEMENTOR functions
    //

	void delete_action();

	// The following functions exist for the User of this class to determine
	// how in the heck they want to render the description based upon previous
	// operations and states.

	// The following operations/states are useful to determine exactly what
	// description text should be rendered. IMPORTANT: It up to the user
	// to set these accordingly; they will NOT be set automatically.

	enum t_desc_state { DESC_INIT, DESC_USE_VERBATIM, DESC_USE_RELOCATABLE,
		DESC_USE_OTHER_1, DESC_USE_OTHER_2 };

     // AL_PARSE_ON_APPLY_SET is only used for exporting/importing to indicate
     // when parse_on_apply is true, but no parse has been done yet.
  enum t_parse_result { AL_NOT_PARSED = 0,
                        AL_PARSE_SUCCESSFUL = 1,
                        AL_PARSE_UNSUCCESSFUL = 2,
                        AL_PARSE_ON_APPLY_SET = 3 };

	t_desc_state get_desc_state() const
		{ return m_desc_state; }
	void set_desc_state( t_desc_state p_desc_state )
		{ m_desc_state = p_desc_state; }

	// parse returns TRUE if parse successful; FALSE otherwise with p_err_msg
	// filled-out. Note that parse will ALWAYS use the verbatim description
	// as its input (see below).
	// A successful parse must not have ANY syntax errors or undefined symbols.
	// If a successful parse, then we will create a relocatable form replacing
	// the previous one (if one existed). If not successful, then we will leave
	// the previous parse tree intact (if it existed). Note that a relocatable
	// form resulting from a successful parse may subsequently render a
	// description with undefined symbols if the database changed underneath
	// since the last parse.

	t_boolean parse( Description &p_err_msg, long int &p_bad_line_num,
                   long int &p_err_start, long int &p_err_end );

	t_parse_result get_last_parse_result() const
		{ return( m_last_parse_result); }
	t_boolean last_parse_successful() const
		{ return( m_last_parse_result == AL_PARSE_SUCCESSFUL ); }
	void set_last_parse_flag (t_parse_result p_flag)
		{ m_last_parse_result = p_flag; }

	// current_parse_successful() returns TRUE if the last parse was
	// successful and there currently are no undefined/unresolved symbols.

	t_boolean current_parse_successful() const
		{ return( last_parse_successful() && relocatable_desc_resolved() ); }

	t_boolean relocatable_desc_exists() const;

	// relocatable_desc_resolved returns TRUE if relocatable form has no
	// undefined symbols at this exact moment; FALSE otherwise.

	t_boolean relocatable_desc_resolved() const;

	// get_relocatable_desc returns the relocatable description regardless of
	// undefined symbols or not (undefined's will be represented by "####"'s).
	// If relocatable form doesn't exist, then a null ("") description is
	// returned.

	Description get_relocatable_desc() const;

	// get_export_desc returns a description that has the relocatables
    // encoded so ids may be resolved to their new string value on import.

	Description get_export_desc() const;

	void decode_verbatim( t_boolean p_retain_ids );

	// Get and set verbatim description unconditionally.

	const Description & get_verbatim_desc() const
		{ return m_verbatim_desc; }
	void set_verbatim_desc( const Description & p_desc )
		{ m_verbatim_desc = p_desc; }

	t_boolean get_parse_on_apply () const
		{ return m_parse_on_apply; }
	void set_parse_on_apply ( t_boolean p_parse_on_apply );

	// "action_specification()" should be eventually be written to return the
	// appropriate internal description based on past operations and results.
	// Ideally, I would like to get rid of this, but the M_Model stuff depends
	// on this returning a &.

    Description & action_specification();

    //  Find all datatypes referenced, and mark them so for export
    void mark_referenced_datatypes(D_dd_srm_scm_sam*);

    //  ACCESS functions.  Note that a reference (i.e., &) allows
    //    the corresponding field/attribute to be an l-value or
    //    r-value.  However, prefixing a "const" restricts usage
    //    an r-value, somthing we want to do when we access a
    //    field in another class.
    //

    AL_Bush_action* get_AL_Action_ptr () const
        { return m_AL_Action_ptr; }
    void set_AL_Action_ptr (AL_Bush_action* p_AL_Action_ptr)
        { m_AL_Action_ptr = p_AL_Action_ptr; }

    mc_dbms_segment* get_config_ptr ()
        { return mc_dbms_segment::of (this); }

    Domain* get_domain_ptr ()
	    { return m_domain_ptr; }

    void set_description_shown(t_boolean p_desc_shown)
        { m_description_shown = p_desc_shown; }

    t_boolean is_description_shown()
        { return m_description_shown; }

	virtual D_action* get_action_ptr ()
	    { return 0; }
	virtual D_transformer* get_transformer_ptr ()
	    { return 0; }
	virtual D_bridge* get_bridge_ptr ()
	    { return 0; }
	virtual D_synchronous_service* get_synch_service_ptr ()
	    { return 0; }
	virtual Base_attribute* get_attribute_ptr ()
	    { return 0; }

	virtual int get_spec_type () = 0;

	virtual D_data_type* get_return_type ()
	     { return 0; }

	virtual void	add_derived_communication_path
				(const Id &evt_id, const Id &dest_id)
        { /* default */ }
	virtual void	add_derived_access_path
				(const Id &data_id, const Id &dest_id)
        { /* default */ }

	virtual void remove_action_from_derived_paths ()
        { /* default */ }

    DELETE_DOWN_DECL_SUBTYPE()



protected:

    Description m_verbatim_desc;
    Description m_tmp_desc;

	t_desc_state m_desc_state;
	t_parse_result m_last_parse_result;

	t_boolean m_parse_on_apply;

    // This variable saves which page is shown in the description
    // data editor, and is only saved in .ooa file
    t_boolean m_description_shown;   

    Domain* m_domain_ptr;

    mc_dbms_relationship_1_1(D_execution_spec,m_AL_Action_ptr,AL_Bush_action,m_D_execution_spec_ptr,AL_Bush_action*) m_AL_Action_ptr;

	// Helping functions

};


#endif
