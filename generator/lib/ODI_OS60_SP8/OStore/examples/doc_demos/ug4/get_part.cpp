// get_part.cpp: Reads one Part object from the database named parts
#include "part.hh"

int main(void)
{
	OS_ESTABLISH_FAULT_HANDLER {
		objectstore::initialize();
		os_database *db = os_database::open("parts");
		OS_BEGIN_TXN(txn, 0, os_transaction::read_only) {
			os_database_root *a_root = db->find_root("db_root");
			Part* a_part = (Part*)(a_root->get_value(Part::get_os_typespec()));
			cout << a_part->descrip << " (" << a_part->id << ")\n";
		} OS_END_TXN(txn)
		db->close();
		objectstore::shutdown();

	} OS_END_FAULT_HANDLER
	return 0;
}

