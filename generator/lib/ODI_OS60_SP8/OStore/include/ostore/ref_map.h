/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/* ref_map.h:	Mappings from R1.x => R2 C bindings for reference functions.

*/
#ifndef _REF_MAP_H_
#define _REF_MAP_H_

#define _REF_OLD_H_
#include <ostore/ref_map.hh>	/* for new type names */

/* Mappings for all C functions on references which were available prior
   to R2 (note that this is a subset of what's available now): */
#define new_reference 	       	     os_old_reference_new
#define resolve_reference      	     os_old_reference_resolve

#define new_reference_local    	     os_reference_local_new
#define resolve_reference_local	     os_reference_local_resolve

#define forget_local_safe_reference  os_reference_protected_local_forget
#define local_safe_reference_deleted os_reference_protected_local_deleted
#define new_reference_local_safe     os_reference_protected_local_new
#define resolve_local_safe_reference os_reference_protected_local_resolve

#define forget_safe_reference  	     os_old_reference_protected_forget
#define new_reference_safe     	     os_old_reference_protected_new
#define resolve_safe_reference 	     os_old_reference_protected_resolve
#define safe_reference_deleted 	     os_old_reference_protected_deleted

#endif /* _REF_MAP_H_ */
