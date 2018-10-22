/*========================================================================
 *
 * File:      $RCSfile: i_relate.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:17 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef I_RELATE_HH
#define I_RELATE_HH

#include <u_typdef.hh>


class I_Object_Instance;
class I_Related_Object_Pair;
class GS_string;
class Description;



class I_relate

{
public:
    static t_boolean    relate_object_instance
			    (I_Object_Instance* p_start_oinst_ptr,
			     const Description& p_end_obj_key_letter_str,
			     const Description& p_Rnum_str,
			     const Description& p_rel_direction_str);


	static void clear_related_flag
			    (I_Object_Instance* p_oinst_ptr);
			
private:
    enum e_start_type	{REF_SIDE,ID_SIDE};
    static t_boolean    relate_object_instance
			    (I_Object_Instance* p_oinst_ptr,
			    I_Related_Object_Pair* p_rop_ptr,
			    e_start_type p_start_side);
};




#endif
