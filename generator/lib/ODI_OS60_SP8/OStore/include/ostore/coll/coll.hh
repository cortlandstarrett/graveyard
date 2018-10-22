/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _ABSTRACT_COLLECTION
#define _ABSTRACT_COLLECTION

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#endif

#if !defined (_OS_STATIC_DM) && defined (sun)
#define _OS_STATIC_DM
#endif

/* __null is a builtin symbol for the gcc compiler, so we can't use it
   as a method name.  Unfortunately we can't change it across the
   board since it is an exported symbol and that would break link
   compatability.  The macro below will be used anywhere we need the
   __null function in the collections code. PZL 12/8/00 */
#if defined(__os_linux)
#define __OS_COLL_IS_NULL __is_null
#else
#define __OS_COLL_IS_NULL __null
#endif

#if !defined(_OS_PSE_COLL)

#define _PSE_NS_

#include <ostore/except.hh>
#include <ostore/os_types/virtfunc.hh>
#include <ostore/strconv/chrconv.hh>

#else //_OS_PSE_COLL

#include <os_pse/namespce.hh>
#include <os_pse/api/os_excpt.hh>
#include <os_pse/psecoll/virtfunc.hh>
#include <os_pse/softptr.hh>

_OS_BEGIN_NAMESPACE(os_pse)
class os_str_conv {
public:
  enum encode_type { UNKNOWN=0 };
};

#endif

// unified exception declaration macro.
#if defined(_OS_PSE_COLL)
#define OS_ERR_COLL_CLASS(C, P) \
  class _OS_COLL_IMPORT C : public P { \
        _OS_ERR_CLASS_BODY(C, P) };
#ifdef _OS_DECLARE_COLL_EXCEPTION
#undef _OS_DECLARE_COLL_EXCEPTION
#endif
#define _OS_DECLARE_COLL_EXCEPTION(dllname,name,parent) \
  OS_ERR_COLL_CLASS(os_##name,os_##parent) \
  extern _OS_COLL_IMPORT os_##name name
#else
#define _OS_DECLARE_COLL_EXCEPTION(dll_name,name,parent) \
  extern "C" dll_name##_IMPORT objectstore_exception name
//_OS_DECLARE_EXCEPTION(dllname,name);
#endif

#ifdef _OS_MicrosoftCC
/* disable the folowing warning which is caused by us declaring the structures as exporting
warning C4251: '_coll' : class 'os_soft_pointer32<class whatever>'
needs to have dll-interface to be used by clients of class 'whatever'
 */
#pragma warning(disable : 4251)
#endif

/* the mother of all coll exceptions */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll,err);

/* raised for errors related to the index-only representation */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_index_only,err_coll);

/* raised when a collection with a multi-trans-add-index in progress updated*/
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_add_index_in_progress,err_coll);

/* raised when attempting to update a collection with a protected cursor */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_prot_curs,err_coll);

/* raised when a transaction completes and at least one transient, ordered
   cursor exists on a persistent collection.
   */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_trans_cursor,err_coll);

/* Dangling pointer from collection to deleted object, detected due
   to os_backptr present during deletion of containing object. */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_dangling_pointer,err_coll);

/* the protocol expected a non empty set, but was used on an empty set instead */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_empty,err_coll);

/* the collection was accessed using an out-of-bounds array subscript */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_out_of_range,err_coll);

/* Root exception for collection evolution. */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_evolve,err_coll);

/* Unimplemented part of collection evolution. */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_evolve_not_implemented_yet,err_coll_evolve);

/* collection::only expected a singleton set but the cardinality() != 1 */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_not_singleton,err_coll);

/* syntax/semantic analysis of the query text resulted in an error. */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_illegal_query_expression,err_coll);

/* the query had free references but these references were not bound at the */
/* of the query. The report identifies the unbound variables */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_query_bind,err_coll);

/* error during evaluation of a query */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_query_evaluate,err_coll);

/* attempt to update a const coll thru cursor */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_illegal_update,err_coll);

/* the protocol expected a non-null cursor for the particular operation */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_null_cursor,err_coll);

_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_illegal_cursor,err_coll);

/* an actual argument used in the collection protocol failed validation */
/* the text of the report contains details regarding the specific argument */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_illegal_arg,err_coll);

/* The representation policy was semantically inconsistent w.r.t the */
/* collection object */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_behavior_inconsistency,err_coll);

/* An attempt was made to use a collection subtype specific protocol that was */
/* not supported by this particular subtype */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_not_supported,err_coll);

/* The operation required that the collection be orderedt, but it wasn't */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_not_ordered,err_coll);

/* An attempt was made to duplicate an element in a collection */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_duplicates,err_coll);

/* An attempt was made to insert a null element into a collection */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_nulls,err_coll);

/* An attempt was made to grow a collection that could not be grown, usually */
/* because the grow_by or the grow_at parameter to collection creation */
/* specified no growth */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_cannot_grow_collection,err_coll);

/* A collection could not be mutated into an alternate representation */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_cannot_mutate_collection,err_coll);

/* this exception is used to signal internal collection errors */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_internal,err_coll);

/* An illegal cast operation was attempted */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_illegal_cast,err_coll);

/* error in index */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_index,err);

/* Violation of uniqueness constraint on an index. */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_index_duplicate_key,err_coll);

/* For not-implemented-yet collection features */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_not_implemented_yet,err_coll);

/* Trying to iterate with an unordered index. */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_index_wrong_kind,err_coll_not_implemented_yet);

/* Invalide ordering for an index. */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_index_invalid_ordering,err_coll);

/* error during evolution of index */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_index_evolve,err_index);

/* Miscellaneous error during an index related operation */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_index_miscellaneous,err_coll);

/* Unimplemented index evolution feature */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_index_evolve_not_implemented_yet,err_index_evolve);

/* iteration open on mapping being deleted. */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_open_iteration,err_coll);

/* error in cursor maintenance */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_cursor,err_coll);

/* Need index on restricted cursor */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_cursor_restricted,err_coll);

/* error in cursor order specification */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_cursor_ambiguous,err_coll);

/* error in cursor maintenance */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_cursor_not_implemented_yet,err_cursor);

/* error in ordered iteration */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_cursor_internal,err_cursor);

/* attempt to operate on null cursor */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_null_cursor,err_cursor);

/* error in path interpretation */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_path_interp,err_coll_internal);

/* error in internal list */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_internal_list,err_coll_internal);

/* error in index lookup during scan */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_none_qualifying,err_coll_internal);

/* error in scan */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_scan,err_coll_internal);

/* error during translation of an index path expression */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_illegal_index_path,err_coll);

/* one range fills up due to bad hash function */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_rhash_range_full,err_coll);

/* collection verificaton failure */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_verification,err_coll);

/* inconsistent hash values being returned from hash function */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_inconsistent_hash_values,err_coll);

/* missing assign function */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_missing_assign,err_coll);

/* os_set::optimized_set is only allowed with a transient os_set */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_transient_set,err_coll);

/* invalid pattern as right operand of ~~ operator in a collections query */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_query_invalid_pattern,err_coll);

/* cursor being passed to os_coll function has a different _contents */
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_coll_cursor_mismatch,err_coll);

/* exceptions moved from osbtree.hh which had no comments*/

_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am,err_coll);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_bad_cursor,err_am);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_corrupt,err_am);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_dup_key,err_am);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_dup_key_item,err_am_dup_key);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_empty,err_am);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_key,err_am);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_no_key,err_am);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_no_mark,err_am);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_no_prev,err_am);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_not_singleton,err_am);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_null_cursor,err_am);
_OS_DECLARE_COLL_EXCEPTION(_OS_COLL,err_am_restriction,err_am);

_OS_DECLARE_COLL_EXCEPTION(_OS_CLIENT,err_null_pointer,err);
_OS_DECLARE_COLL_EXCEPTION(_OS_CLIENT,err_address_space_full,err);

class _Index_component;
class _Index_name;
class _Indexes;
class coll_query ;
class os_collection;
#if !defined(_OS_PSE_COLL)
// TBD these are deffed out because they conflict with the definition in os_db.hh which are in
// the os_pse namespace.  When the namespace is wholly implemented for PSE collections, this
// might not be necessary.
class os_database ;
class os_segment ;
class os_cluster ;
class os_cluster_with ;
#endif
class os_keyword_arg_list ;
class os_backptr ;
class os_bound_query ;
class os_cursor ;
class os_index_path ;
class os_coll_range;
class _RH_oflo_list;
class pset;
class _Basic_type;

/*---------------------------------------------------------------*/
/*  The following class is for internal use only.                */
/*---------------------------------------------------------------*/
class _coll_do_nothing {
public:
  char _dummy;
  _coll_do_nothing() {}
  static _coll_do_nothing _DO_NOTHING;
};
/*---------------------------------------------------------------*/

/* Definitions for DEC C++. */
typedef os_collection& os_collection_r;
typedef os_bound_query const& os_bound_query_const_r;
typedef _Indexes* _Indexes_p;
typedef _Index_name* _Index_name_p;

enum os_collection_query_dups { 
  os_collection_query_dont_preserve_duplicates = 0,
  os_collection_query_preserve_duplicates = 1,
  os_collection_query_dups_pad = 1<<30
  };

/* Note: As of 6.0 pick_from_empty_returns_null is a dead enum where we
 * always return nulls.  Since most all applications had to set this
 * we're keeping it around for convenience.
 */ 
enum os_collection_behavior {
    os_collection_allow_duplicates=1<<1,
    os_collection_signal_duplicates=1<<2,
    os_collection_allow_nulls=1<<3,
    os_collection_maintain_order=1<<4,
    os_collection_pick_from_empty_returns_null=1<<6,
    os_collection_be_an_array = 1<<7,
    os_collection_untransformed = 1<<15,   
    os_collection_disallow_duplicates = 1<<16,
    os_collection_optimized_set = 1<<17,
	os_collection_global_optimized = 1<<19,
    /* mask used to extract just the behavior bits, when the field is packed */
    os_collection_behavior_mask=0xff,
       
    os_collection_behavior_pad=1<<30
};

enum {
  os_collection_all_behaviors = -1
};

