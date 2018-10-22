// note.cpp: define methods of note class

#include "note.hh"

// Construct a note with the user_text and priority entered by
// the user. Insert the note being constructed at the front of
// a linked list.
note::note(const char* new_user_text, note* last_note, int note_priority)
{
	// Allocate space for user text and copy
	int len = strlen(new_user_text)+1;
	user_text = new(os_cluster::with(this), os_typespec::get_char(), len) char[len];
	strcpy(user_text,new_user_text);

	next = last_note;
	priority = note_priority;
}

// Destroy storage allocated for user_text before destroying note
note::~note()
{
	delete [] user_text;
}

// Print this note and its priority to the specified stream

void note::display(ostream& out)
{
	out << "(" << priority << ") \"" << user_text << "\"" << endl;
}

