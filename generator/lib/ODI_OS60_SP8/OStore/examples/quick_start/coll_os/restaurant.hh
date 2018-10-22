#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>

class Restaurant;

ostream& operator<<(ostream& os, Restaurant& r);

class Restaurant {
private:
        const char* name;	
        const char* city;
        int tables;
	static const int PERSONSPERTABLE;
	static const int QS_SIZE;
	char* dupl_string(const char* s);
public:
	Restaurant(const char* n, const char* c, int t);
	~Restaurant() { delete [] (char*)name; delete [] (char*)city; }
	const char* get_name() { return name; }
	const char* get_city() { return city; }
	int get_tables() { return tables; }
	void set_tables(int t) { tables = t; }
	int make_reservation(int n_persons);
	static Restaurant* create_restaurant(const char* n,
		const char* c, int t, os_database* db);
	static os_set* create_restaurant_set(os_database* db);
	static Restaurant* query_pick(const char* n, os_database* db,
		os_set* coll);
	static os_collection& query(const char* c, os_database* db,
		os_set* coll);

	
	static os_typespec* get_os_typespec();

private:

	
	Restaurant();
	Restaurant(const Restaurant&);
	Restaurant& operator=(const Restaurant&);
};

