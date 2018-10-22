// note.h: declare note class

#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <ostore/ostore.hh>

#define BUFSIZE 100

// A simple class to record a note and its priority entered
// by the user. Notes are maintained in reverse order in which
// they were created by a simple forward-linked list.

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
  int   priority;
};

