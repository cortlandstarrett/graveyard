#include <stdio.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include "part.hh"
#include "employee.hh"
#include "dbname.h"

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

  os_typespec *part_type = new os_typespec("part");

  printf("\ncoll_get: opening database %s\n", example_db_name);

  os_database *db1 = os_database::open(example_db_name);

  printf("coll_get: beginning a transaction\n");
  printf("coll_get: starting to retrieve objects from the database\n");

  OS_BEGIN_TXN(tx1, 0, os_transaction::update)

    /* retrieve the wheel */
    part *a_wheel = (part*) (db1->find_root("part_0")->get_value(part_type));

    printf("coll_get:   retrieved wheel - part number %d\n", a_wheel->part_number);

    /* traverse the components */
    part *p;
    os_Cursor<part*> c(a_wheel->children);
    for (p = c.first(); c.more(); p = c.next()) {
      printf("coll_get:   retrieved component - part number %d\n", p->part_number);
    }

    printf("coll_get: finished retrieving objects from the database\n");
    printf("coll_get: ending transaction\n");

  OS_END_TXN(tx1)

  printf("coll_get: closing database %s\n\n", example_db_name);

  db1->close();
  OS_END_FAULT_HANDLER

  objectstore::shutdown();
  return 0;
}

