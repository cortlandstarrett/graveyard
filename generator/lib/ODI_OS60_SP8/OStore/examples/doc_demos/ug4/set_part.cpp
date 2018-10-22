// set_part.cpp: Writes one Part object to the database named parts
#include "part.hh"

int main(void)
{
	OS_ESTABLISH_FAULT_HANDLER {
		objectstore::initialize();
		os_database *db = os_database::create("parts");
       		OS_BEGIN_TXN(txn, 0, os_transaction::update) {
			os_typespec* part_ts = Part::get_os_typespec();
			Part *a_part = new(db, part_ts) Part((char*)"wrench", 111);
			os_database_root *a_root = db->create_root("db_root");
			a_root->set_value(a_part, part_ts);
		} OS_END_TXN(txn)
		db->close();
		objectstore::shutdown();

	} OS_END_FAULT_HANDLER
	return 0;
}

