/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_SERVER
#define CLIENT_INTERFACE_SERVER 1

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/nclient/typedefs.hh>

/* TBD: move os_netaddr and os_hostid out of this file.  Users don't need
   access to them */

class os_netaddr {
  os_unsigned_int32 addr;
};

class os_hostid {
  os_unsigned_int32 id;
};

class _OS_DLLIMPORT(_OS_CLIENT) os_server {
protected:
  os_server();
  virtual ~os_server();
public:
  virtual os_boolean is_failover() const = 0;
  virtual char *get_host_name() const = 0;
  virtual void get_databases(os_int32 max_to_return, os_database_p* dblist, 
			     os_int32 &count) const = 0;
  virtual os_int32 get_n_databases() const = 0;
  virtual os_boolean connection_is_broken() const = 0;
  virtual void reconnect() = 0;
  virtual void disconnect() = 0;
  virtual void set_rpc_timeout(os_int32 seconds) = 0;
};

class _OS_DLLIMPORT(_OS_CLIENT) os_failover_server : public os_server {
protected:
  os_failover_server();
  ~os_failover_server();
public:

  char* get_logical_server_hostname() const { return(get_host_name()); }

  virtual char* get_alternative_server_hostname() const = 0;
  virtual char* get_online_server_hostname() const = 0;

  virtual os_boolean set_reconnect_timeout_and_interval(
					os_unsigned_int32 timeout_secs, 
					os_unsigned_int32 interval_secs) = 0;
  virtual os_unsigned_int32 get_reconnect_timeout() const = 0;
  virtual os_unsigned_int32 get_reconnect_retry_interval() const = 0;
};

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_SERVER */
