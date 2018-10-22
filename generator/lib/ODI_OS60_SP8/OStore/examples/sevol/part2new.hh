#include <ostore/ostore.hh>
#include <ostore/coll.hh>

#include <string.h>

/* The new definition of class part */
class part
{
    public:
	char * part_id;
	part(char * id) {
	    int len = strlen(id) + 1;
	    part_id = new(os_cluster::with(this), os_typespec::get_char(), len)
		char[len];
	    strcpy(part_id, id);
	}
	static os_typespec *get_os_typespec();
};
