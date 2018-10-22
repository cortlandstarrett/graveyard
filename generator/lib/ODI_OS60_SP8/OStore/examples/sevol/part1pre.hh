#include <ostore/ostore.hh>
#include <ostore/coll.hh>

/* The old definition of class part */
class part
{
    public:
	short part_id;
	part(short id) { part_id = id; }
	static os_typespec *get_os_typespec();
};
