// note.h: new version of note class, with date member

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ostore/ostore.hh>

#define BUFSIZE 100
#define DATE_SIZE 9

// global function
void get_today(char *s);

// A simple class records a note entered by the user.
// Notes are maintained in reverse order in which they
// were created by a simple forward-linked list.

class note
{
public:

	// Public Member functions
	note(const char*, note*, int);
	~note();
	void display(ostream& = cout);
	static os_typespec* get_os_typespec();

	// Public Data members
	char* user_text;
	note* next;
	int priority;
	char date[DATE_SIZE];
};

