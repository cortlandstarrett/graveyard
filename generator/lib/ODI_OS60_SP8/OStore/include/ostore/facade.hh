/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OSTORE_FACADE_HH
#define _OSTORE_FACADE_HH

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/tix.hh>

class  _OS_DLLIMPORT(_OS_CLIENT) os_facade
{
#if defined(__os_aix43)
 protected:
#else
 private:
#endif
  os_facade();
 private:
  os_facade(const os_facade&);
  os_facade &operator=(const os_facade&);

public:
  void operator delete(void*);
};

#include <ostore/hdrend.hh>

#endif /* _OSTORE_FACADE_HH */
