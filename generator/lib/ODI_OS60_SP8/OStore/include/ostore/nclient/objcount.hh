/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_OBJCOUNT
#define CLIENT_INTERFACE_OBJCOUNT 1

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>

/* An array of these is returned by os_segment::count_objects() or
   os_cluster::count_objects() */
class _OS_DLLIMPORT(_OS_CLIENT) objectstore_object_count {
public:
  os_unsigned_int32 singles;
  os_unsigned_int32 arrays;
  os_unsigned_int32 total;
  os_unsigned_int32 object_size;
  os_unsigned_int32 vector_header_size;
  char *type_name;
  objectstore_object_count();
  objectstore_object_count(const objectstore_object_count&);
  ~objectstore_object_count();
  objectstore_object_count& operator=(const objectstore_object_count&);
};

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_OBJCOUNT */
