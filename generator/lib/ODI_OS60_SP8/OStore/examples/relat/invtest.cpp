#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/relat.hh>
#include <stdio.h>
#include "employee.hh"
#include "part.hh"
#include "dbname.h"

os_database *db = 0;

os_Set<part*> *part_extent = 0;

int main(int , char **argv)
{
  objectstore::initialize();
  os_collection::initialize();
  OS_ESTABLISH_FAULT_HANDLER

  printf("\ninvtest: opening database %s\n", example_db_name);

  db = os_database::open(example_db_name);

  os_typespec *extent_type = os_Set<part*>::get_os_typespec();

  printf("invtest: beginning a transaction\n");
  printf("invtest: starting to retrieve objects from the database\n");

  OS_BEGIN_TXN(tx1,0,os_transaction::update)
    part *the_wheel, *a_rim, *p;
    part_extent = (os_Set<part*>*)
      (db->find_root("part_extent_root")->get_value(extent_type));

    printf("invtest:   retrieved set of parts\n");
    printf("invtest:   querying for wheel with part number 111\n");

    the_wheel = (part*)part_extent->query_pick((char*)"part*",
					       (char*)"part_number==111");

    printf("invtest:   wheel found, querying for rim with part number 211\n");

    a_rim = (part*)the_wheel->children.query_pick((char*)"part*",
						  (char*)"part_number==211");

    printf("invtest:   removing the rim from the wheel's children\n");

    the_wheel->children.remove(a_rim);
    if (a_rim && a_rim->parent == 0)
       printf("invtest:   the rim now has no parent\n");

    printf("invtest:   deleting first spoke of wheel\n");

    delete(the_wheel->children.query_pick((char*)"part*",
					  (char*)"part_number==221"));

    printf("invtest:   the_wheel's children are now:\n");

    os_Cursor<part*> cur(the_wheel->children.getvalue());
    for (p = (part*)cur.first(); p; p = (part*)cur.next())
      printf("invtest:     part number %d\n", p->part_number);

    printf("invtest:   finished retrieving objects from the database\n");

  OS_END_TXN(tx1)

  db->close();

  printf("invtest: closed database %s\n\n", example_db_name);

  OS_END_FAULT_HANDLER

  objectstore::shutdown();
  return 0;
}

