/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


// set_pt.hh
// Initial re-write for 6.0 4/15/1998
// This file contains the following classes:
//   os_Set - Templated facade for os_set.

#ifndef _COLL_SET_PT
#define _COLL_SET_PT

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>

/* IBM's template implementation includes this header alone. */
#if !defined(_COLL_SET)
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#endif

#else

#include <os_pse/psecoll/hdrstart.hh>

/* IBM's template implementation includes this header alone. */
#if !defined(_COLL_SET)
#include <os_pse/ostore.hh>
#include <os_pse/coll.hh>
#endif
_OS_BEGIN_NAMESPACE(os_pse)

#endif

template <class E>
class os_Set : public os_Collection<E>
{
private:
  /* hide access to protocol that is not supported */
  os_int32 ordered_equal(const os_list &) const {return 0;}
  void insert_first(const void* ) {}
  void insert_last(const void* ) {}
  os_int32 remove_first(os_void_const_p &) {return 0;}
  os_int32 remove_last(os_void_const_p &) {return 0;}
  void* remove_first() {return 0;}
  void* remove_last() {return 0;}
  void insert_after(const void* , const os_cursor& ) {}
  void insert_before(const void* , const os_cursor& ) {}
  void insert_before(const void*, os_unsigned_int32){}
  void insert_after(const void*, os_unsigned_int32){}
  void* remove_at(os_unsigned_int32){return 0;}     
  void* replace_at(const void*, os_unsigned_int32){return 0;}
  void* retrieve(os_unsigned_int32){return 0;}
  void* retrieve_first(){return 0;}
  void* retrieve_last(){return 0;} 

public: /* unhide things that would be obscured by hidden overloadings */
  E retrieve(const os_cursor& c) const {return (E)os_collection::retrieve(c);};
  void remove_at(const os_cursor& c) {os_collection::remove_at(c);}
  void replace_at(const E v, const os_cursor& c) {os_collection::replace_at((void*)v,c);} 

public:
  /* get the default behavior associated with this type */
  static os_unsigned_int32 default_behavior() {return 0;};
  
  /* default type */
  static os_os_collection_type default_type() { return os_collection::OS_Set; }

public:

  os_Set(os_unsigned_int32 sz = 0) : os_Collection<E>('S') {
    this->_coll = new (os_cluster::with(this),os_set::get_os_typespec())os_set(sz);
  }

  os_Set(const os_Set<E>&c) : os_Collection<E>('S') {
    this->_coll = new (os_cluster::with(this),os_set::get_os_typespec())os_set(c);
  }

  os_Set(const os_Collection<E>&c) : os_Collection<E>('S') {
    this->_coll = new (os_cluster::with(this),os_set::get_os_typespec())os_set(c);
  }

  static os_Set<E> &create(os_database* db, os_unsigned_int32 behavior = 0,
                           os_int32 expected_size = 0) 
  { 
    return *((os_Set<E>*)(os_Set<E>::generate_facade("os_Set", db, expected_size)));
  }

  static os_Set<E> &create(os_segment* seg, os_unsigned_int32 behavior = 0,
			   os_int32 expected_size = 0)
  { 
    return *((os_Set<E>*)(os_Set<E>::generate_facade("os_Set", seg, expected_size)));
  }

  static os_Set<E> &create(os_cluster_with & clust, os_unsigned_int32 behavior = 0,
			   os_int32 expected_size = 0)
  { 
    return *((os_Set<E>*)(os_Set<E>::generate_facade("os_Set", clust, expected_size)));
  }

  static os_Set<E> &create(const void *proximity,
                           os_unsigned_int32 behavior = 0,
			   os_int32 expected_size = 0)
  { 
    return *((os_Set<E>*)(os_Set<E>::generate_facade("os_Set", (void*)proximity, 
                                         expected_size)));
  }

  static void destroy(os_Set<E>& c) { os_collection::destroy(c); }

public:
    // Used by dump/load
   void init_load(os_unsigned_int32 b = 0, os_int32 sz = 0)
    {
      this->_coll = new(os_cluster::with(this), os_set::get_os_typespec()) os_set(sz);
    }

public:
  /* assignment operators */
  os_Set<E>& operator =(const os_Set<E>& s)
    { return (os_Set<E>&)os_collection::operator =(s);}
  os_Set<E>& operator =(const os_Collection<E>& s)
    { return (os_Set<E>&)os_collection::operator =(s);}
  os_Set<E>& operator =(const E e)
    { return (os_Set<E>&)os_collection::operator =((void*)e);}
  os_Set<E>& operator |=(const os_Collection<E>& s)
    { return (os_Set<E>&)os_collection::operator |=(s) ; }
  os_Set<E>& operator |=(const E e)
    { return (os_Set<E>&)os_collection::operator |=((void*)e);}
  os_Set<E>& operator &=(const os_Collection<E>& s)
    { return (os_Set<E>&)os_collection::operator &=(s) ; }
  os_Set<E>& operator &=(const E e)
    { return (os_Set<E>&)os_collection::operator &=((void*)e);}
  os_Set<E>& operator -=(const os_Collection<E>& s)
    { return (os_Set<E>&)os_collection::operator -=(s) ; }
  os_Set<E>& operator -=(const E e)
    { return (os_Set<E>&)os_collection::operator -=((void*)e);}

public:
 
#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() {return os_ts<os_Set<E > >::get(); }
#endif

#if defined(__xlC__) || defined(__os_cafe) || defined(__EDG) || defined(__os_hpcfront) || defined(__ECPP__) || defined(__os_alpha_osf) || defined(__os_linux)
     ~os_Set();
#endif
};
 
// Type safe facade for os_ixonly.
template <class E>
class os_Ixonly : public os_Collection<E>
{

public:
  os_Ixonly(os_boolean duplicates = 0, os_boolean maintain_cardinality = 0) 
    : os_Collection<E>('I') 
  {
#ifndef _OS_PSE_COLL
    os_typespec spec("os_ixonly");
    this->_coll = new (os_cluster::with(this), &spec)
      os_ixonly(duplicates, maintain_cardinality);
#else
    this->_coll = new (os_cluster::with(this), os_ixonly::get_os_typespec() )
      os_ixonly(duplicates, maintain_cardinality);
#endif
  }


#if defined(__EDG) || defined(__xlC__)
  virtual ~os_Ixonly();
#else
  virtual ~os_Ixonly() {}
#endif

#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec(){return os_ts<os_Ixonly<E > >::get(); }
#endif

};

#if defined(__xlC__) || defined(__EDG) || defined(__ECPP__) || defined(__os_alpha_osf) || defined(__os_linux)
#if defined(__xlC__) && defined(__TEMPINC__)
#pragma implementation ("set_pt.c") /* IBM convention */
#else

#if !defined(_OS_PSE_COLL)
#include <ostore/coll/set_pt.c>
#else
#include <os_pse/coll/set_pt.c>
#endif

#endif
#endif


#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
