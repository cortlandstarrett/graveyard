#include <ostore/ostore.hh>
#include <ostore/coll.hh>

/* The new definition of class part */
class part
{
    public:
	long part_id;
	part(long id) { part_id = id; }
	static os_typespec *get_os_typespec();
};
