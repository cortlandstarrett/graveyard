/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_OBJCURS
#define CLIENT_INTERFACE_OBJCURS 1

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>

class os_segment;
class os_cluster;

class _OS_DLLIMPORT(_OS_CLIENT) os_object_cursor {
public:
  os_object_cursor(const os_segment *seg_arg);
  os_object_cursor(const os_cluster *clus_arg);
  ~os_object_cursor();
  os_boolean current(os_void_p &pointer, os_type_const_p &type,
		     os_int32 &count) const;
  void first();
  void next();
  os_boolean more() const;
  void set(const void *pointer);
  void reset(const void *address);

private:
  os_object_cursor(const os_object_cursor&);
  os_object_cursor& operator= (const os_object_cursor&);
private:
  void *_data;
};

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_OBJCURS */
