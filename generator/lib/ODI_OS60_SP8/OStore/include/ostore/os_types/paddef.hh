/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef __PAD_DEFINITIONS__
#define __PAD_DEFINITIONS__ 1
#include <ostore/hdrstart.hh>

class os_typespec;
struct _Virtual_behavior_____os_align_spec_data;
#define OS_ALIGN_CLASS(x) class _os_align_spec \
 { \
 char _os_pad[x]; \
public: \
 _os_align_spec(_Virtual_behavior_____os_align_spec_data& data); \
 static os_typespec* get_os_typespec(); \
 }

template <class T, int size, int id>
class _os_pad_t {
public:
  char _os_pad_1[size];
};

template <class T, int size, int id>
class _os_pad_vft_base {
public:
  virtual void dummy_vfun(_os_pad_vft_base<T,size,id>*) {}
};

template <class T, int size, int id>
class _os_pad_vft: public _os_pad_vft_base<T,size,id> {
public:
  char _os_pad_1[size];
};


template <class T, int id>
class _os_pad_vft4: public _os_pad_vft_base<T,0,id> {
public:
};


/* hacky classes for linux odd base class alignment problem. */
template <class T, int size, int altsize, int id>
class _os_pad_dnvb_t {
public:
#if defined(__os_linux)
  char _os_pad_1[altsize];
#else
  char _os_pad_1[size];
#endif
};


template <class T, int size, int altsize, int id>
class _os_pad_dnvb_vft : public _os_pad_vft_base<T, size, id> {
public:
#if defined(__os_linux)
  char _os_pad_1[altsize];
#else
  char _os_pad_1[size];
#endif
};


#ifdef _OS_cfrontC

/* cfront */

#define os_pad_vftbl_start char _os_pad_vftbl_start[4];
#define os_pad_vftbl_end class _os_pad_vftbl_end_p{char p[4];};

#define os_pad_vftbl_start8 char _os_pad_vftbl_start8[8];
#define os_pad_vftbl_end8 char _os_pad_vftbl_end8[4];

#define os_pad_vftbl_only class _os_pad_vftbl_only_p{char p[4];};
#define os_pad_vftbl_only8 char _os_pad_vftbl_only8[4];

#ifdef _OS_ANSI_TOKENS
#define os_pad_vbptr_start(x) char _os_pad_vbptr_start_##x[4];
#define os_pad_vbptr_start8(x) char _os_pad_vbptr_start8_##x[4];
#define os_pad_vbptr_end(x) class _os_pad_vbptr_end_##x##_p{char p[4];};
#define os_pad_vbptr_end8(x) char _os_pad_vbptr_end8_##x[4];
#else
#define os_pad_vbptr_start(x) char _os_pad_vbptr_start_/**/x[4];
#define os_pad_vbptr_start8(x) char _os_pad_vbptr_start8_/**/x[4];
#define os_pad_vbptr_end(x) class _os_pad_vbptr_end_/**/x/**/_p{char p[4];};
#define os_pad_vbptr_end8(x) char _os_pad_vbptr_end8_/**/x[4];
#endif

#define os_pad_selfptr  char _os_pad_selfptr[4];

#define os_pad_vbtbl_start  char _os_pad_vbtbl_start[4];
#define os_pad_vbtbl_start8  char _os_pad_vbtbl_start8[8];
#define os_pad_vbtbl_end  char _os_pad_vbtbl_end[4];
#define os_pad_vbtbl_end8  char _os_pad_vbtbl_end8[8];

#ifdef _OS_ANSI_TOKENS
#define os_pad_ptr8(x) char _os_pad_ptr8_##x[4];
#define os_pad_mem_ptr8(x) char _os_pad_mem_ptr8_##x[4];
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_##x[8];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_##x[12];
#else
#define os_pad_ptr8(x) char _os_pad_ptr8_/**/x[4];
#define os_pad_mem_ptr8(x) char _os_pad_mem_ptr8_/**/x[4];
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_/**/x[8];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_/**/x[12];
#endif

