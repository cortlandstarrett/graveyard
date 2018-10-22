/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
 */
#ifndef _os_dictionary_included
#define _os_dictionary_included

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#include <ostore/coll/coll.hh>
#include <ostore/coll/cursor.hh>
#include <ostore/coll/fcncache.hh>

#else
#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/coll.hh>
#include <os_pse/coll/cursor.hh>
#include <os_pse/coll/fcncache.hh>
#endif

/* ---------------------------------------------------------------------
 * enums
 * ------------------------------------------------------------------ */

#ifndef _DIRECTION_DEFINED
#define _DIRECTION_DEFINED
enum _Direction 
  { OS_CURSOR_FORWARD, OS_CURSOR_REVERSE, _Direction_pad = 1<<30 };
#endif

/* ---------------------------------------------------------------------
 * Macro definitions
 * ------------------------------------------------------------------ */

#ifndef mangle_bit
#define mangle_bit(bitfield, flag, mask) \
if(flag) bitfield |= mask; \
else bitfield &= ~mask;
#endif

#ifdef _OS_PSE_COLL
_OS_BEGIN_NAMESPACE(os_pse) 
#endif 

/* ---------------------------------------------------------------------
 * Forward declarations
 * ------------------------------------------------------------------ */

#ifndef _MAPPING_FUNCTIONS
#define _MAPPING_FUNCTIONS
typedef os_int32 (*_Rank_fcn)(os_void_const_p, os_void_const_p);
typedef os_unsigned_int32 (*_Hash_fcn)(os_void_const_p);
#endif

extern "C" {
extern _OS_DLLIMPORT(_OS_COLL) _Function_cache* _Mapping_fcn_cache;
}

class os_dictionary;
class _Fn_Pathop;

/* ---------------------------------------------------------------------
 * os_dictionary_cursor
 */

class _OS_COLL_IMPORT os_dictionary_cursor : public os_virtual_behavior64 {
public:
  os_dictionary_cursor() {};
  virtual ~os_dictionary_cursor();

  virtual void restrict(os_int32 /* os_collection::restriction */ r, const void* k) = 0;
  virtual void restrict(os_int32 r_lo, const void* k_lo, 
                os_int32 r_hi, const void* k_hi) = 0;
  virtual void unrestrict() = 0;


  virtual void remember(_os_cursor_holder &) = 0;
  virtual void restore(_os_cursor_holder &) = 0;
public:		      
  /* The rest of the protocol is for internal use only */
  enum _set_position { FIND_FIRST, DONT_FIND_FIRST, _set_position_pad = 1<<30 };
}; /* class os_dictionary_cursor */

/* ---------------------------------------------------------------------
 * os_dictionary
 */

class _OS_COLL_IMPORT os_dictionary : public os_collection {

friend class os_outofline_dictionary;

public:
  void insert(const void* v) { os_collection::insert(v); }
  os_int32 remove(const void* v) { return os_collection::remove(v); }
  os_boolean contains(const void* v) { return os_collection::contains(v); }
  void* pick() { return os_collection::pick(); }

  void insert(const void* key, const void* value);
  void remove(const void* key, const void* value);
  void remove_no_check(const void* key, const void* value);
  void* remove_value(const void* key, os_unsigned_int32 num = 1);
  os_unsigned_int32 count_values(const void* key) const;
  os_boolean contains(const void* key, const void* value) const;
  void* pick(os_coll_range& r) const;
  void* pick(const void* key) const;

  const void* retrieve_key(const os_cursor& c) const;

  os_dictionary() {};
  virtual ~os_dictionary();

  static os_dictionary* create(const void* where, _Coll_clustering,
			  const char* key_type,
			  os_unsigned_int32 key_size,
			  os_unsigned_int32 array_size,
			  os_unsigned_int32 capacity,
			  os_unsigned_int32 index_options,
			  os_boolean check_key_alignment = 1,
			  _Fn_Pathop* fnp = 0);

public:
  /* -------------------------------------------------------------------
   * The rest of the protocol is for internal use only.
   * ---------------------------------------------------------------- */

  virtual os_boolean _is_a_hashtable() const;

  /* -------------------------------------------------------------------
   * start and end iteration
   * ---------------------------------------------------------------- */
  
