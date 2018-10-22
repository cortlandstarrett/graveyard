/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef FIX_DUMP_HH
#define FIX_DUMP_HH

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

#include <ostore/dumpload/dumper.hh>
#include <ostore/dumpload/fixup.hh>


/***********************************************************************
  class os_Fixup_dumper
***********************************************************************/

class os_Fixup_dumper : public os_Fixup {

  public: // Construction
    os_Fixup_dumper (os_Dumper_stream&, const os_class_type&, 
		     const os_Dumper_reference& object_to_fix,
		     unsigned number_elements = 0);
    os_Fixup_dumper (const os_Fixup_dumper&);
    virtual ~os_Fixup_dumper ();
    virtual os_Fixup& duplicate (os_segment&) const = 0;

  public: // Actions
    virtual void dump () const;
    virtual void dump_info () const = 0;

  public: // Accessors
    virtual const char* get_name () const;
    os_Dumper_stream& get_stream () const;
    os_Dumper& get_dumper () const;

  private: // Actions
    virtual void fix ();

  };


#endif /* FIX_DUMP_HH */
