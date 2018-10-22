/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef __DBUTIL_HH__
#define __DBUTIL_HH__
#include <ostore/hdrstart.hh>

#include <ostore/portypes.hh>
#include <ostore/rawentry.hh>
#include <ostore/nclient/typedefs.hh>

/*
 * Structure versions.  An application assigns the appropriate one to the
 * struct_version field of a structure when passing a pointer to pre-allocated
 * space to an os_dbutil API method.  The API method signals an exception if
 * the library's version number differs from the one in the structure.
 * In addition, API methods set version numbers in the sub-structures they
 * allocate and return.  The application can check those, if desired.
 */
/* Versions checked by API methods */
#define os_free_blocks_version (os_unsigned_int32(1))
#define os_cmgr_stat_version (os_unsigned_int32(2))
#define os_svr_stat_version (os_unsigned_int32(1))
#define os_size_options_version (os_unsigned_int32(3))

/* Versions set by API methods for the user to check */
#define os_cmgr_stat_svr_version (os_unsigned_int32(1))
#define os_cmgr_stat_client_version (os_unsigned_int32(2))
#define os_cmgr_stat_file_usage_version (os_unsigned_int32(1))

#define os_svr_stat_svr_parameters_version (os_unsigned_int32(5))
#define os_svr_stat_svr_rusage_version (os_unsigned_int32(1))
#define os_svr_stat_svr_meters_version (os_unsigned_int32(2))
#define os_svr_stat_client_info_version (os_unsigned_int32(1))
#define os_svr_stat_client_process_version (os_unsigned_int32(1))
#define os_svr_stat_client_meters_version (os_unsigned_int32(2))
#define os_svr_stat_client_state_version (os_unsigned_int32(2))
#define os_svr_log_stat_sample_version (os_unsigned_int32(1))

#define OS_INT32_MAX 0x7FFFFFFF

class os_size_options {
public:
   os_unsigned_int32 struct_version;  
   os_boolean  		flag_all;	        /* -a */
   os_boolean  		flag_segments;		/* -c */
   os_boolean  		flag_total_database;	/* -C */
// obsoleted with 6.0 (os_size_options_version = 3)
// os_boolean 		flag_free_block_map;    /* -f */
   os_unsigned_int32    one_segment_number;	/* -n */
   os_boolean  		flag_every_object;      /* -o */
   char 		flag_summary_order;	/* -s    's'=space 'n'=number 't'=typename */
   os_boolean 		_unused1;
   const char  	       *_unused2;
   os_boolean  		_unused3;
   os_boolean  		flag_internal_segments; /* -0 */
   os_boolean  		flag_access_control;    /* -A */

  os_size_options();
  ~os_size_options();
};


/* --- Cache Manager status --- */
class  _OS_DLLIMPORT(_OS_CLIENT) os_cmgr_stat_notification {
public:
  os_unsigned_int32    queue_size;		/* max queue size */
  os_unsigned_int32    n_queued;		/* cumulative */
  os_unsigned_int32    n_received;		/* cumulative */
  os_unsigned_int32    queue_overflows;
  os_unsigned_int32    thread_state;

  os_cmgr_stat_notification();
  ~os_cmgr_stat_notification();
};


class  _OS_DLLIMPORT(_OS_CLIENT) os_cmgr_stat_client {
public:
  os_unsigned_int32    struct_version;
  os_int32	  	pid;
  os_unsigned_int32 	euid;
  char   	       *name;
  os_int32 	  	major_version;
  os_int32 	  	minor_version;
  os_int32 	  	commseg;
  os_cmgr_stat_notification	*notification;

  os_cmgr_stat_client();
  ~os_cmgr_stat_client();
};


class  _OS_DLLIMPORT(_OS_CLIENT) os_cmgr_stat_svr {
public:
  os_unsigned_int32    struct_version;
  char 		  *host_name;
  os_int32	   client_pid;
  char   	  *status_str;

  os_cmgr_stat_svr();
  ~os_cmgr_stat_svr();
};


class  _OS_DLLIMPORT(_OS_CLIENT) os_cmgr_stat_file_usage {
public:
  os_unsigned_int32    struct_version;
  os_int32	       pid;
  char                *file_name;
  os_unsigned_int32    file_length;
  os_boolean   	       is_free;

  os_cmgr_stat_file_usage();
  ~os_cmgr_stat_file_usage();
};

