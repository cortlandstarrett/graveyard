/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef OBJ_ACTION_HH
#define OBJ_ACTION_HH

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


/***********************************************************************
  class os_Object_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Object_node : public os_Action_node {

  public: // Construction
    os_Object_node (os_Action&, const os_type&, void* object);
    os_Object_node (os_Action&, const os_type&, void* object, 
		    os_int32 count);
    os_Object_node (os_Action&, const os_type&, void* class_object,
		    const os_member_variable& member_variable);
    virtual ~os_Object_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    const os_type& get_type () const;
    void* get_object () const;
    void* get_class_object () const;
    const os_member_variable* get_member_variable () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  public: // Embedded data
    const os_type* type;
    void* object;
    os_int32 count;
    const os_member_variable* member_variable;

  };


/***********************************************************************
  class os_Object_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Object_action : public os_Action {

  public: // Construction
    os_Object_action (os_Predef_action* predef_action = 0,
		      os_Enum_action* enum_action = 0,
		      os_Pointer_action* pointer_action = 0,
		      os_Array_action* array_action = 0,
		      os_Class_action* class_action = 0,
		      os_Function_action* function_action = 0,
		      os_Indirect_action* indirect_action = 0);
    os_Object_action (const os_Object_action& object_action);
    virtual ~os_Object_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Object_action& object_action,
			const os_type& actual_type, void* given_object, 
			os_int32 count)
      { os_Object_node node(object_action, actual_type, given_object, count);
	os_Object_action& action = node.setup_action();
	(action)(actual_type, given_object, count);
      }
    static void invoke (os_Object_action& object_action,
			const os_type& actual_type, void* given_object)
      { os_Object_node node(object_action, actual_type, given_object);
	os_Object_action& action = node.setup_action();
	(action)(actual_type, given_object);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (const os_type& actual_type, void* object, 
			      os_int32 count);
    virtual void operator () (const os_type& actual_type, void* object);

  protected: // Embedded data
    os_Predef_action* predef_action;
    os_Enum_action* enum_action;
    os_Pointer_action* pointer_action;
    os_Array_action* array_action;
    os_Class_action* class_action;
    os_Function_action* function_action;
    os_Indirect_action* indirect_action;
    os_array_type* array_type;

  protected: // Accessors
    os_Object_node& get_object_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Segment_action;
    friend class os_Schema_action;
    friend class os_Cluster_action;
  };


#endif /* OBJ_ACTION_HH */
