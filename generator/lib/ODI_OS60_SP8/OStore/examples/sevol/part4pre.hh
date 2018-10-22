#include <ostore/ostore.hh>
#include <ostore/coll.hh>

#include <string.h>

/* The old definition of class part */

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

class brep
{
    public:
	int bound;
	brep(int b) { bound = b; }
	static os_typespec *get_os_typespec();
};

class part
{
    public:
	int part_id;
	employee * responsible_engineer;
	os_Collection<cell*> *cells;
	brep * boundary_rep;
	part(int id, employee * eng) {
	    part_id = id;
	    responsible_engineer = eng;
	    cells = 0;
	    boundary_rep = 0;
	}
	static os_typespec *get_os_typespec();
	virtual char * part_type();
};
