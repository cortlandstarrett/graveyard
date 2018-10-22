#include <stdio.h>
#include <ostore/ostore.hh>
#include "dbname.h"

int main(int, char **)
{
  objectstore::initialize();
  OS_ESTABLISH_FAULT_HANDLER
  os_typespec *int_type = os_typespec::get_signed_int();

  printf("cntinit: creating database %s\n", example_db_name);

  os_database *db1 = os_database::create(example_db_name);

  printf("cntinit: beginning transaction\n");

  OS_BEGIN_TXN(tx1, 0, os_transaction::update)
    int *countp = new(db1, int_type) int(0);
    printf("cntinit:   creating database root\n");
    db1->create_root("count")->set_value(countp,int_type);
    printf("cntinit:   initializing count to %d\n", *countp);
  OS_END_TXN(tx1)

  printf("cntinit: finished transaction\n");

  db1->close();

  printf("cntinit: closed database %s\n\n", example_db_name);

  OS_END_FAULT_HANDLER

  objectstore::shutdown();
  return 0;
}

