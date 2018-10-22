#include "restaurant.hh"
#include "dbname.h"

extern const char* DB_ROOT;

int main(int argc, char** argv)
{
	OS_ESTABLISH_FAULT_HANDLER {
		int n_tables;

		
		if (argc != 4 || !(n_tables = atoi(argv[3]))) {
			cerr << "USAGE: add_restaurant <name> <city> <n-tables>\n";
			return 1;
		}

		
		objectstore::initialize();
		os_collection::initialize();

		
		os_database* db = os_database::open(DB_NAME);

		
        OS_BEGIN_TXN(txn, 0, os_transaction::update) {
			
			os_set* restaurants =
				(os_set*)(db->find_root(DB_ROOT))->get_value(
				os_set::get_os_typespec());

			
			Restaurant* r = Restaurant::create_restaurant(argv[1],
				argv[2], n_tables, db);

			
			restaurants->insert(r);
        } OS_END_TXN(txn)
		db->close();
		delete db;
		objectstore::shutdown();
	} OS_END_FAULT_HANDLER

	return 0;
}

