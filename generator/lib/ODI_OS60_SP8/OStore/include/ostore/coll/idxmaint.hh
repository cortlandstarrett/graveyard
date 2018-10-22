/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _IDX_MAINT
#define _IDX_MAINT

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#endif

enum os_relationship_indexable{ os_no_index = -1, os_auto_index = -2, os_relationship_indexable_pad = 1<<30 };

#define __os_offsetof(ty,mem) ((os_ptr_val)&(((ty*)0)->mem))

#define os_index(a,b) __os_offsetof(a,b)


#if defined(_OS_ANSI_TOKENS)

#define _Concatidx(x,y) x##y

#define _Concat3idx(x,y,z) x##y##z

#define _Concat4idx(x,y,z,w) x##y##z##w

#else

#define _Selfidx(x)x

#define _Concatidx(x,y)_Selfidx(x)y

#define _Concat3idx(x,y,z)_Concatidx(x,y)z

#define _Concat4idx(x,y,z,w)_Concat3idx(x,y,z)w

#endif

#ifndef OS_INDEXABLE_LINKAGE
#define OS_INDEXABLE_LINKAGE
#endif

#define os_indexable_member(basetype,member,valuetype) \
  friend os_int32 _Concat3idx(os_indexable_offsetof_,basetype,member) (); \
  class OS_INDEXABLE_LINKAGE _Concat3idx(os_indexable_,basetype,member) { \
    private: \
     valuetype value; \
    public: \
     valuetype setvalue(valuetype v); \
     valuetype operator=(valuetype v) {return setvalue(v);} \
     operator valuetype() const {return value;} \
     const valuetype & getvalue() const {return (const valuetype &)value;} \
     _Concat3idx(os_indexable_,basetype,member) () {} \
     _Concat3idx(os_indexable_,basetype,member) (const valuetype& x) \
       : value((valuetype&)x) {} \
     ~ _Concat3idx(os_indexable_,basetype,member) (); \
  } 


#if defined(_OS_cfrontC) && !defined(__os_sgi_mips)

#define os_indexable_body(basetype,member,valuetype,bpoff) \
 os_int32 _Concat3idx(os_indexable_offsetof_,basetype,member) (){return __os_offsetof(basetype,member);};\
 typedef basetype :: _Concat3idx(os_indexable_,basetype,member) _Concat4idx(os_indexable_,basetype,member,_body); \
 valuetype _Concat4idx(os_indexable_,basetype,member,_body) ::setvalue(valuetype v) { \
   os_backptr* bpl = \
     (os_backptr*)((char*)this-_Concat3idx(os_indexable_offsetof_,basetype,member) ()+bpoff); \
   bpl->break_link(this,this,bpoff-_Concat3idx(os_indexable_offsetof_,basetype,member) ()); \
   value = v; \
   bpl->make_link(this,this,bpoff-_Concat3idx(os_indexable_offsetof_,basetype,member) ()); \
   return value; \
 }; \
 _Concat4idx(os_indexable_,basetype,member,_body) ::~ _Concat3idx(os_indexable_,basetype,member)() { \
   os_backptr* bpl = \
     (os_backptr*)((char*)this-_Concat3idx(os_indexable_offsetof_,basetype,member) ()+bpoff); \
   bpl->break_link(this,this,bpoff-_Concat3idx(os_indexable_offsetof_,basetype,member) ()); \
 };

#define os_indexable_body_with_copy(class, member, value_type, bp_offset, copy)

#else   /* _OS_cfrontC */

#define os_indexable_body(basetype,member,valuetype,bpoff) \
 os_int32 _Concat3idx(os_indexable_offsetof_,basetype,member) (){return __os_offsetof(basetype,member);}\
 valuetype basetype::_Concat3idx(os_indexable_,basetype,member)::setvalue(valuetype v) { \
   os_backptr* bpl = \
     (os_backptr*)((char*)this-_Concat3idx(os_indexable_offsetof_,basetype,member) ()+bpoff); \
   bpl->break_link(this,this,bpoff-_Concat3idx(os_indexable_offsetof_,basetype,member) ()); \
   value = v; \
   bpl->make_link(this,this,bpoff-_Concat3idx(os_indexable_offsetof_,basetype,member) ()); \
   return value; \
 } \
 basetype::_Concat3idx(os_indexable_,basetype,member)::~_Concat3idx(os_indexable_,basetype,member)() { \
   os_backptr* bpl = \
     (os_backptr*)((char*)this-_Concat3idx(os_indexable_offsetof_,basetype,member) ()+bpoff); \
   bpl->break_link(this,this,bpoff-_Concat3idx(os_indexable_offsetof_,basetype,member) ()); \
 }

#define os_indexable_body_with_copy(class, member, value_type, bp_offset, copy)

#endif  /* _OS_cfrontC */

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
