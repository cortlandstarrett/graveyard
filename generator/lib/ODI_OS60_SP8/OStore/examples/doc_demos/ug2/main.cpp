// main.cpp:  main application for the bookclub program; reads
// information about reader and selected book, and adds it to
// to the reader and book database files named on command line
#include "bookclub.hh"

int main(int argc, char* argv[])
{
	Reader* rdr = 0;
	Book* bk = 0;
	char name[BUFSIZE];
	char title[BUFSIZE];

	OS_ESTABLISH_FAULT_HANDLER {
		if (argc != 3) { // wrong number of arguments
			cerr << "USAGE:  bookclub <reader-db> <book-db>\n";
			return 1;
		}

		objectstore::initialize();
		os_database *db_rdr, *db_bk;
		// TIX exception handler for problems opening database
		// files.
		TIX_HANDLE (err_database_not_found) {
			// open reader and book databases
			db_rdr = os_database::open(argv[1]);
			db_bk = os_database::open(argv[2]);
		} TIX_EXCEPTION {
			cerr << "Cannot open " << argv[1] << " and/or ";
			cerr << argv[2] << ".  Check that files exist.\n";
			return 1;
		} TIX_END_HANDLE

		// set up lexical transaction
		OS_BEGIN_TXN(txn, 0, os_transaction::update) {
			// get type information for Reader and Book objects
			os_typespec* rdr_type = Reader::get_os_typespec();
			os_typespec* bk_type = Book::get_os_typespec();

			// get root and entry point
			os_database_root* root = db_rdr->find_root(
				RDR_ROOT_NAME);
			Reader* ep_rdr;
			if (!(ep_rdr = (Reader*)root->get_value(rdr_type)))
				err_no_entry_point.signal(
					"%s - use os_database_root::set_value()", argv[1]);

			// get reader's name
			cout << "Enter reader\'s name: " << flush;
			cin.getline(name, BUFSIZE);
			if (!(rdr = (Reader*)ep_rdr->find_item(name))) {
				// reader not in database, so add a new one
				rdr = new(os_cluster::with(ep_rdr), rdr_type)
					Reader(name, &ep_rdr); 
				// make the new reader the entry point
				root->set_value(rdr, rdr_type);
			}

			// get root and entry point for books database
			root = db_bk->find_root(BK_ROOT_NAME);
			Book* ep_bk;
			if (!(ep_bk = (Book*)root->get_value(bk_type)))
				err_no_entry_point.signal(
					"%s - use os_database_root::set_value()", argv[2]);

			// get book info -- author's name and book title
			cout << "Enter author\'s name: " << flush;
			cin.getline(name, BUFSIZE);
			cout << "Enter book title: " << flush;
			cin.getline(title, BUFSIZE);
			// if book is not in database, add it.
			if (!(bk = (Book*)ep_bk->find_item(name, title))) {
				// create a book
				bk = new(os_cluster::with(ep_bk), bk_type)
					Book(name, title, &ep_bk);
				// make the new book the entry point
				root->set_value(bk, bk_type);
			}
			// select reader's choice
			rdr->set_selection(bk); // select book
		} OS_END_TXN(txn)
		db_rdr->close(); // close both database files
		db_bk->close();
		// release the pointers to the os_database objects
		db_rdr->release_pointer();
		db_bk->release_pointer();
		objectstore::shutdown();

	} OS_END_FAULT_HANDLER

	return 0;
}

