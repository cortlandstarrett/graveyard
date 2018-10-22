/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _Rhash_included
#define _Rhash_included


/* ---------------------------------------------------------------------
 * Include files
 * ------------------------------------------------------------------ */
#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#include <ostore/coll/lw.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/lw.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

/* ---------------------------------------------------------------------
 * enums
 * ------------------------------------------------------------------ */

enum _RH_search_type { 
  _RH_INSERT, 
  _RH_LOOKUP, 
  _RH_REORG,
  _RH_REMOVE, 
  _RH_search_type_pad = 1<<30 
};


enum _RH_slot_status {
  _RH_EMPTY_SLOT,
  _RH_SLOT_DELETED,
  _RH_SLOT_OCCUPIED,
  _RH_KEY_MATCH,
  _RH_SLOT_STATUS_PAD = 1<<30 
};

/* ---------------------------------------------------------------------
 * Defines
 * ------------------------------------------------------------------ */

#define _OS_RH_MIN_HT_SIZE 11 
#define _OS_RH_NO_KEYS -1

/* ---------------------------------------------------------------------
 * Forward declarations
 * ------------------------------------------------------------------ */

class _Rhash;
class _RH_HashTable;
class _RH_oflo_list;
class _Rhash_cursor;
class _Rhash_current;
class _Rhash_slot_move;
class _Fn_Pathop;

/* ---------------------------------------------------------------------
 * _Rhash
 */

class _OS_COLL_IMPORT _Rhash : public os_dictionary {
  friend class _RH_HashTable;
  friend class _Rhash_cursor;
  friend class _Rhash_pt_sub;
protected:
  
  os_unsigned_int32 n_HashTables;
  os_unsigned_int16 depth;
  os_unsigned_int16 n_slots;
  os_unsigned_int16 slot_size;
  os_unsigned_int16 key_size;
  os_unsigned_int32 flags;
  os_unsigned_int32 cnt_idx; 
  os_coll_ptr index_sp;
  char * mapping_keytype;
  _Indexes * index_info;

public:
   /* bits from flags */
  enum { 
    _maintain_cardinality = 1 << 0,
    _allow_dups           = 1 << 1,
    _idx_signal_dups      = 1 << 2, 
    _stores_overflow      = 1 << 3,
    _user_hash_fnc        = 1 << 4,
    _char_star_key        = 1 << 5,
    _char_array_key       = 1 << 6,
    _copy_and_point_key   = 1 << 7,
    _point_at_key         = 1 << 8,
    _untransformed        = 1 << 9,
    _cluster_allocated    = 1 << 10,
    _os_pvoid_key         = 1 << 11,
    _optimized_set        = 1 << 12,
    _void_star_key        = 1 << 13,
    _hash_pointer_v607    = 1 << 14,
    _hash_pointer_v608    = 1 << 15 
  };

  /* -------------------------------------------------------------------
   * _Rhash creation / destruction
   * ---------------------------------------------------------------- */

protected:
  _Rhash(const char* type, os_unsigned_int32 _key_size, 
	 os_unsigned_int32 _slot_size, os_unsigned_int32 capacity,
         os_unsigned_int32 option);
   
  /* value is the key */
  _Rhash(os_unsigned_int32 capacity, os_unsigned_int32 options=0);

  /* 
   * Used only by the derived class in colvdsp.cc for a dummy 
   * instance from which is extract the vtbl
   */
  _Rhash() {mapping_keytype = 0;}

  ~_Rhash();

protected:

  _RH_HashTable** allocate_index(os_unsigned_int32);
  void destroy_index();
  void remove_index();
  void remove_index_leave_cluster();
  void create_HashTable(os_unsigned_int32, os_unsigned_int32, _RH_search_type, 
                        os_cluster* cluster = (os_cluster*)0);
  void destroy_HashTable(_RH_HashTable*);
  void delete_HashTable(_RH_HashTable*);
  virtual char* allocate_slots(os_unsigned_int32, os_cluster*, void*) = 0;
  virtual void delete_slots(void*) = 0;
  os_unsigned_int32 * allocate_bitmap(void*, os_unsigned_int32, 
                                      os_unsigned_int32);
  void delete_bitmap(os_unsigned_int32 *);

public:
 
  static _Rhash* create(const void* where, _Coll_clustering,
			const char* type, os_unsigned_int32 _slot_size,
			os_unsigned_int32 _key_size,
			os_unsigned_int32 capacity,
			os_unsigned_int32 index_options,
                        _Fn_Pathop* fnp = 0);

protected:

  /* -------------------------------------------------------------------
   * index functions
   * ---------------------------------------------------------------- */

  virtual _Indexes*& indexes();
  virtual os_int32 has_indexes() const;
     

  /* -------------------------------------------------------------------
   * _Rhash access functions
   * ---------------------------------------------------------------- */

protected:

  void set_maintain_cardinality(os_boolean flag)
  {
    // cardinality is always maintained.
  }

  void set_user_hash_fnc(os_boolean flag)
  {
    if (flag)
      flags &= ~_user_hash_fnc;
    else
      flags |= _user_hash_fnc;
  }

  void set_char_star_key(os_boolean flag)
  {
    if (flag)
      flags &= ~_char_star_key;
    else
      flags |= _char_star_key;
  }
  
  void set_os_pvoid_key(os_boolean flag)
  {
    if (flag)
      flags &= ~_os_pvoid_key;
    else
      flags |= _os_pvoid_key;
  }

  void set_optimized(); 
  
  os_boolean get_maintain_cardinality() const
    { return 1; }

  os_boolean _has_keys() const;
  os_boolean has_keys() const { return _has_keys(); }
  os_unsigned_int32 _compute_n_keys();
  os_unsigned_int32 compute_n_keys() { return _compute_n_keys(); }
  os_boolean _more_than_one_key() const;
  os_boolean more_than_one_key() const { return _more_than_one_key(); }
  os_unsigned_int32 get_HashTable_size(os_unsigned_int32 t) const;
  virtual os_boolean slot_contains(
  	void* ps, os_unsigned_int32, const void* v ) const = 0;
  virtual os_boolean slot_insert(
  	void* ps, os_unsigned_int32 r, os_unsigned_int32 s, const void* v, 
	const void* k, os_unsigned_int32 h) = 0;
  virtual void slot_remove(
  	void* ps, os_unsigned_int32 r, os_unsigned_int32 s, const void* v, 
	os_boolean& d) = 0;
  virtual void slot_assign(void* ps, const void* from) = 0;
  os_unsigned_int32 find_cluster() const;

public:
  virtual void _set_allow_dup(os_unsigned_int32 flag);
  virtual os_unsigned_int32 _update_cardinality();
  virtual os_unsigned_int32 _cardinality_estimate() const;
  virtual os_int32 _cardinality_is_maintained() const;
  virtual os_unsigned_int32 _get_behavior() const;
  os_boolean allow_dup() const
    {return  (flags & _allow_dups); }
  os_boolean support_overflow() const
    {return (flags & _allow_dups && flags & _stores_overflow); }
  os_boolean use_user_hash_fnc() const
    {return  (flags & _user_hash_fnc); }
  os_boolean untransformed() const
    {return  (flags & _untransformed); }
  os_boolean has_cluster() const
    {return  (flags & _cluster_allocated); }
  os_boolean is_optimized_set() const
    {return  (flags & _optimized_set); }
  os_unsigned_int32 get_flags() const {return flags;}
  void get_key(void* obj, void *& val) const;

protected:

  /* -------------------------------------------------------------------
   * _Rhash HashTable selection
   * ---------------------------------------------------------------- */
  
  os_unsigned_int32 first_occupied_HashTable() const;
  os_unsigned_int32 last_occupied_HashTable() const;
  os_unsigned_int32 next_occupied_HashTable(os_unsigned_int32) const;
  os_unsigned_int32 previous_occupied_HashTable(os_unsigned_int32) const;
  os_unsigned_int32 find_HashTable(os_unsigned_int32) const;
 
  /* -------------------------------------------------------------------
   * _Rhash slot selection
   * ---------------------------------------------------------------- */

  virtual void* find_slot(
  	const void*, _RH_search_type, os_unsigned_int32&, os_unsigned_int32&,
	os_unsigned_int32&, os_boolean&, _Rank_fcn = 0, _Hash_fcn = 0,
	os_unsigned_int32 = 0 ) const;
  virtual os_unsigned_int32 first_occupied_slot(os_unsigned_int32) const;
  virtual os_unsigned_int32 last_occupied_slot(os_unsigned_int32) const;
  virtual os_unsigned_int32 next_occupied_slot(
  	os_unsigned_int32, os_unsigned_int32 ) const;
  virtual os_unsigned_int32 previous_occupied_slot(
  	os_unsigned_int32, os_unsigned_int32 ) const;

  virtual void* slot_value(
        const void*,const _Rhash_cursor*,os_unsigned_int32 ) const = 0;
  virtual os_boolean slot_key_eq(
  	const void*, os_unsigned_int32, const void*, _Rank_fcn ) const = 0;
  virtual void* slot_pick(const void*, os_unsigned_int32) const = 0;
  virtual os_boolean slot_first(
  	const void*, _Rhash_cursor*, os_void_p&, os_unsigned_int32) const = 0;
  virtual os_boolean slot_last(
  	const void*, _Rhash_cursor*, os_void_p&, os_unsigned_int32) const = 0;
  virtual os_boolean slot_next(
  	const void*, _Rhash_cursor*, os_void_p&, os_unsigned_int32) const = 0;
  virtual os_boolean slot_previous(
  	const void*, _Rhash_cursor*, os_void_p&, os_unsigned_int32) const =0;
  virtual os_boolean slot_null(
        const void*, const _Rhash_cursor*, os_unsigned_int32) const = 0;
  virtual os_boolean stores_overflow() = 0;
  virtual os_int32 slot_count(void*, os_unsigned_int32) const { return 0; }
  virtual _RH_slot_status slot_status(
  	void*, const void*, _RH_search_type, _Rank_fcn, 
        os_unsigned_int32 ) const = 0;
  void assign_the_slot(
        void*,os_unsigned_int32, const void*, os_unsigned_int32, 
        os_unsigned_int32 , os_unsigned_int32 *);

  /* -------------------------------------------------------------------
   * _Rhash dispatch functions
   * ---------------------------------------------------------------- */
  
  virtual void* slot_key(const void*, os_unsigned_int32) const = 0;
  virtual os_unsigned_int32 slot_hash(
  	const void*, os_unsigned_int32 ) const = 0;
  virtual os_boolean slot_occupied(const void*) const = 0;
  virtual void slot_reclaim_oflo(void*, os_unsigned_int32) = 0;
  
  /* -------------------------------------------------------------------
   * _Rhash reorganization
   * ---------------------------------------------------------------- */

  void HashTable_check_for_reorg(os_unsigned_int32, os_boolean);
  void split(os_unsigned_int32);
  void join(os_unsigned_int32);
  void HashTable_split(os_unsigned_int32, os_unsigned_int32, _RH_HashTable**);
  void HashTable_join(os_unsigned_int32, os_unsigned_int32, _RH_HashTable**);
  void HashTable_reorg(os_unsigned_int32);
  void HashTable_shrink(os_unsigned_int32, os_unsigned_int32);
  void HashTable_grow(os_unsigned_int32);
  void rehash_slots(
       os_unsigned_int32, os_unsigned_int32,char*, char*, os_unsigned_int32*);
  void copy_slots(char*, char*, os_unsigned_int32);
  void clear_slots(char*, os_unsigned_int32);  
  os_unsigned_int32 max_keys(os_unsigned_int32);
  os_unsigned_int32 min_keys(os_unsigned_int32);
  os_unsigned_int32 too_many_deleted(os_unsigned_int32);
 
