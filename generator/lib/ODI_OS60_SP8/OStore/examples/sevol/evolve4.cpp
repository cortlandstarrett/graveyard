#include <stdio.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/schmevol.hh>
#include <ostore/mop.hh>
#include "part4new.hh"
#include "dbname4.h"

static os_char_p part_reclassifier(os_typed_pointer_void_const_r old_obj_typed_ptr)
{
    void * the_old_obj = old_obj_typed_ptr;
    const os_class_type &c = old_obj_typed_ptr.get_type();
    os_void_p the_prev_ptr_value = 0;
    os_fetch(the_old_obj, *c.find_member_variable("cells"), the_prev_ptr_value);
    if (the_prev_ptr_value)
	return (char*)"epart";
    os_fetch(the_old_obj, *c.find_member_variable("boundary_rep"), the_prev_ptr_value);
    if (the_prev_ptr_value)
	return (char*)"mpart";
    return (char *)0;
}

static void epart_transform(os_void_p the_new_obj)
{
    /* get a typed pointer to the old object */
    os_typed_pointer_void old_obj_typed_ptr =
	os_schema_evolution::get_unevolved_object(the_new_obj);

    /* get a void * ponter to the old object */
    void * the_old_obj = old_obj_typed_ptr;

    /* get the type of the old object */
    const os_class_type &c = old_obj_typed_ptr.get_type();

    /* get the old data member value */
    os_void_p the_old_cells_val;
    os_fetch(the_old_obj, *c.find_member_variable("cells"), the_old_cells_val);

    /* set the new data member values */
    ((epart *)the_new_obj)->cells = (os_Collection<cell*>*)the_old_cells_val;
}

static void mpart_transform(os_void_p the_new_obj)
{
    /* get a typed pointer to the old object */
    os_typed_pointer_void old_obj_typed_ptr =
	os_schema_evolution::get_unevolved_object(the_new_obj);

    /* get a void * ponter to the old object */
    void * the_old_obj = old_obj_typed_ptr;

    /* get the type of the old object */
    const os_class_type &c = old_obj_typed_ptr.get_type();

    /* get the old data member values */
    os_void_p the_old_brep_val;
    os_fetch(the_old_obj, *c.find_member_variable("boundary_rep"),
	the_old_brep_val);

    /* set the new data member values */
    ((mpart *)the_new_obj)->boundary_rep = (brep *)the_old_brep_val;
}

int main(int, char **)
{
    objectstore::initialize();
    os_collection::initialize();
    OS_ESTABLISH_FAULT_HANDLER

    /* associate part_reclassifier() with the class part */
    os_schema_evolution::augment_subtype_selectors(
	os_evolve_subtype_fun_binding("part", part_reclassifier));

    /* associate epart_transform with the class epart */
    os_schema_evolution::augment_post_evol_transformers(
	os_transformer_binding("epart", epart_transform) );

    /* associate mpart_transform with the class mpart */
    os_schema_evolution::augment_post_evol_transformers(
	os_transformer_binding("mpart", mpart_transform) );

    /* perform the evolution process */
    os_schema_evolution::evolve(example_wdb4_name,example_db4_name);

    OS_END_FAULT_HANDLER

    objectstore::shutdown();

    return 0;
}