  virtual os_dictionary_cursor& __iteration_start(
        os_boolean pers = 0 ) const = 0;
  virtual os_dictionary_cursor& __iteration_start(
  	os_int32 /* restriction */, const void*, 
	os_boolean pers = 0 ) const = 0;
  virtual os_dictionary_cursor& __iteration_start(
  	os_int32 /* restriction */, const void*, os_int32 /* restriction */, 
	const void*, os_boolean pers = 0 ) const = 0;
  virtual void __iteration_end(os_dictionary_cursor&) const = 0;
  
  /* -------------------------------------------------------------------
   * navigation
   * ---------------------------------------------------------------- */

  virtual os_int32 __first(os_dictionary_cursor&, os_void_p&) const = 0;
  virtual os_int32 __last(os_dictionary_cursor&, os_void_p&) const = 0;
  virtual os_int32 __next(os_dictionary_cursor&, os_void_p&) const = 0;
  virtual os_int32 __previous(os_dictionary_cursor&, os_void_p&) const = 0;
  virtual os_int32 __OS_COLL_IS_NULL(const os_dictionary_cursor&) const = 0;
  virtual os_int32 __more(const os_dictionary_cursor&) const = 0;

  /* -------------------------------------------------------------------
   * retrieval
   * ---------------------------------------------------------------- */

  virtual void* __retrieve(const os_dictionary_cursor&) const = 0;
  virtual void* __retrieve_key(const os_dictionary_cursor&) const = 0;
  virtual void* __pick(os_unsigned_int32&) const = 0;
  virtual void* __pick(
  	os_int32 /* os_collection::restriction */, const void*, 
	os_unsigned_int32& ) const = 0;
  virtual void* __pick(
  	os_int32 /* os_collection::restriction */, const void*,
	os_int32 /* os_collection::restriction */, const void*,
	os_unsigned_int32& ) const = 0;

  /* -------------------------------------------------------------------
   * This is exactly identical to _only() except that it does raise 
   * exception when n_keys == 0. Currently only, _Rhash and _CM provide 
   * the implementation.
   * ---------------------------------------------------------------- */

  virtual void* __only(os_boolean& empty) const { empty=0; return (void*) 0; }

  virtual os_int32 __contains(const void* v, const void* k) const = 0;
  
  /* -------------------------------------------------------------------
   * update
   * ---------------------------------------------------------------- */

  virtual void __insert(
  	const void* v,const void* k, os_collection *cc,
	const void* keycopy=0, os_unsigned_int32 hashval = 0 ) = 0;
  virtual void __remove(const void* v, const void* k, os_collection * cc) = 0;

  /* -------------------------------------------------------------------
   * This is only supported by _CM and _Rhash
   * ---------------------------------------------------------------- */

  virtual void __remove(
  	const void*, const void*, os_boolean&, os_collection * cc) {}
  virtual void __insert(
  	const void*, const void*, os_collection *, const void*,os_boolean& )=0;
 
  virtual os_int32 __count(os_dictionary_cursor&) const = 0;
  virtual os_int32 __count(const void* /*key*/, const void* /*val*/) const=0;

  virtual os_int32 __duplicates() const = 0;
  virtual const char* _key_type() const = 0;
  virtual os_unsigned_int32 _key_size() const;

  

  /* -------------------------------------------------------------------
   * cursor maintenance
   * ---------------------------------------------------------------- */

  virtual void __reset(
  	os_dictionary_cursor&, const void*, const void*, _Direction ) = 0;
  virtual os_collection* _cursors() const = 0;

  /* -------------------------------------------------------------------
   * This is only implemented by _Rhash and _CM.  Calling this 
   * method without an implementation would result in an exception.
   * ---------------------------------------------------------------- */

  virtual void _set_allow_dup(os_unsigned_int32 flag);

protected:

  virtual void find_functions(_Rank_fcn&, _Hash_fcn&) const;


protected:

  /* -------------------------------------------------------------------
   * -------------------------------------------------------------------
   * The collections protocol
   * -------------------------------------------------------------------
   * ---------------------------------------------------------------- */

  /* -------------------------------------------------------------------
   * Index functions
   * ---------------------------------------------------------------- */

  virtual _Indexes*& indexes();
  virtual os_int32 has_indexes() const;

protected:

