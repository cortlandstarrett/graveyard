/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef FUNC_ACTION_HH
#define FUNC_ACTION_HH

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
#include <ostore/traverse/obj_act.hh>


/***********************************************************************
  class os_Function_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Function_node : public os_Object_node {

  public: // Construction
    os_Function_node (os_Function_action&, const os_type&);
    virtual ~os_Function_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Function_action& get_function_action () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }
  };


/***********************************************************************
  class os_Function_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Function_action : public os_Action {

  public: // Construction
    os_Function_action ();
    os_Function_action (const os_Function_action& function_action);
    virtual ~os_Function_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Function_action& function_action,
			const os_type& actual_type)
      { os_Function_node node(function_action, actual_type);
	os_Function_action& action = node.setup_action();
	(action)(actual_type);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (const os_type& actual_type);

  protected: // Accessors
    os_Function_node& get_function_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Object_action;
    friend class os_Member_variable_action;
    friend class os_Indirect_action;
    friend class os_Array_action;

  };


#endif /* FUNC_ACTION_HH */
