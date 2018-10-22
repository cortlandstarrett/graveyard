/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_NOTIFY
#define CLIENT_INTERFACE_NOTIFY 1

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/nclient/typedefs.hh>
#include <ostore/nclient/ref.hh>

class os_subscription;

class _OS_DLLIMPORT(_OS_CLIENT) os_notification {
protected:
  os_soft_pointer<void>  notify_location;
  os_int32	notify_kind;
  char		*p_notify_string;

public:
  os_notification();
  os_notification(const os_soft_pointer<void>  &loc, os_int32 kind=0,
		  const char *notification_string=0);
  os_notification(const os_notification &notification);
  ~os_notification();

  void assign(const os_soft_pointer<void>  &loc, os_int32 kind=0,
	      const char *notification_string=0);
  void assign(const os_notification &notification);

  os_notification& operator=(const os_soft_pointer<void> &loc);
  os_notification& operator=(const os_notification &notification);

  os_database *get_database() const;
  // This method is deprecated and will be removed in a subsequent
  // release.
  os_reference get_reference() const;
  os_soft_pointer<void>  get_location() const;
  os_int32 get_kind() const;
  const char *get_string() const;

  void notify_immediate();
  void notify_on_commit();

  enum {maximum_string_length = 16383};
  enum {default_notification_queue_length = 50,
	maximum_notification_queue_length = 16384};

public:
  /* Top-level Notification API */
  static void subscribe(const os_subscription *sub, os_int32 count = 1);
  static void subscribe(const os_database *db);
  static void subscribe(const os_segment *seg);
  static void subscribe(const os_cluster *clus);
  static void subscribe(const os_soft_pointer<void> &loc, os_int32 n_bytes = 1);

  static void unsubscribe(const os_subscription *sub, os_int32 count = 1);
  static void unsubscribe(const os_database *db);
  static void unsubscribe(const os_segment *seg);
  static void unsubscribe(const os_cluster *clus);
  static void unsubscribe(const os_soft_pointer<void> &loc, os_int32 n_bytes = 1);

  static void notify_immediate(const os_notification *notifications, 
			       os_int32 n_notifications = 1,
			       os_int32 *n_queued = 0);
  static void notify_immediate(const os_soft_pointer<void>  &loc,
			       os_int32 kind = 0,
			       const char *notification_string = 0,
			       os_int32 *n_queued = 0);
  static void notify_on_commit(const os_notification *notifications, 
			       os_int32 n_notifications = 1);
  static void notify_on_commit(const os_soft_pointer<void> &loc, 
			       os_int32 kind = 0,
			       const char *notification_string = 0);
  static void set_queue_size(os_unsigned_int32 queue_size);
  static void queue_status(os_unsigned_int32 &queue_size,
			   os_unsigned_int32 &count_pending_notifications,
			   os_unsigned_int32 &count_queue_overflows);
  static os_boolean receive(os_notification_p &notification,
			    os_int32 timeout = -1);
  static os_int32 _get_fd();

  static void _debug_close_cmgr_connection();
  static void _debug_close_notification_connection();

private:
  friend class os_subscription;

  static void _get_dsco_address(const os_soft_pointer<void>& softptr,
			        os_unsigned_int32& seg_id,
			        os_unsigned_int32& clus_id,
			        os_unsigned_int32& offset);

};

class _OS_DLLIMPORT(_OS_CLIENT) os_subscription {
protected:
  const os_database *p_db;
  os_unsigned_int32 segment_id;
  os_unsigned_int32 cluster_id;
  os_unsigned_int32 offset;
  os_unsigned_int32 offset_len;
public:
  os_subscription();
  os_subscription(const os_database *);
  os_subscription(const os_segment *);
  os_subscription(const os_cluster *);
  os_subscription(const os_soft_pointer<void> &, os_int32 n_bytes = 1);

  void assign(const os_database *new_p_db);
  void assign(const os_segment *new_p_seg);
  void assign(const os_cluster *new_p_cluster);
  void assign(const os_soft_pointer<void>  &loc, os_int32 n_bytes = 1);

  os_subscription &operator=(const os_database *new_p_db)
    { assign(new_p_db); return *this; }
  os_subscription &operator=(const os_segment *new_p_seg)
    { assign(new_p_seg); return *this; }
  os_subscription &operator=(const os_cluster *new_p_cluster)
    { assign(new_p_cluster); return *this; }
  os_subscription &operator=(const os_soft_pointer<void>  &loc)
    { assign(loc); return *this;}

  const os_database* get_database() const	{ return(p_db); }

  void subscribe() const;
  void unsubscribe() const;

};

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_NOTIFY */