enum os_cmgr_stat_notifier_state
{
  notifier_state_initializing,
  notifier_state_running,
  notifier_state_waiting_for_notification,
  notifier_state_waiting_for_ack,
  notifier_state_sending_notification,
  notifier_state_exiting,
  notifier_state_pad = 1<<30
};


class  _OS_DLLIMPORT(_OS_CLIENT) os_cmgr_stat {
public:
  os_unsigned_int32       struct_version;           
  os_unsigned_int32  	  major_version;
  os_unsigned_int32  	  minor_version;
  os_unsigned_int32  	  pid;
  char  	  	 *executable_name;
  char  	  	 *host_name;
  os_unixtime_t		  start_time;
  os_int32 		  soft_limit;
  os_int32 		  hard_limit;
  os_int32 		  free_allocated;
  os_int32 		  used_allocated;
  os_int32 		  n_clients;  	/* num elements in per_client array */
  os_cmgr_stat_client    *per_client;		/* array */
  os_int32 		  n_servers;  	/* num elements in per_server array */
  os_cmgr_stat_svr     	 *per_server;      	/* array */
  os_int32 		  n_cache_file_usage;	/* num elements in cache_file_usage array */
  os_cmgr_stat_file_usage *cache_file_usage;   	/* array */
  os_int32 		  n_commseg_file_usage;	/* num elements in commseg_file_usage array */
  os_cmgr_stat_file_usage  *commseg_file_usage;  /* array */
  char			 *cback_queue;
  char			 *extra;

  os_cmgr_stat();
  ~os_cmgr_stat();
};


/* --- Server status --- */

enum os_svr_ping_state {
  os_svr_ping_is_alive,
  os_svr_ping_not_reachable,
  os_svr_ping_no_such_host,
  os_svr_ping_is_alive_as_failover_backup,
  os_svr_ping_is_alive_as_failover_primary,
  os_svr_ping_state_pad = 1<<30
};

class os_timesecs {
public:
    os_int32    tv_sec;         /* seconds */
    os_int32    tv_usec;        /* and microseconds */
};


/* the os_svr_rusage structure is equivalent
   to the Unix rusage datatype */
class _OS_DLLIMPORT(_OS_CLIENT) os_svr_stat_svr_rusage {
public:
  os_unsigned_int32 struct_version;
  os_timesecs ru_utime;			/* user time used */
  os_timesecs ru_stime;			/* system time used */
  os_int32	ru_maxrss;		/* maximum resident set size */
  os_int32	ru_ixrss;		/* integral shared memory size */
  os_int32	ru_idrss;		/* integral unshared data size */
  os_int32	ru_isrss;		/* integral unshared stack size */
  os_int32	ru_minflt;		/* page reclaims */
  os_int32	ru_majflt;		/* page faults */
  os_int32	ru_nswap;		/* swaps */
  os_int32	ru_inblock;		/* block input operations */
  os_int32	ru_oublock;		/* block output operations */
  os_int32	ru_msgsnd;		/* messages sent */
  os_int32	ru_msgrcv;		/* messages received */
  os_int32	ru_nsignals;		/* signals received */
  os_int32	ru_nvcsw;		/* voluntary context switches */
  os_int32	ru_nivcsw;		/* involuntary context switches */

  os_svr_stat_svr_rusage();
  ~os_svr_stat_svr_rusage();
};

enum os_client_lock_type {
    OSSVRSTAT_CLIENT_LOCK_TO_END_OF_SEGMENT,  /* obsolete in R4 */
    OSSVRSTAT_CLIENT_LOCK_TO_MAX_BLOCKS,
    OSSVRSTAT_CLIENT_LOCK_TO_NBLOCKS,
    os_client_lock_type_pad = 1<<30
};

enum os_client_state_type {
  OSSVRSTAT_CLIENT_WAITING_MESSAGE,
  OSSVRSTAT_CLIENT_EXECUTING_MESSAGE,
  OSSVRSTAT_CLIENT_WAITING_RANGE_READ_LOCK,
  OSSVRSTAT_CLIENT_WAITING_RANGE_WRITE_LOCK,
  OSSVRSTAT_CLIENT_WAITING_SEGMENT_WRITE_LOCK,
  OSSVRSTAT_CLIENT_DEAD,
  OSSVRSTAT_CLIENT_WAITING_SEGMENT_READ_LOCK,
  OSSVRSTAT_CLIENT_WAITING_DB_READ_LOCK,
  OSSVRSTAT_CLIENT_WAITING_DB_WRITE_LOCK,
  OSSVRSTAT_CLIENT_WAITING_CLUSTER_READ_LOCK,
  OSSVRSTAT_CLIENT_WAITING_CLUSTER_WRITE_LOCK,
  OSSVRSTAT_CLIENT_WAITING_CLUSTER_RANGE_READ_LOCK,
  OSSVRSTAT_CLIENT_WAITING_CLUSTER_RANGE_WRITE_LOCK,
  OSSVRSTAT_CLIENT_WAITING_WHILE_FREEZING_COHERENT_SET,
  OSSVRSTAT_CLIENT_WAITING_FOR_CONFLICTING_UPDATE_COMMIT,
  os_client_state_type_pad = 1<<30
};

enum os_db_status_type {
    OSDBCONTROL_DATABASE_IS_ONLINE,
    OSDBCONTROL_DATABASE_IS_OFFLINE,
    OSDBCONTROL_DATABASE_IS_GOING_OFFLINE,
    OSDBCONTROL_DATABASE_DOES_NOT_EXIST,
    os_db_status_type_pad = 1<<30
};

class _OS_DLLIMPORT(_OS_CLIENT) os_svr_stat_client_process {
public:
  os_unsigned_int32 struct_version;
  char* host_name;
  os_unsigned_int32 process_id;
  char* client_name;
  os_unsigned_int32 client_id;

  os_svr_stat_client_process();
  ~os_svr_stat_client_process();
};

class _OS_DLLIMPORT(_OS_CLIENT) os_svr_stat_svr_meters {
public:
  os_unsigned_int32 struct_version;
  os_boolean	    valid;
  os_unsigned_int32 n_minutes;
  os_unsigned_int32 n_receive_msgs;
  os_unsigned_int32 n_callback_msgs;
  os_unsigned_int32 n_callback_sectors_requested;
  os_unsigned_int32 n_callback_sectors_succeeded;
  os_unsigned_int32 n_sectors_read;
  os_unsigned_int32 n_sectors_written;
  os_unsigned_int32 n_commit;
  os_unsigned_int32 n_phase_2_commit;
  os_unsigned_int32 n_readonly_commit;
  os_unsigned_int32 n_abort;
  os_unsigned_int32 n_phase_2_abort;
  os_unsigned_int32 n_deadlocks;
  os_unsigned_int32 n_msg_buffer_waits;
  os_unsigned_int32 n_log_records;
  os_unsigned_int32 n_log_seg_switches;
  os_unsigned_int32 n_flush_log_data_writes;
  os_unsigned_int32 n_flush_log_record_writes;
  os_unsigned_int32 n_log_data_writes;
  os_unsigned_int32 n_log_record_writes;
  os_unsigned_int32 n_sectors_propagated;
  os_unsigned_int32 n_sectors_direct;
  os_unsigned_int32 n_do_some_propagation;
  os_unsigned_int32 n_notifies_sent;
  os_unsigned_int32 n_notifies_received;
  os_unsigned_int32 n_lock_timeouts;
  os_unsigned_int32 n_lock_waits;
  os_timesecs       total_lock_wait_time;

  os_svr_stat_svr_meters();
  ~os_svr_stat_svr_meters();
};

class _OS_DLLIMPORT(_OS_CLIENT) os_svr_stat_svr_header {
public:
  char 		    *os_release_name;
  os_unsigned_int32  server_major_version;
  os_unsigned_int32  server_minor_version;
  char 		    *compilation;

  os_svr_stat_svr_header();
  ~os_svr_stat_svr_header();
};


