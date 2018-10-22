/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_OS_CACHE_POOL_HH_
#define _CMTL_INTERFACE_OS_CACHE_POOL_HH_

#include <ostore/cmtl/os_cache_pool_manager_config.hh>
#include <ostore/cmtl/os_transaction_router.hh>
#include <ostore/cmtl/os_observable.hh>

class os_cache;
class os_cache_pool_manager;

/**
 * A os_cache_pool is a collection of os_cache objects and is constructed
 * with a specified cache pool name which uniquely identifies a cache
 * pool within the owning os_cache_pool_manager.
 *
 * Multiple cache pools can be used to logically parition the data or
 * state of a CMTL application.
 *
 * The os_cache_pool is observable through the os_observable class.  Observers
 * are notified when one of the administrative API's are called.  This
 * allows other objects such as routing implementations to cache information
 * about the cache configuration.
 *
 * A os_cache_pool can be configured with a set of named attributes.
 * CMTL has special knowledge of certain attributes.  User may define their 
 * own attributes as well.  The os_cache_pool attribute names which are 
 * known by CMTL are:
 *
 *   update_caches - A String valued attribute, evaluated at os_cache_pool 
 *     creation time, indicating the number of os_caches within this 
 *     os_cache_pool which should be created with UPDATE database open mode.
 *     If not specified, CMTL uses a value of 1.  You do not want any update 
 *     caches, then you must specify a value of 0.
 *
 *   mvcc_caches - A String valued attribute, evaluated at os_cache_pool 
 *     creation time, indicating the number of os_caches within this 
 *     os_cache_pool which should be created with MVCC database open mode.  
 *     If not specified, CMTL uses a value of 0.
 *
 *   address_space_size - A String valued attribute which may be set to an 
 *     integer value to indicate the amount of address space to be allocated 
 *     for each os_cache within this os_cache_pool.  The value must be an 
 *     unsigned integer in Hexadecimal format. The value must start with 
 *     "0x" or "0X".  The value represent the number of bytes of C++ client
 *     address space allocated to each caches of the current cache pool. 
 *     The actual value used is the amount specified rounded up to the 
 *     nearest 64 KB. If the amount of address space requested is not 
 *     available, an exception is signaled.  If the address_space_size 
 *     property is not specified, the default amount of address space is 
 *     calculated by the total number of caches and the cache pool manager 
 *     attributes "extra_sessions" and "num_expected_sessions".
 *
 *   group_open_interval - The value must be a unsigned integer in decimal 
 *     format.  The value specifies the time in milliseconds that the CMTL 
 *     scheduler will batch virtual transactions into physical transactions.  
 *     The default time is 500ms.
 *
 *   max_concurrent_GTs - The value must be a unsigned integer in decimal 
 *     format.  The value specifies the maximum number of concurrent virtual 
 *     transactions.
 * 
 *   commit_if_idle - The value represents a boolean value, It must be one 
 *     of: "1", "TRUE", "true", "0", "FALSE", "false". The default value is 
 *     "TRUE".  The value tells the CMTL scheduler to commit the physical 
 *     transaction when no virtual transactions are pending for the current 
 *     cache.
 *   
 */


class _OS_DLLIMPORT(_OS_CMTL) os_cache_pool : public os_observable {
 public:
    static const char *get_default_cache_address_space_size();
    static os_cache_pool *get_current();
    virtual os_cache *add_cache(const os_database::open_modes open_mode) = 0;
    virtual void add_database(const char *logical_db) = 0;
    virtual os_cache *choose_cache(const os_transaction_context &txn_ctx) const = 0;
    virtual os_database *create_database(const char *logical_db_name, 
					 os_int32 mode=0664,
					 os_boolean if_exists_overwrite = 0,
					 os_database *schema_database = 0,
					 objectstore::segment_reference_policy
					 new_segment_reference_policy =
					 objectstore::dsco_access_allowed) = 0;
    virtual const char *find_attribute(const char *attr_name) const = 0;
    virtual os_cache *get_cache(const char *cache_name) const = 0;
    virtual os_cache_pool_manager *get_cache_pool_manager() const = 0;
    virtual os_cache **get_caches() const = 0;
    virtual const char **get_database_names() const = 0;
    virtual os_cache **get_mvcc_caches() const = 0;
    virtual const char *get_name() const = 0;
    virtual os_cache **get_update_caches() const = 0;
    virtual void remove_cache(const char *cache_name) = 0;
    virtual void remove_database(const char *logical_db) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~os_cache_pool();
};

#endif // end of #ifndef _CMTL_INTERFACE_OS_CACHE_POOL_HH_



