/*========================================================================
 *
 * File:      $RCSfile: u_env.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:33 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_ENV_HH
#define U_ENV_HH


#include <u_string.hh>
#include <u_typdef.hh>




class U_environment

{
public:
    static void		init ();


    static t_uint	get_debug_value ()
			    { return _debug_value; }
    static t_uint	get_audit_sm_value ()
			    { return _audit_sm_value; }
    static t_uint	get_render_oval_as_rect ()
			    { return _render_oval_as_rect; }
    static t_uint	get_meter_value ()
			    { return _meter_value; }
    static t_uint	get_monochrome_value ()
			    { return _monochrome_value; }

    static String	get_home_dir ()
			    { return _home_dir_string; }
    static String	get_ooa_dir ()
			    { return _ooa_dir_string; }
    static String	get_sql_dir ()
			    { return _sql_dir_string; }
    static String	get_installation_dir_string ()
			    { return _installation_dir_string; }
    static String	get_installation_sql_dir_string ()
			    { return _installation_sql_dir_string; }

    static String	get_properties_file ()
			    { return _prop_file_string; }

    static String	get_user_name ()
			    { return _user_name_string; }

    static String	get_temp_dir ()
			    { return _temp_dir_path_string; }

private:
    static t_uint	_debug_value;
    static t_uint	_audit_sm_value;
    static t_uint	_render_oval_as_rect;
    static t_uint	_meter_value;
    static t_uint	_monochrome_value;

    static String	_home_dir_string;
    static String	_ooa_dir_string;
    static String	_sql_dir_string;
    static String	_installation_dir_string;
    static String	_installation_sql_dir_string;

    static String	_prop_file_string;

    static String	_user_name_string;

	static String   _temp_dir_path_string;
};





class U_env_var

{
public:
    static String	get_value_str (const String& p_name_str);
    static int		put_env_var (const String& p_entire_str);
    static int		put_env_var (const String& p_name_str,
				     const String& p_value_str);
    static mc_dbms_Set<U_env_var*> *get_env_var_collection_ptr();


private:
			U_env_var ()
			:
			m_name_str( 2048 ),
			m_value_str( 2048 ),
			m_entire_str( 2048 )
			{}

			~U_env_var () {}
    String		m_name_str;
    String		m_value_str;
    String		m_entire_str;
};




#endif
