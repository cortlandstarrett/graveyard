/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _COLL_CHAINED_LIST
#define _COLL_CHAINED_LIST
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

/* ---------------------------------------------------------------------
 * Forward declarations
 * ------------------------------------------------------------------ */

class os_chained_list_block;
class os_chained_list;
class _Chained_list_cursor;

/* ---------------------------------------------------------------------
 * enums
 * ------------------------------------------------------------------ */

enum {
  os_chained_list_has_blocks = 1,
  os_chained_list_disallow_dups = 2,
  os_chained_list_signal_dups = 4,
  os_chained_list_use_hard_ptrs = 8,
  os_chained_list_not_in_block = -1
};

enum {
  os_chained_list_block_prev_is_root = 1,
  os_chained_list_block_has_next = 2,
  os_chained_list_block_is_last = 4,
  os_chained_list_block_use_hard_ptrs = 8
};

enum { 
  os_chained_list_moved_ptrs_up = 1, 
  os_chained_list_moved_ptrs_down = 2,
  os_chained_list_moved_2nd_to_last_to_next = 4,
  os_chained_list_moved_last_to_next  = 8,
  os_chained_list_cleared_list = 16,
  os_chained_list_copied_ptrs = 32
};

/* ---------------------------------------------------------------------
 * os_chained_list_block
 * ------------------------------------------------------------------ */

class _OS_COLL_IMPORT os_chained_list_block {

  friend class os_chained_list;

protected:

  /* -------------------------------------------------------------------
   * data members
   * ---------------------------------------------------------------- */

  os_unsigned_int16 	_local_card;
  os_unsigned_int16 	flags;
  void_coll_ptr         prev;

public:

  os_chained_list_block(void* _prev, os_boolean proot);
  os_chained_list_block() {};

  void _splice_self_out_of_list(os_chained_list* cl);

public:

  os_boolean prev_is_root() const 
    { return (flags & os_chained_list_block_prev_is_root) != 0; }

  void set_prev_is_root()
    { flags |= os_chained_list_block_prev_is_root; }

  void clear_prev_is_root()
    { flags &= ~os_chained_list_block_prev_is_root; }   

  void set_is_last()
  { 
    flags |= os_chained_list_block_is_last; 
    flags &= ~os_chained_list_block_has_next;
  }

   void set_use_hard_pointers()
  {
    flags |= os_chained_list_block_use_hard_ptrs;
  }

  os_boolean use_hard_pointers() const
  {
    return (flags & os_chained_list_block_use_hard_ptrs);
  }

  void clear_is_last()
    { flags &= ~os_chained_list_block_is_last; }

  os_boolean is_last() const
    { return (flags & os_chained_list_block_is_last) != 0; }

  os_chained_list_block* get_first(const os_chained_list* cl) const;
  void set_first(const os_chained_list* cl, os_chained_list_block* bl);

  void_coll_ptr& previous() { return prev; }
  const os_unsigned_int16& local_card() const { return _local_card; }
  os_unsigned_int16& local_card() { return _local_card; }
  void set_has_next(os_boolean v);
  os_boolean has_next() const 
    { return (flags & os_chained_list_block_has_next) != 0; }
  void clear_has_next()
    { flags &= ~ os_chained_list_block_has_next; }

public:

  /* 
   * local_index has to be < local_card().  insert_after_local will 
   * insert into next_bucket() if needed.  Both will even allocate a 
   * next bucket if if they need to.
   */
  void insert_before_local(
  	const os_chained_list* cl, const void* v, 
	os_unsigned_int32 local_index, _Chained_list_cursor* c = 0 ); 
  void insert_after_local(
  	const os_chained_list* cl, const void* v, 
	os_unsigned_int32 local_index, _Chained_list_cursor* c = 0 ); 

  /* 
   * Will insert at the very end of the os_chained_list_block list, 
   * allocating a new os_chained_list_block if the current last one 
   * is full.
   */
  void insert_last(const os_chained_list* cl, const void* v);

  /* 
   * Returns the os_chained_list_block which has no successor 
   * (next_block()) 
   */
  os_chained_list_block* find_last_block(const os_chained_list* cl);

  /* 
   * If the local block has 0 local_card() (which it really never should), 
   * it goes to its successor 
   */
  void* pick(const os_chained_list* cl) const;

  /* 
   * Moves existing pointers out of the way starting at starting_pos 
   * to make room for a pointer.  If there is no free pointer in the
   * current object, it'll try to put the overflow in the next 
   * chained_list_block.  If there isn't one or it is full, it will 
   * allocate a new chained_list_block and copy pointers to it.
   */
  os_unsigned_int32 free_up_a_pointer(
  	const os_chained_list* cl, os_unsigned_int32 starting_pos,
	_Chained_list_cursor* c = 0 );

  /* 
   * Will remove v if it is in the local block, otherwise it will 
   * call remove on the next block if it exists.  returns 1 if v was 
   * found and removed, 0 otherwise.
   */
  os_unsigned_int32 remove(
  	const os_chained_list* cl,  const void* v,
	_Chained_list_cursor* c = 0 );

  void remove_at_local(const os_chained_list* cl,
		       os_unsigned_int32 local_index,
		       _Chained_list_cursor* c = 0);

  void compact(const os_chained_list* cl,_Chained_list_cursor* c);

  /* 
   * Unlike contains_local, if v is not in the local block, this 
   * function will ask next_block() if it exists.  The containing 
   * block and the local index within the block are returned.  If 
   * the item is not found, this function returns 0.
   */
  os_chained_list_block* contains(
  	const os_chained_list* cl, const void* v, 
	os_unsigned_int32& local_ix ) const;

  os_unsigned_int32 count(const os_chained_list* cl, const void* v) const;

  /* 
   * Will return the element at position pos within the chain.  
   * if pos > local_card(), local_card() is subtracted from it and 
   * next_block()->retrieve is called.
   */
  void* retrieve(const os_chained_list* cl, os_unsigned_int32 pos);

  os_chained_list_block* block_containing_nth(
  	const os_chained_list* cl, os_unsigned_int32 n,
	os_unsigned_int32& local_ix );

  os_unsigned_int32 max_local_card(const os_chained_list* cl) const;

  void set_ptr(os_unsigned_int32 n, const void* v)
  {
    if (use_hard_pointers())
      get_Pref(n) = v;
    else
      (os_coll_ptr&)ptr(n) = (void*)v;  
 }

  const void* get_ptr(os_unsigned_int32 n)
  {
    if (use_hard_pointers())
      return *(const void**)(((char*)this) + 
			   sizeof(os_chained_list_block) + 
                           (sizeof(void*) * n));
    else
       return *(const void_coll_ptr*)(((char*)this) + 
			   sizeof(os_chained_list_block) + 
                           (sizeof(void_coll_ptr) * n)); 
  }

  const void_coll_ptr& ptr(os_unsigned_int32 n) 
  { 
    return *(const void_coll_ptr*)(((char*)this) + 
			   sizeof(os_chained_list_block) + 
                           (sizeof(void_coll_ptr) * n)); 
  }
  
  const void*& get_Pref(os_unsigned_int32 n) 
  { 
    return *(const void**)(((char*)this) + 
			   sizeof(os_chained_list_block) + 
                           (sizeof(void*) * n)); 
  }

  /* The following is no longer used and has been replaced with 
     set_first_free_ptr(). */
  const void_coll_ptr& first_free_ptr() { return ptr(local_card()); }


  void set_first_free_ptr(const void* v) { set_ptr(local_card(), v); }

  os_chained_list_block* next_block(const os_chained_list* cl) const;

  /* 
   * This function is very clever - it takes into account the case 
   * where the os_chained_list doesn't have a next_block() and has 
   * a collection element pointer where the next block pointer should 
   * go.  It gets called when a new next block gets allocated.
   */
  void set_next_block(
  	const os_chained_list* cl, os_chained_list_block* next,
	_Chained_list_cursor* c = 0 );

  /* 
   * This is a dummy version of the same function.  It gets called 
   * when a chained_list block gets deallocated.
   */
  void set_next_block_simple(
  	const os_chained_list* cl, os_chained_list_block* next );

  /* Move num_ptrs from start_ix to start_ix + num_positions_to_move */
  void move_ptrs_down(
  	const os_chained_list* cl, os_unsigned_int32 start_ix, 
	os_unsigned_int32 num_ptrs, os_unsigned_int32 num_positions_to_move,
	_Chained_list_cursor* c = 0 );

