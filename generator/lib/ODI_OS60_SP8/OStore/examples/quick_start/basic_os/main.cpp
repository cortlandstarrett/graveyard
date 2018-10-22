#include "restaurant.hh"
#include <stdlib.h>
#include "dbname.h"

int main(int argc, char** argv)
{
	int tables_reserved, n_persons;

	OS_ESTABLISH_FAULT_HANDLER {
		objectstore::initialize();

		
		if (argc != 2 || !(n_persons = atoi(argv[1]))) {
			cerr << "USAGE: reserve <n-persons>\n";
			return 1;
		}

		
		os_database* db = os_database::open(DB_NAME);

		
		OS_BEGIN_TXN(txn, 0, os_transaction::update) {

			
			Restaurant* restaurant =
				Restaurant::get_restaurant(db);

			
			tables_reserved =
				restaurant->make_reservation(n_persons);

			
			if (tables_reserved)
				cout << "Reserved " << tables_reserved << " tables";
			else
				cout << "Sorry, all booked";
			cout << " at " << restaurant->get_name() << endl;

			

		} OS_END_TXN(txn)
		db->close();
        delete db;
		objectstore::shutdown();
	} OS_END_FAULT_HANDLER

	return 0;
}

