#include <time.h>
#include <sys/timeb.h>
#ifdef _MSC_VER 
#include <windows.h>
#include <windef.h>
#include <winbase.h>
#else
//extern "C" void ftime(struct timeb*);
#include <sys/timeb.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ostore/dbutil.hh>
#include <ostore/osreleas.hh>
#include <assert.h>
#include "osu_monitor.hh"
#include "osu_monitor_internal.hh"
#include "osu_timer.hh"
#include "osu_sessmgt.hh"
#include "osu_mutex.hh"
#include "osu_datetime.hh"
#include "osu_stream.hh"

// need getpid
#ifdef _MSC_VER
#include <process.h>
#else
#include <unistd.h>
#endif

#if OS_MAJOR_RELEASE < 6
static const char* ncounters[] = {
  "n_notify_receive_no_db",
  "n_notify_on_commit_total",
  "n_notify_on_commit",
  "n_notify_immediate_total",
  "n_notify_immediate",
  "n_notify_receive_string_piece",
  "n_notify_receive_string",
  "n_notify_receive_long",
  "n_notify_receive_reads",
  "n_notify_receive_waits",
  "n_notify_receive_calls",
  "n_range_cache_hits",
  "n_range_cache_probes",
  "n_outbound_access_hooks_called",
  "n_inbound_access_hooks_called",
  "n_softfault_segments_in_use",
  "n_data_segments_in_use",
  "n_scanner_false_positives",
  "n_scanner_rejects",
  "n_scanner_pages",
  "n_easily_evictable",
  "n_return_easy_pages",
  "n_return_hard_pages",
  "n_fault_ewlw",
  "n_fault_upgrade",
  "n_fault_lock",
  "n_fault_detect_usage",
  "n_fault_nested_ro",
  "n_upgrade_lock",
  "n_upgrade_cache",
  "n_real_read_segment_pages",
  "n_real_read_segment",
  "n_real_read_page",
  "n_returned_dirtied",
  "n_returned_locked",
  "n_returned_flushed",
  "n_not_identity_map",
  "n_crowded",
  "n_nested_aborts",
  "n_top_level_aborts",
  "n_nested_commits",
  "n_top_level_commits",
  "n_pages_committed",
  "n_grow_commseg",
  "n_unwire",
  "n_wire",
  "n_assign_for_segment",
  "n_translate_pointer",
  "n_assure_all_assigned",
  "n_rel_page_hetero_out",
  "n_rel_page_hetero_in",
  "n_rel_page_out",
  "n_rel_page_in",
  "n_evict",
  "n_return_pages",
  "n_return_some_pages",
  "n_fetch_segment",
  "n_snapshot",
  "n_page_fault_active",
  "n_touch_page",
  "n_fetch_page",
  "n_page_fault",
  "n_sigsegv"
};
#else
static const char* ncounters[] = {
  "n_create_page",
  "n_evict",
  "n_fetch_page",
  "n_nested_aborts",
  "n_nested_commits",
  "n_page_fault",
  "n_page_fault_active",
  "n_pages_committed",
  "n_sigsegv",
  "n_snapshot_page",
  "n_top_level_aborts",
  "n_top_level_commits",
  "n_touch_page",
  "n_translate_pointer",
  "n_unwire",
  "n_wire"
};
#endif
static int nncounters = sizeof(ncounters)/sizeof(ncounters[0]);


