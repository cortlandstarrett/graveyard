/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


// array_pt.hh
// Initial re-write for 6.0 4/15/1998
// This file contains the following classes:
//   os_Array - Templated facade for os_array.

#ifndef _COLL_ARRAY_PT
#define _COLL_ARRAY_PT

#if !defined(_OS_PSE_COLL)

#include <ostore/hdrstart.hh>

/* IBM's template implementation includes this header alone. */
#if !defined(_COLL_ARRAY)
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#endif

#else

#include <os_pse/psecoll/hdrstart.hh>

/* IBM's template implementation includes this header alone. */
#if !defined(_COLL_ARRAY)
#include <os_pse/ostore.hh>
#include <os_pse/coll.hh>
#endif

_OS_BEGIN_NAMESPACE(os_pse)
#endif

template <class E>
class os_Array : public os_Collection<E>
{
public:
  /* get the default behavior associated with this type */
  /* i.e. if you say array::create, this is the behavior you will get */
  static os_unsigned_int32 default_behavior() 
    {return os_Array<E>::maintain_order | os_Array<E>::allow_duplicates | 
       os_Array<E>::allow_nulls | os_Array<E>::be_an_array;};

  static os_unsigned_int32 required_behavior() 
    {return os_Array<E>::maintain_order | os_Array<E>::allow_nulls | 
       os_Array<E>::be_an_array;};

  /* default type */
  static os_os_collection_type default_type() { return os_Array<E>::OS_Array; }


  os_Array(os_unsigned_int32 sz = 0, os_unsigned_int32 card = 0, 
           E* fill_value = (E*)0) 
       : os_Collection<E>('A') {
    this->_coll = new (os_cluster::with(this),os_array::get_os_typespec())
                 os_array(sz, card, (void*)fill_value);
  }

  os_Array(const os_Array<E>&c) : os_Collection<E>('A') {
    this->_coll = new (os_cluster::with(this),os_array::get_os_typespec())os_array(c);
  }

  os_Array(const os_Collection<E>&c) : os_Collection<E>('A') {
    this->_coll = new (os_cluster::with(this),os_array::get_os_typespec())os_array(c);
  }

 
  static os_Array<E> &create(os_database* db, os_unsigned_int32 behavior = 0,
			    os_int32 expected_size = 0,
			    os_int32 card = 0, void* fill_value = 0)
  { 
     return *(os_Array<E>*)(os_Array<E>::generate_facade("os_Array", db, expected_size,
                                           behavior, card, fill_value));
  }

  static os_Array<E> &create(os_segment* seg, os_unsigned_int32 behavior = 0,
			    os_int32 expected_size = 0,
			    os_int32 card = 0, void* fill_value = 0)
  { 
     return *(os_Array<E>*)(os_Array<E>::generate_facade("os_Array", seg, expected_size,
                                           behavior, card, fill_value));
  }

  static os_Array<E> &create(os_cluster_with & clust, 
                             os_unsigned_int32 behavior = 0,
			     os_int32 expected_size = 0,
			     os_int32 card = 0, void* fill_value = 0)
  { 
     return *(os_Array<E>*)(os_Array<E>::generate_facade("os_Array", clust, expected_size,
                                           behavior, card, fill_value));
  }

  static os_Array<E> &create(const void *proximity, 
                            os_unsigned_int32 behavior = 0,
			    os_int32 expected_size = 0,
			    os_int32 card = 0, void* fill_value = 0)
  { 
     return *(os_Array<E>*)(os_Array<E>::generate_facade("os_Array", (void*)proximity, 
                                  behavior, expected_size, card, fill_value));
  }

  static void destroy(os_Array<E>& c) { os_collection::destroy(c); }

public:
    // Used by dump/load
   void init_load(os_unsigned_int32 b = 0, os_int32 sz = 0)
    {
      this->_coll = new(os_cluster::with(this), os_array::get_os_typespec()) 
         os_array(sz);
    }

public:
  /* assignment operators */
  os_Array<E>& operator =(const os_Array<E>& s)
    { return (os_Array<E>&)os_collection::operator =(s);}
  os_Array<E>& operator =(const os_Collection<E>& s)
    { return (os_Array<E>&)os_collection::operator =(s);}
  os_Array<E>& operator =(const E e)
    { return (os_Array<E>&)os_collection::operator =((void*)e);}

  os_Array<E>& operator |=(const os_Collection<E>& s)
    { return (os_Array<E>&)os_collection::operator |=(s) ; }
  os_Array<E>& operator |=(const E e)
    { return (os_Array<E>&)os_collection::operator |=((void*)e);}
  os_Array<E>& operator &=(const os_Collection<E>& s)
    { return (os_Array<E>&)os_collection::operator &=(s) ; }
  os_Array<E>& operator &=(const E e)
    { return (os_Array<E>&)os_collection::operator &=((void*)e);}
  os_Array<E>& operator -=(const os_Collection<E>& s)
    { return (os_Array<E>&)os_collection::operator -=(s) ; }
  os_Array<E>& operator -=(const E e)
    { return (os_Array<E>&)os_collection::operator -=((void*)e);}

public:
  // ***** PBF  This needs to be fixed before release.  set_cardinality() should be a top
  // down virtual but only is supported by os_array
  void set_cardinality(os_unsigned_int32 new_card, void* fill_value) {
     ((os_array*)this->_coll)->set_cardinality(new_card, fill_value);
  }
 
  
#if !defined(_OS_PSE_COLL)
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() {return os_ts<os_Array<E > >::get(); }
#endif

#if defined(__xlC__) || defined(__os_cafe) || defined(__EDG) || defined(__os_hpcfront) || defined(__ECPP__) || defined(__os_alpha_osf) || defined(__os_linux)
  ~os_Array();
#endif
};
 
#if defined(__xlC__) || defined(__EDG) || defined(__ECPP__) || defined(__os_alpha_osf) || defined(__os_linux)
#if defined(__xlC__) && defined(__TEMPINC__)
#pragma implementation ("array_pt.c") /* IBM convention */
#else

#if !defined(_OS_PSE_COLL)
#include <ostore/coll/array_pt.c>
#else
#include <os_pse/coll/array_pt.c>
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



