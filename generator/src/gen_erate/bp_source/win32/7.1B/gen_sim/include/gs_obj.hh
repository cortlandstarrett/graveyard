/*========================================================================
 *
 * File:      $RCSfile: gs_obj.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:16 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef GS_OBJ_HH
#define GS_OBJ_HH

#include <u_typdef.hh>


class GS_string;
class GS_sim_audit;
class GS_sim_action;
class Id;
class I_Object;
class I_Object_Instance;
class I_Attribute;
class I_Attribute_Instance;
class I_Related_Object_Instance_Pair;
class Relationship;
class Object;
class Attribute;
class SIM_SOR;
class Description;


class GS_sim_obj

{
friend GS_sim_audit;
friend GS_sim_action;
friend SIM_SOR;

public:
    static I_Object_Instance*
			user_request__create   (const Id& p_obj_id);
    static t_boolean	user_request__delete   (I_Object_Instance* p_oinst_ptr);


    static t_boolean	interpret_stmt__create   (const GS_string& p_stmt_str);
    static t_boolean	interpret_stmt__delete   (const GS_string& p_stmt_str);
    static t_boolean	interpret_stmt__relate   (const GS_string& p_stmt_str);
    static t_boolean	interpret_stmt__unrelate (const GS_string& p_stmt_str);

    static t_boolean	audit__all_Assigners ();

    static t_boolean	set_rel_phrases (I_Related_Object_Instance_Pair*,
			    Relationship* p_ooa_rel_ptr);

    static I_Object*	create__I_Object (const Description& p_obj_key_lett_str);




private:
    static I_Object_Instance*	create__I_Object_Instance (const Id& p_obj_id);
    static t_boolean		delete__I_Object_Instance
				    (I_Object_Instance* p_oinst_ptr,
				    t_boolean p_delete__I_Object__flag = TRUE);
    static I_Object*		create__I_Object (const Id& p_obj_id);
    static Object*		audit__I_Object (I_Object* p_sim_obj_ptr);
    static t_boolean		delete__I_Object (I_Object* p_sim_obj_ptr);
    static t_boolean		match_sim_attr_to_ooa_attr
				    (I_Attribute* p_sim_attr_ptr,
				    Attribute* p_ooa_attr_ptr,
				    t_uint p_primary_obj_id_id);
    static t_boolean		set_ainst_initial_value
				    (I_Attribute_Instance* p_ainst_ptr);
    static t_boolean		add_all_ainst_for_new_attr
				    (I_Attribute* p_sim_attr_ptr,
				    t_uint p_attr_position);
};




#endif
