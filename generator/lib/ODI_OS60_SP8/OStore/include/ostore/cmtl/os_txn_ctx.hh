/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_TRANSACTION_CONTEXT
#define _CMTL_INTERFACE_TRANSACTION_CONTEXT 1

#include <ostore/cmtl/common.hh>

class os_cache;
class os_cache_pool;
class os_global_transaction;
class os_operation_context;

/**
 * This interface defines the common protocol for all transaction context 
 * objects.  The transaction context objects communicate context information 
 * from the application code to CMTL for the purpose of cache selection and 
 * virtual transaction queuing.  This class is an abstract interface 
 * class.  All concrete transaction context implementations must derive 
 * from this class.
 */

class _OS_DLLIMPORT(_OS_CMTL) os_transaction_context {

public:					/* public function members */

  enum transaction_type	     {update = 1,
			      read_only = 2,
			      transaction_type_pad = 1<<30};
  enum isolation_level	    {read_uncommitted= 1,
			     read_committed = 2,
			     repeatable_read = 3,
			     serializable = 4,
			     isolation_level_pad = 1<<30};
  /**
   * Returns the os_global_transaction for this operation, if any 
   */
  virtual os_global_transaction *get_global_transaction() const = 0;


  /**
   * Returns the os_cache_pool to which this operation should be dispatched,
   * if known.  Otherwise, returns null.  Callers should not attempt to 
   * delete the os_cache_pool pointer returned by this member function.
   */
  virtual os_cache_pool *get_cache_pool() const = 0;

  /**
   * Returns the os_cache to which this operation should be 
   * dispatched, if known.  Otherwise, returns null.  Callers should not 
   * attempt to delete the os_cache pointer returned by this member 
   * function.
   */
  virtual os_cache *get_cache() const = 0;


  /**
   * Get the isolation level required for an operation 
   */
  virtual isolation_level get_isolation_level() const = 0;


  /**
   * Check whether the virtual transaction is allowed to update data 
   */
  virtual os_boolean is_update() const = 0; 


  /**
   * Check whether the virtual transaction is read only 
   */
  virtual os_boolean is_read_only() const = 0; 


  /**
   * Returns the transaction type
   */
  virtual transaction_type get_transaction_type() const = 0; 


  /**
   * Returns the operation-specific context information 
   */
  virtual os_operation_context *get_operation_context() const = 0; 


  /*
   * Returns true if only one virtual transaction will be started within 
   * the enclosing global transaction.  If true, this allows the scheduler 
   * flexibility in scheduling transactions. 
   */
  virtual os_boolean one_transaction_only() const = 0;

  virtual ~os_transaction_context() { /* empty */ } 

typedef os_transaction_context::transaction_type os_virtual_transaction_type;
typedef os_transaction_context::isolation_level os_isolation_level;

};

#endif /* _CMTL_INTERFACE_TRANSACTION_CONTEXT */


