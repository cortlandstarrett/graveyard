/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#include <ostore/hdrstart.hh>

/* signaled when there is no schema associated with the database */

/* general MOP error */
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_mop) ;

_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_no_schema) ;
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_no_database_schema) ;
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_no_comp_schema) ;
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_no_app_schema) ;
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_schema_not_loaded) ;
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_schema_not_found) ;
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_invalid_for_application_schema) ;
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_cannot_open_DLL_schema) ;
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_transient_dope_damaged) ;


/* an improper cast operation was attempted on a meta object */
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_mop_illegal_cast) ;

/* the protocol could not be supported bya a forward definition */
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_mop_forward_definition) ;

/* exception raised when creating a schema with circular dependencies */
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_mop_cyclic_graph) ;

/* exception raised when neutralizing a schema and it cannot be neutralized*/
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_mop_cannot_neutralize) ;

/* exception raised when creating a schema which is not neutral */
_OS_DECLARE_EXCEPTION(_OS_CLIENT,err_mop_not_neutral) ;

#include <ostore/hdrend.hh>
