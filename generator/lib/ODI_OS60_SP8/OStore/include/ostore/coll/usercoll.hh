/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef os_USER_COLL_EXT
#define os_USER_COLL_EXT

#if !defined(_OS_PSE_COLL)

#include <ostore/hdrstart.hh>
#include <ostore/coll/coll.hh>

#else //defined(_OS_PSE_COLL)

#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/coll.hh>
_OS_BEGIN_NAMESPACE(os_pse)

#endif //defined(_OS_PSE_COLL)

class _OS_COLL_IMPORT os_coll_user_ext_cursor : public os_cursor {

public:

  os_coll_ptr& get_void0() { return void0; }
  os_coll_ptr& get_void1() { return void1; }
  os_unsigned_int32& get_uint0() { return os4u0; }
  os_unsigned_int32& get_uint1() { return os4u1; }
 
  os_coll_user_ext_cursor(const os_collection& c, os_int32 safety = 0)
    : os_cursor(c, safety) {}

  static os_typespec* get_os_typespec();

  void flag_dynamic_extent_cursor()
    { set_dynamic_extent_cursor(1); return; } 

    
};

class _OS_COLL_IMPORT os_coll_user_ext : public os_collection {
protected:
  
  /* -------------------------------------------------------------------- */
  /* Index functions                                                      */
  /* -------------------------------------------------------------------- */
  
  virtual _Indexes*& indexes();
  virtual os_int32 has_indexes() const;
  
protected:
  
  /* -------------------------------------------------------------------- */
  /* behavior protocol                                                    */
  /* -------------------------------------------------------------------- */
  
  virtual os_unsigned_int32 _get_behavior() const;

  
protected:
  
  /* -------------------------------------------------------------------- */
  /* Representation protocol                                              */
  /* -------------------------------------------------------------------- */
  
  
  /* return the name of the "most derived class" that implements the coll */
  virtual char *_rep_name() const;
  virtual os_int32 _rep_enum() const;
  
  virtual void _check_rep_invariants() const;
  
protected:
  
  /* -------------------------------------------------------------------- */
  /* the collections protocol                                             */
  /* -------------------------------------------------------------------- */
  
  virtual void* _pick() const;
  virtual void* _only() const;
  
  virtual void _insert(const void*);
  virtual os_int32 _remove(const void*);
  
  /* List-specific update and access protocol */
  virtual void _insert_first(const void* p);
  virtual void _insert_last(const void* p);
  /* these return true if the element was removed, modifies the argument to */
  
  virtual void* _retrieve(const os_cursor& c) const;
  virtual void* _retrieve(os_unsigned_int32 position) const;
  
  virtual void _insert_after(const void* p, const os_cursor& c);
  virtual void _insert_before(const void* p, const os_cursor& c);
  virtual void _remove_at(const os_cursor& c);
  virtual void* _replace_at(const void* p, const os_cursor& c);
  
  virtual void _insert_after(const void* p, os_unsigned_int32 position);
  virtual void _insert_before(const void* p, os_unsigned_int32 position);
  virtual void _remove_at(os_unsigned_int32 position);
  virtual void* _replace_at(const void* p, os_unsigned_int32 position);
  
  virtual os_int32 _contains(const void*) const;
  virtual os_int32 _count(const void*) const;

 /* unsuppoted functions */
  
  virtual os_int32 _remove_first(os_void_const_p &) ;
  virtual os_int32 _retrieve_first(os_void_const_p &) const;
  virtual os_int32 _retrieve_last(os_void_const_p &) const;
  virtual os_int32 _remove_last(os_void_const_p &) ;   
  
  
protected:
  
  /* -------------------------------------------------------------------- */
  /* cursor protocol                                                      */
  /* -------------------------------------------------------------------- */
  
  virtual os_int32 _first(os_cursor&, os_void_p &) const;
  virtual os_int32 _last(os_cursor&, os_void_p &) const;
  virtual os_int32 _next(os_cursor&, os_void_p &) const;
  virtual os_int32 _previous(os_cursor&, os_void_p &) const;

  /* introduced by os_collection internal */
  virtual void register_cursor(os_cursor&);
  virtual void unregister_cursor(os_cursor&);

protected:
  
  /* -------------------------------------------------------------------- */
  /* other odds and ends                                                  */
  /* -------------------------------------------------------------------- */
  
  virtual void _clear();
  virtual os_unsigned_int32 _cardinality() const;
  virtual os_int32 _empty() const;
  virtual os_boolean _fast_count() const;
  virtual os_unsigned_int32  _update_cardinality();
  virtual os_unsigned_int32 _cardinality_estimate() const;
  virtual os_int32 _cardinality_is_maintained() const;

public:
  
  os_coll_user_ext() {}
  virtual ~os_coll_user_ext();

  static os_typespec* get_os_typespec();
  
private:
  
  virtual void evolve_rep();
  
};

class _OS_COLL_IMPORT os_coll_user_ext_ix : public os_coll_user_ext 
{
private:
   _Indexes * ixs;  

protected:
  
  /* -------------------------------------------------------------------- */
  /* Index functions                                                      */
  /* -------------------------------------------------------------------- */

  virtual _Indexes*& indexes();
  virtual os_int32 has_indexes() const;

public:
  
  os_coll_user_ext_ix() { ixs = NULL; }
  virtual ~os_coll_user_ext_ix();

protected:
  
  /* -------------------------------------------------------------------- */
  /* behavior protocol                                                    */
  /* -------------------------------------------------------------------- */
  
  virtual os_unsigned_int32 _get_behavior() const;

protected:
  /* -------------------------------------------------------------------- */
  /* other odds and ends                                                  */
  /* -------------------------------------------------------------------- */
  
  virtual os_unsigned_int32 _cardinality() const;

public:
  static os_typespec* get_os_typespec(); 
};

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif


