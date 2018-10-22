/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef NLIST_HH
#define NLIST_HH

#if !defined(_OS_PSE_COLL)

#include <ostore/hdrstart.hh>
#include <ostore/coll/cursor.hh>
#include <ostore/coll/chlist.hh>
#include <ostore/coll/chlistpt.hh>
#include <ostore/coll/collptr.hh>

#else

#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/cursor.hh>
#include <os_pse/coll/chlist.hh>
#include <os_pse/coll/chlistpt.hh>
#include <os_pse/coll/collptr.hh>
_OS_BEGIN_NAMESPACE(os_pse)

#endif


/* Since these files will be included for PSE the second time when using both 
   OStore and PSE we want to redefine these macros.
*/

#ifdef OS_MARK_NLIST_REP
#undef OS_MARK_NLIST_REP
#endif
#define OS_MARK_NLIST_REP OS_MARK_NLIST
#ifdef OS_MARK_NLIST_PT_REP
#undef OS_MARK_NLIST_PT_REP
#endif
#define OS_MARK_NLIST_PT_REP OS_MARK_NLIST_PT

#ifdef OS_MARK_NLIST
#undef OS_MARK_NLIST
#endif
#define OS_MARK_NLIST(ptrs_in_head,ptrs_in_blocks) \
OS_MARK_SCHEMA_TYPESPEC((_PSE_NS_ os_nlist<ptrs_in_head,ptrs_in_blocks>));\
OS_MARK_SCHEMA_TYPESPEC((_PSE_NS_ os_chained_list_block_pt<ptrs_in_blocks>));

#ifdef OS_MARK_NLIST_PT
#undef OS_MARK_NLIST_PT
#endif
#define OS_MARK_NLIST_PT(E,ptrs_in_head,ptrs_in_blocks) \
OS_MARK_SCHEMA_TYPESPEC((_PSE_NS_ os_nList<E,ptrs_in_head,ptrs_in_blocks>));\
OS_MARK_SCHEMA_TYPESPEC((_PSE_NS_ os_nlist<ptrs_in_head,ptrs_in_blocks>));\
OS_MARK_SCHEMA_TYPESPEC((_PSE_NS_ os_chained_list_block_pt<ptrs_in_blocks>));

#ifdef OS_TRANSIENT_NLIST
#undef OS_TRANSIENT_NLIST
#endif
#define OS_TRANSIENT_NLIST(ptrs_in_head,ptrs_in_blocks)\
_PSE_NS_ os_typespec* _PSE_NS_ \
os_nlist<ptrs_in_head,ptrs_in_blocks >::get_os_typespec()\
{ return (_PSE_NS_ os_typespec*)0; }\
_PSE_NS_ os_typespec* _PSE_NS_ \
os_chained_list_block_pt<ptrs_in_blocks >::get_os_typespec() \
{ return (_PSE_NS_ os_typespec*)0; }\

#ifdef OS_TRANSIENT_NLIST_NO_BLOCK
#undef OS_TRANSIENT_NLIST_NO_BLOCK
#endif
#define OS_TRANSIENT_NLIST_NO_BLOCK(ptrs_in_head,ptrs_in_blocks)\
_PSE_NS_ os_typespec* _PSE_NS_ \
os_nlist<ptrs_in_head,ptrs_in_blocks >::get_os_typespec()\
{ return (_PSE_NS_ os_typespec*)0; }

template<os_int32 NUM_PTRS_IN_HEAD, os_int32 NUM_PTRS_IN_BLOCKS>
class os_nlist : public os_chained_list {

  friend class os_chained_list_block_pt<NUM_PTRS_IN_BLOCKS>;

protected:

  /* -------------------------------------------------------------------
   * data members
   * ---------------------------------------------------------------- */

  void_coll_ptr pointers[NUM_PTRS_IN_HEAD];

protected:

  /* -------------------------------------------------------------------
   * rep-specific virtual functions (provided by the parameterized 
   * class) 
   * ---------------------------------------------------------------- */

  virtual os_unsigned_int32 num_ptrs_in_head() const; 
        /* defined in nlist.cc */

  virtual os_unsigned_int32 num_ptrs_in_blocks() const
  { 
    return (os_unsigned_int32)NUM_PTRS_IN_BLOCKS;
  }  

  virtual os_chained_list_block* allocate_new_block(
  	_Chained_list_cursor* c =0 )
  {
    os_chained_list_block* new_block;
    new_block = new(
  	os_cluster::with(this),
      	os_chained_list_block_pt<NUM_PTRS_IN_BLOCKS>::get_os_typespec())
      os_chained_list_block_pt<NUM_PTRS_IN_BLOCKS>(this, 1);

    set_next_block(new_block, c);
    return new_block;
  }

