// list_bc.cpp:  lists the readers and the books they have
// selected, as well as all the books in the books database
#include "bookclub.hh"

int main(int argc, char* argv[])
{
	Reader* rdr = 0;
	Book* bk = 0;

	OS_ESTABLISH_FAULT_HANDLER {
		if (argc != 3) { // argument checking
			cout <<"USAGE:  "<<argv[0] <<" <reader-database> <book-database>\n";
			return 1;
		}

		objectstore::initialize();
		// open both databases
		os_database* db_rdr = os_database::open(argv[1]);
		os_database* db_bk = os_database::open(argv[2]);

		OS_BEGIN_TXN(txn, 0, os_transaction::read_only) {
			// get root, set rdr to the entry point, then navigate
			// through the reader database
			os_database_root *r_root = db_rdr->find_root(RDR_ROOT_NAME);
			rdr = (Reader*)r_root->get_value(Reader::get_os_typespec());
			for ( ; rdr; rdr = (Reader*)rdr->get_next()) {
				// print reader and selected book (if any)
				cout << *rdr << " selected ";
				if (bk = rdr->get_selection())
					cout << *bk;
				else
					cout << "nothing";
				cout << ".\n";
			}

			// do the same with books database
			os_database_root *b_root = db_bk->find_root(BK_ROOT_NAME);
			bk = (Book*)b_root->get_value(Book::get_os_typespec());
			for ( ; bk; bk = (Book*)bk->get_next())
				cout << *bk << endl;
		} OS_END_TXN(txn)
		db_rdr->close();
		db_bk->close();
		objectstore::shutdown();

	} OS_END_FAULT_HANDLER

	return 0;
}

