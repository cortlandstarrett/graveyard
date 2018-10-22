// tix_example.cpp: illustrates a very simple TIX exception handler
// The program tries to open a database named on the command-line.
// If the open fails, the exception handler creates the database.
#include <ostore/ostore.hh>
#include <iostream.h>

int main(int argc, char** argv)
{
	OS_ESTABLISH_FAULT_HANDLER {
		objectstore::initialize();
		if (argc != 2) { // check for name of database
			cout << "Usage:  " << argv[0] << " <database>" << endl;
			return 1;
		}

		os_database *db;
		TIX_HANDLE(err_database_not_found) {
			db = os_database::open(argv[1]);
		} TIX_EXCEPTION {
			cout << "Can't open " << argv[1];
			cout << ", will create it." << endl;
			db = os_database::create(argv[1]);
		} TIX_END_HANDLE
		cout << "Opened " << db->get_pathname() << endl;
		db->close(); // close database
		objectstore::shutdown();
	} OS_END_FAULT_HANDLER
	return 0;
}

