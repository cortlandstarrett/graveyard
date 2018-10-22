/*========================================================================
 *
 * File:      $RCSfile: sv_synch.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:12 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef SV_SYNCH_HH
#define SV_SYNCH_HH

#include <vcommand.h>
#include <vdialog.h>
#include <vlistitem.h>
#include <vtextitem.h>

void W_gui_vr_set_command_space (vwindow *, vcommandFunctionTemplate *, int);
 int W_synch_service_vr_number_of_commands ();

 int W_synch_service_vr_close_hook (vdialog *, vevent *);
void W_synch_service_vr_synch_service_notify (vlistitem *, vevent *);
void W_synch_service_vr_parameter_list_notify (vlistitem *, vevent *);
void W_synch_service_vr_parameter_value_notify(vtextitem *textitem,vevent * event, int message);

extern vcommandFunctionTemplate Synch_Cmds [];

#endif
