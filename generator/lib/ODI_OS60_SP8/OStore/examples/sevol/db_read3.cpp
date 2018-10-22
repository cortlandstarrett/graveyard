#include <stdlib.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include "part3new.hh"
#include "dbname3.h"

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

    printf("db_read3: opening database %s\n", example_db3_name);

    os_database *db = os_database::open(example_db3_name);

    printf("db_read3: beginning a transaction\n");

    OS_BEGIN_TXN(tx1, 0, os_transaction::update)

        printf("db_read3: finding eparts database root\n");

	os_database_root * parts_root = os_database_root::find("eparts", db);
	os_typespec eparts_typespec("os_Collection<epart*>");

        printf("db_read3: walking through eparts collection\n");

	os_Collection<epart*> &eparts =
	    *(os_Collection<epart*>*) parts_root->get_value(&eparts_typespec);
        os_index_path& eip = os_index_path::create("epart*","part_id", db);
        os_Cursor<epart*> ecursor(eparts, eip);
	for (epart * ep = ecursor.first(); ecursor.more(); ep = ecursor.next()) {
	    printf("db_read3: Found epart with id %d and engineer %s\n", ep->part_id,
		   ep->responsible_engineer->name);
	    printf("          in os_database %s.\n", example_db3_name);
	}
        delete (os_index_path*)&eip;

        printf("db_read3: finding mparts database root\n");

	parts_root = os_database_root::find("mparts", db);
	os_typespec mparts_typespec("os_Collection<mpart*>");

        printf("db_read3: walking through mparts collection\n");

	os_Collection<mpart*> &mparts =
	    *(os_Collection<mpart*>*) parts_root->get_value(&mparts_typespec);
        os_index_path& mip = os_index_path::create("mpart*","part_id", db);
        os_Cursor<mpart*> mcursor(mparts, mip);
	for (mpart * mp = mcursor.first(); mcursor.more(); mp = mcursor.next()) {
	    printf("db_read3: Found mpart with id %d and engineer %s\n", mp->part_id,
		   mp->responsible_engineer->name);
	    printf("          in os_database %s.\n", example_db3_name);
	}
        delete (os_index_path*)&mip;

    printf("db_read3: ending transaction\n");

    OS_END_TXN(tx1)

    printf("db_read3: closing database %s\n\n", example_db3_name);

    db->close();

    OS_END_FAULT_HANDLER

    objectstore::shutdown();

    return 0;
}

