/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/* ref_map.hh:	Mappings from R1.x => R2 reference class names.

*/
#ifndef _REF_MAP_HH_
#define _REF_MAP_HH_

#include <ostore/client/ref_old.hh>

/* References which include a DBID:
   (These are NOT mapped to the new R2 names, since the R2 versions of these
   are a different size, and doing so would trigger schema evolution.
   To use the R2 versions, you must specify them explicitly (ie, use
   "os_reference", rather than "reference" or "os_reference_old"). */
#define reference     	       	  os_old_Reference
#define reference_safe         	  os_old_Reference_protected
#define reference_base     	  os_old_reference
#define reference_safe_base       os_old_reference_protected

/* References which don't include a DBID: */
#define reference_local     	  os_Reference_local
#define reference_local_safe      os_Reference_protected_local
#define reference_local_base      os_reference_local
#define reference_local_safe_base os_reference_protected_local

#endif /* _REF_MAP_HH_ */
