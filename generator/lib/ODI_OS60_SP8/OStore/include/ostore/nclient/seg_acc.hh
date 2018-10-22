/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_SEG_ACCESS
#define CLIENT_INTERFACE_SEG_ACCESS 1

/* Access control for segments. */
class _OS_DLLIMPORT(_OS_CLIENT) os_segment_access
{
public:

  enum os_segment_access_type { no_access, read_access, read_write_access,
				os_segment_access_type_pad = 1<<30 };

private:

  char			*p_group_name;
  os_segment_access_type group_access;
  os_segment_access_type other_access;

public:

  os_segment_access();
  os_segment_access(const char		  *p_primary_group,
		    os_segment_access_type primary_group_access_type,
		    os_segment_access_type default_access_type);
  os_segment_access(const os_segment_access& source);
  ~os_segment_access();

  os_segment_access& operator=(const os_segment_access &source);

  os_boolean operator==(const os_segment_access &other);

  os_boolean operator!=(const os_segment_access &other)
  { return(!(*this == other)); }

  os_segment_access_type get_primary_group(os_char_const_p* pp_primary_group = 0) const;

  os_segment_access_type get_default() const
  { return(other_access); }

  void set_primary_group(const char	       *p_primary_group,
			 os_segment_access_type access_type);

  void set_primary_group(os_segment_access_type access_type)
  { group_access = access_type; }

  void set_default(os_segment_access_type access_type)
  { other_access = access_type; }

};

#endif
