/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef __RH_DYNHASH_H
#define __RH_DYNHASH_H
#if !defined(_OS_PSE_COLL)
#include <ostore/coll/cursor.hh>
#include <ostore/coll/rh.hh>
#else
#include <os_pse/coll/cursor.hh>
#include <os_pse/coll/rh.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

/* ---------------------------------------------------------------------
 * _RH_dynhash
 */

class _OS_COLL_IMPORT _RH_dynhash : public _Rhash {

public:

  _RH_dynhash(os_unsigned_int32 capacity,  
          os_unsigned_int32 option = 0);
  ~_RH_dynhash();

  /* testing */
  virtual char* _rep_type() const;

  virtual void* slot_value(
        const void*, const _Rhash_cursor*, os_unsigned_int32) const;
  virtual os_boolean slot_key_eq(const void*,os_unsigned_int32,
                                 const void*, _Rank_fcn) const;
  virtual void* slot_pick(const void*, os_unsigned_int32) const;
  virtual os_boolean slot_first(const void*, _Rhash_cursor*, 
                                void*&,os_unsigned_int32 ) const;
  virtual os_boolean slot_last(const void*, _Rhash_cursor*, 
                                void*&, os_unsigned_int32) const;
  virtual os_boolean slot_next(const void*, _Rhash_cursor*,
                               void*&, os_unsigned_int32 ) const;
  virtual os_boolean slot_previous(const void*, _Rhash_cursor*,
                               void*&, os_unsigned_int32 ) const;
  virtual os_boolean slot_null(const void*, const _Rhash_cursor*,
                               os_unsigned_int32 ) const;
  virtual os_boolean stores_overflow();
  virtual os_int32 slot_count(void*, os_unsigned_int32) const;
  virtual _RH_slot_status slot_status(void*, const void*, _RH_search_type,
                                      _Rank_fcn, os_unsigned_int32) const;

  virtual void* slot_key(const void*, os_unsigned_int32) const;
  virtual os_unsigned_int32 slot_hash(const void*, os_unsigned_int32) const; 
  virtual os_boolean slot_occupied(const void*) const;
  virtual void slot_reclaim_oflo(void*, os_unsigned_int32);

private:
  virtual os_boolean slot_contains(void*, 
                                   os_unsigned_int32, 
                                   const void*) const;
  virtual os_boolean  slot_insert(void*,os_unsigned_int32, 
                                  os_unsigned_int32, 
                                  const void*, const void*,
                                  os_unsigned_int32);
  virtual void slot_remove(void*, os_unsigned_int32, 
                           os_unsigned_int32, const void*, os_boolean&);
  virtual void slot_assign(void*, const void*);

  virtual char* allocate_slots(os_unsigned_int32, os_cluster *, void *);
  virtual void delete_slots(void *);


protected:

  virtual void find_functions(_Rank_fcn&, _Hash_fcn&) const;
  virtual char *_rep_name() const;

public:

  static os_typespec* get_os_typespec();


};

#ifdef _OS_PSE_COLL
_OS_END_NAMESPACE
#endif

#endif /* __RH_DYNHASH_H */
