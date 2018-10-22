/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _Path_step_included
#define _Path_step_included
#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#endif

/* classes defined in this header are not used by PSE C++ */
#ifndef _OS_PSE_COLL

/*----------------------------------------------------------------------*/

/*
_Path_step

_Path_step serves two purposes, 1) the obvious one, of
describing a step in an index path indexes, and 2) storing the
collection element type as part of os_index_path::steps. The
right thing to do is to modify os_index_path, but this would
result in an incompatible schema.  As part of this,
_Path_step::contribute_to_name is being turned into a word of
flags.

*/

/*----------------------------------------------------------------------*/

#define _PATH_STEP_FLAGS contribute_to_name

class os_dictionary;
class _Pset;
class _Index_component;
class os_index_path;
class _Ipset;


class _OS_COLL_IMPORT _Path_step
{
  friend class os_index_path;
  friend class _Index_name;
  friend class _Index_tree;
  friend class _Index_component;
  friend class os_collection;
  friend class _Ipset;
public:
  enum
    {
      dont_use_name = 0x0,
      use_name = 0x1,
      element_type = 0x2,
      fn_path_step = 0x4
    };

private:
  os_soft_pointer<_Path_op> opcode;
  os_soft_pointer<char> field_name;
  os_soft_pointer<char> LI_path_name_so_far;
  os_soft_pointer<char> DML_path_name_so_far;
  os_unsigned_int32 contribute_to_name;

public:
  _Path_step(_Path_op*, char const *, os_unsigned_int32 = dont_use_name);
  _Path_step(_Path_op*, os_unsigned_int32 = dont_use_name);
  _Path_step(_Path_step* const);
  _Path_step(_Path_step&);

  /* For element type name */
  _Path_step(const char*);

  ~_Path_step();

private:
  /* string description, for identification purposes */
  void LI_description(char *) const;
  void DML_description(char *) const;

public:
  char* LI_partial_path_name() const
    { return (_PATH_STEP_FLAGS & element_type) ? (char *) 0 : (char *)LI_path_name_so_far; }
  char* DML_partial_path_name() const
    { return (_PATH_STEP_FLAGS & element_type) ? (char *) 0 : (char *)DML_path_name_so_far; }
  char* element_type_name() const
    { return (_PATH_STEP_FLAGS & element_type) ? (char *)DML_path_name_so_far : (char *) 0; }
  os_unsigned_int32 interesting() const
    { return _PATH_STEP_FLAGS & use_name; }
  _Path_op * get_op() const
    { return opcode; }
  char* get_field_name() const
    { return field_name; }
  void reset_offset(const _Path_step& p)
    { opcode->reset_offset(*p.opcode); }
  os_int32 backptr_offset() const
    { return opcode->data_member_to_backptr(); }

private:
  /* Return a new, empty inverse mapping for this step, */
  /* or NULL if none needed. */
  os_dictionary* inverse_mapping(_Pset& p, _Index_component* n,
			    os_int32 index_properties,
			    const void* where, _Coll_clustering clust, os_collection *cc) const
    { return opcode->inverse_mapping(p, n, index_properties, where, clust, cc); }

  /* added to support os_ixonly */
  void _interpret_singleton(void* v, void *&val) const {
    if (opcode) {
      opcode->_interpret_singleton(v, val);
    } 
    else
      val = v;
  }

  /* Step interpretation. */
  void interpret(_Pset& p) const
    { opcode->interpret(p); }
  void interpret_and_disassociate(_Pset& p, const _Index_component* inv) const
    { opcode->interpret_and_disassociate(p, inv); }
  void terpretni(_Pset& p, os_dictionary const * const inv) const
    { opcode->terpretni(p, inv); }
  void terpretni(_Pset& p, os_dictionary const * const inv,
		 os_int32 /* os_collection::restriction */ r,
		 void* k, os_collection* c) const
    { opcode->terpretni(p, inv, r, k, c); }
  void terpretni(_Pset& p, os_dictionary const * const inv,
		 os_int32 /* os_collection::restriction */ r_lo, void* k_lo,
		 os_int32 /* os_collection::restriction */ r_hi, void* k_hi,
		 os_collection* c) const
    { opcode->terpretni(p, inv, r_lo, k_lo, r_hi, k_hi, c); }
  void* terpretni(void* p, os_dictionary const * const inv, os_unsigned_int32& found) const
    { return opcode->terpretni(p, inv, found); }
  void* terpretni_pick(os_dictionary* m, os_int32 /* os_collection::restriction */ r,
		       void* k, os_collection* c, os_unsigned_int32& found) const
    { return opcode->terpretni_pick(m, r, k, c, found);  }
  void* terpretni_pick(os_dictionary* m,
		       os_int32 /* os_collection::restriction */ r_lo, void* k_lo,
		       os_int32 /* os_collection::restriction */ r_hi, void* k_hi,
		       os_collection* c, os_unsigned_int32& found) const
    { return opcode->terpretni_pick(m, r_lo, k_lo, r_hi, k_hi, c, found);  }
  void forget(_Pset& unreachable, _Index_component* const inv,
	      _Pset*& next_unreachable,
	      os_int32& starting_offset, os_collection * cc) const
    { opcode->forget(unreachable, inv, next_unreachable, starting_offset, cc); }
  void remember(_Pset& reachable, _Index_component* const inv,
		_Pset*& next_reachable,
		os_int32& starting_offset, os_collection * cc) const
    { opcode->remember(reachable, inv, next_reachable, starting_offset, cc); }

  friend os_int32 compare(const _Path_step* p1, const _Path_step* p2);

  friend class os_index_path;
public:
  static os_typespec* get_os_typespec();
};

#endif // not PSE C++

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
