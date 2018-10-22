#include <stdio.h>
#include <ostore/ostore.hh>
#include "part.hh"
#include "employee.hh"
#include "dbname.h"

int main(int, char **)
{
  objectstore::initialize();
  OS_ESTABLISH_FAULT_HANDLER
  os_typespec *part_type = new os_typespec("part");

  printf("empretr: opening database %s\n", example_db_name);

  os_database *db1 = os_database::open(example_db_name);

  printf("empretr: beginning transaction\n");

  OS_BEGIN_TXN(tx1, 0, os_transaction::update)	
    part *a_part = (part*) (db1->find_root("part_root")->get_value(part_type));
    printf("empretr: retrieving part from database root\n");
    printf("empretr:   the part has an engineer of id %d\n", a_part->responsible_engineer->emp_id);
  OS_END_TXN(tx1)

  printf("empretr: finished transaction\n");

  db1->close();

  printf("empretr: closed database %s\n\n", example_db_name);

  OS_END_FAULT_HANDLER

  objectstore::shutdown();
  return 0;
}

