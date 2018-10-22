/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_ROOT_MAPPING
#define _CMTL_INTERFACE_ROOT_MAPPING 1

#include <ostore/cmtl/common.hh>

/*
 ********************************
 *                              *
 *	  os_root_mapping       *
 *                              *
 ********************************
 */

// This class is used to handle the mapping of logical name to a root value,
// hiding the os_database_root as an implementation detail.  
class _OS_DLLIMPORT(_OS_CMTL) os_root_mapping  : public os_cmtl_object 
{
public:
  static os_root_mapping *create(const char *logical_db_name, 
				 const char *root_name, 
				 void * value = NULL);
  const char *get_logical_database_name() const;
  const char *get_physical_root_name() const;
  void *get_root_value();
  void set_root_value(void *new_value);
  virtual ~os_root_mapping() { /* empty */ };
};

struct os_logical_root_elem {
  const char *key;
  os_root_mapping *value;
};

#endif /* _CMTL_INTERFACE_ROOT_MAPPING */
