// set_sk.cpp: illustrates how to set the application's schema key
// The program attempts to access the three databases created by
// change_sk.cc.  The first attempt is successful.  The second attempt
// causes an exception because the original schema key is still in effect.
// The exception is handled by a TIX exception handler, which sets
// the schema key for accessing the third database.  That access is
// successful.
#include <ostore/ostore.hh>
#include <iostream.h>

int main()
{
	const char *db_name[] = { "stuff1.db", "stuff2.db", 
			    "stuff3.db" };
	const char *root_name[] = { "root1", "root2", 
			      "root3" };
	os_database *db[3];
	int* two_ints;

	OS_ESTABLISH_FAULT_HANDLER {
		objectstore::initialize();
		OS_BEGIN_TXN(t1, 0, os_transaction::read_only) {
			// set the schema key for the first database
			objectstore::set_current_schema_key(1, 2);
			for (int i = 0; i < 3; i++) {
				db[i] = os_database::open(db_name[i]);
				TIX_HANDLE(err_schema_key) {
					two_ints =
						(int*)(db[i]->find_root(root_name[i]))->get_value();
					cout << "Contents of " << db_name[i] << ": ";
					cout << *two_ints << " and " << *(two_ints+1) << "\n\n";
				} TIX_EXCEPTION {
					// we get here only if the attempt to access the
					// database fails because of a schema key violation
					cout << tix_handler::get_report();
					// set the key for accessing the third database
					objectstore::set_current_schema_key(i*2+3, i*2+4);
					cout << "Continuing execution . . .\n\n";
				} TIX_END_HANDLE
				db[i]->close();
			}
		} OS_END_TXN(t1)

		objectstore::shutdown();

	} OS_END_FAULT_HANDLER
	return 0;
}
