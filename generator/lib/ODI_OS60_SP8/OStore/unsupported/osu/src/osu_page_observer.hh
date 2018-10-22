#ifndef OSU_PAGE_OBSERVER_HH
#define OSU_PAGE_OBSERVER_HH

#include "base.hh"
#include <ostore/ostore.hh>

class OSUEXPORT osu_page_observer {
public:
  osu_page_observer() { ; }

  static void subscribe(osu_page_observer* observer);
  static void unsubscribe(osu_page_observer* observer);

private:  // not allowed...
  osu_page_observer(const osu_page_observer&);
  osu_page_observer& operator=(const osu_page_observer&);

public:
  virtual ~osu_page_observer();
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
};

#endif
