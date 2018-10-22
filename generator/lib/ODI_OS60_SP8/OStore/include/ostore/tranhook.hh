/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _TRANHOOK_HH_
#define _TRANHOOK_HH_

#include <ostore/hdrstart.hh>

#include <ostore/portypes.hh>

class os_transaction;

class _OS_DLLIMPORT(_OS_CLIENT) os_transaction_hook {
public:
  enum event_type {
    invalid_event,
    after_begin,
    before_commit,
    after_commit,
    before_abort,
    after_abort,
    before_retry,
    before_rpc,
    before_finish_xa_commit,
    before_checkpoint,
    after_checkpoint,
    event_type_pad = 1<<30
  };

  typedef void (*hook_t) (const event_type, const os_transaction*);

  static hook_t register_hook(const event_type, hook_t);
  static void deregister_hook(const event_type);
};

#include <ostore/hdrend.hh>

#endif // _TRANHOOK_HH_
