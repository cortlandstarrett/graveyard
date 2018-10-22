/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_OBJSTORE
#define CLIENT_INTERFACE_OBJSTORE 1

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/except.hh>
#include <ostore/nclient/alloc_strat.hh>
#include <ostore/nclient/typedefs.hh>
#include <ostore/nclient/fault.hh>
#include <ostore/nclient/export_id.hh>

class os_persistent_to_transient_pointer_manager;
class os_schema_handle;
class os_transaction;
struct xa_switch_t;  /* The externally defined XA interface structure */

class _OS_DLLIMPORT(_OS_CLIENT) os_as_interval {
public:
  char *start;
  os_ptr_val size;
};

class _OS_DLLIMPORT(_OS_CLIENT) objectstore {
public:						/* PUBLIC FUNCTION MEMBERS */
  /* cache management */
  static os_unsigned_int32 get_cache_size();
  static void set_cache_size(os_unsigned_int32 new_cache_size);
  static void return_all_pages();
  static void return_memory(void *address,
			    os_unsigned_int32 length, os_boolean evict_now);

  /* address space management */
  static os_boolean acquire_address_space(os_ptr_val size,
					  os_ptr_val mapaside_size=0);
  static os_boolean is_persistent(void const *address);
  static void set_reserve_as_mode(os_boolean new_mode);
  static void retain_persistent_addresses();
  static void release_persistent_addresses(os_boolean force = 0);
  static os_boolean get_retain_persistent_addresses();
  static void set_retain_persistent_addresses(os_boolean value);
  static void reset_persistent_addresses(os_boolean force = 0);
  static void set_retain_address(void *address, os_boolean value = 1);
  static os_unsigned_int32 get_retain_count(void *address);
  static os_ptr_val get_unassigned_address_space();
  static os_ptr_val get_largest_contiguous_unassigned_address_space();
  static os_boolean is_unassigned_contiguous_address_space(os_unsigned_int32 size);
  static os_unsigned_int32 get_address_space_generation_number();
  static void *convert_DSCO_to_address(os_database *db,
				       os_unsigned_int32 segnum,
				       os_unsigned_int32 clustnum,
				       os_unsigned_int32 offset,
				       os_unsigned_int32 mapping_size = 0);
  static void *convert_DSCO_to_address_and_map_it(os_lock_type access,
						  os_database *db,
						  os_unsigned_int32 segnum,
						  os_unsigned_int32 clustnum,
						  os_unsigned_int32 offset,
						  os_unsigned_int32 mapping_size = 0);
  static void convert_address_to_DSCO(void *addr,
				      os_database *&db,
				      os_unsigned_int32 &segnum,
				      os_unsigned_int32 &clustnum,
				      os_unsigned_int32 &offset,
				      os_unsigned_int32 &mapping_size);
  static void *convert_DSEO_to_address(os_database * db,
				       os_unsigned_int32 segnum,
				       os_export_id const& export_id,
				       os_unsigned_int32 offset);
  static void *convert_DSEO_to_address_and_map_it(os_lock_type access,
						  os_database * db,
						  os_unsigned_int32 segnum,
						  os_export_id const& export_id,
						  os_unsigned_int32 offset);
  static void convert_address_to_DSEO(void* addr,
				      os_database *&db,
				      os_unsigned_int32 &segnum,
				      os_export_id& export_id,
				      os_unsigned_int32& offset);

  static os_boolean convert_DSCO_to_DSEO(os_database *db,
					 os_unsigned_int32 segnum,
					 os_unsigned_int32 clustnum,
					 os_unsigned_int32 cluster_offset,
					 os_unsigned_int32 mapping_size,
					 os_export_id& export_id,
					 os_unsigned_int32& object_offset);

  static os_boolean convert_DSEO_to_DSCO(os_database *db,
					 os_unsigned_int32 segnum,
					 os_export_id export_id,
					 os_unsigned_int32 object_offset,
					 os_unsigned_int32& clustnum,
					 os_unsigned_int32& cluster_offset,
					 os_unsigned_int32& mapping_size);

  /* soft pointer address modes */
  enum address_mode { address_dsco, address_dseo, address_transient };

  static void set_decache_soft_pointers_after_address_space_release(os_boolean);
  static os_boolean get_decache_soft_pointers_after_address_space_release();

