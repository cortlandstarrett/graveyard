#include "restaurant.hh"
#include "dbname.h"

int main(int argc, char** argv)
{
	int n_tables;

	OS_ESTABLISH_FAULT_HANDLER {
		objectstore::initialize();

		
		if (argc != 3 || !(n_tables = atoi(argv[2]))) {
			cerr << "USAGE: init_db <restaurant-name> <n-tables>\n";
			return 1;
		}

		
		os_database* db = os_database::create(DB_NAME);

		
		OS_BEGIN_TXN(txn, 0, os_transaction::update) {

			
			Restaurant::create_restaurant(argv[1], n_tables, db);

		} OS_END_TXN(txn)
		db->close();
        delete db;
		objectstore::shutdown();
	} OS_END_FAULT_HANDLER

	return 0;
}

