/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_SCHEMA_HANDLE
#define CLIENT_INTERFACE_SCHEMA_HANDLE

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>

struct os_schema_info;
class os_database;
class os_app_schema;
class os_schema;

enum os_schema_handle_status {
  os_schema_handle_unloaded = 0,
  os_schema_handle_loaded = 1,
  os_schema_handle_queued_to_load = 2,
  os_schema_handle_queued_to_unload = 3,
  os_schema_handle_status_enum_pad = 1<<30 };   /* force 4-byte size */

/* Transient handle to a program schema,
 * which can be either a DLL schema or an application schema.
 * This is an abstract base class, the real class is a subclass.
 *
 * This class is defined even if defined(DISABLE_DLL_SCHEMA),
 * because it is also used for the application schema.
 */
class _OS_DLLIMPORT(_OS_CLIENT) os_schema_handle {
public:	  /* Function members */
  os_schema_handle_status get_status() const;
  os_schema_info& get_schema_info() const;
  os_database& get_schema_database() const;
  const os_app_schema& get() const;
  const char* const* get_DLL_identifiers(os_unsigned_int32& count) const;
  void insert_required_DLL_identifiers(os_database& db);
  const char* get_schema_database_pathname() const;
  void set_schema_database_pathname(const char* path);
  void DLL_unloaded();

  static os_schema_handle* get_application_schema_handle();
  static os_schema_handle** get_all(os_boolean to_load = 0 /* false */);
  static os_schema* get_unified_program_schema();
  
protected:  /* Abstract class */
  os_schema_handle() { };
};

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_SCHEMA_HANDLE */
