/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef PRED_ACTION_HH
#define PRED_ACTION_HH

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
  class os_Predef_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Predef_node : public os_Object_node {

  public: // Construction
    os_Predef_node (os_Predef_action&, const os_type&, void* object);
    os_Predef_node (os_Predef_action&, const os_type&, 
		    void* object, unsigned total_elements);
    os_Predef_node (os_Predef_action&, const os_type&, void* class_object,
		    const os_member_variable&);
    os_Predef_node (os_Predef_action&, const os_type&);
    os_Predef_node (os_Predef_action&, const os_type&,
		    const os_member_variable& member_variable);
    virtual ~os_Predef_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Predef_action& get_predef_action () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const 
      { visitor.visit(*this); }

  protected: // Embedded data
    const os_member_variable* member_variable;

  };


/***********************************************************************
  class os_Predef_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Predef_action : public os_Action {

  public: // Construction
    os_Predef_action ();
    os_Predef_action (const os_Predef_action& predef_action);
    virtual ~os_Predef_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Predef_action& predef_action,
			const os_type& actual_type, void* given_object)
      { os_Predef_node node(predef_action, actual_type, given_object);
	os_Predef_action& action = node.setup_action();
	(action)(actual_type, given_object);
      }
    static void invoke (os_Predef_action& predef_action,
			const os_type& actual_type, void* class_object,
			const os_member_variable& given_member_variable)
      { os_Predef_node node(predef_action, actual_type, class_object,
			    given_member_variable);
	os_Predef_action& action = node.setup_action();
	(action)(actual_type, class_object, given_member_variable);
      }
    static void invoke (os_Predef_action& predef_action,
			const os_type& actual_type)
      { os_Predef_node node(predef_action, actual_type);
	os_Predef_action& action = node.setup_action();
	(action)(actual_type);
      }
    static void invoke (os_Predef_action& predef_action,
			const os_type& actual_type,
			const os_member_variable& member_variable)
      { os_Predef_node node(predef_action, actual_type, member_variable);
	os_Predef_action& action = node.setup_action();
	(action)(actual_type, member_variable);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (const os_type& actual_type, void* object);
    virtual void operator () (const os_type& actual_type, 
			      void* class_object,
			      const os_member_variable& member_variable);
    virtual void operator () (const os_type& actual_type);
    virtual void operator () (const os_type& actual_type,
			      const os_member_variable& member_variable);
    virtual void char_array_action (const os_type& actual_type, 
				    void* object, 
				    unsigned total_elements);
    virtual void number_array_action (const os_type& actual_type, 
				      void* object, 
				      unsigned total_elements);

  protected: // Accessors
    os_Predef_node& get_predef_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Object_action;
    friend class os_Member_variable_action;
    friend class os_Indirect_action;
    friend class os_Array_action;

  };


#endif /* PRED_ACTION_HH */