  /* -------------------------------------------------------------------
   * _Mapping interface
   * ---------------------------------------------------------------- */

public:
  /* -------------------------------------------------------------------
   * Start and end iteration
   * ---------------------------------------------------------------- */
  
  virtual os_dictionary_cursor& __iteration_start(os_boolean=0 ) const;
  virtual os_dictionary_cursor& __iteration_start(
  	os_int32, const void*, os_boolean=0 ) const;
  virtual os_dictionary_cursor& __iteration_start(
  	os_int32, const void*, os_int32, const void*, os_boolean=0 ) const;
  virtual void __iteration_end(os_dictionary_cursor&) const;
  
  /* -------------------------------------------------------------------
   * Navigation
   * ---------------------------------------------------------------- */
  
  virtual os_int32 __first(os_dictionary_cursor&, os_void_p&) const;
  virtual os_int32 __last(os_dictionary_cursor&, os_void_p&) const;
  virtual os_int32 __next(os_dictionary_cursor&, os_void_p&) const;
  virtual os_int32 __previous(os_dictionary_cursor&, os_void_p&) const;
  virtual os_int32 __OS_COLL_IS_NULL(const os_dictionary_cursor& c) const;
  virtual os_int32 __more(const os_dictionary_cursor& c) const;

  /* -------------------------------------------------------------------
   * Retrieval
   * ---------------------------------------------------------------- */
  
  virtual void* __retrieve(const os_dictionary_cursor&) const;
  virtual void* __retrieve_key(const os_dictionary_cursor&) const;
  virtual void* __pick(os_unsigned_int32&) const;
  virtual void* __pick(os_int32, const void*, os_unsigned_int32&) const;
  virtual void* __pick(
  	os_int32, const void*, os_int32, const void*, 
	os_unsigned_int32& ) const;
  virtual void* _only() const;
  virtual void* __only(os_boolean& empty) const;

  virtual os_int32 __contains(const void* v, const void* k) const;

  virtual os_int32 __duplicates() const;

  virtual os_int32 __count(os_dictionary_cursor&) const;
  virtual os_int32 __count(const void*  /* key */, const void* /* val */) const;
  

  /* -------------------------------------------------------------------
   * Update
   * ---------------------------------------------------------------- */
  
  virtual void __insert(
  	const void* v, const void* k, os_collection* cc = (os_collection*)0, 
        const void* keycopy = 0, os_unsigned_int32 hashval = 0 );
  virtual void __insert(	
  	const void* v, const void* k, os_collection* cc,
        const void* keycopy, os_boolean& dup_key );
  virtual void __remove(const void* v, const void* k, os_collection * cc);
  virtual void __remove(
  	const void* v, const void* k, os_boolean& key_found, 
	os_collection * cc );

  /* -------------------------------------------------------------------
   * Cursor maintenance
   * ---------------------------------------------------------------- */

  virtual void __reset(
  	os_dictionary_cursor&,const void*,const void*, _Direction );

  /* -------------------------------------------------------------------
   * Odds and ends
   * ---------------------------------------------------------------- */

protected:
  os_unsigned_int32 sizeof_slot() const { return slot_size; }
  virtual os_unsigned_int32 _cardinality() const;
  virtual os_int32 _empty() const;
  static void assert_prime(os_unsigned_int32);
  virtual void _clear();
  virtual void _re_initialize(os_unsigned_int32 size);
  os_unsigned_int32 re_hash(os_unsigned_int32) const;
  os_boolean is_reorg(_RH_search_type s) const 
     { return (s == _RH_REORG) ? 1 : 0; }
  void initialize(os_unsigned_int32 capacity, os_unsigned_int32 _slot_size,
                  os_unsigned_int32 _key_size, const char * key_type);
  void set_n_slots(os_unsigned_int32);
  os_unsigned_int32 calculate_n_slots();
  os_unsigned_int32 max_table_size(os_unsigned_int32 _n_slots);
  os_unsigned_int32 get_t_slots(os_unsigned_int32) const;
  void propagate_HashTable(os_unsigned_int32,_RH_HashTable*);
  os_unsigned_int32 find_left_boundry(os_unsigned_int32);
  os_unsigned_int32 find_right_boundry(os_unsigned_int32);
  _RH_HashTable** index() const { return (_RH_HashTable**)(void*)index_sp; }
  _RH_HashTable** index() { return (_RH_HashTable**)(void*)index_sp; }
  void set_index(_RH_HashTable** tp) { index_sp = (void*)tp; }

public:  
  void print_directory(os_unsigned_int32);

 /* -------------------------------------------------------------------
  * Bitmap functions
  * ---------------------------------------------------------------- */
public:
  os_unsigned_int32 has_overflow(os_unsigned_int32, os_unsigned_int32) const;

protected:
  void set_overflow(os_unsigned_int32, os_unsigned_int32,os_unsigned_int32);
  os_unsigned_int32 * bitmap_copy(os_unsigned_int32);
  os_unsigned_int32 bitmap_size(os_unsigned_int32 _n_slots);
  os_unsigned_int32 has_overflow(os_unsigned_int32 *, os_unsigned_int32) const;
    
  /* -------------------------------------------------------------------
   * Stolen from _Mapping
   * ---------------------------------------------------------------- */

public:
  os_boolean _point_to_key() const { return flags & _point_at_key; }
  os_boolean _is_char_star_key() const { return flags & _char_star_key; }
  os_boolean _is_os_pvoid_key() const { return flags & _os_pvoid_key; }
  os_boolean _is_pointer_key() const
      { return (flags &(_char_star_key | _os_pvoid_key | _void_star_key));}
  const char * _key_type() const { return mapping_keytype; }
  os_unsigned_int32 _key_size() const { return key_size; }
  os_collection * _cursors() const;

 /* -------------------------------------------------------------------
  * for schema evolution and compactor.  See collevl2.cc for use
  * ---------------------------------------------------------------- */
private:
   virtual void _set_untransformed(os_boolean flag);
   virtual void evolve_rep();

  /* -------------------------------------------------------------------
   * From os_collection_internal, so we can instantiate an os_Dictionary
   * ---------------------------------------------------------------- */
protected:
  virtual void _insert_first(os_void_const_p) ;
  virtual void _insert_last(os_void_const_p);
  virtual void _insert_after(os_void_const_p, const os_cursor&);
  virtual void _insert_before(os_void_const_p, const os_cursor&) ;
  virtual os_int32 _remove_first(os_void_const_p &) ;
  virtual os_int32 _remove_last(os_void_const_p &) ;
  virtual void _insert_after(os_void_const_p p, os_unsigned_int32 position) ;
  virtual void _insert_before(os_void_const_p p, os_unsigned_int32 position) ;
  virtual void _remove_at(const os_cursor& c) ;
  virtual void _remove_at(os_unsigned_int32 position) ;
  virtual void* _replace_at(os_void_const_p p, const os_cursor& c) ;
  virtual void* _replace_at(os_void_const_p p, os_unsigned_int32 position) ;
  virtual os_int32 _retrieve_first(os_void_const_p &) const;
  virtual os_int32 _retrieve_last(os_void_const_p &) const;

}; /* class _Rhash */

/* ---------------------------------------------------------------------
 * _RH_HashTable
 */

class _RH_HashTable {
  friend class _Rhash;
  friend class _Rhash_cursor;

private:
 