class _OS_DLLIMPORT(_OS_CLIENT) os_svr_stat_svr_parameters {
public:
  os_unsigned_int32  struct_version;  
  char 		    *parameter_file;
  os_boolean 	     allow_shared_mem_usage;
  os_int32 	    *authentication_list;
  os_unsigned_int32  n_authentications;
  os_int32 	     RAWFS_db_expiration_time;
  os_int32 	     deadlock_strategy;
  os_unsigned_int32  direct_to_segment_threshold;
  char 		    *log_path;
  os_unsigned_int32  current_log_size_sectors;
  os_unsigned_int32  initial_log_data_sectors;
  os_unsigned_int32  growth_log_data_sectors;
  os_unsigned_int32  log_buffer_sectors;
  os_unsigned_int32  initial_log_record_sectors;
  os_unsigned_int32  growth_log_record_sectors;
  os_unsigned_int32  max_data_propagation_threshold;
  os_unsigned_int32  max_propagation_sectors;
  os_unsigned_int32  max_msg_buffer_sectors;
  os_unsigned_int32  max_msg_buffers;
  os_unsigned_int32  sleep_time_between_2p_outcomes;
  os_unsigned_int32  sleep_time_between_propagates;
  os_unsigned_int32  write_buffer_sectors;
  os_unsigned_int32  tcp_recv_buffer_size;
  os_unsigned_int32  tcp_send_buffer_size;
  os_boolean         allow_nfs_locks;
  os_boolean         allow_remote_database_access;
  os_unsigned_int32  max_two_phase_delay;
  os_unsigned_int32  max_aio_threads;
  os_unsigned_int32  cache_mgr_ping_time;
  os_unsigned_int32  cache_mgr_ping_time_in_trans;
  os_unsigned_int32  max_memory_usage;
  os_unsigned_int32  max_connect_memory_usage;
  os_unsigned_int32  remote_db_grow_reserve;
  os_boolean         allow_estale_to_currupt_dbs;
  os_int32           restricted_file_db_access_only;
  os_unsigned_int32  failover_heartbeat_time;
  os_unsigned_int32  rpc_timeout_in_seconds;

  os_svr_stat_svr_parameters();
  ~os_svr_stat_svr_parameters();
};

class _OS_DLLIMPORT(_OS_CLIENT) os_svr_stat_client_state {
public:
  os_unsigned_int32  struct_version;  
  os_client_state_type client_state;
  char       	    *message_name;
  os_boolean         txn_in_progress;
  os_unsigned_int32  txn_priority;
  os_unsigned_int32  txn_duration;
  os_unsigned_int32  txn_work;
  os_client_lock_type lock_state;
  os_unsigned_int32  db_id;
  char              *db_pathname;
  os_unsigned_int32  locked_seg_id;

/* Data in these 2 fields are valid only when lock_state is
   OSSVRSTAT_CLIENT_STATE_WAITING_RANGE_READ_LOCK, or
   OSSVRSTAT_CLIENT_STATE_WAITING_RANGE_WRITE_LOCK. */
  os_unsigned_int32  locking_start_sector; 
  os_unsigned_int32  locking_for_n_sectors;

  os_unsigned_int32  n_conflicts;
  os_svr_stat_client_process *lock_conflicts;

  /* This field is only present if struct_version is >= 2 */

  os_unsigned_int32  locked_cluster_id;

  os_svr_stat_client_state();
  ~os_svr_stat_client_state();
};


class _OS_DLLIMPORT(_OS_CLIENT)  os_svr_stat_client_meters {
public:
  os_unsigned_int32  struct_version;
  os_unsigned_int32  n_receive_msgs;
  os_unsigned_int32  n_callback_msgs;
  os_unsigned_int32  n_callback_sectors_requested;
  os_unsigned_int32  n_callback_sectors_succeeded;
  os_unsigned_int32  n_sectors_read;
  os_unsigned_int32  n_sectors_written;
  os_unsigned_int32  n_deadlocks;
  os_unsigned_int32  n_lock_timeouts;
  os_unsigned_int32  n_commit;
  os_unsigned_int32  n_phase_2_commit;
  os_unsigned_int32  n_readonly_commit;
  os_unsigned_int32  n_abort;
  os_unsigned_int32  n_phase_2_abort;
  os_unsigned_int32  n_notifies_sent;
  os_unsigned_int32  n_notifies_received;
  os_unsigned_int32  n_lock_waits;
  os_timesecs        total_lock_wait_time;

  os_svr_stat_client_meters();
  ~os_svr_stat_client_meters();
};

class _OS_DLLIMPORT(_OS_CLIENT) os_svr_stat_client_info {
public:
  os_unsigned_int32  struct_version;
  os_svr_stat_client_process *process;
  os_svr_stat_client_state   *state;
  os_svr_stat_client_meters  *meters;

  os_svr_stat_client_info();
  ~os_svr_stat_client_info();
};

class _OS_DLLIMPORT(_OS_CLIENT) os_db_statistic_info {
public:

