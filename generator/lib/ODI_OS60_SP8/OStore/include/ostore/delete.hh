/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _OS_DELETE_HH
#define _OS_DELETE_HH
#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>

typedef os_boolean (*os_default_delete_function) (os_void_p);

class os_default_delete_handler {
public:
  const os_default_delete_function fcn;
  os_default_delete_handler(os_default_delete_function);
  ~os_default_delete_handler();
};

#include <ostore/hdrend.hh>
#endif /* _OS_DELETE_HH */
