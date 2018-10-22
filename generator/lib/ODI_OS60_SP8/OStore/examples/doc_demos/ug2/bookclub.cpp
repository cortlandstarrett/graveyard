// bookclub.cpp:  definition file for the bookclub program
#include "bookclub.hh"

// user-defined TIX exception
DEFINE_EXCEPTION(err_no_entry_point, "No entry-point object for ", 0);

// constructor for Reader
Reader::Reader(char* s, Reader** last) : Ele((Ele**)last)
{
	name = bc_strdup(s, os_cluster::with(this));
	selection = 0;
}

// destructor for Reader
Reader::~Reader() { delete [] name; }

// constructor for Book
Book::Book(char* a, char* t, Book** last) : Ele((Ele**)last)
{
	author = bc_strdup(a, os_cluster::with(this));
	title = bc_strdup(t, os_cluster::with(this));
}

// destructor for Book
Book::~Book() { delete [] author; delete [] title; }

// Walks recursively through a Ele list looking for the object
// whose members match the arguments.  Returns the object, if
// found; otherwise, returns NULL (the value returned by
// get_next() for the last object in the list).
Ele* Ele::find_item(char* s1, char* s2)
{
	if (!this)  // end of list
		return 0;  // not found
	else if (members_match(s1, s2))
		return this;  // found it
	else
		return (get_next())->find_item(s1, s2); // keep looking
}

// Returns true (1) if name member of Reader object matches n;
// dummy argument (unused) needed to keep the compiler happy.
// Without the second char* argument, members_match() would
// have different signature from the virtual members_match()
// in Ele.  The invocation will specify one argument (n); the
// other is supplied by the initializer (0) specified in the
// declaration of the virtual member function in Ele.
int Reader::members_match(char* n, char*)
{
	if (strcmp(get_name(), n))
		return 0;
	else
		return 1;
}

// Returns true (1) if author and title members of Book
// object match n and t.
int Book::members_match(char* n, char* t)
{
	if (strcmp(get_name(), n) || strcmp(get_title(), t))
		return 0;
	else
		return 1;
}

// global functions

// The following overloadings of the << operator are used to
// print Reader and Book objects.  As explained in "C++,
// The Core Language", p. 115 (footnote), these functions must
// be global  (or friends) and not member functions of the
// classes:  "If a binary operator like = or << is going to be
// a member function, it must be a member of the class it takes
// on its lefthand side."

ostream &operator<<(ostream& os, Reader& r)
{
	os << r.get_name();
	return os;
}

ostream &operator<<(ostream& os, Book& b)
{
	os << b.get_name() << "\'s " << "\""<< b.get_title() << "\"";
	return os;
}

// returns newly allocated string
char *bc_strdup(char* s1, os_cluster_with with_this)
{
	int len = strlen(s1)+1;
	char* s2 = new(with_this, os_typespec::get_char(), len) char [len];
	return strcpy(s2, s1);
}

