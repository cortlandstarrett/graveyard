#include <stdio.h>
#include <ostore/ostore.hh>
#include "dbname.h"

int main(int, char **)
{
  objectstore::initialize();
  OS_ESTABLISH_FAULT_HANDLER
  os_typespec *int_type = os_typespec::get_signed_int();

  printf("hello2: opening database %s\n", example_db_name);

  os_database *db1 = os_database::open(example_db_name);

  printf("hello2: beginning transaction\n");

  OS_BEGIN_TXN(tx1, 0, os_transaction::update)
    os_database_root *a_root = db1->find_root("count");
    int *countp = (int*) (a_root->get_value(int_type));
    printf("hello2:   hello, world.\n");
    printf("hello2:   the counter is now %d\n",*countp);
    ++*countp;
    printf("hello2:   incremented counter to %d\n",*countp);
  OS_END_TXN(tx1)

  printf("hello2: finished transaction\n");

  db1->close();

  printf("hello2: closed database %s\n\n", example_db_name);

  OS_END_FAULT_HANDLER

  objectstore::shutdown();
  return 0;
}

