/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_EXPORT_ID
#define CLIENT_INTERFACE_EXPORT_ID 1

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/tix.hh>

class os_segment;

class _OS_DLLIMPORT(_OS_CLIENT) os_export_id {
public:
  // Construct a null export id, which is guaranteed to not identify
  // any object
  os_export_id();

  os_export_id(os_export_id const&);

  os_export_id& operator=(os_export_id const&);
  os_boolean operator==(os_export_id const&) const;

  // returns true if the export id has a default assignment
  os_boolean is_null() const;

  // return the internal export ID value
  os_unsigned_int32 get_value() const;

  // create an export id with a particular export id value
  static os_export_id create(os_unsigned_int32 export_id_value);

private:
  os_unsigned_int32 opaque;
};


class _OS_DLLIMPORT(_OS_CLIENT) os_export_id_cursor : public basic_undo
{
public:
  os_export_id_cursor(os_segment *seg, 
		      os_unsigned_int32 max_n_ids_at_a_time = 100);
  ~os_export_id_cursor();

  void	 reset();
  void	 reset(os_export_id const& export_id);
  void	 reset(os_segment *seg);

  os_export_id next();
  
  os_export_id get_current() const;

private:
  void finished();

private:
  os_segment	  	  *seg;
  const os_unsigned_int32 max_eids;
  os_boolean		  b_more;
  os_export_id		  *p_eids;
  os_unsigned_int32	  n_eids;
  os_int32		  i_eids;

};

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_EXPORT_ID */