  static os_ptr_val get_default_address_space_partition_size();
  static void set_default_address_space_partition_size(os_ptr_val);
  static void get_as_intervals(os_as_interval_p *persist, os_int32& n_persist_intervals,
			       os_as_interval_p *other, os_int32& n_other_intervals);


  /* pointer management */
  static void set_always_ignore_illegal_pointers(os_boolean new_val);
  static os_boolean get_always_ignore_illegal_pointers();
  static void set_always_null_illegal_pointers(os_boolean new_val);
  static os_boolean get_always_null_illegal_pointers();
  static void set_check_illegal_pointers(os_boolean);
  static os_boolean get_check_illegal_pointers();
  static void set_null_illegal_pointers(os_boolean);
  static os_boolean get_null_illegal_pointers();
  static void set_handle_transient_faults(os_boolean);
  static void set_suppress_invalid_hard_pointer_errors(os_boolean);
  static os_boolean get_suppress_invalid_hard_pointer_errors();


  /* transaction/page locking management */
  enum objectstore_lock_option_enum {lock_as_used, own_page_write, lock_page_write,
				     lock_cluster_read, lock_cluster_write,
				     lock_segment_read, lock_segment_write,
				     lock_database_read, lock_database_write,
				     objectstore_lock_option_enum_pad =
				     1<<30};
  static void set_lock_option(objectstore_lock_option_enum);
  static objectstore_lock_option_enum get_lock_option();
  static void set_lock_timeout(os_int32 milliseconds);
  static os_int32 get_lock_timeout();
  static void set_readlock_timeout(os_int32 milliseconds);
  static os_int32 get_readlock_timeout();
  static void set_writelock_timeout(os_int32 milliseconds);
  static os_int32 get_writelock_timeout();
  static os_lock_timeout_exception *acquire_lock(void *address,
						 os_lock_type access,
						 os_int32 milliseconds,
						 os_unsigned_int32 size = 1);
  static os_lock_timeout_exception *acquire_lock(os_database  *db,
						 os_lock_type access,
						 os_int32     milliseconds);
  static os_lock_timeout_exception *acquire_lock(os_segment   *seg,
						 os_lock_type access,
						 os_int32     milliseconds);
  static os_lock_timeout_exception *acquire_lock(os_cluster   *clus,
						 os_lock_type access,
						 os_int32     milliseconds);
  static enum os_lock_type get_lock_status(void *address);
  static void set_transaction_priority(os_unsigned_int16 priority);
  static os_unsigned_int16 get_transaction_priority();
  static void set_transaction_max_retries(os_unsigned_int32 max_retries);
  static os_unsigned_int32 get_transaction_max_retries();
  static os_boolean is_lock_contention();
  static os_boolean get_always_check_server_connection_at_commit();
  static void set_always_check_server_connection_at_commit(os_boolean);
  
  /* server connection management */
  static os_int32 get_n_servers();
  static void get_all_servers(os_int32 max_servers, os_server_p *servers,
			      os_int32& n_servers);
  static void set_client_name(const char *new_name);
  static const char *get_client_name();

  /* object/pointer and allocation management */
  //static void *change_array_length(void *array, os_unsigned_int32 new_length);
  static void free_memory(void *);
  static void get_object_range(void const *address, os_void_p &base_address,
			       os_unsigned_int32 &size);
  static void get_object_range(void const *address, os_void_p &base_address,
			       os_unsigned_int32 &size,
			       os_void_p &header_address,
			       os_unsigned_int32 &total_size);
  static os_unsigned_int32 get_page_size();
  static objectstore_delete_function get_transient_delete_function();
  static void set_transient_delete_function(objectstore_delete_function f);
  static os_allocation_strategy get_allocation_strategy();
  static void set_allocation_strategy(os_allocation_strategy);

  /* object export management */
  enum segment_reference_policy { export_id_access_required,
				  dsco_access_allowed,
				  segment_reference_policy_pad = 1 << 30 };
  /* export is a C++ keyword, however gcc is the only compiler that currently       *
   * complains.  export_address should now be called instead of export.  However,   *
   * export is still provided for all other platforms for backward compatibility.   */
#if !defined(__os_linux) && !defined(__os_sol2c5)
  static os_export_id export(const void *export_address);
#endif
  static os_export_id export_address(const void *export_address);
  static os_export_id unexport(const void *export_address);
  static os_export_id get_export_id(const void *export_address);
  static void set_export_id(const void *export_address, os_export_id const& eid);

