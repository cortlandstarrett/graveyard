/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef ROOT_ACTION_HH
#define ROOT_ACTION_HH

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

//-- Forward declaration -----------------------------------------------
class os_Root_action;

//-- Include files -----------------------------------------------------

#include <ostore/ostore.hh>
#include <ostore/traverse/action.hh>

/***********************************************************************
  class os_Root_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE)  os_Root_node : public os_Action_node {
  public: // Construction
    os_Root_node(os_Root_action&, const os_database &);
    virtual ~os_Root_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Root_action& get_root_action () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  public:
    os_database *database;

  };


/***********************************************************************
  class os_Root_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE)  os_Root_action : public os_Action {

  public: // Construction
    os_Root_action ();
    os_Root_action (const os_Root_action& class_action);
    virtual ~os_Root_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Root_action& root_action,
			os_database& db)
      { os_Root_node node(root_action, db);
	os_Root_action& action = (os_Root_action &)node.setup_action();
	(action)(db);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (os_database& db);

  public: // Modifiers
    virtual void set_traverser (os_Traverser&);

  protected: // Accessors
    os_Root_node& get_root_node () const;

  };


#endif /* ROOT_ACTION_HH */

