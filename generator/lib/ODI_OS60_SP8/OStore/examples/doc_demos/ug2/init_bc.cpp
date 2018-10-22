// init_bc.cpp:  creates and initializes two databases used by the
// bookclub program
#include "bookclub.hh"

int main(int argc, char* argv[])
{
	Reader* rdr = 0;
	Book* bk = 0;
	char name[BUFSIZE];
	char title[BUFSIZE];

	OS_ESTABLISH_FAULT_HANDLER {
		// argument checking
		if (argc !=3) {
			cout <<"USAGE:  " <<argv[0] << " reader-db book-db < input-file\n";
			return 1;
		}

		objectstore::initialize();
		// create two databases, one for readers and the other for books
		os_database *db_rdr = os_database::create(argv[1]);
		os_database *db_bk = os_database::create(argv[2]);

		// affiliate db_rdr with db_bk:  db_rdr will contain
		// pointers to objects stored in db_bk
		db_rdr->affiliate(db_bk,0,0);

		OS_BEGIN_TXN(txn, 0, os_transaction::update) {
			// read in names of readers until encountering empty string
			while (cin.getline(name, BUFSIZE) && name[0])
				// create a reader object; constructor links it into list
				rdr = new(db_rdr,Reader::get_os_typespec()) Reader(name,&rdr); 
			// create a root that we can use to establish the entry point,
			// the last reader in list
			os_database_root* r_root = db_rdr->create_root(RDR_ROOT_NAME);
			r_root->set_value(rdr, Reader::get_os_typespec());

			// read in authors and their books
			while (cin.getline(name, BUFSIZE) && name[0]) {
				cin.getline(title, BUFSIZE);
				// create a book object; constructor links it into list
				bk = new(db_bk,Book::get_os_typespec()) Book(name,title,&bk); 
			}
			// create root and establish entry point
			os_database_root* b_root = db_bk->create_root(BK_ROOT_NAME);
			b_root->set_value(bk, Book::get_os_typespec());
		} OS_END_TXN(txn)
		db_rdr->close();
		db_bk->close();
		objectstore::shutdown();

	} OS_END_FAULT_HANDLER

	return 0;
}
