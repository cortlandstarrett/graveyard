/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _Pset_included
#define _Pset_included

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else // !defined(_OS_PSE_COLL)
#include <os_pse/psecoll/hdrstart.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif // !defined(_OS_PSE_COLL)

typedef _Pset* _Pset_p;

class os_dictionary;
class _Index_component;
class os_collection;
class _Fn_Deref;
class _Fn_Ob_value;
class _Fn_Deset;

class _Pcell;

class _OS_COLL_IMPORT _Pset
{
/*...................................................................... */

/* representation */

protected:
  os_int32 offset;
  os_boolean duplicates;
  enum { OS_PSET_ONE, OS_PSET_MANY, os_pset_size_pad = 1<<30 } size;
  union contents_u
    {
      void* one;
      os_collection* many;
    } contents;
  union current_u
    {
      void* one;
      os_cursor* many;
    } current;

  os_unsigned_int32 n_visited;

  // The next two flags are used for low address space queries
  os_boolean low_address_space;  // True if low address space query.
  os_boolean set_based;          // True if pset is a set as opposed
                                 // to a list.

protected:

  _Pset(os_boolean, os_unsigned_int32, os_boolean make_a_set = 0);
  void set_memory_mode(os_boolean);

public:
  _Pset(os_boolean);
  _Pset(const os_collection&, os_boolean);
  _Pset(os_cursor&,os_unsigned_int32, os_boolean);
  _Pset(const _Pset&, os_boolean);
  ~_Pset();

  /* iteration */
  void reset(os_int32 sort_by_address = 0, os_int32 force_sort = 0);
  void* last(os_address_space_marker *);
  void* previous(os_address_space_marker *);
  void* next(os_address_space_marker *);
  os_unsigned_int32 visited() const
    { return n_visited; }

public:
  /* interpretation */
  void replace_ptr();
  void replace_ptr_fn(const _Fn_Deref* const pop);
  void replace_set();
  void replace_set_fn(const _Fn_Deset* const pop);
  void add_offset(os_int32, os_int32&);
  void clear_offset()
    { offset = 0; }
  void replace_key_by_data(os_dictionary const * const, os_boolean make_set = 0);
  void lookup(os_dictionary const * const,
	      os_int32 /* os_collection::restriction */, void*);
  void lookup(os_dictionary const * const,
	      os_int32 /* os_collection::restriction */, void*,
	      os_int32 /* os_collection::restriction */, void*);
  void operator &=(const _Pset&);
  void operator |=(const _Pset&);
  void operator -=(const os_collection&);
  void operator -=(const _Pset&);
  void restore_offset(os_int32);
  void complete();
  void* pick() const;

  /* forward interpretation during drop_index */
  void replace_ptr_and_disassociate(const _Index_component*, os_int32);
  void replace_ptr_fn_and_disassociate(const _Index_component*, 
				       const _Fn_Deref* const);
  void replace_set_and_disassociate(const _Index_component*);
  void replace_set_fn_and_disassociate(const _Index_component*,
				       const _Fn_Deset* const);
  void terminal_disassociate(const _Index_component*, os_int32);
  void terminal_disassociate_fn(const _Index_component* index_component,
			   const _Fn_Ob_value* const);

  /* create inverse mappings */
  void inverse_mapping_ptr(const _Index_component*,
			   os_dictionary* const, os_int32, os_collection *);
  void inverse_mapping_ptr_fn(const _Index_component*,
			      os_dictionary* const, const _Fn_Deref* const, os_collection *);
  void inverse_mapping_set(const _Index_component*,
			   os_dictionary* const, os_collection *);
  void inverse_mapping_set_fn(const _Index_component*,
			      os_dictionary* const,
			      const _Fn_Deset* const, os_collection *);
  void inverse_mapping_ob(const _Index_component*,
			   os_dictionary* const, os_int32, os_collection *);
  void inverse_mapping_ob_fn(const _Index_component*,
			     os_dictionary* const, const _Fn_Ob_value* const, os_collection *);

  /* reachability computations */
  void forget_ptr(_Index_component*, os_int32, _Pset_p &, os_collection*);
  void forget_ptr_fn(_Index_component*, const _Fn_Deref* const, _Pset_p &,
                     os_collection*);
  void forget_set(_Index_component*, _Pset_p &, os_collection*);
  void forget_set_fn(_Index_component*, const _Fn_Deset* const, _Pset_p &,
                     os_collection*);
  void forget_ob(_Index_component*, os_int32, os_collection*);
  void forget_ob_fn(_Index_component*, const _Fn_Ob_value* const,
                    os_collection*);
  void remember_ptr(_Index_component*, os_int32, _Pset_p &, os_collection *);
  void remember_ptr_fn(_Index_component*, const _Fn_Deref* const, _Pset_p &,
                       os_collection *);
  void remember_set(_Index_component*, _Pset_p &, os_collection *);
  void remember_set_fn(_Index_component*, const _Fn_Deset* const, _Pset_p &,
                       os_collection *);
  void remember_ob(_Index_component*, os_int32, os_collection *);
  void remember_ob_fn(_Index_component*, const _Fn_Ob_value* const,
                      os_collection *);

  /* update */
  /* DO NOT use during iteration over pset: */
  void insert(void*);
  void append(void*);  /* duplicates OK */
  void remove(void*);
  void clear();
  
  /* Turn result of query into collection */
  os_collection& turn_into_collection();

  /* membership */
  os_boolean empty() const;
  os_boolean contains(const void*) const;

  os_unsigned_int32 cardinality() const
    {
      return size == OS_PSET_ONE
	     ? (contents.one ? 1 : 0)
	     : contents.many->cardinality();
    }


  /* utilities */
  void remove_dups();

protected:
  void steal_contents(_Pset&);
  os_int32 unreachable(void*, os_dictionary* const) const;
  os_int32 reachable(void*, os_dictionary* const) const;
};

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else // !defined(_OS_PSE_COLL)
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif // !defined(_OS_PSE_COLL)
#endif