  /* Move pointers up to fill up gap at start_ix. decrements local_card() */
  void move_ptrs_up(
  	const os_chained_list* cl, os_unsigned_int32 start_ix,
	_Chained_list_cursor* c = 0 );

  /* The following copy_ptrs is no longer used and can be removed when
     compatibility is not an issue. */
  void copy_ptrs(
  	const os_chained_list* cl, void_coll_ptr* starting_addr,
	os_unsigned_int32 target_position, os_unsigned_int32 num_ptrs ) {}

  /* Doesn't do any cursor maintenance, so watch out.  
     if v_starting_addr is not null then do hardpointer based copy,
     else do softpointer based copy from s_starting_addr. */
   
  void copy_ptrs(
	const os_chained_list*, void** h_starting_addr, 
        void_coll_ptr* s_starting_addr,
	os_unsigned_int32 target_position, os_unsigned_int32 num_ptrs );

public:


  static os_typespec* get_os_typespec();

}; /* class os_chained_list_block */

/* ---------------------------------------------------------------------
 * os_chained_list
 * ------------------------------------------------------------------ */

class _OS_COLL_IMPORT os_chained_list  : public os_collection {

  friend class os_chained_list_block;

protected:
  
  /* -------------------------------------------------------------------
   * data members
   * ---------------------------------------------------------------- */

  os_unsigned_int32 flags;
  os_unsigned_int32 _local_card;
  os_unsigned_int32 card;
  _Indexes*         index_info;
  
public:

  /* internal use only */
  static void protect_safe_cursors(
  	const os_chained_list* cl, os_chained_list_block* bl,
	_Chained_list_cursor* c, os_unsigned_int32 done_log,
	os_unsigned_int32 local_ix, os_unsigned_int32 num_positions,
	os_chained_list_block* target_bl = 0, 
	os_unsigned_int32 start_addr = 0 );

protected:

  /* -------------------------------------------------------------------
   * rep-specific functions
   * ---------------------------------------------------------------- */

  /* move num_ptrs from start_ix to start_ix + num_positions_to_move */
  void move_ptrs_down(
  	os_unsigned_int32 start_ix, os_unsigned_int32 num_ptrs,
	os_unsigned_int32 num_positions_to_move, _Chained_list_cursor* c = 0 );

  /* move pointers up to fill gap at start_ix; decrements local_card(). */
  void move_ptrs_up(
  	os_unsigned_int32 start_ix, _Chained_list_cursor* c = 0 ); 

  /* this doesn't do cursor maintenance so watch out*/
  void copy_ptrs(
  	void_coll_ptr* starting_addr, os_unsigned_int32 target_position,
	os_unsigned_int32 num_ptrs );

  /* Copies from a hard pointer array to a void_coll_ptr array. */
  void copy_ptrs(
  	void** starting_addr, os_unsigned_int32 target_position,
	os_unsigned_int32 num_ptrs );

  const void_coll_ptr& ptr(os_unsigned_int32 n) 
  { 
    return *(const void_coll_ptr*)
    	( ((char*)this) + 
     	sizeof(os_chained_list) + n * sizeof(void_coll_ptr)); 
  }

  const void_coll_ptr& raw_ptr(os_unsigned_int32 n) 
  { 
    return *(const void_coll_ptr*)
    	( ((char*)this) + sizeof(os_chained_list) + (n * 
          sizeof(void_coll_ptr) ) ); 
  }

  os_chained_list_block* next_block() const
  {
    return 
    	has_blocks() ?
      	  ( (os_chained_list_block*)(void*)
       	    ((os_chained_list*)this)->raw_ptr(num_ptrs_in_head()-1) )
	    ->get_first(this) 
       	  : 0;
  }

  os_unsigned_int32 full_cardinality() const { return card; }
  os_unsigned_int16 local_card() const { return _local_card; }
  void set_local_card(os_unsigned_int16 nc) { _local_card = nc; }
  void inc_local_card() { _local_card++; }
  void inc_local_card(os_unsigned_int32 amt) { _local_card += amt; }
  void dec_local_card() { _local_card--; }
  void dec_local_card(os_unsigned_int32 amt) { _local_card -= amt; }

  os_boolean has_blocks() const
  {
    return (flags & os_chained_list_has_blocks) != 0;
  }

  void set_blocks(os_boolean v)
  {
    if (v)
      flags |= os_chained_list_has_blocks;
    else
      flags &= ~os_chained_list_has_blocks;
  }

