/*========================================================================
 *
 * File:      $RCSfile: u_mc_dbms.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:33 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_STORE_HH
#define U_STORE_HH

class MCDBMSInit
{
  public:
	static void start_initialization(const char *app_name);

	static int ok_to_initialize()
	{ return _ok_to_initialize; }

private:

	MCDBMSInit();   // prevent accidental creations
	~MCDBMSInit();

	static int _initialized;
    static int _ok_to_initialize;
    
};


#endif
