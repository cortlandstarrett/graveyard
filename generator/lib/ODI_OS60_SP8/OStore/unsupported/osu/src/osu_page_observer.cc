#include "osu_page_observer.hh"
#include "osu_sessmgt.hh"
#include "osu_vector.hh"
#include <ostore/ostore.hh>
#include <ostore/osreleas.hh>


#define FOR_EACH(VECTOR,ELEMENT)                                    \
    {  unsigned short n = VECTOR->cardinality();                    \
       for (unsigned short i = 0; i < n; i++) {                     \
           void* aHook = (*VECTOR)[i];                              \
           osu_page_observer* ELEMENT = (osu_page_observer*) aHook; \
           if (ELEMENT) {

#define END_FOR       }}}




#if OS_MAJOR_RELEASE < 6
#define SECTSZ  512
#define PAGESZ  objectstore::get_page_size()
#endif

#if OS_MAJOR_RELEASE > 5
static void page_observer_page_fault(os_char_p         addr,
				     os_database*      db,
				     os_unsigned_int32 segno,
				     os_unsigned_int32 clusno,
				     os_unsigned_int32 pageno,
				     os_boolean        b_for_write)
{
#else 
static void page_observer_page_fault(os_char_p         addr,
				     os_segment_p seg,
				     os_unsigned_int32 segment_no,
				     os_unsigned_int32 page_no)
{
  os_database*         db  = seg->database_of();
  os_unsigned_int32 segno  = seg->get_number();
  os_unsigned_int32 clusno = 0;
  os_unsigned_int32 pageno = page_no;
  os_boolean   b_for_write = 0;
#endif
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->page_fault(addr,db,segno,clusno,pageno,b_for_write);
    } END_FOR;
  }
}



#if OS_MAJOR_RELEASE > 5
static void page_observer_page_fetch(os_database*      db,
				     os_unsigned_int32 segno,
				     os_unsigned_int32 clusno,
				     os_unsigned_int32 pageno,
				     os_unsigned_int32 n_pages,
				     os_boolean        b_for_write)
{
#else 
static void page_observer_page_fetch(os_segment_p      seg,
				     os_unsigned_int32 segno,
				     os_unsigned_int32 pageno,
				     os_boolean        b_for_write)
{
  os_database*         db   = seg->database_of();
  os_unsigned_int32 clusno  = 0;
  os_unsigned_int32 n_pages = 1;
#endif
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->page_fetch(db,segno,clusno,pageno,n_pages,b_for_write);
    } END_FOR;
  }
}



#if OS_MAJOR_RELEASE > 5
static void page_observer_fault_active(os_database*      db,
				       os_unsigned_int32 segno,
				       os_unsigned_int32 clusno,
				       os_unsigned_int32 pageno,
				       os_boolean        b_for_write)
{
#else 
static void page_observer_fault_active(os_segment_p      seg,
				       os_unsigned_int32 segno,
				       os_unsigned_int32 pageno,
				       os_boolean        b_for_write)
{
  os_database*         db  = seg->database_of();
  os_unsigned_int32 clusno = 0;
#endif
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->fault_active(db,segno,clusno,pageno,b_for_write);
    } END_FOR;
  }
}


#if OS_MAJOR_RELEASE > 5
static void page_observer_return_pages(os_database*      db,
				       os_unsigned_int32 segno,
				       os_unsigned_int32 clusno,
				       os_unsigned_int32 pageno,
				       os_unsigned_int32 n_pages,
				       os_boolean        dirty_p)
{
#else 
static void page_observer_return_pages(os_segment_p      seg,
				       os_unsigned_int32 segno,
				       os_unsigned_int32 sector_no,
				       os_unsigned_int32 n_sectors,
				       os_boolean        dirty_p)

{
  os_database*         db  = seg->database_of();
  os_unsigned_int32 clusno = 0;
  os_unsigned_int32 n_pages = SECTSZ*n_sectors/PAGESZ;
  os_unsigned_int32 pageno = SECTSZ*sector_no/PAGESZ;
#endif
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->return_pages(db,segno,clusno,pageno,n_pages,dirty_p);
    } END_FOR;
  }
}


#if OS_MAJOR_RELEASE > 5
static void page_observer_reloc_page_in(os_database*      db,
					os_unsigned_int32 segno,
					os_unsigned_int32 clusno,
					os_unsigned_int32 pageno)
{
#else 
  static void page_observer_reloc_page_in(os_segment_p      seg,
					  os_unsigned_int32 segno,
					  os_unsigned_int32 pageno)
{
  os_database*         db  = seg->database_of();
  os_unsigned_int32 clusno = 0;
#endif
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->reloc_page_in(db,segno,clusno,pageno);
    } END_FOR;
  }
}


#if OS_MAJOR_RELEASE > 5
static void page_observer_reloc_page_out(os_database*      db,
				       os_unsigned_int32 segno,
				       os_unsigned_int32 clusno,
				       os_unsigned_int32 pageno)
{
#else 
  static void page_observer_reloc_page_out(os_segment_p      seg,
					   os_unsigned_int32 segno,
					   os_unsigned_int32 pageno)
{
  os_database*         db  = seg->database_of();
  os_unsigned_int32 clusno = 0;
#endif
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->reloc_page_out(db,segno,clusno,pageno);
    } END_FOR;
  }
}


#if OS_MAJOR_RELEASE > 5
static void page_observer_reloc_page_fwd(os_database*      db,
				       os_unsigned_int32 segno,
				       os_unsigned_int32 clusno,
				       os_unsigned_int32 pageno)
{
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->reloc_page_fwd(db,segno,clusno,pageno);
    } END_FOR;
  }
}
#else
static void page_observer_fetch_segment(os_segment_p      seg,
					os_unsigned_int32 segno,
					os_unsigned_int32 sector_no,
					os_unsigned_int32 n_sectors)
{
  os_database*          db = seg->database_of();
  os_unsigned_int32 clusno = 0;
  os_unsigned_int32 npages = SECTSZ*n_sectors/PAGESZ;
  os_unsigned_int32 pageno = SECTSZ*sector_no/PAGESZ;
  os_boolean   b_for_write = 0;

  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->page_fetch(db,segno,clusno,pageno,npages,b_for_write);
    } END_FOR;
  }
}
#endif


#if OS_MAJOR_RELEASE > 5
static void page_observer_commit_pages(os_database*      db,
				       os_unsigned_int32 segno,
				       os_unsigned_int32 clusno,
				       os_unsigned_int32 pageno,
				       os_unsigned_int32 npages)
{
#else 
static void page_observer_commit_pages(os_segment_p      seg,
				       os_unsigned_int32 segno,
				       os_unsigned_int32 sector_no,
				       os_unsigned_int32 n_sectors,
				       os_boolean)
{
  os_database*         db  = seg->database_of();
  os_unsigned_int32 clusno = 0;
  os_unsigned_int32 npages = SECTSZ*n_sectors/PAGESZ;
  os_unsigned_int32 pageno = SECTSZ*sector_no/PAGESZ;
#endif
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->commit_pages(db,segno,clusno,pageno,npages);
    } END_FOR;
  }
}


#if OS_MAJOR_RELEASE > 5
static void page_observer_upgrade_lock(os_database*      db,
				     os_unsigned_int32 segno,
				     os_unsigned_int32 clusno,
				     os_unsigned_int32 pageno,
				     os_boolean        b_write_lock)
{
#else 
static void page_observer_upgrade_lock(os_segment_p      seg,
				       os_unsigned_int32 segno,
				       os_unsigned_int32 sector_no)
{
  os_database*         db  = seg->database_of();
  os_unsigned_int32 clusno = 0;
  os_unsigned_int32 pageno  = SECTSZ*sector_no/PAGESZ;
  os_boolean  b_write_lock = 1;
#endif
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->upgrade_lock(db,segno,clusno,pageno,b_write_lock);
    } END_FOR;
  }
}


#if OS_MAJOR_RELEASE > 5
static void page_observer_deadlock(os_database*      db,
				   os_unsigned_int32 segno,
				   os_unsigned_int32 clusno,
				   os_unsigned_int32 pageno,
				   os_unsigned_int32 n_pages)
{
#else 
static void page_observer_deadlock(os_segment_p      seg,
				   os_unsigned_int32 segno,
				   os_unsigned_int32 sector_no,
				   os_unsigned_int32 n_sectors)
{
  os_database*         db  = seg->database_of();
  os_unsigned_int32 clusno = 0;
  os_unsigned_int32 n_pages = SECTSZ*n_sectors/PAGESZ;
  os_unsigned_int32 pageno  = SECTSZ*sector_no/PAGESZ;
#endif
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->deadlock(db,segno,clusno,pageno,n_pages);
    } END_FOR;
  }
}


#if OS_MAJOR_RELEASE > 5
static void page_observer_page_create(os_database*      db,
				    os_unsigned_int32 segno,
				    os_unsigned_int32 clusno,
				    os_unsigned_int32 pageno,
				    os_unsigned_int32 n_pages)
{
#else 
static void page_observer_page_create(os_segment_p      seg,
				      os_unsigned_int32 segno,
				      os_unsigned_int32 pageno,
				      os_unsigned_int32 n_pages)
{
  os_database*         db  = seg->database_of();
  os_unsigned_int32 clusno = 0;
#endif
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    FOR_EACH(hookList,anObserver) {
	anObserver->page_create(db,segno,clusno,pageno,n_pages);
    } END_FOR;
  }
}

