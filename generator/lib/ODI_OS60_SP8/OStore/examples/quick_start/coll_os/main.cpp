#include "restaurant.hh"
#include "dbname.h"
#include <stdlib.h>

extern const char* DB_ROOT;

int main(int argc, char** argv)
{
	OS_ESTABLISH_FAULT_HANDLER {
		int tables_reserved;

		
		if (argc != 3) {
			cerr << "USAGE: reserve <restaurant-name> <n-persons>\n";
			return 1;
		}

		
		objectstore::initialize();
		os_collection::initialize();

		
		os_database* db = os_database::open(DB_NAME);

		os_database_root* db_root;

		
        OS_BEGIN_TXN(txn, 0, os_transaction::update) {
			
			db_root = db->find_root(DB_ROOT);

			
			os_set* rset = (os_set*)db_root->get_value(
				os_set::get_os_typespec());

			
			Restaurant* r = Restaurant::query_pick(
				argv[1], db, rset);

			
			if (r) {
				
				tables_reserved = r->make_reservation(atoi(argv[2]));

				
				if (tables_reserved)
					cout << "Reserved " << tables_reserved
						<< " tables.\n";
				else
					cout << "Sorry, all booked.\n";
			}
			else
				cout << "Can\'t find " << argv[1] << " in database.\n";
        } OS_END_TXN(txn)

		db->close();

		
		delete db;
		delete db_root;

		objectstore::shutdown();
	} OS_END_FAULT_HANDLER

	return 0;
}

