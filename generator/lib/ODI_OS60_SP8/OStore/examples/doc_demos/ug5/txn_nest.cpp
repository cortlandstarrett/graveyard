// txn_nest.cpp: illustrates a nested, abort-only transaction
// The outer, read-only transaction prevents data written in
// inner transaction from being recorded in database. The
// explicit abort at the end of inner transaction causes the
// roll back.
#include "note.hh"

note* head = 0; // Head of linked-list of notes

int main(int argc, char** argv)
{
	char buff[BUFSIZE], buff2[BUFSIZE];
	int note_priority;

	OS_ESTABLISH_FAULT_HANDLER {
		// check for command-line argument
		if(argc!=2) { // check for name of database
			cout << "Usage:  " << argv[0] << " <database>" << endl;
			return 1;
		}

		objectstore::initialize();
		// open database; create one if it doesn't exist
		os_database *db = os_database::open(argv[1], 0, 0644);
	
		// a nested transaction that does an abort-only transaction
		OS_BEGIN_TXN(t1, 0, os_transaction::read_only) {
			OS_BEGIN_TXN(t2, 0, os_transaction::update) {
				os_database_root *root_head = db->find_root("head");
				if(!root_head)
					root_head = db->create_root("head");
				head = (note *)root_head->get_value(note::get_os_typespec());
		
				cout << "Enter a new note: " << flush; // Prompt for new note
				cin.getline(buff, sizeof(buff));
		
				cout << "Enter a note priority: " << flush; // Prompt for priority
				cin.getline(buff2, sizeof(buff2));
				note_priority = atoi(buff2);
		
				head = new(db, note::get_os_typespec()) note(buff, head, note_priority);
				root_head->set_value(head, note::get_os_typespec());
				// roll back transaction
				os_transaction::abort();
			} OS_END_TXN(t2) // end update txn
		} OS_END_TXN(t1) // end read-only txn
	
		db->close();
		objectstore::shutdown();

	} OS_END_FAULT_HANDLER
	return 0;
}
