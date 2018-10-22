/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_OS_CACHE_HH_
#define _CMTL_INTERFACE_OS_CACHE_HH_

#include <ostore/cmtl/os_cache_pool_manager.hh>
#include <ostore/cmtl/os_txn_synch.hh>

class _OS_DLLIMPORT(_OS_CMTL) os_cache : public os_cmtl_object {
public:
    static os_cache *get_current();
    static os_database *create_database(const char *logical_db_name, 
					os_int32 mode=0664,
					os_boolean if_exists_overwrite = 0,
					os_database *schema_database = 0,
					objectstore::segment_reference_policy
					new_segment_reference_policy =
					objectstore::dsco_access_allowed);
    virtual ~os_cache() { /* empty */ };
    virtual os_cache_pool *get_cache_pool() const = 0;
    virtual const char *get_name() const = 0;
    virtual const os_database::open_modes get_open_mode() const = 0;
    virtual os_session *get_session() const = 0;
    virtual void *get_root_value(const char *logical_root_name) const = 0;
    virtual os_database *get_database(const char *logical_db_name) = 0;
    virtual int get_transaction_load() const = 0;
    virtual void add_transaction_synch(os_transaction_synch &txn_sync) = 0;
    virtual void remove_transaction_synch(os_transaction_synch &txn_sync) = 0;
    virtual void synchronize() = 0;
};

#endif // end of #ifndef _CMTL_INTERFACE_OS_CACHE_HH_


