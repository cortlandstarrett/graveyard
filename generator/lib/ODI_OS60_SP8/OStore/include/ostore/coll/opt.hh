/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _Opt_included
#define _Opt_included
#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

#define _QUERY_STRING_BUFFER_SIZE 10000
#define _QUERY_MAX_N_NODES 100
#define _QUERY_MAX_NESTING 20

class _Index_name;

class _Index_info
{
public:
  _Index_name* _index;
  os_int32 lookup;
  os_int32 inhibited;
  void * query_this;
};


class _Query_node_info : public basic_undo
{
private:
  static char index_name_buffer[_QUERY_STRING_BUFFER_SIZE];
  static os_int32 index_name_buffer_size[_QUERY_MAX_NESTING];

public:
  /* Also used by rank(char*, char*, os_int32). See rank.hh */
  static os_int32 query_level;

private:
  os_int32 n_nodes;
  char* buffer_start;
  _Index_info indexes[_QUERY_MAX_N_NODES];

public:
  _Query_node_info(os_int32);
  ~_Query_node_info();

  _Index_info& operator [](os_int32 i)
    { return indexes[i]; }
  char* strip_suffix(char const *, os_int32);
};

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
