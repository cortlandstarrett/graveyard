/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _COLL_LIST
#define _COLL_LIST

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#include <ostore/coll/chlist.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/chlist.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

class os_list : public os_chained_list_4_8 {

public:
  virtual ~os_list();

#ifdef _OS_COLL_LIST_OPTIMIZE
  os_list(os_unsigned_int32 size = 0,
          os_unsigned_int32 behavior = 0) 
     :  os_chained_list_4_8(size, (behavior |= os_collection_global_optimized)) {}

  os_list(const os_list&l)
     :  os_chained_list_4_8(0, os_collection_global_optimized) {*this = l;}

  os_list(const os_collection&c)
     :  os_chained_list_4_8(0, os_collection_global_optimized) {*this = c;}
#else
  os_list(os_unsigned_int32 size = 0,
          os_unsigned_int32 behavior = 0) 
     :  os_chained_list_4_8(size, behavior) {}

  os_list(const os_list&l) {*this = l;}
  os_list(const os_collection&c) {*this = c;}
#endif

  /* get the default behavior associated with this type */
  /* i.e. if you say list::create, this is the behavior you will get */
  static os_unsigned_int32 default_behavior()
    { return maintain_order | allow_duplicates; };

  static os_unsigned_int32 required_behavior()
  { return maintain_order; }
  
  /* default type */
  static os_collection::os_collection_type default_type() { return OS_List; }

  static os_list &create(os_database* db, os_unsigned_int32 behavior = 0,
                         os_int32 expected_size = 0);
  
  static os_list &create(os_segment* seg, os_unsigned_int32 behavior = 0,
			 os_int32 expected_size = 0);
			
  static os_list &create(os_cluster_with & clust, os_unsigned_int32 behavior = 0,
			 os_int32 expected_size = 0);

  static os_list &create(os_cluster_with * clust, 
			 os_unsigned_int32 behaviour = 0,
			 os_int32 expected_size = 0);
			
  static os_list &create(const void *proximity, os_unsigned_int32 behavior = 0,
			 os_int32 expected_size = 0);
			
  static void destroy(os_list& c) { os_collection::destroy(c); }


public:
  /* assignment operators */
  os_list& operator =(const os_list& s) /* need this one or cfront will generate it! */
    {return (os_list&)os_collection::operator =(s);}
  os_list& operator =(const os_collection& s)
    {return (os_list&)os_collection::operator =(s);}
  os_list& operator =(const void * e)
    { return (os_list&)os_collection::operator =((void *)e);}

  os_list& operator |=(const os_collection& s)
    { return (os_list&)os_collection::operator |=(s) ; }
  os_list& operator |=(const void * e)
    { return (os_list&)os_collection::operator |=((void *)e);}

  os_list& operator &=(const os_collection& s)
    { return (os_list&)os_collection::operator &=(s) ; }
  os_list& operator &=(const void * e)
    { return (os_list&)os_collection::operator &=((void *)e);}

  os_list& operator -=(const os_collection& s)
    { return (os_list&)os_collection::operator -=(s) ; }
  os_list& operator -=(const void * e)
    { return (os_list&)os_collection::operator -=((void *)e);}

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
};  /*- class os_list -*/

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
