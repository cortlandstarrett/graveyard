/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef SCHM_ACTION_HH
#define SCHM_ACTION_HH

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
#include <ostore/mop.hh>

#include <ostore/traverse/action.hh>
#include <ostore/traverse/obj_act.hh>

class os_Schema_action;

/***********************************************************************
  class os_Schema_node
***********************************************************************/

class  _OS_DLLIMPORT(_OS_TRAVERSE) os_Schema_node : public os_Action_node {

  public: // Construction
    os_Schema_node (os_Schema_action& given_schema_action, 
		    os_schema& given_schema);
    virtual ~os_Schema_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Schema_action& get_schema_action () const;
    os_schema& get_schema () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  public: // Embedded data
    os_schema* schema;

  };


/***********************************************************************
  class os_Schema_action
***********************************************************************/

class  _OS_DLLIMPORT(_OS_TRAVERSE) os_Schema_action : public os_Action {

  public: // Construction
    os_Schema_action (const os_Schema_action& given_schema_action);
    os_Schema_action (os_Object_action* given_object_action,
		      os_Class_action* given_class_action);
    virtual ~os_Schema_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Schema_action& schema_action,
			os_schema& given_schema)
      { os_Schema_node node(schema_action, given_schema);
	os_Schema_action& action = (os_Schema_action&)node.setup_action();
	(action)(given_schema);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (os_schema& schema);

  protected: // Embedded data
    os_Object_action* object_action;
    os_Class_action* class_action;

  protected: // Accessors
    os_Schema_node& get_schema_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  protected: // Actions
    virtual void schema_action (os_schema& schema);

  private: // Friends
    friend class os_Database_action;

  };


#endif /* SCHM_ACTION_HH */
