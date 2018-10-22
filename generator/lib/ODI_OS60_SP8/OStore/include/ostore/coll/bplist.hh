/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef os_backptr_included
#define os_backptr_included
#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#endif

class _Pvts;

#if defined(_OS_PSE_COLL)
_OS_BEGIN_NAMESPACE(os_pse)
#endif

class _Index_component;

class _OS_COLL_IMPORT os_backptr
{
public:
  os_backptr() {}
  os_backptr(const os_backptr&) { clear(); }
  ~os_backptr();

  void operator=(const os_backptr&) { clear(); }

  void clear()
    { head.clear(); }

  os_int32 empty() const
    { return (os_int32) (!head.index_component && (head.data_member_offset != -5)); }

  /* os_int32 argument identifies which data member the backptr represents. */
  /* Each set has its own backptr list - default 0 is used for id. */
  void make_link(void*, void*, os_int32 = 0) const;
  void break_link(void*, void*, os_int32 = 0) const;
  void insert(const _Index_component*, os_int32 = 0, const void* v = 0);
  os_int32 remove(const _Index_component*, os_int32 = 0, const void* v = 0);

  void make_link(void*, void*, const char*, const char*) const;
  void break_link(void*, void*, const char*, const char*) const;
  void insert(const _Index_component*, const char*, const char*);
  os_int32 remove(const _Index_component*, const char*, const char*);


  void dump() const
    {}

  static os_typespec* get_os_typespec();

  /* Transformation during schema evolution */
  static void evolution_transform(void*);

private:
  _Backptr head;
};

typedef os_backptr _Backptr_list;

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
