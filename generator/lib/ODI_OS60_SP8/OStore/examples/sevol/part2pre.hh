#include <ostore/ostore.hh>
#include <ostore/coll.hh>

/* The old definition of class part */
class part
{
    public:
	int part_id;
	part(int id) { part_id = id; }
	static os_typespec *get_os_typespec();
};
