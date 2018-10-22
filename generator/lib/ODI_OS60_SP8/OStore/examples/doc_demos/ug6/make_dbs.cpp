// make_dbs.cpp: Tries to open databases specified on
// command-line, and creates them if they don't exist.
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
		os_database* db1 = os_database::open(argv[1], 0, 0666);
		db1->close();
		os_database* db2 = os_database::open(argv[2], 0, 0666);
		db2->close();
		objectstore::shutdown();

	} OS_END_FAULT_HANDLER
	return 0;
}