  /* -------------------------------------------------------------------
   * Behavior protocol
   * ---------------------------------------------------------------- */

  virtual os_unsigned_int32 _get_behavior() const;
  virtual void _check_rep_invariants() const;

  virtual void _re_initialize(os_unsigned_int32 size);

  /* the following two are here for compatability */ 
  virtual char *_rep_name() const;
  virtual os_int32 _rep_enum() const;

protected:

  /* -------------------------------------------------------------------
   * The collections protocol
   * ---------------------------------------------------------------- */

  virtual void* _pick() const;
  virtual void* _only() const;

  virtual void _insert(os_void_const_p);
  virtual os_int32 _remove(os_void_const_p);

  /* -------------------------------------------------------------------
   * These return true if the element was removed, modifies the
   * argument to.
   * ---------------------------------------------------------------- */

  virtual void* _retrieve(const os_cursor& c) const;
  virtual void* _retrieve(os_unsigned_int32) const;

  virtual os_int32 _contains(os_void_const_p) const;
  virtual os_int32 _count(os_void_const_p) const;

protected:

  /* -------------------------------------------------------------------
   * cursor protocol
   * ---------------------------------------------------------------- */

  virtual os_int32 _first(os_cursor&, os_void_p &) const;
  virtual os_int32 _last(os_cursor&, os_void_p &) const;
  virtual os_int32 _next(os_cursor&, os_void_p &) const;
  virtual os_int32 _previous(os_cursor&, os_void_p &) const;

protected:

  /* -------------------------------------------------------------------
   * other odds and ends
   * ---------------------------------------------------------------- */

  virtual os_boolean _fast_count() const;


public:

  /* -------------------------------------------------------------------
   * The values of these enums are crafted carefully so as to avoid 
   * the need for translation between os_index_path enums (used by 
   * _Mappings) and collections enums.
   * ---------------------------------------------------------------- */

  enum { 
       maintain_key_order = 1<<9,
       no_dup_keys = (1<<10) | (1<<11),
       signal_dup_keys = (1<<11) | (1<<10),
       use_reference = 1<<13,
       dont_maintain_cardinality = (1<<14),
       index_option_mask = 0x37,
       index_option_rightshift = 9
  };

public:

  /* -------------------------------------------------------------------
   * Applies to _Cbtree, only at this time.  set_load_mode() makes the
   * node splitting strategy optimal for a sequence of inserts where 
   * the key/value pairs are inserted in increasing key order.
   * ---------------------------------------------------------------- */

  static void set_load_mode();
  static void clear_load_mode();
  static os_boolean in_load_mode();

 
}; /* class os_dictionary */

/* ---------------------------------------------------------------------
 * _Dictionary_cursor
 */

class _Dictionary_cursor : public os_cursor {

public:
  os_dictionary_cursor*& mc() { return (os_dictionary_cursor*&)void0; }
  
  _Dictionary_cursor(const os_collection& c) : os_cursor(c) {}
  ~_Dictionary_cursor() {} ;

  static os_typespec* get_os_typespec();
}; /* class _Dictionary_cursor */





class _OS_COLL_IMPORT os_outofline_dictionary : public os_dictionary
{
public:
  // These are public to allow standalone instantiation so the vtbl
  // can be looked up for dynamic dispatching in colvsdp.cc
  os_outofline_dictionary();
  os_outofline_dictionary(os_dictionary *);
  void _init_load(os_unsigned_int32 expected_cardinality,
	          os_unsigned_int32 behavior)
  { allocate_coll(expected_cardinality, behavior); }

  virtual void allocate_coll(os_unsigned_int32 expected_cardinality,
	                      os_unsigned_int32 behavior)
  { }

protected:
  // os_collection virtuals dispatced through the outofline pointer
  virtual void* _pick() const;
  virtual void* _only() const;
  
  virtual void _insert(os_void_const_p p);
  virtual os_int32 _remove(os_void_const_p p);
  