enum os_index_path_options
{
  os_index_path_ordered =             1 << 0,
  os_index_path_no_duplicates =       1 << 1,
  os_index_path_signal_duplicates =   1 << 2,
  os_index_path_point_to_key =        1 << 3,
  os_index_path_use_references =      1 << 4,
  os_index_path_index_on_pointer_target =     1 << 5,

  os_index_path_allow_duplicates = 0,
  os_index_path_unordered = 0,
  os_index_path_copy_key = 0,
  os_index_path_options_pad = 1<<30
};  /* Cross-reference: path.hh */

#ifndef _Path_op_included
enum _Coll_clustering { 
	_Coll_cluster_db, 
	_Coll_cluster_seg, 
	_Coll_cluster_cluster, 
	_Coll_clustering_pad = 1<<30 
};
#endif

#ifdef __os_cplusplus
#pragma ObjectStore path_class_name os_index_path
#endif

enum os_rep_type {
  os_unspecified_rep = 0,
  os_packed_list_rep,
  os_chained_list_rep,
  os_ixonly_rep,
  os_dyn_hash_rep,
  os_dyn_bag_rep,
  os_rep_type_pad = 1<<30
};

// Enums for query memory mode
enum os_query_memory_mode {
  os_query_memory_mode_none = 0,
  os_query_memory_mode_normal,
  os_query_memory_mode_low,
  os_query_memory_mode_pad = 1<<30
};


/*****************************************************************************
* 									     *
* All the subtypes built upon collections must have the same size. This	     *
* requirement is imposed by the fact that a collection may transformed to a  *
* more suitable representation at any point in it's life. This		     *
* transformation may take place any time during it's existence. The	     *
* transformation must preserve object identity, and as a consequence must be *
* done in place. It is only required that all subtypes be the same same	     *
* size, they need not have the same layout. Any substructures used to	     *
* implement the subtype are not constrained in any way. In order to ensure   *
* that collection transformation is transparent to the collection client     *
* code, the implementation should never pass "pointers" into the	     *
* implementation to the client code. The only exception to this rule is the  *
* cursor abstraction. This is a special case, "pointers" contained within    *
* cursors are managed via the private cursor collection protocol.	     *
* 									     *
*****************************************************************************/

class os_list ;
class os_set ;
class os_bag ;
class os_array ;
class os_cursor ;
class _Pset;
class _Index_tree;
class os_rel_many;
class os_rel_m_m;
class os_rel_m_m_coll;
class os_rel_m0_m0;
class os_rel_m_m0;
class os_rel_m_m0_coll;
class os_rel_m0_m;
class os_rel_m_1;
class os_rel_m_1_coll;
class os_rel_m0_1;
class _OSRTQ_Query_QNode;
class ossql_gateway;
class Indexes;
class _Ipset;
class os_outofline_collection;


class os_collection;
typedef os_collection_r (*_Gateway_Retrieve) (os_bound_query_const_r);

class _OS_COLL_IMPORT os_collection : public os_virtual_behavior64
{
friend class os_cursor ;
friend class _Pset;
friend class _Index_tree;
friend class _Indexes;
friend class os_rel_many;
friend class os_rel_m_m;
friend class os_rel_m_m_coll;
friend class os_rel_m0_m0;
friend class os_rel_m_m0;
friend class os_rel_m_m0_coll;
friend class os_rel_m0_m;
friend class os_rel_m_1;
friend class os_rel_m_1_coll;
friend class os_rel_m0_1;
friend class _OSRTQ_Query_QNode ;
friend class _New_Qn_Qnode;
friend class _Qn_exec;
friend class ossql_gateway;
friend class _RH_oflo_list;
friend class _Coll_btree_overflow;
friend class _Ipset;
friend class _Nscan;
friend class os_cursor_holder;
friend class os_outofline_collection;
friend class os_outofline_dictionary;
friend class os_event_info_coll_index_add;

friend void 
  _Rel_single_assignment_operator (void *,void *, os_unsigned_int32,
				   os_unsigned_int32,os_unsigned_int32 ,
				   void*,os_collection *,os_collection *,
				   os_int32,os_int32,os_int32,os_int32);
friend void 
  _Rel_single_clear_inverse (void *,os_unsigned_int32,
				       os_unsigned_int32,
				       void *,os_collection*,
				       os_int32,os_int32);
friend void 
  _Rel_many_assignment_revive (os_collection*,void*,
			       os_unsigned_int32, os_unsigned_int32,
			       os_unsigned_int32,void *,os_int32,os_int32);
friend void 
  _Rel_many_insert (os_collection*,void *,os_unsigned_int32,
		    os_unsigned_int32,os_unsigned_int32,void *,
		    void *,os_int32,os_int32);
friend void
  _Rel_many_unset_all_inverses(os_collection*, 
			       void*,os_unsigned_int32,
			       os_unsigned_int32,void *,
			       os_int32,os_int32);
friend void
  _Rel_many_assignment_kill (os_collection*,void*,os_unsigned_int32,
			     os_unsigned_int32, void *,
			     os_int32,os_int32);
friend void
  _Rel_many_remove(os_collection*,void *,os_unsigned_int32,
		   os_unsigned_int32,void *,void *,
		   os_int32,os_int32);

protected:

