// hello.cpp
// Exercises basic features of CMTL API; uses API to configure CMTL.
// To keep the program simple, application code does minimal error-checking.

#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include "hello.h"

const char* HELLOWORLD_DB = "HelloWorld Database";
const char* HELLOWORLD_ROOT = "HelloWorld Root";
const char* CACHE_POOL = "HelloWorld Cache Pool";

// configures and creates a cache pool manager, maps a physical database
// name to a logical database name, and creates the database, using the logical
// name
void setup(const char* physical_db, const char* physical_root)
{
	// cache pool attributes
	struct os_attribute_elem cp_attribs[] = {
		{ "update_caches", "1" },
		{ "mvcc_caches", "1" },
	};

	// make a NULL-terminated array of attribute pointers for
	// configuring cache pool
	struct os_attribute_elem *attrib_array[4];
	attrib_array[0] = &cp_attribs[0];
	attrib_array[1] = &cp_attribs[1];
	attrib_array[2] = NULL;

	cout << "Configuring the cache pool manager ...";

	// create a cache pool configuration
	os_cache_pool_config* cp_cfg =
		os_cache_pool_config::create(CACHE_POOL, attrib_array);

	// cache pool manager attributes
	struct os_attribute_elem cpm_attribs[] = {
		{ "debug_level", "cmtl_log_debug" },
		{ "debug_output_file", "hello.log" },
		{ "overwrite_debug_output_file", "true" },
	};

	// make a NULL-terminated array of attribute pointers for
	// configuring cache pool manager
	attrib_array[0] = &cpm_attribs[0];
	attrib_array[1] = &cpm_attribs[1];
	attrib_array[2] = &cpm_attribs[2];
	attrib_array[3] = NULL;

	os_cache_pool_config* cp_cfg_array[2];
	cp_cfg_array[0] = cp_cfg;
	cp_cfg_array[1] = NULL;

	// make a NULL-terminated array of attribute pointers for
	// configuring cache pool manager
	// create a cache pool manager configuration
	os_cache_pool_manager_config* cpm_cfg =
		os_cache_pool_manager_config::create(cp_cfg_array, attrib_array);

	// create cache pool manager with configuration information
	os_cache_pool_manager* cpm =
		os_cache_pool_manager::create(*cpm_cfg);

	// no longer need the configuration objects
	delete cp_cfg;
	delete cpm_cfg;

	// map the physical database name to the logical database name so that
	// you can reference the root by its logical name the cache pool manager
	cpm->set_db_mapping(HELLOWORLD_DB, physical_db);

	cout << " done!\n";

	cout << "Creating database ...";

	// create database with read-write access
	cpm->get_cache_pool(CACHE_POOL)->create_database(HELLOWORLD_DB);

	cout << " done!\n";
}

// sets up a virtual transaction to create a database root
void create_root()
{
	cout << "Creating the database root ... ";

	// use a BasicTransactionContext for the operations
	os_basic_transaction_context* ctx = os_basic_transaction_context::create();

	// start a virtual transaction using the BasicTransactionContext
	OS_BEGIN_VT (vt1, *ctx) {
		// get the database with the logical name HELLOWORLD_DB, using the
		// current cache; note that, since we haven't specified a "current
		// cache", the default is the update cache
		os_database* db = os_cache::get_current()->get_database(HELLOWORLD_DB);

		// create a persistent entry-point object to associate with the root
		int len = strlen("Hello World") + 1;
		char* ep_obj = new(db, os_typespec::get_char(), len) char [len];
		strcpy(ep_obj, "Hello World");

		// map the entry-point object to the database root, and let the
		// cache pool managaer know about the mapping
		os_root_mapping* root =
			os_root_mapping::create(HELLOWORLD_DB, "string");
		root->set_root_value(ep_obj);
		os_cache_pool_manager::get()->add_root(HELLOWORLD_ROOT, root);

		db->release_pointer();
	} OS_END_VT (vt1)
	cout << "done!\n";
	delete ctx;
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
		// and output its name
		cout << (char*)os_cache::get_current()->get_root_value(HELLOWORLD_ROOT);
	} OS_END_VT (vt2)
	cout << " ... done!\n";
	delete ctx;
}

// uses a virtual transaction to associate a new entry-point object with
// logical database root, then calls read_db() to read new object
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
		// the logical root name; note that the database root was previously
		// created, so that this call to set_root_value() does not try to
		// create it (see above, create_root())
		(os_cache_pool_manager::get()->get_root(HELLOWORLD_ROOT))->set_root_value(new_ep_obj);

		db->release_pointer();
	} OS_END_VT (vt3)
	cout << " done!\n";
	delete ctx;
}

