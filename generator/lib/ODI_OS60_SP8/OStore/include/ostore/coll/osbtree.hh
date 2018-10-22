/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


// osbtree.hh
// Header file for collections btree used for ordered dictionaries and ordered
// indexes.  Added for 6.0 6/3/1998


#ifndef OSBTREE_HH
#define OSBTREE_HH

#if !defined(_OS_PSE_COLL)

#include <ostore/hdrstart.hh>
#include <ostore/coll/coll.hh>
#include <ostore/coll/cursor.hh>
#include <ostore/coll/lw.hh>

#else //!defined(_OS_PSE_COLL)

#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/coll.hh>
#include <os_pse/coll/cursor.hh>
#include <os_pse/coll/lw.hh>

#endif //!defined(_OS_PSE_COLL)


// Forward declarations
class _Coll_btree_node;
class _Coll_btree_stackvars;

#ifdef _OS_PSE_COLL
_OS_BEGIN_NAMESPACE(os_pse)
#endif

// Top level os_btree class
class _OS_COLL_IMPORT os_btree : public os_dictionary
{
public:
  // Construction / Destruction
  os_btree(const char* key_type,
			     os_unsigned_int32 key_size,
           os_unsigned_int32 array_size,
			     os_unsigned_int32 options = 0,
           os_unsigned_int32 cardinality = 0);

  ~os_btree();

public:

  virtual os_unsigned_int32 _cardinality() const;
  virtual os_unsigned_int32 _cardinality_estimate() const;
  virtual os_unsigned_int32 _update_cardinality();
  virtual os_int32 _cardinality_is_maintained() const {return 0;}


  // os_dictionary interface
  virtual os_dictionary_cursor& __iteration_start(os_boolean pers) const;
  virtual os_dictionary_cursor& __iteration_start(os_int32, const void*,  
						os_boolean pers) const;
  virtual os_dictionary_cursor& __iteration_start(os_int32, const void*, 
                                                  os_int32, const void*, 
                                                  os_boolean pers) const;
  virtual void __iteration_end(os_dictionary_cursor&) const;
  virtual os_int32 __count(os_dictionary_cursor&) const
          { return 1; }
  virtual os_int32 __count(const void* /* key */, const void* /* val */) const
          { return 1; }

  virtual os_int32 __duplicates() const {return allow_dups();}

  const char* _key_type() const;
  os_unsigned_int32 _key_size() const;
  os_unsigned_int32 internalKeySize() const {return _keySize;}
  const char* internalKeyType() const {return _keyType;}
  virtual os_collection* _cursors() const {return 0;}
  os_boolean _is_a_hashtable() const { return 0; }



  /* navigation */
  virtual os_int32 __first(os_dictionary_cursor&, void*&) const;
  virtual os_int32 __last(os_dictionary_cursor&, void*&) const;
  virtual os_int32 __next(os_dictionary_cursor&, void*&) const;
  virtual os_int32 __previous(os_dictionary_cursor&, void*&) const;
  virtual os_int32 __OS_COLL_IS_NULL(const os_dictionary_cursor&) const;
  virtual os_int32 __more(const os_dictionary_cursor&) const;


  /* retrieval */

  virtual void* __retrieve(const os_dictionary_cursor&) const;
  virtual void* __retrieve_key(const os_dictionary_cursor&) const;
  virtual void* __pick(os_unsigned_int32&) const;
  virtual void* __pick(os_int32 /* os_collection::restriction */,
		     const void*, os_unsigned_int32&) const;
  virtual void* __pick(os_int32 /* os_collection::restriction */, const void*,
		       os_int32 /* os_collection::restriction */, const void*,
		       os_unsigned_int32&) const;
  virtual void* _only() const;
  virtual void* _only(os_boolean&) const;
  virtual os_int32 __contains(const void*, const void*) const;
  virtual os_int32 _empty() const;

  
  /* update */

  virtual void __insert(const void* v, const void* k, os_collection * cc,
                        const void* keycopy = 0, os_unsigned_int32 hashval = 0);
  virtual void __insert(const void* v, const void* k, os_collection * cc,
                        const void* keycopy, os_boolean&);
  virtual void __remove(const void* v, const void* k, os_collection * cc);
  virtual void __remove(const void* v, const void* k, os_boolean&,
                        os_collection * cc);

  virtual void _clear();

  virtual os_unsigned_int32 _get_behavior() const;

  /* check consistency */
  virtual void _check_rep_invariants() const;

  /* cursor maintenance */

  void __reset(os_dictionary_cursor&,const void* v, const void* k, _Direction);

  virtual void _re_initialize(os_unsigned_int32 size) {}

protected:

