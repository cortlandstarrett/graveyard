#include "restaurant.hh"
#include "dbname.h"

const char* DB_ROOT = "restaurant_root";

const int Restaurant::QS_SIZE = 100;
const int Restaurant::PERSONSPERTABLE = 4;

Restaurant::Restaurant(const char* n, const char* c, int t):
    name(dupl_string(n)), city(dupl_string(c))
{
	tables = t;
}

Restaurant* Restaurant::create_restaurant(const char* n,
	const char* c, int t, os_database* db)
{
	
	os_typespec* ts = Restaurant::get_os_typespec();
	
	return new(db, ts) Restaurant(n, c, t);
}

os_set* Restaurant::create_restaurant_set(os_database* db)
{
	
	os_typespec* rest_ts = os_set::get_os_typespec();

	
	os_set* rest_set = new(db, rest_ts) os_set();

	
	os_database_root* db_root = db->create_root(DB_ROOT);
	db_root->set_value(rest_set, rest_ts);

	
	delete db_root;

	return rest_set;
}

char* Restaurant::dupl_string(const char* s)
{
	int len = strlen(s)+1;
	char* p = new(os_cluster::with(this), os_typespec::get_char(),
		len) char [len];
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

Restaurant* Restaurant::query_pick(const char* n,
	os_database* db, os_set* coll)
{
	char qstr[QS_SIZE];

	sprintf(qstr,"!strcmp(name, \"%s\")", n);
	return (Restaurant*)coll->query_pick((char*)"Restaurant*", qstr, db);
}

os_collection& Restaurant::query(const char* c,
	os_database* db, os_set* coll)
{
	char qstr[QS_SIZE];

	sprintf(qstr,"!strcmp(city, \"%s\")", c);
	return coll->query((char*)"Restaurant*", qstr, db);
}

ostream& operator<<(ostream& os, Restaurant& r)
{
	cout << r.get_name() << " in " << r.get_city()
		<< " has " << r.get_tables() << " table(s) available.\n";
	return os;
}

