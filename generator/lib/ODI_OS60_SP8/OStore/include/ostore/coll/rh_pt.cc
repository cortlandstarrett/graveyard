/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _AM_RH_PT_CC
#define _AM_RH_PT_CC

/* ---------------------------------------------------------------------
 * Include files
 * ------------------------------------------------------------------ */
#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#include <ostore/coll/rh_pt.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/coll/rh_pt.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif



/* ---------------------------------------------------------------------
 * Macro definitions
 * ------------------------------------------------------------------ */

#define OS_COLL_RHASH_NULL_SLOT  ~(os_unsigned_int32)0
#define OS_COLL_RHASH_NULL_TABLE ~(os_unsigned_int32)0

/* ---------------------------------------------------------------------
 * Member functions of _Rhash_pt
 * ------------------------------------------------------------------ */

template<class KEYTYPE>
_Rhash_pt<KEYTYPE>::_Rhash_pt(const char* type, 
                              os_unsigned_int32 capacity,
                              os_unsigned_int32 options)
  : _Rhash(type, sizeof(_Dict_pt_slot<KEYTYPE>),
           sizeof(KEYTYPE), capacity, 
           _maintain_cardinality | _stores_overflow |
           (!(options & os_dictionary::no_dup_keys) ? _allow_dups : 0) |
           (options & os_dictionary::signal_dup_keys ? _idx_signal_dups : 0))
{
  _Rank_fcn rfn;
  _Hash_fcn hfn;
  os_dk_wrapper<KEYTYPE> dkw;
  if (!(os_dk_wrapper<KEYTYPE>::_functions(rfn, hfn))) {
     set_user_hash_fnc(0);
  }
  else if ((strcmp(dkw._type(),"char*")) == 0) {
     set_char_star_key(0);
  }
  else if ((strcmp(dkw._type(),"os_pvoid")) == 0) {
     set_os_pvoid_key(0);
  }  
 
}

template <class KEYTYPE> 
_Rhash_pt<KEYTYPE>::~_Rhash_pt()
{ destroy_index(); }

template<class KEYTYPE>
char* 
_Rhash_pt<KEYTYPE>::allocate_slots(
        os_unsigned_int32 _n_slots, os_cluster * cluster, void* with)
{
  if (cluster)
     return (char *) new (cluster, 
                          _Dict_pt_slot<KEYTYPE>::get_os_typespec(),
                          _n_slots) _Dict_pt_slot<KEYTYPE>[_n_slots];
  else
     return (char *) new (os_cluster::with(with), 
                          _Dict_pt_slot<KEYTYPE>::get_os_typespec(),
                          _n_slots) _Dict_pt_slot<KEYTYPE>[_n_slots];
}

template<class KEYTYPE>
void 
_Rhash_pt<KEYTYPE>::delete_slots(void* tbl)
{
  delete [] (_Dict_pt_slot<KEYTYPE>*)tbl;
}

template<class KEYTYPE>
void 
_Rhash_pt<KEYTYPE>::do_char_star_key_insert(void* ps, void * v, char** k, 
                                            os_unsigned_int32 h)
{
  os_int32 size = strlen(*k) + 1;
  char * nk = new (os_cluster::with(_key_type()), 
                   os_typespec::get_char(), size) char[size];
  strcpy(nk, *k);
  ((_Dict_pt_slot<KEYTYPE>*)ps)->insert(v, (KEYTYPE*) &nk, h);
}

template<class KEYTYPE> 
char* 
_Rhash_pt<KEYTYPE>::_rep_type() const
{ return (char*)"_Rhash_pt<class KEYTYPE>"; }

template<class KEYTYPE> 
void*
_Rhash_pt<KEYTYPE>::slot_key(const void* ps, os_unsigned_int32) const
{ return ((_Dict_pt_slot<KEYTYPE>*)ps)->get_key(); }

template<class KEYTYPE> 
void*
_Rhash_pt<KEYTYPE>::slot_value(const void* ps, 
                               const _Rhash_cursor* rc,
                               os_unsigned_int32 overflow) const
{
  if (overflow)
    return rc->get_oflo_current()->retrieve();
  else
    return ((_Dict_pt_slot<KEYTYPE>*)ps)->value();
}

