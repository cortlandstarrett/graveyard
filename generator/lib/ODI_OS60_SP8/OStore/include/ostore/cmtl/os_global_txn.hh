/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_GLOBAL_TRANSACTION
#define _CMTL_INTERFACE_GLOBAL_TRANSACTION 1

#include <ostore/cmtl/os_txn_ctx.hh>
#include <ostore/portypes.hh>

/*
 ********************************
 *                              *
 *  os_global_transaction       *
 *                              *
 ********************************
 */

/* 
 * os_global_transaction represents a middleware transaction or an internal
 *  CMTL created wrapper around an independent virtual transaction. 
 */

class _OS_DLLIMPORT(_OS_CMTL) os_global_transaction {


public:
  
  /**
   * Returns true if the global transaction is an update transaction, false
   * otherwise.
   */
  virtual os_boolean is_update() const = 0;

  /**
   * Returns true if the global transaction is a readonly transaction, false
   * otherwise.
   */
  virtual os_boolean is_read_only() const = 0;

  /**
   * Returns the transaction type associated with this transaction.
   */ 
  virtual os_transaction_context::transaction_type get_transaction_type() const = 0;

  /**
   * Returns the isolation level associated with this transaction.
   */ 
  virtual os_transaction_context::isolation_level get_isolation_level() const = 0;

};

#endif /* _CMTL_INTERFACE_GLOBAL_TRANSACTION */