  virtual void* _pick() const = 0;
  virtual void* _only() const = 0;
  
  virtual void _insert(os_void_const_p) = 0;
  virtual os_int32 _remove(os_void_const_p) = 0;
  
  /* List-specific update and access protocol */
  virtual void _insert_first(os_void_const_p p) = 0 ;
  virtual void _insert_last(os_void_const_p p) = 0 ;
  /* these return true if the element was removed, modifies the argument to */
  /* indicate the removed element */
  virtual os_int32 _remove_first(os_void_const_p &) = 0 ;
  virtual os_int32 _remove_last(os_void_const_p &) = 0 ;
  virtual os_int32 _retrieve_first(os_void_const_p &) const = 0 ;
  virtual os_int32 _retrieve_last(os_void_const_p &) const = 0 ;
  virtual void* _retrieve(const os_cursor& c) const = 0 ;
  virtual void* _retrieve(os_unsigned_int32 position) const = 0 ;
  
  virtual void _insert_after(os_void_const_p p, const os_cursor& c) = 0 ;
  virtual void _insert_before(os_void_const_p p, const os_cursor& c) = 0 ;
  virtual void _remove_at(const os_cursor& c) = 0 ;
  virtual void* _replace_at(os_void_const_p p, const os_cursor& c) = 0 ;
  
  virtual void _insert_after(os_void_const_p p, os_unsigned_int32 position) = 0 ;
  virtual void _insert_before(os_void_const_p p, os_unsigned_int32 position) = 0 ;
  virtual void _remove_at(os_unsigned_int32 position) = 0 ;
  virtual void* _replace_at(os_void_const_p p, os_unsigned_int32 position) = 0 ;
  
  virtual os_int32 _ordered_equal(const os_collection &) const ;
  virtual os_int32 _contains(os_void_const_p) const = 0;
  virtual os_int32 _count(os_void_const_p) const = 0 ;
   
  virtual os_collection& _assign(const os_collection& s);
  virtual os_collection& _assign(os_void_const_p e);
  virtual os_collection& _assign_or(const os_collection& s);
  virtual os_collection& _assign_or(os_void_const_p e);
  virtual os_collection& _assign_and(const os_collection& s);
  virtual os_collection& _assign_and(os_void_const_p e);
  virtual os_collection& _assign_sub(const os_collection& s);
  virtual os_collection& _assign_sub(os_void_const_p e);
   
  virtual os_collection& _or(const os_collection&) const;
  virtual os_collection& _or(os_void_const_p) const;
  virtual os_collection& _and(const os_collection&) const;
  virtual os_collection& _and(os_void_const_p) const;
  virtual os_collection& _sub(const os_collection&) const;
  virtual os_collection& _sub(os_void_const_p) const;
  
  virtual os_int32 _eq(const os_collection& s) const;
  virtual os_int32 _eq(os_void_const_p e) const;
  virtual os_int32 _ne(const os_collection& s) const ;
  virtual os_int32 _ne(os_void_const_p e) const ;
  virtual os_int32 _lt(const os_collection& s) const;
  virtual os_int32 _lt(os_void_const_p) const ;
  virtual os_int32 _le(const os_collection& s) const;
  virtual os_int32 _le(os_void_const_p e) const;
  virtual os_int32 _gt(const os_collection& s) const;
  virtual os_int32 _gt(os_void_const_p e) const;
  virtual os_int32 _ge(const os_collection& s) const;
  virtual os_int32 _ge(os_void_const_p e) const;
  
  virtual os_int32 _first(os_cursor&, os_void_p &) const = 0;
  virtual os_int32 _last(os_cursor&, os_void_p &) const = 0;
  virtual os_int32 _next(os_cursor&, os_void_p &) const = 0;
  virtual os_int32 _previous(os_cursor&, os_void_p &) const = 0;
  
  virtual os_collection* _get_innermost_collection();
  
  virtual os_int32 _remove_all(os_void_const_p);
  
  virtual void _unbind_cursor(os_cursor& c) const;
  
  virtual os_unsigned_int32 _cardinality() const = 0 ;
  virtual os_int32 _empty() const = 0 ;

  virtual os_unsigned_int32  _update_cardinality();
  virtual os_unsigned_int32 _cardinality_estimate() const;
  virtual os_int32 _cardinality_is_maintained() const;
  
  virtual void _re_initialize(os_unsigned_int32 size);

public:
  /* From old coll: */
  enum ord_spec { unordered = os_index_path_unordered,
		  ordered = os_index_path_ordered,
		  ord_spec_pad = 1<<30 };
  enum _Duplication { DUPLICATES, NO_DUPLICATES, _Duplication_pad = 1<<30 };
  enum restriction { EQ = 0, NE = 100, LT = -1, LE = -2,
		     GT = 1, GE = 2, ANY = 200, restriction_pad = 1<<30 };
  /* Query intermediates: */
  enum _Temp_signal { TEMPORARY, _Temp_signal_pad = 1<<30 };
  

protected:
  /* index functions */
  virtual os_int32 has_indexes() const ;
  virtual _Indexes*& indexes() = 0;
  void add_temporary_index(const os_index_path&, os_int32 index_options);
  void drop_temporary_index(const os_index_path&);
  void add_index_name(_Index_name const*);
  os_boolean is_temporary_index(const _Index_name*);
  void remove_index_name(_Index_name const*);
  _Index_name* _index(const os_index_path&, os_int32 /* restriction */) const;
  void maintain_index_insert(_Indexes*, const void*, os_boolean = 0);
  void maintain_index_remove_for_sure(_Indexes*, const void* );
  void maintain_index_remove(_Indexes*, const void*);
  virtual void _add_index(const os_index_path&, os_int32,
			  const void*, _Coll_clustering);
  os_boolean _index_already_exists(const os_index_path&,os_int32,_Indexes_p &);
  
