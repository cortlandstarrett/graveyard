/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/* -*- Mode:C++ -*- */
#ifndef _COLL_DYN_BAG
#define _COLL_DYN_BAG

#if !defined(_OS_PSE_COLL)
#include <ostore/coll/dyn_hash.hh>
#else
#include <os_pse/coll/dyn_hash.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif


/* ---------------------------------------------------------------------
 * os_dyn_bag
 */

class _OS_COLL_IMPORT os_dyn_bag : public os_dyn_hash {


protected:

  /* -------------------------------------------------------------------
   * behavior protocol
   * ---------------------------------------------------------------- */

  virtual os_unsigned_int32 _get_behavior() const 
    { return os_collection::allow_duplicates; }

  virtual os_int32 _rep_enum() const 
    {return os_dyn_bag_rep;}

protected:
  
  /* these return true if the element was removed, modifies the argument to */
  virtual os_int32 _count(os_void_const_p) const ;
  
  /* assignment operators are not inherited, so supply one */
  os_dyn_bag& operator =(const os_dyn_bag& s)
    { return (os_dyn_bag &)os_collection::operator =(s); }
  os_dyn_bag& operator =(const os_collection& s)
    { return (os_dyn_bag &)os_collection::operator =(s); }
  os_dyn_bag& operator =(const void* e)
    { return (os_dyn_bag &)os_collection::operator =(e); }


protected:

  /* -------------------------------------------------------------------
   * other odds and ends
   * ---------------------------------------------------------------- */

  virtual os_boolean _fast_count() const;

public:

  os_dyn_bag(os_unsigned_int32 size = 0);
  virtual ~os_dyn_bag();

  static os_typespec* get_os_typespec(); 
}; /* class os_dyn_bag */

#ifdef _OS_PSE_COLL
_OS_END_NAMESPACE
#endif

#endif /* _COLL_DYN_BAG */
