// evol_schema.cpp:  schema-evolution application for evolving
// schema for note program.  Schema evolution in this example
// will include setting the new data member (date) to the
// desired date, using the get_today() function defined by the
// application.
#include "note.hh"
#include <ostore/coll.hh>
#include <ostore/schmevol.hh>

static void note_transform(os_void_p new_note);

int main(int argc, char** argv)
{
	OS_ESTABLISH_FAULT_HANDLER {
		if (argc != 3) { // check for name of database
			cout << "Usage:  " << argv[0] << " <scratch-file> <db-to-evolve>"
				<< endl;
			return 1;
		}

		objectstore::initialize();
		// associate the transformer function note_transform()
		// with the class note
		os_schema_evolution::augment_post_evol_transformers(
			os_transformer_binding("note", note_transform));
		// initiate evolution
		os_schema_evolution::evolve(argv[1], argv[2]);

		objectstore::shutdown();

	} OS_END_FAULT_HANDLER
	return 0;
}

// called for each new note object in evolved database,
// to write current date in the new date member
static void note_transform(os_void_p new_note)
{
	// get a pointer to new note object
	note* p = (note*)new_note;
	// call get_today() (defined in note.cpp) to copy
	// string containing current date into date member
	get_today(p->date);
}