  /* Set behavior safely */
  static os_unsigned_int16 modified_behavior(os_unsigned_int16 b_old,
					     os_unsigned_int16 b_new)
    { return 
	(os_unsigned_int16)((b_new & behavior_mask));
    }

  // Static function to convert behavior bits to a rep string.
  static void bits_to_rep(char *, os_unsigned_int32 behavior);
  static os_collection * generate_rep(const char * type,
                                      os_database * db,
				      os_unsigned_int32 size,
                                      os_unsigned_int32 behavior=0,
                                      os_unsigned_int32 card=0,
                                      void * filler = (void*)0);
  static os_collection * generate_rep(const char * type,
                                      os_segment * seg,
				      os_unsigned_int32 size,
                                      os_unsigned_int32 behavior=0,
                                      os_unsigned_int32 card=0,
                                      void * filler = (void*)0); 
  static os_collection * generate_rep(const char * type,
                                      os_cluster_with & cl,
                                      os_unsigned_int32 size,
                                      os_unsigned_int32 behavior=0,
                                      os_unsigned_int32 card=0,
                                      void * filler = (void*)0); 
  static os_collection * generate_rep(const char * type,
                                      const void * prox,
                                      os_unsigned_int32 size,
                                      os_unsigned_int32 behavior=0,
                                      os_unsigned_int32 card=0,
                                      void * filler = (void*)0); 

  void _dbg_element_index_compare(const _Basic_type *, const char *) const;
  void _dbg_check_element_with_indexes(const void *) const;
  void _dbg_check_index_with_collection(const os_index_path &) const;

public:
  void _dbg_check_all_indexes() const;

public:
  void _set_backptr(const _Index_component*, const void* v = 0);
  void _prune_backptr(const _Index_component*, const void* v = 0);
  
public:  /* HERE BEGINS THE PUBLICLY VISIBLE PART OF THE COLLECTION INTERFACE */
 
  /* For compatibility we need to map these to os_cursor enums. */
  enum { forward = 0, reverse = 1,
	 unsafe = 0, safe = 1 << 6,
         default_order = 0, order_by_address = 1 << 18,
	 update_insensitive = 1 << 6,
	 index_on_pointer_target = 0  /* old and meaningless */
	 };
  enum { direction_mask = 1 };
  
protected:
  virtual void _clear() = 0 ;
  
public:
  static void initialize() ;
  
  void clear();
  /* Update protocol */
  void insert(const void* p);
  os_int32 remove(const void* p);
  
  
  /* List-specific update and access protocol */
  void insert_first(const void* p);
  void insert_last(const void* p);
  os_int32 remove_first(os_void_const_p &p);
  os_int32 remove_last(os_void_const_p &p);

  /* for collections that don't contain null pointers */
  /* --- The (const void*) coercions get around a BCC bug. */
  void* remove_first();
  void* remove_last();
  void* retrieve_first() const;
  void* retrieve_last() const;
  void* retrieve(os_unsigned_int32 position) const;
  void* retrieve(const os_cursor& c) const;
  
  void insert_before(const void* p, const os_cursor& c);
  void insert_after(const void* p, const os_cursor& c);
  void remove_at(const os_cursor& c);
  void* replace_at(const void* p, const os_cursor& c);
  
  void insert_before(const void* p, os_unsigned_int32 position);
  void insert_after(const void* p, os_unsigned_int32 position);
  void remove_at(os_unsigned_int32 position);
  void* replace_at(const void* p, os_unsigned_int32 position);
  
  os_int32 retrieve_first(os_void_const_p &v) const;
  os_int32 retrieve_last(os_void_const_p &v) const;
  
public:
  /* retrieval from os_collection */
  void* pick() const;
  void* pick(const os_index_path& p, const os_coll_range& r) const;
  
  void* only() const;
  
public:
  
  /* membership */
  os_int32 contains(const void* p) const;
  os_int32 count(const void* p) const;
  
  os_int32 ordered_equal(const os_collection &c) const;

