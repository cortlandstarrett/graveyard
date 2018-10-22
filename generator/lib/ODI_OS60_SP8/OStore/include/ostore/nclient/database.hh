/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_DATABASE
#define CLIENT_INTERFACE_DATABASE 1

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/os_int64.hh>
#include <ostore/nclient/typedefs.hh>
#include <ostore/nclient/objstore.hh>
#include <ostore/facade.hh>

class os_typespec;
class os_session;

class _OS_DLLIMPORT(_OS_CLIENT) os_database : public os_facade
{
public:
  void operator delete(void*); 

  static os_database * const get_transient_database();
  os_boolean is_transient_database() const;

  os_database *get_schema_database() const;
  void set_schema_database(os_database& schema_database);

  char *get_pathname() const;

  void affiliate(const os_database* target_db, 
                 os_boolean deep = 0,
                 os_boolean relative = 1,
                 const char* common_parent = (const char*)NULL);
  void change_affiliation(os_unsigned_int16 index,
                          const os_database* target_db,
                          os_boolean relative = 1,
                          const char* common_parent = (const char*)NULL);
  char* get_path_to(const os_database* target_db) const;
  os_unsigned_int16 get_affiliation_index_of(const os_database* target_db) const;
  os_boolean has_affiliation_to(const os_database* target_db) const;
  void get_affiliated_databases(os_int32 &n_databases,
                                os_database**& databases) const;

  enum open_modes {
    not_open,
    open_for_update,
    open_for_read_only,
    open_for_mvcc,
    open_for_multi_db_mvcc,
    open_modes_pad = 1<<30
  };
  open_modes get_open_mode() const;
  os_boolean is_open() const;
  os_boolean is_open_update() const;
  os_boolean is_open_read_only() const;
  os_boolean is_open_mvcc() const;
  os_boolean is_open_single_db_mvcc() const;
  os_boolean is_open_multi_db_mvcc() const;

  static os_int32 get_n_databases();
  static void get_all_databases(os_int32 max_databases,
                                os_database** databases,
                                os_int32& n_databases);

  void open(os_boolean read_only = 0);
  void open_mvcc();
  void open_multi_db_mvcc();
  void close(os_boolean force = 0);

  static os_database *lookup(const char *pathname, os_int32 create_mode = 0);
  static os_database *open_mvcc(const char *pathname);
  static os_database *open_multi_db_mvcc(const char *pathname);
  static os_database *open(const char *pathname, os_boolean read_only = 0,
			   os_int32 create_mode = 0,
			   objectstore::segment_reference_policy
			     new_segment_reference_policy =
			       objectstore::dsco_access_allowed);
  static os_database *open(const char *pathname, os_boolean read_only,
			   os_int32 create_mode, os_database *schema_database,
			   objectstore::segment_reference_policy
			     new_segment_reference_policy =
				objectstore::dsco_access_allowed);
  static os_database *create(const char *pathname, os_int32 mode = 0664,
			     os_boolean if_exists_overwrite = 0,
			     os_database *schema_database = 0,
			     objectstore::segment_reference_policy
			       new_segment_reference_policy =
				 objectstore::dsco_access_allowed);
  void destroy();

  objectstore::segment_reference_policy
    get_new_segment_reference_policy() const;
  void set_new_segment_reference_policy(
			objectstore::segment_reference_policy
				new_segment_reference_policy);


  os_segment *create_segment();
  os_segment *create_segment(objectstore::segment_reference_policy
			       segment_reference_policy);
  os_segment *get_segment(os_unsigned_int32 segment_number) const;
  os_int32 get_n_segments() const;

  void get_all_segments_and_permissions(os_int32 max_segments,
					os_segment_p *segs,
					os_segment_access_p* controls,
					os_int32& n_segments) const;

  void get_all_segments(os_int32     max_segments,
			os_segment_p *segs,
			os_int32&    n_segments) const
    { get_all_segments_and_permissions(max_segments, segs, 0, n_segments); }

