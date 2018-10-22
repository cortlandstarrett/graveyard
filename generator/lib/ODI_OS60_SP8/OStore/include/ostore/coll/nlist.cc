/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/* 
    ObjectStore(TM) Release 6.0

    Copyright (c) Excelon Corp. 1989-2000
    All Rights Reserved. Patent Pending.
*/

#ifndef NLIST_CC
#define NLIST_CC

#if !defined(_OS_PSE_COLL)

#include <ostore/hdrstart.hh>
#include <ostore/coll/cursor.hh>
#include <ostore/coll/chlist.hh>
#include <ostore/coll/chlistpt.hh>
#include <ostore/coll/collptr.hh>
#include <ostore/coll/nlist.hh>

#else

#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/cursor.hh>
#include <os_pse/coll/chlist.hh>
#include <os_pse/coll/chlistpt.hh>
#include <os_pse/coll/collptr.hh>
#include <os_pse/coll/nlist.hh>
_OS_BEGIN_NAMESPACE(os_pse)

#endif

/* 
 * Make at least one virtual non-inlined member function defined
 * for both os_nlist and os_nList. 
 */

template<os_int32 NUM_PTRS_IN_HEAD, os_int32 NUM_PTRS_IN_BLOCKS>
os_unsigned_int32
os_nlist<NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>::num_ptrs_in_head() const 
{
  return (os_unsigned_int32)NUM_PTRS_IN_HEAD;
}

template<class E, os_int32 NUM_PTRS_IN_HEAD, os_int32 NUM_PTRS_IN_BLOCKS>
os_nList<E,NUM_PTRS_IN_HEAD,NUM_PTRS_IN_BLOCKS>::~os_nList()
{}

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif 

