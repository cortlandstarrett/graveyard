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
  os_typespec *emp_type = new os_typespec("employee");

  printf("partinit: creating database %s\n", example_db_name);

  os_database *db1 = os_database::create(example_db_name);

  printf("partinit: beginning transaction\n");

  OS_BEGIN_TXN(tx1, 0, os_transaction::update)
    employee* an_employee = new(db1,emp_type) employee(1186);
    part *a_part = new(db1, part_type) part(111);
    a_part->responsible_engineer = an_employee;
    printf("partinit:   creating database root of type part, with engineer id 1186\n");
    db1->create_root("part_root")->set_value(a_part,part_type);
  OS_END_TXN(tx1)

  printf("partinit: finished transaction\n");

  db1->close();

  printf("partinit: closed database %s\n\n", example_db_name);

  OS_END_FAULT_HANDLER

  objectstore::shutdown();
  return 0;
}

