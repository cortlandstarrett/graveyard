#include <ostore/ostore.hh>
#include <ostore/coll.hh>

#include <string.h>

/* The new definitions of classes epart and mpart */

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
	part(int id, employee * eng) {
	    part_id = id;
	    responsible_engineer = eng;
	};
	virtual char * part_type();
};

class epart : public part
{
    public:
	os_Collection<cell*> *cells;
	epart(int id, employee * eng) : part(id, eng) {}
	static os_typespec *get_os_typespec();
	virtual char * part_type();
};

class mpart : public part
{
    public:
	brep *boundary_rep;
	mpart(int id, employee * eng) : part(id, eng) {}
	static os_typespec *get_os_typespec();
	virtual char *  part_type();
};
