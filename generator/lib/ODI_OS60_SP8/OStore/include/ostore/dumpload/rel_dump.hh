/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef REL_DUMP_HH
#define REL_DUMP_HH

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

/* -- include files ---------------------------------------------*/
#include <ostore/dumpload/rel_spc.hh>

class os_rel_dumper : public os_rel_specialization
   {
public: // Actions
   virtual void operator () (const os_class_type& actual_type, void* object);
   };

#endif /* REL_DUMP_HH */
