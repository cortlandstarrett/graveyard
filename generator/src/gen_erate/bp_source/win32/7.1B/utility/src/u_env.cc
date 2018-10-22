/*========================================================================
 *
 * File:      $RCSfile: u_env.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:59 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <vpref.h>
#include <vname.h>
#include <vchar.h>
#include <vnum.h>
#include <vfs.h>

#include <stdlib.h>

#include <u_string.hh>
#include <u_env.hh>
#include <u_trace.hh>
#include <u_error.hh>
#include <u_cursor.hh>
#include <u_userid.hh>
#include <u_tempdir.hh>

char default_print_file [256];

t_uint U_environment::_debug_value = 0;
t_uint U_environment::_audit_sm_value = 0;
t_uint U_environment::_render_oval_as_rect = 0;
t_uint U_environment::_meter_value = 0;
t_uint U_environment::_monochrome_value = 0;

String U_environment::_home_dir_string;
String U_environment::_ooa_dir_string;
String U_environment::_sql_dir_string;
String U_environment::_prop_file_string;
String U_environment::_user_name_string;
String U_environment::_temp_dir_path_string;
String U_environment::_installation_dir_string;
String U_environment::_installation_sql_dir_string;



//  Declare the collection of all instances of U_env_var.  This is
//  a collection in transient memory.
//
mc_dbms_Set<U_env_var*> *U_env_var::get_env_var_collection_ptr()
{
  static mc_dbms_Set<U_env_var*> *s_env_var_collection_ptr = 0;

  if (! s_env_var_collection_ptr)
    {
      s_env_var_collection_ptr = &mc_dbms_Set<U_env_var*>::create
          (mc_dbms_database::get_transient_database ());
    }
  return s_env_var_collection_ptr;
}


void
U_environment::init ()

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin U_environment::init ()."));

	_home_dir_string = "";
	_ooa_dir_string = "";
	_sql_dir_string = "";
	_prop_file_string = "";
	_user_name_string = "";
	
    _installation_sql_dir_string="";
    _installation_dir_string="";	

    // Do this first, so that temp files we create later are
	// created in the right place.
	_temp_dir_path_string = String(U_get_temp_dir());


    // Call Galaxy function to read current environment and write them back
    // into the preferences dictionary.
    //
    vprefReadEnvironment ();
    char environment_string [4096];
    vprefDict* prefdict_ptr = vprefGetRootDict ();


    const vchar* char_ptr = vprefDictLoad (prefdict_ptr,
	vnameInternGlobalLiteral ("PT_DEBUG"));
    if (char_ptr != 0)
    {
	_debug_value = vnumParseUInt (char_ptr, 0);
    }
    else
    {
	_debug_value = 0;
    }
    LOG_TRACE (L_D_DATA, L_FUNCTION_STEP_LO, (L_log_string,
	"U_environment::init ():  _debug_value = %d",
	_debug_value));


    char_ptr = vprefDictLoad (prefdict_ptr,
	vnameInternGlobalLiteral ("PT_AUDIT_SM"));
    if (char_ptr != 0)
    {
	_audit_sm_value = vnumParseUInt (char_ptr, 0);
    }
    else
    {
	_audit_sm_value = 1;
    }
    LOG_TRACE (L_D_DATA, L_FUNCTION_STEP_LO, (L_log_string,
	"U_environment::init ():  _audit_sm_value = %d",
	_audit_sm_value));


    char_ptr = vprefDictLoad (prefdict_ptr,
	vnameInternGlobalLiteral ("PT_RENDER_OVAL_AS_RECT"));
    if (char_ptr != 0)
    {
	_render_oval_as_rect = vnumParseUInt (char_ptr, 0);
    }
    else
    {
	_render_oval_as_rect = 0;
    }
    LOG_TRACE (L_D_DATA, L_FUNCTION_STEP_LO, (L_log_string,
	"U_environment::init ():  _render_oval_as_rect = %d",
	_render_oval_as_rect));


    char_ptr = vprefDictLoad (prefdict_ptr,
	vnameInternGlobalLiteral ("PT_MONOCHROME"));
    if (char_ptr != 0)
    {
	_monochrome_value = vnumParseUInt (char_ptr, 0);
    }
    else
    {
	_monochrome_value = 0;
    }
    LOG_TRACE (L_D_DATA, L_FUNCTION_STEP_LO, (L_log_string,
	"U_environment::init ():  _monochrome_value = %d",
	_monochrome_value));


    char_ptr = vprefDictLoad (prefdict_ptr,
	vnameInternGlobalLiteral ("HOME"));
    if (char_ptr != 0)
    {
	vcharExport (vcharScribeSystemExport (char_ptr), environment_string);
	_home_dir_string = environment_string;
    }
    else
    {
	_home_dir_string = ".";
    }
    LOG_TRACE (L_D_DATA, L_FUNCTION_STEP_LO, (L_log_string,
	"U_environment::init ():  _home_dir_string = %S",
	vcharScribeASCII(_home_dir_string.char_ptr ()) ));


    char_ptr = vprefDictLoad (prefdict_ptr,
	vnameInternGlobalLiteral ("PT_OOA_DIR"));
    if (char_ptr != 0)
    {
	vcharExport (vcharScribeSystemExport (char_ptr), environment_string);
	_ooa_dir_string = environment_string;
    }
    else
    {
	_ooa_dir_string = ".";
    }
    LOG_TRACE (L_D_DATA, L_FUNCTION_STEP_LO, (L_log_string,
	"U_environment::init ():  _ooa_dir_string = %S",
	vcharScribeASCII(_ooa_dir_string.char_ptr ()) ));

    _prop_file_string = _home_dir_string;

    _prop_file_string += PATH_DELIM_STR ".bridgepoint";

    _user_name_string = get_userid();

	String temp_name = U_environment::get_temp_dir() + "ptXXXXXX";
    vchar* generated_name
	= vstrCloneScribed (vcharScribeLiteral (temp_name.char_ptr()));
    vfsPath * path_ptr = vfsPathFromStr (vfsGenerateTempName (generated_name));
    while (vfsAccess (path_ptr, vfsFILE_EXISTS))
    {
	vfsDestroyPath (path_ptr);
	vstrDestroy (generated_name);

	generated_name
	    = vstrCloneScribed (vcharScribeLiteral (temp_name.char_ptr()));
	path_ptr = vfsPathFromStr (vfsGenerateTempName (generated_name));
    }


    //  Set up the USER_FILE for printing in order to allow the
    //    'F3' button to be pushed at any time.
    //
    default_print_file [0] = '\0';
    char default_user_file [256];
    default_user_file [0] = '\0';
    vcharExport (vcharScribeSystemExport (generated_name), default_user_file);
    strcpy (default_print_file, "USER_FILE=");
    strcat (default_print_file, default_user_file);
    putenv (default_print_file);

    //setup installation directories
#ifdef WIN32  
    _installation_dir_string=U_env_var::get_value_str("PT_HOME_DRIVE");
#endif    
    _installation_dir_string+=U_env_var::get_value_str("PT_HOME");
    _installation_dir_string+=PATH_DELIM_STR;
    
    _installation_sql_dir_string=_installation_dir_string;
	_installation_sql_dir_string+="sql_dir";
    _installation_sql_dir_string+=PATH_DELIM_STR;
	_installation_sql_dir_string+="templates";
    _installation_sql_dir_string+=PATH_DELIM_STR;
     
    char_ptr = vprefDictLoad (prefdict_ptr,
	vnameInternGlobalLiteral ("PT_SQL_DIR"));
    if (char_ptr != 0 && vcharLength(char_ptr) > 0 )
    {
	vcharExport (vcharScribeSystemExport (char_ptr), environment_string);
	_sql_dir_string = environment_string;
    }
    else
    {
	_sql_dir_string = _installation_dir_string;
    _sql_dir_string += "sql_dir";
    }

    LOG_TRACE (L_D_DATA, L_FUNCTION_STEP_LO, (L_log_string,
	"U_environment::init ():  _sql_dir_string = %S",
	vcharScribeASCII(_sql_dir_string.char_ptr ()) ));

       
    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End U_environment::init ()."));
}





String
U_env_var::get_value_str (const String& p_name_str)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin U_env_var::get_value_str (p_name_str=\"%S\").",
	vcharScribeASCII(p_name_str.char_ptr ()) ));


    char* system_value_char_ptr
	= getenv (((String&) p_name_str).char_ptr ());


    if (system_value_char_ptr)
    {
	LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	    "End U_env_var::get_value_str (system_value_char_ptr=0x%08x=\"%S\").",
	    system_value_char_ptr,
      vcharScribeASCII(system_value_char_ptr)));
    }
    else
    {
	LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	    "End U_env_var::get_value_str (system_value_char_ptr=0x%08x).",
	    system_value_char_ptr));
    }
    return system_value_char_ptr;
}





int
U_env_var::put_env_var (const String& p_entire_str)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin U_env_var::put_env_var (p_entire_str=\"%S\").",
	vcharScribeASCII(p_entire_str.char_ptr ()) ));
    

    GS_string entire_str (p_entire_str);
    GS_string name_str (entire_str.parse_token ('='));
    if (entire_str != '=')
    {
	LOG_ERROR ((L_log_string,
	    "End #1  U_env_var::put_env_var (p_entire_str=\"%S\"):  Malformed environment variable string.",
	    vcharScribeASCII(p_entire_str.char_ptr ()) ));
	return 1;
    }


    entire_str++;
    GS_string value_str (entire_str.parse_to_end ());


    int return_value = put_env_var
	(name_str.char_ptr (), value_str.char_ptr ());


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End U_env_var::put_env_var (return_value=%d).",
	return_value));
    return return_value;
}






int
U_env_var::put_env_var
    (const String& p_name_str, const String& p_value_str)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Begin U_env_var::put_env_var (p_name_str=\"%S\", p_value_str=\"%S\").",
	vcharScribeASCII(p_name_str.char_ptr ()),
  vcharScribeASCII(p_value_str.char_ptr ()) ));


    //  Search for the environment variable in the transient collection of
    //    environment variables.
    //
    U_env_var* found_env_var_ptr = 0;
    U_env_var* env_var_ptr = 0;
    FOR_ALL_ELEMENTS_SAFE
	(env_var_ptr,
	U_env_var,
	get_env_var_collection_ptr(),
	env_var_cursor)
    {
	if (env_var_ptr->m_name_str == p_name_str)
	{
	    found_env_var_ptr = env_var_ptr;

/********************
	    //  Sanity/Safety checks.  The first one checks to make sure that
	    //    the system is still using the 'entire_str' copy of the found
	    //    U_env_var instance.
	    //
	    char* system_value_char_ptr
		= getenv (found_env_var_ptr->m_name_str.char_ptr ());
	    if (! system_value_char_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "U_env_var::put_env_var (found_env_var_ptr->m_entire_str.char_ptr ()=0x%08x=\"%S\", system_value_char_ptr=0x0):  getenv () returned 0 for env var in Local Collection.",
		    found_env_var_ptr->m_entire_str.char_ptr (),
		    vcharScribeASCII(found_env_var_ptr->m_entire_str.char_ptr ()) ));

		//  Leak this variable into memory in case it is still
		//    somehow in use.  Remove it from the collection of
		//    U_env_var instances.
		//
		get_env_var_collection_ptr()->remove (found_env_var_ptr);
		found_env_var_ptr = 0;
	    }
	    else if ((((int) (found_env_var_ptr->m_entire_str.char_ptr ()))
		    + found_env_var_ptr->m_name_str.length () + 1)
		!= ((int) system_value_char_ptr))
	    {
		LOG_ERROR ((L_log_string,
		    "U_env_var::put_env_var (found_env_var_ptr->m_entire_str.char_ptr ()=0x%08x=\"%S\", system_value_char_ptr=0x%08x=\"%S\"):  System copy of env var no longer within Local Entire Copy.",
		    found_env_var_ptr->m_entire_str.char_ptr (),
		    vcharScribeASCII(found_env_var_ptr->m_entire_str.char_ptr ()),
		    system_value_char_ptr,
        vcharScribeASCII(system_value_char_ptr) ));

		//  Leak this variable into memory in case it is still
		//    somehow in use.  Remove it from the collection of
		//    U_env_var instances.
		//
		get_env_var_collection_ptr()->remove (found_env_var_ptr);
		found_env_var_ptr = 0;
	    }
	    else if (found_env_var_ptr->m_value_str != system_value_char_ptr)
	    {
		LOG_ERROR ((L_log_string,
		    "U_env_var::put_env_var (found_env_var_ptr->m_entire_str.char_ptr ()=0x%08x=\"%S\", system_value_char_ptr=0x%08x=\"%S\"):  Local copy of env var does not match system copy.",
		    found_env_var_ptr->m_entire_str.char_ptr (),
		    vcharScribeASCII(found_env_var_ptr->m_entire_str.char_ptr ()),
		    system_value_char_ptr,
        vcharScribeASCII(system_value_char_ptr) ));

		//  Leak this variable into memory in case it is still
		//    somehow in use.  Remove it from the collection of
		//    U_env_var instances.
		//
		get_env_var_collection_ptr()->remove (found_env_var_ptr);
		found_env_var_ptr = 0;
	    }
********************/
	}
    }


    if (! found_env_var_ptr)
    {
	found_env_var_ptr = new U_env_var ();
	get_env_var_collection_ptr()->insert (found_env_var_ptr);
    }


    strcpy( (char *)found_env_var_ptr->m_name_str.char_ptr(),
	p_name_str.char_ptr() );

    strcpy( (char *)found_env_var_ptr->m_value_str.char_ptr(),
	p_value_str.char_ptr() );

    String entire_str = found_env_var_ptr->m_name_str + "=" +
	found_env_var_ptr->m_value_str;
    strcpy( (char *)found_env_var_ptr->m_entire_str.char_ptr(),
	entire_str.char_ptr() );
    

    // NOTE: Must typecase to _non_const for Solaris.
    int return_value = putenv ((char*)found_env_var_ptr->m_entire_str.char_ptr());


    if (return_value != 0)
    {
	LOG_ERROR ((L_log_string,
	    "End #1  U_env_var::put_env_var (found_env_var_ptr->m_entire_str.char_ptr ()=0x%08x=\"%S\"):  _putenv () returned non-0:  errno=%d.",
	    found_env_var_ptr->m_entire_str.char_ptr (),
	    vcharScribeASCII(found_env_var_ptr->m_entire_str.char_ptr ()),
	    errno));

	//  Leak this variable into memory in case it is still
	//    somehow in use.  Remove it from the collection of
	//    U_env_var instances.
	//
	get_env_var_collection_ptr()->remove (found_env_var_ptr);
	found_env_var_ptr = 0;
	return 1;
    }


    //  Sanity/Safety checks.  The first one checks to make sure that
    //    the system is still using the 'entire_str' copy of the found
    //    U_env_var instance.
    //
