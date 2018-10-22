/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_BASIC_TRANSACTION_CONTEXT
#define _CMTL_INTERFACE_BASIC_TRANSACTION_CONTEXT 1

#include <ostore/cmtl/os_txn_ctx.hh>

class os_cache;
class os_cache_pool;
class os_global_transaction;
class os_operation_context;

/**
 * The os_basic_transaction_context represents the most basic transction 
 * context. It is used in the absence of a middleware-provided transaction 
 * manager. When using the no argument constructor, the isolation level of 
 * this os_transaction_context is SERIALIZABLE and the context is for update. 
 * When using this constructor, the instance does not return a os_cache_pool, 
 * so in order for the os_cache_pool_manager to be able to route to a 
 * os_cache_pool using this os_basic_transaction_context for an operation, 
 * there must either be only one os_cache_pool set up with the 
 * os_cache_pool_manager or the "default_cache_pool" attribute for the 
 * os_cache_pool_manager must be set to a valid os_cache_pool name.
 * This requirement is avoided by specifying a os_cache_pool for routing 
 * through one of the other os_basic_transaction_context constructors.
 *
 */

class _OS_DLLIMPORT(_OS_CMTL) os_basic_transaction_context : public os_transaction_context {

public:					/* public static member functions */

  /**
   * Create a transaction context, possibly specifying update/read-only 
   * attribute and isolation level.
   */
  static os_basic_transaction_context* create(os_transaction_context::transaction_type transaction_type = os_transaction_context::update,
					      os_transaction_context::isolation_level isolation_level = os_transaction_context::serializable);


  /**
   * Create a transaction context, specifying cache pool and possibly 
   * update/read-only attribute and isolation level.
   */
  static os_basic_transaction_context* create(os_cache_pool *p_cache_pool,
					      os_transaction_context::transaction_type = os_transaction_context::update,
					      os_transaction_context::isolation_level isolation_level = os_transaction_context::serializable);

  /**
   * Create a transaction context, specifying cache and possibly 
   * update/read-only attribute and isolation level.
   */
  static os_basic_transaction_context* create(os_cache *p_cache,
					      os_transaction_context::transaction_type = os_transaction_context::update,
					      os_transaction_context::isolation_level isolation_level = os_transaction_context::serializable);


  /**
   * Create a fully customizable transaction context
   * Note: In CMTL for ObjectStore 6.0.6 there is no provided middleware 
   *       intergration.  Users should pass in a NULL for the global
   *       transaction (p_gt) and a TRUE for one transaction only
   *       (b_one_transaction_only).
   *   
   */
  static os_basic_transaction_context* create(os_cache_pool *p_cache_pool,
					      os_cache *p_cache,
					      os_global_transaction *p_gt,
					      os_operation_context *p_op_ctx,
					      os_transaction_context::transaction_type = os_transaction_context::update,
					      os_transaction_context::isolation_level = os_transaction_context::serializable,
					      os_boolean b_one_transaction_only = 1);


  virtual ~os_basic_transaction_context() { /* empty */ } 
};

#endif /* _CMTL_INTERFACE_BASIC_TRANSACTION_CONTEXT */


