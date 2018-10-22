#include <stdio.h>
#include <stdlib.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include "part4pre.hh"
#include "dbname4.h"

static const char *engineers[10] = {
    "Adam",
    "Bob",
    "Dan",
    "Don",
    "Dave",
    "Jack",
    "Mary",
    "Janice",
    "Rick",
    "Sam"
};

int main(int, char **)
{
    objectstore::initialize();
    os_collection::initialize();
    OS_ESTABLISH_FAULT_HANDLER

    printf("db_pop4: opening database %s\n", example_db4_name);

    os_database *db = os_database::create(example_db4_name);

    printf("db_pop4: beginning a transaction\n");

    OS_BEGIN_TXN(tx1, 0, os_transaction::update)

        printf("db_pop4: creating and populating parts collection\n");

	os_Collection<part*> &parts =
	    os_Collection<part*>::create(db, 0, 10);
	long part_id_start = 1000;
	int i;
	part *p;
	for (i = 0; i < 5; i++) {
	    int pid = (int)(i + part_id_start);
	    p = new(db, part::get_os_typespec())
		part(pid, new(db, employee::get_os_typespec())
		    employee(engineers[i]));
	    p->cells = &os_Collection<cell*>::create(db, 0, 2);
	    parts |= p;
	    printf("db_pop4:     created part with id %d and engineer %s\n",
		   pid, engineers[i]);
	    printf("             with cells in os_database %s.\n", example_db4_name);
	}
	for (i = 5; i < 10; i++) {
	    int pid = (int)(i + part_id_start);
	    p = new(db, part::get_os_typespec())
		part(pid, new(db, employee::get_os_typespec())
		    employee(engineers[i]));
	    p->boundary_rep = new(db, brep::get_os_typespec()) brep(i);
	    parts |= p;
	    printf("db_pop4:     created part with id %d and engineer %s\n",
		   pid, engineers[i]);
	    printf("             with boundary_reps in os_database %s.\n", example_db4_name);
	}

        printf("db_pop4: creating parts database root\n");

	os_typespec parts_typespec("os_Collection<part*>");
	db->create_root("parts")->set_value(&parts, &parts_typespec);

        printf("db_pop4: ending transaction\n");

    OS_END_TXN(tx1)

    printf("db_pop4: closing database %s\n\n", example_db4_name);

    db->close();

    OS_END_FAULT_HANDLER

    objectstore::shutdown();

    return 0;
}

