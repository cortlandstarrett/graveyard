#include "restaurant.hh"
#include "dbname.h"

int main(int argc, char** argv)
{
	int n_tables;

	
	if (argc != 3 || !(n_tables = atoi(argv[2]))) {
		cerr << "USAGE: init_db <restaurant-name> <n-tables>\n";
		return 1;
	}

	
	ofstream db(DB_NAME);

	
	Restaurant::create_restaurant(argv[1], n_tables, &db);

	db.close();

	return 0;
}

