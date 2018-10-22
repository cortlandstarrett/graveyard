/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
 */
#ifndef _fcncache
#define _fcncache

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#endif

/* From mapping.hh: */
#ifndef _MAPPING_FUNCTIONS
#define _MAPPING_FUNCTIONS
typedef os_int32 (*_Rank_fcn)(os_void_const_p, os_void_const_p);
typedef os_unsigned_int32 (*_Hash_fcn)(os_void_const_p);
typedef void (*_Assign_fcn) (void*);
#endif

#ifdef _OS_PSE_COLL
_OS_BEGIN_NAMESPACE(os_pse)
#endif

class os_dictionary;

class _Mapping_functions
{
  friend class _Function_cache;

private:
  char* type_name;
  _Rank_fcn rankf;
  _Hash_fcn hashf;
  _Assign_fcn assignf;
 
  _Mapping_functions(const char* t, _Rank_fcn r, _Hash_fcn h = 0, 
                     _Assign_fcn a = 0);
  ~_Mapping_functions();
};


class _OS_COLL_IMPORT _Function_cache
{
  friend class _Mapping;

private:
  os_dictionary* cache;

  char* most_recent_type;
  _Rank_fcn most_recent_rank;
  _Hash_fcn most_recent_hash;

public:
  _Function_cache();
  ~_Function_cache();

  void find_functions(const char* type, _Rank_fcn& r, _Hash_fcn& h,
		      os_boolean signal_if_not_found = 1);
  void find_assign_function(const char* type, _Assign_fcn& a,
		            os_boolean signal_if_not_found = 1);
  void insert(const char*, _Rank_fcn, _Hash_fcn = 0);
  void insert_assign_fcn(const char*, _Assign_fcn);
  void replace_rank(const char*, _Rank_fcn);
  void replace_hash(const char*, _Hash_fcn);
  void clear_cache() { delete most_recent_type; most_recent_type = 0; };

  static os_boolean is_strcmp(_Rank_fcn);
  static os_boolean is_strcoll(_Rank_fcn);
};


char* _Canonicalize_key_type(const char* type_name);

/* Alternative to default char* and char[] rank functions,
 * for internationalization.
 */

os_int32 _OS_COLL_IMPORT os_strcoll_for_char_pointer(const void*, const void*);
os_int32 _OS_COLL_IMPORT os_strcoll_for_char_array(const void*, const void*);


extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Int_rank(const void* x, const void* y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Char_rank(const void* x, const void* y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Short_rank(const void* x, const void* y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Ushort_rank(const void* x, const void* y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Uint_rank(const void* x, const void* y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Ushort_rank(const void* x, const void* y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Str_rank(const void* x, const void* y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Str_nocopy_rank(const void* x, const void* y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Char_arr_rank(const void* x, const void* y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Float_rank(const void* f, const void* g);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Double_rank(const void* f, const void* g);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Pvoid_rank(const void* _x, const void* _y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Ptr_rank(const void* _x, const void* _y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32 _Long_rank(const void* x, const void* y);
extern _OS_DLLIMPORT(_OS_COLL) os_int32  _Ulong_rank(const void* x, const void* y);

extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32 _Int_hash(const void* x);
extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32 _Char_hash(const void* x);
extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32 _Char_hash(const void* x);
extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32 _Short_hash(const void* x);
extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32 _Str_hash_khs(const void* p);
extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32 _Str_nocopy_hash_khs(const void* p);
extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32 _Float_hash(const void*);
extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32 _Double_hash(const void*);
extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32 _Pvoid_hash(const void* _x);
extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32 _Ptr_hash(const void* _x);
extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32  _Long_hash(const void* x);
/* hash into transient hashtable - regardless of whether or not _x
   is transient or persistent
*/
extern _OS_DLLIMPORT(_OS_COLL) os_unsigned_int32 _Ptr_hash_trans(const void* _x);

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
