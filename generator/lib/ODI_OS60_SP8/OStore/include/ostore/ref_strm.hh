/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/* ref_strm.hh:	Definitions of insertors & extractors for os_reference
   classes.
   
   */
#ifndef _REF_STRM_H_
#define _REF_STRM_H_
#include <ostore/hdrstart.hh>

/* The insertors & extractors defined here operate upon the types declared
   in ref.hh.  The definitions are in a separate header so that only users
   who need stream operations will have to link against the stream library. */

#include <ostore/hdrsys.hh>
#include <iostream.h>
#include <stdlib.h>
#include <ostore/hdrend.hh>

#include <ostore/client/ref.hh>

/* Ideally, these would be templates, but until templates are universal, it
   is cleaner to use macros than to mess w/ the deparameterization stuff. */
#define _os_insertor(type) \
inline ostream& operator<< (ostream& s, type r) { \
  return s << r.dump(); \
}
#define _os_extractor(type) \
inline istream& operator>> (istream& s, type& r) { \
  char* handle = (char*)malloc(_ODI_REF_MAX_DUMP); \
  s.get(handle, _ODI_REF_MAX_DUMP); \
  r.load(handle); \
  free(handle); \
  return s; \
}


/* Only references which are fully specified can be dumped to an ostream: */
_os_insertor(_Reference_safe_global)
_os_insertor(_Reference_transient)
_os_insertor(_Reference_unsafe_global)
_os_insertor(_Reference_unsafe_this_DB)

/* The extractors for non-fully specified references simply ignore any
   information which is not part of their definition: */
_os_extractor(_Reference_safe)
_os_extractor(_Reference_safe_global)
_os_extractor(_Reference_transient)
_os_extractor(_Reference_unsafe)
_os_extractor(_Reference_unsafe_global)
_os_extractor(_Reference_unsafe_this_DB)

#include <ostore/hdrend.hh>
#endif /* _REF_STRM_H_ */
