/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_TXN_SYNCH 
#define _CMTL_INTERFACE_TXN_SYNCH 1

#include <ostore/cmtl/common.hh>

// CMTL transaction synchronization
//

class _OS_DLLIMPORT(_OS_CMTL) os_transaction_synch {

public:					/* public static member functions */

  /**
   * The after_begin method notifies the implementer of this interface
   * that a new transaction has started.
   */
  virtual void after_begin() = 0;

  /**
   * The before_completion method notifies the implementer of this interface
   * that a transaction is about to commit or checkpoint.
   */
  virtual void before_completion() = 0;

  /**
   * The afterCompletion method notifies the implementer of this interface
   * that a transaction has completed, either via a commit or an abort.
   */
  virtual void after_completion(const os_boolean committed) = 0;

};

#endif /* _CMTL_INTERFACE_TXN_SYNCH */


