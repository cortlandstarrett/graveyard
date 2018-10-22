#include <stdio.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include "part.hh"
#include "employee.hh"
#include "dbname.h"

os_Set<part*> *part_extent = 0;

/* A function to force vftable inclusion for collections templates */
void force_vfts (void*){
  force_vfts(new os_Array<part*>);
  force_vfts(new os_Bag<part*>);
  force_vfts(new os_Collection<part*>);
  force_vfts(new os_List<part*>);
  force_vfts(new os_Set<part*>);
}

int main(int, char **)
{
  objectstore::initialize();
  os_collection::initialize();
  OS_ESTABLISH_FAULT_HANDLER
  part *a_wheel;
      
  os_typespec *extent_type = os_Set<part*>::get_os_typespec();

  printf("\ncoll_get: opening database %s\n", example_db_name);

  os_database *db2 = os_database::open(example_db_name);

  printf("coll_get: beginning a transaction\n");
  printf("coll_get: starting to retrieve objects from the database\n");

  OS_BEGIN_TXN(tx1, 0, os_transaction::update)

    /* retrieve the entry point */
    part_extent = (os_Set<part*>*) (db2->find_root("part_extent_root")->get_value(extent_type));

    printf("coll_get:   retrieved set of parts\n");
    printf("coll_get:   querying set to find part with number 111\n");

    /* query */
    a_wheel = part_extent->query_pick((char*)"part*", (char*)"part_number == 111", db2);

    /* traversal */
    printf("coll_get: The wheel's children are:\n");
    os_Cursor<part*> c(a_wheel->children);
    for (part *p = c.first(); p; p = c.next())
      printf("coll_get:    part number %d\n", p->part_number);

    printf("coll_get: finished retrieving objects from the database\n");
    printf("coll_get: ending transaction\n");

  OS_END_TXN(tx1)

  printf("coll_get: closing database %s\n\n", example_db_name);

  db2->close();

  OS_END_FAULT_HANDLER

  objectstore::shutdown();
  return 0;
}

