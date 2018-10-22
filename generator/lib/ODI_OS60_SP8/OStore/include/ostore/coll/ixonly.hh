/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _COLL_IXONLY
#define _COLL_IXONLY

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#include <ostore/coll/coll.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/coll.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

/*****************************************************************************
* 									     *

*****************************************************************************/

/******************************************************************************/
/******************************************************************************/

class _OS_COLL_IMPORT os_ixonly : public os_collection {

protected:
  _Indexes * index_info;
  os_unsigned_int32 	card;
  os_boolean destroyed_flag;
  os_boolean maintain_card;
  os_boolean dups;
  os_unsigned_int32 unused;
  os_unsigned_int32 reserved1;
  os_coll_ptr reserved2;

protected:

  virtual void _remove_at(const os_cursor &c) ;
  virtual void _remove_at(os_unsigned_int32);
  virtual void* _retrieve(const os_cursor& c) const;
  virtual void* _retrieve(os_unsigned_int32) const;

protected:
  /* collection implementation protocol */
  virtual void* _pick() const;
  virtual void* _only() const;

  virtual void _insert(os_void_const_p value);
  virtual os_int32 _remove(os_void_const_p value);
  virtual os_int32 _contains(os_void_const_p) const;
  virtual os_int32 _count(os_void_const_p) const;

  void _clear() ;
  
  os_int32 _maintain_cursors() { return 0; };

  /* these will both raise exceptions */
  virtual void register_cursor(os_cursor&);
  virtual void unregister_cursor(os_cursor&);

  virtual os_int32 _first(os_cursor&, os_void_p &) const ;
  virtual os_int32 _last(os_cursor&, os_void_p &) const ;
  virtual os_int32 _next(os_cursor&, os_void_p &) const ;
  virtual os_int32 _previous(os_cursor&, os_void_p &) const ;

  virtual os_unsigned_int32 _update_cardinality();
  virtual os_unsigned_int32 _cardinality_estimate() const;
  virtual os_int32 _cardinality_is_maintained() const;


public:
  os_ixonly(os_boolean duplicates = 0, 
            os_boolean maintain_cardinality = 0);
  virtual ~os_ixonly();
  void _destroy() ;

  /* assignment operators are not inherited, so supply one */
  os_ixonly& operator =(const os_ixonly& c)
    {
      return (os_ixonly&) _assign(c);
    }
  os_ixonly& operator =(const os_collection& c)
    {
      return (os_ixonly&) _assign(c);
    }
  os_ixonly& operator =(const void* e)
    {
      return (os_ixonly &) _assign(e);
    }

  operator os_int32() const { return card != 0 ; }

  os_unsigned_int32 _cardinality() const;
  os_int32 _empty() const;

  os_unsigned_int32 _get_behavior() const;
  
  virtual void _set_untransformed(os_boolean flag);

public:
  /* representation protocol */
  void _check_rep_invariants() const {}
  char *_rep_name() const;
  os_int32 _rep_enum() const;

  /* normalize the cursor to an implementation independent form */
  virtual void normalize_cursor(os_cursor &) const {};
  /* convert it back os_int32o it's implementation specific form */
  virtual void denormalize_cursor(os_cursor &) const {};

  /* For queries of the form [: this == foo :] */
  os_boolean _fast_count() const;

  static os_typespec* get_os_typespec();

protected:
  virtual os_int32 has_indexes() const;
  _Indexes*& indexes();
  os_boolean destroyed() const
    { return destroyed_flag; }
  void mark_destroyed() 
    { destroyed_flag = 1; };
  void clear_destroyed ()
    { destroyed_flag = 0; }

  /* Transformation during schema evolution */
  virtual void evolve_rep() {};

public:
  /* unsuppoted update functions */
  virtual void _insert_first(os_void_const_p) ;
  virtual void _insert_last(os_void_const_p);
  virtual void _insert_after(os_void_const_p, const os_cursor&);
  virtual void _insert_before(os_void_const_p, const os_cursor&) ;
  virtual os_int32 _remove_first(os_void_const_p &) ;
  virtual os_int32 _remove_last(os_void_const_p &) ;
  virtual void _insert_after(os_void_const_p p, os_unsigned_int32 position) ;
  virtual void _insert_before(os_void_const_p p, os_unsigned_int32 position) ;
  virtual void* _replace_at(os_void_const_p p, const os_cursor& c) ;
  virtual void* _replace_at(os_void_const_p p, os_unsigned_int32 position) ;
  virtual os_int32 _retrieve_first(os_void_const_p &) const;
  virtual os_int32 _retrieve_last(os_void_const_p &) const;
 
};




/******************************************************************************/
/******************************************************************************/



#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
