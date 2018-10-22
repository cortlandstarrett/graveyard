/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_RETAIN_ADDRESS
#define CLIENT_INTERFACE_RETAIN_ADDRESS

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/tix.hh> 

class _OS_DLLIMPORT(_OS_CLIENT) os_retain_address : public basic_undo
{
  void *_internal;
private:
  os_retain_address(const os_retain_address&);
  os_retain_address &operator=(const os_retain_address&);

public:
  os_retain_address(void **ptr_to_ptr = 0);
  ~os_retain_address();

  void *retaining() const;

  void release();

  void set_retain(void **ptr_to_ptr);
};

#include <ostore/hdrend.hh>
#endif /* CLIENT_INTERFACE_RETAIN_ADDRESS */
