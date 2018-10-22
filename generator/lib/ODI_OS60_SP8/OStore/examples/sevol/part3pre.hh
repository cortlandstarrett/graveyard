#include <ostore/ostore.hh>
#include <ostore/coll.hh>

#include <string.h>

/* The old definitions of classes epart and mpart */

class supplier
{
    public:
	int supplier_id;
	supplier(int sid) { supplier_id = sid; }
};

class employee
{
    public:
	char * name;
	employee(const char * n) {
	    int len = strlen(n) + 1;
	    name = new(os_cluster::with(this), os_typespec::get_char(), len)
		char[len];
	    strcpy(name, n);
	}
	static os_typespec *get_os_typespec();
};

class cell{};

class epart : public supplier
{
    public:
	int part_id;
	employee * responsible_engineer;
	os_Collection<cell*> cells;
	epart(int id, employee * eng) : supplier(5) {
	    part_id = id;
	    responsible_engineer = eng;
	}
	static os_typespec *get_os_typespec();
};

class brep{};

class mpart : public supplier
{
    public:
	int part_id;
	employee * responsible_engineer;
	os_Collection<brep*> boundaries;
	mpart(int id, employee * eng) : supplier(5) {
	    part_id = id;
	    responsible_engineer = eng;
	}
	static os_typespec *get_os_typespec();
};