template<class KEYTYPE> 
os_unsigned_int32
_Rhash_pt<KEYTYPE>::slot_hash(
	const void* ps, os_unsigned_int32 ) const
{
  return ((_Dict_pt_slot<KEYTYPE>*)ps)->key.hashval();
}

template<class KEYTYPE> 
os_boolean
_Rhash_pt<KEYTYPE>::slot_key_eq(
	const void* ps, os_unsigned_int32, const void* k, _Rank_fcn rfn ) const
{
  return (((_Dict_pt_slot<KEYTYPE>*)ps)->status(this,0,k,rfn) ==  _RH_KEY_MATCH); 

}

template<class KEYTYPE> 
void* 
_Rhash_pt<KEYTYPE>::slot_pick(const void* ps, os_unsigned_int32 overflow) const
{
  if (overflow)
    return ((_Dict_pt_slot<KEYTYPE>*)ps)->oflo_list()->pick();
  else
    return ((_Dict_pt_slot<KEYTYPE>*)ps)->value();
}

template<class KEYTYPE> 
os_boolean
_Rhash_pt<KEYTYPE>::slot_occupied(const void* s) const
{
  return (((_Dict_pt_slot<KEYTYPE>*)s)->status(this,1) == _RH_SLOT_OCCUPIED) 
         ? 1 : 0;  
}

template<class KEYTYPE> 
os_boolean
_Rhash_pt<KEYTYPE>::slot_first(
	const void* ps, _Rhash_cursor* rc, void*& v, 
        os_unsigned_int32 overflow) const
{
  _Dict_pt_slot<KEYTYPE>* psl = (_Dict_pt_slot<KEYTYPE>*)ps;
  if (overflow) {
    if (!rc->get_oflo_current())
      rc->set_oflo_current(new os_cursor(*psl->oflo_list()));
    else {
      if (rc->get_oflo_current()->owner() != psl->oflo_list())
	rc->get_oflo_current()->rebind(*psl->oflo_list());
    }

    v = rc->get_oflo_current()->first();
    return rc->get_oflo_current()->more();
  }
  else {
    os_boolean rv = _Rhash_pt<KEYTYPE>::slot_occupied(ps);
    if (rv)
      v = psl->value();
    return rv;
  }
}

template<class KEYTYPE> 
os_boolean
_Rhash_pt<KEYTYPE>::slot_last(
	const void* ps, _Rhash_cursor* rc, void*& v,
        os_unsigned_int32 overflow) const
{
  _Dict_pt_slot<KEYTYPE>* psl = (_Dict_pt_slot<KEYTYPE>*)ps;
  if (overflow) {
    if (!rc->get_oflo_current())
      rc->set_oflo_current(new os_cursor(*psl->oflo_list()));
    else {
      if (rc->get_oflo_current()->owner() != psl->oflo_list())
	rc->get_oflo_current()->rebind(*psl->oflo_list());
    }
    
    v = rc->get_oflo_current()->last();
    return rc->get_oflo_current()->more();
  }
  else {
    os_boolean rv = _Rhash_pt<KEYTYPE>::slot_occupied(ps);
    if (rv)
      v = psl->value();
    return rv;
  }
}

template<class KEYTYPE> 
os_boolean
_Rhash_pt<KEYTYPE>::slot_next(
	const void* ps, _Rhash_cursor* rc, void*& v, 
        os_unsigned_int32 overflow) const
{
  if (overflow) {
    v = rc->get_oflo_current()->next();
    return rc->get_oflo_current()->more();
  }
  else
    return 0;
}

template<class KEYTYPE> 
os_boolean
_Rhash_pt<KEYTYPE>::slot_previous(
	const void* ps, _Rhash_cursor* rc, void*& v,
        os_unsigned_int32 overflow) const
{
  if (overflow) {
    v = rc->get_oflo_current()->previous();
    return rc->get_oflo_current()->more();
  }
  else
    return 0;
}