  os_boolean                 database_is_rawfs;
  os_unsigned_int32          n_writes;
  os_unsigned_int32          n_reads;
  os_unsigned_int32          n_sector_writes;
  os_unsigned_int32          n_sector_reads;
  os_unsigned_int32          n_write_flushes;

  os_timesecs                write_flush_time;
  os_timesecs                write_time;
  os_timesecs                read_time;
  os_unsigned_int32          elapsed_time;

  os_db_statistic_info();
  ~os_db_statistic_info();
};

class _OS_DLLIMPORT(_OS_CLIENT) os_svr_log_stat_sample {
public:
  os_unsigned_int32	struct_version;
  os_boolean		valid;
  os_unsigned_int32	n_minutes;

  os_unsigned_int32	log_size;
  os_unsigned_int32	data_segment_size;
  os_unsigned_int32	record_segments_size;
  os_unsigned_int32	log_free_size;

  os_unsigned_int32	data_segment_active_size;
  os_unsigned_int32	data_segment_min_active_size;
  os_unsigned_int32	data_segment_max_active_size;

  os_unsigned_int32	current_record_segment_active_size;
  os_unsigned_int32	current_record_segment_min_active_size;
  os_unsigned_int32	current_record_segment_max_active_size;

  os_unsigned_int32	current_record_segment_live_size;
  os_unsigned_int32	current_record_segment_min_live_size;
  os_unsigned_int32	current_record_segment_max_live_size;

  os_unsigned_int32	previous_record_segment_active_size;
  os_unsigned_int32	previous_record_segment_min_active_size;
  os_unsigned_int32	previous_record_segment_max_active_size;

  os_unsigned_int32	previous_record_segment_live_size;
  os_unsigned_int32	previous_record_segment_min_live_size;
  os_unsigned_int32	previous_record_segment_max_live_size;

  os_unsigned_int32	delayed_data_size;
  os_unsigned_int32	delayed_data_min_size;
  os_unsigned_int32	delayed_data_max_size;

  os_unsigned_int32	n_garbage_collections;
  os_unsigned_int32	n_trivial_garbage_collections;

  os_unsigned_int32	n_grow_because_not_enough_time;
  os_unsigned_int32	n_grow_because_not_enough_transactions;
  os_unsigned_int32	n_grow_because_not_enough_time_and_transactions;
  os_unsigned_int32	n_grow_because_not_enough_data;
  os_unsigned_int32	n_grow_because_mvcc;
  os_unsigned_int32	n_grow_because_unfinished_transactions;
  os_unsigned_int32	n_grow_because_unpropagated_data;

  os_db_statistic_info	log_io_stats;

  os_svr_log_stat_sample();
  ~os_svr_log_stat_sample();
};

class _OS_DLLIMPORT(_OS_CLIENT) os_svr_stat_delayed_db_info {
public:
  os_unsigned_int32	how_long;
  char*			dbname;

  os_svr_stat_delayed_db_info();
  ~os_svr_stat_delayed_db_info();
};

class _OS_DLLIMPORT(_OS_CLIENT) os_svr_stat_extension {
public:
  os_unsigned_int32		n_log_samples; 
  os_svr_log_stat_sample*	p_log_samples;
  os_unsigned_int32		n_delayed_dbs;
  os_svr_stat_delayed_db_info*	p_delayed_dbs;
  char*				internal;
  char*				reserved[11];	/* future expansion */

  os_svr_stat_extension();
  ~os_svr_stat_extension();
};

class _OS_DLLIMPORT(_OS_CLIENT) os_svr_stat {
public:
  enum os_svr_stat_request_type {
    get_svr_rusage = 0x1,
    get_svr_meter_samples = 0x2,
    get_svr_parameters = 0x4,
    get_client_info_self = 0x8,
    get_client_info_others = 0x10,
    get_log_statistics = 0x20,
    os_svr_stat_request_type_pad = 1<<30
  };

  os_unsigned_int32  struct_version;  
  os_svr_stat_svr_header      header;
  os_svr_stat_svr_parameters *svr_parameters;
  os_svr_stat_svr_rusage     *svr_rusage;
  os_svr_stat_svr_meters     *svr_meter_samples;
  os_unsigned_int32           n_meter_samples;
  os_svr_stat_client_info    *client_info_self;
  os_svr_stat_client_info    *client_info_others;
  os_unsigned_int32           n_clients;
  os_svr_stat_extension      *p_extended_status;

