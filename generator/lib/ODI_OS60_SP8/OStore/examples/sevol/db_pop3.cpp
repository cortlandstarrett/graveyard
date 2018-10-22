#include <stdio.h>
#include <stdlib.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include "part3pre.hh"
#include "dbname3.h"

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

/* A function to force vftable inclusion for collections templates */
void force_vfts (void*){
  force_vfts(new os_Array<cell*>);
  force_vfts(new os_Bag<cell*>);
  force_vfts(new os_Collection<cell*>);
  force_vfts(new os_List<cell*>);
  force_vfts(new os_Set<cell*>);

  force_vfts(new os_Array<brep*>);
  force_vfts(new os_Bag<brep*>);
  force_vfts(new os_Collection<brep*>);
  force_vfts(new os_List<brep*>);
  force_vfts(new os_Set<brep*>);
}

int main(int, char **)
{
    objectstore::initialize();
    os_collection::initialize();
    OS_ESTABLISH_FAULT_HANDLER

    printf("db_pop3: opening database %s\n", example_db3_name);

    os_database *db = os_database::create(example_db3_name);

    printf("db_pop3: beginning a transaction\n");

    OS_BEGIN_TXN(tx1, 0, os_transaction::update)

        printf("db_pop3: creating and populating eparts collection\n");

	os_Collection<epart*> &eparts =
	    os_Collection<epart*>::create(db, 0, 5);
	long part_id_start = 1000;
	int i;
	for (i = 0; i < 5; i++) {
	    int pid = (int)(i + part_id_start);
	    eparts |= new(db, epart::get_os_typespec())
		epart(pid, new(db, employee::get_os_typespec())
		    employee(engineers[i]));
	    printf("db_pop3:     created epart with id %d and engineer %s\n",
		   pid, engineers[i]);
	    printf("             in os_database %s.\n", example_db3_name);
	}

        printf("db_pop3: creating eparts database root\n");

	os_typespec eparts_typespec("os_Collection<epart*>");
	db->create_root("eparts")->set_value(&eparts, &eparts_typespec);

        printf("db_pop3: creating and populating mparts collection\n");

	os_Collection<mpart*> &mparts =
	    os_Collection<mpart*>::create(db, 0, 5);
	for (i = 5; i < 10; i++) {
	    int pid = (int)(i + part_id_start);
	    mparts |= new(db, mpart::get_os_typespec())
		mpart(pid, new(db, employee::get_os_typespec())
		    employee(engineers[i]));
	    printf("db_pop3:     created mpart with id %d and engineer %s\n",
		   pid, engineers[i]);
	    printf("             in os_database %s.\n", example_db3_name);
	}
	os_typespec mparts_typespec("os_Collection<mpart*>");

        printf("db_pop3: creating mparts database root\n");

	db->create_root("mparts")->set_value(&mparts, &mparts_typespec);

        printf("db_pop3: ending transaction\n");

    OS_END_TXN(tx1)

    printf("db_pop3: closing database %s\n\n", example_db3_name);

    db->close();

    OS_END_FAULT_HANDLER

    objectstore::shutdown();

    return 0;
}

