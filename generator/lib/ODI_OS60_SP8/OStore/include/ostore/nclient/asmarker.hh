/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_ASMARKER
#define CLIENT_INTERFACE_ASMARKER

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/tix.hh>

class _OS_DLLIMPORT(_OS_CLIENT) os_address_space_marker
{
  void *_internal;
private:
  os_address_space_marker(const os_address_space_marker&);
  os_address_space_marker &operator=(const os_address_space_marker&);
  
public:
  os_address_space_marker();
  ~os_address_space_marker();

  void release(os_boolean unmap_all_fast = 0);

  os_address_space_marker *get_previous() const;
  
  os_address_space_marker *get_next() const;
  
  os_unsigned_int32 get_level() const;

  static os_address_space_marker *get_current();

  static void retain(void *p, os_address_space_marker *other = 0);

  static os_address_space_marker *of(void *addr);
};


/* use this derived class for stack-allocated address space markers when not
   using C++-exceptions: */
class _OS_DLLIMPORT(_OS_CLIENT) os_address_space_marker_stacked
  : public basic_undo,
    public os_address_space_marker
{};

#include <ostore/hdrend.hh>
#endif /* CLIENT_INTERFACE_ASMARKER */
