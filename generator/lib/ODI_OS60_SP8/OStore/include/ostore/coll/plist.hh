/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _COLL_LIST_ARRAY
#define _COLL_LIST_ARRAY

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>

#include <ostore/coll/coll.hh>
#include <ostore/coll/cursor.hh>
#include <ostore/coll/collptr.hh>

#else

#include <os_pse/psecoll/hdrstart.hh>

#include <os_pse/coll/coll.hh>
#include <os_pse/coll/cursor.hh>
#include <os_pse/coll/collptr.hh>
_OS_BEGIN_NAMESPACE(os_pse)

#endif

/*****************************************************************************
* 									     *
* A list implementation. This is the list implementation of choice, when the *
* list is created and maintained by appending elements to the list or	     *
* deleting elements at the end of the list. This implementation makes very   *
* efficient use of storage. The list can be "tuned" so that the overhead is  *
* exactly "n" words of storage if the list has "n" members. This storage     *
* efficiency is obtained at some cost in the time complexity associated with *
* inserting elements in the middle of the list. Such an insertion takes O(n) *
* time on the average. For lists that need effecient insertion operations,   *
* the cons_list is a more suitable representation.			     *
* 									     *
******************************************************************************/

/* ---------------------------------------------------------------------
 * Forward declarations
 * ------------------------------------------------------------------ */

class _Packed_list_cursor;

/* ---------------------------------------------------------------------
 * typedefs
 * ------------------------------------------------------------------ */

typedef const void** const_void_star_star;

/* ---------------------------------------------------------------------
 * os_packed_list
 */

class _OS_COLL_IMPORT os_packed_list : public os_collection {

  enum { 
	no_slot = -1,
	min_list_size = 5 /* never reduce the size of the list below this */
  };
  enum { move_cursor_next, move_cursor_previous };

protected:
  os_unsigned_int32 list_entries; /* the number of valid entries in the list */
  os_unsigned_int32 list_size;    /* the current size of the list array */
  const void_coll_ptr  *alist,    /* the array holding the list */
                       *tail ;    /* the last element in the list, 
		    		     0 if no elements*/
  
  _Indexes * index_info;
  os_unsigned_int32 lower_bound ;
  
private:
  /* -------------------------------------------------------------------
   * representation-specific part of the implementation
   * ---------------------------------------------------------------- */

  const void_coll_ptr * _alloc_next_free_slot(const void_coll_ptr *p) ;
  void _dealloc_slot(const void_coll_ptr*p, _Packed_list_cursor* c = 0) ;
  const void_coll_ptr *_containing_slot(const void* e) const ;
  void _make_free_block(const void_coll_ptr*head, const void_coll_ptr*tail) ;
  const void_coll_ptr *_first_slot() const;
  const void_coll_ptr *_last_slot() const;
  const void_coll_ptr *_next_slot(const void_coll_ptr*) const;
  const void_coll_ptr *_previous_slot(const void_coll_ptr*) const;
  /* obtain the position of the slot in the list */
  os_unsigned_int32 _slot_pos(const void_coll_ptr*) const ;
  /* inverse of the above */
  const void_coll_ptr * _pos_slot(os_unsigned_int32 i) const ;
  const void_coll_ptr * _find_slot(os_unsigned_int32 pos) const ;

  os_int32 _free_slot_header(const void_coll_ptr *p) const
  {
    return ((p >= alist) &&
	      (p < &alist[list_size]) &&
	      ((void*)*p >= (void*)p) &&
	      ((void*)*p < (void*)&alist[list_size]));
  }
  os_int32 _free_slot_trailer(const void_coll_ptr *p) const
  {
    return ((p >= alist) &&
	      (p < &alist[list_size]) &&
	      ((void*)*p <= (void*)p) &&
	      ((void*)*p >= (void*)alist));
  }

  os_int32 _value_at_cursor(_Packed_list_cursor&c, const void* &e) const;
  void _shuffle_down(const void_coll_ptr*p, 
                     const void_coll_ptr*l, _Packed_list_cursor* c);

  void _adjust(os_unsigned_int32 size = 0, os_cursor *c=0) ;
  void _grow(os_unsigned_int32 size = 0, os_cursor *c=0) ;
  
  /* constructor used internally when reorganizing a list */
  os_packed_list(os_packed_list&) ;
  void _compact(_Packed_list_cursor *c=0) ;

  /* -------------------------------------------------------------------
   * _set_size(): compute the size and...  compute the trigger points 
   * associated with the collection size; these trigger points may 
   * initiate either a mutation, or a reorganization.
   * ---------------------------------------------------------------- */

  os_unsigned_int32 _set_size(os_unsigned_int32 size) ;

  void __clear() ;
  void _clear_contents_and_indexes() ;
  os_int32 check_for_duplicates(const void* e) const ;

private:
  /* -------------------------------------------------------------------
   * collection implementation protocol
   * ---------------------------------------------------------------- */

  virtual void* _pick() const;
  virtual void* _only() const ;
  virtual void _insert(os_void_const_p);
  virtual os_int32 _remove(os_void_const_p);
  virtual void* _retrieve(os_unsigned_int32 position) const;
  virtual os_int32 _contains(os_void_const_p) const;
  virtual os_int32 _count(os_void_const_p) const ;
  virtual void _insert_after(os_void_const_p p, os_unsigned_int32 position) ;
  virtual void _insert_before(os_void_const_p p, os_unsigned_int32 position) ;
  virtual void _remove_at(os_unsigned_int32 position) ;
  virtual void* _replace_at(os_void_const_p p, os_unsigned_int32 position) ;
  virtual os_int32 _remove_all(os_void_const_p);
  void _clear() ;

private:
  /* -------------------------------------------------------------------
   * List-specific update protocol
   * ---------------------------------------------------------------- */

  virtual void _insert_first(os_void_const_p p) ;
  virtual void _insert_last(os_void_const_p p) ;
  virtual os_int32 _remove_first(os_void_const_p &) ;
  virtual os_int32 _remove_last(os_void_const_p &) ;
  virtual os_int32 _retrieve_first(os_void_const_p &) const;
  virtual os_int32 _retrieve_last(os_void_const_p &) const;

  /* -------------------------------------------------------------------
   * cursor protocol
   * ---------------------------------------------------------------- */

  virtual os_int32 _first(os_cursor&, void* &) const ;
  virtual os_int32 _last(os_cursor&, void* &) const ;
  virtual os_int32 _next(os_cursor&, void* &) const ;
  virtual os_int32 _previous(os_cursor&, void* &) const ;
  virtual void _insert_after(os_void_const_p p, const os_cursor& c) ;
  virtual void _insert_before(os_void_const_p p, const os_cursor&c) ;
  virtual void _remove_at(const os_cursor &c) ;
  virtual void* _replace_at(os_void_const_p p, const os_cursor& c) ;
  virtual void* _retrieve(const os_cursor& c) const;

  void normalize_cursor(os_cursor &) const;
  void denormalize_cursor(os_cursor &) const;

  /* -------------------------------------------------------------------
   * behavior protocol
   * ---------------------------------------------------------------- */

  os_unsigned_int32 _get_behavior() const;

  /* -------------------------------------------------------------------
   * other odds and ends
   * ---------------------------------------------------------------- */

  os_unsigned_int32 _cardinality() const;
  os_int32 _empty() const;
  /* For queries of the form [: this == foo :] */
  os_boolean _fast_count() const;
  
  virtual void _re_initialize(os_unsigned_int32 size);

  /* -------------------------------------------------------------------
   * check_rep_invariants
   * ---------------------------------------------------------------- */

  virtual void _check_rep_invariants() const;

  virtual char *_rep_name() const;
  virtual os_int32 _rep_enum() const;
     
public:
  /* -------------------------------------------------------------------
   * constructors/destructors
   * ---------------------------------------------------------------- */

  os_packed_list(os_unsigned_int32 size = 0);
  virtual ~os_packed_list();

  static os_typespec* get_os_typespec();  
  /* -------------------------------------------------------------------
   * assignment operators are not inherited, so supply one
   * ---------------------------------------------------------------- */

  os_packed_list& operator =(const os_packed_list& c)
    { return (os_packed_list&)os_collection::operator =(c); }
  os_packed_list& operator =(const os_collection& c)
    { return (os_packed_list&)os_collection::operator =(c); }
  os_packed_list& operator =(const void* e)
    { return (os_packed_list &)os_collection::operator =(e); }

 /* -------------------------------------------------------------------
  *  osevol and oscompactor specific functions.  See collevl2.cc for use,
  *  although, an os_packed_list does no schema evolution.
  * ---------------------------------------------------------------- */
private:
   virtual void _set_untransformed(os_boolean flag) {};
   virtual void evolve_rep() {};

private:
  /* -------------------------------------------------------------------
   * Index functions
   * ---------------------------------------------------------------- */

  os_int32 has_indexes() const;
  _Indexes*& indexes();

}; /* class os_packed_list */

/* ---------------------------------------------------------------------
 * _Packed_list_cursor
 */

class _Packed_list_cursor : public os_cursor {

public:
  friend class os_packed_list;

  void_coll_ptr * ppos() { return (void_coll_ptr*)(void*)get_void0(); }

  /* The following function can be removed at a release when compatibility
     is not an issue. */
  void_coll_ptr & ppos_ref() {return void0;}

  os_unsigned_int32& subscr() { return os4u1; };

  void set_ppos(const void_coll_ptr* s) { set_void0((void*)s); set_more(s != 0); }

public:
  _Packed_list_cursor(const os_collection& c) : os_cursor (c) {}
  ~_Packed_list_cursor() {}

  static os_typespec* get_os_typespec(); 
}; /* class _Packed_list_cursor */

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif

