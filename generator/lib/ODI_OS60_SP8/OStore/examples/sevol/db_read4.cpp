#include <stdlib.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include "part4new.hh"
#include "dbname4.h"

int main(int, char **)
{
    objectstore::initialize();
    os_collection::initialize();
    OS_ESTABLISH_FAULT_HANDLER

    printf("db_read4: opening database %s\n", example_db4_name);

    os_database *db = os_database::open(example_db4_name);

    printf("db_read4: beginning a transaction\n");

    OS_BEGIN_TXN(tx1, 0, os_transaction::update)

        printf("db_read4: finding parts database root\n");

	os_database_root * parts_root = os_database_root::find("parts", db);
	os_typespec parts_typespec("os_Collection<part*>");

        printf("db_read4: walking through parts collection\n");

	os_Collection<part*> &parts =
	    *(os_Collection<part*>*) parts_root->get_value(&parts_typespec);
        os_index_path& ip = os_index_path::create("part*", "part_id", db);
        os_Cursor<part*> cursor(parts, ip);
	for (part * p = cursor.first(); cursor.more(); p = cursor.next()) {
	    printf("db_read4: Found %s with part id %d\n", p->part_type(), p->part_id);
	    printf("          in os_database %s.\n", example_db4_name);
	}
        delete (os_index_path*)&ip;

    printf("db_read4: ending transaction\n");

    OS_END_TXN(tx1)

    printf("db_read4: closing database %s\n\n", example_db4_name);

    db->close();

    OS_END_FAULT_HANDLER

    objectstore::shutdown();

   return 0;
}