  os_svr_stat();
  ~os_svr_stat();
};

class _OS_DLLIMPORT(_OS_CLIENT) os_db_status_client_info {
public:

  os_svr_stat_client_process *process;   
  os_svr_stat_client_state   *state;
  
  os_db_status_client_info();
  ~os_db_status_client_info();
};


class _OS_DLLIMPORT(_OS_CLIENT) os_db_status_info {
public:

  os_db_status_type          status_type;
  os_unsigned_int32          n_clients;    
  os_db_status_client_info   *client_info;
  
  os_db_status_info();
  ~os_db_status_info();
};

class _OS_DLLIMPORT(_OS_CLIENT) os_free_blocks {
public:
  os_unsigned_int32  struct_version;
  os_unsigned_int32  free_blocks;
  os_unsigned_int32  file_system_size;
  os_unsigned_int32  used_blocks;

  os_free_blocks();
  ~os_free_blocks();
};

/* osverifydb options */
class _OS_DLLIMPORT(_OS_DBUTIL) os_verifydb_options {
public:
  os_boolean verify_segment_zero ;   /* verify the schema segment */
  os_boolean verify_collections ;    /* check all top-level collections */

  os_boolean verify_pointer_verbose; /* print pointers asthey are verified */
  os_boolean verify_object_verbose ; /* print objects as they are verified */
  os_boolean verify_references ;     /* check all OS references */
  
  os_int32  segment_error_limit ;    /* maximum errors per segment */
  os_boolean print_tag_on_errors ;   /* print out the tag value on error */

  enum info_sector_tag_verify_opt_enum { 
    verify_skip = 0,            /* do not verify info sector tag */ 
    verify_report_only = 1,     /* report only */
    verify_upgrade = 2,         /* upgrade info sector tags */
    verify_skip_others = 4      /* skip other verifications */
  } info_sector_tag_verify_opt ;
 
  const void* track_object_ptr ;     /* Track object identified by pointer */
  const char* track_object_ref_string;/* Track the object identified by the */
                                     /* reference string. */

  enum illegal_pointer_actions { default_action, ask_action, null_action, illegal_pointer_action_pad = 1<<30 } illegal_pointer_action ;



  /* Track object identified by segment, cluster, offset. The above 2 are
     close to useless, but need to be preserved for runtime compatibility. */
  os_unsigned_int32 track_object_segment,
                    track_object_cluster,
                    track_object_offset;
  
  /* Constructor, initialize with the default parameter values */
  os_verifydb_options() ;
  os_boolean is_valid_info_sector_tag_verify_opt(os_int32 opt) {
    return opt == verify_skip                               ||
           opt == verify_report_only                        ||
           opt == verify_upgrade                            ||
           opt == (verify_report_only | verify_skip_others) ||
           opt == (verify_upgrade | verify_skip_others) ;
  }
} ;

/****
* Future versions of object store will replace os_verifydb_options with
* this. It includes more information, Provides better input handling,
* andAllows MT behavior (removes global and static data from ndbutilvr)
*
* Issues:
*  Remote schema database verification is unknown
*  Verification of database undergoing schema evolution is unknown
*  Squatter tag..unknown behavior
****/

class os_Verifier_actions;
class _OS_DLLIMPORT(_OS_DBUTIL) os_Verify_options : public os_verifydb_options
{
 public:

  friend class os_Verifier_actions;
  enum supplied_arg { NONE =0, CLUSTER, OFFSET };
  
  os_Verify_options(os_verifydb_options& opt);
  os_Verify_options();
  ~os_Verify_options();

  /* The user has specified the -segment_n switch */
  os_boolean user_specified_segment() { return user_segment; }
  /* The user has specified the -start_cluster switch */
  os_boolean user_specified_cluster() { return !(specified | CLUSTER); }
  /* The user has specified the -start_offset switch */
  os_boolean user_specified_offset()  { return !(specified | OFFSET);  }
  void set_user_specified(os_Verify_options::supplied_arg type) {
    specified |= type;
  }
  
  /* Specify exactly what to verify. This is NOT idempotent */
  void set_range_to_verify(os_unsigned_int32 segment,
    os_unsigned_int32 cluster_start = OS_INT32_MAX,
    os_unsigned_int32 cluster_end   = OS_INT32_MAX,
    os_unsigned_int32 offset_start  = OS_INT32_MAX,
    os_unsigned_int32 offset_end    = OS_INT32_MAX);
  
