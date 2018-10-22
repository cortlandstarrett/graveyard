/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef __RAWENTRY_HH__
#define __RAWENTRY_HH__
#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>

/*
 * Class os_rawfs_entry supplies basic info about a raw filesystem
 * database, directory or link.
 */

class _Rawhfs_entry;

class os_rawfs_entry {
  friend class _Rawhfs_entry;
public:
  enum os_rawfs_entry_type {OSU_DATABASE, OSU_DIRECTORY, OSU_LINK, rawfs_entry_type_enum_pad = 1<<30};

public:
  const char* get_name() const;
  const char* get_server_host() const;
  os_boolean is_dir() const;
  os_boolean is_db() const;
  os_boolean is_link() const;
  os_int32 get_type() const;
  os_unsigned_int32 get_n_sectors() const;
  os_unsigned_int32 get_permission() const;
  os_boolean does_dir_have_subdirs() const;
  os_unixtime_t get_creation_time() const;
  const char* get_group_name() const;
  const char* get_user_name() const;
  const char* get_link_host() const;
  const char* get_link_path() const;
  const char* get_abs_path() const;

  os_rawfs_entry(_Rawhfs_entry* e);
  os_rawfs_entry(const os_rawfs_entry& e);
  ~os_rawfs_entry();
  os_rawfs_entry& operator= (const os_rawfs_entry&);

private:
  _Rawhfs_entry* entry;
};

/* Definitions for DEC C++. */
typedef os_rawfs_entry* os_rawfs_entry_p;

#include <ostore/hdrend.hh>
#endif /* __RAWENTRY_HH__ */
