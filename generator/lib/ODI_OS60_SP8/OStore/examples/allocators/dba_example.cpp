#include <iostream.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>

void populate_rule_db(void);
void populate_alloc_db(void);

int main(int argc, void * argv[])
{
  objectstore::initialize();
  os_collection::initialize();

  OS_ESTABLISH_FAULT_HANDLER

  populate_rule_db();

  populate_alloc_db();

  OS_END_FAULT_HANDLER
  objectstore::shutdown();
  return 0;
}

