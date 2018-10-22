/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_COLL_os_dictionary_h
#define _OS_COLL_os_dictionary_h
#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#include <ostore/hdrsys.hh>
#include <string.h>
#include <ostore/hdrend.hh>
#include <ostore/ostore.hh>
#include <ostore/coll/lw.hh>
#include <ostore/coll/dkey.hh>
#include <ostore/coll/rh_pt.hh>
#include <ostore/coll/collptr.hh>
#include <ostore/nclient/softptr.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include <string.h>
#include <os_pse/ostore.hh>
#include <os_pse/coll/lw.hh>
#include <os_pse/coll/dkey.hh>
#include <os_pse/coll/rh_pt.hh>
#include <os_pse/coll/collptr.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif



/* ---------------------------------------------------------------------
 * os_Dictionary
 */

template<class KT, class VT >
class os_Dictionary : public os_outofline_dictionary {
public:

  os_Dictionary(os_unsigned_int32 expected_cardinality = 10,
	              os_unsigned_int32 behavior = 0 );

  os_Dictionary(os_Dictionary<KT,VT > &d);

  ~os_Dictionary() {}

  static os_Dictionary<KT,VT >&
    create(os_database* db, os_unsigned_int32 expected_cardinality = 10,
	   os_unsigned_int32 behavior = 0)
  {
    return *new(db, os_Dictionary<KT,VT >::get_os_typespec())
      os_Dictionary<KT,VT>(expected_cardinality, behavior);
  }

  static os_Dictionary<KT,VT >&
    create(os_segment* seg, os_unsigned_int32 expected_cardinality = 10,
	   os_unsigned_int32 behavior = 0)
  {
    return *new(seg, os_Dictionary<KT,VT >::get_os_typespec())
      os_Dictionary<KT,VT >(expected_cardinality, behavior);
  }

  static os_Dictionary<KT,VT >&
    create(os_cluster_with & cls, os_unsigned_int32 expected_cardinality = 10,
	   os_unsigned_int32 behavior = 0)
  {
    return *new(cls, os_Dictionary<KT,VT >::get_os_typespec())
      os_Dictionary<KT,VT >(expected_cardinality, behavior);
  }

  static void destroy(os_Dictionary<KT,VT>& c) { delete &c; }

  virtual void allocate_coll(os_unsigned_int32 expected_cardinality,
	                     os_unsigned_int32 behavior);

  void init_load(os_unsigned_int32 expected_cardinality,
	         os_unsigned_int32 behavior)
  { _init_load(expected_cardinality, behavior); }
 

  void insert(const KT* key, const VT value)
    { os_dictionary::insert(key, (const void *)value); }
  void insert(const KT& key, const VT value) 
    {insert((const KT*)&key, value);}

  void remove(const KT* key, const VT value)
    { os_dictionary::remove(key,value); }
  void remove(const KT& key, const VT value)
    {remove((const KT*)&key, value);}

  void remove(const VT value) {_remove(value);}

  VT remove_value(const KT* key, os_unsigned_int32 num = 1)
    { return (VT) os_dictionary::remove_value(key, num); }
  VT remove_value(const KT& key, os_unsigned_int32 num = 1)
    { return remove_value((const KT*)&key, num); }

  os_boolean contains(const KT* key, const VT value) const
    { return os_dictionary::contains(key,value); }
  os_boolean contains(const KT& key, const VT value) const
    { return contains((const KT*)&key, value); }
	
  os_unsigned_int32 count_values(const KT* key) const
  { return os_dictionary::count_values(key); }
  os_unsigned_int32 count_values(const KT& key) const
  { return count_values((const KT*)&key); }

  VT pick(os_coll_range& r) const
    { return (VT)os_dictionary::pick(r); }
  VT pick(KT const* key) const
    { return (VT)os_dictionary::pick (key); }
  VT pick(KT const& key) const
    { return pick (&key); }
  VT pick() const { return (VT)os_collection::pick(); }

  VT retrieve(const os_cursor& c) { return (VT)os_collection::retrieve(c); }
  typedef _OS_TYPENAME os_dk_ptr_type<KT>::TYPE dict_ptr_type;
  const dict_ptr_type retrieve_key(const os_cursor& c) const
    { return (const dict_ptr_type)os_dictionary::retrieve_key(c); }

