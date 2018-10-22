/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_CLUSTER
#define CLIENT_INTERFACE_CLUSTER 1

#include <ostore/hdrstart.hh>

#include <ostore/portypes.hh>
#include <ostore/facade.hh>
#include <ostore/tix.hh>
#include <ostore/nclient/objstore.hh>
#include <ostore/nclient/persnew.hh>

class os_segment;
class os_session;

class _OS_DLLIMPORT(_OS_CLIENT) os_cluster : public os_facade {

public:
  void operator delete(void*); 

  void count_objects(os_int32 &length,
		     objectstore_object_count_p &oocs) const;

  os_database *database_of() const;

  void destroy();

  /* Get methods */
  os_allocation_strategy get_allocation_strategy(void) const;
  void get_fetch_policy(os_fetch_policy &, os_int32 &) const;
  objectstore_lock_option get_lock_option() const;
  os_boolean get_null_illegal_pointers() const;
  os_unsigned_int32 get_number() const;
  static os_cluster *const get_transient_cluster();

  os_boolean is_deleted();
  os_boolean is_empty();  
  os_boolean is_transient_cluster() const;

  static os_cluster* of(void const* obj);

  void release_pointer();
  void retain_pointer();

  void return_memory(os_boolean evict_now);

  os_segment* segment_of() const;

  /* Set methods */
  void set_allocation_strategy(os_allocation_strategy);
  void set_fetch_policy(os_fetch_policy, os_int32);
  void set_lock_option(objectstore_lock_option);
  void set_null_illegal_pointers(os_boolean b_null);

  os_session *session_of() const;

  os_unsigned_int32 size(os_boolean b_lock_cluster = 1);

  /* Support for os_cluster_with
   * This indirect way of calling the os_cluster_with constructor
   * prevents the C++ compiler from quietly inserting a call to it
   * as a standard pointer conversion where it is not wanted */
  static os_cluster_with with(const void* object) {
    os_cluster_with cluster_with;
    cluster_with.cluster_with = object;
    return cluster_with; }
};

/* User class to iterate through os_cluster objects */
class _OS_DLLIMPORT(_OS_CLIENT) os_cluster_cursor : public basic_undo
{
private:
  os_segment		  *seg;
  const os_unsigned_int32 max_clusters;
  os_boolean		  b_more;
  os_boolean		  b_seen;
  os_cluster_p		  *p_clusters;
  os_unsigned_int32	  n_clusters;
  os_unsigned_int32	  i_clusters;
  os_unsigned_int32	  next_cluster_num;

public:

  os_cluster_cursor(os_segment *seg, os_unsigned_int32 max_n_clusters_at_a_time = 100);
  ~os_cluster_cursor();

  void	 reset();
  void	 reset(os_unsigned_int32 cluster_num);
  void	 reset(os_segment *seg);

  os_cluster * next();
  
  os_cluster * get_current();

private:
  void   _get_clusters(os_unsigned_int32 starting_num);
};


/* This class provides a mechanism to call the release_pointer() method
  on a specified os_cluster pointer when that pointer goes out of scope. 
*/
class _OS_DLLIMPORT(_OS_CLIENT) os_release_cluster_pointer : public basic_undo
{
private:
  os_cluster *ptr;

public:
  os_release_cluster_pointer(os_cluster *_ptr) : ptr(_ptr) {}
  ~os_release_cluster_pointer() { if (ptr) ptr->release_pointer(); }
};

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_CLUSTER */
