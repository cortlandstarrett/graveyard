/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DMP_ARGS_HH
#define DMP_ARGS_HH

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
#include <ostore/coll.hh>

#include <ostore/traverse/argument.hh>


/***********************************************************************
  class os_Dumper_arguments
***********************************************************************/

class os_Dumper_arguments : public os_Arguments {

  public: // Construction
    os_Dumper_arguments (int argc, char* argv[]);
    ~os_Dumper_arguments ();

  public: // Embedded data
    os_String_const_list* database_paths;
    const char* dump_pathname;

  };


extern os_Dumper_arguments* arguments;


#endif /* DMP_ARGS_HH */
