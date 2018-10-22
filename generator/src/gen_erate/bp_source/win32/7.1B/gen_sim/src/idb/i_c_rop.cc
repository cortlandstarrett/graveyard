/*========================================================================
 *
 * File:      $RCSfile: i_c_rop.cc,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:36 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifdef OLD_FILE_NAMES
#include <L_log_trace.hh>
#include <L_log_error.hh>
#include <DBU_utility.hh>
#else
#include <u_trace.hh>
#include <u_error.hh>
#include <u_util.hh>
#endif


#include <i_c_rop.hh>





I_Chain_Rel_Obj_Pair *
I_Chain_Rel_Obj_Pair::create (mc_dbms_database* p_db_ptr,
    int p_ONE_side_is_conditional, int p_ONE_side_is_many,
    int p_OTH_side_is_conditional, int p_OTH_side_is_many)

{
    LOG_TRACE (L_D_DATA, L_FUNCTION_BEGIN, (L_log_string,
	"Entered I_Chain_Rel_Obj_Pair::create ()"));


    I_Chain_Rel_Obj_Pair* ptr
	= new (p_db_ptr, I_Chain_Rel_Obj_Pair::get_mc_dbms_typespec ())
	I_Chain_Rel_Obj_Pair (p_ONE_side_is_conditional, p_ONE_side_is_many,
	    p_OTH_side_is_conditional, p_OTH_side_is_many );


    LOG_TRACE (L_D_DATA, L_FUNCTION_END, (L_log_string,
	"Exitted I_Chain_Rel_Obj_Pair::create ()"));
    return (ptr);
}


I_Chain_Rel_Obj_Pair::I_Chain_Rel_Obj_Pair (
		int p_ONE_side_is_conditional,
		int p_ONE_side_is_many,
		int p_OTH_side_is_conditional,
		int p_OTH_side_is_many )
		:
		I_Related_Object_Pair( p_ONE_side_is_conditional, p_ONE_side_is_many, p_OTH_side_is_conditional, p_OTH_side_is_many )
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Chain_Rel_Obj_Pair::I_Chain_Rel_Obj_Pair()" ));


LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Chain_Rel_Obj_Pair::I_Chain_Rel_Obj_Pair()" ));

}


I_Chain_Rel_Obj_Pair::~I_Chain_Rel_Obj_Pair ()
{

LOG_TRACE( L_D_DATA, L_FUNCTION_BEGIN,
	( L_log_string, "Entered I_Chain_Rel_Obj_Pair::~I_Chain_Rel_Obj_Pair()" ));


operator delete( this, ""); // Remove from InstanceTracker

LOG_TRACE( L_D_DATA, L_FUNCTION_END,
	( L_log_string, "Exitted I_Chain_Rel_Obj_Pair::~I_Chain_Rel_Obj_Pair()" ));

}
