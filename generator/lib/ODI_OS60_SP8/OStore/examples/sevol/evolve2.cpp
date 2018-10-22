#include <stdio.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/schmevol.hh>
#include <ostore/mop.hh>
#include "part2new.hh"
#include "dbname2.h"

static void part_transform(os_void_p the_new_obj)
{
    /* get a typed pointer to the old object */
    os_typed_pointer_void old_obj_typed_ptr =
	os_schema_evolution::get_unevolved_object(the_new_obj);

    /* get a void * ponter to the old object */
    void * the_old_obj = old_obj_typed_ptr;

    /* get the type of the old object */
    const os_class_type &c = old_obj_typed_ptr.get_type();

    /* get the old data member value */
    int the_old_val;
    os_fetch(the_old_obj, *c.find_member_variable("part_id"), the_old_val);

    /* convert the old value to string form */
    char conv_buf[16];
    sprintf(conv_buf, "%d", the_old_val);

    int len = strlen(conv_buf) + 1;
    part * part_ptr = (part *)the_new_obj;
    part_ptr->part_id =
	new(os_cluster::with(the_new_obj), os_typespec::get_char(), len) char[len];
    strcpy(part_ptr->part_id, conv_buf);
}

int main(int, char **)
{
    objectstore::initialize();
    os_collection::initialize();
    OS_ESTABLISH_FAULT_HANDLER

    /* associate part_transform with the class part */
    os_schema_evolution::augment_post_evol_transformers(
	os_transformer_binding("part", part_transform) );

    /* initiate evolution */
    os_schema_evolution::evolve(example_wdb2_name,example_db2_name);

    OS_END_FAULT_HANDLER

    objectstore::shutdown();

    return 0;
}

