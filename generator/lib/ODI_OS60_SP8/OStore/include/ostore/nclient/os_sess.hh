/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_SESSION
#define CLIENT_INTERFACE_SESSION 1

#include <ostore/portypes.hh>
#include <ostore/facade.hh>

class os_database;
class os_segment;
class os_cluster;

/********************************/
/* os_session definition       	*/
/********************************/

class _OS_DLLIMPORT(_OS_CLIENT) os_session: public os_facade
{
public:
  /* Returns a heap allocated os_session object.  Caller is responsible
     for deleting the object when it is no longer used by the application. */
  static os_session* create(const char *name);

  /* shuts down a client os_session and deletes the storage associated
     with that os_session. */
  void operator delete(void *ptr);
  
  /* Previous current os_session, if any, is returned. */
  static os_session* set_current(os_session* new_current_session);

  /* Signals err_no_session if calling thread is not part of an os_session */
  static os_session* get_current();

  /* returns the current number of sessions in the application */
  static os_unsigned_int32 get_n_sessions();

  /* User is responsible for allocating/deleting array of os_session*,
     but not the individual elements */
  static os_session** get_all_sessions(os_unsigned_int32& n_sessions);

  /* Returns a pointer to the os_session owned session name.  Should not
     be deleted by the caller.  */
  const char* get_name() const;

  /* Forces full client initialization (initialize client cache, psr, etc)
     instead of deferring initialization until it is needed */
  void force_full_initialization();

  /* Thread absorption API */
  void set_thread_absorption(os_boolean allowed);

  os_boolean get_thread_absorption();

  /* Returns the os_session owning the address space partition containing
     the address.  Returns 0 if no os_session if the address isn't within
     any address space partitions of the process. */
  static os_session *of(void const *address);

  void *get_value() const;

  void set_value(void *ptr);

  /* Make the DLL schema in use in the current session. Load the DLL if it is
     not yet loaded. */
  static os_DLL_handle use_DLL(const char *DLL_identifier,
			       os_boolean error_if_not_found = 1);

  /* Unuse the DLL schema in the current session. */
  static void unuse_DLL(const char *DLL_identifier);

};

typedef os_session* os_session_p;

#endif /* CLIENT_INTERFACE_SESSION */
