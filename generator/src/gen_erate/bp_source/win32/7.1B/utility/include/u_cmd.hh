/*========================================================================
 *
 * File:      $RCSfile: u_cmd.hh,v $
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
#ifndef U_CMD_HH
#define U_CMD_HH




#include <u_typdef.hh>




class String;




class U_shell_cmd

{
public:
		//  'exec_shell_cmd' returns the exit status from the
		//    shell command.
		//
    static int	exec_shell_cmd (const String& p_shell_cmd_str);


private:
};




#endif