#if OS_MAJOR_RELEASE < 6
static const char* rtcounters[] = {
  "_RT__Count_notify_initial_conn",
  "_RT__Count_notify_receive",
  "_RT__Count_copy_segtrm",
  "_RT__Count_segtrm_from_prm",
  "_RT__Count_segtrm_assure_all_assigned",
  "_RT__Count_reloc_address_with_bv",
  "_RT__Count_reloc_address",
  "_RT__Count_reloc_for_return",
  "_RT__Count_reloc_out_access_hooks",
  "_RT__Count_reloc_in_access_hooks",
  "_RT__Count_reloc_page_out",
  "_RT__Count_reloc_page_in",
  "_RT__Count_reloc_to_update_maps",
  "_RT__Count_reloc_out_all_in_use",
  "_RT__Count_prepare_normal_commit",
  "_RT__Count_prepare_mapped_commit",
  "_RT__Count_notify_unsubscribe",
  "_RT__Count_notify_subscribe",
  "_RT__Count_notify_on_commit",
  "_RT__Count_notify_immediate",
  "_RT__Count_server_ping",
  "_RT__Count_do_authentication",
  "_RT__Count_commit_trans_rpc",
  "_RT__Count_abort_rpc",
  "_RT__Count_end_2p_commit_rpc",
  "_RT__Count_start_2p_commit_rpc",
  "_RT__Count_seg_size_rpc",
  "_RT__Count_del_segment_rpc",
  "_RT__Count_close_connect_rpc",
  "_RT__Count_upgrade_rpc",
  "_RT__Count_commit_mapped_rpc",
  "_RT__Count_commit_rpc",
  "_RT__Count_finish_xa_rpc",
  "_RT__Count_prepare_xa_rpc",
  "_RT__Count_vote_rpc",
  "_RT__Count_create_segments_rpc",
  "_RT__Count_on_exit",
  "_RT__Count_startup",
  "_RT__Count_signal_handler_1",
  "_RT__Count_signal",
  "_RT__Count_validate_schema",
  "_RT__Count_translate_pathname",
  "_RT__Count_rawhfs_set_seg_access",
  "_RT__Count_rawhfs_get_seg_access",
  "_RT__Count_rawhfs_delete",
  "_RT__Count_rawhfs_stat",
  "_RT__Count_rawhfs_open_lookup",
  "_RT__Count_rawhfs_create",
  "_RT__Count_write_lock_seg",
  "_RT__Count_read_lock_seg",
  "_RT__Count_write_lock_db",
  "_RT__Count_read_lock_db",
  "_RT__Count_start_abort_only",
  "_RT__Count_database_reconnect",
  "_RT__Count_reconnect",
  "_RT__Count_release_db_handle_1",
  "_RT__Count_lookup_file_db_21_rpc",
  "_RT__Count_file_db_size",
  "_RT__Count_del_file_db",
  "_RT__Count_canonical_to_path",
  "_RT__Count_path_to_canonical",
  "_RT__Count_lookup_file_db_canonical_rpc",
  "_RT__Count_set_tp_priority",
  "_RT__Count_get_lock_status_1",
  "_RT__Count_del_db_1_rpc",
  "_RT__Count_del_db_by_handle",
  "_RT__Count_what_segments2",
  "_RT__Count_create_file_db_21_rpc",
  "_RT__Count_segment_rpc",
  "_RT__Count_create_file_db_and_segs_21_rpc",
  "_RT__Count_get_database_handle",
  "_RT__Count_mapped_return_rpc",
  "_RT__Count_return_rpc",
  "_RT__Count_page_rpc",
  "_RT__Count_open_conn",
  "_RT__Count_hello",
  "_RT__Count_return_hard",
  "_RT__Count_return_easy",
  "_RT__Count_return_some",
  "_RT__Count_map_pages",
  "_RT__Count_protect",
  "_RT__Count_protect_page",
  "_RT__Count_map_prot",
  "_RT__Count_map_mmap_3",
  "_RT__Count_map_mmap_2",
  "_RT__Count_map_mmap_1"
};
#else
static const char* rtcounters[] = {
  "_RT__Count_allocate_huge_object",
  "_RT__Count_allocate_normal_object",
  "_RT__Count_cluster_size_rpc",
  "_RT__Count_commit_rpc",
  "_RT__Count_create_cluster_rpc",
  "_RT__Count_create_huge_object_rpc",
  "_RT__Count_create_segment_rpc",
  "_RT__Count_delete_cluster_rpc",
  "_RT__Count_delete_huge_object",
  "_RT__Count_delete_normal_object",
  "_RT__Count_delete_segment_rpc",
  "_RT__Count_map_page",
  "_RT__Count_mapped_commit_rpc",
  "_RT__Count_mapped_return_rpc",
  "_RT__Count_page_rpc",
  "_RT__Count_prefetch_rpc",
  "_RT__Count_protect_page",
  "_RT__Count_read_lock_cluster",
  "_RT__Count_read_lock_db",
  "_RT__Count_read_lock_seg",
  "_RT__Count_reloc_address",
  "_RT__Count_reloc_page_forward",
  "_RT__Count_reloc_page_in",
  "_RT__Count_reloc_page_out",
  "_RT__Count_reloc_page_scan",
  "_RT__Count_reloc_page_sp_conditional_decache",
  "_RT__Count_reloc_page_sp_resolve",
  "_RT__Count_reloc_page_spm_gc",
  "_RT__Count_return_rpc",
  "_RT__Count_server_side_allocation",
  "_RT__Count_signal",
  "_RT__Count_upgrade_rpc",
  "_RT__Count_validate_schema",
  "_RT__Count_write_lock_cluster",
  "_RT__Count_write_lock_db",
  "_RT__Count_write_lock_seg"
};
#endif
static int nrtcounters = sizeof(rtcounters)/sizeof(rtcounters[0]);

