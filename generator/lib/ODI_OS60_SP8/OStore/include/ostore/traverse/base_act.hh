/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef BASE_ACTION_HH
#define BASE_ACTION_HH

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


/***********************************************************************
  class os_Base_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Base_node : public os_Action_node {

  public: // Construction
    os_Base_node (os_Base_action&, void* class_object, 
		  const os_base_class& base_class);
    os_Base_node (os_Base_action&, const os_base_class& base_class);
    virtual ~os_Base_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Base_action& get_base_action () const;
    const os_base_class& get_base_class () const;
    void* get_class_object () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  protected: // Embedded data
    const os_base_class* base_class;
    void* class_object;

  };


/***********************************************************************
  class os_Base_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Base_action : public os_Action {

  public: // Construction
    os_Base_action (os_Class_action* class_action = 0);
    os_Base_action (const os_Base_action& base_action);
    virtual ~os_Base_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Base_action& base_action, void* class_object,
			const os_base_class& base_class)
      { os_Base_node node(base_action, class_object, base_class);
	os_Base_action& action = node.setup_action();
	(action)(class_object, base_class);
      }
    static void invoke (os_Base_action& base_action,
			const os_base_class& base_class)
      { os_Base_node node(base_action, base_class);
	os_Base_action& action = node.setup_action();
	(action)(base_class);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Modifiers
    void set_class_action (os_Class_action& action);

  public: // Actions
    virtual void operator () (void* class_object, 
			      const os_base_class& base_class);
    virtual void operator () (const os_base_class& base_class);

  protected: // Embedded data
    os_Class_action* class_action;

  protected: // Accessors
    os_Base_node& get_base_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Class_action;
    friend class os_Class_specialization;

  };


#endif /* BASE_ACTION_HH */
