/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _AM_RH_PT_HH
#define _AM_RH_PT_HH

/* ---------------------------------------------------------------------
 * Include files
 * ------------------------------------------------------------------ */

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#include <ostore/coll/rh.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/rh.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

/* ---------------------------------------------------------------------
 * _Rhash_pt
 */

template<class KEYTYPE>
class _Rhash_pt : public _Rhash {

public:
  _Rhash_pt(const char* keytype, os_unsigned_int32 capacity,
            os_unsigned_int32 options);
  ~_Rhash_pt();

  char* _rep_type() const;

protected:

  virtual os_boolean slot_key_eq(
  	const void*, os_unsigned_int32, const void*, _Rank_fcn ) const;
  virtual void* slot_pick(const void*, os_unsigned_int32) const;
  virtual os_boolean slot_first(
        const void*, _Rhash_cursor*, void*&, os_unsigned_int32) const;
  virtual os_boolean slot_last(
        const void*, _Rhash_cursor*, void*&, os_unsigned_int32) const;
  virtual os_boolean slot_next(
        const void*, _Rhash_cursor*, void*&, os_unsigned_int32) const;
  virtual os_boolean slot_previous(
        const void*, _Rhash_cursor*, void*&, os_unsigned_int32) const;
  virtual os_boolean slot_null(
        const void*, const _Rhash_cursor*, os_unsigned_int32) const;
  virtual os_boolean stores_overflow();
  virtual os_int32 slot_count(void* ps, os_unsigned_int32) const;
  virtual _RH_slot_status slot_status(
  	void*, const void*, _RH_search_type, 
        _Rank_fcn, os_unsigned_int32) const;
  virtual void* slot_value(
        const void*,const _Rhash_cursor*, os_unsigned_int32) const;

  virtual void* slot_key(const void*, os_unsigned_int32) const;
  virtual os_unsigned_int32 slot_hash(
  	const void*, os_unsigned_int32 ) const;
  virtual os_boolean slot_occupied(const void*) const;
  virtual void slot_reclaim_oflo(void*, os_unsigned_int32);

protected:

  virtual char* allocate_slots(os_unsigned_int32, os_cluster *, void*);
  virtual void delete_slots(void*);
  os_boolean slot_contains(void*, os_unsigned_int32, const void*) const;
  os_boolean slot_insert(
  	void*, os_unsigned_int32, os_unsigned_int32, const void*, 
	const void*, os_unsigned_int32);
  void slot_remove(
  	void*, os_unsigned_int32, os_unsigned_int32, const void*, 
	os_boolean&);
  void slot_assign(void*, const void*);

  virtual void find_functions(_Rank_fcn& rfn, _Hash_fcn& hfn) const;

  virtual os_unsigned_int32 next_occupied_slot(
  	os_unsigned_int32, os_unsigned_int32 ) const;
  virtual os_unsigned_int32 previous_occupied_slot(
  	os_unsigned_int32, os_unsigned_int32 ) const;
  virtual os_unsigned_int32 first_occupied_slot(os_unsigned_int32) const;
  virtual os_unsigned_int32 last_occupied_slot(os_unsigned_int32) const;
  void do_char_star_key_insert(void * ps, void * v, char** k, os_unsigned_int32 h);  

public:
  os_boolean allow_dup() const
    {return  (get_flags() & _allow_dups); }

#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() { 
    return os_ts<_Rhash_pt<KEYTYPE > >::get(); }
#endif
};/* class _Rhash_pt */

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif /* _AM_RH_PT_HH */
