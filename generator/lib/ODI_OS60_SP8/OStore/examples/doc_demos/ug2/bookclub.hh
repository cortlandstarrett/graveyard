// bookclub.h: defines the classes used by bookclub program
#include <iostream.h>
#include <string.h>
#include <ostore/ostore.hh>

#define BUFSIZE 100
#define RDR_ROOT_NAME "readers"
#define BK_ROOT_NAME "books"

// make the user-defined exception err_no_entry_point
// (defined in bookclub.cc) accessible to other files
DECLARE_EXCEPTION(err_no_entry_point);

// forward declarations of classes
class Ele;
class Reader;
class Book;

// global functions defined in bookclub.c
ostream &operator<<(ostream& os, Reader& r);
ostream &operator<<(ostream& os, Book& b);
char* bc_strdup(char* s1, os_cluster_with with_this);

// base class for managing linked lists
class Ele {
private:  // data member
	Ele* next;  // singly linked

public:  // methods
	Ele(Ele** last) { next = *last; *last = this; }
	virtual ~Ele() { next = 0; }
	Ele* get_next() { return next; }
	void set_next(Ele* e) { next = e; }
	Ele* find_item(char* s1, char* s2 = 0);
	virtual char* get_name() = 0;
	virtual int members_match(char* s1, char* s2 = 0) = 0;

private:
	// declared but unimplemented functions to prevent
	// inadvertent calls
	Ele();
	Ele(const Ele&);
	Ele& operator=(const Ele&);
};

// information about reader of Book
class Reader : public Ele {
private:  // data
	char* name;  // name of reader
	Book* selection;  // book selected

public:  // methods
	Reader(char* s, Reader** last);
	~Reader() ;

	// ObjectStore implements this function using the type
	// information in the schema file
	static os_typespec* get_os_typespec();

	char* get_name() { return name; }
	Book* get_selection() { return selection; }
	void set_selection(Book* b) { selection = b; }
	int members_match(char* n, char* dummy);
};

// information about book selected for Reader
class Book : public Ele {
private:  // data
	char* author; // author and ...
	char* title; // title of book

public:
	Book(char* a, char* t, Book** last);
	~Book();
	static os_typespec* get_os_typespec();
	char* get_name() { return author; }
	char* get_title() { return title; }
	int members_match(char* n, char* t);
};

