/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _Index_name_included
#define _Index_name_included

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#endif

/* classes defined in this header are not used by PSE C++ */
#ifndef _OS_PSE_COLL 

/*---------------------------------------------------------------------- */
/*

_Index_name

_Index_name serves two purposes, 1) the obvious one, of naming
indexes, and 2) storing the collection element type as part of
_Indexes::requested_names. The right thing to do is to modify
_Indexes, but this would result in an incompatible schema.
As part of this, _Index_name::temporary is being turned into a
word of flags.

*/
/*---------------------------------------------------------------------- */

class _Index_component;
class _Path_step;
class _Pset;
class os_index_path;

#define _INDEX_NAME_FLAGS temporary

class _OS_COLL_IMPORT _Index_name
{
private:
  enum { TEMP = 0x1,
	 ETYPE = 0x2,
	 /* index options */
	 NO_DUPLICATES = 0x4,
         SIGNAL_DUPLICATES = 0x8,
	 POINT_TO_KEY = 0x10,
	 ORDERED = 0x20
       };

public:
  os_soft_pointer<char> LI_name;
  os_soft_pointer<char> DML_name;
  os_soft_pointer<_Index_component> terminus;
  os_soft_pointer<os_index_path> path;
  os_collection_ord_spec order;
  os_int32 temporary;

private:
  void check_real_index_name() const
    {
      if (_INDEX_NAME_FLAGS & ETYPE)
	err_coll_internal.signal("Attempt to use element type name as index name");
    }

public:

  enum _Index_status { PERMANENT, TEMPORARY, _Index_status_pad = 1<<30 };

  _Index_name(const _Path_step*, os_int32 index_options,
	      _Index_component * const, os_int32 /* _Index_status */);

  /* <external_use> indicates if the _Index_name is being created for */
  /* internal purposes or external use; by default, this constructor */
  /* creates a _Index_name for Internal use. */
  _Index_name(const _Index_name&, os_boolean external_use = 0);

  /* For storing name of element-type */
  _Index_name(const char*);

  ~_Index_name();

  /* Reverse interpretation */
  _Index_component* step() const
    { check_real_index_name(); return terminus; }

  void record_path(const os_index_path&);
  void record_options(os_int32 index_options);
  os_int32 options();

  const char* element_type_name() const
    { return (_INDEX_NAME_FLAGS & ETYPE) ? (const char*)DML_name : (const char*)0; }

  char* path_name() const;

  friend os_int32 compare(const _Index_name&, const _Index_name&);
  friend os_int32 compare(const _Index_name&, const os_index_path&);
  friend os_int32 compare(const os_index_path&, const _Index_name&);

  static os_typespec* get_os_typespec();
};

typedef _Index_name::_Index_status _Index_name_index_status;


class _OS_COLL_IMPORT os_index_name : private _Index_name {

public:

  os_index_name(const _Index_name& name);
  ~os_index_name();
  const char* LI_pathname();
  const char* DML_pathname();
  os_collection_ord_spec ordered();
  const os_index_path* associated_path();
  os_int32 get_options();
  char* get_path_name();
  const char* get_element_type_name() const;

  static os_typespec* get_os_typespec();

private:
  os_index_name& operator= (const os_index_name&);
};

#endif // not PSE C++

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif
