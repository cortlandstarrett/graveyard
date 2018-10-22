// note.cpp: definitions file for updated notes program
#include "note.hh"

// Construct a note with the user_text and priority entered by
// user. Insert the note being constructed at the front of list.
note::note(const char* new_user_text, note* last_note, int note_priority)
{
	// Allocate space for user text and copy
	int len = strlen(new_user_text)+1;
	user_text = new(os_segment::of(this),os_typespec::get_char(),len) char[len];
	strcpy(user_text,new_user_text);

	next = last_note;
	priority = note_priority;
	get_today(date);
}

// Destroy storage allocated for user_text before destroying note
note::~note()
{
	delete [] user_text;
}

// Print this note to the specified stream
void note::display(ostream& out)
{
	out << date << ":  (" << priority << ") \"" << user_text << "\"" << endl;
}

// return current date in s, formatted as "mm/dd/yy"
void get_today(char *s)
{
	time_t t1, *p1;

	p1 = &t1;
	time(p1);
	strftime(s, DATE_SIZE, "%m/%d/%y", localtime(p1));
}

