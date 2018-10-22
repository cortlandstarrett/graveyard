#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <ostore/ostore.hh>

class Restaurant {
private:
	const char* name;
	int tables;
	static const int PERSONSPERTABLE;
	static const char* DB_ROOT;
	char* dupl_string(const char* s);
public:
	Restaurant(const char* s, int t);
	~Restaurant() { delete [] (char*)name; }
	static void create_restaurant(const char* s, int t,
		os_database* db);
	static Restaurant* get_restaurant(os_database* db);
	const char* get_name() { return name; }
	int get_tables() { return tables; }
	void set_tables(int t) { tables = t; }
	int make_reservation(int n_persons);

	
	static os_typespec* get_os_typespec();

private:
	
	
	Restaurant();
	Restaurant(const Restaurant&);
	Restaurant& operator=(const Restaurant&);
};

