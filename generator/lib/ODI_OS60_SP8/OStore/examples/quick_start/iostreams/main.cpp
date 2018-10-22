#include "restaurant.hh"
#include "dbname.h"

int main(int argc, char** argv)
{
	int tables_reserved, n_persons;

	
	if (argc != 2 || !(n_persons = atoi(argv[1]))) {
		cerr << "USAGE: reserve <n-persons>\n";
		return 1;
	}

	
	fstream db(DB_NAME, ios::in|ios::out);

	
	Restaurant* restaurant = Restaurant::get_restaurant(&db);

	
	tables_reserved = restaurant->make_reservation(n_persons);

	
	if (tables_reserved)
		cout << "Reserved " << tables_reserved << " tables";
	else
		cout << "Sorry, all booked";
	cout << " at " << restaurant->get_name() << endl;

	
	restaurant->save_restaurant(&db);
	delete restaurant;

	db.close();

	return 0;
}