#define os_pad_cons_disp(x) , public virtual _os_pad_cons_disp<x>

#define os_pad_base_vbtbl_start public _os_pad_vbtbl_start,
#define os_pad_base_vftbl_start public _os_pad_vftbl_start,
#endif

#ifdef __os_xlc

/* Cset++ on AIX or OS/2 */

#define os_pad_vftbl_start class _os_pad_vftbl_start_p{char p[4];};
#define os_pad_vftbl_end char _os_pad_vftbl_end[4];

#define os_pad_vftbl_start8 char _os_pad_vftbl_end[4];
#define os_pad_vftbl_end8 char _os_pad_vftbl_end[8];

#define os_pad_vftbl_only class _os_pad_vftbl_only_p{char p[4];};
#define os_pad_vftbl_only8 char _os_pad_vftbl_only8[4];

#define os_pad_vbptr_start(x) class _os_pad_vbptr_start_##x##_p{char p[4];};
#define os_pad_vbptr_start8(x)  char _os_pad_vbptr_start8_##x[4];
#define os_pad_vbptr_end(x) char _os_pad_vbptr_end_##x[4];
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_##x[8];

#define os_pad_selfptr class _os_pad_selfptr_p {};

#define os_pad_vbtbl_start  char _os_pad_vbtbl_start[4];
#define os_pad_vbtbl_start8  char _os_pad_vbtbl_start8[8];
#define os_pad_vbtbl_end  char _os_pad_vbtbl_end[4];
#define os_pad_vbtbl_end8  char _os_pad_vbtbl_end8[8];

#define os_pad_ptr8(x) char _os_pad_ptr8_##x##[4];
#define os_pad_mem_ptr8(x) class _os_pad_mem_ptr8_##x##_p{char p[4];};
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_##x[4];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_##x[8];

#define os_pad_cons_disp(x) , public virtual _os_pad_cons_disp<x>
#define os_pad_base_vbtbl_start public _os_pad_vbtbl_start,
#define os_pad_base_vftbl_start
#endif

#ifdef _OS_MicrosoftCC

/* Visual C++ */

#define os_pad_vftbl_start class _os_pad_vftbl_start_p{char p[4];};
#define os_pad_vftbl_end char _os_pad_vftbl_end[4];

#define os_pad_vftbl_start8 char _os_pad_vftbl_end[4];
#define os_pad_vftbl_end8 char _os_pad_vftbl_end[8];

#define os_pad_vftbl_only class _os_pad_vftbl_only_p{char p[4];};
#define os_pad_vftbl_only8 char _os_pad_vftbl_only8[4];

#define os_pad_vbptr_start(x) char _os_pad_vbptr_start_##x [4];
#define os_pad_vbptr_start8(x)  char _os_pad_vbptr_start8_##x[8];
#define os_pad_vbptr_end(x) char _os_pad_vbptr_end_##x [4];
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_##x[8];

#define os_pad_selfptr  char _os_pad_selfptr[4];

#define os_pad_vbtbl_start  class _os_pad_vbtbl_p{char p[4];};
#define os_pad_vbtbl_start8  char _os_pad_vbtbl8[4];
#define os_pad_vbtbl_end  char _os_pad_vbtbl_end[4];
#define os_pad_vbtbl_end8  char _os_pad_vbtbl_end8[8];

#define os_pad_ptr8(x) char _os_pad_ptr8_##x##[4];
#define os_pad_mem_ptr8(x) char _os_pad_mem_ptr8_##x[4];
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_##x[8];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_##x[12];

#define os_pad_cons_disp(x)

#define os_pad_base_vbtbl_start 
#define os_pad_base_vftbl_start
#endif


#if defined(__os_cafe) && !defined(__os_sol64)
/* Sun C++ 4.0 */

