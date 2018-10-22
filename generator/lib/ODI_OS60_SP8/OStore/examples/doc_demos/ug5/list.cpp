// list.cpp: lists notes with priority numbers, as stored in database
#include "note.hh"

int main(int argc, char** argv)
{
	OS_ESTABLISH_FAULT_HANDLER {
		if(argc!=2) { // check for name of database
			cout << "Usage:	" << argv[0] << " <database>" << endl;
			return 1;
		}

		objectstore::initialize();
		os_database *db = os_database::open(argv[1]); // open database
		OS_BEGIN_TXN(t1,0,os_transaction::read_only) {
			os_database_root *root_head = db->find_root("head");
			if(!root_head) {
				cout << "Can't list empty database." << endl;
				return 1;
			}
			note* head = (note *)root_head->get_value(note::get_os_typespec());
	
			for(note* n = head; n; n = n->next) // Display existing notes
				n->display();
		} OS_END_TXN(t1)
	
		db->close();
		objectstore::shutdown();

	} OS_END_FAULT_HANDLER
	return 0;
}

