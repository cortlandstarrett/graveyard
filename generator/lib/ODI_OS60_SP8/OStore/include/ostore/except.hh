/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_
#include <ostore/hdrstart.hh>

/* except.hh: Macro and other stuff for cleaner exception handling in ObjectStore. */

#include <ostore/portypes.hh>
#include <ostore/tix.hh>

#if defined(_OS_MicrosoftCC)
#pragma warning(error : 4530)
#endif

#if defined(__STDC__)
#ifndef _OS_ANSI_TOKENS
#define _OS_ANSI_TOKENS
#endif
#endif

#ifdef _OS_ANSI_TOKENS

#define DEFINE_EXCEPTION(name,message,parent)		\
objectstore_exception name((char*)#name,message,parent)
#define INITIALIZE_EXCEPTION(name,message,parent)	\
  name._initialize((char*)#name,message,parent)

#define _OS_DECLARE_EXCEPTION(dll_name,name)			\
extern "C" dll_name##_IMPORT objectstore_exception name
 
#else
  
#define DEFINE_EXCEPTION(name,message,parent)		\
objectstore_exception name((char*)"name", message, parent)
#define INITIALIZE_EXCEPTION(name,message,parent)	\
  name._initialize((char*)"name", message, parent)

#define _OS_DECLARE_EXCEPTION(dll_name,name)			\
extern "C" objectstore_exception name
  
#endif /* _OS_ANSI_TOKENS */
  
#define DEFINE_EXCEPTION_NAMEONLY(name)			\
objectstore_exception name
#define DECLARE_EXCEPTION(name)				\
extern objectstore_exception name

#define _OS_DEFINE_EXCEPTION(name,message,parent)	\
extern "C" _OS_DLLEXPORT objectstore_exception name;	\
_OS_DLLEXPORT DEFINE_EXCEPTION(name,message,parent)

#define _OS_DEFINE_EXCEPTION_NAMEONLY(name)		\
extern "C" _OS_DLLEXPORT objectstore_exception name;	\
_OS_DLLEXPORT objectstore_exception name
  
class objectstore_exception : public tix_exception {
private:
  char *name;
public:

  objectstore_exception() : tix_exception() {};
  objectstore_exception(char *name_arg,
			char const *message_arg,
			tix_exception const *exception_arg)
  : tix_exception(message_arg, exception_arg)
  { name = name_arg; };

  objectstore_exception(char *name_arg,
			const _ODI_arg2 arg2,
			tix_exception const *exception_arg)
  : tix_exception(arg2, exception_arg)
  { name = name_arg; };

  void _initialize(char *name_arg,
		   const _ODI_arg2 arg2,
		   tix_exception const *exception_arg)
  { name = name_arg;
      tix_exception::_initialize(arg2, exception_arg);
  };    
  
  void signal(const _ODI_arg2 * arg2 ...);
  
  void _initialize(char *name_arg,
		   char const *message_arg,
		   tix_exception const *exception_arg)
    { name = name_arg;
      tix_exception::_initialize(message_arg, exception_arg);
    };

  void signal(char const *format ...);
  void signal(os_int32 value_arg, char const *format ...);

  void vsignal(char const *format, va_list args);
  void vsignal(os_int32 value_arg, char const *format, va_list args);
  objectstore_exception *derive(char const *format ...);
};

/* here are a couple of exceptions used everyplace, not just
   in the client. */

_OS_DECLARE_EXCEPTION(_OS_LOW,err_objectstore);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_restartable);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_internal);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_misc);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_nyi);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_charset);

_OS_DECLARE_EXCEPTION(_OS_LOW,err_not_supported);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_protocol_not_supported);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_operation_not_supported);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_operation_not_supported_on_failover_server);

/* DLL load/unload exceptions */
_OS_DECLARE_EXCEPTION(_OS_LOW,err_DLL);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_DLL_not_loaded);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_DLL_not_unloaded);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_DLL_symbol_not_found);

/* exceptions mapped to server errors in libsvrpc/con_rpc.cc */

_OS_DECLARE_EXCEPTION(_OS_LOW,err_awaiting_recovery);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_beyond_cluster_length);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_cache_manager_not_responding);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_deadlock);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_server_restarted);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_cluster_is_deleted);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_cross_server_rename);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_database_ESTALE);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_database_exists);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_database_id_exists);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_database_id_not_found);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_database_lock_conflict);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_database_not_found);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_db_already_open_exclusive);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_db_already_open_mvcc);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_db_already_open_non_mvcc);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_db_already_open_single_db_mvcc);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_db_already_open_multi_db_mvcc);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_db_cannot_change_open);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_db_cannot_open_exclusive);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_db_is_offline);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_db_going_offline);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_not_auth_db_kill);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_db_kill_clients_failed);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_mvcc_incoherent);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_directory_not_empty);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_directory_not_found);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_file_error);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_file_not_db);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_no_shrink_seg);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_file_not_local);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_inconsistent_db);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_invalid_pathname);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_invalid_rename);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_license_limit);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_link_not_found);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_log_data_segment_full);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_no_credentials);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_not_a_database);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_not_a_directory);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_not_a_link);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_permission_denied);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_locator_read_only);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_rawhfs_not_upgraded);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_read_only_file_system);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_segment_is_deleted);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_server_cannot_open_cache);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_server_cannot_talk_to_server);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_server_full);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_server_db_full);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_server_log_full);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_server_out_of_vm);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_server_not_superuser);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_no_rawfs);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_lock_timeout);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_too_many_links);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_too_many_cross_svr_links);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_cluster_full);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_server_refused_connection);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_failover_server_refused_connection);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_broken_server_connection);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_broken_failover_server_connection);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_file_pathname);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_conflicting_failover_configuration);

/* low level (tclient) errors */

_OS_DECLARE_EXCEPTION(_OS_LOW,err_trans);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_no_trans);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_no_query_trans);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_cannot_commit);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_database_is_deleted);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_database_not_open);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_database_not_open_update);

/* nclient errors */
_OS_DECLARE_EXCEPTION(_OS_LOW,err_prepare_to_commit);
_OS_DECLARE_EXCEPTION(_OS_LOW, err_write_during_query);
_OS_DECLARE_EXCEPTION(_OS_LOW, err_invalid_option_value);

/* locator file errors. */

_OS_DECLARE_EXCEPTION(_OS_LOW,err_locator_syntax);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_locator_file_io);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_locator_misc);

_OS_DECLARE_EXCEPTION(_OS_LOW,err_session);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_session_is_deleted);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_no_session);
_OS_DECLARE_EXCEPTION(_OS_LOW,err_wrong_session);

/* here are a few exceptions that are used internally */

_OS_DECLARE_EXCEPTION(_OS_LOW,err_level_1_io);

/* here is the exception for conveying lock timeout information */

enum os_lock_type {os_read_lock, os_write_lock, os_no_lock, os_lock_type_pad = 1<<30};

class os_lock_timeout_exception : public objectstore_exception { 
public:
  void *get_fault_addr();
  os_lock_type get_lock_type();
  os_int32 number_of_blockers();
  os_char_p *get_hostnames();
  os_pid *get_pids();
  os_char_p *get_application_names();
  os_lock_timeout_exception();
  ~os_lock_timeout_exception();
};

/* This is the exception for conveying deadlock information.
   It would share a base class with os_lock_timeout_exception
   if not for upward compatibility requirements in 6.0 sp1. */

class os_deadlock_exception : public objectstore_exception { 
public:
  void *get_fault_addr();
  os_lock_type get_lock_type();
  os_int32 number_of_blockers();
  os_char_p *get_hostnames();
  os_pid *get_pids();
  os_char_p *get_application_names();
  os_deadlock_exception();
  ~os_deadlock_exception();
};

#include <ostore/hdrend.hh>
#endif







