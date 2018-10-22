/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _DUMPLOAD_DL_OPNEW_HH_
#define _DUMPLOAD_DL_OPNEW_HH_
/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Function:    operator new
  Description: 
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

#if !defined(__os_sol2c5)
inline void* operator new (size_t, void* object)
{
  return object;
}
#endif

/* create "default" operator delete for VC++ 6.0 */
#if (_OS_MicrosoftCC >= 1200)
static inline void operator delete(void *addr, void*)
{
  ::delete addr;
}
#endif


#endif /* _DUMPLOAD_DL_OPNEW_HH_ */
