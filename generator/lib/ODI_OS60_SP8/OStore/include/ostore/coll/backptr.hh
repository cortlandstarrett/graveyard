/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _Backptr_included
#define _Backptr_included
#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#endif

/*---------------------------------------------------------------------- */

class _Pvts;

class _Cbackptr;

#if defined(_OS_PSE_COLL)
_OS_BEGIN_NAMESPACE(os_pse)
#endif

class _Index_component;

class _OS_COLL_IMPORT _Backptr 
{
friend class _Cbackptr;

private:
  _Index_component * index_component;
  os_soft_pointer<_Backptr> next;
  os_int32 data_member_offset;

public:
  _Backptr()
    : data_member_offset(0),
      index_component(0),
      next(0)
    {}

  _Backptr(os_int32 id, const _Index_component* n, _Backptr* b)
    : data_member_offset(id),
      index_component((_Index_component*)n),
      next(b)
    {}

  ~_Backptr()
    {}

  void clear()
    { data_member_offset = 0; index_component = 0; next = 0; }

  void unlink(void* from, void* to) const;
  void link(void*, void*) const;

  static os_typespec* get_os_typespec();

  friend class os_backptr;
};

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
