/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_SEGMENT
#define CLIENT_INTERFACE_SEGMENT 1

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/os_int64.hh>
#include <ostore/facade.hh>
#include <ostore/nclient/objstore.hh>
#include <ostore/nclient/typedefs.hh>

class os_export_id;

class _OS_DLLIMPORT(_OS_CLIENT) os_segment : public os_facade
{
public:						/* PUBLIC FUNCTION MEMBERS */
  void operator delete(void*); 

  void count_objects(os_int32 &length,
		     objectstore_object_count_p &oocs) const;
  
  os_cluster* create_cluster();

  os_database *database_of() const;

  void destroy();

  /* Get methods */
  os_segment_access* get_access_control() const;
  void get_all_clusters(os_int32 max_clusters,
			os_cluster_p* cluster_array,
			os_int32& n_clusters) const;
  os_allocation_strategy get_allocation_strategy(void) const;
  void *get_application_info() const;
  os_boolean get_check_illegal_pointers() const;
  os_cluster *get_cluster(os_unsigned_int32 cluster_num) const;
  void get_clusters(os_unsigned_int32 first_cluster_num,
		    os_unsigned_int32 max_clusters,
		    os_cluster_p *clusters,
		    os_unsigned_int32& n_clusters,
		    os_boolean &b_more) const;
  void get_export_ids(const os_export_id& last_export_id,
		      os_unsigned_int32 max_export_ids,
		      os_export_id *p_export_ids,
		      os_unsigned_int32& n_export_ids,
		      os_boolean &b_more) const;
  char *get_comment() const;
  os_cluster* get_default_cluster() const; 
  void get_fetch_policy(os_fetch_policy &, os_int32 &) const;
  objectstore_lock_option get_lock_option() const;
  os_int32 get_n_clusters() const;
  os_boolean get_null_illegal_pointers() const;
  os_unsigned_int32 get_number() const;
  os_int32 get_readlock_timeout() const;
  os_int32 get_writelock_timeout() const;
  objectstore::segment_reference_policy
    get_segment_reference_policy() const;

  static os_segment *const get_transient_segment();

  os_boolean is_deleted();
  os_boolean is_empty();  
  os_boolean is_transient_segment() const;

  static os_segment* of(void const *);

  void release_pointer();
  void retain_pointer();

  void return_memory(os_boolean evict_now);

  os_session *session_of() const;

  void* resolve_export_id(const os_export_id& export_id) const;

  /* Set methods */
  void set_access_control(const os_segment_access* seg_access);
  void set_allocation_strategy(os_allocation_strategy);
  void set_application_info(void *info);
  void set_check_illegal_pointers(os_boolean);
  void set_comment(const char *new_comment);
  void set_default_cluster(os_cluster *cluster);
  void set_fetch_policy(os_fetch_policy, os_int32);
  void set_lock_option(objectstore_lock_option);
  void set_null_illegal_pointers(os_boolean);
  void set_readlock_timeout(os_int32 milliseconds);
  void set_writelock_timeout(os_int32 milliseconds);

  os_unsigned_int64 size(os_boolean b_lock_segment = 1);

#if 0
  /* This API is added for internal test */

  os_unsigned_int32 _pointer_to_offset(void *addr);
#endif
};

/* User class to iterate through os_segment objects */
class _OS_DLLIMPORT(_OS_CLIENT) os_segment_cursor : public basic_undo
{
private:
  os_database		  *db;
  const os_unsigned_int32 max_segs;
  os_boolean		  b_more;
  os_boolean		  b_seen;
  os_segment_p		  *p_segs;
  os_unsigned_int32	  n_segs;
  os_unsigned_int32	  i_segs;
  os_unsigned_int32	  next_seg_num;

public:

  os_segment_cursor(os_database *db, os_unsigned_int32 max_n_segs_at_a_time = 100);
  ~os_segment_cursor();

  void	 reset();
  void	 reset(os_unsigned_int32 seg_num);
  void	 reset(os_database *db_);

  os_segment * next();
  
  os_segment * get_current();

private:
  void    _get_segments(os_unsigned_int32 starting_num);
};


/* This class provides a mechanism to call the release_pointer() method
  on a specified os_segment pointer when that pointer goes out of scope. 
*/
class _OS_DLLIMPORT(_OS_CLIENT) os_release_segment_pointer : public basic_undo
{
private:
  os_segment *ptr;

public:
  os_release_segment_pointer(os_segment *_ptr) : ptr(_ptr) {}
  ~os_release_segment_pointer() { if (ptr) ptr->release_pointer(); }
};

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_DATABASE */

