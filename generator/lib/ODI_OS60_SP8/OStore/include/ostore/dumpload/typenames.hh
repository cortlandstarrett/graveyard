/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef TYPENAMES_HH
#define TYPENAMES_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1999-2000 by eXcelon Corporation. All Rights Reserved.                          *
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

char* nested_class_name(const char* class_name);
char* copy_class_name(const char* class_name);
char* dataname_for_os_type(const os_type& class_type,os_Traverser& traverser,
                           class os_Dumper_specialization*(fn)(const char*));

// TBD -- move more naming stuff out of emit load?

#endif /* TYPENAMES_HH */
