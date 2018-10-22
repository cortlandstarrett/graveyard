/*========================================================================
 *
 * File:      $RCSfile: sw_ctrl.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:13 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef SW_CTRL_HH
#define SW_CTRL_HH



#ifdef OLD_FILE_NAMES
#include <D_domain.hh>
#include <U_id.hh>
#else
#include <d_domain.hh>
#include <u_id.hh>
#endif

#include <u_string.hh>


class Object;
class W_window;
class I_Object_Instance;




enum t_control_type	{
	INDEX_WINDOW	= 0,
	ABOUT_WINDOW	= 1,
	SUPPORT_WINDOW	= 2
	};




class W_control
{
public:
    static void			insert_window (W_window*);
    static void			delete_window (W_window*);

    static t_boolean		get_all_window_quit ()
				    { return all_window_quit; }

    static Domain_id		get_id_of_domain_under_update ()
				    { return id_of_domain_under_update; }

    static void			all_window_update__rerender (Domain_id);
    static void			all_window_update__version (Domain_id, Id);
    static void			all_window_update__processing_event (Domain_id);
    static void			all_window_update__quit ();

    static void			show_dialog_window (Domain *);
    static void			show_dialog_window (Object *);

    static void			show_state_machine_window (I_Object_Instance*);

	
    static void			show_control_window (t_control_type, t_boolean);




private:
    static mc_dbms_List<W_window*>*
				window_collection_ptr;

    static Domain_id		id_of_domain_under_update;

    static t_boolean        	all_window_quit;
};




#endif
