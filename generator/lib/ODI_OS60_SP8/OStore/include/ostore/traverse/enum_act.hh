/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef ENUM_ACTION_HH
#define ENUM_ACTION_HH

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
  class os_Enum_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Enum_node : public os_Object_node {

  public: // Construction
    os_Enum_node (os_Enum_action&, const os_enum_type&, void* object);
    os_Enum_node (os_Enum_action&, const os_enum_type&, 
		  void* object, unsigned total_elements);
    os_Enum_node (os_Enum_action&, const os_enum_type&, void* class_object,
		  const os_member_variable&);
    os_Enum_node (os_Enum_action&, const os_enum_type&);
    os_Enum_node (os_Enum_action&, const os_enum_type&,
		  const os_member_variable& member_variable);
    virtual ~os_Enum_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Enum_action& get_enum_action () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  protected: // Embedded data
    const os_member_variable* member_variable;

  };


/***********************************************************************
  class os_Enum_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Enum_action : public os_Action {

  public: // Construction
    os_Enum_action ();
    os_Enum_action (const os_Enum_action& enum_action);
    virtual ~os_Enum_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Enum_action& enum_action,
			const os_enum_type& actual_type, void* given_object)
      { os_Enum_node node(enum_action, actual_type, given_object);
	os_Enum_action& action = node.setup_action();
	(action)(actual_type, given_object);
      }
    static void invoke (os_Enum_action& enum_action,
			const os_enum_type& actual_type, void* class_object,
			const os_member_variable& given_member_variable)
      { os_Enum_node node(enum_action, actual_type, class_object,
			  given_member_variable);
	os_Enum_action& action = node.setup_action();
	(action)(actual_type, class_object, given_member_variable);
      }
    static void invoke (os_Enum_action& enum_action,
			const os_enum_type& actual_type)
      { os_Enum_node node(enum_action, actual_type);
	os_Enum_action& action = node.setup_action();
	(action)(actual_type);
      }
    static void invoke (os_Enum_action& enum_action,
			const os_enum_type& actual_type,
			const os_member_variable& member_variable)
      { os_Enum_node node(enum_action, actual_type, member_variable);
	os_Enum_action& action = node.setup_action();
	(action)(actual_type, member_variable);
      }


  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (const os_enum_type& actual_type, 
			      void* object);
    virtual void operator () (const os_enum_type& actual_type, 
			      void* class_object,
			      const os_member_variable& member_variable);
    virtual void operator () (const os_enum_type& actual_type);
    virtual void operator () (const os_enum_type& actual_type,
			      const os_member_variable& member_variable);

  protected: // Accessors
    os_Enum_node& get_enum_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Object_action;
    friend class os_Member_variable_action;
    friend class os_Member_type_action;
    friend class os_Indirect_action;
    friend class os_Array_action;

  };


#endif /* ENUM_ACTION_HH */