  os_unsigned_int16 _level;
  os_unsigned_int16 _n_deleted;
  os_unsigned_int32 _n_entries;
  os_unsigned_int32 _n_keys;
  os_unsigned_int32 _n_slots;
  void * _contents;  
  os_unsigned_int32 * bitmap;

public:
  _RH_HashTable(os_unsigned_int32 num_slots)
  {
    _n_entries = 0;
    _n_keys = 0;
    _n_deleted = 0;
    _level = 0;    
    _n_slots = num_slots;  
    _contents = 0;
  }
 
  void clear(_Rhash*, os_unsigned_int32);

  char*& contents() { return (char*&) _contents; }
  const char* const& contents() const { return (char const*const&) _contents; }

  os_unsigned_int32 get_n_entries() { return _n_entries; }
  void set_n_entries(os_unsigned_int32 n) { _n_entries = n; }
  void inc_n_entries() { _n_entries++; }
  void dec_n_entries() { _n_entries--; }

  os_unsigned_int32 get_n_keys() { return _n_keys; }
  void set_n_keys(os_unsigned_int32 n) { _n_keys = n; }
  void inc_n_keys() { _n_keys++; }
  void dec_n_keys() { _n_keys--; }

  os_unsigned_int32 get_n_deleted() { return _n_deleted; }
  void set_n_deleted(os_unsigned_int32 n) { _n_deleted = n; }
  void inc_n_deleted() { _n_deleted++; }
  void dec_n_deleted() { _n_deleted--; }
 
  os_unsigned_int32 get_level() { return _level; }
  void set_level(os_unsigned_int32 n) { _level = n; }
  void inc_level() { _level++; }
  void dec_level() { if (_level) _level--;}
   
  void set_n_slots(os_unsigned_int32 num_slots) 
     { _n_slots = num_slots; }
  os_unsigned_int32 get_n_slots() { return _n_slots; }
    
  void* slot(const _Rhash* h, os_unsigned_int32 s) const
    { return (void*)(contents() + (h->sizeof_slot()*s)); }
  

  static os_typespec* get_os_typespec();

}; /* class _RH_HashTable */

/* ---------------------------------------------------------------------
 * _Rhash_cursor
 */

class _OS_COLL_IMPORT _Rhash_cursor : public os_dictionary_cursor {
  friend class _Rhash;

protected:
  enum { restricted_flag = 1, two_sided_flag = 2 };
  os_unsigned_int32 flags;

public: 
  /* one-sided */
  os_collection_restriction key_restriction;
  os_coll_ptr key;

  /* two-sided */
  os_collection_restriction lo_restriction;
  os_collection_restriction hi_restriction;
  os_coll_ptr lo;
  os_coll_ptr hi;

  os_unsigned_int32 table;
  os_unsigned_int32 slot;
  os_coll_ptr _oflo_current;
  os_cursor * get_oflo_current() const {return (os_cursor*)(void*)_oflo_current;}
  void set_oflo_current(os_cursor * curs) {_oflo_current = curs;}
  /* 
   * null_after_maintenance: used only in a special case of cursor 
   * maintenance. See _Rhash::fix_cursors_remove and _Rhash::previous. 
   */
  osbitf null_after_maintenance : 1;
  osbitf oflo : 1;
  osbitf _os_pad_1 : 30;
  char _os_pad_2[4];	/* 64-bit neutralization */

public:
  _Rhash_cursor(
        const _Rhash&, os_dictionary_cursor::_set_position = FIND_FIRST );
  _Rhash_cursor(
  	os_collection_restriction, const void*, const _Rhash&, 
	os_dictionary_cursor::_set_position = FIND_FIRST );
  _Rhash_cursor(
  	os_collection_restriction, const void*, os_collection_restriction, 
	const void*, const _Rhash&, 
	os_dictionary_cursor::_set_position = FIND_FIRST );
  ~_Rhash_cursor();

  void activate_oflo_cursor(const _RH_oflo_list*);

