/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#include <ostore/hdrstart.hh>

#if defined(_OS_ANSI_TOKENS)
#define _Concat4cidx(w,x,y,z) w##x##y##z
#else
#define _Concat4cidx(w,x,y,z) w/**/x/**/y/**/z
#endif

#define _Offsetof(t,m) ((int)&(((t*)0)->m))

#define os_indexable_member(class, member, type) type

#define os_indexable_body(class, member, value_type, bp_offset) \
void _Concat4cidx(class,_,member,_setvalue)(idx, value) \
value_type* idx; \
value_type* value; \
{ \
  os_backptr* bp = (os_backptr*) \
                   ((char*)idx - _Offsetof(class, member) + bp_offset); \
  _os_backptr_break_link(bp, idx, idx, bp_offset - _Offsetof(class, member)); \
  *idx = *value; \
  _os_backptr_make_link(bp, idx, idx, bp_offset - _Offsetof(class, member)); \
}

#define os_indexable_body_with_copy(class, member, value_type, bp_offset, copy) \
void _Concat4cidx(class,_,member,_setvalue)(idx, value) \
value_type* idx; \
value_type* value; \
{ \
  os_backptr* bp = (os_backptr*) \
                   ((char*)idx - _Offsetof(class, member) + bp_offset); \
  _os_backptr_break_link(bp, idx, idx, bp_offset - _Offsetof(class, member)); \
  copy(idx, value); \
  _os_backptr_make_link(bp, idx, idx, bp_offset - _Offsetof(class, member)); \
}

#define os_indexable_setvalue(class, member, idx, value) \
_Concat4cidx(class,_,member,_setvalue)(&(idx), value)


#define os_index(t, bp) _Offsetof(t,bp)

#include <ostore/hdrend.hh>
