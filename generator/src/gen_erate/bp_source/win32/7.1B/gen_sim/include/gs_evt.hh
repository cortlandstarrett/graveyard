/*========================================================================
 *
 * File:      $RCSfile: gs_evt.hh,v $
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
#ifndef GS_EVT_HH
#define GS_EVT_HH


#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#else
#include <u_typdef.hh>
#endif


#include <gs_stack.hh>


class GS_string;
class Id;
class GS_sim_evt;
class GS_sim_obj;
class GS_sim_audit;
class GS_sim_bridge;
class GS_stack;
class I_SM_Evt;
class I_SM_Evt_Inst;
class I_SM_Evt_Supp_DI;
class I_SM_Evt_Supp_DI_Inst;
class I_Object_Instance;
class D_sm_event_data_item;
class D_sm_event;
class SIM_SOR;


class GS_sim_evt
{
friend GS_sim_obj;
friend GS_sim_audit;
friend GS_sim_bridge;
friend SIM_SOR;


public:
    static I_SM_Evt_Inst*
			user_request__create
			    (const Description& p_label_meaning_str,
			    I_Object_Instance* p_dest_oinst_ptr,
				const Id& p_obj_id);
    static t_boolean	user_request__delete (I_SM_Evt_Inst* p_einst_ptr);




private:
    static I_SM_Evt_Inst*	create__I_SM_Evt_Inst (const Id& p_evt_id);
    static I_SM_Evt*		create__I_SM_Evt (const Id& p_evt_id);
    static D_sm_event*		audit__I_SM_Evt (I_SM_Evt* p_sim_evt_ptr);
    static t_boolean		delete__I_SM_Evt (I_SM_Evt* p_sim_evt_ptr);
    static t_boolean		match_sim_esdi_to_ooa_esdi
				    (I_SM_Evt_Supp_DI* p_sim_esdi_ptr,
				    D_sm_event_data_item* p_ooa_esdi_ptr);

    static t_boolean		set_esdii_initial_value
				    (I_SM_Evt_Supp_DI_Inst* p_esdii_ptr);
    static t_boolean		add_all_esdii_for_new_esdi
				    (I_SM_Evt_Supp_DI* p_esdi_ptr,
				    t_uint p_esdi_position);
};




#endif