template<class KEYTYPE> 
os_boolean
_Rhash_pt<KEYTYPE>::slot_null(const void* ps, const _Rhash_cursor* rc,
        os_unsigned_int32 overflow) const
{
  if (overflow)
    return rc->get_oflo_current()->null();
  else
    return !slot_occupied(ps);
}

template<class KEYTYPE>
os_int32 
_Rhash_pt<KEYTYPE>::slot_count(void* ps, os_unsigned_int32 overflow) const
{
  _Dict_pt_slot<KEYTYPE>* s = (_Dict_pt_slot<KEYTYPE>*)ps;
  if (overflow)
    return s->oflo_list()->cardinality();
  return slot_occupied(ps) ? 1 : 0;

}

template<class KEYTYPE> 
os_boolean
_Rhash_pt<KEYTYPE>::stores_overflow()
{ return 1; }

template<class KEYTYPE> 
void
_Rhash_pt<KEYTYPE>::slot_reclaim_oflo(void* ps,os_unsigned_int32 overflow)
{ 
  if (overflow)
    delete ((_Dict_pt_slot<KEYTYPE>*)ps)->oflo_list();
}

template <class KEYTYPE> 
_RH_slot_status
_Rhash_pt<KEYTYPE>::slot_status(
	void* ps, const void* k, _RH_search_type st, 
        _Rank_fcn rfn, os_unsigned_int32 h) const
{
  return ((_Dict_pt_slot<KEYTYPE>*)ps)->status(this, is_reorg(st), k, rfn, h);
}

template<class KEYTYPE> 
void
_Rhash_pt<KEYTYPE>::slot_assign(void* ps, const void* p )
{ ((_Dict_pt_slot<KEYTYPE>*)ps)->assign((_Dict_pt_slot<KEYTYPE>*)p); }


template<class KEYTYPE> 
os_boolean
_Rhash_pt<KEYTYPE>::slot_insert(
	void* ps, os_unsigned_int32 t, os_unsigned_int32 s, const void* v, 
	const void* k, os_unsigned_int32 h) 
{
  if (allow_dup()) {
    if (slot_occupied(ps)) {
      if (!(has_overflow(t,s))) {
	void * temp = ((_Dict_pt_slot<KEYTYPE>*)ps)->value();
	if (temp == v)
	  return 0;
	((_Dict_pt_slot<KEYTYPE>*)ps)->set_oflo( 
	  (new (os_cluster::with(this), os_list::get_os_typespec()) os_list));
	((_Dict_pt_slot<KEYTYPE>*)ps)->oflo_list()->insert(temp);
        set_overflow(t,s,1);
      }
      ((_Dict_pt_slot<KEYTYPE>*)ps)->oflo_list()->insert(v);
    }
    else {
      if (_is_char_star_key())
        do_char_star_key_insert(ps, (void*)v, (char**)k, h);  
      else
        ((_Dict_pt_slot<KEYTYPE>*)ps)->insert((void*)v, (KEYTYPE*)k, h);
    }
  }
  else
    if (_is_char_star_key()) 
      do_char_star_key_insert(ps, (void*)v, (char**)k, h); 
    else
      ((_Dict_pt_slot<KEYTYPE>*)ps)->insert((void*)v, (KEYTYPE*)k, h);

  return 1;
}

template<class KEYTYPE> 
void
_Rhash_pt<KEYTYPE>::slot_remove(
	void* ps, os_unsigned_int32 t, os_unsigned_int32 s, const void* v, 
	os_boolean& becomes_deleted) 
{
  if (has_overflow(t,s)) {
    ((_Dict_pt_slot<KEYTYPE>*)ps)->oflo_list()->remove(v);
    
    if (((_Dict_pt_slot<KEYTYPE>*)ps)->oflo_list()->cardinality() == 1) {
      void* temp = ((_Dict_pt_slot<KEYTYPE>*)ps)->oflo_list()->pick();
	
      delete ((_Dict_pt_slot<KEYTYPE>*)ps)->oflo_list();
      ((_Dict_pt_slot<KEYTYPE>*)ps)->set_value(temp);
      set_overflow(t,s,0);
    }
  }
  else {
    ((_Dict_pt_slot<KEYTYPE>*)ps)->make_deleted(this);
    becomes_deleted = 1;
  }
}

