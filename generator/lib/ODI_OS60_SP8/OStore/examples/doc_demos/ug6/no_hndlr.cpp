// no_hndlr.cpp: Uses a handler-less TIX exception handler
// to handle exception signaled if one or both databases
// specified on command line do not exist
#include <ostore/ostore.hh> 
#include <fstream.h> 

int main(int argc, char** argv)
{
	OS_ESTABLISH_FAULT_HANDLER {
		if(argc!=3) { // check for name of database
			cout << "Usage:  " << argv[0]  << " <db1> <db2>\n";
			return 1;
		}

		objectstore::initialize();
		// set both pointers to 0 so we can later see if open() was successful
		os_database *db1 = 0, *db2 = 0; 
		TIX_HANDLE (err_database_not_found) { 
			db1 = os_database::open(argv[1]); // open first db
		} TIX_EXCEPTION {
			// no handler code
		} TIX_END_HANDLE 
		TIX_HANDLE (err_database_not_found) { 
			db2 = os_database::open(argv[2]); // open second db
		} TIX_EXCEPTION {
			// no handler code
		} TIX_END_HANDLE 
		// check if files were opened; null means the open failed 
		if (!db1 || !db2) { 
			cout << "Cannot open "; 
			if (db2) 
				cout << argv[1];  // failed to open first db
			else if (db1) 
				cout << argv[2];  // failed to open second db 
			else  // couldn't open either one
				cout << argv[1] << " or " << argv[2];
			cout << endl;
			return 1; 
		} 
		else  // both databases exist
			cout << "Opened " << argv[1] << " and " << argv[2] << endl;

		objectstore::shutdown();

	} OS_END_FAULT_HANDLER
	return 0;
}

