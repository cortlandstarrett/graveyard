/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _Scan_included
#define _Scan_included
#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

class os_collection;
class os_cursor;
class _Pset;
class _Pset_cursor;
class _Index_component;
class _Index_name;


class  _OS_COLL_IMPORT _Scan : public os_virtual_behavior
{
public:
  enum _Scan_implementation { PICK, SCAN, _Scan_implementation_pad = 1<<30 };

  _Scan(const os_collection&, _Index_name*,
	os_int32 /* os_collection::restriction */, void*,
	os_int32 /* _Scan_implementation */ imp = 0);
  _Scan(const os_collection&);
  _Scan(const os_collection&, _Index_name*, os_boolean user_def_type,
	os_int32 /* os_collection::restriction */, void*,
	os_int32 /* _Scan_implementation */ i,
	os_int32 term_step = 1,
	os_int32 type = 0);
  _Scan(const os_collection&, _Index_name*, os_boolean user_def_type,
	os_int32 /* os_collection::restriction */, void*,
	os_int32 /* os_collection::restriction */, void*,
	os_int32 /* _Scan_implementation */ i,
	os_int32 type = 0);
  virtual ~_Scan();

  os_unsigned_int32 cardinality() const;

  /* Reverse interpretation */
  _Scan& breakpoint(_Index_name*, os_int32 /* _Scan_implementation */);
  void breakpoint(os_int32);
  os_int32 empty() const;
  _Pset* materialize() const;
  void* materialize_pick() const;
  void go_to_same_depth(_Scan&);

  /* Iteration */
  void iteration_start();
  void next();
  void last();
  void previous();
  os_int32 null() const;
  os_int32 more() const;
  void* retrieve() const;

  /* Modification */
  void operator &=(_Scan&);
  void operator |=(_Scan&);
  void operator =(_Pset*);
  os_boolean convert_to_range_query(const _Scan*);

  static os_typespec* get_os_typespec();


private:
  os_collection* aggregate;
  os_int32 restricted;
  os_int32 terminal_step;
  os_int32 dml_query;
  os_int32 two_sided;
  _Scan_implementation implementation;
  os_collection* li_query_result;
  os_cursor* li_query_cursor;

  /* indexed */
  void* pick;
  _Pset* contents;
  void* pcurrent;
  _Index_component* step;
  os_collection_restriction key_restriction;
  void* key;
  os_collection_restriction lo_restriction;
  void* lo_key;
  os_collection_restriction hi_restriction;
  void* hi_key;

  /* unindexed */
  os_cursor* current;
};



template <class K>
class _Scan_K : public _Scan
{
private:
  K key;

public:
  _Scan_K(const os_collection& a, _Index_name* index,
	  os_int32 /* os_collection::restriction */ r, K const& k)
    : _Scan(a, index, r, (void*)&key),
      key(k)
    {}

  ~_Scan_K()
    {}
};

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
