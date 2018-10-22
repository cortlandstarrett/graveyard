/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _OS_MAN_SCHEMA
#define _OS_MAN_SCHEMA
#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>

/* macros used to mark a type as persistent in the schema
   when doing batch schema maintenance */


#if (defined(_ODI_OSSG_))
class _odi_manschem_r4_ { };

#if (defined(_ODI_EDGFE_))

template<int I> class __sfic {};

#define OS_MARK_SCHEMA_TYPE(type) void __os_persist(type*);
#define OS_MARK_SCHEMA_TYPESPEC(type) void __os_persist type;

#define OS_SCHEMA_DLL_ID(string) void __os_schema_dll_id(__sfic< __LINE__ >, char* v = string);
#define OS_REPORT_DLL_LOAD_AND_UNLOAD(value) void __os_report_dll_load_unload(__sfic< __LINE__ >, int v = value);
#define OS_SCHEMA_INFO_NAME(name) void __os_schema_info_name( __sfic< __LINE__ >, char* name);

#else
#define OS_MARK_SCHEMA_TYPE(type) OS_MARK_SCHEMA_TYPESPEC((type))
/* Do the real work in OSSG: */
#define OS_MARK_SCHEMA_TYPESPEC(type) __os_persist type;
#define OS_SCHEMA_DLL_ID(string) __os_schema_dll_id (string);
#define OS_REPORT_DLL_LOAD_AND_UNLOAD(value) __os_report_dll_load_unload (value);
#define OS_SCHEMA_INFO_NAME(name) __os_schema_info_name (name);
#endif

#else

/* If compiling with a third-party compiler, just do nothing. */
#define OS_MARK_SCHEMA_TYPE(type)
#define OS_MARK_SCHEMA_TYPESPEC(type)
#define OS_SCHEMA_DLL_ID(string)
#define OS_REPORT_DLL_LOAD_AND_UNLOAD(value)
#define OS_SCHEMA_INFO_NAME(name)

#endif /* if (defined(_ODI_OSSG_)) */

#include <ostore/hdrend.hh>
#endif /* #ifndef _OS_MAN_SCHEMA */
