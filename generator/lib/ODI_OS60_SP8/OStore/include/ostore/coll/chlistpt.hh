/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _COLL_CHAINED_LIST_PT
#define _COLL_CHAINED_LIST_PT

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#include <ostore/coll/cursor.hh>
#include <ostore/coll/chlist.hh>
#include <ostore/coll/collptr.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/cursor.hh>
#include <os_pse/coll/chlist.hh>
#include <os_pse/coll/collptr.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

/* ---------------------------------------------------------------------
 * Forward declarations
 * ------------------------------------------------------------------ */

/* ---------------------------------------------------------------------
 * os_chained_list_block_pt - // Inline class
 */

template<os_int32 NUM_PTRS> 
class os_chained_list_block_pt : public os_chained_list_block {

protected:

  /* -------------------------------------------------------------------
   * data members
   * ---------------------------------------------------------------- */

  void_coll_ptr pointers[NUM_PTRS];

public:
  ODI_INST();

  os_chained_list_block* allocate_new_block(
  	const os_chained_list* cl, os_chained_list_block*clb,
	_Chained_list_cursor* c = 0 )
  {
    os_chained_list_block* new_block;
    new_block = new(os_cluster::with(clb), 
        os_chained_list_block_pt<NUM_PTRS>::get_os_typespec())
      os_chained_list_block_pt<NUM_PTRS>(clb, 0);

    clb->set_next_block(cl, new_block, c);
    return new_block;
  }

  os_unsigned_int32 contains_local(const void* v) const
  {
    register void_coll_ptr* t = (void_coll_ptr*)&pointers[0];
    register void_coll_ptr* lim = t + local_card();
    for (;t < lim; t++)
      if ((void*)*t == (void*)v)
	return (os_unsigned_int32)(t - &pointers[0]);

    return (os_unsigned_int32)os_chained_list_not_in_block;
  }

  os_unsigned_int32 count_local(const void* v) const
  {
    os_unsigned_int32 count = 0;
    register void_coll_ptr* t = (void_coll_ptr*)&pointers[0];
    register void_coll_ptr* lim = t + local_card();
    for (;t < lim; t++)
      if ((void*)*t == (void*)v)
	count++;
    return count;
  }

public:

  os_chained_list_block_pt(void* __prev, os_boolean proot)
  : os_chained_list_block(__prev, proot) {}

  os_chained_list_block_pt() : os_chained_list_block(0, 0) {}

private:

  os_unsigned_int32 max_local_card() const
  {
    return (os_unsigned_int32)
      (has_next() || is_last() ? NUM_PTRS - 1 : NUM_PTRS);
  }

  os_chained_list_block* next_block()
  {
    return has_next() ? (os_chained_list_block*) (void*)pointers[NUM_PTRS - 1] : 0;
  }

public:
#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() {return os_ts<os_chained_list_block_pt<NUM_PTRS> >::get(); }
#endif

}; /* class os_chained_list_block_pt */


/* ---------------------------------------------------------------------
 * os_chained_list_block_hpt - // Inline class
 */

template<os_int32 NUM_PTRS> 
class os_chained_list_block_hpt : public os_chained_list_block {

protected:

  /* -------------------------------------------------------------------
   * data members
   * ---------------------------------------------------------------- */

  void * pointers[NUM_PTRS];

public:
  ODI_INST();

  os_chained_list_block* allocate_new_block(
  	const os_chained_list* cl, os_chained_list_block*clb,
	_Chained_list_cursor* c = 0 )
  {
    os_chained_list_block* new_block;
    new_block = new(os_cluster::with(clb), 
        os_chained_list_block_hpt<NUM_PTRS>::get_os_typespec())
      os_chained_list_block_hpt<NUM_PTRS>(clb, 0);

    clb->set_next_block(cl, new_block, c);
    return new_block;
  }

  os_unsigned_int32 contains_local(const void* v) const
  {
    register void** t = (void**)&pointers[0];
    register void** lim = t + local_card();
    for (;t < lim; t++)
      if (*t == v)
        return (os_unsigned_int32)(t - (void**)&pointers[0]);

    return (os_unsigned_int32)os_chained_list_not_in_block;
  }

  os_unsigned_int32 count_local(const void* v) const
  {
    os_unsigned_int32 count = 0;
    register void** t = (void**)&pointers[0];
    register void** lim = t + local_card();
    for (;t < lim; t++)
      if (*t == v)
        count++;
    return count;
  }

public:

  os_chained_list_block_hpt(void* __prev, os_boolean proot)
  : os_chained_list_block(__prev, proot) 
    {set_use_hard_pointers();}

  os_chained_list_block_hpt() : os_chained_list_block(0, 0) 
    {set_use_hard_pointers();}

private:

  os_unsigned_int32 max_local_card() const
  {
    return (os_unsigned_int32)
      (has_next() || is_last() ? NUM_PTRS - 1 : NUM_PTRS);
  }

  os_chained_list_block* next_block()
  {
    return has_next() ? (os_chained_list_block*)pointers[NUM_PTRS - 1] : 0;
  }

public:
#ifndef _OS_PSE_COLL
  static os_typespec* get_os_typespec();
#else
  static os_typespec* get_os_typespec() {return os_ts<os_chained_list_block_hpt<NUM_PTRS> >::get(); }
#endif

}; /* class os_chained_list_block_hpt */



#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif /* _COLL_CHAINED_LIST_PT */