static osu_vector* page_observer_initialize(void*)
{
  // Need to enable and register event hooks...

  objectstore::enable_event_hooks();
  objectstore::set_page_fault_hook(page_observer_page_fault);
  objectstore::set_page_fetch_hook(page_observer_page_fetch);
  objectstore::set_fault_active_hook(page_observer_fault_active);
  objectstore::set_return_pages_hook(page_observer_return_pages);
  objectstore::set_reloc_page_in_hook(page_observer_reloc_page_in);
  objectstore::set_reloc_page_out_hook(page_observer_reloc_page_out);
#if OS_MAJOR_RELEASE > 5
  objectstore::set_reloc_page_forward_hook(page_observer_reloc_page_fwd);
  objectstore::set_commit_pages_hook(page_observer_commit_pages);
#else
  objectstore::set_fetch_segment_hook(page_observer_fetch_segment);
  objectstore::set_commit_page_hook(page_observer_commit_pages);
#endif
  objectstore::set_upgrade_lock_hook(page_observer_upgrade_lock);  
  objectstore::set_deadlock_hook(page_observer_deadlock);  
  objectstore::set_page_creation_hook(page_observer_page_create);  

  return new osu_vector(10);
}




void osu_page_observer::subscribe(osu_page_observer* observer)
{
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__",
					&page_observer_initialize);
  hooks->insert(observer);
}



void osu_page_observer::unsubscribe(osu_page_observer* observer)
{
  osu_sessdata_ptr<osu_vector> hooks("__osu_page_observer__");
  osu_vector* hookList = hooks;
  if (hookList) {
    hookList->remove(observer);
  }
}


osu_page_observer::~osu_page_observer()
{
  osu_page_observer::unsubscribe(this);
}


/* Default do nothing implementations */


void osu_page_observer::page_fault(os_char_p,
				   os_database*      db,
				   os_unsigned_int32 segno,
				   os_unsigned_int32 clusno,
				   os_unsigned_int32 pageno,
				   os_boolean        b_for_write)
{
  ;
}



void osu_page_observer::page_fetch(os_database*      db,
				   os_unsigned_int32 segno,
				   os_unsigned_int32 clusno,
				   os_unsigned_int32 pageno,
				   os_unsigned_int32 npages,
				   os_boolean        b_for_write)
{
  ;
}



void osu_page_observer::fault_active(os_database*      db,
				     os_unsigned_int32 segno,
				     os_unsigned_int32 clusno,
				     os_unsigned_int32 pageno,
				     os_boolean        b_for_write)
{
  ;
}



void osu_page_observer::return_pages(os_database*      db,
				     os_unsigned_int32 segno,
				     os_unsigned_int32 clusno,
				     os_unsigned_int32 pageno,
				     os_unsigned_int32 n_pages,
				     os_boolean        dirty_p)
{
  ;
}



void osu_page_observer::reloc_page_in(os_database*      db,
				      os_unsigned_int32 segno,
				      os_unsigned_int32 clusno,
				      os_unsigned_int32 pageno)
{
  ;
}



void osu_page_observer::reloc_page_out(os_database*      db,
				       os_unsigned_int32 segno,
				       os_unsigned_int32 clusno,
				       os_unsigned_int32 pageno)
{
  ;
}



void osu_page_observer::reloc_page_fwd(os_database*      db,
				       os_unsigned_int32 segno,
				       os_unsigned_int32 clusno,
				       os_unsigned_int32 pageno)
{
  ;
}



void osu_page_observer::commit_pages(os_database*      db,
				     os_unsigned_int32 segno,
				     os_unsigned_int32 clusno,
				     os_unsigned_int32 pageno,
				     os_unsigned_int32 npages)
{
  ;
}



void osu_page_observer::upgrade_lock(os_database*      db,
				     os_unsigned_int32 segno,
				     os_unsigned_int32 clusno,
				     os_unsigned_int32 pageno,
				     os_boolean        b_write_lock)
{
  ;
}



void osu_page_observer::deadlock(os_database*      db,
				 os_unsigned_int32 segno,
				 os_unsigned_int32 clusno,
				 os_unsigned_int32 pageno,
				 os_unsigned_int32 n_pages)
{
  ;
}



void osu_page_observer::page_create(os_database*      db,
				    os_unsigned_int32 segno,
				    os_unsigned_int32 clusno,
				    os_unsigned_int32 pageno,
				    os_unsigned_int32 n_pages)
{
  ;
}