#if OS_MAJOR_RELEASE < 6
class os_session {
public:
  static os_session* get_current() {
    if (theCURRENT == 0) {
      theCURRENT = new os_session;
    }
    return theCURRENT;
  }
  const char* get_name() {
    return "default";
  }

protected:
  static os_session* theCURRENT;
};
os_session* os_session::theCURRENT = 0;

#endif

static osu_sys_timer     g_timer;  // timers start at initialization
static osu_wall_timer    w_timer; 
static osu_low::mutex*   g_mutex = 0;
static osu_event_stream* g_out   = 0;
static osu_datetime      g_dt    = osu_datetime::now();

class osu_stream_guard {
public:
  osu_stream_guard() { ; }
  ~osu_stream_guard() { if (g_out) delete g_out; }
};

static osu_stream_guard beSureToFlush;

// NOTE: There is code that limits these values to [0-31]...

static os_unsigned_int32 VERSION    = 0;
static os_unsigned_int32 TXNBEG     = 1;   // osu_monitor_txn
static os_unsigned_int32 TXNCOMMIT1 = 2;   // osu_monitor_txn
static os_unsigned_int32 TXNCOMMIT2 = 3;   // osu_monitor_txn
static os_unsigned_int32 TXNABORT1  = 4;   // osu_monitor_txn
static os_unsigned_int32 TXNABORT2  = 5;   // osu_monitor_txn
static os_unsigned_int32 TXNRETRY   = 6;   // osu_monitor_txn
static os_unsigned_int32 TXNRPC     = 7;   // osu_monitor_txn
static os_unsigned_int32 TXNXA      = 8;   // osu_monitor_txn
static os_unsigned_int32 FAULT      = 9;   // osu_monitor_page
static os_unsigned_int32 FETCH      = 10;  // osu_monitor_page
static os_unsigned_int32 ACTIVE     = 11;  // osu_monitor_page
static os_unsigned_int32 RETURN     = 12;  // osu_monitor_page
static os_unsigned_int32 RELOCIN    = 13;  // osu_monitor_page
static os_unsigned_int32 RELOCOUT   = 14;  // osu_monitor_page
static os_unsigned_int32 RELOCFWD   = 15;  // osu_monitor_page
static os_unsigned_int32 COMMIT     = 16;  // osu_monitor_page
static os_unsigned_int32 UPGRADE    = 17;  // osu_monitor_page
static os_unsigned_int32 DEADLOCK   = 18;  // osu_monitor_page
static os_unsigned_int32 CREATE     = 19;  // osu_monitor_page
static os_unsigned_int32 DBHANDLE   = 20;  // osu_monitor_dbhandle
static os_unsigned_int32 SESSID     = 21;  // osu_monitor_sessid
static os_unsigned_int32 RTCOUNTER1 = 22;  //...
static os_unsigned_int32 RTCOUNTER2 = 23;  //...
static os_unsigned_int32 SVRMETERS  = 24;  // osu_monitor_svr_meters
static os_unsigned_int32 USER       = 25;
static os_unsigned_int32 RTCOUNTER3 = 26;  //...
static os_unsigned_int32 NCOUNTER0  = 27;  // Displays names of NCOUNTERS
static os_unsigned_int32 NCOUNTER1  = 28;  // Display values of NCOUNTERS

