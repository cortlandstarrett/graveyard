#include "restaurant.hh"
#include "dbname.h"

const int Restaurant::PERSONSPERTABLE = 4;
const char* Restaurant::DB_ROOT = "restaurant_root";

Restaurant::Restaurant(const char* s, int t):
    name(dupl_string(s))
{
	tables = t;
}

void Restaurant::create_restaurant(const char* s, int t,
	os_database* db)
{
	
	os_typespec* ts = Restaurant::get_os_typespec();
	
	Restaurant* restaurant = new(db, ts) Restaurant(s, t);
	
	os_database_root* db_root = db->create_root(DB_ROOT);
	
	db_root->set_value(restaurant, ts);
	
	delete db_root;
}

Restaurant* Restaurant::get_restaurant(os_database* db)
{
	
	os_database_root* db_root = db->find_root(DB_ROOT);
	
	return (Restaurant*)db_root->get_value(
		Restaurant::get_os_typespec());
	
	delete db_root;
}

char* Restaurant::dupl_string(const char* s)
{
	int len = strlen(s)+1;
	char* p = new(os_cluster::with(this),
		os_typespec::get_char(), len) char [len];
	return strcpy(p, s);
}

int Restaurant::make_reservation(int n_persons)
{
	int tables_to_reserve = 0;
	int tables_available = get_tables();

	if (!tables_available)
		;
	else if (n_persons <= PERSONSPERTABLE) {
		set_tables(tables_available-1);
		tables_to_reserve = 1;
	}
	else {
		tables_to_reserve = n_persons / PERSONSPERTABLE;
		if (tables_to_reserve*PERSONSPERTABLE < n_persons)
			tables_to_reserve++;
		if (tables_to_reserve > tables_available)
		
			tables_to_reserve = 0;
		else
		
			set_tables(tables_available-tables_to_reserve);
	}
	return tables_to_reserve;
}