  /* union discriminant management. */
  static os_unsigned_int16 get_union_variant(void *address, 
					     const char *type_name);
  static void set_union_variant(void *address, 
			 	const char *type_name,
			 	os_unsigned_int16 variant);

  /* schema management */
  static os_boolean get_incremental_schema_installation() ;
  static void set_incremental_schema_installation(os_boolean) ;
  static void set_application_schema_pathname(const char * path);
  static const char * get_application_schema_pathname();
  static void set_current_schema_key(os_unsigned_int32 key_low, 
				     os_unsigned_int32 key_high);
  static void remove_cached_transient_dope();
  static void add_missing_dispatch_table_handler
    (os_missing_dispatch_table_handler_function);


  /* authentication management */
  static void set_simple_auth_ui(os_simple_auth_ui_t, void *);
  static void get_simple_auth_ui(os_simple_auth_ui_t&, os_void_p&);


  /* version and product info */
  static const char *release_name();
  static os_unsigned_int32 release_major();
  static os_unsigned_int32 release_minor();
  static os_unsigned_int32 release_maintenance();
  enum os_product_type { pse, pse_pro, ostore_cpp };
  static os_product_type which_product() { return ostore_cpp; };

  /* performance monitoring */
  static void disable_ope_auto_start(os_boolean always_disabled = 0);
  static void enable_counters();
  static void disable_counters();
  static void record_realtime_counters(os_boolean enable);
  static void reset_counters();
  static void print_counters();
  static os_unsigned_int32 read_counter(char const *name);
  static os_int32 get_n_counters();
  static void get_all_counters(os_int32 max_ctrs, os_char_p *names, os_int32& n_ctrs);


  /* event hooks */
  static void enable_event_hooks();
  static void disable_event_hooks();
  static os_boolean are_event_hooks_enabled();
  static void set_default_hooks();

  static void set_page_fault_hook (void (*fcn) (os_char_p addr,
						os_database * database,
						os_unsigned_int32 segment_no,
						os_unsigned_int32 cluster_no,
						os_unsigned_int32 page_no,
						os_boolean b_for_write));
  static void default_page_fault_hook (os_char_p addr,
				       os_database *database,
				       os_unsigned_int32 segment_no,
				       os_unsigned_int32 cluster_no,
				       os_unsigned_int32 page_no,
				       os_boolean b_for_write);

  static void set_page_fetch_hook (void (*fcn) (os_database *database,
						os_unsigned_int32 segment_no,
						os_unsigned_int32 cluster_no,
						os_unsigned_int32 page_no,
						os_unsigned_int32 n_pages,
						os_boolean for_write));
  static void default_page_fetch_hook (os_database *database,
				       os_unsigned_int32 segment_no,
				       os_unsigned_int32 cluster_no,
				       os_unsigned_int32 page_no,
				       os_unsigned_int32 n_pages,
				       os_boolean for_write);

  static void set_fault_active_hook (void (*fcn) (os_database * database,
						os_unsigned_int32 segment_no,
						os_unsigned_int32 cluster_no,
						os_unsigned_int32 page_no,
						os_boolean b_for_write));
  static void default_fault_active_hook (os_database *database,
				       os_unsigned_int32 segment_no,
				       os_unsigned_int32 cluster_no,
				       os_unsigned_int32 page_no,
				       os_boolean b_for_write);

  static void set_return_pages_hook (void (*fcn) (os_database *database,
						  os_unsigned_int32 segment_no,
						  os_unsigned_int32 cluster_no,
						  os_unsigned_int32 page_no,
						  os_unsigned_int32 n_pages,
						  os_boolean dirty_p));
  static void default_return_pages_hook (os_database *database,
					 os_unsigned_int32 segment_no,
					 os_unsigned_int32 cluster_no,
					 os_unsigned_int32 page_no,
					 os_unsigned_int32 n_pages,
					 os_boolean dirty_p);