  os_Collection<VT>& query(char *element_type,
		       char *query_string,
		       os_database *schema_db = 0,
		       char* file_name = 0,
		       os_unsigned_int32 line = 0,
		       os_boolean dups = query_dont_preserve_duplicates) const
    {
      return (os_Collection<VT>&)os_collection::query(
			element_type, query_string,
			schema_db, file_name, line, dups);
    }

  os_Collection<VT>& query(char *element_type,
                       char *query_string,
                       os_str_conv::encode_type string_literal_char_encoding,
                       os_database *schema_db = 0,
                       char* file_name = 0,
                       os_unsigned_int32 line = 0,
                       os_boolean dups = query_dont_preserve_duplicates) const
    {
      return (os_Collection<VT>&)os_collection::query (
			element_type, query_string,
			string_literal_char_encoding, schema_db,
			file_name, line, dups);
    }

  os_Collection<VT>& query(const os_bound_query& bq,
		       os_boolean dups = query_dont_preserve_duplicates) const 
    {
      return (os_Collection<VT>&)os_collection::query(bq, dups);
    }
   
  VT query_pick(char *element_type, char *query_string,
		os_database *schema_db = 0, char *file_name = 0,
		os_unsigned_int32 line = 0)
    { 
      return (VT) os_collection::query_pick(element_type,query_string,
					    schema_db, file_name, line);
    }
  VT query_pick(const os_bound_query& bq) const
    { return (VT) os_collection::query_pick(bq); }

  virtual const char* _key_type() const;


protected:

  virtual void find_functions(_Rank_fcn&, _Hash_fcn&) const;

public:

#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() { 
    return os_ts<os_Dictionary<KT, VT > >::get(); }
#endif
}; /* class os_Dictionary */

/* ---------------------------------------------------------------------
 * _Dict_pt_slot
 */

template<class KEYTYPE > class _Dict_pt_slot {

private:
  os_coll_ptr _value;
  
public:
  os_dk_wrapper<KEYTYPE> key;

  _Dict_pt_slot() {}
  ~_Dict_pt_slot() {}

  void* value() { return (void*)_value; }
  os_coll_ptr& get_value() 
     { return (( os_coll_ptr&)_value); }
  void set_value(void* v) {_value = v;}
  void set_oflo(os_collection * v) {_value = (void*)v;}
  void insert(void* v, KEYTYPE const* k, os_unsigned_int32 h) 
    { _value = v; key = *k; key.set_hashval(h); }
  void* get_key() {return key.key();}
  void assign(_Dict_pt_slot<KEYTYPE >* s) 
  { 
    _value = s->get_value(); 
    key.assign(&s->key);
  }
  void make_deleted(const void* delval = 0) 
  {
    _value = (delval ? (void*)delval : (void*)this);
    key.die();
  }
   
  _RH_slot_status status(
    const void* delval, os_boolean no_key_chk, 
    const void * k = 0,  _Rank_fcn rfn = 0,
    os_unsigned_int32 h = 0) const 
    {
      if (!_value)
         return _RH_EMPTY_SLOT;
      else if (_value == delval)
         return _RH_SLOT_DELETED;
      else if (no_key_chk)
         return _RH_SLOT_OCCUPIED;
      else if (key.eq(rfn,(KEYTYPE const*)k))
         return _RH_KEY_MATCH;
      else 
         return _RH_SLOT_OCCUPIED;
   }
 
  os_collection* oflo_list()  
    { return (os_collection*)(void*)_value; }
 
#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() { 
    return os_ts<_Dict_pt_slot<KEYTYPE > >::get(); }
#endif
}; /* class _Dict_pt_slot */


/* ---------------------------------------------------------------------
 * _Dict_pt_slot<char*>
 */

#ifdef __os_sol2c5
template <> 
#endif
class _Dict_pt_slot<char*> {

private:
  os_coll_ptr _value;
public:
  os_dk_wrapper<char*> key;

  _Dict_pt_slot() {}
  ~_Dict_pt_slot() {}

  void* value() { return (void*)_value; }
  os_coll_ptr& get_value() 
      { return (( os_coll_ptr&)_value); }
  void set_value(void* v) {_value = v;}
  void set_oflo(os_collection * v) {_value = (void*)v;}
  void insert(void* v, os_char_p const* k, os_unsigned_int32 h) 
    { _value = v; key.set_key((char*)*k); key.set_hashval(h); }
  void* get_key() {return key.key();}
  void assign(_Dict_pt_slot<char*>* s) 
  { 
    _value = s->get_value(); 
    key.assign(&s->key);
  }
  void make_deleted(const void* delval = 0) 
  {
    _value = (delval ? (void*)delval : (void*)this);
    key.die();
  }

