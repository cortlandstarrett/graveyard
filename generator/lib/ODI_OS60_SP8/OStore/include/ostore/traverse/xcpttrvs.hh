/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef TRAVERSER_EXCEPTIONS_HH
#define TRAVERSER_EXCEPTIONS_HH

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

#include <ostore/except.hh>

//---- exceptions ------------------------------------------------------------

//---- os_Traverser exceptions -----------------------------------------------

DECLARE_EXCEPTION(err_os_Traverser);
DECLARE_EXCEPTION(err_os_Traverser_bad_initialization);
DECLARE_EXCEPTION(err_os_Traverser_bad_action_stack);
DECLARE_EXCEPTION(err_os_Traverser_bad_cast);
DECLARE_EXCEPTION(err_os_Traverser_unexpected_traverser);


#endif /* TRAVERSER_EXCEPTIONS_HH */