  virtual void remember(_os_cursor_holder &);
  virtual void restore(_os_cursor_holder &);

  os_unsigned_int32& oflo_counter()
    { return *((os_unsigned_int32*)(void*)&lo_restriction); }

  virtual void restrict(os_int32 /* os_collection::restriction */ r, const void * k)
  {
    mangle_bit(flags, 1, restricted_flag);
    key_restriction = (os_collection_restriction)r;
    key = (void *)k;
  }

  virtual void restrict(
  	os_int32 r_lo, const void * k_lo, os_int32 r_hi, const void * k_hi )
  {
    mangle_bit(flags, 1, restricted_flag);
    lo_restriction = (os_collection_restriction)r_lo;
    hi_restriction = (os_collection_restriction)r_hi;
    lo = (void *)k_lo;
    hi = (void *)k_hi;
  }

  virtual void unrestrict()
  {
    mangle_bit(flags, 0, restricted_flag);
    mangle_bit(flags, 0, two_sided_flag);
  }

  os_int32 restricted() const { return flags & restricted_flag; }
  os_int32 two_sided() const { return flags & two_sided_flag; }
  
  void set_two_sided(os_unsigned_int32 onoff) 
    { mangle_bit(flags, onoff, two_sided_flag); }

  static os_typespec* get_os_typespec();

}; /* class _Rhash_cursor */


/* ---------------------------------------------------------------------
 * _RH_oflo_list
 *
 * Overflow list for hash tables with duplicates.
 */

class _RH_oflo_list {
  friend class _Rhash_cursor;

protected:
  os_collection * contents;
  _RH_oflo_list() {};     /* dummy constructor used by _RH_ref_oflo_list */

public:
  _RH_oflo_list(os_unsigned_int32) ;
  ~_RH_oflo_list() { delete (os_collection*)contents; }

  void insert(const _Rhash*, const void* v) { contents->_insert(v); }
  void remove(
  	const _Rhash* rh, os_unsigned_int32 r, os_unsigned_int32 slot, 
	const void* v );
    
  void* pick() { return contents->_pick(); }
  os_boolean contains(const void* v) { return contents->_contains(v); }

  os_boolean first(_Rhash_cursor*, void*& v) const;
  os_boolean last(_Rhash_cursor*, void*& v) const;

  os_boolean next(_Rhash_cursor* rc, void*& v) const
    { return contents->_next(*(rc->get_oflo_current()), v); }
  os_boolean previous(_Rhash_cursor* rc, void*& v) const
    { return contents->_previous(*(rc->get_oflo_current()), v); }

  void* value(const _Rhash_cursor* rc) const
    { return contents->_retrieve(*rc->get_oflo_current()); }
  os_boolean one_left() const
    { return contents->_cardinality() == 1; }

  static os_typespec* get_os_typespec();

}; /* class _RH_oflo_list */


/* ---------------------------------------------------------------------
 * Macro definitions
 * ------------------------------------------------------------------ */

#define CURRENT_TABLE() rh
#define KEY_SIZE (CURRENT_TABLE()->_key_size())
#define SLOT_ADDR(r,s) (index()[r]->slot(this,s))

/* ---------------------------------------------------------------------
 * Exceptions
 * ------------------------------------------------------------------

OS_ERR_COLL_CLASS(err_am_bad_cursor, err_coll);
OS_ERR_COLL_CLASS(err_am_corrupt, err_coll);
OS_ERR_COLL_CLASS(err_am_dup_key_item, err_coll);
OS_ERR_COLL_CLASS(err_am_empty, err_coll);
OS_ERR_COLL_CLASS(err_am_key, err_coll);
OS_ERR_COLL_CLASS(err_am_no_mark, err_coll);
OS_ERR_COLL_CLASS(err_am_no_prev, err_coll);
OS_ERR_COLL_CLASS(err_am_null_cursor, err_coll);
OS_ERR_COLL_CLASS(err_am_restriction, err_coll);
*/

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
