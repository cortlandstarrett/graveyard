#include "restaurant.hh"
#include "dbname.h"

extern const char* DB_ROOT;

int main(int argc, char** argv)
{
	OS_ESTABLISH_FAULT_HANDLER {
		Restaurant* r = 0;
		os_cursor* c = 0;

		
		if (argc > 2) {
			cerr << "USAGE: rlist [<city-name>]\n";
			return 1;
		}

		
		objectstore::initialize();
		os_collection::initialize();

		
		os_database* db = os_database::open(DB_NAME);

		
        OS_BEGIN_TXN(txn, 0, os_transaction::read_only) {
			
			os_set* rcoll =
				(os_set*)(db->find_root(DB_ROOT))->get_value(
				os_set::get_os_typespec());

			if (argc == 2) {
				
				
				os_collection& city = Restaurant::query(argv[1], db, rcoll);

				
				c = new os_cursor(city);
			}
			else
				
				c = new os_cursor(*rcoll);

			
			if (r = (Restaurant*)c->first())
				
				for (; c->more(); r = (Restaurant*)c->next())
					cout << *r;
			else if (argc == 2)
				cout << "No restaurants in " << argv[1] << ".\n";
			else
				cout << "No restaurants in database.\n";

			delete c;
        } OS_END_TXN(txn)
		db->close();
		delete db;
		objectstore::shutdown();
	} OS_END_FAULT_HANDLER

	return 0;
}

