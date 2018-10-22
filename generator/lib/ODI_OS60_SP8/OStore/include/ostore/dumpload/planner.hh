/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef PLANNER_HH
#define PLANNER_HH

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


/***********************************************************************
  os_Planning_action registration types
***********************************************************************/

template <class Key, class Value> class os_Registration_entry;
template <class Key, class Value> class os_Registration_block;
template <class Key, class Value> class os_Registrations;

typedef os_Registration_entry<os_Planning_action*, os_Dumper>
os_Planner_registration_entry;
typedef os_Registration_block<os_Planning_action*, os_Dumper>
os_Planner_registration_block;
typedef os_Registrations<os_Planning_action*, os_Dumper>
os_Planner_registrations;


/***********************************************************************
  class os_Planning_action
***********************************************************************/

class os_Planning_action {

  public: // Construction
    os_Planning_action ();
    virtual ~os_Planning_action ();

  public: // Accessors
    os_Dumper& get_dumper () const;
    virtual os_boolean should_emit_loader
        (const os_class_type& class_type) const;

  public: // Actions
    virtual void operator () (const os_type& actual_type, void* object, 
			      os_int32 count);
    virtual void operator () (const os_type& actual_type, void* object) = 0;

  protected: // Embedded data
    os_Dumper* dumper;

  public: // Modifiers
    void set_dumper (os_Dumper&);

  private: // Friends
  //friend void os_Planner_registration_entry::set_context (os_Dumper& dumper);

  };


#endif /* PLANNER_HH */
