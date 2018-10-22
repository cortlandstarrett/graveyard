/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#endif

/* Template implementation for IBM C++, CAFE, SGI C++ */

/* Just get this out of line to get the vtbl out of line where
   the schema can get to it */
#ifndef __os_set_pt_c
#define __os_set_pt_c
template <class E>
os_Set <E> :: ~os_Set () { }

#if defined(__EDG) || defined(__xlC__)
template <class E>
os_Ixonly <E> :: ~os_Ixonly () { }
#endif

#endif

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
#include <os_pse/psecoll/hdrend.hh>
#endif