  // Functions needed to override os_collection pure virtuals
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


public:
  static os_typespec* get_os_typespec();

protected:
  // Internal API
  void initialize(os_unsigned_int32 presize = 0);
  void check_for_remove_all_keys();
  void check_for_duplicate_class_keys();
  _Coll_btree_node * deleteAllNodes(_Coll_btree_node *);
  _Coll_btree_node * findNode(void * key, _Coll_btree_stackvars * stackvars,
                              os_boolean track_history = 0) const;
  void splitTree(_Coll_btree_node * node, const void * key, const void * data, 
                 os_unsigned_int32 pos, _Coll_btree_stackvars * stackvars);
  _Coll_btree_node * getLowNode() const;
  _Coll_btree_node * getHighNode() const;
  void treeReplaceKey(_Coll_btree_stackvars & stackvars);
  void collapseTree(_Coll_btree_node * node, 
                    _Coll_btree_stackvars & stackvars);
  void deleteNode(_Coll_btree_node * node);
  os_cluster * getNodeCluster(_Coll_btree_node * node);

  os_boolean findFirst(os_collection_restriction r,
                       const void* key,
                       os_unsigned_int32 & index, 
                       _Coll_btree_node *& node,
                       void* found_key,
                       _Coll_btree_stackvars * stackvars) const;

  os_boolean findLast(os_collection_restriction r,
                      const void* key,
                      os_unsigned_int32 & index, 
                      _Coll_btree_node *& node,
                      void* found_key,
                      _Coll_btree_stackvars * stackvars) const;


