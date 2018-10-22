#include <stdio.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/schmevol.hh>
#include <ostore/mop.hh>
#include "part3new.hh"
#include "dbname3.h"

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

    /* set the new data member values */
    epart * epart_ptr = (epart *)the_new_obj;
    epart_ptr->part_id = the_old_id_val;
    epart_ptr->responsible_engineer = (employee *)the_old_resp_eng_val;
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

    /* set the new data member values */
    mpart * mpart_ptr = (mpart *)the_new_obj;
    mpart_ptr->part_id = the_old_id_val;
    mpart_ptr->responsible_engineer = (employee *)the_old_resp_eng_val;
}

int main(int, char **)
{
    objectstore::initialize();
    os_collection::initialize();
    OS_ESTABLISH_FAULT_HANDLER

    /* associate epart_transform with the class epart */
    os_schema_evolution::augment_post_evol_transformers(
	os_transformer_binding("epart", epart_transform) );

    /* associate mpart_transform with the class mpart */
    os_schema_evolution::augment_post_evol_transformers(
	os_transformer_binding("mpart", mpart_transform) );

    /* perform the evolution process */
    os_schema_evolution::evolve(example_wdb3_name,example_db3_name);

    OS_END_FAULT_HANDLER

    objectstore::shutdown();

    return 0;
}

