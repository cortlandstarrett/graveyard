/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef __PORTDEF_HH__
#define __PORTDEF_HH__ 1
#include <ostore/hdrstart.hh>

#include <ostore/portypes.hh>

class os_signed_long_rep {
public:
  os_signed_long_rep (long);
  os_signed_long_rep (const os_signed_long_rep&);
  operator long () const;
  char* string_rep() const;

private:
  long get_value () const;
  void get_string_rep (char*) const;

  os_int32 high_order;
  os_int32 low_order;
};

class os_unsigned_long_rep {
public:
  os_unsigned_long_rep (unsigned long);
  os_unsigned_long_rep (const os_unsigned_long_rep&);
  operator unsigned long () const;
  char* string_rep() const;

private:
  unsigned long get_value () const;
  void get_string_rep (char*) const;

  os_unsigned_int32 high_order;
  os_unsigned_int32 low_order;
};

#include <ostore/hdrend.hh>
#endif
