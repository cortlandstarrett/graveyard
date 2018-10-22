/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _COLL_ARRAY
#define _COLL_ARRAY

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#include <ostore/coll/plist.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/plist.hh>

_OS_BEGIN_NAMESPACE(os_pse)
#endif

/* the typeless interface for dealing with arrays */
   
class os_array : public os_packed_list
{
public:
  virtual ~os_array() ;
  os_array(const os_array& a) {*this = a;}
  os_array(const os_collection&c) {*this = c;}  
  os_array(os_unsigned_int32 expected_size = 0, os_unsigned_int32 card = 0, 
     void* fill_value = (void*)0) : os_packed_list(expected_size) 
  {  
    while (card--) this->insert(fill_value);
  }

  /* get the default behavior associated with this type */
  /* i.e. if you say array::create, this is the behavior you will get */
  static os_unsigned_int32 default_behavior() 
    {return maintain_order | allow_duplicates | allow_nulls | be_an_array;};

  static os_unsigned_int32 required_behavior() 
    {return maintain_order | allow_nulls | be_an_array;};

  /* default type */
  static os_collection::os_collection_type default_type() { return OS_Array; }

  static os_array &create(os_database* db, os_unsigned_int32 behavior = 0,
			  os_int32 expected_size = 0,
			  os_unsigned_int32 card = 0, void* fill_value = 0) ;
  static os_array &create(os_segment* seg, os_unsigned_int32 behavior = 0,
			  os_int32 expected_size = 0,
			  os_unsigned_int32 card = 0, void* fill_value = 0) ;
  static os_array &create(os_cluster_with & clust, os_unsigned_int32 behavior = 0,
			  os_int32 expected_size = 0,
			  os_unsigned_int32 card = 0, void* fill_value = 0) ;
  static os_array &create(const void *proximity, 
                          os_unsigned_int32 behavior = 0,
			  os_int32 expected_size = 0,
			  os_unsigned_int32 card = 0, void* fill_value = 0);

  static void destroy(os_array& c) { os_collection::destroy(c); }

public:
  void set_cardinality(os_unsigned_int32 new_card, void* fill_value);

  /* assignment operators */
  os_array& operator =(const os_array& s) /* need this one or cfront will generate it! */
    { return (os_array&)os_collection::operator =(s);}
  os_array& operator =(const os_collection& s)
    { return (os_array&)os_collection::operator =(s);}
  os_array& operator =(const void* e)
    { return (os_array&)os_collection::operator =((void *)e);}

  os_array& operator |=(const os_collection& s)
    { return (os_array&)os_collection::operator |=(s) ; }
  os_array& operator |=(const void* e)
    { return (os_array&)os_collection::operator |=((void *)e);}

  os_array& operator &=(const os_collection& s)
    { return (os_array&)os_collection::operator &=(s) ; }
  os_array& operator &=(const void* e)
    { return (os_array&)os_collection::operator &=((void *)e);}

  os_array& operator -=(const os_collection& s)
    { return (os_array&)os_collection::operator -=(s) ; }
  os_array& operator -=(const void* e)
    { return (os_array&)os_collection::operator -=((void *)e);}

public:
  /* non-destructive set operators */
  os_collection& operator |(const os_collection& s) const
    { return os_collection::operator |(s); }
  os_collection& operator |(const void* e) const
    { return os_collection::operator |(e); }
  os_collection& operator &(const os_collection& s) const
    { return os_collection::operator &(s); }
  os_collection& operator &(const void* e) const
    { return os_collection::operator &(e); }
  os_collection& operator -(const os_collection& s) const
    { return os_collection::operator -(s); }
  os_collection& operator -(const void* e) const
    { return os_collection::operator -(e); }


  static os_typespec* get_os_typespec();
}; 

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