  void get_segments(os_unsigned_int32 first_seg_num,
		    os_unsigned_int32 max_segments,
		    os_segment_p *segs,
		    os_unsigned_int32& n_segments,
		    os_boolean &b_more) const;

  static os_database *of(void const *location);
  os_int32 get_n_roots() const;
  void get_all_roots(os_int32 max_roots, os_database_root_p*roots,
		     os_int32& n_roots) const;

  os_unsigned_int64 size() const;
  os_unsigned_int32 size_in_sectors() const;
  static os_int32 get_sector_size();
  os_unixtime_t time_created() const;
  char *get_host_name() const;
  char *get_file_host_name() const;
  os_database_root *create_root(const char *name_arg);
  os_database_root *find_root(const char *name_arg) const;
  void set_allocation_strategy(os_allocation_strategy);
  os_allocation_strategy get_allocation_strategy(void) const;
  void set_fetch_policy(os_fetch_policy, os_int32);
  void get_fetch_policy(os_fetch_policy &, os_int32 &) const;
  void set_check_illegal_pointers(os_boolean);
  void set_null_illegal_pointers(os_boolean);
  void set_default_check_illegal_pointers(os_boolean);
  /* To be deprecated */
  os_boolean get_default_check_illegal_pointers() const;
  os_boolean get_check_illegal_pointers() const;
  os_boolean get_null_illegal_pointers() const;
  objectstore_lock_option get_lock_option() const;
  void set_lock_option(objectstore_lock_option);
  
  void set_readlock_timeout(os_int32 milliseconds);
  os_int32 get_readlock_timeout() const;
  void set_writelock_timeout(os_int32 milliseconds);
  os_int32 get_writelock_timeout() const;
  os_boolean get_incremental_schema_installation() const;
  void set_incremental_schema_installation(os_boolean);
  void *get_application_info() const;
  void set_application_info(void *info);
  os_segment *get_default_segment() const;
  void set_default_segment(os_segment *seg);
  void server_debug_message(os_int32 level, const char *message);
  void change_schema_key(os_unsigned_int32 old_key_low, 
			 os_unsigned_int32 old_key_high, 
			 os_unsigned_int32 new_key_low, 
			 os_unsigned_int32 new_key_high);
  void freeze_schema_key(os_unsigned_int32 key_low, 
			 os_unsigned_int32 key_high);
#ifndef DISABLE_DLL_SCHEMA
  /* For DLL Schema feature */
  const char* const* get_required_DLL_identifiers(os_unsigned_int32& count);
  void insert_required_DLL_identifier(const char* DLL_identifier);
  void insert_required_DLL_identifiers(const char* const* DLL_identifiers,
				       os_unsigned_int32 count);
  void remove_required_DLL_identifier(const char* DLL_identifier);
#endif /* DISABLE_DLL_SCHEMA */

  os_session *session_of() const;

  void release_pointer();
  void retain_pointer();

  void return_memory(os_boolean evict_now);
};

/* This class provides a mechanism to call the release_pointer() method
  on a specified os_database pointer when that pointer goes out of scope. 
*/
class _OS_DLLIMPORT(_OS_CLIENT) os_release_database_pointer : public basic_undo
{
private:
  os_database *ptr;

public:
  os_release_database_pointer(os_database *_ptr) : ptr(_ptr) {}
  ~os_release_database_pointer() { if (ptr) ptr->release_pointer(); }
};

/* This class provides a mechanism to call the close() method on a 
  specified os_database pointer when that pointer goes out of scope. 
  It can be used where code has called open on a database and wants
  to ensure that it leaves the database in the same state as before 
  the open.
*/
class _OS_DLLIMPORT(_OS_CLIENT) os_close_database : public basic_undo
{
private:
  os_database *ptr;

public:
  os_close_database(os_database *_ptr) : ptr(_ptr) {}
  ~os_close_database() { if (ptr) ptr->close(); }
};

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_DATABASE */
