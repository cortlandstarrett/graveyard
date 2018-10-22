/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _CM_included
#define _CM_included

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#include <ostore/coll/cursor.hh>
#include <ostore/coll/lw.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/cursor.hh>
#include <os_pse/coll/lw.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif


/* ---------------------------------------------------------------------
 * Forward declarations
 * ------------------------------------------------------------------ */

#ifdef scaffold
class _Rhash;
class _Indexes;

/* ---------------------------------------------------------------------
 * Constants
 *
 * MAP_SIZE is in terms of number of slots, not number of bytes - must
 * be prime.
 * ------------------------------------------------------------------ */

#define _OS_CM_MAP_SIZE_LIMIT 65536
#define _OS_CM_MIN_MAP_SIZE 11 
#define OS_COLL_CM_NULL_SLOT ((os_unsigned_int32)0xffffffff)

/* ---------------------------------------------------------------------
 * enums
 * ------------------------------------------------------------------ */

enum {
  /* bit 0 thorugh 8 are used for os_index_path_option */
  _cm_index_options_mask = 0x7f,
  _cm_options_use_bag = 1 << 8,
  _cm_options_use_set = 0,  /* default */
  _cm_options_use_outofline = 1 << 9
};

enum _CM_search_type 
  { _CM_INSERT, _CM_LOOKUP, _CM_REORG, _CM_search_type_pad = 1<<30 };

enum 
{
  _CM_non_ptr_slot_capacity = 16,
  _CM_non_ptr_slot_set_mask = 0xf
};

/* ---------------------------------------------------------------------
 * _CM_cursor
 */

class _OS_COLL_IMPORT _CM_cursor : public os_dictionary_cursor {

  friend class _CM;

private:
  enum { restricted_flag = 1, two_sided_flag = 2, safe_flag = 4};

public:
  os_unsigned_int32 	flags;
  _CM * 		mapping;
  void * 		slot_addr;
  os_unsigned_int32 	slot_num;
  os_collection::restriction lo_restriction;
  os_collection::restriction hi_restriction;
  void * 		lo;
  void * 		hi;
  os_cursor * 		oflo_cursor;
  os_unsigned_int32 	oflo_counter;

  void restrict(os_int32 /* os_collection::restriction */ r, const void* k)
  {
    mangle_bit(flags, 1, restricted_flag);
    lo_restriction = (os_collection::restriction)r;
    lo = (void*)k;
  }

  void restrict(os_int32 r_lo, const void* k_lo, 
		os_int32 r_hi, const void* k_hi )
  {
    mangle_bit (flags, 1, restricted_flag);
    lo_restriction = (os_collection::restriction)r_lo;
    hi_restriction = (os_collection::restriction)r_hi;
    lo = (void*)k_lo;
    hi = (void*)k_hi;
  }

  void unrestrict() { mangle_bit(flags, 0, restricted_flag); }

  os_int32 restricted() const { return flags & restricted_flag; }
  os_int32 two_sided() const { return flags & two_sided_flag; }
  os_int32 safe() const { return flags & safe_flag; }

  void set_two_sided(os_unsigned_int32 onoff) 
    { mangle_bit(flags, onoff, two_sided_flag); }
  void set_safe(os_unsigned_int32 onoff) 
    { mangle_bit(flags, onoff, safe_flag); }

public:
  _CM_cursor(	const _CM&, os_unsigned_int32 sf,
		os_dictionary_cursor::_set_position = FIND_FIRST );

  _CM_cursor(	os_collection::restriction, const void*,
	     	const _CM&, os_unsigned_int32 sf,
	     	os_dictionary_cursor::_set_position = FIND_FIRST );

  _CM_cursor(	os_collection::restriction, const void*,
       		os_collection::restriction, const void*,
	     	const _CM&, os_unsigned_int32 sf,
	     	os_dictionary_cursor::_set_position = FIND_FIRST );

  ~_CM_cursor();

  static os_typespec* get_os_typespec();

}; /* class _CM_cursor */

