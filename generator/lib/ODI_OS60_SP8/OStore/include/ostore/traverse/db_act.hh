/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DB_ACTION_HH
#define DB_ACTION_HH

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

#include <ostore/ostore.hh>
#include <ostore/traverse/action.hh>
#include <ostore/traverse/seg_act.hh>
#include <ostore/traverse/root_act.hh>
#include <ostore/traverse/schm_act.hh>

/***********************************************************************
  class os_Database_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Database_node : public os_Action_node {

  public: // Construction
    os_Database_node (os_Database_action&, os_database&);
    virtual ~os_Database_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Database_action& get_database_action () const;
    os_database& get_database () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  public: // Embedded data
    os_database* database;

  };


/***********************************************************************
  class os_Database_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Database_action : public os_Action {

  public: // Construction
    os_Database_action (os_Segment_action* action = 0,
			os_Root_action *given_root_action = 0,
			os_Schema_action * given_schema_action = 0,
			os_boolean should_do_roots_last = 0);
    os_Database_action (const os_Database_action& database_action);
    virtual ~os_Database_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Database_action& database_action,
			os_database& given_database)
      { os_Database_node node(database_action, given_database);
	os_Database_action& action = node.setup_action();
	(action)(given_database);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (os_database& database);

  protected: // Embedded data
    os_Segment_action* segment_action;
    os_Root_action* root_action;
    os_Schema_action* schema_action;
    os_boolean should_do_roots_last;

  protected: // Accessors
    os_Database_node& get_database_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Traverser;

  };


#endif /* DB_ACTION_HH */
