// hello.cpp
// Exercises basic features of CMTL API; configures CMTL from XML file.
// To keep the program simple, application code does minimal error-checking.

#include "hello.h"

// names of logical database and database root
const char* HELLOWORLD_DB = "HelloWorld Database";
const char* HELLOWORLD_ROOT = "HelloWorld Root";
const char* CACHE_POOL = "HelloWorld Cache Pool";

// configures caches and cache pool manager, creates a cache pool manager,
// and creates the database, using the logical name
void setup(const char *xml_path)
{
	cout << "Configuring the cache pool manager ...";

	// create a cache pool manager configuration
	os_cache_pool_manager_config* cpm_cfg =
		os_cache_pool_manager_config::create_from_xml_file(xml_path);

	// create the cache pool manager
	os_cache_pool_manager* cpm = os_cache_pool_manager::create(*cpm_cfg);
	cout << " done!\n";
}

// sets up a virtual transaction to create a database root
void create_root()
{
	cout << "Creating the database and database root ...";

	// use a BasicTransactionContext for the operations
	os_basic_transaction_context* ctx = os_basic_transaction_context::create();

	// start a virtual transaction using the BasicTransactionContext
	OS_BEGIN_VT (vt1, *ctx) {
		// get the database with the logical name HELLOWORLD_DB, using the
		// current cache
		os_database* db =
			os_cache::get_current()->create_database(HELLOWORLD_DB);

		// create a persistent entry-point object to associate with the root
		int len = strlen("Hello World") + 1;
		char* ep_obj = new(db, os_typespec::get_char(), len) char [len];
		strcpy(ep_obj, "Hello World");

		// associate the entry-point object with the database root
		os_cache_pool_manager::get()->get_root(HELLOWORLD_ROOT)->set_root_value(ep_obj);

		db->release_pointer();
	} OS_END_VT (vt1)
	cout << " done!\n";
}

void access_db_root()
{
	read_db_root();
	write_db_root();
	read_db_root();
}

// uses a virtual transaction to retrieve the persistent object (a string)
// associated with logical database root, then writes this object on standard
// output
void read_db_root()
{
	cout << "Reading the database root ... ";
	os_basic_transaction_context* ctx =
		os_basic_transaction_context::create(os_transaction_context::read_only, os_transaction_context::read_uncommitted);
	OS_BEGIN_VT (vt2, *ctx) {
		// get the entry-point object associated with the logical database root
		cout << (char*)os_cache::get_current()->get_root_value(HELLOWORLD_ROOT);
	} OS_END_VT (vt2)
	cout << " ... done!\n";
}

// uses a virtual transaction to associate a new entry-point object with
// logical database root, then calls read_db_root() to read new object
void write_db_root()
{
	cout << "Writing a new database root ... ";
	os_basic_transaction_context* ctx = os_basic_transaction_context::create();
	OS_BEGIN_VT (vt3, *ctx) {
		os_database* db = os_cache::get_current()->get_database(HELLOWORLD_DB);

		int len = strlen("Hello Brave New World") + 1;
		char* new_ep_obj = new(db, os_typespec::get_char(), len) char [len];
		strcpy(new_ep_obj, "Hello Brave New World");

		// associate a new entry-point object with the database root, using
		// the logical root name to get the root.  The database root was
		// previously created, so that the call to set_root_value() does not
		// try to create it; see above, create_root().  set_root_value()
		// creates the root only if it doesn't already exist.
		os_cache_pool_manager::get()->get_root(HELLOWORLD_ROOT)->set_root_value(new_ep_obj);

		db->release_pointer();
	} OS_END_VT (vt3)
	cout << " done!\n";
}