/* ---------------------------------------------------------------------
 * _CM
 */

class _OS_COLL_IMPORT _CM: public os_dictionary {

  friend class _CM_cursor;
  friend class os_cursor_holder;


protected:

  /* -------------------------------------------------------------------
   * data members
   * ---------------------------------------------------------------- */

  void * 		mapping;
  os_unsigned_int32 	n_keys;
  os_unsigned_int32 	n_slots;
  os_unsigned_int32 	n_deleted;
  os_unsigned_int32 	reorg_threshold;
  os_unsigned_int32 	local_flags;
  static os_unsigned_int32 	_cm_alloc_outofline;
  static os_boolean 		_cm_out_of_line_at_low_card;
   os_unsigned_int32 unused;

public:
  static void _set_alloc_outofline(os_int32);

public:
  /* -------------------------------------------------------------------
   * birth and death
   * ---------------------------------------------------------------- */

  _CM(os_boolean dup_tracking_rep = 0); 

  virtual ~_CM();

  /* constructors of all derived classes must call this function */
  void initialize_mapping(os_unsigned_int32 capacity);

  /* -------------------------------------------------------------------
   * os_dictionary protocol
   * ---------------------------------------------------------------- */

  virtual os_dictionary_cursor& __iteration_start(
  	os_boolean safe, os_boolean pers = 0 ) const;
  virtual os_dictionary_cursor& __iteration_start(
  	os_int32 /* restriction */, const void*,
	os_boolean safe, os_boolean pers = 0 ) const;
  virtual os_dictionary_cursor& __iteration_start(
  	os_int32 /* restriction */, const void*,
	os_int32 /* restriction */, const void*,
	os_boolean safe, os_boolean pers = 0 ) const;
  virtual void __iteration_end(os_dictionary_cursor&) const;
  
  virtual os_int32 __first(os_dictionary_cursor&, os_void_p &) const;
  virtual os_int32 __last(os_dictionary_cursor&, os_void_p &) const;
  virtual os_int32 __next(os_dictionary_cursor&, os_void_p &) const;
  virtual os_int32 __previous(os_dictionary_cursor&, os_void_p &) const;
  virtual os_int32 __OS_COLL_IS_NULL(const os_dictionary_cursor&) const;
  virtual os_int32 __more(const os_dictionary_cursor&) const;
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
  virtual void* __only() const;
  virtual void* __only(os_boolean& empty) const;
  virtual os_int32 __contains(const void* v, const void* k) const;
  virtual os_int32 _empty() const;
  virtual void __insert(
  	const void* v, const void* k, os_collection * cc,
	const void* keycopy = 0, os_unsigned_int32 hashval = 0 );
  virtual void __remove(const void* v, const void* k, os_collection * cc);
  virtual void _clear();
  virtual void __remove(
  	const void* v, const void* k, 
	os_boolean& key_found, os_collection * cc );
  virtual void __insert(
  	const void* , const void* , os_collection *,
	const void* , os_boolean& );

  virtual os_unsigned_int32 _cardinality() const;

  virtual os_unsigned_int32 _cardinality_estimate() const;
  virtual os_unsigned_int32 _update_cardinality();
  virtual os_int32 _cardinality_is_maintained() const;

  virtual os_int32 __count(os_dictionary_cursor&) const;
  virtual os_int32 __count(const void* /* key */, const void* /* val */) const;
  virtual os_int32 __duplicates() const;
  virtual void __reset(	
  	os_dictionary_cursor&, const void*, const void*, _Direction );
  virtual os_collection* _cursors() const;

protected:

  /* -------------------------------------------------------------------
   * rep specific functions
   * ---------------------------------------------------------------- */

