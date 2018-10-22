/*========================================================================
 *
 * File:      $RCSfile: dbdump_main.cpp,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:42:02 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
// Headers for Galaxy
#include <vstartup.h>
#include <vformat.h>

// Header that allows us to get a database open
#include <i_idb.hh>

#include <iostream.h>
#include <dbdump.h>

//  Declare a global variable to hold a pointer to the process name so that
//    a logfile of the appropriate name may be opened up for LOG_ERROR,
//    LOG_REPORT, and LOG_TRACE.
//
char* process_name_char_ptr = "dbdump";

int main (int argc, char* *argv)
{

	if ( argc != 2 )
	{
		cerr << "Usage: dbdump <database>" << endl;
		return 1;
	}

	keyword_init();
	String::Default = "";
    String default_feature;

    //  Initialize Galaxy...
    //
    vstartupMinimal (argc, argv);
    vformatStartup();
    
    const char* err_msg;

    bool load_ok = I_instance_db::open_database ("dump_gdb",
		argv[1], err_msg);

    if (! load_ok ) 
    {
    	cerr << endl;
		cerr << "ERROR:  Unable to Open Database - Error is:" << endl;
		cerr << err_msg << endl;
		cerr << endl;
		return 1;
    }
    else
	{
        dump_data();
    }
    
	return 0;
}

