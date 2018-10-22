/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _schftyps_h
#define _schftyps_h
#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>

/* Forward declarations */
struct _OS_schema_init_info;
class os_schema_handle;


/* The common base class of os_DLL_schema_info and os_application_schema_info. */
struct _OS_DLLIMPORT(_OS_CLIENT) os_schema_info {
public:	  /* Function members */
  const char* const* get_DLL_identifiers(os_unsigned_int32& count) const;
  os_schema_handle& get();
  const char* get_schema_database_pathname() const {
    return schema_db_file; }
  void set_schema_database_pathname(const char* new_pathname);

public: /* Data members */
  os_int32 id ; 
  os_int32 meta_schema_id ; 
  char *schema_db_file ; 
 
  // the number of types in the boot schema, serves as a quick check to 
  // determine whether the meta schema needs to be augmented 
  os_int32 number_of_types ; 
 
  _OS_schema_init_info * init_info ; 
};


/* Information in an application about its schema */
struct  _OS_DLLIMPORT(_OS_CLIENT) os_application_schema_info : public os_schema_info {
};


/* Information in a DLL (dynamic link library) about its schema */
struct _OS_DLLIMPORT(_OS_CLIENT) os_DLL_schema_info : public os_schema_info {
public:	  /* Function members */
  void add_DLL_identifier(const char* id);
  os_schema_handle* DLL_loaded(os_boolean load_DLL_schema_for_current_session_only = 0);
  os_schema_handle* DLL_loaded_global();
  os_schema_handle* DLL_loaded(const char* explicit_schema_database_path);
  void DLL_unloaded();
};


extern os_schema_info * _ODI_get_appschema_info();

#define __Application_schema_info _ODI_get_appschema_info()

extern void _ODI_set_appschema_info(os_schema_info *);

extern _OS_DLLIMPORT(_OS_CLIENT) const_after_preinit
os_schema_info __Bootstrap_schema_info ;

extern char *(__Boot_type_code_map[]) ;

#include <ostore/hdrend.hh>
#endif
