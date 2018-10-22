/*========================================================================
 *
 * File:      $RCSfile: sw_inst.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:05 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef SW_INST_HH
#define SW_INST_HH

#include <sg_inst.hh>

#include <u_string.hh>

#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#else
#include <u_typdef.hh>
#endif




class Object;
class D_sm_spt_pm;
class I_Object_Instance;
class I_Attribute_Instance;
class I_SM_Evt_Inst;
class I_SM_Evt_Supp_DI_Inst;




class W_inst_window : public W_inst_gui_drivers
{
public:
    virtual			~W_inst_window ();

    static void			show (Object* p_ooa_obj_ptr);
    static void			show (I_Object_Instance* p_ooa_obj_inst_ptr,I_SM_Evt_Inst* einst_ptr=0);
    static void         disposeAll();                 
    static t_boolean    MDA_is_displayed();   // i2844.2.5.1  added
        
    virtual W_inst_window*	get_inst_window_ptr () { return this; }
    				
    void			populate_einst_create_menu (D_sm_spt_pm* p_sm_spt_pm_ptr);
    void			populate_einst_create_creation_menu (Object* p_ooa_object_ptr);

    void			oinst_select (t_int p_row);
    void			oinst_deselect (t_int p_row);
    void			oinst_create ();
    void			oinst_delete ();

    void			ainst_select (t_int p_row);
    void			ainst_deselect (t_int p_row);
    void			ainst_apply ();
    void			ainst_reset ();


    void			einst_select (t_int p_row);
    void			einst_deselect (t_int p_row);
    void			einst_create (const Description& p_label_meaning_str);
    void			einst_create_creation (const Description& p_label_meaning_str);
    void			einst_delete ();
    void			einst_dequeue ();

    void			esdii_select (t_int p_row);
    void			esdii_deselect (t_int p_row);
    void			esdii_apply ();
    void			esdii_reset ();


	void			show_state_machine ();



private:
				W_inst_window (Object* p_ooa_obj_ptr);

    void			update_oinst_list ();
    void			update_ainst_list ();
    void			update_einst_list ();
    void			update_esdii_list ();

    virtual void		window_update__rerender ();
    virtual void		window_update__version (Id p_id);
    virtual void		window_update__processing_event ();

	t_boolean   AInst__set_value_enum( I_Attribute_Instance* p_ainst_ptr, vchar* p_value_char_ptr );
	t_boolean   EInst__set_value_enum( I_SM_Evt_Supp_DI_Inst* p_esdii_ptr, vchar* p_value_char_ptr );


    void			format_window_label ();

    static mc_dbms_List<W_inst_window*>
				*inst_window_collection_ptr;

    I_Object_Instance*		get_selected_oinst_ptr ();
    I_Attribute_Instance*	get_selected_ainst_ptr ();
    I_SM_Evt_Inst*		get_selected_einst_ptr ();
    I_SM_Evt_Supp_DI_Inst*	get_selected_esdii_ptr ();
};




#endif
