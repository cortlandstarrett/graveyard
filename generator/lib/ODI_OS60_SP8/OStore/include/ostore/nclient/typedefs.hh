/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_TYPEDEFS
#define CLIENT_INTERFACE_TYPEDEFS 1

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>

/* forward declarations and typedefs for the ObjectStore client API */
class objectstore_object_count;
class os_as_interval;
class os_cluster;
class os_database;
class os_database_root;
class os_notification;
class os_pathname_and_segment_number;
class os_segment;
class os_segment_access;
class os_server;
class os_session;
class os_type;
class os_typespec;

enum os_fetch_policy {os_fetch_page, os_fetch_stream, os_fetch_cluster, 
			os_fetch_segment = os_fetch_cluster, 
			os_fetch_policy_pad = 1<<30};

typedef objectstore_object_count* objectstore_object_count_p;
typedef os_as_interval* os_as_interval_p;
typedef os_database* os_database_p;
typedef os_database_root* os_database_root_p;
typedef os_notification* os_notification_p;
typedef os_cluster* os_cluster_p;
typedef os_pathname_and_segment_number* os_pathname_and_segment_number_p;
typedef os_segment* os_segment_p;
typedef os_segment** os_segment_p_p;
typedef os_segment_access* os_segment_access_p;
typedef os_server* os_server_p;
typedef os_type const* os_type_const_p;

typedef void (*os_simple_auth_ui_t) (os_void_p, os_char_const_p, os_char_p,
				     os_int32, os_char_p, os_int32);

typedef void (*objectstore_delete_function)(os_void_p);
typedef os_void_p (*os_missing_dispatch_table_handler_function)
    (os_char_const_p dispatch_table_identifier, os_char_const_p dispatch_table_symbol);

typedef void (*_ODI_rph_retp)(os_void_p,os_unsigned_int32,os_void_p,os_unsigned_int32,os_database_p);

/* declarations for access hooks */
/* TBD: we can't support access hooks in their current form, find a
   replacement */
enum os_access_reason {os_reason_accessed, os_reason_committed,
		       os_reason_aborted, os_reason_returned,
		       os_access_reason_pad = 1<<30};

typedef void (*os_access_hook)(os_void_p, enum os_access_reason, os_void_p,
			       os_void_p, os_void_p);

/* For DLL Schema */
typedef void (*os_autoload_DLLs_function)(os_database* db);

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_TYPEDEFS */
