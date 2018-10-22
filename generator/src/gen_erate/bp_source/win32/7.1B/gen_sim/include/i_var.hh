/*========================================================================
 *
 * File:      $RCSfile: i_var.hh,v $
 * Version:   $Revision: 1.12 $
 * Modified:  $Date: 2013/01/10 23:41:17 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef I_VAR_HH
#define I_VAR_HH

#include <stdio.h>
#include <time.h>


#include <vdate.h>

#include <u_typdef.hh>
#include <u_id.hh>
#include <u_string.hh>
#include <u_desc.hh>
#include <d_typdef.hh>
#include <i_obj.hh>
#include <u_keyword.hh>

class I_var;
class I_void_var;
class I_boolean_var;
class I_integer_var;
class I_enumerator_var;
class I_real_var;
class I_string_var;
class I_unique_id_var;
class I_current_state_var;
class I_object_inst_ref_var;
class I_object_inst_ref_set_var;
class I_event_inst_var;
class I_mapping_inst_var;
class I_mapping_inst_ref_var;

class I_date_var;
class I_timestamp_var;
class I_timer_inst_ref_var;

class I_frag_ref_var;

class I_Object;
class I_Object_Instance;
class I_SM_Evt_Inst;

class P_checkGenDB;
class SIM_SOR;


class I_var : public SerializableObject
{
public:
    static mc_dbms_typespec*			get_mc_dbms_typespec ();

					I_var ()
					{
					    m_reference_count = 0;
					}
    virtual				~I_var ();

    static I_var*			create_in_transient
					    (t_core_data_type p_core_data_type,
					    t_user_data_type p_user_data_type);
    static I_var*			create_in_persistent
					    (mc_dbms_segment* p_segment_ptr,
					    t_core_data_type p_core_data_type,
					    t_user_data_type p_user_data_type);

    virtual t_core_data_type		get_core_data_type () const = 0;
    virtual GS_string			get_core_data_type_str () const = 0;
    virtual t_user_data_type		get_user_data_type () const
					{
					    return USER_DEFINED_USERDATATYPE;
					}
    virtual Description&		get_user_data_type_str () const
					{
					    return lc_user_defined_string;
					}
    virtual Description&		get_data_type_str () const = 0;

    virtual t_boolean			get_is_initialized () const
					{
					    return TRUE;
					}
    virtual const Description&		get_value_str () const = 0;
    virtual void			override_value_str
					    (const Description& p_value_str) = 0;

    virtual t_boolean			operator==
					    (const I_var& p_var) const = 0;
    virtual t_boolean			reassign (const I_var* p_var_ptr) = 0;
    virtual I_var*			clone_to_transient () const = 0;
    virtual I_var*			clone_to_persistent () const = 0;

    t_int				get_reference_count ();
    void				increment_reference_count ();
    t_int				decrement_reference_count ();

    I_var*				get_var_ptr ()
					    { return this; }
    virtual I_void_var*			get_void_var_ptr ()
					    { return 0; }
    virtual I_boolean_var*		get_boolean_var_ptr ()
					    { return 0; }
    virtual I_enumerator_var*	get_enumerator_var_ptr ()
					    { return 0; }
    virtual I_integer_var*		get_integer_var_ptr ()
					    { return 0; }
    virtual I_real_var*			get_real_var_ptr ()
					    { return 0; }
    virtual I_string_var*		get_string_var_ptr ()
					    { return 0; }
    virtual I_unique_id_var*		get_unique_id_var_ptr ()
					    { return 0; }
    virtual I_current_state_var*	get_current_state_var_ptr ()
					    {return 0;}
    virtual I_object_inst_ref_var*	get_object_inst_ref_var_ptr ()
					    { return 0; }
    virtual I_object_inst_ref_set_var*	get_object_inst_ref_set_var_ptr ()
					    {return 0; }
    virtual I_event_inst_var*		get_event_inst_var_ptr ()
					    { return 0; }
    virtual I_mapping_inst_var*		get_mapping_inst_var_ptr ()
					    {return 0; }
    virtual I_mapping_inst_ref_var*	get_mapping_inst_ref_var_ptr ()
					    { return 0; }

    virtual I_date_var*			get_date_var_ptr ()
					    { return 0; }
    virtual I_timestamp_var*		get_timestamp_var_ptr ()
					    { return 0; }
    virtual I_timer_inst_ref_var*	get_timer_inst_ref_var_ptr ()
					    { return 0; }

    virtual I_frag_ref_var*		get_frag_ref_var_ptr ()
					    { return 0; }

public:

	virtual long persist() {
		long bytesWritten = writeLong(m_reference_count);
		return bytesWritten;
	}
	
	virtual void restore() {
		m_reference_count = readLong();
	}
	
private:
    t_int				m_reference_count;
};





class I_void_var : public I_var
{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_void_var (bool isRestoring = false)
			{
				if ( !isRestoring ) {
				    set_void_str ();
				}
			}
			I_void_var (const I_void_var& )
			{
			    set_void_str ();
			}
    I_void_var&		operator= (const I_void_var&)
			{
			    set_void_str ();
			    return *this;
			}
    virtual		~I_void_var ()
			{
			operator delete( this, ""); // Remove from InstanceTracker
			}

private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_void_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_void_str = p_value_str;
			}
    void		set_void_str ();
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return VOID_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "void";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_void_string;
			}
    virtual I_void_var* get_void_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten = m_void_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		m_void_str.restore();
	}
	
	static char* create() {
		I_void_var* inst = new I_void_var(true);
		inst->restore();
		return (char*)inst;
	}

private:
    Description		m_void_str;
};





class I_boolean_var : public I_var
{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_boolean_var ()
			{
			    set_value (FALSE);
			}
			I_boolean_var (const I_boolean_var& p_boolean_var )
			{
			    set_value (p_boolean_var.get_value ());
			}
    I_boolean_var&	operator= (const I_boolean_var& p_boolean_var)
			{
			    set_value (p_boolean_var.get_value ());
			    return *this;
			}
    virtual		~I_boolean_var ()
			{
			operator delete( this, ""); // Remove from InstanceTracker
			}


			I_boolean_var (t_boolean p_boolean )
			{
			    set_value (p_boolean);
			}
    t_boolean		get_value () const
			{
			    return m_boolean;
			}
    void		set_value (t_boolean p_boolean);


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_boolean_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_boolean_str = p_value_str;
			}
    void		set_boolean_str ();
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return BOOLEAN_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "boolean";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_boolean_string;
			}
    virtual I_boolean_var*
			get_boolean_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += writeLong(m_boolean);
		bytesWritten += m_boolean_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		m_boolean = (t_boolean)readLong();
		m_boolean_str.restore();
	}
	
	static char* create() {
		I_boolean_var* inst = new I_boolean_var();
		inst->restore();
		return (char*)inst;
	}

private:
    t_boolean		m_boolean;
    Description		m_boolean_str;
};


class I_enumerator_var : public I_var

{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_enumerator_var ()
			{
			    set_value ("un-initialized");
			}
			I_enumerator_var (const I_enumerator_var& p_enumerator_var )
			{
			    set_value (p_enumerator_var.get_value ());
			}
    I_enumerator_var&	operator= (const I_enumerator_var& p_enumerator_var)
			{
			    set_value (p_enumerator_var.get_value ());
			    return *this;
			}
    virtual		~I_enumerator_var ()
			{
			operator delete( this, ""); // Remove from InstanceTracker
			}


			I_enumerator_var (const Description& p_enumerator )
			{
			    set_value (p_enumerator);
			}
    Description		get_value () const
			{
			    return m_enumerator_str;
			}
    void		set_value (const Description& p_enumerator);


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_enumerator_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_enumerator_str = p_value_str;
			}
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return ENUMERATION_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "enumeration";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_enumeration_string;
			}
    virtual I_enumerator_var*
			get_enumerator_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += m_enumerator_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		m_enumerator_str.restore();
	}
	
	static char* create() {
		I_enumerator_var* inst = new I_enumerator_var();
		inst->restore();
		return (char*)inst;
	}

private:
    Description		m_enumerator_str;
};





class I_integer_var : public I_var

{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_integer_var ()
			{
			    set_value (0);
			}
			I_integer_var (const I_integer_var& p_integer_var )
			{
			    set_value (p_integer_var.get_value ());
			}
    I_integer_var&	operator= (const I_integer_var& p_integer_var)
			{
			    set_value (p_integer_var.get_value ());
			    return *this;
			}
    virtual		~I_integer_var ()
			{
			operator delete( this, ""); // Remove from InstanceTracker
			}


			I_integer_var (t_long p_integer )
			{
			    set_value (p_integer);
			}
    t_long		get_value () const
			{
			    return m_integer;
			}
    void		set_value (t_long p_integer);


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_integer_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_integer_str = p_value_str;
			}
    void		set_integer_str ();
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return INTEGER_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "integer";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_integer_string;
			}
    virtual I_integer_var*
			get_integer_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += writeLong(m_integer);
		bytesWritten += m_integer_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		m_integer = readLong();
		m_integer_str.restore();
	}
	
	static char* create() {
		I_integer_var* inst = new I_integer_var();
		inst->restore();
		return (char*)inst;
	}

private:
    t_long		m_integer;
    Description		m_integer_str;
};





class I_real_var : public I_var

{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_real_var ()
			{
			    set_value (0.0);
			}
			I_real_var (const I_real_var& p_real_var )
			{
			    set_value (p_real_var.get_value ());
			}
    I_real_var&		operator= (const I_real_var& p_real_var)
			{
			    set_value (p_real_var.get_value ());
			    return *this;
			}
    virtual		~I_real_var ()
			{
			operator delete( this, ""); // Remove from InstanceTracker
			}


			I_real_var (t_double p_real )
			{
			    set_value (p_real);
			}
    t_double		get_value () const
			{
			    return m_real;
			}
    void		set_value (t_double p_real);


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_real_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_real_str = p_value_str;
			}
    void		set_real_str ();
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return REAL_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "real";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_real_string;
			}
    virtual I_real_var*
			get_real_var_ptr ()
			{
			    return this;
			}

public:
	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += writeBlob((char*)&m_real, sizeof(t_double));
		bytesWritten += m_real_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		readBlob((char*)&m_real);
		m_real_str.restore();
	}
	
	static char* create() {
		I_real_var* inst = new I_real_var();
		inst->restore();
		return (char*)inst;
	}

private:
    t_double		m_real;
    Description		m_real_str;
};





class I_string_var : public I_var

{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_string_var ()
			{
			    set_value (Description::Default);
			}
			I_string_var (const I_string_var& p_string_var )
			{
			    set_value
				(((I_string_var&) p_string_var).get_value ());
			}
    I_string_var&	operator= (const I_string_var& p_string_var)
			{
			    set_value
				(((I_string_var&) p_string_var).get_value ());
			    return *this;
			}
    virtual		~I_string_var ()
			{
			operator delete( this, ""); // Remove from InstanceTracker
			}


			I_string_var (const Description& p_string )
			{
			    set_value (p_string);
			}
    const Description&	get_value ()
			{
			    return m_string_str;
			}
    void		set_value (const Description& p_string);
    void		append_to_value (const Description& p_string);


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_string_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_string_str = p_value_str;
			}
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return STRING_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "string";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_string_string;
			}
    virtual I_string_var*
			get_string_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += m_string_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		m_string_str.restore();
	}
	
	static char* create() {
		I_string_var* inst = new I_string_var();
		inst->restore();
		return (char*)inst;
	}

private:
    Description		m_string_str;
};





class I_unique_id_var : public I_var
{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_unique_id_var ()
			{
			    set_value (0);
			}
			I_unique_id_var (const I_unique_id_var& p_unique_id_var )
			{
			    set_value (p_unique_id_var.m_unique_id);
			}
    I_unique_id_var&	operator= (const I_unique_id_var& p_unique_id_var)
			{
			    set_value (p_unique_id_var.m_unique_id);
			    return *this;
			}
    virtual		~I_unique_id_var () 
            {
            operator delete( this, ""); // Remove from InstanceTracker
    		}


			I_unique_id_var (t_ulong p_unique_id_value )
			{
			    set_value (p_unique_id_value);
			}
    t_ulong		get_value () const
			{
			    return m_unique_id;
			}
    void		set_value (t_ulong p_unique_id_value);


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_unique_id_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_unique_id_str = p_value_str;
			}
    void		set_unique_id_str ();
    virtual t_boolean	get_is_initialized () const
			{
			    return (get_value () == 0) ? FALSE : TRUE;
			}
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return UNIQUE_ID_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "unique_id";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_unique_id_string;
			}
    virtual I_unique_id_var*
			get_unique_id_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += writeLong(m_unique_id);
		bytesWritten += m_unique_id_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		m_unique_id = readLong();
		m_unique_id_str.restore();
	}
	
	static char* create() {
		I_unique_id_var* inst = new I_unique_id_var();
		inst->restore();
		return (char*)inst;
	}

private:
    t_ulong		m_unique_id;
    Description		m_unique_id_str;
};





class I_current_state_var : public I_var

{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_current_state_var ()
			{
			    set_value (0);
			}
			I_current_state_var
			    (const I_current_state_var& p_current_state_var )
			{
			    set_value (p_current_state_var.get_value ());
			    override_value_str
				(((I_current_state_var&) p_current_state_var).
				get_value_str ());
			}
    I_current_state_var&
			operator=
			    (const I_current_state_var& p_current_state_var)
			{
			    set_value (p_current_state_var.get_value ());
			    override_value_str
				(((I_current_state_var&) p_current_state_var).
				get_value_str ());
			    return *this;
			}
    virtual		~I_current_state_var ()
			{
			operator delete( this, ""); // Remove from InstanceTracker
			}


			I_current_state_var (t_uint p_current_state )
			{
			    set_value (p_current_state);
			}
    t_uint		get_value () const
			{
			    return m_current_state;
			}
    void		set_value (t_uint p_current_state);


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_current_state_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_current_state_str = p_value_str;
			}
    void		set_current_state_str ();
    virtual t_boolean	get_is_initialized () const
			{
			    return (get_value () == 0) ? FALSE : TRUE;
			}
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return CURRENT_STATE_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "state<State_Model>";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_state_model_string;
			}
    virtual I_current_state_var*
			get_current_state_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += writeLong(m_current_state);
		bytesWritten += m_current_state_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		m_current_state = readLong();
		m_current_state_str.restore();
	}
	
	static char* create() {
		I_current_state_var* inst = new I_current_state_var();
		inst->restore();
		return (char*)inst;
	}

private:
    t_uint		m_current_state;
    Description		m_current_state_str;
};





class GS_select;
class I_Attribute_Instance;

class I_object_inst_ref_var : public I_var
{
friend P_checkGenDB;
friend SIM_SOR;
friend GS_select;
friend I_object_inst_ref_set_var;

public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_object_inst_ref_var (bool restoring = false)
			{
			    m_obj_ptr = 0;
			    m_oinst_ptr = 0;
			    if ( !restoring ) {
				    set_object_inst_ref_str ();
    	            get_extent()->insert( this );    // i2744.2.1
    	        }
			}
			I_object_inst_ref_var
			    (const I_object_inst_ref_var& p_object_inst_ref_var )
			{
			    m_obj_ptr = p_object_inst_ref_var.m_obj_ptr;
			    m_oinst_ptr = p_object_inst_ref_var.m_oinst_ptr;
			    set_object_inst_ref_str ();
                get_extent()->insert( this );    // i2744.2.1
			}
    I_object_inst_ref_var&
			operator=
			    (const I_object_inst_ref_var& p_object_inst_ref_var)
			{
			    m_obj_ptr = p_object_inst_ref_var.m_obj_ptr;
			    m_oinst_ptr = p_object_inst_ref_var.m_oinst_ptr;
			    set_object_inst_ref_str ();
			    return *this;
			}
    virtual		~I_object_inst_ref_var ()
			{
                get_extent()->remove( this );    // i2744.3.1
                operator delete( this, ""); // Remove from InstanceTracker
			}


			I_object_inst_ref_var (const I_object_inst_ref_var*
			    p_object_inst_ref_var_ptr);
			I_object_inst_ref_var (I_object_inst_ref_set_var*
			    p_object_inst_ref_set_var_ptr );
			I_object_inst_ref_var (I_Object* p_obj_ptr,
			    I_Object_Instance* p_oinst_ptr );


    Description	get_key_letters_str () const;
    void		set_last_resort_key_letters_str (const Description& p_str)
			    { m_last_resort_key_letters = p_str; }
    t_boolean		is_empty () const;
    t_uint		cardinality 	() const
			    { return (is_empty() ? 0 : 1); }
    t_boolean		is_valid_attr_name
			    (const Description& p_attr_name_str) const;
    I_Attribute_Instance*		get_attr_inst_ptr
			    (const Description& p_attr_name_str);
    I_var*		get_attr_var_ptr
			    (const Description& p_attr_name_str);
    I_Object_Instance*	get_oinst_ptr ();
    void		set_oinst_ptr (I_Object_Instance* p_oinst_ptr);
    I_Object*		get_obj_ptr ();
    void		set_obj_ptr (I_Object* p_obj_ptr);

    static mc_dbms_List<I_object_inst_ref_var*> * get_extent();    // i2744.1.2

private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_object_inst_ref_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_object_inst_ref_str = p_value_str;
			}
    void		set_object_inst_ref_str ();
    virtual t_boolean	get_is_initialized () const
			{
			    return ((m_obj_ptr == 0) &&
				(m_last_resort_key_letters == Description::Default))
				    ? FALSE : TRUE;
			}
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return OBJECT_INST_REF_DATATYPE;
			}
    virtual GS_string get_core_data_type_str () const
			{
			    return "inst_ref<Object>";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_inst_ref_string;
			}
    virtual I_object_inst_ref_var*
			get_object_inst_ref_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
			
		bytesWritten += I_var::persist();

		// Write a flag to indicate if the pointer is null or not
		bytesWritten += m_obj_ptr ? writeLong(0) : writeLong(1);
		if (m_obj_ptr) {
			bytesWritten += InstanceTracker::Instance::persist((char*)m_obj_ptr);
		}
		
		// Write a flag to indicate if the pointer is null or not
		bytesWritten += m_oinst_ptr ? writeLong(0) : writeLong(1);	
		if (m_oinst_ptr) {
			bytesWritten += InstanceTracker::Instance::persist((char*)m_oinst_ptr);
		}
		
		m_last_resort_key_letters.persist();
		m_object_inst_ref_str.persist();

		// Write a flag to indicate if the pointer is null or not
		bytesWritten += m_extent_coll ? writeLong(0) : writeLong(1);	
		if (m_extent_coll) {
			bytesWritten += InstanceTracker::Instance::persist((char*)m_extent_coll);
		}
				
		return bytesWritten;
	}
	
	virtual void restore() {
		
		I_var::restore();
		
		long ptrIsNull = readLong();	
		if ( !ptrIsNull ) {
			m_obj_ptr = (I_Object*)InstanceTracker::Instance::create()->m_block;
		}
		
		ptrIsNull = readLong();	
		if ( !ptrIsNull ) {
			m_oinst_ptr = (I_Object_Instance*)InstanceTracker::Instance::create()->m_block;
		}
		
		m_last_resort_key_letters.restore();
		m_object_inst_ref_str.restore();

		ptrIsNull = readLong();	
		if ( !ptrIsNull ) {
			m_extent_coll = (mc_dbms_List<I_object_inst_ref_var*> *)InstanceTracker::Instance::create()->m_block;
		}
	}

	static char* create() {
		I_object_inst_ref_var* inst = new I_object_inst_ref_var(true);
		inst->restore();
		return (char*)inst;
	}

private:
	
    I_Object*		m_obj_ptr;
    I_Object_Instance*	m_oinst_ptr;
    Description		m_last_resort_key_letters;
    Description		m_object_inst_ref_str;
    static mc_dbms_List<I_object_inst_ref_var*> *m_extent_coll;      // i2744.1.1
};


class GS_select;
class I_object_inst_ref_set_var : public I_var
{
friend P_checkGenDB;
friend SIM_SOR;
friend GS_select;
friend I_object_inst_ref_var;

public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_object_inst_ref_set_var (bool isRestoring = false);
			I_object_inst_ref_set_var
			    (const I_object_inst_ref_set_var& );
    I_object_inst_ref_set_var&
			operator = (const I_object_inst_ref_set_var&);
    virtual		~I_object_inst_ref_set_var ()
			{
			operator delete( this, ""); // Remove from InstanceTracker
			}


			I_object_inst_ref_set_var (const I_object_inst_ref_var*
			    p_object_inst_ref_var_ptr );
			I_object_inst_ref_set_var (I_object_inst_ref_set_var*
			    p_object_inst_ref_set_var_ptr );
			I_object_inst_ref_set_var
			    (const I_object_inst_ref_var*
				p_object_inst_ref_var1_ptr,
			    const I_object_inst_ref_var*
				p_object_inst_ref_var2_ptr,
			    const GS_string& p_binary_op_str );
			I_object_inst_ref_set_var
			    (const I_object_inst_ref_var*
				p_object_inst_ref_var1_ptr,
			    const I_object_inst_ref_set_var*
				p_object_inst_ref_set_var2_ptr,
			    const GS_string& p_binary_op_str );
			I_object_inst_ref_set_var
			    (const I_object_inst_ref_set_var*
				p_object_inst_ref_set_var1_ptr,
			    const I_object_inst_ref_var*
				p_object_inst_ref_var2_ptr,
			    const GS_string& p_binary_op_str );
			I_object_inst_ref_set_var
			    (const I_object_inst_ref_set_var*
				p_object_inst_ref_set_var1_ptr,
			    const I_object_inst_ref_set_var*
				p_object_inst_ref_set_var2_ptr,
			    const GS_string& p_binary_op_str );
			I_object_inst_ref_set_var
			    (I_Object* p_obj_ptr,
			    const mc_dbms_List <I_Object_Instance*>*
				p_oinst_coll_ptr );


    Description	get_key_letters_str () const;
    void		set_last_resort_key_letters_str (const Description& p_str)
			    { m_last_resort_key_letters = p_str; }
    t_uint		cardinality 	() const;
    t_uint		cursor		() const;
    void		first		();
    void		next		();
    t_boolean		is_empty	() const;
    t_boolean		is_first	() const;
    t_boolean		is_last		() const;
    t_boolean		is_done		() const;
    I_Object_Instance*	get_oinst_ptr ();
    I_Object*		get_obj_ptr ();


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_object_inst_ref_set_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_object_inst_ref_set_str = p_value_str;
			}
    void		set_object_inst_ref_set_str ();
    virtual t_boolean	get_is_initialized () const
			{
			    return ((m_obj_ptr == 0) &&
				(m_last_resort_key_letters == Description::Default))
				    ? FALSE : TRUE;
			}
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return OBJECT_INST_REF_SET_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "inst_ref_set<Object>";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_inst_ref_set_string;
			}
    virtual I_object_inst_ref_set_var*
			get_object_inst_ref_set_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;

		bytesWritten += I_var::persist();
		
		bytesWritten += writeBlob((char*)&m_cursor, sizeof(t_uint));
			
		// Write a flag to indicate if the pointer is null or not
		bytesWritten += m_obj_ptr ? writeLong(0) : writeLong(1);	
		if (m_obj_ptr) {
			bytesWritten += InstanceTracker::Instance::persist((char*)m_obj_ptr);
		}
				
		bytesWritten += m_oinst_coll.persist();

		bytesWritten += m_last_resort_key_letters.persist();
		bytesWritten += m_object_inst_ref_set_str.persist();

		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		
		readBlob((char*)&m_cursor);
		
		long ptrIsNull = readLong();	
		if ( !ptrIsNull ) {
			m_obj_ptr = (I_Object*)InstanceTracker::Instance::create()->m_block;
		}
		
		m_oinst_coll.restore();

		m_last_resort_key_letters.restore();
		m_object_inst_ref_set_str.restore();

	}

	static char* create() {
		I_object_inst_ref_set_var* inst = new I_object_inst_ref_set_var(true);
		inst->restore();
		return (char*)inst;
	}

private:

    t_uint		m_cursor;
    I_Object*		m_obj_ptr;
    mc_dbms_List<I_Object_Instance*>	m_oinst_coll;
    Description		m_last_resort_key_letters;
    Description		m_object_inst_ref_set_str;
};


class I_event_inst_var : public I_var
{
friend SIM_SOR;

public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_event_inst_var (bool isRestoring = false);
			I_event_inst_var
			    (const I_event_inst_var& p_event_inst_var );
    I_event_inst_var&	operator= (const I_event_inst_var& p_event_inst_var);
    virtual		~I_event_inst_var ();


    I_SM_Evt_Inst*	get_einst_ptr ();
    const Id&		get_einst_id ()
			{
			    return m_einst_id;
			}
    void		set_einst_id (const Id& p_einst_id);


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_event_inst_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_event_inst_str = p_value_str;
			}
    void		set_event_inst_str ();
    virtual t_boolean	get_is_initialized () const
			{
			    return (m_einst_id == Id::Default)
				? FALSE : TRUE;
			}
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return EVENT_INST_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "inst<Event>";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_inst_event_string;
			}
    virtual I_event_inst_var*
			get_event_inst_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += writeBlob((char*)&m_einst_id, sizeof(Id));
		bytesWritten += m_event_inst_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		readBlob((char*)&m_einst_id);
		m_event_inst_str.restore();
	}
	
	static char* create() {
		I_event_inst_var* inst = new I_event_inst_var(true);
		inst->restore();
		return (char*)inst;
	}
	
private:
    Id			m_einst_id;
    Description		m_event_inst_str;
};


class I_mapping_inst_var : public I_var
{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_mapping_inst_var (bool isRestoring = false);
			I_mapping_inst_var (const I_mapping_inst_var& p_var )
			{
			    m_tracking_value = p_var.m_tracking_value;
			    set_mapping_inst_str ();
			}
    I_mapping_inst_var&	operator= (const I_mapping_inst_var& p_var)
			{
			    m_tracking_value = p_var.m_tracking_value;
			    set_mapping_inst_str ();
			    return *this;
			}
    virtual             ~I_mapping_inst_var ()
			{
			operator delete( this, ""); // Remove from InstanceTracker
			}

			I_mapping_inst_var (int p_tracking_value)
			{
			    m_tracking_value = p_tracking_value;
			    set_mapping_inst_str ();
			}

    t_boolean		operator<  (const I_mapping_inst_var&) const;
    t_boolean		operator<= (const I_mapping_inst_var&) const;
    t_boolean		operator>= (const I_mapping_inst_var&) const;
    t_boolean		operator>  (const I_mapping_inst_var&) const;


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_mapping_inst_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_mapping_inst_str = p_value_str;
			}
    void		set_mapping_inst_str ();
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return MAPPING_INST_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "inst<Mapping>";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_inst_mapping_string;
			}
    virtual I_mapping_inst_var*
			get_mapping_inst_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += writeLong(m_tracking_value);
		bytesWritten += m_mapping_inst_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		m_tracking_value = readLong();
		m_mapping_inst_str.restore();
	}
	
	static char* create() {
		I_mapping_inst_var* inst = new I_mapping_inst_var(true);
		inst->restore();
		return (char*)inst;
	}

private:
    int			m_tracking_value;
    Description		m_mapping_inst_str;
};


class I_mapping_inst_ref_var : public I_var
{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_mapping_inst_ref_var (bool isRestoring = false);
			I_mapping_inst_ref_var
			    (const I_mapping_inst_ref_var& p_var )
			{
			    m_tracking_value = p_var.m_tracking_value;
			    set_mapping_inst_ref_str ();
			}
    I_mapping_inst_ref_var&
			operator= (const I_mapping_inst_ref_var& p_var)
			{
			    m_tracking_value = p_var.m_tracking_value;
			    set_mapping_inst_ref_str ();
			    return *this;
			}
    virtual             ~I_mapping_inst_ref_var ()
			{
			operator delete( this, ""); // Remove from InstanceTracker
			}

			I_mapping_inst_ref_var (int p_tracking_value)
			{
			    m_tracking_value = p_tracking_value;
			    set_mapping_inst_ref_str ();
			}


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_mapping_inst_ref_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_mapping_inst_ref_str = p_value_str;
			}
    void		set_mapping_inst_ref_str ();
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return MAPPING_INST_REF_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "inst_ref<Mapping>";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_inst_ref_mapping_string;
			}
    virtual I_mapping_inst_ref_var*
			get_mapping_inst_ref_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += writeLong(m_tracking_value);
		bytesWritten += m_mapping_inst_ref_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		m_tracking_value = readLong();
		m_mapping_inst_ref_str.restore();
	}
	
	static char* create() {
		I_mapping_inst_ref_var* inst = new I_mapping_inst_ref_var(true);
		inst->restore();
		return (char*)inst;
	}

private:
    int			m_tracking_value;
    Description		m_mapping_inst_ref_str;
};


class I_date_var : public I_var
{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

	I_date_var (bool isRestoring = false);
	I_date_var (const I_date_var& p_var );
    I_date_var&		operator= (const I_date_var& p_var);
    virtual		~I_date_var ();


    void		set_to_current_date ();
    void		set_to_un_initialized ();

    t_int		get_second ();
    void		set_second (t_int p_second);
    t_int		get_minute ();
    void		set_minute (t_int p_minute);
    t_int		get_hour ();
    void		set_hour (t_int p_hour);
    t_int		get_day ();
    void		set_day (t_int p_day);
    t_int		get_month ();
    void		set_month (t_int p_month);
    t_int		get_year ();
    void		set_year (t_int p_year);

    t_boolean		operator<  (const I_date_var&) const;
    t_boolean		operator<= (const I_date_var&) const;
    t_boolean		operator>= (const I_date_var&) const;
    t_boolean		operator>  (const I_date_var&) const;


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_date_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_date_str = p_value_str;
			}
    void		set_date_str ();
    virtual t_boolean	get_is_initialized () const;
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return MAPPING_INST_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "inst<Mapping>";
			}
    virtual t_user_data_type
			get_user_data_type () const
			{
			    return DATE_USERDATATYPE;
			}
    virtual Description&	get_user_data_type_str () const
			{
			    return lc_date_string;
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_date_string;
			}
    virtual I_date_var*	get_date_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
        
		bytesWritten += I_var::persist();

        // This Galaxy date has a couple of embedded pointers that we can't
        // persist.  Fortunatly, we don't seem to need them (when we recreate a
        // new object we'll use the new pointers.
        int numBytesToSerialize = sizeof(vdate) - sizeof(vloadable) - sizeof(vchar*);
        char* startingPosition = ((char*)&m_date) + sizeof(vloadable); 
		bytesWritten += writeBlob(startingPosition, numBytesToSerialize);
     
		bytesWritten += m_date_str.persist();
				
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
        char* startingPosition = ((char*)&m_date) + sizeof(vloadable); 
		readBlob((char*)&startingPosition);
		m_date_str.restore();
	}
	
	static char* create() {
		I_date_var* inst = new I_date_var(true);
		inst->restore();
		return (char*)inst;
	}

private:

    vdate		m_date;
    Description		m_date_str;
};


class I_timestamp_var : public I_var
{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_timestamp_var (bool isRestoring = false);
			I_timestamp_var
			    (const I_timestamp_var& p_timestamp_var);
    I_timestamp_var&	operator= (const I_timestamp_var& p_timestamp_var);
    virtual		~I_timestamp_var ();


			I_timestamp_var
			    (t_ulong p_second, t_ulong p_microsecond);

    t_ulong		get_microsecond () { return m_microsecond; }
    t_ulong		get_millisecond () { return m_microsecond / 1000; }
    t_ulong		get_second () { return m_second; }
    t_ulong		get_minute () { return m_second / 60; }
    t_ulong		get_hour () { return m_second / 3600; }

    void		set_microsecond (t_ulong p_microsecond);
    void		set_second (t_ulong p_second);
    void		reset ();
			    

    I_timestamp_var&	operator-= (const I_timestamp_var& p_time);
    I_timestamp_var&	operator+= (t_ulong p_microseconds);
    t_boolean		operator<  (const I_timestamp_var&) const;
    t_boolean		operator<= (const I_timestamp_var&) const;
    t_boolean		operator>= (const I_timestamp_var&) const;
    t_boolean		operator>  (const I_timestamp_var&) const;

    virtual t_boolean	operator== (const I_var& p_var) const;

private:
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_timestamp_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_timestamp_str = p_value_str;
			}
    void		set_timestamp_str ();
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return MAPPING_INST_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "inst<Mapping>";
			}
    virtual t_user_data_type
			get_user_data_type () const
			{
			    return TIMESTAMP_USERDATATYPE;
			}
    virtual Description&	get_user_data_type_str () const
			{
			    return lc_timestamp_string;
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_timestamp_string;
			}
    virtual I_timestamp_var*
			get_timestamp_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += writeLong(m_second);
		bytesWritten += writeLong(m_microsecond);
		bytesWritten += m_timestamp_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		m_second = readLong();
		m_microsecond = readLong();
		m_timestamp_str.restore();
	}
	
	static char* create() {
		I_timestamp_var* inst = new I_timestamp_var(true);
		inst->restore();
		return (char*)inst;
	}

private:
    t_ulong		m_second;
    t_ulong		m_microsecond;
    Description		m_timestamp_str;
};


class I_timer_inst_ref_var : public I_var
{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_timer_inst_ref_var (bool isRestoring = false)
			{
				if (!isRestoring) {
				    set_einst_id (Id::Default);
				}
			}
			I_timer_inst_ref_var
			    (const I_timer_inst_ref_var& p_timer_inst_ref_var )
			{
			    set_einst_id (((I_timer_inst_ref_var&)
				p_timer_inst_ref_var).get_einst_id ());
			}
    I_timer_inst_ref_var&
			operator=
			    (const I_timer_inst_ref_var& p_timer_inst_ref_var)
			{
			    set_einst_id (((I_timer_inst_ref_var&)
				p_timer_inst_ref_var).get_einst_id ());
			    return *this;
			}
    virtual		~I_timer_inst_ref_var ();


			I_timer_inst_ref_var (const Id& p_einst_id)
			{
			    set_einst_id (p_einst_id);
			}
    I_SM_Evt_Inst*	get_einst_ptr ();
    const Id&		get_einst_id ()
			{
			    return m_einst_id;
			}
    void		set_einst_id (const Id& p_einst_id);


private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const
			{
			    return m_timer_inst_ref_str;
			}
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_timer_inst_ref_str = p_value_str;
			}
    void		set_timer_inst_ref_str ();
    virtual t_boolean	get_is_initialized () const
			{
			    return (m_einst_id == Id::Default)
				? FALSE : TRUE;
			}
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return MAPPING_INST_REF_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "inst_ref<Mapping>";
			}
    virtual t_user_data_type
			get_user_data_type () const
			{
			    return TIMER_INST_REF_USERDATATYPE;
			}
    virtual Description&	get_user_data_type_str () const
			{
			    return lc_inst_ref_timer_string;
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_inst_ref_timer_string;
			}
    virtual I_timer_inst_ref_var*
			get_timer_inst_ref_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;
		
		bytesWritten += I_var::persist();
		bytesWritten += writeBlob((char*)&m_einst_id, sizeof(Id));
		bytesWritten += m_timer_inst_ref_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		readBlob((char*)&m_einst_id);
		m_timer_inst_ref_str.restore();
	}
	
	static char* create() {
		I_timer_inst_ref_var* inst = new I_timer_inst_ref_var(true);
		inst->restore();
		return (char*)inst;
	}

private:
    Id			m_einst_id;
    Description		m_timer_inst_ref_str;
};


class I_frag_ref_var : public I_var
{
public:
    static mc_dbms_typespec*	get_mc_dbms_typespec ();

			I_frag_ref_var (bool isRestoring = false);
			I_frag_ref_var (const I_frag_ref_var& );
    I_frag_ref_var&	operator= (const I_frag_ref_var&);
    virtual		~I_frag_ref_var ();

    void		append_to_body (const Description& p_str);

    void		add_attr (const Description& p_attr_name_str,
			    I_var* p_var_ptr);
    t_boolean		is_valid_attr_name
			    (const Description& p_attr_name_str) const;
    I_var*		get_attr_var_ptr
			    (const Description& p_attr_name_str);
    t_boolean		replace_attr_var_ptr
			    (const Description& p_attr_name_str,
			    const I_var* p_var_ptr);
    void		clear_attrs (t_boolean p_keep_body_var = FALSE);



private:
    virtual t_boolean	operator== (const I_var& p_var) const;
    virtual t_boolean	reassign (const I_var* p_var_ptr);
    virtual I_var*	clone_to_transient () const;
    virtual I_var*	clone_to_persistent () const;
    virtual const Description&
			get_value_str () const;
    virtual void	override_value_str (const Description& p_value_str)
			{
			    m_fragment_str = p_value_str;
			}
    void		set_fragment_str ();
    virtual t_core_data_type
			get_core_data_type () const
			{
			    return FRAGMENT_DATATYPE;
			}
    virtual GS_string	get_core_data_type_str () const
			{
			    return "fragment";
			}
    virtual Description&	get_data_type_str () const
			{
			    return lc_fragment_string;
			}
    virtual I_frag_ref_var* get_frag_ref_var_ptr ()
			{
			    return this;
			}

public:

	virtual long persist() {
		long bytesWritten = 0;

		bytesWritten += I_var::persist();
		bytesWritten += m_attr_name_str_coll.persist();
		bytesWritten += m_attr_var_coll.persist();
		bytesWritten += m_fragment_str.persist();
	
		return bytesWritten;
	}
	
	virtual void restore() {
		I_var::restore();
		m_attr_name_str_coll.restore();
		m_attr_var_coll.restore();
		m_fragment_str.restore();
	}
	
	static char* create() {
		I_frag_ref_var* inst = new I_frag_ref_var(true);
		inst->restore();
		return (char*)inst;
	}

private:
    mc_dbms_List <String*>	m_attr_name_str_coll;
    mc_dbms_List <I_var*>	m_attr_var_coll;
    Description		m_fragment_str;
};

#endif