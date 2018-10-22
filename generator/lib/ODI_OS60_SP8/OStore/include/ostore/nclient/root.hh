/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_ROOT
#define CLIENT_INTERFACE_ROOT 1

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/facade.hh>

class os_typespec;
class os_database;

class _OS_DLLIMPORT(_OS_CLIENT) os_database_root : public os_facade
{
public:						/* PUBLIC FUNCTION MEMBERS */
  void operator delete(void*); 

  static os_database_root* find(const char* name_arg, os_database* db);

  void destroy();

  const char *get_name() const;
  const os_typespec *get_typespec() const;
  void *get_value(const os_typespec *typespec_arg = 0) const;
  void set_value(void *new_value, const os_typespec *typespec_arg = 0);

  void release_pointer();
  void retain_pointer();
};

/* This class provides a mechanism to call the release_pointer() method
  on a specified os_database_root pointer when that pointer goes out of scope. 
*/
class _OS_DLLIMPORT(_OS_CLIENT) os_release_root_pointer : public basic_undo
{
private:
  os_database_root *ptr;

public:
  os_release_root_pointer(os_database_root *_ptr) : ptr(_ptr) {}
  ~os_release_root_pointer() { if (ptr) ptr->release_pointer(); }
};

#include <ostore/hdrend.hh>
#endif /* CLIENT_INTERFACE_ROOT */