static os_unsigned_int32 osu_clock() {
  w_timer.stop();
  return w_timer.msecs();
}  

struct osu_monitor_event {
  osu_monitor_event(os_unsigned_int32 opcode)
    : _opcode(opcode), _clock(osu_clock()),
      _session(os_session::get_current())
  {
    ;
  }
  void write(osu_event_stream*);
public:
  os_unsigned_int32 _opcode;
  os_unsigned_int32 _clock;
  os_session*       _session;
};


struct osu_monitor_page :public osu_monitor_event {
public:
  osu_monitor_page(os_unsigned_int32 opcode, os_database*,
		   os_unsigned_int32 segno,  os_unsigned_int32 clus_no,
		   os_unsigned_int32 pgno,   os_boolean flag = 0,
		   os_unsigned_int32 n_pages = 1);
  void write(osu_event_stream*);
public:
  os_database*      _database;
  os_unsigned_int32 _segment_no;
  os_unsigned_int32 _cluster_no;
  os_unsigned_int32 _page_no;
  os_unsigned_int32 _flag;
  os_unsigned_int32 _n_pages;
};

struct osu_monitor_svr_meters :public osu_monitor_event {
public:
  osu_monitor_svr_meters(char* host) : osu_monitor_event(SVRMETERS)
  {
    _host = host;
    os_dbutil::svr_stat(host,os_svr_stat::get_client_info_self,&_stat);
  }
  void write(osu_event_stream*);
public:
  os_svr_stat _stat;
  char*       _host;
};


struct osu_monitor_dbhandle :public osu_monitor_event {
public:
  osu_monitor_dbhandle() : osu_monitor_event(DBHANDLE) { ; }
  void write(osu_event_stream*);
public:
  os_database*      _database;
  char              _dbname[128];
};

struct osu_monitor_sessid : public osu_monitor_event {
public:
  osu_monitor_sessid() : osu_monitor_event(SESSID) { ; }
  void write(osu_event_stream*);
public:
  char              _name[64];
  time_t            _time;
};

struct osu_monitor_txn :public osu_monitor_event {
public:
  osu_monitor_txn(os_unsigned_int32 opcode) : osu_monitor_event(opcode) { ; }
  void write(osu_event_stream*);
public:
  void*              _txnid;
  os_unsigned_int32  _usertime;
  os_unsigned_int32  _kerneltime;
  os_unsigned_int32  _walltime;
  char               _txnname[64];
};




inline void osu_monitor_event::write(osu_event_stream* out)
{
  out->write(this->_opcode);
  out->write(this->_session);
  out->write(this->_clock);
}


inline void osu_monitor_svr_meters::write(osu_event_stream* out)
{
  if (_stat.client_info_self) {
    os_svr_stat_client_info& info = *_stat.client_info_self;
    if (info.meters) {
      os_svr_stat_client_meters& meters = *info.meters;
      osu_sync sync(*g_mutex);

      out->begin();
      osu_monitor_event::write(out);
      out->write(_host);
      out->write(meters.n_receive_msgs );
      out->write(meters.n_callback_msgs );
      out->write(meters.n_callback_sectors_requested );
      out->write(meters.n_callback_sectors_succeeded );
      out->write(meters.n_sectors_read );
      out->write(meters.n_sectors_written );
      out->write(meters.n_deadlocks );
      out->write(meters.n_lock_timeouts );
      out->write(meters.n_commit );
      out->write(meters.n_phase_2_commit );
      out->write(meters.n_readonly_commit );
      out->write(meters.n_abort );
      out->write(meters.n_phase_2_abort );
      out->write(meters.n_notifies_sent );
      out->write(meters.n_notifies_received );
      out->write(meters.n_lock_waits);
      out->write(meters.total_lock_wait_time);
      out->end();
    }
  }
}


inline void osu_monitor_txn::write(osu_event_stream* out)
{
  osu_sync sync(*g_mutex);

  out->begin();
  osu_monitor_event::write(out);
  out->write(this->_txnid);
  out->write(this->_usertime);
  out->write(this->_kerneltime);
  out->write(this->_walltime);
  out->write(this->_txnname);
  out->end();
}

