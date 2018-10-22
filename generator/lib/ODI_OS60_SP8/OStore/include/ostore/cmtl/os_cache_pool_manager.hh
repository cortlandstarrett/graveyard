/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_OS_CACHE_POOL_MANAGER_HH_
#define _CMTL_INTERFACE_OS_CACHE_POOL_MANAGER_HH_

#include <ostore/cmtl/os_cache_pool.hh>

class _OS_DLLIMPORT(_OS_CMTL) os_cache_pool_manager : public os_observable {
public:

    // Create a os_cache_pool_manager for a specific 
    // os_cache_pool_manager_config.  There must not be 
    // os_cache_pool_manager currently running.  Signals a 
    // err_cmtl_cache_pool_manager_exists if there is already another
    // os_cache_pool_manager running in this process.  Signals a 
    // err_cmtl_invalid_configuration if the configuration is invalid
    // or internally inconsistent.
    static os_cache_pool_manager *create(os_cache_pool_manager_config &config); 
    static os_cache_pool_manager *get();

    
    // Return the os_cache_pool with the specified cache pool name.  Throws 
    // a err_cmtl_cache_pool_not_found TIX exception if there is no 
    // os_cache_pool of the specified name.
    virtual os_cache_pool *get_cache_pool(const char *cache_pool_name) const = 0;

    // Return the os_cache with the specified cache name.  Throws a 
    // err_cmtl TIX exception if the cache name is not in valid format for 
    // a os_cache name.  Throws a err_cmtl_cache_pool_not_found TIX exception 
    // if the cache name references a nonexistent os_cache_pool.  Throws a 
    // err_cmtl_cache_pool_not_found TIX exception if the cache name 
    // references a valid os_cache_pool but that os_cache_pool has no 
    // ObjectStore sesssion with the specified name.
    virtual os_cache *get_cache(const char *cache_name) const = 0;


    // Returns a snapshot of the os_cache_pools within this cache pool 
    // manager.  The resulting array is a snapshot of the os_cache_pools 
    // in existence at the time this method was called.  
    virtual os_cache_pool **get_cache_pools() const = 0;

    virtual const char *get_physical_db_name(const char *logical_db_name) const = 0;
    virtual os_cache *choose_cache(const os_transaction_context &txn_context) const = 0;
    virtual os_root_mapping *get_root(const char *logical_root_name) const = 0;  // return is not const
    virtual const char *find_attribute(const char *attribute_name) const = 0;
    virtual const char *get_method_routing_rule(const char *method_name) const = 0;
    virtual void shutdown() = 0;
    virtual void remove_cache_pool(os_cache_pool &cache_pool_to_remove) = 0;
    virtual os_cache_pool *add_cache_pool(os_cache_pool_config &new_cache_pool_config) = 0;
    virtual void set_db_mapping(const char *logical_db_name, const char *physical_db_name) = 0;
    virtual void set_router(os_transaction_router *new_router) = 0;
    virtual void add_root(const char *logical_root_name, os_root_mapping *root_mapping) = 0;
    virtual const enum os_log_constants get_debug_level() const = 0;
    virtual void set_debug_level(const enum os_log_constants level) = 0;
    virtual void log_message(const char *msg, const enum os_log_constants msg_level) const = 0;
    virtual void initialize_collections() = 0;
    virtual ~os_cache_pool_manager();
};

#endif // end of #ifndef _CMTL_INTERFACE_OS_CACHE_POOL_MANAGER_HH_
