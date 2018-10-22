/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef IN_PLACE_HH
#define IN_PLACE_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1997-2000 by eXcelon Corporation. All Rights Reserved.                          *
*                                                                      *
* eXcelon Corporation Confidential Restricted material.  This work     *
* contains confidential trade secrets of eXcelon Corp..  Use,          *
* examination, copying, transfer and/or disclosure to others are       *
* prohibited, except with the express written agreement of eXcelon     *
* Corp.                                                                *
*                                                                      *
* THIS WORK IS PROVIDED AS IS, WHERE IS, WITH ABSOLUTELY NO WARRANTIES *
* WHATSOEVER, WHETHER EXPRESS OR IMPLIED.                              *
*                                                                      *
***********************************************************************/

//-- Include files -----------------------------------------------------

#include <stdlib.h>

/***********************************************************************
  Function:     operator new
  Description:  The in-place operator new. Used to reconstruct the
                given object. This function must be inline to prevent
                any linkage clash with any other instance of this
		overloading from any other possible party.
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

#if !defined (__os_sol2c5)
inline static void* operator new (size_t, void* object)
{
 return object;
}
#endif 


#endif /* IN_PLACE_HH */

