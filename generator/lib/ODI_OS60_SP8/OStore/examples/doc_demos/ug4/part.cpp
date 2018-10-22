// part.cc:  definition file for the inventry program
#include "part.hh"

Part::Part(char* s, int n)
{
	int len = strlen(s)+1;
	descrip = new (os_cluster::with(this), os_typespec::get_char(), len)
		char[len];
	strcpy(descrip, s);

	id = n;
}