  static void set_reloc_page_in_hook (void (*fcn) (os_database *database,
						   os_unsigned_int32 segment_no,
						   os_unsigned_int32 cluster_no,
						   os_unsigned_int32 page_no));
  static void default_reloc_page_in_hook (os_database *database,
					  os_unsigned_int32 segment_no,
					  os_unsigned_int32 cluster_no,
					  os_unsigned_int32 page_no);

  static void set_reloc_page_out_hook (void (*fcn) (os_database *database,
						    os_unsigned_int32 segment_no,
						    os_unsigned_int32 cluster_no,
						    os_unsigned_int32 page_no));
  static void default_reloc_page_out_hook (os_database *database,
					   os_unsigned_int32 segment_no,
					   os_unsigned_int32 cluster_no,
					   os_unsigned_int32 page_no);

  static void set_reloc_page_forward_hook (void (*fcn) (os_database *database,
						   os_unsigned_int32 segment_no,
						   os_unsigned_int32 cluster_no,
						   os_unsigned_int32 page_no));
  static void default_reloc_page_forward_hook (os_database *database,
					  os_unsigned_int32 segment_no,
					  os_unsigned_int32 cluster_no,
					  os_unsigned_int32 page_no);

  static void set_commit_pages_hook (void (*fcn) (os_database *database,
						 os_unsigned_int32 segment_no,
						 os_unsigned_int32 cluster_no,
						 os_unsigned_int32 page_no,
						 os_unsigned_int32 n_pages));
  static void default_commit_pages_hook (os_database *database,
					os_unsigned_int32 segment_no,
					os_unsigned_int32 cluster_no,
					os_unsigned_int32 page_no,
					os_unsigned_int32 n_pages);

  static void set_upgrade_lock_hook (void (*fcn) (os_database *database,
						  os_unsigned_int32 segment_no,
						  os_unsigned_int32 cluster_no,
						  os_unsigned_int32 page_no,
						  os_boolean b_write_lock));
  static void default_upgrade_lock_hook (os_database *database,
					 os_unsigned_int32 segment_no,
					 os_unsigned_int32 cluster_no,
					 os_unsigned_int32 page_no,
					 os_boolean b_write_lock);

  static void set_deadlock_hook (void (*fcn) (os_database *database,
					      os_unsigned_int32 segment_no,
					      os_unsigned_int32 cluster_no,
					      os_unsigned_int32 page_no,
					      os_unsigned_int32 n_pages));
  static void default_deadlock_hook (os_database *database,
				     os_unsigned_int32 segment_no,
				     os_unsigned_int32 cluster_no,
				     os_unsigned_int32 page_no,
				     os_unsigned_int32 n_pages);

  static void set_page_creation_hook (void (*fcn) (os_database *database,
						   os_unsigned_int32 segment_no,
						   os_unsigned_int32 cluster_no,
						   os_unsigned_int32 page_no,
						   os_unsigned_int32 n_pages));
  static void default_page_creation_hook (os_database *database,
					  os_unsigned_int32 segment_no,
					  os_unsigned_int32 cluster_no,
					  os_unsigned_int32 page_no,
					  os_unsigned_int32 n_pages);
  
  /* Component (DLL) Schema */
  static void enable_DLL_schema(os_boolean);
  static os_boolean is_DLL_schema_enabled();
  static void enable_damaged_dope_repair(os_boolean);
  static os_boolean is_damaged_dope_repair_enabled();
  static os_DLL_handle load_DLL(const char* DLL_identifier,
				os_boolean error_if_not_found = 1);
  static void unload_DLL(os_DLL_handle h);
  static void* lookup_DLL_symbol(os_DLL_handle h, const char* symbol);
  static os_schema_handle* find_DLL_schema(const char* DLL_identifier,
					   os_boolean load_if_not_loaded,
					   os_boolean error_if_not_found);
  static os_autoload_DLLs_function get_autoload_DLLs_function();
  static os_autoload_DLLs_function set_autoload_DLLs_function
					    (os_autoload_DLLs_function fcn);



  /* objectstore single */
  static os_boolean embedded_server_available();
  static os_boolean network_servers_available();
  static void set_log_file(const char *log_path);
  static char *get_log_file();
  static void set_propagate_on_commit(os_boolean propagate_on_commit);
  static os_boolean get_propagate_on_commit();
  static void propagate_log(const char *log_path);
  static void set_cache_file(const char *cache_path, 
			     os_boolean pre_allocate = 1);
  static char *get_cache_file();


  /* initialization and shutdown */
  static void initialize(os_boolean force_full_initialization = 0);
  static void initialize_for_sessions(os_unsigned_int32 n_expected_sessions);
  static os_boolean is_full_client();
  static os_boolean is_multiple_session_mode();
  static os_boolean is_single_session_mode();
  static void shutdown();
  static void set_thread_locking(os_boolean);
  static os_boolean get_thread_locking();
  static xa_switch_t *get_xa_switch();
  
  /* locator files */
  static const char* get_locator_file();
  static void set_locator_file(const char *);
  static void ignore_locator_file(os_boolean);


  /* auto-database open */
  enum auto_open_mode_enum {
    auto_open_disable,
    auto_open_update,
    auto_open_read_only,
    auto_open_mvcc,
    auto_open_multi_db_mvcc,
    auto_open_enum_pad = 1<<30
  };
  /* Deprecate these methods which marry fetch policy to auto-open mode */
  static void set_auto_open_mode(auto_open_mode_enum mode,
				 os_fetch_policy,
				 os_int32 bytes);
  static void get_auto_open_mode(auto_open_mode_enum &mode,
				 os_fetch_policy &fp,
				 os_int32 &bytes);
  				   
  static void set_auto_open_mode(auto_open_mode_enum mode);

  static void get_auto_open_mode(auto_open_mode_enum &mode);

  static void set_fetch_policy(os_fetch_policy fp = os_fetch_page,
			       os_int32 bytes = 0);
  static void get_fetch_policy(os_fetch_policy &fp,
			       os_int32 &bytes);

  /* API for managing persistent to transient pointers */
  static void * set_persistent_to_transient_pointer(
		void * p_pointer,  
		void * pointer,
		os_persistent_to_transient_pointer_manager &pttp_mgr);

  static os_int32 clear_persistent_to_transient_pointers(
		  os_int32 max = -1);
  static os_int32 clear_persistent_to_transient_pointers(
		  os_database *, os_int32 max = -1);
  static os_int32 clear_persistent_to_transient_pointers(
		  os_segment *, os_int32 max = -1);
  static os_int32 clear_persistent_to_transient_pointers(
		  os_cluster *, os_int32 max = -1);

  static os_int32 release_cleared_persistent_to_transient_pointers(
		  os_int32 max = -1);
  static os_int32 release_cleared_persistent_to_transient_pointers(
		  os_database *, os_int32 max = -1);
  static os_int32 release_cleared_persistent_to_transient_pointers(
		  os_segment *, os_int32 max = -1);
  static os_int32 release_cleared_persistent_to_transient_pointers(
		  os_cluster *, os_int32 max = -1);

#ifdef _OS_Win32
  static os_se_translator_function set_se_translator(os_se_translator_function f);
#endif /* _OS_Win32 */

  
public:
  static os_boolean _in_house();
  static void _debug_show_address_space(os_boolean show_gaps);
  static void _debug_show_tags(void *address);
  static void _debug_show_PRM(void *address);
  static void _get_object_info(void const *address,
			       os_void_p &base_address,
			       os_char_p &type_name,
			       os_unsigned_int32 &type_code,
			       os_int32 &array,
			       os_int32 &count);
  static void get_pointer_numbers(const void *address,
				  os_unsigned_int32 &number_1,
				  os_unsigned_int32 &number_2,
				  os_unsigned_int32 &number_3);
  static void set_check_vector_headers(os_boolean value);
  static os_boolean get_check_vector_headers();
  static void set_fix_vector_headers(os_boolean value);
  static os_boolean get_fix_vector_headers();
};

typedef objectstore::objectstore_lock_option_enum objectstore_lock_option;
typedef objectstore::auto_open_mode_enum objectstore_auto_open_mode;

class _OS_DLLIMPORT(_OS_CLIENT) os_with_mapped : public basic_undo {
  void **pages;
  os_unsigned_int32 n_pages;
  os_transaction *current_txn;
public:
  os_with_mapped(void const *address, 
		 os_unsigned_int32 size, 
		 os_boolean for_write = 0);
  ~os_with_mapped();
};

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_OBJSTORE */