 private:
  os_boolean        user_segment;
  os_unsigned_int32 specified_segment_number;
  char specified;
  os_unsigned_int32 cluster_number_start;
  os_unsigned_int32 cluster_number_end;
  os_unsigned_int32 start_offset;
  os_unsigned_int32 end_offset;

 private:
  os_Verify_options(const os_Verify_options&) ;
  os_Verify_options& operator=(const os_Verify_options&);
  
 public:
  
  //TBD
  /* se_in_progress_on_db is True if verification is being done on a        */
  /* database for which schema evolution has not yet been completed.        */
  //  os_boolean se_in_progress;
  //  os_unsigned_int32 squatter_tag;
};



class os_dbu_walk_tree {
public:
  /* returns 0 for ok, one for do not descend into here */
  virtual os_int32 visit_action (os_unsigned_int32 level, os_rawfs_entry* entry) = 0;
  virtual void post_visit_action (os_unsigned_int32, os_rawfs_entry*);
  virtual void visit_failed(os_unsigned_int32 level);

  os_unsigned_int32 const get_version();
  const char* get_server_host() const;
  const char* get_cur_path() const;
  void set_cur_path(const char * path);
  void set_server_host(const char * host);

protected:
  os_dbu_walk_tree(os_unsigned_int32 vers, char const * host, char const * path);
  os_dbu_walk_tree();
  ~os_dbu_walk_tree();

private:
  os_unsigned_int32 version;	/* allow for link-compatible expansion */
  char * p_server_host;
  char * p_cur_path;

  os_dbu_walk_tree(const os_dbu_walk_tree&);
  os_dbu_walk_tree& operator=(const os_dbu_walk_tree&);
};

/* For setting options needed for os_dbutil::osdbcontrol. */

class _OS_DLLIMPORT(_OS_DBUTIL) os_dbcontrol_options {
public:
  os_boolean   flag_offline;	  /* -offline set database offline.*/
  os_boolean   flag_online;	  /* -online  set database online.*/
  os_boolean   flag_kill_clients; /* -kill_clients kill all clients 
                                      using a db before setting offline. */
  os_boolean   flag_status;	/* -status display database status. */
  os_boolean   flag_statistics; /* -statistics  display database I/O statistics. */
  os_boolean   flag_do_print;   /* Print status or statistic information,  
                                   default is true, always print. */

  char *       reason_str;      /* A reason string that is appended to the
                                   offline exception message. The string
                                   is deleted in ~os_dbcontrol_options(). */

  os_dbcontrol_options();
  ~os_dbcontrol_options();

  void reset();                 /* Reset all options. */

  os_boolean validate_options();  /* Returns true if options are valid. */

};

/* The results of os_dbutil::osdbcontrol -status or -statistic options
   are saved when a pointer to this class is passed to os_dbutil::osdbcontol.*/

class _OS_DLLIMPORT(_OS_DBUTIL) os_dbcontrol_result {
public:
 
  os_unsigned_int32 n_info;      /* Number of pathnames and info. */

  os_db_statistic_info ** statistic_info; /* Array of statistic info. */ 
  os_db_status_info ** status_info;       /* Array of status info. */
  char ** pathnames;                      /* Array of pathnames. */

  os_dbcontrol_result();
  ~os_dbcontrol_result();

  /* Format and print status information for the database specified by
     index which corresponds to the pathnames array. */
  void format_and_print_status(os_unsigned_int32 index);
 
  /* Format and print statistic information for the database specified by
     index which corresponds to the pathnames array */
  void format_and_print_statistics(os_unsigned_int32 index);


  /* Initialize all data members.  Always called by os_dbutil::osdbcontrol.*/ 
  void initialize(const char **pathns, os_unsigned_int32 n_pathns, 
                  const os_dbcontrol_options & options);

protected:
  void _clear();

};


class _OS_DLLIMPORT(_OS_DBUTIL) os_dbutil
{
   public:
     /* methods */

      static os_unsigned_int32 get_sector_size();
      static void set_client_name (const char *name);
      static char const* get_client_name();
      static void close_all_connections();
      static void close_server_connection(char const* hostname);
      static void close_all_server_connections();

