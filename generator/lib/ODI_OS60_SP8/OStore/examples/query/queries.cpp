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

int contains(os_collection * coll, void * p)
{
   return coll->contains(p);
}

int main(int, char **)
{
  objectstore::initialize();
  os_collection::initialize();
  OS_ESTABLISH_FAULT_HANDLER
  os_Set<part*> &selected_parts =
      os_Set<part*>::create(os_database::get_transient_database ());
  part *p;

  os_typespec *extent_type = os_Set<part*>::get_os_typespec();

  printf("\nqueries: opening database %s\n", example_db_name);

  os_database *db = os_database::open(example_db_name);

  printf("queries: beginning a transaction\n");
  printf("queries: starting to retrieve objects from the database\n");

  OS_BEGIN_TXN(tx1, 0, os_transaction::update)
    part_extent = (os_Set<part*>*) (db->find_root("part_extent_root")->get_value(extent_type));

    printf("queries:   retrieved set of parts\n");
    printf("queries:   querying set to find parts with responsible_engineer->emp_id == 1186\n");

    selected_parts =
      part_extent->query((char*)"part*",(char*)"responsible_engineer->emp_id == 1186",db);

    printf("queries:   parts for which engineer 1186 is responsible:\n");

    os_Cursor<part*> c(selected_parts);	
    for (p = c.first(); p; p = c.next())
      printf("queries:     part #%d\n", p->part_number);

    printf("queries:   querying set to find primitive parts\n");

    selected_parts = part_extent->query((char*)"part*",
					(char*)"!children[:1:]", db);

    printf("queries:   primitive parts in \'query.db\':\n");
    for (p = c.first();	p; p = c.next())
      printf("queries:      part #%d\n", p->part_number);

    printf("queries:   querying set to find primitive children of part #111\n");

    selected_parts =
      part_extent->query_pick((char*)"part*", (char*)"part_number==111", db)
	->children.query((char*)"part*", (char*)"!children[:1:]", db);

    printf("queries:   primitive children of part #111:\n");
    for (p = c.first(); p; p = c.next())
      printf("queries:      part #%d\n", p->part_number);

    printf("queries:   querying set to find parents of part #211\n");

    selected_parts =
      part_extent->query((char*)"part*",
                         (char*)"children[:part_number==211:]",
			 db);

    printf("queries:   parents of part #211:\n");
    for(p = (part*)c.first(); p; p = (part*)c.next())
        printf("queries:      part #%d\n", p->part_number);

    printf("queries:   finished retrieving objects from the database\n");

  OS_END_TXN(tx1)

  db->close();

  printf("queries: closed database %s\n\n", example_db_name);

  OS_END_FAULT_HANDLER

  objectstore::shutdown();
  return 0;
}

