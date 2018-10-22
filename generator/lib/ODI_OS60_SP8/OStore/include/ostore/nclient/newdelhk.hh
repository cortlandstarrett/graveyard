/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _NEWDELHK
#define _NEWDELHK

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>

/* support for allocate and deallocate hooks */

typedef void		(*os_alloc_hook_t) (os_void_p obj);

class _OS_DLLIMPORT(_OS_CLIENT) os_alloc_hook {
public:
  static os_alloc_hook_t	register_hook(os_alloc_hook_t);
  static void			deregister_hook();
  static void			_call_current_hook(void* obj);
};


typedef os_boolean	(*os_dealloc_hook_t) (os_void_p obj);

class _OS_DLLIMPORT(_OS_CLIENT) os_dealloc_hook {
public:
  /*
   * the delete hook is called first and must return a non-zero value for
   * the storage-level delete to proceed
   */

  static os_dealloc_hook_t	register_hook(os_dealloc_hook_t);
  static void			deregister_hook();
  static os_boolean		_call_current_hook(void* obj);
};

#include <ostore/hdrend.hh>
#endif /* _NEWDELHK */