  /* collection properties */
public:
  os_unsigned_int32 cardinality() const;
  os_int32 empty() const;
  operator os_int32() const;
  os_unsigned_int32 update_cardinality();
  os_unsigned_int32 cardinality_estimate() const;
  os_int32 cardinality_is_maintained() const;
  
public:
  /* index functions */
  void add_index(const os_index_path& p, os_int32 index_options,
		 os_segment* seg = 0 /* 0 indicates allocate index in
					segment of collection */);
  void add_index(const os_index_path& p, 
	 	 os_int32 index_options, os_cluster* cls);
  void add_index(const os_index_path& p, 
		 os_int32 index_options, os_database* db);
  void add_index(const os_index_path& p, os_segment* seg = 0);
  void add_index(const os_index_path& p, os_cluster*);
  void add_index(const os_index_path& p, os_database* db);

#if !defined(_OS_PSE_COLL)
  static void multi_trans_add_index
    (os_reference /* os_Reference<os_collection> */,
     const os_index_path& p,
     os_int32 index_options,
     os_segment* index_seg,
     os_segment* scratch_seg,
     os_unsigned_int32 num_per_trans);

  static void multi_trans_drop_index
    (os_reference /* os_Reference<os_collection> */,
    const os_index_path& p,
    os_segment* scratch_seg,
    os_unsigned_int32 num_per_trans);
#endif

  void drop_index(const os_index_path&);


  os_int32 has_index(const char*, os_int32 index_options,
		     os_char_const_p rank_func_name,
		     _Index_name_p * iname_out = 0) const;

  os_int32 has_index(const os_index_path&, 
		     os_int32 index_options = unordered) const;

  /* Returns a collection of os_index_name* if the collection has */
  /* indices; otherwise, returns 0. The caller has the responsibility */
  /* of deleting the collection and its content. */
  os_collection* get_indexes() const;

  /* Returns a collection of os_index_name* if the collection has */
  /* indices; otherwise, returns 0. The caller has the responsibility */
  /* of deleting the collection and its content. */
  /* Returns the element type name via the const char*& argument. */
  os_collection* get_indexes(os_char_const_p & element_type_name) const;

  /* Returns the segment pointer of which segment the index is allocated 
   * in or null if no segment.
   */
  os_segment * get_index_segment(char * name);
 
protected:

  os_collection* _get_indexes(os_char_const_p & element_type_name) const;
 
public:
  /* this is one of the user visible semantic os_collection types, not an */
  /* implementation/representation type */
  enum os_collection_type { OS_Collection, OS_Set, OS_Bag, OS_List, OS_Array,
			    OS_Dictionary,
			    os_collection_type_pad = 1<<30
			  };
  os_collection_type type () const;  /* actual semantic type of the instance */
  static os_collection_type default_type() { return OS_Collection; }


public:
  
  operator const os_list &() const;
  operator const os_set &() const;
  operator const os_bag &() const;
  operator const os_array &() const;
  
  operator os_list &();
  operator os_set &();
  operator os_bag &();
  operator os_array &();

public:
  /* assignment operators */
  os_collection& operator =(const os_collection& s);
  os_collection& operator =(const void* e);
  os_collection& operator |=(const os_collection& s);
  os_collection& operator |=(const void* e);
  os_collection& operator &=(const os_collection& s);
  os_collection& operator &=(const void* e);
  os_collection& operator -=(const os_collection& s);
  os_collection& operator -=(const void* e);
  
  /* non-destructive set operators */
  os_collection& operator |(const os_collection& s) const;
  os_collection& operator |(const void* e) const;
  os_collection& operator &(const os_collection& s) const;
  os_collection& operator &(const void* e) const;
  os_collection& operator -(const os_collection& s) const;
  os_collection& operator -(const void* e) const;
  
  /* equality operators */
  os_int32 operator ==(const os_collection& s) const;
  os_int32 operator ==(const void* e) const;
  os_int32 operator !=(const os_collection& s) const;
  os_int32 operator !=(const void* e) const;
  os_int32 operator <(const os_collection& s) const;
  os_int32 operator <(const void* e) const;
  os_int32 operator <=(const os_collection& s) const;
  os_int32 operator <=(const void* e) const;
  os_int32 operator >(const os_collection& s) const;
  os_int32 operator >(const void* e) const;
  os_int32 operator >=(const os_collection& s) const;
  os_int32 operator >=(const void* e) const;
  

  enum {
    allow_duplicates = os_collection_allow_duplicates,
    signal_duplicates = os_collection_signal_duplicates,
    allow_nulls = os_collection_allow_nulls,
    maintain_order = os_collection_maintain_order,
    be_an_array = os_collection_be_an_array,
    pick_from_empty_returns_null = os_collection_pick_from_empty_returns_null, 
    disallow_duplicates = os_collection_disallow_duplicates,
    untransformed = os_collection_untransformed,
    optimized_list = os_collection_optimized_set,
    /* mask used to extract just the behavior bits, when the field is packed */
    behavior_mask = os_collection_behavior_mask
  
    };

  static void behavior_names(os_unsigned_int32 behavior,
                             char *            behavior_names_str) ;

  /* get the default behavior associated with this type */
  /* i.e. if you say collection::create, this is the behavior you will get */
  static os_unsigned_int32 default_behavior() {return 0;};

  /* Determine behavior for result of a non-destructive set operation */
  static os_unsigned_int32 combine_behavior(os_unsigned_int32,
					    os_unsigned_int32);

protected:
  /* get the set of behavior associated with the particular coll object */
  virtual os_unsigned_int32 _get_behavior() const = 0;

   
  void change_behavior_via_facade(os_unsigned_int32 new_behavior,
				  const char* type_name,
				  os_int32 default_behavior,
				  os_int32 verify);
  
public:
  /* get the set of behavior associated with the particular coll object */
  os_unsigned_int32 get_behavior() const;
 
public:

  /* creation and deletion */
  virtual ~os_collection();
  static os_collection &create(os_database*, os_unsigned_int32 behavior = 0,
			       os_int32 expected_size = 0);

  static os_collection &create(os_segment*, os_unsigned_int32 behavior = 0,
			       os_int32 expected_size = 0);

  static os_collection &create(os_cluster_with &,
			       os_unsigned_int32 behavior = 0,
			       os_int32 expected_size = 0);

  static os_collection &create(os_cluster_with *,
			       os_unsigned_int32 behavior = 0,
			       os_int32 expected_size = 0);

  static os_collection &create(const void*, os_unsigned_int32 behavior = 0,
			       os_int32 expected_size = 0);

  static os_collection &create(os_int32 /* _Temp_signal */,
			       os_unsigned_int32 behavior = 0,
			       os_int32 expected_size = 0);

  static void destroy(os_collection& c) { delete (os_collection*)&c; }

protected:
  
#ifdef _OS_BorlandCC
  os_collection();
#else
  os_collection() { }
#endif
  os_collection(const os_collection&) { }

  virtual void _destroy();

public:
  /* Query protocol */

  enum { query_dont_preserve_duplicates = 0,
	 query_preserve_duplicates = 1
	 };

    os_collection& query(char *element_type,
		       char *query_string,
		       os_database *schema_db = 0,
		       char* file_name = 0,
		       os_unsigned_int32 line = 0,
		       os_boolean dups = query_dont_preserve_duplicates) const;
  os_collection& query(char *element_type,
                       char *query_string,
                       os_str_conv::encode_type string_literal_char_encoding,
                       os_database *schema_db = 0,
                       char* file_name = 0,
                       os_unsigned_int32 line = 0,
                       os_boolean dups = query_dont_preserve_duplicates) const;
  os_collection& query(const os_bound_query&,
		       os_boolean dups = query_dont_preserve_duplicates) const;

   

  void* query_pick(char *element_type,
		   char *query_string,
		   os_database *schema_db = 0,
		   char *file_name = 0,
		   os_unsigned_int32 line = 0) const;
  void* query_pick(char *element_type,
                   char *query_string,
                   os_str_conv::encode_type string_literal_char_encoding,
                   os_database *schema_db = 0,
                   char *file_name = 0,
                   os_unsigned_int32 line = 0) const; 
  void* query_pick(const os_bound_query&) const;

  os_int32 exists(char *element_type,
		  char *query_string,
		  os_database *schema_db = 0,
		  char *file_name = 0,
		  os_unsigned_int32 line = 0) const;
  os_int32 exists(char *element_type,
                  char *query_string,
                  os_str_conv::encode_type string_literal_char_encoding,
                  os_database *schema_db = 0,
                  char *file_name = 0,
                  os_unsigned_int32 line = 0) const;
  os_int32 exists(const os_bound_query&) const;

  /* Control threshold for doing pre-sorted iteration in queries */
    static void set_query_iteration_presort_threshold(os_unsigned_int32 t) ; 
  static os_unsigned_int32 query_iteration_presort_threshold() ;

  /* 
     public, but for internal use only, for dml queries of the
     form [: this == foo :] 
     */
  /* scaffold - dummy funtion until merge into houdini */
  _Pset* _this_query(os_int32  ,const void*) const;
  void* _this_pick_query(os_int32  , const void*,
                         os_unsigned_int32&) const;

  virtual os_boolean _fast_count() const = 0;
  _Index_name* _index(const char*, os_int32 /* restriction */) const;
  _Index_name* _index(const char*, os_int32 /* restriction */,
		      const char* /* zvec_func_name */ ) const;
  os_int32 _presort_if_appropriate() const ;

  /* Representation protocol */
protected:
 
			   
  /* return the name of the "most derived class" that implements the coll */
  virtual char * _rep_name() const = 0;

  virtual os_int32 _rep_enum() const = 0;
  				
  virtual void _check_rep_invariants() const = 0;

public:
  /* returns true, if it is a collection implementation that is available */
  /* to the user */
  virtual os_int32 _is_user_coll() const;

public:

  /* return the name of the "most derived class" that implements the coll */
  char *rep_name() const;
  os_int32 rep_enum() const;
				
  void check_rep_invariants() const;

public:

  static void set_protect_unsafe_cursors(os_boolean b);
  static void set_warn_if_coll_deleted_before_cursor(os_boolean b);


// Function for setting query memory mode
public:
  static void set_query_memory_mode(os_query_memory_mode m);
 
 
public:

  static void _set_record_index_use(os_boolean b);
  static void _clear_index_use_history();
  static const os_list* _get_index_use_history();
  static void _record_index_use(_Index_name* in);

  /* Schema evolution */

private:
  
  friend class os_backptr;  
  friend class _Backptr;
  void evolution_transform();
  void pre_evolution_transform();
 