  _RH_slot_status status(
     const void* delval, os_boolean no_key_chk, 
     const void* k = 0, _Rank_fcn rfn = 0,
     os_unsigned_int32 h = 0) const     
   {
      if (!_value)
         return _RH_EMPTY_SLOT;
      else if (_value == delval)
         return _RH_SLOT_DELETED;
      else if (no_key_chk)
         return _RH_SLOT_OCCUPIED;
      else if (key.eq(rfn,(const char*)k))
         return _RH_KEY_MATCH;
      else 
         return _RH_SLOT_OCCUPIED;
   }

  os_collection* oflo_list()
    { return (os_collection*)(void*)_value; }
    
#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() { 
    return os_ts<_Dict_pt_slot<char*> >::get(); }
#endif

}; /* class _Dict_pt_slot<char*> */

/* ---------------------------------------------------------------------
 * _Dict_pt_slot<const char*>
 */

#ifdef __os_sol2c5
template <> 
#endif
class _Dict_pt_slot<const char*> {

private:
  os_coll_ptr _value;
public:
  os_dk_wrapper<const char*> key;

  _Dict_pt_slot() {}
  ~_Dict_pt_slot() {}

  void* value() { return (void*)_value; }
  os_coll_ptr& get_value() 
      { return (( os_coll_ptr&)_value); }
  void set_value(void* v) {_value = v;}
  void set_oflo(os_collection * v) {_value = (void*)v;}
  void insert(void* v, const char * const * k, os_unsigned_int32 h) 
    { _value = v; key.set_key((char*)*k); key.set_hashval(h); }
  void* get_key() {return key.key();}
  void assign(_Dict_pt_slot<const char*>* s) 
  { 
    _value = s->get_value(); 
    key.assign(&s->key);
  }
  void make_deleted(const void* delval = 0) 
  {
    _value = (delval ? (void*)delval : (void*)this);
    key.die();
  }

  _RH_slot_status status(
     const void* delval, os_boolean no_key_chk, 
     const void* k = 0, _Rank_fcn rfn = 0,
     os_unsigned_int32 h = 0) const     
   {
      if (!_value)
         return _RH_EMPTY_SLOT;
      else if (_value == delval)
         return _RH_SLOT_DELETED;
      else if (no_key_chk)
         return _RH_SLOT_OCCUPIED;
      else if (key.eq(rfn,(const char *)k))
         return _RH_KEY_MATCH;
      else 
         return _RH_SLOT_OCCUPIED;
   }

  os_collection* oflo_list()
    { return (os_collection*)(void*)_value; }
    
#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() { 
    return os_ts<_Dict_pt_slot<const char*> >::get(); }
#endif

}; /* class _Dict_pt_slot<const char*> */

/* ---------------------------------------------------------------------
 * _Dict_pt_slot<void*>
 */

#ifdef __os_sol2c5
template <> 
#endif
class _Dict_pt_slot<void*> {

private:
  os_coll_ptr _value;
  
public:
  os_dk_wrapper<void*> key;

  _Dict_pt_slot() {}
  ~_Dict_pt_slot() {}

  void* value() { return (void*)_value; }
  os_coll_ptr& get_value()
     { return (( os_coll_ptr&)_value); }
  void set_value(void* v) {_value = v;}
  void set_oflo(os_collection * v) {_value = (void*)v;}
  void insert(void* v, os_void_p const* k, os_unsigned_int32 h) 
  { 
    _value = (void*)v;
    key = (const void *)*k; 
    key.set_hashval(h); 
  }
  void* get_key() {return key.key();}
  void assign(_Dict_pt_slot<void*>* s) 
  { 
    _value = s->get_value(); 
    key.assign(&s->key);
  }
  void make_deleted(const void* delval = 0) 
  {
    _value = (delval ? (void*)delval : (void*)this);
    key.die();
  }
  _RH_slot_status status(
     const void* delval, os_boolean no_key_chk, 
     const void* k = 0, _Rank_fcn rfn = 0,
     os_unsigned_int32 h = 0) const     
  {
      if (!_value)
         return _RH_EMPTY_SLOT;
      else if (_value == delval)
         return _RH_SLOT_DELETED;
      else if (no_key_chk)
         return _RH_SLOT_OCCUPIED;
      else if (key.eq(rfn,(os_void_p const*)k))
         return _RH_KEY_MATCH;
      else 
         return _RH_SLOT_OCCUPIED;
   }
 
