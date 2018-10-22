/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_OS_CACHE_POOL_MANAGER_CONFIG_HH_
#define _CMTL_INTERFACE_OS_CACHE_POOL_MANAGER_CONFIG_HH_

// os_cache_pool_manager_config describes an organization of os_cache_pools

#include <ostore/cmtl/common.hh>
#include "os_root_mapping.hh"
#include "os_cache_pool_config.hh"

class _OS_DLLIMPORT(_OS_CMTL) os_cache_pool_manager_config {
 public:
    static os_cache_pool_manager_config *create(os_cache_pool_config **cache_pool_configs = NULL,
						os_attribute_elem **attributes = NULL,
						os_attribute_elem **db_name_map = NULL,
						os_logical_root_elem **logical_root_definitions = NULL);

    static os_cache_pool_manager_config *create(os_cache_pool_config &cache_pool_configs,
						os_attribute_elem **attributes = NULL,
						os_attribute_elem **db_name_map = NULL,
						os_logical_root_elem **logical_root_definitions = NULL);

    virtual os_cache_pool_config **get_cache_pool_configurations() const = 0;
    virtual os_attribute_elem **get_db_name_map() const = 0;
    virtual const os_logical_root_elem **get_logical_root_map() const = 0;
    virtual os_attribute_elem **get_attributes() const = 0;

    /* Depricated in 6.0 SP7 -- may be removed in a future release, use create_from_xml_stream instead. */
    static os_cache_pool_manager_config *create_from_xml(ifstream &xml_doc);  

    /* Depricated in 6.0 SP7 -- may be removed in a future release, use create_from_xml_buffer instead */
    static os_cache_pool_manager_config *create_from_xml(const char *xml_doc);  

    static os_cache_pool_manager_config *create_from_xml_file(const char *xml_filename);
    static os_cache_pool_manager_config *create_from_xml_stream(ifstream &xml_doc);
    static os_cache_pool_manager_config *create_from_xml_buffer(const char *xml_doc);
    virtual ~os_cache_pool_manager_config();
};

#endif // end of #ifndef _CMTL_INTERFACE_OS_CACHE_POOL_MANAGER_CONFIG_HH_


