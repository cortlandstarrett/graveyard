/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _COLL_SET
#define _COLL_SET
#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#include <ostore/coll/dyn_hash.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/dyn_hash.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

/* ---------------------------------------------------------------------
 * Forward declarations
 * ------------------------------------------------------------------ */

class os_list;
   
/* ---------------------------------------------------------------------
 * os_set
 *
 * the typeless interface for dealing with sets.
 * ------------------------------------------------------------------ */

class os_set : public os_dyn_hash {
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
  void* retrieve(const os_cursor& c) const {return os_collection::retrieve(c);}
  void remove_at(const os_cursor& c) {os_collection::remove_at(c);}
  void replace_at(const void* v, const os_cursor& c) {os_collection::replace_at(v,c);}

public:
  enum os_set_type { unknown=0,
              optimized_set = os_collection_optimized_set};
  virtual ~os_set() ;

#ifdef _OS_COLL_SET_OPTIMIZE
  os_set(os_unsigned_int32 size = 0) :  
    os_dyn_hash(size, os_collection_global_optimized) {}
  os_set(const os_set& s) : os_dyn_hash((os_unsigned_int32)0, 
                                        os_collection_global_optimized) 
    {*this = s;}
  os_set(const os_collection&c) : os_dyn_hash((os_unsigned_int32)0, 
                                              os_collection_global_optimized) 
    {*this = c;}

#else
  os_set(os_unsigned_int32 size = 0) :  os_dyn_hash(size) {} 

  os_set(const os_set& s) : os_dyn_hash((os_unsigned_int32)0) {*this = s;}
  os_set(const os_collection&c) : os_dyn_hash((os_unsigned_int32)0) {*this = c;}
#endif

  os_set(os_unsigned_int32 size, os_set_type option ) : 
    os_dyn_hash(size, (os_unsigned_int32)option) {}

  /* get the default behavior associated with this type */
  /* i.e. if you say set::create, this is the behavior you will get */
  static os_unsigned_int32 default_behavior() {return 0;};
  
  /* default type */
  static os_collection::os_collection_type default_type() { return OS_Set; }

  static os_set &create(os_database* db, os_unsigned_int32 behavior = 0,
			os_int32 expected_size = 0);
			
  static os_set &create(os_segment* seg, os_unsigned_int32 behavior = 0,
			os_int32 expected_size = 0);
			
  static os_set &create(os_cluster_with & clust, os_unsigned_int32 behavior = 0,
			os_int32 expected_size = 0);

  static os_set &create(os_cluster_with* clust,
			os_unsigned_int32 behaviour = 0,
			os_int32 expected_size = 0);
			
  static os_set &create(const void *proximity, os_unsigned_int32 behavior = 0,
			os_int32 expected_size = 0);
			
  static void destroy(os_set& c) { os_collection::destroy(c); }

public:
  /* assignment operators */
  os_set& operator =(const os_set& s) /* need this one or cfront will generate it! */
    { return (os_set&)os_collection::operator =(s);}
  os_set& operator =(const os_collection& s)
    { return (os_set&)os_collection::operator =(s);}
  os_set& operator =(const void* e)
    { return (os_set&)os_collection::operator =((void *)e);}

  os_set& operator |=(const os_collection& s)
    { return (os_set&)os_collection::operator |=(s) ; }
  os_set& operator |=(const void* e)
    { return (os_set&)os_collection::operator |=((void *)e);}

  os_set& operator &=(const os_collection& s)
    { return (os_set&)os_collection::operator &=(s) ; }
  os_set& operator &=(const void* e)
    { return (os_set&)os_collection::operator &=((void *)e);}

  os_set& operator -=(const os_collection& s)
    { return (os_set&)os_collection::operator -=(s) ; }
  os_set& operator -=(const void* e)
    { return (os_set&)os_collection::operator -=((void *)e);}

  /* non-destructive set operators */
public:
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