  /* List-specific update and access protocol */
  virtual void _insert_first(os_void_const_p p);
  virtual void _insert_last(os_void_const_p p);
  /* these return true if the element was removed, modifies the argument to */
  /* indicate the removed element */
  virtual os_int32 _remove_first(os_void_const_p &p);
  virtual os_int32 _remove_last(os_void_const_p &p);
  virtual os_int32 _retrieve_first(os_void_const_p &p) const; 
  virtual os_int32 _retrieve_last(os_void_const_p &p) const;
  virtual void* _retrieve(const os_cursor& c) const;
  virtual void* _retrieve(os_unsigned_int32 position) const;
  virtual void _insert_after(os_void_const_p p, const os_cursor& c);
  virtual void _insert_before(os_void_const_p p, const os_cursor& c); 
  virtual void _remove_at(const os_cursor& c);
  virtual void* _replace_at(os_void_const_p p, const os_cursor& c);
  virtual void _insert_after(os_void_const_p p, os_unsigned_int32 position);
  virtual void _insert_before(os_void_const_p p, os_unsigned_int32 position);
  virtual void _remove_at(os_unsigned_int32 position); 
  virtual void* _replace_at(os_void_const_p p, os_unsigned_int32 position);
  virtual os_int32 _ordered_equal(const os_collection &c) const;
  virtual os_int32 _contains(os_void_const_p p) const; 
  virtual os_int32 _count(os_void_const_p p) const; 
  virtual os_collection& _assign(const os_collection& s); 
  virtual os_collection& _assign(os_void_const_p e);
  virtual os_collection& _assign_or(const os_collection& s);
  virtual os_collection& _assign_or(os_void_const_p e);
  virtual os_collection& _assign_and(const os_collection& s);
  virtual os_collection& _assign_and(os_void_const_p e);
  virtual os_collection& _assign_sub(const os_collection& s);
  virtual os_collection& _assign_sub(os_void_const_p e);
   
  virtual os_collection& _or(const os_collection& c) const;
  virtual os_collection& _or(os_void_const_p p) const;
  virtual os_collection& _and(const os_collection& c) const;
  virtual os_collection& _and(os_void_const_p p) const;
  virtual os_collection& _sub(const os_collection& c) const;
  virtual os_collection& _sub(os_void_const_p p) const;
  
  virtual os_int32 _eq(const os_collection& s) const;
  virtual os_int32 _eq(os_void_const_p e) const;
  virtual os_int32 _ne(const os_collection& s) const; 
  virtual os_int32 _ne(os_void_const_p e) const;
  virtual os_int32 _lt(const os_collection& s) const;
  virtual os_int32 _lt(os_void_const_p e) const; 
  virtual os_int32 _le(const os_collection& s) const;
  virtual os_int32 _le(os_void_const_p e) const;
  virtual os_int32 _gt(const os_collection& s) const;
  virtual os_int32 _gt(os_void_const_p e) const;
  virtual os_int32 _ge(const os_collection& s) const;
  virtual os_int32 _ge(os_void_const_p e) const;

  virtual os_int32 _first(os_cursor& c, os_void_p &p) const;
  virtual os_int32 _last(os_cursor& c, os_void_p &p) const;
  virtual os_int32 _next(os_cursor& c, os_void_p &p) const;
  virtual os_int32 _previous(os_cursor& c, os_void_p &p) const;

  virtual os_collection* _get_innermost_collection();
  
  virtual os_int32 _remove_all(os_void_const_p p);
  
  virtual void _unbind_cursor(os_cursor& c) const;
  
  virtual os_unsigned_int32 _cardinality() const;
  virtual os_int32 _empty() const;

  virtual os_unsigned_int32  _update_cardinality();
  virtual os_unsigned_int32 _cardinality_estimate() const;
  virtual os_int32 _cardinality_is_maintained() const;

  /* index functions */
  virtual os_int32 has_indexes() const; 
  virtual _Indexes*& indexes();

  virtual void _add_index(const os_index_path& path, os_int32 i,
			  const void* v, _Coll_clustering clus);
  virtual void _clear();

  /* get the set of behavior associated with the particular coll object */
  virtual os_unsigned_int32 _get_behavior() const;
  virtual void _destroy();

  virtual os_boolean _fast_count() const;
  virtual char * _rep_name() const;
  virtual os_int32 _rep_enum() const;
				
  virtual void _check_rep_invariants() const;

  virtual void _re_initialize(os_unsigned_int32 size);
  
