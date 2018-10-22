/*========================================================================
 *
 * File:      $RCSfile: u_config.hh,v $
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
#include <mc_dbms/mc_dbms.hh>

#ifndef U_CONFIG_HH
#define U_CONFIG_HH

// Include those header files that are DIRECTLY needed by this one.


// #include "u_typdef.hh"
#include "u_id.hh"


//
// CLASS: U_config
//
// DESCRIPTION:
//
// REMARKS:
//

class U_config
{
public:
  static t_uint get_next_config_id()
      { return ++config_id; }

private:

  static t_uint config_id;
};


#endif
