/*========================================================================
 *
 * File:      $RCSfile: u_fopen.hh,v $
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
#ifndef U_FOPEN_HH
#define U_FOPEN_HH

#include <vdialog.h>
#include <u_typdef.hh>

class U_file_open
{
public:
	
	static t_boolean load_ooa_file_win32 (vdialog* index_dialog, 
		char*& p_filepath, char*& p_filename);
	static t_boolean load_sim_file_win32 (vdialog* index_dialog, 
		char*& p_filepath, char*& p_filename);
	static t_boolean load_bak_file_win32 (vdialog* index_dialog, 
		char*& p_filepath, char*& p_filename);

};


#endif

