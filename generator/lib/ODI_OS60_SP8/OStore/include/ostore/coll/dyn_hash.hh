/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/* -*- Mode:C++ -*- */

#ifndef _COLL_DYNA_HASH
#define _COLL_DYNA_HASH
#if !defined(_OS_PSE_COLL)
#include <ostore/coll/cursor.hh>
#include <ostore/coll/rh.hh>
#include <ostore/coll/rh_dynhash.hh>
#else
#include <os_pse/coll/cursor.hh>
#include <os_pse/coll/rh.hh>
#include <os_pse/coll/rh_dynhash.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

/* ---------------------------------------------------------------------
 * Forward declarations
 * ------------------------------------------------------------------ */

class os_dictionary_cursor;

/* ---------------------------------------------------------------------
 * os_dyn_hash
 */

class _OS_COLL_IMPORT os_dyn_hash : public _RH_dynhash {

  friend class os_dyn_hash_descriptor;


protected:

  /* -------------------------------------------------------------------
   * rep-specific functions
   * ---------------------------------------------------------------- */

  void do_insert_checks(const void* v);

  /* -------------------------------------------------------------------
   * -------------------------------------------------------------------
   * Functions inherited from os_collection 
   * ----------------------------------------------------------------
   * ---------------------------------------------------------------- */

protected:

  /* List-specific update and access protocol */
  virtual void _insert_first(os_void_const_p p);
  virtual void _insert_last(os_void_const_p p);
  virtual os_int32 _remove_first(os_void_const_p &);
  virtual os_int32 _remove_last(os_void_const_p &);
  virtual os_int32 _retrieve_first(os_void_const_p &) const;
  virtual os_int32 _retrieve_last(os_void_const_p &) const;
  
  virtual void _insert_after(os_void_const_p p, const os_cursor& c);
  virtual void _insert_before(os_void_const_p p, const os_cursor& c);
  virtual void _remove_at(const os_cursor& c);
  virtual void* _replace_at(os_void_const_p p, const os_cursor& c);
  
  virtual void _insert_after(os_void_const_p p, os_unsigned_int32 position);
  virtual void _insert_before(os_void_const_p p, os_unsigned_int32 position);
  virtual void _remove_at(os_unsigned_int32 position);
  virtual void* _replace_at(os_void_const_p p, os_unsigned_int32 position);

protected:

  /* -------------------------------------------------------------------
   * behavior protocol
   * ---------------------------------------------------------------- */

  virtual os_unsigned_int32 _get_behavior() const { return 0; }
  
  virtual os_int32 _rep_enum() const 
    {return os_dyn_hash_rep;}
protected:

  /* -------------------------------------------------------------------
   * the collections protocol
   * ---------------------------------------------------------------- */
  
  virtual void* _pick() const;
  virtual void* _only() const;

  virtual void _insert(os_void_const_p);
  virtual os_int32 _remove(os_void_const_p);
  
  /* these return true if the element was removed, modifies the argument to */

  virtual void* _retrieve(const os_cursor& c) const ;
  virtual void* _retrieve(os_unsigned_int32) const ;
  
  virtual os_int32 _contains(os_void_const_p) const;
  virtual os_int32 _count(os_void_const_p) const ;

  
protected:

  /* -------------------------------------------------------------------
   * cursor protocol
   * ---------------------------------------------------------------- */

  virtual os_int32 _first(os_cursor&, void* &) const;
  virtual os_int32 _last(os_cursor&, void* &) const;
  virtual os_int32 _next(os_cursor&, void* &) const;
  virtual os_int32 _previous(os_cursor&, void* &) const;

protected:

  /* -------------------------------------------------------------------
   * other odds and ends
   * ---------------------------------------------------------------- */

  virtual void _clear();
  virtual os_int32 _empty() const;
  virtual os_boolean _fast_count() const;

public:
  /* ----------------------------------------------------------------
   * constructors and destructors
   * ---------------------------------------------------------------- */
   os_dyn_hash(os_unsigned_int32 size,
               os_unsigned_int32 option=0)
   : _RH_dynhash(size, option) {index_info = (_Indexes*)0;}
 
  virtual ~os_dyn_hash();

public:
  /* ----------------------------------------------------------------
   * public odds and endss
   * ---------------------------------------------------------------- */
  

  static os_typespec* get_os_typespec();

}; /* class os_dyn_hash */

#ifdef _OS_PSE_COLL
_OS_END_NAMESPACE
#endif
#endif /* _COLL_DYNA_HASH */
