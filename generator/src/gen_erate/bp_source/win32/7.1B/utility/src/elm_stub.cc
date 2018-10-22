/*========================================================================
 *
 * File:      $RCSfile: elm_stub.cc,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:59 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */

void LM_license::set_heartbeat()
{
}

LM_license::LM_RETCODE LM_license::get_license(char *featname, int p_log_report)
{
	if ( featname ) ;   // avoid unreferenced parameter warnings
	if ( p_log_report ) ;   // avoid unreferenced parameter warnings
	return LM_OK;
}

LM_license::LM_RETCODE LM_license::connect_to_LM_server(void)
{
	return LM_OK;
}