osu_monitor_page::osu_monitor_page(os_unsigned_int32 opcode, os_database* db,
				   os_unsigned_int32 segno,  os_unsigned_int32 clusno,
				   os_unsigned_int32 pgno,   os_boolean flag,
				   os_unsigned_int32 npages)
  : osu_monitor_event(opcode)
{
  _database   = db;
  _segment_no = segno;
  _cluster_no = clusno;
  _page_no    = pgno;
  _flag       = flag;
  _n_pages    = npages;
}

inline void osu_monitor_page::write(osu_event_stream* out)
{
  osu_sync sync(*g_mutex);

  out->begin();
  osu_monitor_event::write(out);
  out->write(this->_database);
  out->write(this->_segment_no);
  out->write(this->_cluster_no);
  out->write(this->_page_no);
  out->write(this->_flag);
  out->write(this->_n_pages);
  out->end();
}

inline void osu_monitor_dbhandle::write(osu_event_stream* out)
{
  osu_sync sync(*g_mutex);

  out->begin();
  osu_monitor_event::write(out);
  out->write(this->_database);
  out->write(this->_dbname);
  out->end();
}

inline void osu_monitor_sessid::write(osu_event_stream* out)
{
  osu_sync sync(*g_mutex);
  out->begin();
  osu_monitor_event::write(out);
  out->write(this->_time);
  out->write(this->_name);
  out->end();
}

osu_monitor_internal::osu_monitor_internal()
  : _databases(5),
    _hosts(5)
{
  _active = 0;
  char* values = ::getenv("OSU_MONITOR");
  while (*values) {
    char ch = *values;
    static const char* active_ndx = "AWCDFRSEUTMN";
    static os_unsigned_int32 active[] = {
      1UL<<ACTIVE,
      1UL<<COMMIT,
      1UL<<CREATE,
      1UL<<DEADLOCK,
      1UL<<FAULT,
      1UL<<FETCH,
      (1UL<<RELOCFWD)|(1<<RELOCIN)|(1<<RELOCOUT),
      1UL<<RETURN,
      1UL<<UPGRADE,
      1UL<<RTCOUNTER1,
      1UL<<SVRMETERS,
      1UL<<NCOUNTER0
    };
    const char* a = ::strchr(active_ndx,ch);
    if (a) {
      int ndx =  a - active_ndx;
      _active |= active[ndx];
    }
    values++;
  }

  if (check(RTCOUNTER1)) {
    objectstore::record_realtime_counters(1);
    // Write out realtime counter names.
    osu_monitor_event event2(RTCOUNTER3);
    g_out->begin();
    event2.write(g_out);
    for (int n = 0; n < nrtcounters; n++) {
      g_out->write(rtcounters[n]+11);
    }
    g_out->end();
  }
  if (check(NCOUNTER0)) {
#if OS_MAJOR_RELEASE > 5
    objectstore::enable_counters();
#endif
    // Write out ncounter names.
    osu_monitor_event event3(NCOUNTER0);
    g_out->begin();
    event3.write(g_out);
    for (int n = 0;  n < nncounters; n++) {
      g_out->write(ncounters[n]);
    }
    g_out->end();
  }


  // write SESSID
  osu_monitor_sessid data;
  const char* sessname = os_session::get_current()->get_name();
  data._time    = ::time(0);
  ::memset(data._name,0,sizeof(data._name));
  ::strncpy(data._name,sessname,sizeof(data._name));
  data.write(g_out);

  // mask the bits for non page activity
  unsigned long mask = ~((1UL<<RTCOUNTER1)|(1UL<<SVRMETERS)|(1UL<<NCOUNTER0));
  if (_active & mask) {
    osu_page_observer::subscribe(this);
  }
  osu_txn_observer::subscribe(this);
}

osu_monitor_internal::~osu_monitor_internal()
{
  unsigned long mask = ~((1UL<<RTCOUNTER1)|(1UL<<SVRMETERS)|(1UL<<NCOUNTER0));
  if (_active & mask) {
    osu_page_observer::unsubscribe(this);
  }
  osu_txn_observer::unsubscribe(this);
}  


void osu_monitor_internal::handle(const os_transaction_hook::event_type evtype,
			 const os_transaction* txn)
{
  g_timer.stop();

#if OS_MAJOR_RELEASE > 5
  if (evtype == os_transaction_hook::after_commit ||
      evtype == os_transaction_hook::after_abort) {
#else
  if (evtype == os_transaction_hook::after_commit) {
#endif

    if (check(RTCOUNTER1)) {
      osu_sync sync(*g_mutex);
    
      osu_monitor_event rtevent1(RTCOUNTER1);
      g_out->begin();
      rtevent1.write(g_out);
      int i = 0;
      for (i =0;i < nrtcounters; i++) {
	g_out->write(objectstore::read_counter(rtcounters[i]));
      }
      g_out->end();

      osu_monitor_event rtevent2(RTCOUNTER2);
      g_out->begin();
      rtevent2.write(g_out);
      for (i =0;i < nrtcounters; i++) {
	g_out->write(objectstore::read_counter(rtcounters[i]+4));
      }
      g_out->end();
    }

    if (check(NCOUNTER0)) {
      osu_sync sync(*g_mutex);

      osu_monitor_event nevent(NCOUNTER1);
      g_out->begin();
      nevent.write(g_out);
      for (int i=0; i < nncounters; i++) {
	g_out->write(objectstore::read_counter(ncounters[i]));
      }
      g_out->end();
    }

    if (check(SVRMETERS)) {

      // We assume that once you are connected to a server
      // you don't get disconnected...

      os_int32 nservers = objectstore::get_n_servers();
      if (nservers != _hosts.cardinality()) {
	os_server_p* servers = new os_server_p[nservers];
	objectstore::get_all_servers(nservers, servers, nservers);
	for (os_int32 i = 0; i < nservers; i++) {
	  char* host = (char*) servers[i]->get_host_name();
	  unsigned short n = _hosts.cardinality();
	  for (unsigned short p = 0; p < n; p++) {
	    char* h = (char*) _hosts[p];
	    if (::strcmp(h,host) == 0) {
	      delete [] host;
	      host = 0;
	    }
	  }
	  if (host) _hosts.insert(host);
	}
	delete [] servers;
      }

      unsigned short n = _hosts.cardinality();
      if (n) {
	for (unsigned short p = 0; p < n; p++) {
	  char* host = (char*) _hosts[p];
	  osu_monitor_svr_meters event(host);
	  event.write(g_out);
	}
      }
    }
  }

  // print out transaction header.
#if OS_MAJOR_RELEASE < 6
  //EVENT TYPES were defined for R6, need to readjust R5 values to R6...
  //R5 after_begin = 0, before_commit = 1, after_commit = 2, before_abort = 3,
  //   before_retry = 4, before_rpc = 5, before_finish_xa_commit = 6,
  //R6 after_begin = 1, before_commit = 2, after_commit = 3, before_abort = 4,
  //   after_abort = 5, before_retry = 6, before_rpc = 7,
  //   before_finish_xa_commit = 8
  int ntype = evtype+1;
  if (ntype > 4) ntype++;
#else
  int ntype = evtype;
#endif

  osu_monitor_txn data(ntype);
  data._walltime   = g_timer.msecs();
  data._usertime   = g_timer.user();
  data._kerneltime = g_timer.kernel();
  data._txnid      = (void*) txn;
  ::memset(data._txnname,0,sizeof(data._txnname));
  char* txnname = 0;
  if ((evtype == os_transaction_hook::after_begin) && (txnname = txn->get_name())) {
    ::strncpy(data._txnname,txnname,sizeof(data._txnname));
  }
  data.write(g_out);
  //g_out->flush();
}

void osu_monitor_internal::check_db(os_database* db)
{
  if (_databases.contains(db) == 0) {
    _databases.insert(db);
    osu_monitor_dbhandle data;
    data._database = db;
    char* pathname = db->get_pathname();
    ::memset(data._dbname,0,sizeof(data._dbname));
    ::strncpy(data._dbname,pathname,sizeof(data._dbname));
    data.write(g_out);
    delete [] pathname;
  }
}

os_boolean osu_monitor_internal::check(os_unsigned_int32 opcode)
{
  return ((1UL <<opcode) & _active);
}

void osu_monitor_internal::page_fault (os_char_p addr,
			      os_database *database,
			      os_unsigned_int32 segment_no,
			      os_unsigned_int32 cluster_no,
			      os_unsigned_int32 page_no,
			      os_boolean b_for_write)
{
  check_db(database);
  if (check(FAULT)) {
    osu_monitor_page X(FAULT,database,segment_no,cluster_no,
		       page_no,b_for_write);
    X.write(g_out);
  }
}

void osu_monitor_internal::page_fetch (os_database *database,
			      os_unsigned_int32 segment_no,
			      os_unsigned_int32 cluster_no,
			      os_unsigned_int32 page_no,
			      os_unsigned_int32 n_pages,
			      os_boolean b_for_write)
{
  if (check(FETCH)) {
    osu_monitor_page X(FETCH,database,segment_no,
		       cluster_no,page_no,b_for_write,n_pages);
    X.write(g_out);
  }
}

void osu_monitor_internal::fault_active (os_database *database,
				os_unsigned_int32 segment_no,
				os_unsigned_int32 cluster_no,
				os_unsigned_int32 page_no,
				os_boolean b_for_write)
{
  if (check(ACTIVE)) {
    osu_monitor_page X(ACTIVE,database,segment_no,cluster_no,
		       page_no,b_for_write);
    X.write(g_out);
  }
}

void osu_monitor_internal::return_pages (os_database *database,
				os_unsigned_int32 segment_no,
				os_unsigned_int32 cluster_no,
				os_unsigned_int32 page_no,
				os_unsigned_int32 n_pages,
				os_boolean dirty_p)
{
  if (check(RETURN)) {
    osu_monitor_page X(RETURN,database,segment_no,
		       cluster_no,page_no,dirty_p,n_pages);
    X.write(g_out);
  }
}

void osu_monitor_internal::reloc_page_in (os_database *database,
				 os_unsigned_int32 segment_no,
				 os_unsigned_int32 cluster_no,
				 os_unsigned_int32 page_no)
{
  if (check(RELOCIN)) {
    osu_monitor_page X(RELOCIN,database,segment_no,
		       cluster_no,page_no);
    X.write(g_out);
  }
}


void osu_monitor_internal::reloc_page_out (os_database *database,
				  os_unsigned_int32 segment_no,
				  os_unsigned_int32 cluster_no,
				  os_unsigned_int32 page_no)
{
  if (check(RELOCOUT)) {
    osu_monitor_page X(RELOCOUT,database,segment_no,
		       cluster_no,page_no);
    X.write(g_out);
  }
}

void osu_monitor_internal::reloc_page_fwd (os_database *database,
				  os_unsigned_int32 segment_no,
				  os_unsigned_int32 cluster_no,
				  os_unsigned_int32 page_no)
{
  if (check(RELOCFWD)) {
    osu_monitor_page X(RELOCFWD,database,segment_no,
		       cluster_no,page_no);
    X.write(g_out);
  }
}

void osu_monitor_internal::commit_pages (os_database *database,
				os_unsigned_int32 segment_no,
				os_unsigned_int32 cluster_no,
				os_unsigned_int32 page_no,
				os_unsigned_int32 n_pages)
{
  if (check(COMMIT)) {
    osu_monitor_page X(COMMIT,database,segment_no,cluster_no,
		       page_no,0,n_pages);
    X.write(g_out);
  }
}

void osu_monitor_internal::upgrade_lock (os_database *database,
				os_unsigned_int32 segment_no,
				os_unsigned_int32 cluster_no,
				os_unsigned_int32 page_no,
				os_boolean b_write_lock)
{
  if (check(UPGRADE)) {
    osu_monitor_page X(UPGRADE,database,segment_no,cluster_no,
		       page_no,b_write_lock);
    X.write(g_out);
  }
}

void osu_monitor_internal::deadlock (os_database *database,
			    os_unsigned_int32 segment_no,
			    os_unsigned_int32 cluster_no,
			    os_unsigned_int32 page_no,
			    os_unsigned_int32 n_pages)
{
  if (check(DEADLOCK)) {
    osu_monitor_page X(DEADLOCK,database,segment_no,cluster_no,
		       page_no,0,n_pages);
    X.write(g_out);
  }
}

void osu_monitor_internal::page_create (os_database *database,
			       os_unsigned_int32 segment_no,
			       os_unsigned_int32 cluster_no,
			       os_unsigned_int32 page_no,
			       os_unsigned_int32 n_pages)
{
  if (check(CREATE)) {
    osu_monitor_page X(CREATE,database,segment_no,cluster_no,
		       page_no,0,n_pages);
    X.write(g_out);
  }
}

struct osu_monitor_user_event :public osu_monitor_event {
public:
  osu_monitor_user_event(const char* str)
    : osu_monitor_event(USER),
      _str(str)
  {
    ;
  }
  void write(osu_event_stream* o)
  {
    osu_sync sync(*g_mutex);
    o->begin();
    osu_monitor_event::write(o);
    o->write(_str);
    o->end();
  }
protected:
  const char* _str;
};


// osu_monitor has a protected destructor.  The osu_sessdata_ptr
// requires a public destructor.  So this hack will give us a public
// destructor.

class osu_monitor_hack  :public osu_monitor {
public:
  osu_monitor_hack() : osu_monitor() { ; }
  ~osu_monitor_hack() { ; }
};

void osu_monitor_internal::initialize_all()
{
#if OS_MAJOR_RELEASE > 5
  os_session* sess = os_session::get_current();

  os_unsigned_int32 n = os_session::get_n_sessions();
  os_session** _sessions = os_session::get_all_sessions(n);
  for (int i =0;i < n; i++) {
    os_session::set_current(_sessions[i]);
    osu_monitor_internal::initialize();
  }
  os_session::set_current(sess);

  delete [] _sessions;
#else
  osu_monitor_internal::initialize();
#endif
}


char* toupper(char* str)
{
  char* r = str;
  while (*r) {
    if (*r >= 'a' && *r <= 'z') *r = 'A' + (*r - 'a');
    r++;
  }
  return str;
}

void osu_monitor_internal::initialize()
{
  static char* osu_monitor_env = ::getenv("OSU_MONITOR");
  static char* arg = osu_monitor_env
    ? toupper(::strdup(osu_monitor_env))
    : 0;

  if (osu_monitor_env) {
    if (g_mutex == 0) g_mutex = new osu_low::mutex();

    if (g_out == 0) {
      osu_sync sync(*g_mutex);
      if (g_out == 0) {
	const char* uri = ::getenv("OSU_MONITOR_URL");
	g_out = osu_event_stream::makeInstance(uri);
	if (g_out == 0) {
	  char name[128];
	  sprintf(name,"osu_monitor_%d.txt",getpid());
	  g_out = new osu_event_fstream(name);
	}
      
	// Write out version info...
	g_out->begin();
	osu_monitor_event event(VERSION);
	event.write(g_out);
	g_out->write((unsigned int)1);
	g_out->write((unsigned int)OS_MAJOR_RELEASE);
	g_out->write((unsigned int)OS_MINOR_RELEASE);
	g_out->write((unsigned int)OS_MAINTENANCE_RELEASE);
	g_out->write(arg);
	g_out->write(g_dt);
	g_out->end();
      }
    }

    osu_sessdata_ptr<osu_monitor_internal> monitor("__osu_monitor__");
    if (monitor != 0) return;

    monitor = new osu_monitor_internal();
  }

}

//* Initializes all sessions...

void osu_monitor::initialize_all()
{
  osu_monitor_internal::initialize_all();
}


//* Initializes for current session only...

void osu_monitor::initialize()
{
#if OS_MAJOR_RELEASE > 5
  os_session* sess = os_session::get_current();
  assert(sess != 0);
#endif
  osu_monitor_internal::initialize();
}

void osu_monitor::log(const char* format, ...)
{
  osu_sessdata_ptr<osu_monitor_internal> monitor("__osu_monitor__");
  if ((monitor != 0) && (g_out != 0)) {
    osu_sync sync(*g_mutex);

    char    buffer[4096];
    va_list args;
    va_start(args,format);
    vsprintf(buffer,format,args);
    osu_monitor_user_event event(buffer);
    event.write(g_out);
  }
}
