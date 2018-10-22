/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


// coll_pt.hh
// Initial re-write for 6.0 4/15/1998
// This file contains the following classes:
//   os_Collection -  Base class for classes
//     collections.  Non-instantiable.

#ifndef _COLL_PT
#define _COLL_PT
#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>

/* IBM's template implementation includes this header alone. */
#if !defined(_ABSTRACT_COLLECTION)
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#endif
#else
#include <os_pse/psecoll/hdrstart.hh>

/* IBM's template implementation includes this header alone. */
#if !defined(_ABSTRACT_COLLECTION)
#include <os_pse/ostore.hh>
#include <os_pse/coll.hh>
#endif
_OS_BEGIN_NAMESPACE(os_pse)
#endif // _OS_PSE_COLL

template <class E>  class os_Set ;
template <class E>  class os_Bag ;
template <class E>  class os_List ;
template <class E>  class os_Array ;
template <class E>  class os_Cursor ;
template <class E>  class os_Collection ;


template <class E>
class os_Collection : public os_outofline_collection
{
public:
  os_Collection(os_unsigned_int32 sz = 0) {
    _coll = new(os_cluster::with(this), os_set::get_os_typespec()) os_set(sz);
  }
  os_Collection(const os_Collection<E>&c) {
     _coll = new(os_cluster::with(this), os_set::get_os_typespec()) os_set(c);
  }
 
  static os_Collection<E> &create(os_database* db, 
                                  os_unsigned_int32 behavior = 0,
			          os_int32 expected_size = 0)
    {
      char buffer[16];
      bits_to_rep(buffer, behavior);
      return *((os_Collection<E>*)generate_facade(buffer, db, expected_size));
    }

  static os_Collection<E> &create(os_cluster_with & clust, 
				  os_unsigned_int32 behavior = 0,
				  os_int32 expected_size = 0)
    { 
      char buffer[16];
      bits_to_rep(buffer, behavior);
      return *((os_Collection<E>*)generate_facade(buffer, clust, expected_size));
    }

  static os_Collection<E> &create(os_segment* seg, 
                                  os_unsigned_int32 behavior = 0,
				  os_int32 expected_size = 0)
    {
      char buffer[16];
      bits_to_rep(buffer, behavior);
      return *((os_Collection<E>*)generate_facade(buffer, seg, expected_size));
    }

  static os_Collection<E> &create(const void *proximity,
				  os_unsigned_int32 behavior = 0,
				  os_int32 expected_size = 0)
    {
      char buffer[16];
      bits_to_rep(buffer, behavior);
      return *((os_Collection<E>*)generate_facade(buffer, (void*)proximity, 
               expected_size));
    }

public:
  // Used by dump/load
   void init_load(os_unsigned_int32 b = 0, os_int32 sz = 0)
    {
      _coll = new(os_cluster::with(this), os_set::get_os_typespec()) os_set(sz);
    }

public:
 
  static void destroy(os_Collection<E>& c) { os_collection::destroy(c); }
				  
  E pick(const os_index_path& p, const os_coll_range& r) const
    { return (E)os_collection::pick(p, r); }
  E pick() const { return (E)os_collection::pick() ; }
  E only() const { return (E)os_collection::only() ; }
  E retrieve(os_unsigned_int32 i) const {return (E)os_collection::retrieve(i);}
  E retrieve(const os_cursor& c) const 
    {return (E)os_collection::retrieve(*(os_cursor*)(void*)&c);}

  os_int32 retrieve_first(const E &v) const
    {return os_collection::retrieve_first((const void*&)v);}
  E retrieve_first() const 
  {return (E) os_collection::retrieve_first();}
  os_int32 retrieve_last(const E &v) const 
    {return os_collection::retrieve_last((const void*&)v);}
  E retrieve_last() const 
  {return (E) os_collection::retrieve_last();}

public:
  /* Update protocol */
  void insert(E p) { os_collection::insert((void*)p) ; }
  os_int32 remove(E p) { return os_collection::remove((void*)p) ; }

  /* List-specific update protocol */
  void insert_first(E p) { os_collection::insert_first((void*)p) ; }
  void insert_last(E p) { os_collection::insert_last((void*)p) ; }

  os_int32 remove_first(E &p) 
  {return os_collection::remove_first((const void* &) p);}
  os_int32 remove_last(E &p) 
  {return os_collection::remove_last((const void* &)p);}
  
  /* for collections that don't contain null pointers */
  E remove_first() 
  {return (E) os_collection::remove_first(); }
  E remove_last() 
  {return (E)os_collection::remove_last();}
  void insert_before(const E p, const os_cursor& c) 
    {os_collection::insert_before(p,*(os_cursor*)(void*)&c);}
  void insert_before(const E p, os_unsigned_int32 position) 
    {os_collection::insert_before(p,position);}
  void insert_after(const E p, const os_cursor& c) 
    {os_collection::insert_after(p,*(os_cursor*)(void*)&c);}
  void insert_after(const E p, os_unsigned_int32 position) 
    {os_collection::insert_after(p,position);}

  void remove_at(const os_cursor& c) 
    {os_collection::remove_at(*(os_cursor*)(void*)&c);}
  void remove_at(os_unsigned_int32 position)  
    {os_collection::remove_at(position);}

  E replace_at(const E p, const os_cursor& c) 
    {return (E)os_collection::replace_at(p,*(os_cursor*)(void*)&c);}
  E replace_at(const E p, os_unsigned_int32 position) 
    {return (E)os_collection::replace_at(p,position);}

public:
  /* membership */
  os_int32 contains(E p) const { return os_collection::contains((void*)p) ; }
  os_int32 count(E p) { return os_collection::count((void*)p) ; }


public:
  /* assignment operators */
  os_Collection<E>& operator =(const os_Collection<E>& s)
    {return (os_Collection<E>&)os_collection::operator =(s);}
  os_Collection<E>& operator =(const E e)
    { return (os_Collection<E>&)os_collection::operator =((void*)e);}
  os_Collection<E>& operator |=(const os_Collection<E>& s)
    { return (os_Collection<E>&)os_collection::operator |=(s) ; }
  os_Collection<E>& operator |=(const E e)
    { return (os_Collection<E>&)os_collection::operator |=((void*)e);}
  os_Collection<E>& operator &=(const os_Collection<E>& s)
    { return (os_Collection<E>&)os_collection::operator &=(s) ; }
  os_Collection<E>& operator &=(const E e)
    { return (os_Collection<E>&)os_collection::operator &=((void*)e);}
  os_Collection<E>& operator -=(const os_Collection<E>& s)
    { return (os_Collection<E>&)os_collection::operator -=(s) ; }
  os_Collection<E>& operator -=(const E e)
    { return (os_Collection<E>&)os_collection::operator -=((void*)e);}


  /* non-destructive set operators */
  os_Collection<E>& operator |(const os_Collection<E>& s) const
    { return (os_Collection<E>&)os_collection::operator |(s); }
  os_Collection<E>& operator |(const E e) const
    { return (os_Collection<E>&)os_collection::operator |(e); }
  os_Collection<E>& operator &(const os_Collection<E>& s) const
    { return (os_Collection<E>&)os_collection::operator &(s); }
  os_Collection<E>& operator &(const E e) const
    { return (os_Collection<E>&)os_collection::operator &(e); }
  os_Collection<E>& operator -(const os_Collection<E>& s) const
    { return (os_Collection<E>&)os_collection::operator -(s); }
  os_Collection<E>& operator -(const E e) const
    { return (os_Collection<E>&)os_collection::operator -(e); }

  /* relational operators */
  os_int32 operator ==(const os_Collection<E>& s) const 
    { return os_collection::operator ==(s) ; }
  os_int32 operator ==(const E e) const 
    { return os_collection::operator ==((void*)e) ; }
  os_int32 operator !=(const os_Collection<E>& s) const 
    { return os_collection::operator !=(s) ; }
  os_int32 operator !=(const E e) const 
    { return os_collection::operator !=((void*)e) ; }
  os_int32 operator <(const os_Collection<E>& s) const 
    { return os_collection::operator <(s) ; }
  os_int32 operator <(const E e) const 
    { return os_collection::operator <((void*)e) ; }
  os_int32 operator <=(const os_Collection<E>& s) const 
    { return os_collection::operator <=(s) ; }
  os_int32 operator <=(const E e) const 
    { return os_collection::operator <=((void*)e) ; }
  os_int32 operator >(const os_Collection<E>& s) const 
    { return os_collection::operator >(s) ; }
  os_int32 operator >(const E e) const 
    { return os_collection::operator >((void*)e) ; }
  os_int32 operator >=(const os_Collection<E>& s) const 
    { return os_collection::operator >=(s) ; }
  os_int32 operator >=(const E e) const 
    { return os_collection::operator >=((void*)e) ; }

