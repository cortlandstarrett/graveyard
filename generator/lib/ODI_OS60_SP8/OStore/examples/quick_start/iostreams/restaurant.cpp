#include "restaurant.hh"
#include "dbname.h"

const int Restaurant::BUFSIZE = 100;
const int Restaurant::PERSONSPERTABLE = 4;

Restaurant::Restaurant(const char* s, int t):
	name(dupl_string(s))
{
	tables = t;
}

void Restaurant::save_restaurant(fstream* db)
{
	db->seekp(0, ios::beg);
	*db << dec << tables << endl;
	*db << name << endl;
}

void Restaurant::create_restaurant(const char* s, int t, ofstream* db)
{
	*db << dec << t << endl;
	*db << s << endl;
}

Restaurant* Restaurant::get_restaurant(fstream* db)
{
	char name_buf[BUFSIZE];
	char table_buf[BUFSIZE];

	db->getline(table_buf, BUFSIZE);
	db->getline(name_buf, BUFSIZE);

	return (Restaurant*)new Restaurant(name_buf, atoi(table_buf));
}

char* Restaurant::dupl_string(const char* s)
{
	int len = strlen(s)+1;
	char* p = new char [len];
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