#define os_pad_vftbl_start char _os_pad_vftbl_start[4];
#define os_pad_vftbl_end class _os_pad_vftbl_end_p{char p[4];}

#define os_pad_vftbl_start8 char _os_pad_vftbl_start[8];
#define os_pad_vftbl_end8 char _os_pad_vftbl_end[4];

#define os_pad_vftbl_only class _os_pad_vftbl_only_p{char p[4];}
#define os_pad_vftbl_only8 char _os_pad_vftbl_only8[4];

#ifdef _OS_ANSI_TOKENS
#define os_pad_vbptr_start(x) class _os_pad_vbptr_start_##x##_p{char p[4];};
#define os_pad_vbptr_start8(x)  char _os_pad_vbptr_start8_##x[4];
#define os_pad_vbptr_end(x) char _os_pad_vbptr_end_##x[4];
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_##x[8];
#else
#define os_pad_vbptr_start(x) class _os_pad_vbptr_start_/**/x/**/_p{char p[4];};
#define os_pad_vbptr_start8(x)  char _os_pad_vbptr_start8_/**/x[4];
#define os_pad_vbptr_end(x) char _os_pad_vbptr_end_/**/x[4];
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_/**/x[8];
#endif

#define os_pad_selfptr  char _os_pad_selfptr[4];

#define os_pad_vbtbl_start  char _os_pad_vbtbl_start[4];
#define os_pad_vbtbl_start8  char _os_pad_vbtbl_start8[8];
#define os_pad_vbtbl_end  char _os_pad_vbtbl_end[4];
#define os_pad_vbtbl_end8  char _os_pad_vbtbl_end8[8];

#ifdef _OS_ANSI_TOKENS
#define os_pad_ptr8(x) char _os_pad_ptr8_##x##[4];
#define os_pad_mem_ptr8(x) char _os_pad_mem_ptr8_##x[4];
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_##x[8];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_##x[12];
#else
#define os_pad_ptr8(x) char _os_pad_ptr8_/**/x[4];
#define os_pad_mem_ptr8(x) char _os_pad_mem_ptr8_/**/x[4];
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_/**/x[8];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_/**/x[12];
#endif

#define os_pad_cons_disp(x) , public virtual _os_pad_cons_disp<x>

#define os_pad_base_vbtbl_start public _os_pad_vbtbl_start,
#define os_pad_base_vftbl_start public _os_pad_vftbl_start,
#endif /* solaris 32 bit */

#if defined(__os_sol64)
/* Sun C++ 5.2 */

#define os_pad_vftbl_start char _os_pad_vftbl_start[4];
#define os_pad_vftbl_end class _os_pad_vftbl_end_p{char p[4];};

#define os_pad_vftbl_start8 char _os_pad_vftbl_start[8];
#define os_pad_vftbl_end8 char _os_pad_vftbl_end[4];

#define os_pad_vftbl_only class _os_pad_vftbl_only_p{char p[4];};
#define os_pad_vftbl_only8 class _os_pad_vftbl_only8_p{char p[8];};

#ifdef _OS_ANSI_TOKENS
#define os_pad_vbptr_start(x) class _os_pad_vbptr_start_##x##_p{char p[4];};
#define os_pad_vbptr_start8(x)  char _os_pad_vbptr_start8_##x[4];
#define os_pad_vbptr_end(x) char _os_pad_vbptr_end_##x[4];
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_##x[8];
#else
#define os_pad_vbptr_start(x) class _os_pad_vbptr_start_/**/x/**/_p{char p[4];};
#define os_pad_vbptr_start8(x)  class _os_pad_vbptr_start8_/**/x[4];
#define os_pad_vbptr_end(x) class _os_pad_vbptr_end_/**/x[4];
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_/**/x[8];
#endif

#define os_pad_selfptr  char _os_pad_selfptr[4];

