#include "restaurant.hh"
#include "dbname.h"

extern const char* DB_ROOT;

int main(int argc, char** argv)
{
	OS_ESTABLISH_FAULT_HANDLER {
		Restaurant* r;
		
		struct {
		        const char* n;
		        const char* c;
			int t;
		}rinfo[] =
		{
			"Il Falchetto", "Perugia", 25,
			"Agawam Diner", "Rowley", 12,
			"Maurizio\'s", "Marblehead", 34,
			"Daily Catch", "Boston", 6,
			"Woodman\'s", "Essex", 67,
			"Elephant Walk", "Boston", 33,
			"Farnham\'s", "Essex", 16,
			NULL, NULL, 0,
		};

		
		objectstore::initialize();
		os_collection::initialize();

		
		os_database* db = os_database::create(DB_NAME);

		
        OS_BEGIN_TXN(txn, 0, os_transaction::update) {
			
			os_set* rcoll = Restaurant::create_restaurant_set(db);

			
			for (int i = 0; rinfo[i].n; i++) {
				
				r = Restaurant::create_restaurant(rinfo[i].n,
						rinfo[i].c, rinfo[i].t, db);
				
				rcoll->insert(r);
			}
        } OS_END_TXN(txn)
		db->close();
		delete db;
		objectstore::shutdown();
	} OS_END_FAULT_HANDLER

	return 0;
}

