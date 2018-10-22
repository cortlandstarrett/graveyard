/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef BOOLEAN_HH
#define BOOLEAN_HH

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

#include <ostore/ostore.hh>

/***********************************************************************
  class os_Bool
***********************************************************************/


#if !defined(_OS_Win32) && !defined(__os_cafe)
#ifdef TRUE
#undef TRUE
#endif
 
#ifdef FALSE
#undef FALSE
#endif
#endif

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Bool {

  public: // Subtypes

    enum Value { _FALSE = 0, _TRUE = 1 };

  };


#endif /* BOOLEAN_HH */
