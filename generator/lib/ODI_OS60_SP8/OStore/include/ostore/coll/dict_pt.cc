/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_COLL_os_Dictionary_cc
#define _OS_COLL_os_Dictionary_cc
#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#include<ostore/ostore.hh>
#include<ostore/coll/coll.hh>
#include <ostore/coll/dict_pt.hh>
#include <ostore/coll/rh_pt.hh>
#include <ostore/coll/rh_pt.cc>
#include<ostore/coll/osbtree.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include<os_pse/ostore.hh>
#include<os_pse/coll/coll.hh>
#include<os_pse/coll/dict_pt.hh>
#include<os_pse/coll/rh_pt.hh>
#include<os_pse/coll/rh_pt.cc>
#include<os_pse/coll/osbtree.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif


/* ---------------------------------------------------------------------
 * Member functions of os_Dictionary
 * ------------------------------------------------------------------ */

template<class KT, class VT>
os_Dictionary<KT,VT>::os_Dictionary(os_unsigned_int32 expected_cardinality,
	                                  os_unsigned_int32 behavior)
{ 
  allocate_coll(expected_cardinality, behavior);
 
}

template<class KT, class VT>
os_Dictionary<KT,VT>::os_Dictionary(os_Dictionary<KT,VT > &d)
{
   allocate_coll(d.cardinality(), d.get_behavior());
   os_cursor c(d);
   os_address_space_marker asmarker;
   for (c.first(asmarker); c.more(); c.next(asmarker))
      insert(d.retrieve_key(c), d.retrieve(c));
}


template<class KT, class VT>
void
os_Dictionary<KT,VT>::allocate_coll(os_unsigned_int32 expected_cardinality,
	                            os_unsigned_int32 behavior)
{ 
  // Generate an rhash or btree for unordered/ordered dictionaries
  if (behavior & maintain_key_order) {
#ifndef _OS_PSE_COLL
    os_typespec btree_type("os_btree");
#else
    os_typespec& btree_type = *(os_ts<os_btree>::get());
#endif
    _coll = (os_dictionary*)
         new(os_cluster::with(this), &btree_type)
         os_btree(
		this->_key_type(), 
		sizeof(KT), 
		1, 
		behavior >> os_dictionary::index_option_rightshift, 
		expected_cardinality );
  }
  else {
    _coll = (os_dictionary*)
         new(os_cluster::with(this), _Rhash_pt<KT>::get_os_typespec()) 
        _Rhash_pt<KT>(this->_key_type(), expected_cardinality, behavior); 
  }
     
}
template<class KT, class VT>
void os_Dictionary<KT,VT>::find_functions(_Rank_fcn& rf, _Hash_fcn& hf) const
{
  os_dk_wrapper<KT> dkw;
  if (!os_dk_wrapper<KT>::_functions(rf, hf))
    _Mapping_fcn_cache->find_functions(dkw._type(), rf, hf);
}


template<class KT,class VT>
const char* os_Dictionary<KT,VT>::_key_type() const
{
  return os_dk_wrapper<KT>::_type();
}

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif /* _OS_COLL_os_Dictionary_cc */