  virtual void _set_untransformed(os_boolean flag);
  virtual void evolve_rep();
 
public:
  static void _schema_evolution_initialize();
  static void _pre_evolution_transform(void* p);
  static void _evolution_transform(void* p);
  os_boolean transformed() const
    { return !(get_behavior() & untransformed); }
public:
  static os_typespec* get_os_typespec();

} ;

#if defined(__os_linux)
/* typedefs don't work so well in the circumstances in which these
   are used, so use #defines instead. */
#define os_os_collection_type os_collection::os_collection_type
#define os_collection_restriction os_collection::restriction
#define os_collection_ord_spec os_collection::ord_spec
#define _OS_collection_duplication os_collection::_Duplication
#else
typedef os_collection::restriction os_collection_restriction;
typedef os_collection::ord_spec os_collection_ord_spec;
typedef os_collection::_Duplication _OS_collection_duplication;
typedef os_collection::os_collection_type os_os_collection_type;
#endif

/* class used to collect "use" parameters for collections */
class os_coll_use_parameters {
public:
  /* percentages indicting the relative frequency of each operation */
  os_int16 insert, remove, lookup, traverse,
       insert_first, insert_last,
       remove_first, remove_last,
       misc,
       dups;

  os_int16 space_time_tradeoff ;
  os_coll_use_parameters(os_int16 insert, os_int16 remove, os_int16  lookup, os_int16 traverse,
			 os_int16 insert_first=0,
			 os_int16 insert_last=0,
			 os_int16 remove_first=0,
			 os_int16 remove_last=0,
                         os_int16 misc=0,
                         os_int16 dups=0) ;

} ;





class _OS_COLL_IMPORT os_outofline_collection : public os_collection
{
friend class os_collection_dump;
friend class os_collection_load;
friend class os_coll_element_fixup_loader;
public:
  // These are public to allow standalone instantiation so the vtbl
  // can be looked up for dynamic dispatching in colvsdp.cc
  os_outofline_collection();
  os_outofline_collection(os_collection *);

protected:
  

  // Generator functions for facade classes.  These functions are used
  // to get around missing os_typespec functions for transient collections
  static os_outofline_collection * generate_facade(const char * type,
                                                   os_database * db,
						   os_unsigned_int32 size,
                                                   os_unsigned_int32 beh=0,
                                                   os_unsigned_int32 card = 0,
                                                   void* filler = (void*)0);
  static os_outofline_collection * generate_facade(const char * type,
                                                   os_segment * seg,
						   os_unsigned_int32 size,
                                                   os_unsigned_int32 beh=0,
                                                   os_unsigned_int32 card = 0,
                                                   void* filler = (void*)0);   

  //we dont need this overload in PSE since os_cluster_with is nothing but 'void *'
#ifndef _OS_PSE_COLL
  static os_outofline_collection * generate_facade(const char * type,
                                                   os_cluster_with & cl,
                                                   os_unsigned_int32 size,
                                                   os_unsigned_int32 beh=0,
                                                   os_unsigned_int32 card = 0,
                                                   void* filler = (void*)0); 
#endif
  static os_outofline_collection * generate_facade(const char * type,
                                                   void * prox,
                                                   os_unsigned_int32 size,
                                                   os_unsigned_int32 beh=0,
                                                   os_unsigned_int32 card = 0,
                                                   void* filler = (void*)0);  
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

protected:
  /* these functions are needed by dumpload */
  void set_outofline(os_collection *);
  os_collection * get_outofline();

protected:
  // outofline collection pointer
  os_collection* _coll;  
  char  _os_pad_0[4];   /* 64-bit neutralization */
public:
  static os_typespec* get_os_typespec();

  virtual ~os_outofline_collection();

};  // os_outofline_collection


class _Indexes
{
  friend class os_ixonly;
  friend class os_collection;
  friend class os_event_info_coll_index_add;

private:
  os_soft_pointer<os_collection> owner;
  os_soft_pointer<os_list> names;                /* os_List<_Index_name*> */
  os_soft_pointer<os_list> requested_names;      /* os_List<_Index_name*> */
  os_soft_pointer<_Index_tree> tree;
  os_soft_pointer<os_backptr> backptrs;

private:

  static os_index_path*
  make_valid_evolved_index(_Index_name* in, const char* type);

public:
  _Indexes(const os_collection*);
  ~_Indexes();
  const char* element_type_name() const;
  void set_element_type_name(const char*);
  void evolution_transform();
  void pre_evolution_transform();
  void check_rep() const;

  /* Functions needed for index-only collection rep (os_ixonly) */
  _Index_component *icomp_with_a_mapping();
  void interpret_singleton(_Index_component* icomp, os_void_p & value, os_void_p & retval) const;

  static os_typespec* get_os_typespec();
};

/*---------------------------------------------------------------------- */


#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif

/* From mapping.hh: */
#ifndef _MAPPING_FUNCTIONS
#define _MAPPING_FUNCTIONS
typedef os_int32 (*_Rank_fcn)(os_void_const_p, os_void_const_p);
typedef os_unsigned_int32 (*_Hash_fcn)(os_void_const_p);
typedef void (*_Assign_fcn)(void*, void*);
#endif


