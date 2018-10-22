// tix_nest.cpp: illustrates a nested TIX exception handler
// Program checks for one command-line argument; if missing,
// (null string), the innermost handler outputs usage message.
// If the argument is not an ObjectStore database, the middle
// handler reports that error. The outermost handler (the
// parent) calls the ObjectStore method tix_handler::get_report()
// to report any other exception.
#include <ostore/ostore.hh>
#include <fstream.h>
 
int
main(int argc, char **argv)
{
	objectstore::initialize();
	TIX_HANDLE (err_objectstore) { // parent exception
		// the next two exceptions are descended from err_objectstore
		TIX_HANDLE (err_database_not_found) { // bad name
			TIX_HANDLE (err_invalid_pathname)  { // no argument (null string)
				os_database* db = os_database::open(argv[1]);
				db->close();
				cout << "The database named " << argv[1] << " exists.\n";
			} TIX_EXCEPTION {
				cout << "Usage:  " << argv[0] << " <database name>\n";
			} TIX_END_HANDLE
		} TIX_EXCEPTION {
			cout << "Sorry, no such database. Try again.\n";
		} TIX_END_HANDLE
	} TIX_EXCEPTION {
		// get a full report on the exception
		cout << tix_handler::get_report();
	} TIX_END_HANDLE

	objectstore::shutdown();

	return 0;
}

