/*========================================================================
 *
 * File:      $RCSfile: s_simref.hh,v $
 * Version:   $Revision: 1.9 $
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

#ifndef SIM_REF_HH
#define SIM_REF_HH


#include <u_string.hh>

#include <i_obj.hh>

#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#else
#include <u_typdef.hh>
#endif


// Declare all classes defined in this file here so that they may be
// referenced before they are defined (ie - a forward reference such as a
// pointer to a class not yet defined). This also gives the user a quick
// glance at what classes reside in this file.

class Sim_ref;

// Also declare classes in other subsystem that we reference, but don't
// include header file.


//
// CLASS: Sim_reference
//
// DESCRIPTION: Instances of this class are used to uniquely identify a
//	simulation instance within a given Sinvocation.
//
// REMARKS: It is important to note that instances of this class should
//	be transient for a given Invocation only. There is NO need for instances
//	of this class to be persistent. We can navigate to the persistent
//	I_Object instance in a given database simply via the mc_dbms_database
//	pointer and the I_OBJECT database root). 
//

class Sim_reference
	{
	public:
		// IMPLEMENTOR functions

		// ACCESS functions.

		// When we create/open SIM databases, we will add them to our collection
		// of MC_DBMS references to simulation instances, each of which resides in
		// a different database. The "create_database" function will create
		// the new Sim_ref instance.
		//
		// The following is the full entire pathname of the SIM database
		// file to be created/opened. It must begin with a "/".

		static mc_dbms_database *create_database(
			const char *p_sim_db_full_pathname, GS_string &p_err_msg );

		static mc_dbms_database *open_database(
			const char *p_sim_db_full_pathname, GS_string &p_err_msg );

		static t_boolean extract_names_from_path_ok( const char *p_sim_db_full_pathname,
			String &p_directory, String &p_file, String &p_domain,
			GS_string &p_err_msg );
		mc_dbms_database *get_db_ptr() const { return db_ptr; }
		mc_dbms_List< I_Object * > *get_i_object_coll_ptr()
			{ return i_object_coll_ptr; }

                String &sim_name() { return simulation_name; }
                const char *get_sim_name_char_ptr() const
                        { return simulation_name.char_ptr(); }
 
                String &sim_directory_name() { return directory; }
                const char *get_sim_directory_name_char_ptr() const
                        { return directory.char_ptr(); }

                String &sim_file_name() { return filename; }
                const char *get_sim_file_name_char_ptr() const
                        { return filename.char_ptr(); }

		~Sim_reference();

	private:

		// MANAGER functions

		Sim_reference( mc_dbms_database *p_db_ptr, const char *p_directory,
                        const char *p_file, const char *p_domain );


		mc_dbms_database *db_ptr;
		mc_dbms_List< I_Object * > *i_object_coll_ptr;
		
		String	simulation_name;
		String	filename;
		String	directory;

		// HELPING functions.
	};


#endif 
