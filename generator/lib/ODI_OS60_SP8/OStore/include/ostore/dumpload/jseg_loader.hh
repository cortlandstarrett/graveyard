/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef JSEGMENT_LOADER_HH
#define JSEGMENT_LOADER_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1997-2001 by eXcelon Corporation. All Rights Reserved. *
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

#include <ostore/dumpload/seg_loader.hh>

/***********************************************************************
  class osji_Segment_loader
***********************************************************************/

class osji_Segment_loader : public os_Segment_loader
{
public: // Construction
  osji_Segment_loader ();
  ~osji_Segment_loader ();

public: // Accessors

public: // Modifiers

public: // Actions

protected: // Embedded data

protected: // Actions

  //  virtual os_boolean export_id_access_required(unsigned long segment_flags);

  virtual void create (os_Loader_info& info);

};


#endif /* JSEGMENT_LOADER_HH */
