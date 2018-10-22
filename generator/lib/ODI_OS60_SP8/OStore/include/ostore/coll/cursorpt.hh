/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
 */
#ifndef __OS_CURSORPT
#define __OS_CURSORPT

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

template <class E>
class os_Cursor : public os_cursor
{
  os_int32 first(E& el) {return os_cursor::first(*(void**)(E*)&el); };
  os_int32 last(E& el) {return os_cursor::last(*(void**)(E*)&el);};
  os_int32 next(E& el) {return os_cursor::next(*(void**)(E*)&el);};
  os_int32 previous(E& el) {return os_cursor::previous(*(void**)(E*)&el);};
  E operator++() { return next(); };
  E operator--() { return previous(); };
public:
  /* coll */
#ifdef _OS_COLL_CURSOR_OPTIMIZE
  os_Cursor(const os_Collection<E>& c, os_int32 _flags = os_cursor::optimized):
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
  os_Cursor(const os_dictionary& c, os_int32 _flags = os_cursor::optimized) :
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
  os_Cursor(const os_Set<E>& c, os_int32 _flags =  os_cursor::optimized) :
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
  os_Cursor(const os_Bag<E>& c, os_int32 _flags =  os_cursor::optimized) :
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
  os_Cursor(const os_List<E>& c, os_int32 _flags =  os_cursor::optimized) :
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
  os_Cursor(const os_Array<E>& c, os_int32 _flags =  os_cursor::optimized) :
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
#else
  os_Cursor(const os_Collection<E>& c, os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
  os_Cursor(const os_dictionary& c, os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
  os_Cursor(const os_Set<E>& c, os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
  os_Cursor(const os_Bag<E>& c, os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
  os_Cursor(const os_List<E>& c, os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
  os_Cursor(const os_Array<E>& c, os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), _flags) {}
#endif

  /* coll, index path */
  os_Cursor(const os_Collection<E>& c, const os_index_path& ixp, 
	    os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), ixp, _flags) {}
  os_Cursor(const os_dictionary& c, const os_index_path& ixp, 
	    os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), ixp, _flags) {}
  os_Cursor(const os_Set<E>& c, const os_index_path& ixp, 
	    os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), ixp, _flags) {}
  os_Cursor(const os_Bag<E>& c, const os_index_path& ixp, 
	    os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), ixp, _flags) {}
  os_Cursor(const os_List<E>& c, const os_index_path& ixp, 
	    os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), ixp, _flags) {}
  os_Cursor(const os_Array<E>& c, const os_index_path& ixp, 
	    os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), ixp, _flags) {}

  /* coll, typename */
  os_Cursor(const os_Collection<E>& c, const char* _typename, 
	    os_int32 _flags = 0) 
    : os_cursor(*(const os_collection*)((void*)&c), _typename, _flags) {};
  os_Cursor(const os_dictionary& coll, const char * _typename,
	    os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&coll), _typename, _flags) {}
  os_Cursor(const os_Set<E>& coll, const char* _typename, 
	    os_int32 _flags = 0) : 
    os_cursor(*(const os_collection*)((void*)&coll), _typename, _flags) {}
  os_Cursor(const os_Bag<E>& coll, const char* _typename, 
	    os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void*)&coll), _typename, _flags) {}
  os_Cursor(const os_List<E>& coll, const char* _typename, 
	    os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void*)&coll), _typename, _flags) {}
  os_Cursor(const os_Array<E>& coll, const char* _typename, 
	    os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void*)&coll), _typename, _flags) {}
  
  /* coll, rank fcn */
  os_Cursor(const os_Collection<E>& c, _Rank_fcn rnk, os_int32 _flags = 0) 
    : os_cursor(*(const os_collection*)((void*)&c), rnk, _flags) {};
  os_Cursor(const os_dictionary& c, _Rank_fcn rnk, os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void *)&c), rnk, _flags) {}
  os_Cursor(const os_Set<E>& c, _Rank_fcn rnk, os_int32 _flags = 0) : 
    os_cursor(*(const os_collection*)((void*)&c), rnk, _flags) {}
  os_Cursor(const os_Bag<E>& c, _Rank_fcn rnk, os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void*)&c), rnk,_flags) {}
  os_Cursor(const os_List<E>& c, _Rank_fcn rnk, os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void*)&c),rnk,_flags) {}
  os_Cursor(const os_Array<E>& c, _Rank_fcn rnk, os_int32 _flags = 0) :
    os_cursor(*(const os_collection*)((void*)&c), rnk, _flags) {}

  /* coll, index path, range */
  os_Cursor(const os_Collection<E>& c, const os_index_path& ixp, 
	    const os_coll_range& r, os_int32 _flags = 0)
    : os_cursor(*(const os_collection*)((void*)&c), ixp, r, _flags) {}
  os_Cursor(const os_dictionary& c, const os_index_path& ixp, 
	    const os_coll_range& r, os_int32 _flags = 0)
    : os_cursor(*(const os_collection*)((void *)&c), ixp, r, _flags) {}
  os_Cursor(const os_Set<E>& c, const os_index_path& ixp, 
	    const os_coll_range& r, os_int32 _flags = 0)
    : os_cursor(*(const os_collection*)((void*)&c), ixp, r, _flags) {}
  os_Cursor(const os_Bag<E>& c, const os_index_path& ixp, 
	    const os_coll_range& r, os_int32 _flags = 0)
    : os_cursor(*(const os_collection*)((void*)&c), ixp, r, _flags) {}
  os_Cursor(const os_List<E>& c, const os_index_path& ixp, 
	    const os_coll_range& r, os_int32 _flags = 0)
    : os_cursor(*(const os_collection*)((void*)&c), ixp, r, _flags) {}
  os_Cursor(const os_Array<E>& c, const os_index_path& ixp, 
	    const os_coll_range& r, os_int32 _flags = 0)
    : os_cursor(*(const os_collection*)((void*)&c), ixp, r, _flags) {}

  /* dictionary, range */
  os_Cursor(const os_dictionary& c, const os_coll_range& r, 
	    os_int32 _flags = 0)
    : os_cursor(c, r, _flags) {}

  void rebind(const os_dictionary& c)
    { os_cursor::rebind(*(const os_collection*)((void*)&c)); }

  void rebind(const os_Collection<E>& c)
    { os_cursor::rebind(*(const os_collection*)((void*)&c)); }

  /* navigation within the collection */
  E first() {return (E)os_cursor::first(); };
  E last() {return (E)os_cursor::last();};
  E next() {return (E)os_cursor::next();};
  E previous() {return (E)os_cursor::previous();};

  /* retrieval from collection */
  E retrieve() {return (E)os_cursor::retrieve();};
  operator E () { return retrieve(); };
#ifdef __os_cplusplus
  E operator-> () { return retrieve(); };
#endif

  /* operations that modify the collection */
  void insert_after(const E p) const { os_cursor::insert_after(p) ; }
  void insert_before(const E p) const { os_cursor::insert_before(p) ; }
  void remove_at() const { os_cursor::remove_at() ; }

  os_Cursor<E>& operator= (const os_Cursor<E>& c)  
    { return (os_Cursor<E>&)(os_cursor::operator=(c)); }

  static os_typespec* get_os_typespec() { return os_cursor::get_os_typespec(); }
};

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
