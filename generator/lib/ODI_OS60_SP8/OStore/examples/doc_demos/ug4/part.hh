// part.h: defines the classes used by set_part.cpp and
// get_part.cpp programs
#include <iostream.h>
#include <string.h>
#include <ostore/ostore.hh>

class Part {
public:
	char* descrip;
	int id;

	static os_typespec *get_os_typespec();
	Part(char* s, int n);
};
