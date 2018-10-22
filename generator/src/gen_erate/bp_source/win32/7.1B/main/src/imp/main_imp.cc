/*========================================================================
 *
 * File:      $RCSfile: main_imp.cc,v $
 * Version:   $Revision: 1.13 $
 * Modified:  $Date: 2013/01/10 23:43:11 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>
#include <iostream.h>
#include <fstream.h>
#include <sstream>
#include <vdate.h>
#include <stdlib.h>
#include <gs_imp.hh>
#include <u_string.hh>
#include <gs_ui.hh>
#include <i_idb.hh>
#include <u_desc.hh>
#include <u_log.hh>
#include <u_trace.hh>
#include <u_mc_dbms.hh>
#include <string>

using namespace std;

// i3020.1 deleted

class mc_dbms_database;
extern mc_dbms_database* GS_gen_sim_db_ptr;
extern int GS_domain_code;
extern t_int s_number_of_errors;
extern GS_string gen_file_name_str;

::ifstream* getFilePointer(const string& sqlFileName );
void verifyDomainCode();

/**
 *	This is the revised gen_file main.  It was changed to make it easier to interface with the global gen_erate main.
 * 	It takes the regular argc and argv, like a normal main, along with some other parameters to make 
 *	
 * @param sqlFileName The name of the sql or xtuml file to process. 
 * @return A return value is 0 indicates success and anything else indicates failure.
 */ 
int gen_import_main(const string& sqlFileName)
{
    ::istream* ifstream_ptr = getFilePointer(sqlFileName);

	int return_value = 0;

	verifyDomainCode();

	// Process the file
	bool importSucceeded = GS_import::import_sql_file (ifstream_ptr);
	if (!ifstream_ptr) {
		delete ifstream_ptr;
	}	
	
	if ( !importSucceeded )
	{
		std::stringstream errMsg;
		errMsg << "Error Occurred During Import... (Number of Errors: " << s_number_of_errors << ")";
		throw std::runtime_error(errMsg.str());
	}

    return return_value;
}

::ifstream* getFilePointer(const string& sqlFileName )
{
	::ifstream* ifstream_ptr = 0;
	
    if ( sqlFileName.empty() )
    {
		//  SQL Filename not specified - therefore, need to get it from stdin.
		//
		ifstream_ptr = new ::ifstream (0);
		if (! ifstream_ptr)
		{   
		    string msg("\nERROR:  Could not Allocate memory to open stdin.\n");
		    throw runtime_error(msg);
		}
	
		if (! ifstream_ptr->good ())
		{   
		    string msg("\nERROR:  Could not open  stdin.\n");
		    throw runtime_error(msg);
		}
	
		GS_ui::set_name_str ("stdin");
    }
    else 
    {
		//  SQL file specified.
		//
	    // i3193, i3196 deleted
		ifstream_ptr = new ::ifstream;
		if (! ifstream_ptr)
		{  
			std::ostringstream msg; 
		    msg << "\nERROR:  Could not Allocate memory to open <data_file_name>:  "
			 	<< sqlFileName << endl;
			throw runtime_error(msg.str());
		}
	
		ifstream_ptr->open (sqlFileName.c_str(), ios::in);
		if (! ifstream_ptr->good ())
		{   
		    delete ifstream_ptr;
			std::ostringstream msg; 
		    msg << "\nERROR:  Could not open <data_file_name>:  "
			    << sqlFileName << endl;
			throw runtime_error(msg.str());
		}
	
		GS_ui::set_name_str ( GS_string(sqlFileName.c_str()) );
    }
    
    return ifstream_ptr;
}

void verifyDomainCode()
{
	// Verify that the domain code can be used in this database.
	// Note that we want to print (automatically) chosen domain code if
	// user didn't enter one (err_msg will contain this).

	int auto_chosen_domain_code = -1;
	String str_err_msg;
	if ( ! I_instance_db::domain_code_ok (GS_gen_sim_db_ptr, GS_domain_code,
		auto_chosen_domain_code, str_err_msg) )
	{
		std::ostringstream msg;
		msg << endl << str_err_msg.char_ptr () << endl << endl;
		throw runtime_error(msg.str());
	}
	else 
	{
		if ( GS_domain_code == -1 )
		{
			// Print chosen domain code and save it.
			cout << str_err_msg.char_ptr () << endl;
			GS_domain_code = auto_chosen_domain_code;
		}
		else if ( str_err_msg != "" )
		{
			// Print diagnostic note
			cout 	<< str_err_msg.char_ptr () << endl;
		}		
	}
}