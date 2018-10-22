/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#if !defined(_OS_PSE_COLL)

#include <ostore/hdrstart.hh>
#include <ostore/coll/fcncache.hh>

#else

#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/fcncache.hh>

#endif

#ifdef _OS_PSE_COLL
_OS_BEGIN_NAMESPACE(os_pse) 
#endif
extern "C" {
extern _OS_DLLIMPORT(_OS_COLL) _Function_cache* _Mapping_fcn_cache;
}
#ifdef _OS_PSE_COLL
_OS_END_NAMESPACE 

#endif //_OS_PSE_COLL
#ifdef _OS_ANSI_TOKENS
#define os_assign_cat(suf) os_coll_Afcn_##suf
#else
#define os_assign_cat(suf) os_coll_Afcn_/**/suf
#endif

#ifdef _OS_ANSI_TOKENS
#define os_index_key(T,R,H) { \
     if(_Mapping_fcn_cache) _Mapping_fcn_cache->insert(#T, R, H); }
#define os_index_key_rank_function(T,R) { \
     if(_Mapping_fcn_cache) _Mapping_fcn_cache->replace_rank(#T, R); }
#define os_index_key_hash_function(T,H) { \
     if(_Mapping_fcn_cache) _Mapping_fcn_cache->replace_hash(#T, H); }
#define os_assign_function(T) { \
     if(_Mapping_fcn_cache) \
       _Mapping_fcn_cache->insert_assign_fcn(#T,os_assign_cat(T)); }
#else
#define os_index_key(T,R,H) { \
      if(_Mapping_fcn_cache) _Mapping_fcn_cache->insert("T", R, H); }
#define os_index_key_rank_function(T,R) { \
      if(_Mapping_fcn_cache) _Mapping_fcn_cache->replace_rank("T", R); }
#define os_index_key_hash_function(T,H) { \
      if(_Mapping_fcn_cache) _Mapping_fcn_cache->replace_hash("T", H); }
#define os_assign_function(T) { \
     if(_Mapping_fcn_cache) \
       _Mapping_fcn_cache->insert_assign_fcn("T",os_assign_cat(T)); }
#endif
#ifdef _OS_ANSI_TOKENS
#define os_assign_cat(suf) os_coll_Afcn_##suf
#else
#define os_assign_cat(suf) os_coll_Afcn_/**/suf
#endif
#define os_assign_function_body(T) \
static void  os_assign_cat(T) (void * to, void* from) { \
   T * _to = (T*)to; \
   T * _from = (T*)from; \
   *_to = *_from; \
} 


#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
#include <os_pse/psecoll/hdrend.hh>
#endif
