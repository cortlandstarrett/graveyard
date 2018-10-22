/*========================================================================
 *
 * File:      $RCSfile: sv_com.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:04 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef SV_COMMON_HH
#define SV_COMMON_HH


#ifdef OLD_FILE_NAMES
#include <U_typedefs.hh>
#include <L_log_error.hh>
#include <D_domain_id.hh>
#include <D_invocation.hh>
#else
#include <u_typdef.hh>
#include <u_error.hh>
#include <d_domid.hh>
#include <d_invoct.hh>
#endif

#include <sw_ctrl.hh>




class W_stubs_begin_end
{
public:
    static void		handle_exception (Domain_id);


    static void		begin_update_processing ();
    static void		end_update_processing ();

    static void		begin_read_only_processing ();
    static void		end_read_only_processing ();

    static void		begin_no_txn_processing ();
    static void		end_no_txn_processing ();

    static void		begin_mouse_event_processing ();
    static void		end_mouse_event_processing ();

	static t_boolean exception_occurred;
	static Description error_message;

};

#endif
//
// Formatting information for emacs
//
// Local Variables:
// tab-width:4
// End:
//
