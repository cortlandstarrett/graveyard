/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


// list_pt.hh
// Initial re-write for 6.0 4/15/1998
// This file contains the following classes:
//   os_List -  Templated facade for os_list.


#ifndef _COLL_LIST_PT
#define _COLL_LIST_PT

#if !defined(_OS_PSE_COLL)

#include <ostore/hdrstart.hh>

/* IBM's template implementation includes this header alone. */
#if !defined(_COLL_LIST)
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#endif

#else

#include <os_pse/psecoll/hdrstart.hh>

/* IBM's template implementation includes this header alone. */
#if !defined(_COLL_LIST)
#include <os_pse/ostore.hh>
#include <os_pse/coll.hh>
#endif
_OS_BEGIN_NAMESPACE(os_pse)

#endif

template <class E>
class os_List : public os_Collection<E>
{
public:
  /* get the default behavior associated with this type */
  /* i.e. if you say list::create, this is the behavior you will get */
  static os_unsigned_int32 default_behavior()
    { return os_List<E>::maintain_order | os_List<E>::allow_duplicates; };

  static os_unsigned_int32 required_behavior()
    { return os_List<E>::maintain_order; };
  
  /* default type */
  static os_os_collection_type default_type() { return os_List<E>::OS_List; }
  
  os_List(os_unsigned_int32 sz = 0, os_unsigned_int32 behavior = 0) 
       : os_Collection<E>('L') {
    this->_coll = new (os_cluster::with(this),os_list::get_os_typespec())
      os_list(sz, behavior);
  }

  os_List(const os_List<E>&c) : os_Collection<E>('L') {
    this->_coll = new (os_cluster::with(this),os_list::get_os_typespec())os_list(c);
  }

  os_List(const os_Collection<E>&c) : os_Collection<E>('L') {
    this->_coll = new (os_cluster::with(this),os_list::get_os_typespec())os_list(c);
  }

 
  // create functions are provided for backward compatibility
  static os_List<E> &create(os_database* db, os_unsigned_int32 behavior = 0,
			    os_int32 expected_size = 0)
  {			 
    return *((os_List<E>*)(os_List<E>::generate_facade("os_List", db, 
                                          expected_size, behavior)));
  }

  static os_List<E> &create(os_segment* seg, os_unsigned_int32 behavior = 0,
			    os_int32 expected_size = 0)
  {  
    return *((os_List<E>*)(os_List<E>::generate_facade("os_List", seg, 
                                          expected_size, behavior)));
  }

  static os_List<E> &create(os_cluster_with & clust, os_unsigned_int32 behavior = 0,
			    os_int32 expected_size = 0)
  { 
    return *((os_List<E>*)(os_List<E>::generate_facade("os_List", clust, 
                                          expected_size, behavior))); 
  }

  static os_List<E> &create(const void *proximity, 
                            os_unsigned_int32 behavior = 0,
			    os_int32 expected_size = 0)
  { 
    return *((os_List<E>*)(os_List<E>::generate_facade("os_List", (void*)proximity, 
                                          expected_size, behavior)));
  }

  static void destroy(os_List<E>& c) { os_collection::destroy(c); }

  os_int32 ordered_equal(const os_List<E> &c) const
    { return os_collection::ordered_equal(c) ; }

public:
    // Used by dump/load
   void init_load(os_unsigned_int32 b = 0, os_int32 sz = 0)
    {
      this->_coll = new(os_cluster::with(this), os_list::get_os_typespec()) 
	os_list(sz, b);
    }

public:

  /* assignment operators */
  os_List<E>& operator =(const os_List<E>& s)
    { return (os_List<E>&)os_collection::operator =(s);}
  os_List<E>& operator =(const os_Collection<E>& s)
    { return (os_List<E>&)os_collection::operator =(s);}
  os_List<E>& operator =(const E e)
    { return (os_List<E>&)os_collection::operator =((void*)e);}
  os_List<E>& operator |=(const os_Collection<E>& s)
    { return (os_List<E>&)os_collection::operator |=(s) ; }
  os_List<E>& operator |=(const E e)
    { return (os_List<E>&)os_collection::operator |=((void*)e);}
  os_List<E>& operator &=(const os_Collection<E>& s)
    { return (os_List<E>&)os_collection::operator &=(s) ; }
  os_List<E>& operator &=(const E e)
    { return (os_List<E>&)os_collection::operator &=((void*)e);}
  os_List<E>& operator -=(const os_Collection<E>& s)
    { return (os_List<E>&)os_collection::operator -=(s) ; }
  os_List<E>& operator -=(const E e)
    { return (os_List<E>&)os_collection::operator -=((void*)e);}

public:

#if !defined(_OS_PSE_COLL)
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() {return os_ts<os_List<E > >::get(); }
#endif

public:
#if defined(__xlC__) || defined(__os_cafe) || defined(__EDG) || defined(__os_hpcfront) || defined(__ECPP__) || defined(__os_alpha_osf) || defined(__os_linux)
  ~os_List();
#endif
};
 
#if defined(__xlC__) || defined(__EDG) || defined(__ECPP__) || defined(__os_alpha_osf) || defined(__os_linux)
#if defined(__xlC__) && defined(__TEMPINC__)
#pragma implementation ("list_pt.c") /* IBM convention */
#else

#if !defined(_OS_PSE_COLL)
#include <ostore/coll/list_pt.c>
#else
#include <os_pse/coll/list_pt.c>
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



