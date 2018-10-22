/*========================================================================
 *
 * File:      $RCSfile: sw_synch.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:07 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef SW_SYNCH_HH
#define SW_SYNCH_HH

#include <sg_synch.hh>

#include <u_string.hh>

#include <u_typdef.hh>




class Domain;
class D_synchronous_service;
class D_synchronous_service_parm;




class W_synch_service_window : public W_synch_service_gui_drivers
{
public:
    virtual			~W_synch_service_window ();

    static void			show (Domain* p_ooa_domain_ptr);

    virtual W_synch_service_window*	get_synch_service_window_ptr () { return this; }
    				
    void			synch_select (t_int p_row);
    void			synch_deselect (t_int p_row);

    void			parm_select (t_int p_row);
    void			parm_deselect (t_int p_row);
    void			parm_apply ();
    void			parm_reset ();

    void			invoke ();
    void			invoke_dequeue ();


private:
				W_synch_service_window (Domain* p_ooa_domain_ptr);

    void			update_synch_service_list ();
    void			update_parm_list ();

    virtual void		window_update__rerender ();
    virtual void		window_update__version (Id p_id);
    virtual void		window_update__processing_event ();

    void			format_window_label ();
	
    static W_synch_service_window* synch_service_window_ptr;

    int get_selected_synch_service_row(const Id&);
    D_synchronous_service*		get_selected_synch_service_ptr ();
    D_synchronous_service_parm*		get_selected_parm_ptr ();
	int			get_selected_parm_index();

};




#endif