  /* osevol and oscompactor specific functions.  See collevl2.cc for use.*/
private:
   virtual void _set_untransformed(os_boolean flag);
   virtual void evolve_rep();

public:
  /* returns true, if it is a collection implementation that is available */
  /* to the user */
  virtual os_int32 _is_user_coll() const;

public:
  // Dictionary specific
  virtual os_boolean _is_a_hashtable() const;

  /* -------------------------------------------------------------------
   * start and end iteration
   * ---------------------------------------------------------------- */
  
  virtual os_dictionary_cursor& __iteration_start(
  	os_boolean pers = 0 ) const;
  virtual os_dictionary_cursor& __iteration_start(
  	os_int32 /* restriction */, const void*, 
	os_boolean pers = 0 ) const;
  virtual os_dictionary_cursor& __iteration_start(
  	os_int32 /* restriction */, const void*, os_int32 /* restriction */, 
	const void*, os_boolean pers = 0 ) const;
  virtual void __iteration_end(os_dictionary_cursor&) const;
  
  /* -------------------------------------------------------------------
   * navigation
   * ---------------------------------------------------------------- */

  virtual os_int32 __first(os_dictionary_cursor&, os_void_p&) const;
  virtual os_int32 __last(os_dictionary_cursor&, os_void_p&) const;
  virtual os_int32 __next(os_dictionary_cursor&, os_void_p&) const;
  virtual os_int32 __previous(os_dictionary_cursor&, os_void_p&) const;
  virtual os_int32 __OS_COLL_IS_NULL(const os_dictionary_cursor&) const;
  virtual os_int32 __more(const os_dictionary_cursor&) const;

  /* -------------------------------------------------------------------
   * retrieval
   * ---------------------------------------------------------------- */

  virtual void* __retrieve(const os_dictionary_cursor&) const;
  virtual void* __retrieve_key(const os_dictionary_cursor&) const;
  virtual void* __pick(os_unsigned_int32&) const;
  virtual void* __pick(
  	os_int32 /* os_collection::restriction */, const void*, 
	os_unsigned_int32& ) const;
  virtual void* __pick(
  	os_int32 /* os_collection::restriction */, const void*,
	os_int32 /* os_collection::restriction */, const void*,
	os_unsigned_int32& ) const;

  /* -------------------------------------------------------------------
   * This is exactly identical to _only() except that it does raise 
   * exception when n_keys == 0. Currently only, _Rhash and _CM provide 
   * the implementation.
   * ---------------------------------------------------------------- */

  virtual void* __only(os_boolean& empty) const;

  virtual os_int32 __contains(const void* v, const void* k) const;
  
  /* -------------------------------------------------------------------
   * update
   * ---------------------------------------------------------------- */

  virtual void __insert(
  	const void* v,const void* k, os_collection *cc,
	const void* keycopy=0, os_unsigned_int32 hashval = 0 );
  virtual void __remove(const void* v, const void* k, os_collection * cc);

  /* -------------------------------------------------------------------
   * This is only supported by _CM and _Rhash
   * ---------------------------------------------------------------- */

  virtual void __remove(
  	const void*, const void*, os_boolean&, os_collection * cc);
  virtual void __insert(
  	const void*, const void*, os_collection *, const void*,os_boolean& );
 
  virtual os_int32 __count(os_dictionary_cursor&) const;
  virtual os_int32 __count(const void* /*key*/, const void* /*val*/) const;

  virtual os_int32 __duplicates() const;
  virtual const char* _key_type() const;

  /* -------------------------------------------------------------------
   * cursor maintenance
   * ---------------------------------------------------------------- */

  virtual void __reset(
  	os_dictionary_cursor&, const void*, const void*, _Direction );
  virtual os_collection* _cursors() const;

  /* -------------------------------------------------------------------
   * This is only implemented by _Rhash and _CM.  Calling this 
   * method without an implementation would result in an exception.
   * ---------------------------------------------------------------- */

  virtual void _set_allow_dup(os_unsigned_int32 flag);

protected:
  virtual void find_functions(_Rank_fcn&, _Hash_fcn&) const;


protected:
  // outofline dictionary pointer
  os_dictionary * _coll;
  char _os_pad_0[4];   /* 64-bit neutralization */

public:
  static os_typespec* get_os_typespec();

  virtual ~os_outofline_dictionary();

};  // os_outofline_dictionary



#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif

