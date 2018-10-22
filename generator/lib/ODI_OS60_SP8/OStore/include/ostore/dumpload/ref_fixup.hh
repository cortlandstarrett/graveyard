/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DUMPER_REFERENCE_FIXUP_HH
#define DUMPER_REFERENCE_FIXUP_HH
#include <ostore/dumpload/dmp_ref.hh>

class os_Dumper_reference_fixup {
public:
   unsigned long object_offset; /* offset to be added to persistent object */
   /* following were obtained by reading dumped object as <%lu,%lu,%lu> */
   unsigned long database_number;
   unsigned long segment_number;
   unsigned long offset;
	
};

#endif
