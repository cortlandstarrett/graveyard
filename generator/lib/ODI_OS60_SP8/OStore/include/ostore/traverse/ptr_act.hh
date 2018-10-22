/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef PTR_ACTION_HH
#define PTR_ACTION_HH

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
  class os_Pointer_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Pointer_node : public os_Object_node {

  public: // Construction
    os_Pointer_node (os_Pointer_action&, const os_pointer_type&, void* object);
    os_Pointer_node (os_Pointer_action&, const os_pointer_type&, 
		     void* object, unsigned total_elements);
    os_Pointer_node (os_Pointer_action&, const os_pointer_type&);
    os_Pointer_node (os_Pointer_action&, const os_pointer_type&,
		     const os_member_variable& member_variable);
    virtual ~os_Pointer_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Pointer_action& get_pointer_action () const;
    const os_pointer_type& get_pointer_type () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }
  };


/***********************************************************************
  class os_Pointer_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Pointer_action : public os_Action {

  public: // Construction
    os_Pointer_action ();
    os_Pointer_action (const os_Pointer_action& pointer_action);
    virtual ~os_Pointer_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Pointer_action& pointer_action,
			const os_pointer_type& actual_pointer, 
			void* given_object)
      { os_Pointer_node node(pointer_action, actual_pointer, given_object);
	os_Pointer_action& action = node.setup_action();
	(action)(actual_pointer, given_object);
      }
    static void invoke (os_Pointer_action& pointer_action,
			const os_pointer_type& actual_pointer)
      { os_Pointer_node node(pointer_action, actual_pointer);
	os_Pointer_action& action = node.setup_action();
	(action)(actual_pointer);
      }
    static void invoke (os_Pointer_action& pointer_action,
			const os_pointer_type& actual_pointer,
			const os_member_variable& member_variable)
      { os_Pointer_node node(pointer_action, actual_pointer, member_variable);
	os_Pointer_action& action = node.setup_action();
	(action)(actual_pointer, member_variable);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (const os_pointer_type& actual_pointer, 
			      void* object);
    virtual void operator () (const os_pointer_type& actual_pointer);
    virtual void operator () (const os_pointer_type& actual_pointer,
			      const os_member_variable& member_variable);

  protected: // Accessors
    os_Pointer_node& get_pointer_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Object_action;
    friend class os_Member_variable_action;
    friend class os_Indirect_action;
    friend class os_Array_action;

  };


#endif /* PTR_ACTION_HH */


