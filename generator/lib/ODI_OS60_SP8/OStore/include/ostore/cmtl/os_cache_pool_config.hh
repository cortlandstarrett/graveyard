/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_OS_CACHE_POOL_CONFIG_HH_
#define _CMTL_INTERFACE_OS_CACHE_POOL_CONFIG_HH_

#include <ostore/cmtl/common.hh>

class _OS_DLLIMPORT(_OS_CMTL) os_cache_pool_config {
 public:
    static os_cache_pool_config *create();
    static os_cache_pool_config *create(const char *name);
    static os_cache_pool_config *create(const char *name, os_attribute_elem **attributes);
    virtual const char *get_name() const = 0;
    virtual os_attribute_elem **get_attributes() const = 0;
    virtual ~os_cache_pool_config();
};

#endif // end of #ifndef _CMTL_INTERFACE_OS_CACHE_POOL_CONFIG_HH_


