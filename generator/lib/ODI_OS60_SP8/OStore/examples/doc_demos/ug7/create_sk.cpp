// create_sk.cpp:  illustrates how to specify schema keys for databases
// The program creates three databases, writes a pair of integers
// to each, and specifies a schema key for each database. The values
// of the keys are the same as the values written to the database.
#include <ostore/ostore.hh>
#include <iostream.h>

int main()
{
	const char *db_name[] = { "stuff1.db", "stuff2.db", 
			    "stuff3.db" };
	const char *root_name[] = { "root1", "root2", 
			      "root3" };
	os_database *db[3];
	os_database_root* root;

	OS_ESTABLISH_FAULT_HANDLER {
		objectstore::initialize();
		OS_BEGIN_TXN(t1, 0, os_transaction::update) {
			for (int i = 0; i < 3; i++) {
				// create the database, overwriting it if it exists
				db[i] = os_database::create(db_name[i], 0644, 1);
				// specify the schema key for this database
				db[i]->change_schema_key(0, 0, i*2+1, i*2+2);
				cout << "Storing two integers in " << db_name[i];
				// create database root
				root = db[i]->create_root(root_name[i]);
				// allocate storage for an integer array of 2 elements
				// and associate the array with the database root
				int* two_ints = new (db[i], os_typespec::get_int(), 2) int[2];
				root->set_value(two_ints);
				// assign values to the allocated storage for both
				// array elements
				*two_ints = i*2+1;
				*(two_ints+1) = i*2+2;
				cout << ": " << i*2+1 << " and " << i*2+2 << endl;
				db[i]->close();
			}
		} OS_END_TXN(t1)

		objectstore::shutdown();

	} OS_END_FAULT_HANDLER
	return 0;
}
