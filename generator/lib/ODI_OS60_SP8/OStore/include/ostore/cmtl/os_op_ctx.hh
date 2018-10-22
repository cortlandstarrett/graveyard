/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_OP_CTX_HH_
#define _CMTL_INTERFACE_OP_CTX_HH_

#include <ostore/cmtl/common.hh>

/**
 * CMTL operation context
 * 
 * This interface defines the minimal protocol for communicating
 * operation-specific information for the purposes of os_cache
 * selection and transaction queueing.
 */

class _OS_DLLIMPORT(_OS_CMTL) os_operation_context {
 public:

  // Get the symbolic name for an operation 
  virtual const char *get_method_name() const = 0;  

  // Returns a array of string to operand values 
  virtual os_attribute_elem **get_operands() const = 0; 

  // Returns an array of the names of all partitions which might need to be 
  // accessed in order to complete either read-only or update behavior.
  // This array is the union of modified and read-only partitions.
  virtual const char **get_referenced_partitions() const = 0; 

  // Returns an array of the names of data partitions which might be modified
  // by this operation.  If this returns null and this operation occurs 
  // within an update transaction, the operation is assumed to modify all
  // partitions of the os_cache. 
  virtual const char *get_modified_partitions() const = 0;

  // Returns an array of the names of data partitions which might be
  // accessed by this operation, but only for read-only behavior. If
  // this returns null and this operation occurs within an read-only
  // transaction, the operation is assumed to access all partitions of
  // the os_cache.
  virtual const char *get_read_only_partitions() const = 0;

  // Return the name of the os_cache_pool for this operation.
  virtual const char *get_cache_pool_name () const = 0;

  // Returns a boolean indicating whether to consider overriding any
  // existing binding to a os_cache for the purposes of routing. 
  virtual os_boolean override_binding() const = 0;
};

#endif // end of #ifndef _CMTL_INTERFACE_OP_CTX_HH_


