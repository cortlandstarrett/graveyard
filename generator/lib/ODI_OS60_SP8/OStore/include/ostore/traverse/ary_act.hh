/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef ARY_ACTION_HH
#define ARY_ACTION_HH

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
  class os_Array_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Array_node : public os_Object_node {

  public: // Construction
    os_Array_node (os_Array_action&, const os_array_type&, void* object);
    os_Array_node (os_Array_action&, const os_array_type&);
    os_Array_node (os_Array_action&, const os_array_type&,
		   const os_member_variable& member_variable);
    virtual ~os_Array_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Array_action& get_array_action () const;
    const os_array_type& get_array_type () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  public:
    os_int32 current_index;
  };


/***********************************************************************
  class os_Array_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Array_action : public os_Action {

  public: // Construction
    os_Array_action (os_Predef_action* predef_action = 0,
		     os_Enum_action* enum_action = 0,
		     os_Pointer_action* pointer_action = 0,
		     os_Class_action* class_action = 0,
		     os_Function_action* function_action = 0,
		     os_Indirect_action* indirect_action = 0);
    os_Array_action (const os_Array_action& array_action);
    virtual ~os_Array_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Array_action& array_action,
			const os_array_type& actual_array, void* given_object)
      { os_Array_node node(array_action, actual_array, given_object);
	os_Array_action& action = node.setup_action();
	(action)(actual_array, given_object);
      }
    static void invoke (os_Array_action& array_action,
			const os_array_type& actual_array)
      { os_Array_node node(array_action, actual_array);
	os_Array_action& action = node.setup_action();
	(action)(actual_array);
      }
    static void invoke (os_Array_action& array_action,
			const os_array_type& actual_array,
			const os_member_variable& member_variable)
      { os_Array_node node(array_action, actual_array, member_variable);
	os_Array_action& action = node.setup_action();
	(action)(actual_array, member_variable);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Modifiers
    void set_class_action (os_Class_action& action);
    void set_indirect_action (os_Indirect_action& action);

  public: // Actions
    virtual void operator () (const os_array_type& actual_array, 
			      void* object);
    virtual void operator () (const os_array_type& actual_array);
    virtual void operator () (const os_array_type& actual_array,
			      const os_member_variable& member_variable);

  public: // Element Actions
    virtual void apply_element_actions (const os_array_type& actual_array);

  protected: // Embedded data
    os_Predef_action* predef_action;
    os_Enum_action* enum_action;
    os_Pointer_action* pointer_action;
    os_Class_action* class_action;
    os_Function_action* function_action;
    os_Indirect_action* indirect_action;

  protected: // Accessors
    os_Array_node& get_array_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Object_action;
    friend class os_Member_variable_action;
    friend class os_Indirect_action;

  };


#endif /* ARY_ACTION_HH */