#define os_pad_vbtbl_start  char _os_pad_vbtbl_start[4];
#define os_pad_vbtbl_start8  char _os_pad_vbtbl_start8[8];
#define os_pad_vbtbl_end  char _os_pad_vbtbl_end[4];
#define os_pad_vbtbl_end8  char _os_pad_vbtbl_end8[8];

#ifdef _OS_ANSI_TOKENS
#define os_pad_ptr8(x) class _os_pad_ptr8_##x##_p{char p[4];};
#define os_pad_mem_ptr8(x) class _os_pad_mem_ptr8_##x##_p{char p[8];};
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_##x##_p[4];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_##x##_p[8];
#else
#define os_pad_ptr8(x) class _os_pad_ptr8_/**/x_p { char p[4]; };
#define os_pad_mem_ptr8(x) class _os_pad_mem_ptr8_/**/x_p { char p[4]; };
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_/**/x_p[4];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_/**/x_p[8];
#endif

#define os_pad_cons_disp(x) , public virtual _os_pad_cons_disp<x>

#define os_pad_base_vbtbl_start public _os_pad_vbtbl_start,
#define os_pad_base_vftbl_start public _os_pad_vftbl_start,
#endif /* solaris 64 bit */


#ifdef _OS_EPC

/* EPC C++ */

#define os_pad_vftbl_start class _os_pad_vftbl_start_p{char p[4];}
#define os_pad_vftbl_end char _os_pad_vftbl_end[4];

#define os_pad_vftbl_start8 char _os_pad_vftbl_start[4];
#define os_pad_vftbl_end8 char _os_pad_vftbl_end[8];

#define os_pad_vftbl_only class _os_pad_vftbl_only_p{char p[4];}
#define os_pad_vftbl_only8 char _os_pad_vftbl_only8[4];

#ifdef _OS_ANSI_TOKENS
#define os_pad_vbptr_start(x) char _os_pad_vbptr_start_##x[4];
#define os_pad_vbptr_start8(x)  char _os_pad_vbptr_start8_##x[8];
#define os_pad_vbptr_end(x) class _os_pad_vbptr_end_##x##_p{char p[4];};
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_##x[4];
#else
#define os_pad_vbptr_start(x) char _os_pad_vbptr_start_/**/x[4];
#define os_pad_vbptr_start8(x)  char _os_pad_vbptr_start8_/**/x[8];
#define os_pad_vbptr_end(x) class _os_pad_vbptr_end_/**/x/**/_p{char p[4];};
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_/**/x[4];
#endif

#define os_pad_selfptr  char _os_pad_selfptr[4];

#define os_pad_vbtbl_start  char _os_pad_vbtbl_start[4];
#define os_pad_vbtbl_start8  char _os_pad_vbtbl_start8[8];
#define os_pad_vbtbl_end  char _os_pad_vbtbl_end[4];
#define os_pad_vbtbl_end8  char _os_pad_vbtbl_end8[8];

#ifdef _OS_ANSI_TOKENS
#define os_pad_ptr8(x) char _os_pad_ptr8_##x##[4];
#define os_pad_mem_ptr8(x) char _os_pad_mem_ptr8_##x[4];
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_##x[8];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_##x[12];
#else
#define os_pad_ptr8(x) char _os_pad_ptr8_/**/x[4];
#define os_pad_mem_ptr8(x) char _os_pad_mem_ptr8_/**/x[4];
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_/**/x[8];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_/**/x[12];
#endif

#define os_pad_cons_disp(x) , public virtual _os_pad_cons_disp<x>

#define os_pad_base_vbtbl_start public _os_pad_vbtbl_start,
#define os_pad_base_vftbl_start
#endif


#if defined(_OS_DECCXX) & !defined(_OS_DECCXX64)

/* 32 Dec C++ */

#define os_pad_vftbl_start char _os_pad_vftbl_start[4];
#define os_pad_vftbl_end class _os_pad_vftbl_end_p{char p[4];};

