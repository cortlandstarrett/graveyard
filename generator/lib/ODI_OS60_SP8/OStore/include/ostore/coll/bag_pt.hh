/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


// bag_pt.hh
// Initial re-write for 6.0 4/15/1998
// This file contains the following classes:
//   os_Bag - Templated facade for os_bag.

#ifndef _COLL_BAG_PT
#define _COLL_BAG_PT

#if !defined(_OS_PSE_COLL)

#include <ostore/hdrstart.hh>

/* IBM's template implementation includes this header alone. */
#if !defined(_COLL_BAG)
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#endif

#else

#include <os_pse/psecoll/hdrstart.hh>

/* IBM's template implementation includes this header alone. */
#if !defined(_COLL_BAG)
#include <os_pse/ostore.hh>
#include <os_pse/coll.hh>
#endif
_OS_BEGIN_NAMESPACE(os_pse)

#endif

template <class E>
class os_Bag : public os_Collection<E>
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
  void insert_before(const void*, os_unsigned_int32) {}
  void insert_after(const void*, os_unsigned_int32) {}
  void* remove_at(os_unsigned_int32) {return 0;}     
  void* replace_at(const void*, os_unsigned_int32) {return 0;}
  void* retrieve(os_unsigned_int32) {return 0;}
  void* retrieve_first() {return 0;}
  void* retrieve_last() {return 0;}

public: /* unhide things that would be obscured by hidden overloadings */
  E retrieve(const os_cursor& c) const {return (E)os_collection::retrieve(c);}
  void remove_at(const os_cursor& c) {os_collection::remove_at(c);}
  void replace_at(const E v, const os_cursor& c) {os_collection::replace_at((void*)v,c);}

public:
  /* get the default behavior associated with this type */
  /* i.e. if you say set::create, this is the behavior you will get */
  static os_unsigned_int32 default_behavior() {return os_Bag<E>::allow_duplicates;};
  
  /* default type */
  static os_os_collection_type default_type() { return os_Bag<E>::OS_Bag; }

  os_Bag(os_unsigned_int32 sz = 0) : os_Collection<E>('B') {
    this->_coll = new (os_cluster::with(this),os_bag::get_os_typespec())os_bag(sz);
  }

  os_Bag(const os_Bag<E>&c) : os_Collection<E>('B') {
    this->_coll = new (os_cluster::with(this),os_bag::get_os_typespec())os_bag(c);
  }

  os_Bag(const os_Collection<E>&c) : os_Collection<E>('B') {
    this->_coll = new (os_cluster::with(this),os_bag::get_os_typespec())os_bag(c);
  }
 
  static os_Bag<E> &create(os_database* db, os_unsigned_int32 behavior = 0,
			   os_int32 expected_size = 0)
  {
    return *((os_Bag<E>*)(os_Bag<E>::generate_facade("os_Bag", db, expected_size)));
  }

  static os_Bag<E> &create(os_segment* seg, os_unsigned_int32 behavior = 0,
			   os_int32 expected_size = 0)
  {  
    return *((os_Bag<E>*)(os_Bag<E>::generate_facade("os_Bag", seg, expected_size)));
  }

  static os_Bag<E> &create(os_cluster_with & clust, os_unsigned_int32 behavior = 0,
			   os_int32 expected_size = 0)
  { 
    return *((os_Bag<E>*)(os_Bag<E>::generate_facade("os_Bag", clust, expected_size)));
  }

  static os_Bag<E> &create(const void *proximity, 
                           os_unsigned_int32 behavior = 0,
			   os_int32 expected_size = 0)
  { 
    return *((os_Bag<E>*)(os_Bag<E>::generate_facade("os_Bag", (void*)proximity, expected_size)));
  }

  static void destroy(os_Bag<E>& c) { os_collection::destroy(c); }

  os_int32 ordered_equal(const os_Bag<E> &c) const
    { return os_collection::ordered_equal(c) ; }

public:
    // Used by dump/load
   void init_load(os_unsigned_int32 b = 0, os_int32 sz = 0)
    {
      this->_coll = new(os_cluster::with(this), os_bag::get_os_typespec()) os_bag(sz);
    }

public:
  /* assignment operators */
  os_Bag<E>& operator =(const os_Bag<E>& s)
    { return (os_Bag<E>&)os_collection::operator =(s);}
  os_Bag<E>& operator =(const os_Collection<E>& s)
    { return (os_Bag<E>&)os_collection::operator =(s);}
  os_Bag<E>& operator =(const E e)
    { return (os_Bag<E>&)os_collection::operator =((void*)e);}
  os_Bag<E>& operator |=(const os_Collection<E>& s)
    { return (os_Bag<E>&)os_collection::operator |=(s) ; }
  os_Bag<E>& operator |=(const E e)
    { return (os_Bag<E>&)os_collection::operator |=((void*)e);}
  os_Bag<E>& operator &=(const os_Collection<E>& s)
    { return (os_Bag<E>&)os_collection::operator &=(s) ; }
  os_Bag<E>& operator &=(const E e)
    { return (os_Bag<E>&)os_collection::operator &=((void*)e);}
  os_Bag<E>& operator -=(const os_Collection<E>& s)
    { return (os_Bag<E>&)os_collection::operator -=(s) ; }
  os_Bag<E>& operator -=(const E e)
    { return (os_Bag<E>&)os_collection::operator -=((void*)e);}

public:

#if !defined(_OS_PSE_COLL)
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() {return os_ts<os_Bag<E > >::get(); }
#endif

#if defined(__xlC__) || defined(__os_cafe) || defined(__EDG) || defined(__os_hpcfront) || defined(__ECPP__) || defined(__os_alpha_osf) || defined(__os_linux)
  ~os_Bag();
#endif
};
 
#if defined(__xlC__) || defined(__EDG) || defined(__ECPP__) || defined(__os_alpha_osf) || defined(__os_linux)
#if defined(__xlC__) && defined(__TEMPINC__)
#pragma implementation ("bag_pt.c") /* IBM convention */
#else

#if !defined(_OS_PSE_COLL)
#include <ostore/coll/bag_pt.c>
#else
#include <os_pse/coll/bag_pt.c>
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