  /* Cast operators */
  operator const os_List<E> &() const
    { return (const os_List<E> &) (this->operator const os_list &()); }
  operator os_List<E> &()
    { return (os_List<E> &) (this->operator os_list&()); }
  operator const os_Set<E> &() const
    { return (const os_Set<E> &) (this->operator const os_set &()); }
  operator os_Set<E> &()
    { return (os_Set<E> &) (this->operator os_set &()); }
  operator const os_Bag<E> &() const
    { return (const os_Bag<E> &) (this->operator const os_bag &()); }
  operator os_Bag<E> &()
    { return (os_Bag<E> &) (this->operator os_bag &()); }
  operator const os_Array<E> &() const
    { return (const os_Array<E> &) (this->operator const os_array &()); }
  operator os_Array<E> &()
    { return (os_Array<E> &) (this->operator os_array&()); }
 
public:
  /* Query protocol */
     
  os_Collection<E>& query(char *element_type,
			char *query_string,
			os_database *schema_db=0,
			char* file_name = 0,
			os_unsigned_int32 line =0,
		        os_boolean dups = query_dont_preserve_duplicates) const
    {
      return (os_Collection<E>&)
	     os_collection::query(element_type, query_string,
				  schema_db, file_name, line, dups);
    }

  os_Collection<E>& query(char *element_type,
			char *query_string,
			os_str_conv::encode_type string_literal_char_encoding,
			os_database *schema_db=0,
			char* file_name = 0,
			os_unsigned_int32 line =0,
		        os_boolean dups = query_dont_preserve_duplicates) const
    {
      return (os_Collection<E>&)
	     os_collection::query(element_type, query_string, 
                                  string_literal_char_encoding,
				  schema_db, file_name, line, dups);
    }
					      
  os_Collection<E>& query(const os_bound_query& q,
			os_boolean dups = query_dont_preserve_duplicates) const
    { return (os_Collection<E>&) os_collection::query(q, dups); }

  E query_pick(char *element_type,
	       char *query_string,
	       os_database *schema_db=0,
	       char *file_name=0,
	       os_unsigned_int32 line=0) const
    {
      return (E) os_collection::query_pick(element_type, query_string,
					   schema_db, file_name, line);
    }

   E query_pick(char *element_type,
	        char *query_string,
                os_str_conv::encode_type string_literal_char_encoding,
	        os_database *schema_db=0,
	        char *file_name=0,
	        os_unsigned_int32 line=0) const
    {
      return (E) os_collection::query_pick(element_type, query_string,
                                           string_literal_char_encoding, 
                                           schema_db, 
                                           file_name, line);
    }

  E query_pick(const os_bound_query& q) const
    {
      return (E) os_collection::query_pick(q); 
    }

public:
#if !(defined(__odi_hp11) || defined(__os_aix43))
#endif
#if !defined(_OS_PSE_COLL)
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() {return os_ts<os_Collection<E > >::get(); }
#endif

protected:
  // Special constructor called by derived class so a default 
  // os_set does not get generated
/* AIX xlC compiler complains about specialized constructors */
#if defined(__xlC__)
  os_Collection(char override) {}
#else
  os_Collection<E>(char override) {}
#endif

public:
#if defined(__xlC__) || defined(__os_cafe) || defined(__EDG) || defined(__os_hpcfront) || defined(__ECPP__) || defined (__os_alpha_osf) || defined(__os_linux)
   ~os_Collection();
#endif
};  // os_Collection

#if defined(__xlC__) || defined(__EDG) || defined(__ECPP__) || defined(__os_alpha_osf) || defined(__os_linux)
#if defined(__xlC__) && defined(__TEMPINC__)
#pragma implementation ("coll_pt.c"); /* IBM convention */
#else
#if !defined(_OS_PSE_COLL)
#include <ostore/coll/coll_pt.c>
#else
#include <os_pse/coll/coll_pt.c>
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