/********************
    char* system_value_char_ptr
	= getenv (found_env_var_ptr->m_name_str.char_ptr ());
    if (! system_value_char_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #1  U_env_var::put_env_var (found_env_var_ptr->m_entire_str.char_ptr ()=0x%08x=\"%S\", system_value_char_ptr=0x0):  getenv () returned 0 right after _putenv ().",
	    found_env_var_ptr->m_entire_str.char_ptr (),
	    vcharScribeASCII(found_env_var_ptr->m_entire_str.char_ptr ()) ));

	//  Leak this variable into memory in case it is still
	//    somehow in use.  Remove it from the collection of
	//    U_env_var instances.
	//
	get_env_var_collection_ptr()->remove (found_env_var_ptr);
	found_env_var_ptr = 0;
	return 1;
    }
    else if ((((int) (found_env_var_ptr->m_entire_str.char_ptr ()))
	    + found_env_var_ptr->m_name_str.length () + 1)
	!= ((int) system_value_char_ptr))
    {
	LOG_ERROR ((L_log_string,
	    "End #2  U_env_var::put_env_var (found_env_var_ptr->m_entire_str.char_ptr ()=0x%08x=\"%S\", system_value_char_ptr=0x%08x=\"%S\"):  System copy of env var no longer within Local Entire Copy.",
	    found_env_var_ptr->m_entire_str.char_ptr (),
	    vcharScribeASCII(found_env_var_ptr->m_entire_str.char_ptr ()),
	    system_value_char_ptr,
      vcharScribeASCII(system_value_char_ptr) ));

	//  Leak this variable into memory in case it is still
	//    somehow in use.  Remove it from the collection of
	//    U_env_var instances.
	//
	get_env_var_collection_ptr()->remove (found_env_var_ptr);
	found_env_var_ptr = 0;
	return 1;
    }
    else if (found_env_var_ptr->m_value_str != system_value_char_ptr)
    {
	LOG_ERROR ((L_log_string,
	    "End #3  U_env_var::put_env_var (found_env_var_ptr->m_entire_str.char_ptr ()=0x%08x=\"%S\", system_value_char_ptr=0x%08x=\"%S\"):  Local copy of env var does not match system copy.",
	    found_env_var_ptr->m_entire_str.char_ptr (),
	    vcharScribeASCII(found_env_var_ptr->m_entire_str.char_ptr ()),
	    system_value_char_ptr,
      vcharScribeASCII(system_value_char_ptr) ));

	//  Leak this variable into memory in case it is still
	//    somehow in use.  Remove it from the collection of
	//    U_env_var instances.
	//
	get_env_var_collection_ptr()->remove (found_env_var_ptr);
	found_env_var_ptr = 0;
	return 1;
    }
********************/


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"End #4:  U_env_var::put_env_var (return_value=%d).",
	return_value));
    return return_value;
}
