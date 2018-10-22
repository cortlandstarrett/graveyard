/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_LOG_CONSTANTS_HH_
#define _CMTL_INTERFACE_LOG_CONSTANTS_HH_

// CMTL Logging constant definitions

enum os_log_constants {

  /**
   * NONE indicates that no logging should be done.  All error communication
   * will be done through exceptions.
   */
  cmtl_log_none = 0,

  /**
   * ERROR indicates that a significant problem was encountered which 
   * probably requires some level of attention and which may prevent 
   * work from continuing.
   */
  cmtl_log_error = 1,

  /**
   * WARNING indicates that a problem was encountered which may be
   * of interest to an administrator or developer, but which doesn't
   * prevent work from continuing at all.
   */
  cmtl_log_warning = 2,

  /**
   * STATUS indicates that a major event has occurred which may be of interest
   * to an administrator in monitoring a cache manager.
   */
  cmtl_log_status = 3,

  /**
   * VERBOSE indicates that a minor event has occurred which may be
   * of interest to an administrator in monitoring a cache manager.
   */
  cmtl_log_verbose = 4,

  /**
   * DEBUG indicates that information is useful for debugging an
   * unexplained problem.
   */
  cmtl_log_debug = 5,

  os_log_constants_enum_pad = 1<<30
};

#endif // end of #ifndef _CMTL_INTERFACE_LOG_CONSTANTS_HH_

