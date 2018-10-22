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
  part *a_wheel, *a_rim, *a_spoke, *a_hub;
  part *a_flange, *an_axle;
  int i;

  os_typespec *part_type = new os_typespec("part");

  printf("\ncoll_put: creating database %s\n", example_db_name);

  os_database *db1 = os_database::create(example_db_name);

  printf("coll_put: beginning a transaction\n");
  printf("coll_put: starting to populate database\n");

  OS_BEGIN_TXN(tx1, 0, os_transaction::update)	

    printf("coll_put:   creating a wheel - part number 111\n");
    printf("coll_put:   starting to create wheel components\n");

    a_wheel = new(db1, part_type) part(111);
    db1->create_root("part_0")->set_value(a_wheel,part_type);

    printf("coll_put:     creating a rim - part number 211\n");

    a_rim = new(db1, part_type) part(211);
    a_wheel->children.insert(a_rim);

    for (i = 1; i <= 4; i++)
    {
      printf("coll_put:     creating a spoke - part number %d\n", 220+i);
      a_spoke = new(db1, part_type) part(220+i);
      a_wheel->children.insert(a_spoke);
    }

    printf("coll_put:     creating a hub - part number 231\n");

    a_hub = new(db1, part_type) part(231);
    a_wheel->children.insert(a_hub);

    printf("coll_put:     creating a flange - part number 311\n");

    a_flange = new(db1, part_type) part(311);
    a_wheel->children.insert(a_flange);

    printf("coll_put:     creating an axle - part number 321\n");

    an_axle = new(db1, part_type) part(321);
    a_wheel->children.insert(an_axle);

    printf("coll_put:   finished creating wheel components\n");
    printf("coll_put: finished populating database\n");
    printf("coll_put: ending transaction\n");

  OS_END_TXN(tx1)

  printf("coll_put: closing database %s\n\n", example_db_name);

  db1->close();
  OS_END_FAULT_HANDLER

  objectstore::shutdown();

  return 0;
}

