// txn_example.cpp: illustrates lexical and dynamic transactions
// The program writes an array of strings to a database in a
// lexical transaction (using the macros), and reads the array
// in a dynamic transaction (using the os_transaction methods).
#include <ostore/ostore.hh>
#include <string.h>
#include <fstream.h>

#define SIZE 5
int main()
{
	os_database* db;
	os_database_root* root;
	os_transaction* txn;

	const char *verse[] = {
		"Matter, as wise logicians say,",
		"  Cannot without a form subsist;",
		"And form, say I as well as they,",
		"  Must fail if matter brings no grist.",
		""
	};
	OS_ESTABLISH_FAULT_HANDLER {
		objectstore::initialize();
		// create the database "stanza.db"; if it already exists, overwrite it
		db = os_database::create("stanza.db", 0644, 1);
	
		// start a lexical transaction in update mode
		OS_BEGIN_TXN(t1, 0, os_transaction::update) {
			// allocate persistent storage for an array of pointers to chars
			char **s = (char**)new(db,
				os_typespec::get_pointer(), SIZE) void**[SIZE];
			// create a root ...
			root = db->create_root("root");
			// ... and associate it with the first element of the array,
			// making it the entry point
			root->set_value(s, os_typespec::get_pointer());
			for (int i = 0; i < SIZE; i++) {
				int len = strlen(verse[i])+1;
				// allocate persistent storage for the string, clustering
				// it with the previously allocated array
				s[i] = new(os_cluster::with(s),
					os_typespec::get_char(), len) char[len];
				// copy the string in verse[i] to the allocated storage
				strcpy(s[i], verse[i]);
			}
		} OS_END_TXN(t1)
		db->close(); // close database

		db->open(0); // re-open database for read-only
		// start a dynamic transaction in read-only mode
		txn = os_transaction::begin(os_transaction::read_only);
		root = db->find_root("root"); // find the database root
		// get the entry-point (the first element of an array of
		// pointers to chars) associated with the root
		char** s = (char**)(root->get_value(os_typespec::get_pointer()));
		// print the strings
		for (; **s; s++)
			cout << *s << endl;
		txn->commit(); // commit transaction
		db->close(); // close database
		// clean up
		delete db;
		delete root;
		delete txn;
		objectstore::shutdown();
	} OS_END_FAULT_HANDLER
	return 0;
}


