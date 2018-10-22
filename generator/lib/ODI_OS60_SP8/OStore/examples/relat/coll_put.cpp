#include <stdio.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/relat.hh>
#include "employee.hh"
#include "part.hh"
#include "dbname.h"

os_Set<part*> *part_extent = 0;

int main(int, char **)
{
  objectstore::initialize();
  os_collection::initialize();
  OS_ESTABLISH_FAULT_HANDLER
  part *a_wheel, *a_rim, *a_spoke;
  part *a_hub, *a_flange, *an_axle;
  employee* an_emp;
  int i;

  os_typespec *part_type = part::get_os_typespec();
  os_typespec *emp_type = employee::get_os_typespec();
  os_typespec *extent_type = os_Set<part*>::get_os_typespec();

  printf("\ncoll_put: creating database %s\n", example_db_name);

  os_database *db = os_database::create(example_db_name);

  printf("coll_put: beginning a transaction\n");
  printf("coll_put: starting to populate database\n");

  OS_BEGIN_TXN(tx1, 0, os_transaction::update)
    part_extent = &os_Set<part*>::create(db);
    db->create_root("part_extent_root")->set_value(part_extent, extent_type);

    printf("coll_put:   creating an employee with id 1186\n");

    an_emp = new(db, emp_type) employee(1186);

    printf("coll_put:   creating a wheel - part number 111\n");
    printf("coll_put:   starting to create wheel components\n");

    a_wheel = new(db, part_type) part(111, an_emp);

    printf("coll_put:     creating a rim - part number 211\n");

    a_rim = new(db, part_type) part(211, an_emp);
    a_rim->parent = a_wheel;

    for (i=1; i<=4; i++)
    {
      printf("coll_put:     creating a spoke - part number %d\n", 220+i);
      a_spoke = new(db, part_type) part(220+i, an_emp);
      a_spoke->parent = a_wheel;
    }

    printf("coll_put:     creating a hub - part number 231\n");

    a_hub = new(db, part_type) part(231, an_emp);
    a_hub->parent = a_wheel;

    printf("coll_put:     creating a flange - part number 311\n");

    a_flange = new(db, part_type) part(311, an_emp);
    a_flange->parent = a_wheel;

    printf("coll_put:     creating an axle - part number 321\n");

    an_axle = new(db, part_type) part(321, an_emp);
    an_axle->parent = a_wheel;

    printf("coll_put:   finished creating wheel components\n");
    printf("coll_put: finished populating database\n");
    printf("coll_put: ending transaction\n");

  OS_END_TXN(tx1)

  printf("coll_put: closing database %s\n\n", example_db_name);

  db->close();

  OS_END_FAULT_HANDLER

  objectstore::shutdown();
  return 0;
}

