/*========================================================================
 *
 * File:      $RCSfile: u_util.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef U_UTIL_HH
#define U_UTIL_HH



#include "u_id.hh"
#include "u_string.hh"




extern String String_default;




inline
unsigned int
assign_next_id_value (mc_dbms_database* p_db_ptr)

{
    Id_assigner* id_assigner_ptr;
    mc_dbms_database_root* root_ptr = p_db_ptr->find_root ("Id_assigner");

    if (root_ptr)
    {
	id_assigner_ptr = (Id_assigner*) root_ptr->get_value ();
    }
    else
    {
	mc_dbms_typespec* id_assigner_type = new mc_dbms_typespec ("Id_assigner",sizeof(Id_assigner));
	id_assigner_ptr
	    = new (p_db_ptr, id_assigner_type) Id_assigner (0,0,0,0);

	p_db_ptr->create_root ("Id_assigner")->set_value (id_assigner_ptr);
    }

    Id new_id = id_assigner_ptr->assign_next_id ();

    return (new_id.get_entire_value ());
}




#endif