  virtual os_unsigned_int32 contains_local(const void* v) const
  {
    register const os_coll_ptr * t = &pointers[0];
    register const os_coll_ptr * lim = t + local_card();
    for (; t < lim; t++)
      if ((void*)*t == v)
        return (os_unsigned_int32)(t - &pointers[0]) ;
    return os_chained_list_not_in_block;
  }

  virtual os_unsigned_int32 count_local(const void* v) const 
  {
    os_unsigned_int32 count = 0;
    register const os_coll_ptr* t = &pointers[0];
    register const os_coll_ptr* lim = t + local_card();
    for (; t < lim; t++)
      if ((void*)*t == v)
        count++;
    return count;
  }
 
protected:

  virtual os_chained_list_block* allocate_new_block(
  	os_chained_list_block* _this, os_chained_list_block*clb,
	_Chained_list_cursor* c=0 )
  {
    return (((os_chained_list_block_pt<NUM_PTRS_IN_BLOCKS>*)_this)
	  ->allocate_new_block(this, clb, c));
  }


  /* returns the local index if found, else 0xffffffff */
  virtual os_unsigned_int32 contains_local(
  	const os_chained_list_block* _this, const void* v ) const
  {
    return ( ((os_chained_list_block_pt<NUM_PTRS_IN_BLOCKS>*)_this)
  	 ->contains_local(v) );
  }

  virtual os_unsigned_int32 count_local(
  	const os_chained_list_block* _this, const void* v ) const
  {
    return ( ((os_chained_list_block_pt<NUM_PTRS_IN_BLOCKS>*)_this)
	 ->count_local(v) );
  }

  virtual void delete_block(os_chained_list_block* _this)
  {
    _this->_splice_self_out_of_list(this);
    delete ((os_chained_list_block_pt<NUM_PTRS_IN_BLOCKS>*)_this);
  }

public:

  os_nlist(os_unsigned_int32 size = 0, os_unsigned_int32 behavior = 0) 
        : os_chained_list(size, behavior) {}
  os_nlist(const os_collection & c) : os_chained_list() {*((os_collection*)this) = c;}

  virtual ~os_nlist()
  {
    destroy();
  }

private:

  os_unsigned_int32 max_local_card() const
  {
     return ((os_unsigned_int32)COLL_INT_NUM_PTRS_IN_HEAD) 
        - (has_blocks() ? 1 : 0);
  }
public:

#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else 
  static os_typespec* get_os_typespec() {return os_ts<os_nlist<NUM_PTRS_IN_HEAD, NUM_PTRS_IN_BLOCKS> >::get(); } 
#endif 


}; /* class os_nlist */


// Type safe facade
template<class E, os_int32 NUM_PTRS_IN_HEAD, os_int32 NUM_PTRS_IN_BLOCKS>
class os_nList : public os_Collection<E> {

public:
  os_nList(os_unsigned_int32 size = 0, os_unsigned_int32 behavior = 0)
  {
    this->_coll = new (os_cluster::with(this),
        os_nlist<NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>::get_os_typespec())
      os_nlist<NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>(size, behavior);
  }

  os_nList(const os_Collection<E>&c)
  {
    this->_coll = new (os_cluster::with(this),
        os_nlist<NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>::get_os_typespec())
        os_nlist<NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>(c);
  }

  virtual ~os_nList();

public:

  /* assignment operators */
  os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>& 
   operator =(const os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>& s)
    { return (os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>&)os_collection::operator =(s);}


  os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>& 
   operator =(const os_Collection<E>& s)
    { return (os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>&)os_collection::operator =(s);}

  os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>& 
   operator =(const E e)
    { return (os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>&)os_collection::operator =((void*)e);}

  os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>& 
   operator |=(const os_Collection<E>& s)
    { return (os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>&)os_collection::operator |=(s) ; }

  os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>& 
   operator |=(const E e)
    { return (os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>&)os_collection::operator |=((void*)e);}

  os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>& 
   operator &=(const os_Collection<E>& s)
    { return (os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>&)os_collection::operator &=(s) ; }

  os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>& 
   operator &=(const E e)
    { return (os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>&)os_collection::operator &=((void*)e);}

  os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>& 
   operator -=(const os_Collection<E>& s)
    { return (os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>&)os_collection::operator -=(s) ; }

  os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>& 
   operator -=(const E e)
    { return (os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>&)os_collection::operator -=((void*)e);}

public:
#ifndef _OS_PSE_COLL 
  static os_typespec* get_os_typespec();
#else  
  static os_typespec* get_os_typespec() {return os_ts<os_nList<E, NUM_PTRS_IN_HEAD, NUM_PTRS_IN_BLOCKS> >::get(); }  
#endif  


};


#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif 