  os_boolean find_first_eq(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;
  os_boolean find_first_ne(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;
  os_boolean find_first_lt(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;
  os_boolean find_first_le(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;
  os_boolean find_first_gt(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;
  os_boolean find_first_ge(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;
  os_boolean find_last_eq(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;
  os_boolean find_last_ne(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;
  os_boolean find_last_lt(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;
  os_boolean find_last_le(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;
  os_boolean find_last_gt(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;
  os_boolean find_last_ge(const void*, os_unsigned_int32 & index, 
                           _Coll_btree_node *& node,
                           _Coll_btree_stackvars & stackvars) const;

  // Return the next key index
  os_unsigned_int32 findNextKey(_Coll_btree_node *& node,  // Node to start with
                   os_unsigned_int32 index,                // index to start with
                   os_boolean first = 0) const;     // Start with the first key

  // Return the prev key index
  os_unsigned_int32 findPrevKey(_Coll_btree_node *& node,  // Node to start with
                   os_unsigned_int32 index,                // index to start with
                   os_boolean last = 0) const;     // Start with the last key

 /* -------------------------------------------------------------------
  *  osevol and oscompactor specific functions.  See collevl2.cc for use.
  * ---------------------------------------------------------------- */
private:
   virtual void _set_untransformed(os_boolean flag);
   virtual void evolve_rep();

public:
  void setMaxKeys(os_unsigned_int32 numKeys) {_maxKeys = numKeys;}
  os_unsigned_int32 getMaxKeys() {return _maxKeys;}

  // enum for internal flags
  enum {
    var_char_key        = 1,
    point_to_key        = 2,
    os_btree_allow_dups = 4,
    char_array_key      = 8,
    cluster_created     = 16,
    untransformed       = 32,
    user_assign_fcn     = 64,
    char_nocopy_key     = 128,
    pvoid_key           = 256,
    remove_all_keys     = 512,
    class_dup_key       = 1024

  };

  // This function is used to get a free node.  It will first try the presize
  // list.  If that is empty it will then try to allocate a new one
  _Coll_btree_node * getNewNode(os_unsigned_int32 flags,
                                _Coll_btree_node * allocate_with);

  // Enum accessors
  os_boolean is_var_char_key() const {return _internalFlags & var_char_key;}
  os_boolean is_pvoid_key() const {return _internalFlags & pvoid_key;}
  os_boolean is_point_to_key() const {return _internalFlags & point_to_key;}
  os_boolean allow_dups() const {return _internalFlags & os_btree_allow_dups;}
  os_boolean is_char_array() const {return _internalFlags & char_array_key;}
  os_boolean is_char_nocopy_key() const {return _internalFlags & char_nocopy_key;}
  os_boolean is_tree_empty() const;
  os_boolean has_cluster() const {return _internalFlags & cluster_created;}
  os_boolean is_untransformed() const {return _internalFlags & untransformed;}
  os_boolean has_user_assign_fcn() const 
    {return  (_internalFlags &(var_char_key | user_assign_fcn));} 
  os_boolean is_soft_pointer_key() const
    {return _internalFlags & pvoid_key;}
  os_boolean is_remove_all_keys() const {return _internalFlags & remove_all_keys;}
  os_boolean has_duplicate_class_keys() const 
    {return _internalFlags & class_dup_key;}
  void set_has_cluster() {_internalFlags |= cluster_created;}
 
  void find_assign_function(_Assign_fcn& afn, os_boolean signal = 1);   
  virtual void assignKey(void * addr, void * key);
  const char * _compare_type() const {return _compareType;}
  // Only called from a debugger to print the key values of a node.
  void print_node( _Coll_btree_node * node);

protected:
  /* -------------------------------------------------------------------
   * index support needed for unordered os_Dictionary
   * ---------------------------------------------------------------- */

  _Indexes * index_info;
  
  virtual _Indexes*& indexes();
  virtual os_int32 has_indexes() const;

protected:
  // Data members
  os_soft_pointer<char>                _keyType;
  os_soft_pointer<char>                _compareType;
  os_soft_pointer<_Coll_btree_node>    _root;
  os_soft_pointer<_Coll_btree_node>    _presizeList;  
  os_unsigned_int32    _keySize;
  os_unsigned_int32    _arraySize;
  os_unsigned_int32    _card;
  os_unsigned_int32    _flags;
  os_unsigned_int32    _internalFlags;
  os_unsigned_int32    _maxKeys;
  char                 _os_pad_0[4];   /* 64-bit neutralization */

};


// os_btree cursor class
class _OS_COLL_IMPORT _os_btree_cursor : public os_dictionary_cursor {
  friend class os_btree;
public:

  // Construction/Destruction
  _os_btree_cursor(const os_btree&, os_unsigned_int32,
    os_dictionary_cursor::_set_position sp = FIND_FIRST);

  _os_btree_cursor(os_collection_restriction, const void*,
		 const os_btree&, os_unsigned_int32,
     os_dictionary_cursor::_set_position sp = FIND_FIRST);

  _os_btree_cursor(os_collection_restriction, const void*,
		 os_collection_restriction, const void*,
		 const os_btree&, os_unsigned_int32,
     os_dictionary_cursor::_set_position sp = FIND_FIRST);

  ~_os_btree_cursor();


  virtual void remember(_os_cursor_holder &);
  virtual void restore(_os_cursor_holder &);
 
  // Functions for setting up restriction
  virtual void restrict(os_int32 /* os_collection::restriction */ r, const void* k);
  
  virtual void restrict(os_int32 r_lo, const void* k_lo, 
                os_int32 r_hi, const void* k_hi);

  virtual void unrestrict(); 

  static os_typespec * get_os_typespec();

  // Flags accessors
  os_boolean is_restricted() const { return _flags & restricted_flag; }
  os_boolean is_two_sided() const { return _flags & two_sided_flag; }
  os_boolean is_btree_cursor() { return 1; }
  void set_iterate_off_range() {_flags |= iterate_off_range;}
  os_boolean is_iterate_off_range() {return(_flags & iterate_off_range);}
  void set_var_char_key() {_flags |= var_char_key;}
  os_boolean is_var_char_key() {return _flags & var_char_key;}


  // Set and get the current position (key level)
  void setCurrentPos(os_unsigned_int32 null, 
                     _Coll_btree_node * node, 
                     os_unsigned_int32 index);
   // Set and get the current position (key level)
  void getCurrentPos(os_unsigned_int32 & null, 
                     _Coll_btree_node *& node, 
                     os_unsigned_int32 & index);

  // Enums for flags
  os_unsigned_int32 _flags;
  enum { restricted_flag = 1, 
         two_sided_flag = 2, 
         iterate_off_range = 4,
         var_char_key = 8}; 

  // Pointer to the tree in question
  os_coll_ptr __tree;
  os_btree * get_tree() const {return (os_btree*)(void*)__tree;}
  void set_tree(const os_btree * tree) {__tree = (void*)tree;}


  /* one-sided */
  os_collection_restriction key_restriction;
  os_coll_ptr key;

  /* two-sided */
  os_collection_restriction lo_restriction;
  os_collection_restriction hi_restriction;
  os_coll_ptr lo;
  os_coll_ptr hi;
     
  // These fields actually point to the current position in the tree
  void_coll_ptr   _node;
  os_unsigned_int32    _index;
  os_coll_ptr          _overflow;
  os_cursor * get_overflow() const {return (os_cursor*)(void*)_overflow;}
  void set_overflow(os_cursor * curs) {_overflow = curs;}
  os_unsigned_int32    _null;
};

// This is a macro for decoding keys.  It will return the usable address
// of the key for comparison.  This is here to handle point to key vs
// emedded key btree
#define OS_BTREE_DECODE_KEY(t,k)  t->is_point_to_key() ? *((void**)k) : k

// This macro is for encoding keys for copy into the tree
#define OS_BTREE_ENCODE_KEY(t,k)  t->is_point_to_key() ? (void*)&k : k

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else // !defined(_OS_PSE_COLL)
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif // !defined(_OS_PSE_COLL)


#endif

