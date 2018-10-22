/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _QUERY_RUNTIME
#define _QUERY_RUNTIME
#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
_OS_BEGIN_NAMESPACE(os_pse)
#include <os_pse/psecoll/hdrstart.hh>
#endif

/* qrun.hh -- various things that have to be in the
   compilation environment for queries. */

/* Someday this define will be optional */
/* #define DEBUGGING_QUERIES */

#ifdef DEBUGGING_QUERIES
extern "C" char * demangle (char *);
#endif

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrsys.hh>
#include <stdio.h>
#include <ostore/hdrend.hh>
#else
#include <stdio.h>
#endif

class _Query_runtime {
  public:
    static void error (const char *, ...);
    enum _Query_runtime_trace_level 
	{ os_qrtl_none, os_qrtl_function, os_qrtl_detail, os_qrtl_dump,
	  _Query_runtime_trace_level_pad = 1<<30 };
    static void set_trace_level (os_int32 /* _Query_runtime_trace_level */);
#ifdef DEBUGGING_QUERIES	
    static os_int32 do_trace (os_int32 /* _Query_runtime_trace_level */ l);
#else
    static os_int32 do_trace (os_int32 /* _Query_runtime_trace_level */) { 	return 0; }
#endif

#ifdef  DEBUGGING_QUERIES
    static enum _Query_runtime_strategy_check 
	{ s_none,
	  s_node,
	  s_node_coll,
	  _Query_runtime_strategy_check_pad = 1<<30
	  } strategy_check;
    static collection const * check_collection;
    static os_int32 check_node_id;
    static os_int32 check_l_lookup;
    static os_int32 check_r_lookup;
    static os_int32 check_made;
    static void check_strategy (collection const&,void*,os_int32,os_int32);
    static char * de_mangle (char * cs) { return demangle (cs); };
#endif
};

typedef _Query_runtime::_Query_runtime_trace_level _QR_runtime_trace_level;

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif
