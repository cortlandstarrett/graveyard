#ifndef OSU_MONITOR_INTERNAL_HH
#define OSU_MONITOR_INTERNAL_HH

#include <ostore/ostore.hh>
#include "osu_page_observer.hh"
#include "osu_txn_observer.hh"
#include "osu_vector.hh"

class  osu_monitor_internal
  :public osu_page_observer, osu_txn_observer { 

public:
  static void initialize();
  static void initialize_all();

  osu_monitor_internal();
  ~osu_monitor_internal();

protected:

  os_boolean check(os_unsigned_int32 opcode);
  void       check_db(os_database* db);

  /* osu_txn_observer methods */
  virtual void handle(const os_transaction_hook::event_type,
		      const os_transaction* txn);

  /* osu_page_observer methods */

  virtual void page_fault(os_char_p,
			  os_database*      db,
			  os_unsigned_int32 segno,
			  os_unsigned_int32 clusno,
			  os_unsigned_int32 pageno,
			  os_boolean        b_for_write);
  virtual void page_fetch(os_database*      db,
			  os_unsigned_int32 segno,
			  os_unsigned_int32 clusno,
			  os_unsigned_int32 pageno,
			  os_unsigned_int32 npages,
			  os_boolean        b_for_write);
  virtual void fault_active(os_database*      db,
			    os_unsigned_int32 segno,
			    os_unsigned_int32 clusno,
			    os_unsigned_int32 pageno,
			    os_boolean        b_for_write);
  virtual void return_pages(os_database*      db,
			    os_unsigned_int32 segno,
			    os_unsigned_int32 clusno,
			    os_unsigned_int32 pageno,
			    os_unsigned_int32 n_pages,
			    os_boolean        dirty_p);
  virtual void reloc_page_in(os_database*      db,
			     os_unsigned_int32 segno,
			     os_unsigned_int32 clusno,
			     os_unsigned_int32 pageno);
  virtual void reloc_page_out(os_database*      db,
			      os_unsigned_int32 segno,
			      os_unsigned_int32 clusno,
			      os_unsigned_int32 pageno);
  virtual void reloc_page_fwd(os_database*      db,
			      os_unsigned_int32 segno,
			      os_unsigned_int32 clusno,
			      os_unsigned_int32 pageno);
  virtual void commit_pages(os_database*      db,
			    os_unsigned_int32 segno,
			    os_unsigned_int32 clusno,
			    os_unsigned_int32 pageno,
			    os_unsigned_int32 npages);
  virtual void upgrade_lock(os_database*      db,
			    os_unsigned_int32 segno,
			    os_unsigned_int32 clusno,
			    os_unsigned_int32 pageno,
			    os_boolean        b_write_lock);

  virtual void deadlock(os_database*      db,
			os_unsigned_int32 segno,
			os_unsigned_int32 clusno,
			os_unsigned_int32 pageno,
			os_unsigned_int32 n_pages);
  virtual void page_create(os_database*      db,
			   os_unsigned_int32 segno,
			   os_unsigned_int32 clusno,
			   os_unsigned_int32 pageno,
			   os_unsigned_int32 n_pages);

protected:
  osu_vector        _databases;
  osu_vector        _hosts;
  os_unsigned_int32 _active;
};

#endif
