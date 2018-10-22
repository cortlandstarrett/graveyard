#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <stdlib.h>

class Restaurant {
private:
	const char* name;
	int tables;
	static const int BUFSIZE;
	static const int PERSONSPERTABLE;
	char* dupl_string(const char* s);
public:
	Restaurant(const char* s, int t);
	~Restaurant() { delete [] (char*)name; };
	static void create_restaurant(const char* s, int t, ofstream* db);
	static Restaurant* get_restaurant(fstream* db);
	void save_restaurant(fstream* db);
	const char* get_name() { return name; }
	int get_tables() { return tables; }
	void set_tables(int t) { tables = t; }
	int make_reservation(int n_persons);
private:
	
	
	Restaurant();
	Restaurant(const Restaurant&);
	Restaurant& operator=(const Restaurant&);
};