  os_collection* oflo_list()
    { return (os_collection*)(void*)_value; }
    
#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() { 
    return os_ts<_Dict_pt_slot<void*> >::get(); }
#endif

}; /* class _Dict_pt_slot<void*> */

/* ---------------------------------------------------------------------
 * _Dict_pt_slot<double>
 */

#ifdef __os_sol2c5
template <> 
#endif
class _Dict_pt_slot<double> {

private:
  os_coll_ptr _value;
  char _os_pad_0[4];	/* 64-bit neutralization */
  
public:
  os_dk_wrapper<double> key;

  _Dict_pt_slot() {}
  ~_Dict_pt_slot() {}

  void* value() { return (void*)_value; }
  os_coll_ptr& get_value() 
     { return (( os_coll_ptr&)_value); }
  void set_value(void* v) {_value = v;}
  void set_oflo(os_collection * v) {_value = (void*)v;}
  void insert(void* v, double const* k, os_unsigned_int32 h) 
    { _value = v; key = (double)*k; key.set_hashval(h); }
  void* get_key() {return key.key();}
  void assign(_Dict_pt_slot<double >* s) 
  { 
    _value = s->get_value(); 
    key.assign(&s->key);
  }
  void make_deleted(const void* delval = 0) 
  {
    _value = (delval ? (void*)delval : (void*)this);
    key.die();
  }
   
  _RH_slot_status status(
    const void* delval, os_boolean no_key_chk, 
    const void * k = 0,  _Rank_fcn rfn = 0,
    os_unsigned_int32 h = 0) const 
    {
      if (!_value)
         return _RH_EMPTY_SLOT;
      else if (_value == delval)
         return _RH_SLOT_DELETED;
      else if (no_key_chk)
         return _RH_SLOT_OCCUPIED;
      else if (key.eq(rfn,(double const*)k))
         return _RH_KEY_MATCH;
      else 
         return _RH_SLOT_OCCUPIED;
   }
 
  os_collection* oflo_list()  
    { return (os_collection*)(void*)_value; }
 
#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() { 
    return os_ts<_Dict_pt_slot<double > >::get(); }
#endif
}; /* class _Dict_pt_slot<double> */


/* ---------------------------------------------------------------------
 * Macro definitions
 * ------------------------------------------------------------------ */

#ifndef _OS_PSE_COLL

#define OS_MARK_DICTIONARY(kt,vt) \
OS_MARK_SCHEMA_TYPESPEC((os_Dictionary<kt,vt >)) \
OS_MARK_SCHEMA_TYPESPEC((_Dict_pt_slot<kt >)) \
OS_MARK_SCHEMA_TYPESPEC((_Rhash_pt<kt >))

#endif 

/* If os_Dictionary<K,V> isn't marked in the schema, it's get_os_typespec()
   function will be undefined.  This macro, used at file scope in a source file
   defines a dummy get_os_typespec() function.
*/

/* Since these files will be included for PSE the second time when using both 
   OStore and PSE we want to redefine these macros.
*/
#ifdef OS_TRANSIENT_DICTIONARY
#undef OS_TRANSIENT_DICTIONARY
#endif
#ifdef OS_TRANSIENT_DICTIONARY_NOKEY
#undef OS_TRANSIENT_DICTIONARY_NOKEY
#endif

#define OS_TRANSIENT_DICTIONARY(kt,vt)\
_PSE_NS_ os_typespec* _PSE_NS_ os_Dictionary<kt,vt >::get_os_typespec()\
{ return (_PSE_NS_ os_typespec*)0; }\
_PSE_NS_ os_typespec* _PSE_NS_ _Rhash_pt<kt >::get_os_typespec() \
{ return (_PSE_NS_ os_typespec*)0; }\
_PSE_NS_ os_typespec* _PSE_NS_ _Dict_pt_slot<kt >::get_os_typespec()\
{ return (_PSE_NS_ os_typespec*)0; }

#define OS_TRANSIENT_DICTIONARY_NOKEY(kt,vt)\
_PSE_NS_ os_typespec* _PSE_NS_ os_Dictionary<kt,vt >::get_os_typespec()\
{ return (_PSE_NS_ os_typespec*)0;}

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif /* _OS_COLL_os_dictionary_h */