#define os_pad_vftbl_start8 char _os_pad_vftbl_start8[8];
#define os_pad_vftbl_end8 char _os_pad_vftbl_end8[4];

#define os_pad_vftbl_only class _os_pad_vftbl_only_p{char p[4];};
#define os_pad_vftbl_only8 char _os_pad_vftbl_only8[4];

#define os_pad_vbptr_start(x) char _os_pad_vbptr_start_##x[4];
#define os_pad_vbptr_start8(x) char _os_pad_vbptr_start8_##x[8];
#define os_pad_vbptr_end(x) char _os_pad_vbptr_end_##x[4];
#define os_pad_vbptr_end8(x) char _os_pad_vbptr_end8_##x[8];

#define os_pad_selfptr  char _os_pad_selfptr[4];

#define os_pad_vbtbl_start  char _os_pad_vbtbl_start[4];
#define os_pad_vbtbl_start8  char _os_pad_vbtbl_start8[8];
#define os_pad_vbtbl_end class _os_pad_vbtbl_end_p{char p[4];};
#define os_pad_vbtbl_end8  char _os_pad_vbtbl_end8[4];

#define os_pad_ptr8(x) char _os_pad_ptr8_##x##[4];
#define os_pad_mem_ptr8(x) class _os_pad_mem_ptr8_##x##_p{char p[4];};
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_##x[4];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_##x[8];

#define os_pad_cons_disp(x) , public virtual _os_pad_cons_disp<x>

#define os_pad_base_vbtbl_start public _os_pad_vbtbl_start,
#define os_pad_base_vftbl_start public _os_pad_vftbl_start,
#endif

#if defined(_OS_DECCXX64)

/* 64 bit Dec C++ */

#define os_pad_vftbl_start char _os_pad_vftbl_start[4];
#define os_pad_vftbl_end class _os_pad_vftbl_end_p{char p[4];};

#define os_pad_vftbl_start8 char _os_pad_vftbl_start8[8];
#define os_pad_vftbl_end8 class _os_pad_vftbl_end8_p{char p[8];};

#define os_pad_vftbl_only class _os_pad_vftbl_only_p{char p[4];};
#define os_pad_vftbl_only8 class _os_pad_vftbl_only8_p{char p[8];};

#define os_pad_vbptr_start(x) char _os_pad_vbptr_start_##x[4];
#define os_pad_vbptr_start8(x) char _os_pad_vbptr_start8_##x[8];
#define os_pad_vbptr_end(x) char _os_pad_vbptr_end_##x[4];
#define os_pad_vbptr_end8(x) char _os_pad_vbptr_end8_##x[8];

#define os_pad_selfptr  char _os_pad_selfptr[4];

#define os_pad_vbtbl_start  char _os_pad_vbtbl_start[4];
#define os_pad_vbtbl_start8  char _os_pad_vbtbl_start8[8];
#define os_pad_vbtbl_end class _os_pad_vbtbl_end_p{char p[4];};
#define os_pad_vbtbl_end8  class _os_pad_vbtbl_end8_p{char p[8];};

#define os_pad_ptr8(x) class _os_pad_ptr8_##x##_p{char p[4];};
#define os_pad_mem_ptr8(x) class _os_pad_mem_ptr8_##x##_p{char p[8];};
#define os_pad_mem_ptr12(x) class _os_pad_mem_ptr12_##x##_p{char p[12];};
#define os_pad_mem_ptr16(x) class _os_pad_mem_ptr16_##x##_p{char p[16];};

#define os_pad_cons_disp(x) , public virtual _os_pad_cons_disp<x>

#define os_pad_base_vbtbl_start public _os_pad_vbtbl_start,
#define os_pad_base_vftbl_start public _os_pad_vftbl_start,
#endif

#if defined(__os_hp64)

#define os_pad_vftbl_start class _os_pad_vftbl_start_p{char p[4];};
#define os_pad_vftbl_end class _os_pad_vftbl_end_p{char p[4];};

#define os_pad_vftbl_start8 char _os_pad_vftbl_end[4];
#define os_pad_vftbl_end8 class _os_pad_vftbl_end8_p{char p[8];};

#define os_pad_vftbl_only class _os_pad_vftbl_only_p{char p[4];};
#define os_pad_vftbl_only8 class _os_pad_vftbl_only8_p{char p[8];};

#define os_pad_vbptr_start(x) char _os_pad_vbptr_start8_##x[4];
#define os_pad_vbptr_start8(x) char _os_pad_vbptr_start8_##x[8];
#define os_pad_vbptr_end(x) char _os_pad_vbptr_end_##x[4];
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_##x[8];

#define os_pad_selfptr char _os_pad_selfptr[4];

#define os_pad_vbtbl_start  char _os_pad_vbtbl_start[4];
#define os_pad_vbtbl_start8  char _os_pad_vbtbl_start8[8];
#define os_pad_vbtbl_end  char _os_pad_vbtbl_end[4];
#define os_pad_vbtbl_end8  char _os_pad_vbtbl_end8[8];


#define os_pad_ptr8(x) class _os_pad_ptr8_##x##_p{char p[4];};

#define os_pad_mem_ptr8(x) class _os_pad_mem_ptr8_##x##_p { char p[8]; };
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_##x##_p[4];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_##x##_p[8];


#define os_pad_cons_disp(x) , public virtual _os_pad_cons_disp<x>
#define os_pad_base_vbtbl_start public _os_pad_vbtbl_start,
#define os_pad_base_vftbl_start
#endif /* __os_hp64  hpux 11.0 64bit */

#if defined(__os_hp32)

#define os_pad_vftbl_start class _os_pad_vftbl_start_p{char p[4];};
#define os_pad_vftbl_end char _os_pad_vftbl_end[4];

#define os_pad_vftbl_start8 char _os_pad_vftbl_end[4];
#define os_pad_vftbl_end8 char _os_pad_vftbl_end[8];

#define os_pad_vftbl_only class _os_pad_vftbl_only_p{char p[4];};
#define os_pad_vftbl_only8 char _os_pad_vftbl_only8[4];

#define os_pad_vbptr_start(x) char _os_pad_vbptr_start_##x[4];
#define os_pad_vbptr_start8(x) char _os_pad_vbptr_start8_##x[8];
#define os_pad_vbptr_end(x) char _os_pad_vbptr_end_##x[4];
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_##x[8];

#define os_pad_selfptr char _os_pad_selfptr[4];

#define os_pad_vbtbl_start  char _os_pad_vbtbl_start[4];
#define os_pad_vbtbl_start8  char _os_pad_vbtbl_start8[8];
#define os_pad_vbtbl_end  char _os_pad_vbtbl_end[4];
#define os_pad_vbtbl_end8  char _os_pad_vbtbl_end8[8];

#define os_pad_ptr8(x) char _os_pad_ptr8_##x[4];
#define os_pad_mem_ptr8(x)  char _os_pad_mem_ptr8_##x##[4];
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_##x##[8];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_##x##[12];

#define os_pad_cons_disp(x) , public virtual _os_pad_cons_disp<x>
#define os_pad_base_vbtbl_start public _os_pad_vbtbl_start,
#define os_pad_base_vftbl_start

#endif /* __os_hp32  hpux 11.0 32bit */

#ifdef __os_linux


#define os_pad_vftbl_start char _os_pad_vftbl_start[4];
#define os_pad_vftbl_end class _os_pad_vftbl_end_p{char p[4];}

#define os_pad_vftbl_start8 char _os_pad_vftbl_start[8];
#define os_pad_vftbl_end8 char _os_pad_vftbl_end[4];

#define os_pad_vftbl_only class _os_pad_vftbl_only_p{char p[4];}
#define os_pad_vftbl_only8 char _os_pad_vftbl_only8[4];

#ifdef _OS_ANSI_TOKENS
#define os_pad_vbptr_start(x) class _os_pad_vbptr_start_##x##_p{char p[4];};
#define os_pad_vbptr_start8(x)  char _os_pad_vbptr_start8_##x[4];
#define os_pad_vbptr_end(x) char _os_pad_vbptr_end_##x[4];
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_##x[8];
#else
#define os_pad_vbptr_start(x) class _os_pad_vbptr_start_/**/x/**/_p{char p[4];};
#define os_pad_vbptr_start8(x)  char _os_pad_vbptr_start8_/**/x[4];
#define os_pad_vbptr_end(x) char _os_pad_vbptr_end_/**/x[4];
#define os_pad_vbptr_end8(x)  char _os_pad_vbptr_end8_/**/x[8];
#endif

#define os_pad_selfptr  char _os_pad_selfptr[4];

#define os_pad_vbtbl_start  char _os_pad_vbtbl_start[4];
#define os_pad_vbtbl_start8  char _os_pad_vbtbl_start8[8];
#define os_pad_vbtbl_end  char _os_pad_vbtbl_end[4];
#define os_pad_vbtbl_end8  char _os_pad_vbtbl_end8[8];

#ifdef _OS_ANSI_TOKENS
#define os_pad_ptr8(x) char _os_pad_ptr8_##x##[4];
#define os_pad_mem_ptr8(x) char _os_pad_mem_ptr8_##x[4];
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_##x[8];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_##x[12];
#else
#define os_pad_ptr8(x) char _os_pad_ptr8_/**/x[4];
#define os_pad_mem_ptr8(x) char _os_pad_mem_ptr8_/**/x[4];
#define os_pad_mem_ptr12(x) char _os_pad_mem_ptr12_/**/x[8];
#define os_pad_mem_ptr16(x) char _os_pad_mem_ptr16_/**/x[12];
#endif

#define os_pad_cons_disp(x) , public virtual _os_pad_cons_disp<x>

#define os_pad_base_vbtbl_start public _os_pad_vbtbl_start,
#define os_pad_base_vftbl_start public _os_pad_vftbl_start,


#endif /* __os_linux */

/* introduce global definition of marker classes to force nesting */
class _os_pad_vftbl_start_p{char p[4];};
class _os_pad_vftbl_end_p{char p[4];};
class _os_pad_vftbl_only_p{char p[4];};
class _os_pad_vftbl_start8_p{char p[8];};
class _os_pad_vftbl_end8_p{char p[8];};
class _os_pad_vftbl_only8_p{char p[4];};
class _os_pad_vbptr_start_1_p{char p[4];};
class _os_pad_vbptr_end_1_p{char p[4];};
class _os_pad_vbptr_start8_1_p{char p[8];};
class _os_pad_vbptr_end8_1_p{char p[8];};
class _os_pad_vbptr_start_2_p{char p[4];};
class _os_pad_vbptr_end_2_p{char p[4];};
class _os_pad_vbptr_start8_2_p{char p[8];};
class _os_pad_vbptr_end8_2_p{char p[8];};
class _os_pad_selfptr_p{char p[4];};
class _os_pad_vbtbl_start_p{char p[4];};
class _os_pad_vbtbl_end_p{char p[4];};
class _os_pad_vbtbl_start8_p{char p[8];};
class _os_pad_vbtbl_end8_p{char p[8];};
class _os_pad_ptr8_p{char p[8]; };
class _os_pad_mem_ptr8_p{char p[8]; };
class _os_pad_mem_ptr12_p{char p[12]; };
class _os_pad_mem_ptr16_p{char p[16]; };
class _os_align_spec { char _os_pad[1]; };

class _os_pad_vbtbl_start { char _os_pad[4]; };
class _os_pad_vftbl_start { char _os_pad[4]; };


#include <ostore/hdrend.hh>
#endif