template<class KEYTYPE> 
os_boolean 
_Rhash_pt<KEYTYPE>::slot_contains(
	void* ps, os_unsigned_int32 overflow, const void* v ) const
{
  if (overflow)
    return((_Dict_pt_slot<KEYTYPE>*)ps)->oflo_list()->contains(v);
  else
    return ((_Dict_pt_slot<KEYTYPE>*)ps)->value() == v;
}

template <class KEYTYPE>
void 
_Rhash_pt<KEYTYPE>::find_functions(_Rank_fcn& rfn, _Hash_fcn& hfn) const
{
  os_boolean found_fnc = 0;
  if (!(use_user_hash_fnc())) {
    /* Avoid running the os_dk_wrapper ctor and dtor for soft_pointer 
       based keys which are very expensive.  */ 
     if (_is_char_star_key()) {
        rfn = _Str_rank; hfn = _Str_hash_khs; 
        found_fnc = 1;
     }
     else if (_is_os_pvoid_key()) {
        rfn = _Pvoid_rank; hfn = _Pvoid_hash;
        found_fnc = 1;
     }
     else {
        os_dk_wrapper<KEYTYPE> dkw;
        found_fnc = os_dk_wrapper<KEYTYPE>::_functions(rfn, hfn);
     }
  }    
  if (!found_fnc)
     _Mapping_fcn_cache->find_functions(_key_type(), rfn, hfn);
}

template<class KEYTYPE> 
os_unsigned_int32 
_Rhash_pt<KEYTYPE>::first_occupied_slot(os_unsigned_int32 r) const
{
  if (index()[r]->get_n_keys() == 0)
    return OS_COLL_RHASH_NULL_SLOT;

  os_unsigned_int32 s = 0;
  _Dict_pt_slot<KEYTYPE>* sl = (_Dict_pt_slot<KEYTYPE>*)index()[r]->contents();
  while (sl->status(this, 1) != _RH_SLOT_OCCUPIED) {
    sl++;
    s++;
  }
  return s;
}

template<class KEYTYPE> 
os_unsigned_int32 
_Rhash_pt<KEYTYPE>::last_occupied_slot(os_unsigned_int32 r) const
{
  if (index()[r]->get_n_keys() == 0)
    return OS_COLL_RHASH_NULL_SLOT;

  os_unsigned_int32 s = index()[r]->get_n_slots() - 1;
  _Dict_pt_slot<KEYTYPE>* sl = 
    &((_Dict_pt_slot<KEYTYPE>*)index()[r]->contents())[s];
  while (sl->status(this, 1) != _RH_SLOT_OCCUPIED) {
    sl--;
    s--;
  }
  return s;
}

template<class KEYTYPE> 
os_unsigned_int32 
_Rhash_pt<KEYTYPE>::next_occupied_slot(
	os_unsigned_int32 r, os_unsigned_int32 s ) const
{
  _Dict_pt_slot<KEYTYPE>* sl = 
    &((_Dict_pt_slot<KEYTYPE>*)index()[r]->contents())[s];
  do
    if (++s == index()[r]->get_n_slots()) {
      s = OS_COLL_RHASH_NULL_SLOT;
      break;
    }
  while ((++sl)->status(this, 1) != _RH_SLOT_OCCUPIED);
  return s;
}

template<class KEYTYPE> 
os_unsigned_int32 
_Rhash_pt<KEYTYPE>::previous_occupied_slot(
	os_unsigned_int32 r, os_unsigned_int32 s ) const
{
  _Dict_pt_slot<KEYTYPE>* sl = 
    &((_Dict_pt_slot<KEYTYPE>*)index()[r]->contents())[s];
  do {
    if (s-- == 0) {
      s = OS_COLL_RHASH_NULL_SLOT;
      break;
    }
    sl--;
  }
  while (sl->status(this, 1) != _RH_SLOT_OCCUPIED);
  return s;
}

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif /* _AM_RH_PT_CC */

