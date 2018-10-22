/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef INDR_ACTION_HH
#define INDR_ACTION_HH

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
  class os_Indirect_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Indirect_node : public os_Object_node {

  public: // Construction
    os_Indirect_node (os_Indirect_action&, const os_indirect_type&, 
		      void* object);
    os_Indirect_node (os_Indirect_action&, const os_indirect_type&, 
		      void* object, unsigned total_elements);
    os_Indirect_node (os_Indirect_action&, const os_indirect_type&);
    os_Indirect_node (os_Indirect_action&, const os_indirect_type&,
		      const os_member_variable& member_variable);
    virtual ~os_Indirect_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Indirect_action& get_indirect_action () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }
  };


/***********************************************************************
  class os_Indirect_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Indirect_action : public os_Action {

  public: // Construction
    os_Indirect_action (os_Predef_action* predef_action = 0,
			os_Enum_action* enum_action = 0,
			os_Pointer_action* pointer_action = 0,
			os_Array_action* array_action = 0,
			os_Class_action* class_action = 0,
			os_Function_action* function_action = 0,
			os_Indirect_action* indirect_action = 0);
    os_Indirect_action (const os_Indirect_action& indirect_action);
    virtual ~os_Indirect_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Indirect_action& indirect_action,
			const os_indirect_type& actual_indirect_type, 
			void* given_object)
      { os_Indirect_node node(indirect_action, actual_indirect_type,
			      given_object);
	os_Indirect_action& action = node.setup_action();
	(action)(actual_indirect_type, given_object);
      }
    static void invoke (os_Indirect_action& indirect_action,
			const os_indirect_type& actual_indirect_type)
      { os_Indirect_node node(indirect_action, actual_indirect_type);
	os_Indirect_action& action = node.setup_action();
	(action)(actual_indirect_type);
      }
    static void invoke (os_Indirect_action& indirect_action,
			const os_indirect_type& actual_indirect_type,
			const os_member_variable& member_variable)
      { os_Indirect_node node(indirect_action, actual_indirect_type,
			      member_variable);
	os_Indirect_action& action = node.setup_action();
	(action)(actual_indirect_type, member_variable);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Modifiers
    void set_class_action (os_Class_action& action);
    void set_indirect_action (os_Indirect_action& action);

  public: // Actions
    virtual void operator () (const os_indirect_type& actual_indirect_type, 
			      void* object);
    virtual void operator () (const os_indirect_type& actual_indirect_type);
    virtual void operator () (const os_indirect_type& actual_indirect_type,
			      const os_member_variable& member_variable);

  public: // Target Type Actions
    virtual void apply_target_type_actions 
        (const os_indirect_type& actual_indirect_type);

  protected: // Embedded data
    os_Predef_action* predef_action;
    os_Enum_action* enum_action;
    os_Pointer_action* pointer_action;
    os_Array_action* array_action;
    os_Class_action* class_action;
    os_Function_action* function_action;
    os_Indirect_action* indirect_action;

  protected: // Accessors
    os_Indirect_node& get_indirect_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Object_action;
    friend class os_Member_variable_action;
    friend class os_Member_type_action;
    friend class os_Array_action;

  };


#endif /* INDR_ACTION_HH */
