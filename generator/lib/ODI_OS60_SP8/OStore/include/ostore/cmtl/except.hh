/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_EXCEPT
#define _CMTL_INTERFACE_EXCEPT

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/except.hh>

/* External declarations of TIX exception classes for CMTL errors. */

_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_abort_and_retry);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_cache_not_found);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_cache_pool_manager_exists);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_cache_pool_not_found);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_database_exists);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_database_not_found);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_fatal_app_error);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_fatal_internal_error);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_illegal_argument);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_illegal_state);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_invalid_configuration);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_invalid_routing);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_logical_database_not_found);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_logical_root_not_found);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_no_transaction_in_progress);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_participant);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_partition_not_found);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_retry);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_shutdown);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_transaction_in_progress);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_illegal_state);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_nested_transaction);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_initialization);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_wrong_cache);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_no_cache);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_insufficient_address_space);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_max_expected_caches);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_no_cache_pool_manager);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_wrong_cache_pool_manager);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_max_cache_pool_managers);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_JThreads);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_invalid_cpm_config);


/* Internal TIX exceptions for CMTL */
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_scheduler_action);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_scheduler_action_abort);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_scheduler_action_checkpoint);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_scheduler_action_commit);
_OS_DECLARE_EXCEPTION(_OS_CMTL,err_cmtl_scheduler_action_evict_objects);

#include <ostore/hdrend.hh>

#endif /* _CMTL_INTERFACE_EXCEPT */