  /* if nonzero return value, don't do the insert */
  os_unsigned_int32 do_insert_checks(const void* v);

  /* 
   * moves existing pointers out of the way starting at starting_pos 
   * to make room for a pointer.  If there is no free pointer in the
   * current object, it'll try to put the overflow in the next 
   * chained_list_block.  If there isn't one or it is full, it will 
   * allocate a new chained_list_block and copy pointers to it.
   */
  os_unsigned_int32 free_up_a_pointer(
  	os_unsigned_int32 starting_pos, _Chained_list_cursor* c = 0 );

  os_chained_list_block* find_last_block() const
  {
    return 
    	has_blocks() ?
      	  (os_chained_list_block*)(void*)
	    ((os_chained_list*)this)->raw_ptr(num_ptrs_in_head()-1)
        : 0;
  }

  /* 
   * local_index has to be < local_card().  insert_after_local will 
   * insert into next_bucket() if needed.  Both will even allocate a 
   * next bucket if if they need to.
   */
  void insert_before_local(
  	const void* v, os_unsigned_int32 local_index,
	_Chained_list_cursor* c = 0 );
  void insert_after_local(
  	const void* v, os_unsigned_int32 local_index,
	_Chained_list_cursor* c = 0 );

  /* identical to _insert, but is guaranteed never to mutate */
  void __insert_last(const void* v);

  void inc_cardinality(os_unsigned_int32 amt = 1) { card += amt; }
  void dec_cardinality(os_unsigned_int32 amt = 1) { card -= amt; }

  static void protect_safe_cursor(
  	const os_chained_list* cl, _Chained_list_cursor* c,
	os_chained_list_block* bl, os_unsigned_int32 done_log,
	os_unsigned_int32 local_ix, os_unsigned_int32 num_positions,
	os_chained_list_block* target_bl = 0, os_unsigned_int32 start_addr = 0);

  void remove_dups();

  os_unsigned_int16 max_local_card() const
  {
    return num_ptrs_in_head() - (has_blocks() ? 1 : 0);
  }

  const void_coll_ptr& first_free_ptr() { return ptr(local_card()); }

  /* 
   * this function is very clever - it takes into account the case 
   * where the os_chained_list doesn't have a next_block() and has a 
   * collection element pointer where the next block pointer should go.
   */
  void set_next_block(os_chained_list_block* next, _Chained_list_cursor* c = 0);

  void set_last_block(os_chained_list_block* clb)
    { (void_coll_ptr&)raw_ptr(num_ptrs_in_head() - 1) = clb; }

public:

  /* 
   * this is a dummy version of the same function: it assumes the 
   * caller is breathing oxygen.  It's public because it gets called 
   * by the os_chained_list_block_pt destructor.
   */
  void set_next_block_simple(os_chained_list_block* next);

protected:

  /* see the comment in the implementation in chlist.cc */
  void destroy();

  /* -------------------------------------------------------------------
   * rep-specific virtual functions (provided by parameterized class)
   * ---------------------------------------------------------------- */

  virtual os_unsigned_int32 num_ptrs_in_head() const = 0;
  virtual os_unsigned_int32 num_ptrs_in_blocks() const = 0;

  /* 
   * allocates an os_chained_list_block and splices it between cl and 
   * next_block() (if there is no next_block(), it just appends to this).
   */

  virtual os_chained_list_block* allocate_new_block(
  	_Chained_list_cursor* c = 0 ) = 0;

  /* returns the local index if found, else 0xffffffff */
  virtual os_unsigned_int32 contains_local(const void* v) const = 0;
  
  virtual os_unsigned_int32 count_local(const void* v) const = 0;

protected:

  /* -------------------------------------------------------------------
   * "virtual" functions for os_chained_list_block
   * ---------------------------------------------------------------- */

  /* 
   * allocates an os_chained_list_block and splices it between clb 
   * and its successor.
   */
  virtual os_chained_list_block*allocate_new_block(
  	os_chained_list_block* _this, os_chained_list_block*clb,
	_Chained_list_cursor* c=0 ) = 0;

  /* returns the local index if found, else 0xffffffff */
  virtual os_unsigned_int32 contains_local(
  	const os_chained_list_block* _this, const void* v ) const = 0;

  virtual os_unsigned_int32 count_local(
  	const os_chained_list_block* _this, const void* v ) const = 0;

  virtual void delete_block(os_chained_list_block* b) = 0;

protected:

  /* -------------------------------------------------------------------
   * functions inherited from os_collection
   * ---------------------------------------------------------------- */

  /* -------------------------------------------------------------------
   * index functions
   * ---------------------------------------------------------------- */

  virtual _Indexes*& indexes();
  virtual os_int32 has_indexes() const;

protected:

  /* -------------------------------------------------------------------
   * behavior protocol
   * ---------------------------------------------------------------- */

  virtual os_unsigned_int32 _get_behavior() const;

  os_boolean disallow_duplicates() const
  {
    return (flags & os_chained_list_disallow_dups) != 0;
  }

  void set_disallow_duplicates()
  {
    flags |= os_chained_list_disallow_dups;
  }

  os_boolean signal_duplicates() const
  {
    return (flags & os_chained_list_signal_dups) != 0;
  }

  void set_signal_duplicates()
  {
    flags |= os_chained_list_signal_dups;
  } 

  void set_use_hard_pointers()
  {
    flags |= os_chained_list_use_hard_ptrs;
  }

  os_boolean use_hard_pointers() const
  {
    return (flags & os_chained_list_use_hard_ptrs);
  }

protected:

  virtual void _check_rep_invariants() const;
  virtual char *_rep_name() const;
  virtual os_int32 _rep_enum() const;

protected:

  /* -------------------------------------------------------------------
   * the collections protocol
   * ---------------------------------------------------------------- */
  
  virtual void* _pick() const;
  virtual void* _only() const;

  virtual void _insert(os_void_const_p);
  virtual os_int32 _remove(os_void_const_p);
  
  /* List-specific update and access protocol */
  virtual void _insert_first(os_void_const_p p) ;
  virtual void _insert_last(os_void_const_p p) ;

  /* 
   * these return true if the element was removed, modifies the 
   * argument to indicate the removed element 
   */
  virtual os_int32 _remove_first(os_void_const_p &) ;
  virtual os_int32 _remove_last(os_void_const_p &) ;
  virtual os_int32 _retrieve_first(os_void_const_p &) const ;
  virtual os_int32 _retrieve_last(os_void_const_p &) const ;

  virtual void* _retrieve(const os_cursor& c) const ;
  virtual void* _retrieve(os_unsigned_int32 position) const ;
  
  virtual void _insert_after(os_void_const_p p, const os_cursor& c) ;
  virtual void _insert_before(os_void_const_p p, const os_cursor& c) ;
  virtual void _remove_at(const os_cursor& c) ;
  virtual void* _replace_at(os_void_const_p p, const os_cursor& c) ;
  
  virtual void _insert_after(os_void_const_p p, os_unsigned_int32 position) ;
  virtual void _insert_before(os_void_const_p p, os_unsigned_int32 position) ;
  virtual void _remove_at(os_unsigned_int32 position) ;
  virtual void* _replace_at(os_void_const_p p, os_unsigned_int32 position) ;
  
  virtual os_int32 _contains(os_void_const_p) const;
  virtual os_int32 _count(os_void_const_p) const ;
  
protected:

  /* -------------------------------------------------------------------
   * cursor protocol
   * ---------------------------------------------------------------- */

  virtual os_int32 _first(os_cursor&, os_void_p &) const;
  virtual os_int32 _last(os_cursor&, os_void_p &) const;
  virtual os_int32 _next(os_cursor&, os_void_p &) const ;
  virtual os_int32 _previous(os_cursor&, os_void_p &) const;

protected:

  /* -------------------------------------------------------------------
   * other odds and ends
   * ---------------------------------------------------------------- */

  virtual os_int32 _remove_all(os_void_const_p);

  virtual void _clear();
  virtual os_unsigned_int32 _cardinality() const;
  virtual os_int32 _empty() const;
  virtual os_boolean _fast_count() const;

  virtual void _re_initialize(os_unsigned_int32 size) {}

 /* -------------------------------------------------------------------
  *  osevol and oscompactor specific functions.  See collevl2.cc for use,
  *  although, an os_chained_list does no schema evolution.
  * ---------------------------------------------------------------- */
private:
   virtual void _set_untransformed(os_boolean flag) {};
   virtual void evolve_rep() {};

public:

  os_chained_list(os_unsigned_int32 size = 0, os_unsigned_int32 behavior = 0);
  virtual ~os_chained_list();

}; /* class os_chained_list */

/* ---------------------------------------------------------------------
 * typedefs
 * ------------------------------------------------------------------ */

typedef os_chained_list* os_chained_list_p;
typedef os_chained_list_block* os_chained_list_block_p;


/* ---------------------------------------------------------------------
 * _Chained_list_cursor
 */

class _OS_COLL_IMPORT _Chained_list_cursor : public os_cursor {

  friend class os_chained_list;
  friend class os_chained_list_block;

public:

  os_chained_list_block*& current_block() 
    { return !is_optimized() ?  (os_chained_list_block*&)void0
                             :  (os_chained_list_block*&)proximal; }
  os_chained_list_block* get_current_block() 
    { return !is_optimized() ?  (os_chained_list_block*)(void*) void0 
                             :  (os_chained_list_block*) proximal; } 
  os_unsigned_int32& subscr_in_block() { return os4u0; }
  os_unsigned_int32& subscr() { return os4u1; }
  os_coll_ptr& current_elt() {return void1; }

  os_collection* coll() { return get_contents(); }

  void set_off_the_edge() 
  { 
    subscr_in_block() = (os_unsigned_int32)os_chained_list_not_in_block; 
    set_at_deleted_element(0);
    set_more(0);
  }

  os_boolean off_the_edge()
  { 
    return ( (subscr_in_block() == 
      (os_unsigned_int32)os_chained_list_not_in_block) && 
      (get_at_deleted_element() == 0) );
  }

  void set_at_deleted_element_0() 
  {
    subscr_in_block() = (os_unsigned_int32)os_chained_list_not_in_block; 
    set_at_deleted_element(1);
    current_block() = 0;
    set_more(0);
  }

  os_boolean at_deleted_element_0() 
  {
    return ((subscr_in_block() == 
	     (os_unsigned_int32)os_chained_list_not_in_block) &&
	    (current_block() == 0) &&
	    (get_at_deleted_element()) );
  }

public:

  _Chained_list_cursor(const os_collection& c) : os_cursor (c) {};
  ~_Chained_list_cursor() {} ;


  static os_typespec* get_os_typespec();

}; /* class _Chained_list_cursor */

/* ---------------------------------------------------------------------
 * os_chained_list_4_8
 */

class _OS_COLL_IMPORT os_chained_list_4_8 : public os_chained_list {

#define COLL_INT_NUM_PTRS_IN_HEAD 4
#define COLL_INT_NUM_PTRS_IN_BLOCKS 8
  
protected:

  /* -------------------------------------------------------------------
   * data members
   * ---------------------------------------------------------------- */

  void_coll_ptr pointers[COLL_INT_NUM_PTRS_IN_HEAD];

protected:

  /* -------------------------------------------------------------------
   * rep-specific virtual functions (provided by the parameterized 
   * class) 
   * ---------------------------------------------------------------- */

  virtual os_unsigned_int32 num_ptrs_in_head() const ;
  virtual os_unsigned_int32 num_ptrs_in_blocks() const ;

  virtual os_chained_list_block* allocate_new_block(
  	_Chained_list_cursor* c =0 );

  virtual os_unsigned_int32 contains_local(const void* v) const;

  virtual os_unsigned_int32 count_local(const void* v) const;
 

protected:

  virtual os_chained_list_block* allocate_new_block(
  	os_chained_list_block* _this, os_chained_list_block*clb,
	_Chained_list_cursor* c=0 );

  /* returns the local index if found, else 0xffffffff */
  virtual os_unsigned_int32 contains_local(
  	const os_chained_list_block* _this, const void* v ) const;

  virtual os_unsigned_int32 count_local(
  	const os_chained_list_block* _this, const void* v ) const;

  virtual void delete_block(os_chained_list_block* _this);

public:
   
  os_chained_list_4_8(os_unsigned_int32 size = 0,
                      os_unsigned_int32 behavior = 0) 
      : os_chained_list(size, behavior) {}

  virtual ~os_chained_list_4_8();

private:

  os_unsigned_int32 max_local_card() const;

public:

  static os_typespec* get_os_typespec();


}; /* class os_chained_list_4_8*/

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif /* _COLL_CHAINED_LIST */