  os_boolean allow_dup() const { return 1; }
  os_boolean signal_duplicate() const { return 0; }
  os_boolean use_outofline() const
    { return (local_flags & _cm_options_use_outofline); }
  os_boolean use_bag() const { return (local_flags & _cm_options_use_bag); }
  os_boolean use_set() const { return !use_bag(); }
  void set_use_bag(os_unsigned_int32 flag)
    { mangle_bit(local_flags, flag, _cm_options_use_bag); }
  void set_use_outofline(os_boolean flag)
    { mangle_bit(local_flags, flag, _cm_options_use_outofline); }
     
protected:
  void _cm_get_actual_keys() {}
  virtual void _cm_clear();

protected:

  /* -------------------------------------------------------------------
   * slot selection
   * ---------------------------------------------------------------- */

  virtual void assign_slots(
  	char* copy, os_unsigned_int32 old_num_slot,
	_Hash_fcn hash_fn,  _Rank_fcn rank_fn );

  virtual void* find_slot(
  	const void* k, _CM_search_type, os_unsigned_int32& slot, 
	os_boolean& key_found, os_unsigned_int32& hashval,
	const void* v_in = 0, os_int32* v_found = 0, void* v_out=0, 
	_Rank_fcn rfn=0, _Hash_fcn hfn=0, 
	os_unsigned_int32 hashval_in = 0 ) const;

  virtual os_unsigned_int32 next_occupied_slot(
  	os_unsigned_int32 s, os_void_p & sl ) const;
  virtual os_unsigned_int32 previous_occupied_slot(
  	os_unsigned_int32 s, os_void_p & sl ) const;
  virtual os_unsigned_int32 first_occupied_slot(os_void_p & sl) const;
  virtual os_unsigned_int32 last_occupied_slot(os_void_p & sl) const;
  virtual os_unsigned_int32 slots_per_slot() const;

  /* -------------------------------------------------------------------
   * PURE VIRTUAL FUNCTION DECLARATION START
   *
   * These functions must be provided by derived classes.
   * ---------------------------------------------------------------- */

  virtual os_dictionary* create_outofline(
  	os_unsigned_int32 capacity, os_boolean use_bag ) = 0;

  /* -------------------------------------------------------------------
   * slot operations (dispatch)
   * ---------------------------------------------------------------- */

  virtual os_unsigned_int32 slot_size() const = 0;
  virtual os_unsigned_int32 key_size() const = 0;
  virtual const char* _key_type() const = 0;
  virtual void* allocate_n_slots(os_unsigned_int32) = 0;
  
  virtual void* slot_value(const _CM_cursor* c) const = 0;
  virtual os_boolean slot_first(_CM_cursor*, os_void_p &) const = 0;
  virtual os_boolean slot_last(_CM_cursor*, os_void_p &) const = 0;
  virtual os_boolean slot_next(_CM_cursor*, os_void_p &) const = 0;
  virtual os_boolean slot_previous(_CM_cursor*, os_void_p &) const = 0;
  virtual os_boolean slot_null( const _CM_cursor*) const = 0;

  virtual void* slot_addr(void* map_arg, os_unsigned_int32 slot) const = 0;

  virtual os_int32 slot_count(void* ps,os_unsigned_int32 s) const;
  virtual void* slot_key(
  	void* v, os_unsigned_int32 subslot, 
	os_unsigned_int32* phashval=0 ) const = 0;
  virtual os_boolean slot_occupied(
  	void* v, os_unsigned_int32 subslot ) const = 0;
  virtual os_boolean slot_key_eq(
  	void* ps, os_unsigned_int32 s, const void* k,
	_Rank_fcn, os_unsigned_int32 hv=0) const = 0;
  virtual void* slot_pick(void* ps, os_unsigned_int32 s) const = 0;
  virtual os_boolean slot_contains(
  	void* ps, os_unsigned_int32 s, const void* v ) const = 0;
  virtual os_boolean slot_insert(
  	void* ps, os_unsigned_int32 s, const void* v, const void* k, 
	os_unsigned_int32 h, os_collection * cc ) = 0;
  virtual void slot_remove(
  	void* ps, os_unsigned_int32 s, const void* v, 
	os_boolean& d, os_collection * cc ) = 0;
  virtual void slot_assign(
  	void* ps, os_unsigned_int32 s, const void* p,
	os_unsigned_int32 p_slot_num ) = 0;
  virtual os_boolean slot_unused(void* ps, os_unsigned_int32 s) const = 0;
  virtual os_boolean slot_deleted(void* ps, os_unsigned_int32 s) const = 0;

  /* -------------------------------------------------------------------
   * END PURE VIRTUAL FUNCTIONS
   * ---------------------------------------------------------------- */

  virtual os_boolean slot_key_matches(
  	void*, os_unsigned_int32, os_unsigned_int32, 
	const void*, os_unsigned_int32, _CM_search_type ) const;

  virtual void destroy_slots(void* map_arg) = 0;
  virtual void set_dup_count(os_unsigned_int32) {}
  virtual os_unsigned_int32 get_dup_count() const { return 0; }
  virtual void decrement_dup_count() {}
  virtual void increment_dup_count() {}

protected:
      
  os_unsigned_int32 n_entries() const { return (n_keys + get_dup_count()); }
  os_unsigned_int32 get_reorg_threshold() { return (n_slots  * 7 / 10); }
  os_boolean too_full() const 
    { return  ((n_keys + n_deleted) >= reorg_threshold); }
  os_boolean too_many_deleted() const
    { return ((reorg_threshold >> 2) <= n_deleted); }
  os_boolean exceeds_n_delete_threshold()
    { return (n_deleted >= (reorg_threshold >> 1)); }

  virtual os_unsigned_int32 map_size() const;
  os_boolean ok_to_use_internal_rep(os_unsigned_int32 slots) const;

  os_boolean exceeds_cm_limit() const;

  void grow(_Hash_fcn hash_fn, _Rank_fcn rank_fn);
  void migrate_to_rhash();
  void reorg(
  	os_unsigned_int32 slots_to_allocate, 
	_Hash_fcn hash_fn, _Rank_fcn rank_fn );

  virtual void add_ref_option_if_needed();

  void destroy_mapping(void* map_arg, os_unsigned_int32 num_slots);

public:
  static void initialize();

public:
  static void _unset_cm_out_of_line_at_low_card()
    { _CM::_cm_out_of_line_at_low_card = 0; }
  static void _set_cm_out_of_line_at_low_card()
    { _CM::_cm_out_of_line_at_low_card = 1; }

public:
  /* for schema evolution */
  static void __rehash_transformer(void *obj);	/* for non-versioned */
  void _set_untransformed(os_boolean flag);
public:

  /* For internal use only; used for testing purpose. */
  void* _get_mapping() { return mapping; }

}; /* _CM */

/* ---------------------------------------------------------------------
 * _CM_with_ix
 */

class _OS_COLL_IMPORT _CM_with_ix : public _CM {

protected:
  _Indexes* ixs;
  
protected:

  /* -------------------------------------------------------------------
   * index functions
   * ---------------------------------------------------------------- */

  virtual _Indexes*& indexes();
  virtual os_int32 has_indexes() const;

protected:

  _CM_with_ix(os_boolean dup_track) :_CM(dup_track), ixs(0) {}
  ~_CM_with_ix();

protected:

  /* -------------------------------------------------------------------
   * behavior protocol
   * ---------------------------------------------------------------- */

  virtual os_unsigned_int32 _get_behavior() const
    { return os_collection::allow_duplicates; }

}; /* _CM_with_ix */

/* ---------------------------------------------------------------------
 * _CM_ptr_keytype
 *
 * This is a little filler class for the whole dyn_hash family of
 * reps.  It turns out that all their keytypes are void* and keysize
 * is sizeof(void*).
 */

class _OS_COLL_IMPORT _CM_ptr_keytype : public _CM_with_ix {

protected:
  virtual os_unsigned_int32 key_size() const;
  virtual const char* _key_type() const;
  virtual void find_functions(_Rank_fcn&, _Hash_fcn&) const;

