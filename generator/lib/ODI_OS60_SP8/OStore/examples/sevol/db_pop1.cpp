#include <stdio.h>
#include <stdlib.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include "part1pre.hh"
#include "dbname1.h"

int main(int, char **)
{
    objectstore::initialize();
    os_collection::initialize();
    OS_ESTABLISH_FAULT_HANDLER

    printf("db_pop1: opening database %s\n", example_db1_name);

    os_database *db = os_database::create(example_db1_name);

    printf("db_pop1: beginning a transaction\n");

    OS_BEGIN_TXN(tx1, 0, os_transaction::update)

        printf("db_pop1: creating and populating parts collection\n");

	os_Collection<part*> &parts =
	    os_Collection<part*>::create(db, 0, 5);
	long part_id_start = 1000;
	for (int i = 0; i < 5; i++) {
	    short pid = (short)(i + part_id_start);
	    parts |= new(db, part::get_os_typespec()) part(pid);
	    printf("db_pop1:     created part with id %d in os_database %s.\n",
		   pid, example_db1_name);
	}
	os_typespec parts_typespec("os_Collection<part*>");

        printf("db_pop1: creating parts database root\n");

	db->create_root("parts")->set_value(&parts, &parts_typespec);

        printf("db_pop1: ending transaction\n");

    OS_END_TXN(tx1)

    printf("db_pop1: closing database %s\n\n", example_db1_name);

    db->close();

    OS_END_FAULT_HANDLER

    objectstore::shutdown();

    return 0;
}

