/*========================================================================
 *
 * File:      $RCSfile: main_gen.cc,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:42:09 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#include <vdate.h>
#include <iostream.h>
#include <vstdio.h>
#include <vstdlib.h>
#include <gs_arch.hh>
#include <u_desc.hh>
#include <vtime.h>      // clock()
#include <u_typdef.hh>
#include <u_log.hh>
#include <string>

using namespace std;

class mc_dbms_database;
extern mc_dbms_database* GS_gen_sim_db_ptr;
extern t_int s_number_of_errors;
extern long num_populations;
extern GS_string gen_file_name_str;

/**
 * This is the revised gen_file main.  It was changed to make it easier to interface with the global gen_erate main.
 * 
 * @return A return value is 0 indicates success and anything else indicates failure.
 */
int gen_file_main (const string& archFileName)
{
    GS_string arc_file_name = archFileName.c_str();
    
    if ( !GS_archetype::test_open_arch_file (arc_file_name))
    {
        std::ostringstream strm;
        strm << endl
             << "Unable to open archetype file '"
             << arc_file_name.char_ptr () << "'." << endl
             << endl;
        throw std::runtime_error(strm.str());
    }
        
	int return_value = 0;

    const char* err_msg = 0;

	t_boolean error_occurred = TRUE;

	error_occurred = (! (GS_archetype::populate_archetype
		(arc_file_name, num_populations, "")));


	if (error_occurred)
	{
		std::stringstream errMsg;
		errMsg << "Error Occurred During File Generation... (Number of Errors: " << s_number_of_errors << ")";
		throw std::runtime_error(errMsg.str());
	}

    return return_value;
}