  virtual os_dictionary* create_outofline(
  	os_unsigned_int32 capacity, os_boolean _use_bag );

  _CM_ptr_keytype(os_boolean dup_tracking_rep = 0)
    : _CM_with_ix(dup_tracking_rep) {}

}; /* class _CM_ptr_keytype */

/* ---------------------------------------------------------------------
 * _CM_vanilla_ptr
 */

class _OS_COLL_IMPORT _CM_vanilla_ptr : public _CM_ptr_keytype {
      
public:

  _CM_vanilla_ptr(os_boolean dup_tracking_rep = 0)
    : _CM_ptr_keytype(dup_tracking_rep) {}
  virtual ~_CM_vanilla_ptr();

protected:

  /* -------------------------------------------------------------------
   * slot operations (dispatch)
   * ---------------------------------------------------------------- */

  virtual os_int32 slot_count(void* ps, os_unsigned_int32 s) const; 
  virtual void* slot_key(
  	void* ps, os_unsigned_int32 subslot, 
	os_unsigned_int32* phashval=0 ) const;
  virtual os_boolean slot_occupied(void* ps, os_unsigned_int32 subslot) const;
  virtual os_unsigned_int32 slot_size() const;

protected:

  virtual void assign_slots(
  	char* copy, os_unsigned_int32 old_num_slot,
	_Hash_fcn hash_fn,  _Rank_fcn rank_fn );
  virtual void* find_slot(
  	const void* k, _CM_search_type, os_unsigned_int32& slot, 
	os_boolean& key_found, os_unsigned_int32& hashval, const void* v = 0, 
	os_int32* v_found = 0, void* v_out=0, _Rank_fcn rfn=0, 
	_Hash_fcn hfn=0, os_unsigned_int32 h_in = 0 )const;
  virtual os_unsigned_int32 next_occupied_slot(
  	os_unsigned_int32 s, os_void_p & sl ) const;
  virtual os_unsigned_int32 previous_occupied_slot(
  	os_unsigned_int32 s, os_void_p & sl ) const;
  virtual os_unsigned_int32 first_occupied_slot(os_void_p & sl) const;
  virtual os_unsigned_int32 last_occupied_slot(os_void_p & sl) const;

  virtual os_boolean slot_key_eq(
  	void* ps, os_unsigned_int32 s, const void* k, 
	_Rank_fcn, os_unsigned_int32=0 ) const;
  virtual void* slot_pick(void* ps, os_unsigned_int32 s) const;
  virtual os_boolean slot_contains(
  	void* ps, os_unsigned_int32 s, const void* v ) const;
  virtual os_boolean slot_insert(
  	void* ps, os_unsigned_int32 s, const void* v, const void* k, 
	os_unsigned_int32 h, os_collection * cc );
  virtual void slot_remove(
  	void* ps, os_unsigned_int32 s, const void* v, 
	os_boolean& d, os_collection* cc );
  virtual os_boolean slot_unused(void* ps, os_unsigned_int32 s) const;
  virtual os_boolean slot_deleted(void* ps, os_unsigned_int32 s) const;
  virtual void slot_assign(
  	void* ps, os_unsigned_int32 s, const void* p, 
	os_unsigned_int32 p_slot_num );

  virtual void* slot_value(const _CM_cursor* c) const;
  virtual os_boolean slot_first(_CM_cursor*, os_void_p &) const;
  virtual os_boolean slot_last(_CM_cursor*, os_void_p &) const;
  virtual os_boolean slot_next(_CM_cursor*, os_void_p &) const;
  virtual os_boolean slot_previous(_CM_cursor*, os_void_p &) const;
  virtual os_boolean slot_null( const _CM_cursor*) const;

  virtual void* slot_addr(void* map_arg, os_unsigned_int32 slot) const;

  virtual void* allocate_n_slots(os_unsigned_int32);

  virtual void destroy_slots(void* map_arg);
}; /* _CM_vanilla_ptr */

#endif // Scaffold
#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif /* _CM_included */
