/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_COMMON_HH_
#define _CMTL_INTERFACE_COMMON_HH_

// This is the header files for all of the common things about CMTL

#include <ostore/portypes.hh>
#include <ostore/ostore.hh>
#include <ostore/cmtl/os_log_constants.hh>

#include <fstream.h>

class _OS_DLLIMPORT(_OS_CMTL) os_enter_cmtl
{

public:
  static os_enter_cmtl* create();

  virtual ~os_enter_cmtl();
	
  // Indicates if cache pool manager created and CMTL is ready to use
  virtual os_boolean is_operational() = 0;
  // Indicates if per-thread initilization was done prior to entry
  virtual os_boolean is_redundant() = 0;
};


class _OS_DLLIMPORT(_OS_CMTL) _Stack_enter_cmtl : public basic_undo
{
private:
  os_enter_cmtl* p_enter_cmtl;

public:
  _Stack_enter_cmtl();
  ~_Stack_enter_cmtl();
};


/* The user must call this macro for every thread that uses CMTL */
#define OS_ENTER_CMTL {{ \
  _Stack_enter_cmtl enter_cmtl;
#define OS_LEAVE_CMTL }}

#define DEFAULT_CACHE_POOL_ROUTER_NAME "default_cache_pool_router"
#define CMTL_WORK_SESSION_NAME "CMTL_WORK_SESSION"


// use this struct to make attribute arrays which can be passed into 
// various CMTL API functions.
struct os_attribute_elem {
  const char *key;
  const char *value;
};


class _OS_DLLIMPORT(_OS_CMTL) os_cmtl_object {
  public:
  virtual void add_class_name(const char *class_name) = 0;
  virtual os_boolean equals(const os_cmtl_object *other) const = 0;
  virtual os_boolean instance_of(const char *class_name) const = 0;
  virtual int add_ref() = 0;
  virtual int del_ref() = 0;
  virtual ~os_cmtl_object() { /* empty */ };
};

#endif // end of #ifndef _CMTL_INTERFACE_COMMON_HH_