      static os_boolean compare_schemas(const os_database* db1,
					const os_database* db2,
					os_boolean verbose = 1);

      static char *cmgr_shutdown(const char *hostname,         /* in  */
				 os_int32 cm_version_number);  /* in  */

      static char *cmgr_remove_file(const char *hostname,       /* in  */
			   os_int32 cm_version_number);        /* in  */

      static void cmgr_stat(const char *hostname,              /* in  */
			    os_int32 cm_version_number,        /* in  */
			    os_cmgr_stat *cmstat_data);        /* out */

      static void set_verify_rds_also(os_boolean value);       /* in */

      static os_boolean svr_checkpoint(const char *hostname);  /* in  */

      static os_boolean svr_client_kill(const char *server_host, /* in   */
				     os_int32 client_pid,     /* in   */
				     const char *client_name, /* in   */
				     const char *client_hostname, /* in   */
				     os_boolean all,	      /* in   */
				     os_int32 &status);	      /* out  */

      static char* svr_ping(const char *server_host, 	/* in */
	                    os_svr_ping_state &state); 	/* out */

      static os_boolean svr_shutdown(const char *server_host);   /* in  */

      static void svr_stat(const char *server_host,          /* in  */
			   os_unsigned_int32 request_bits,   /* in  */
			   os_svr_stat *svrstat_data);        /* out */

      static void copy_database(const char *src_database_name,  /* in  */
				const char *dest_database_name);/* in  */

      static void disk_free(const char *hostname,          /* in  */
			    os_free_blocks *free_blocks);  /* out */


      static os_char_p* expand_global(char const *glob_path,     /* in     */
				  os_unsigned_int32 &n_entries);

      static void remove(char const *path);

      static void mkdir(const char *path,
			const os_unsigned_int32 mode,
			os_boolean create_missing_dirs = 0);

      static void rmdir(const char *path);

      static void rename(const char *source, const char *target);

      static void make_link(const char *target_name, const char *link_name);

      static os_rawfs_entry *stat(const char *path,
				  const os_boolean b_chase_links = 1);

      static os_rawfs_entry_p *list_directory(const char *path,	 /* in */
				  os_unsigned_int32 &n_entries); /* out */

      static void chown(const char *pathname, const char *uname);

      static void chgrp(const char *pathname, const char *gname);

      static void chmod(const char *pathname, const os_unsigned_int32 mode);

      static void rehost_link(const char *pathname, const char *new_host);

      static void rehost_all_links(const char *server_host, const char *old_host,
				   const char *new_host);

      static os_boolean svr_debug(const char *server_host,
				  os_unsigned_int32 debug_level);
      /* set_application_schema_path return:
           if database_pathname is NULL, then
               return new storage containing the current path name.
	   if database_pathname has a value
	       return 0, signal if error.
      */
      static char *set_application_schema_path(const char *executable_pathname,
					       const char *database_pathname);

      static os_int32 ossize(const char *pathname,
			     const os_size_options *options);

      static os_unsigned_int32 osverifydb(const char *dbname,
					  os_verifydb_options* opt= 0) ;

      static os_unsigned_int32 osverifydb(const char* dbname,
            os_Verify_options& opt);

      static os_unsigned_int32
      osverifydb_one_segment(const char *database_pathname,
			     os_unsigned_int32 segment_number,
			     os_unsigned_int32 cluster_start_number = 0,
			     os_unsigned_int32 cluster_end_number = 0,
			     os_unsigned_int32 start_offset = 0,
			     os_unsigned_int32 end_offset = 0,
			     os_verifydb_options *opt = 0) ;

      static void osfixvh(const char* dbname, os_boolean verify_only);

      static os_boolean absolute_pathname(const char *pathname);

      static os_boolean split_pathname(const char *input_pathname_arg,
				       os_char_p *server_name,
				       os_char_p *filename);

      static os_boolean file_db_pathname(const char *pathname);

      static void walk_tree (char const * start_path, os_dbu_walk_tree& arg);

      static void initialize();

      static const char* hostof(const char *pathname);

      static void osdbcontrol(const char **pathnames, 
                              os_unsigned_int32 n_pathnames, 
                              os_dbcontrol_options & options,
                              os_dbcontrol_result * results = 0);

      static void format_and_print_statistics(const os_db_statistic_info& stats);

};

#include <ostore/hdrend.hh>
#endif  /* __DBUTIL_HH__ */






