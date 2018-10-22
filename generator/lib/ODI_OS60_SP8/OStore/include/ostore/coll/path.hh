/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _Path_included
#define _Path_included
#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

#ifndef _MAPPING_FUNCTIONS
#define _MAPPING_FUNCTIONS
typedef os_int32 (*_Rank_fcn)(os_void_const_p, os_void_const_p);
typedef os_unsigned_int32 (*_Hash_fcn)(os_void_const_p);
#endif
typedef void (*_Gateway_Path)();

class os_list;
class _Path_step;
class _OS_schema;
class _Ipset;
class ossql_gateway;
class ossql_path;

class _OS_COLL_IMPORT os_index_path
{
  friend class _Index_tree;

private:
  os_soft_pointer<os_list> steps;  /* <_Path_step*> */
  os_soft_pointer<char> LI_pathname;
  os_soft_pointer<char> DML_pathname;
  os_int32 multivalued;

  void initialize_with_step(const _Path_step&);
  void append_step(const _Path_step&);

public:
  static os_index_path& create(const char * element_type,
			    const char *path_string,
			    const os_database *);
  static os_index_path& create(const char * element_type,
			    const char *path_string,
			    const os_segment *);
  static os_index_path& create(const char * element_type,
			    const char *path_string,
			    const void *);
  static os_index_path& _create(const char * element_type,
				const char * path_string,
				_OS_schema *, os_collection * dm_type_strs);

 
  static void destroy(os_index_path& p) { delete (os_index_path*)&p; }

  /* method to evaluate path steps for gateway interface */
  static ossql_path& get_ossql_path();

  /* build path */
  os_index_path();
  os_index_path(const _Path_step&);
  os_index_path(_Path_step*);  /* consumes input */
  os_index_path(const os_index_path&);
  os_index_path& concatenate (const _Path_step&);
  os_index_path& concatenate (_Path_step*);  /* consumes input */
  os_index_path& concatenate (os_index_path&);
  friend inline os_index_path& concatenate (os_index_path&, os_index_path&);
  friend os_index_path& concatenate (const _Path_step&, const _Path_step&);
  friend os_index_path& concatenate (_Path_step*, _Path_step*);
  /* consumes inputs */

  os_index_path& _set_element_type_name(const char*);
  void _set_gateway_path();
  const char* _element_type_name() const;
  
  /* for internal use only */
  void _get_terminal_step_info(os_char_const_p * keytype, _Rank_fcn* rfn = 0,
			       _Hash_fcn* hfn = 0);

  void operator =(const os_index_path&);

  ~os_index_path();


  enum
    {
      is_multivalued = 1 << 0,
      is_gateway_path = 1 << 1,
      /* append_step() now only uses or set 1 bit of multivalued */
      /* branching() checks for 1st bit, gateway_path() checks for 2nd */ 

      is_multistep_path = 1 << 3
      /* A path is multi-step when it contains at least one _Deref, _Deset, */
      /* _Fn_deref, or _Fn_deset. */         
    }; 
 
  const char* LI_name() const
    { return LI_pathname; }
  const char* DML_name() const
    { return DML_pathname; }
  os_int32 branching() const
    { return (multivalued & is_multivalued) ; }
  os_int32 gateway_path() const
    { return (multivalued & is_gateway_path) ; }
  os_int32 keeping_deref() const
    { return keep_deref; }
  os_list * get_steps() const
    { return steps; }
  os_unsigned_int32 terminates_with_id() const;

  os_boolean is_multistep() const
    { return (multivalued & is_multistep_path) ; }

  _Path_step* get_terminal_pathstep() const;

  /* Compare paths (for EQ, NE). */
  friend os_int32 compare(const os_index_path&, const os_index_path&);


  enum
    {
      ordered =             1 << 0,
      no_duplicates =       1 << 1,
      signal_duplicates =   1 << 2,
      point_to_key =        1 << 3,
      use_references =      1 << 4,
      index_on_pointer_target =     1 << 5,

      /* 1 << 31 reserved for use by collections, (see path_op.hh). */

      allow_duplicates = 0,
      unordered = 0,
      copy_key = 0
    };  /* Cross-reference: coll.hh, os_index_path_options */
 
  static os_typespec* get_os_typespec();

private:
  os_int32 keep_deref;

  friend class _Index_name;

public:
  void _interpret_ipset(_Ipset*);
};

#ifndef _LINGUIST_
inline os_index_path& os_coll_concatenate (os_index_path& p, const _Path_step& ps)
{
  return p.concatenate(ps);
}

inline os_index_path& os_coll_concatenate (os_index_path& p, _Path_step* ps)
{
  return p.concatenate(ps);
}

inline os_index_path& os_coll_concatenate (os_index_path& p1, os_index_path& p2)
{
  return p1.concatenate(p2);
}
#endif

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
