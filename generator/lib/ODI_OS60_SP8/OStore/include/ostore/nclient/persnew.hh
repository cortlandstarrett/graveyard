/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_PERSNEW
#define CLIENT_INTERFACE_PERSNEW 1

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/nclient/typedefs.hh>
#include <ostore/nclient/typespec.hh>

class os_database;
class os_segment;
class os_cluster;
class os_cluster_with;

/* Here are all of our global operator news, in several groups. */
/* the first argument is always the size */
_OS_DLLIMPORT(_OS_CLIENT) void * operator new (size_t _OS_DBALLOC_PARMS, os_database*, os_typespec*);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new _OS_VECTOR (size_t _OS_DBALLOC_PARMS, os_database*, os_typespec*, os_int32);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new (size_t _OS_DBALLOC_PARMS, os_segment*, os_typespec*);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new _OS_VECTOR (size_t _OS_DBALLOC_PARMS, os_segment*, os_typespec*, os_int32);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new (size_t _OS_DBALLOC_PARMS, os_cluster*, os_typespec*);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new _OS_VECTOR (size_t _OS_DBALLOC_PARMS, os_cluster*, os_typespec*, os_int32);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new (size_t _OS_DBALLOC_PARMS, os_cluster_with, os_typespec*);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new _OS_VECTOR (size_t _OS_DBALLOC_PARMS, os_cluster_with, os_typespec*, os_int32);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new (size_t _OS_DBALLOC_PARMS, os_database*, os_unsigned_int32, os_unsigned_int32, os_typespec*);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new _OS_VECTOR (size_t _OS_DBALLOC_PARMS, os_database*, os_unsigned_int32, os_unsigned_int32, os_typespec*, os_int32);
/* For callers inside the client */
class _CLIENT_database;
class _CLIENT_cluster;
_OS_DLLIMPORT(_OS_CLIENT) void * operator new (size_t _OS_DBALLOC_PARMS, _CLIENT_database*, os_typespec*);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new _OS_VECTOR (size_t _OS_DBALLOC_PARMS, _CLIENT_database*, os_typespec*, os_int32);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new (size_t size _OS_DBALLOC_PARMS, _CLIENT_cluster*, os_typespec*);
_OS_DLLIMPORT(_OS_CLIENT) void * operator new _OS_VECTOR (size_t size _OS_DBALLOC_PARMS, _CLIENT_cluster*, os_typespec*, os_int32);

/* To allocate an object nearby another object (if it is persistent,
 * at least in the same cluster of the same segment of the same database),
 * use os_cluster::with(ptr_to_another_object) as the first explicit arg to new
 */
class _OS_DLLIMPORT(_OS_CLIENT) os_cluster_with {
private:
  const void* cluster_with;		/* points to object in same cluster */ 
  os_cluster_with() { }			/* no-op constructor */
  friend class os_cluster;		/* only os_cluster::with can call the constructor */
public:
  const void* get() const {		/* accessor to retrieve argument */
    return cluster_with; }
};


/* placement delete operators for VC++ 6.0 */
#if (defined(_OS_DECCXX) && (__DECCXX_VER < 60300000)) || (_OS_MicrosoftCC >= 1200)    /* MSVC 6.0 and above */

/* for global operator news */
static inline
void operator delete(void* addr, os_database*, os_typespec*)
{ delete addr; }

static inline
void operator delete(void* addr, os_segment*, os_typespec*)
{ delete addr; }

static inline
void operator delete(void* addr, os_cluster*, os_typespec*)
{ delete addr; }

static inline
void operator delete(void* addr, os_cluster_with, os_typespec*)
{ delete addr; }

/* vector delete */
static inline
void operator delete _OS_VECTOR(void* addr, os_database*, os_typespec*, os_int32)
{ delete _OS_VECTOR addr; }

static inline
void operator delete _OS_VECTOR(void* addr, os_segment*, os_typespec*, os_int32)
{ delete _OS_VECTOR addr; }

static inline
void operator delete _OS_VECTOR(void* addr, os_cluster*, os_typespec*, os_int32)
{ delete _OS_VECTOR addr; }

static inline
void operator delete _OS_VECTOR(void* addr, os_cluster_with, os_typespec*, os_int32)
{ delete _OS_VECTOR addr; }

/* for callers inside the client */
static inline
void operator delete (void* addr, _CLIENT_database*, os_typespec*)
{ delete addr; }

static inline  
void operator delete _OS_VECTOR (void* addr, _CLIENT_database*, os_typespec*, os_int32)
{ delete _OS_VECTOR addr; }

static inline  
void operator delete (void* addr, _CLIENT_cluster*, os_typespec*)
{ delete addr; }

static inline  
void operator delete _OS_VECTOR (void* addr, _CLIENT_cluster*, os_typespec*, os_int32)
{ delete _OS_VECTOR addr; }

#endif

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_PERSNEW */
