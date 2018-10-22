#include <stdio.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/schmevol.hh>
#include <ostore/mop.hh>
#include "part5new.hh"
#include "dbname5.h"

/* A function to force vftable inclusion for collections templates */
void force_vfts (void*){
  force_vfts(new os_Array<cell*>);
  force_vfts(new os_Bag<cell*>);
  force_vfts(new os_Collection<cell*>);
  force_vfts(new os_List<cell*>);
  force_vfts(new os_Set<cell*>);

  force_vfts(new os_Array<brep*>);
  force_vfts(new os_Bag<brep*>);
  force_vfts(new os_Collection<brep*>);
  force_vfts(new os_List<brep*>);
  force_vfts(new os_Set<brep*>);
}

static void my_illegal_pointer_handler(
    objectstore_exception_r exc, os_char_p explanation, os_void_p_r illegalp)
{
    if (& exc == & err_se_ambiguous_void_pointer) {
	os_path * member_path =
	    os_schema_evolution::get_path_to_member(illegalp);
	if (member_path) {
	    char * path_string =
		os_schema_evolution::path_name(* member_path);
	    if (strcmp(path_string, "epart::supplier.supplier_id") == 0 ||
		strcmp(path_string, "mpart::supplier.supplier_id") == 0) {
		/**
		 **	We know that these void * pointers in the pre
		 **	evolved world should be void * pointers to parts
		 **	in the post evolved world so we set the pointer
		 **	to the evolved object.
		 **/
		illegalp = (void *)
		    os_schema_evolution::get_evolved_address(illegalp);
		return;
	    }
	}
    }

    /* an unanticipated illegal pointer, signal the exception */
    exc.signal(explanation);
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

    /* get the old data member values */
    int the_old_id_val;
    os_fetch(the_old_obj, *c.find_member_variable("part_id"), the_old_id_val);
    os_void_p the_old_resp_eng_val;
    os_fetch(the_old_obj, *c.find_member_variable("responsible_engineer"),
	the_old_resp_eng_val);
    const os_base_class * the_old_supplier_base_class =
	c.find_base_class("supplier");
    void * the_old_supplier_base_class_ptr =
	os_fetch_address(the_old_obj, * the_old_supplier_base_class);
    int the_old_supplier_id_val;
    os_fetch(the_old_supplier_base_class_ptr,
	*the_old_supplier_base_class->get_class().find_member_variable("supplier_id"),
	the_old_supplier_id_val);

    /* set the new data member values */
    epart * epart_ptr = (epart *)the_new_obj;
    epart_ptr->part_id = the_old_id_val;
    epart_ptr->responsible_engineer = (employee *)the_old_resp_eng_val;
    epart_ptr->supplier_id = the_old_supplier_id_val;
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
    int the_old_id_val;
    os_fetch(the_old_obj, *c.find_member_variable("part_id"), the_old_id_val);
    os_void_p the_old_resp_eng_val;
    os_fetch(the_old_obj, *c.find_member_variable("responsible_engineer"),
	the_old_resp_eng_val);
    const os_base_class * the_old_supplier_base_class =
	c.find_base_class("supplier");
    void * the_old_supplier_base_class_ptr =
	os_fetch_address(the_old_obj, * the_old_supplier_base_class);
    int the_old_supplier_id_val;
    os_fetch(the_old_supplier_base_class_ptr,
	*the_old_supplier_base_class->get_class().find_member_variable("supplier_id"),
	the_old_supplier_id_val);

    /* set the new data member values */
    mpart * mpart_ptr = (mpart *)the_new_obj;
    mpart_ptr->part_id = the_old_id_val;
    mpart_ptr->responsible_engineer = (employee *)the_old_resp_eng_val;
    mpart_ptr->supplier_id = the_old_supplier_id_val;
}

int main(int, char **)
{
    objectstore::initialize();
    os_collection::initialize();
    OS_ESTABLISH_FAULT_HANDLER

    /* register the illegal pointer handler */
    os_schema_evolution::set_illegal_pointer_handler(
	my_illegal_pointer_handler
    );

    /* associate epart_transform with the class epart */
    os_schema_evolution::augment_post_evol_transformers(
	os_transformer_binding("epart", epart_transform)
    );

    /* associate mpart_transform with the class mpart */
    os_schema_evolution::augment_post_evol_transformers(
	os_transformer_binding("mpart", mpart_transform)
    );

    /* perform the evolution process */
    os_schema_evolution::evolve(example_wdb5_name, example_db5_name);

    OS_END_FAULT_HANDLER

    objectstore::shutdown();

    return 0;
}

