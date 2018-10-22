/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef MEM_ACTION_HH
#define MEM_ACTION_HH

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
  class os_Member_variable_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Member_variable_node : public os_Action_node {

  public: // Construction
    os_Member_variable_node (os_Member_variable_action&, void* class_object, 
			     const os_member_variable& member_variable);
    os_Member_variable_node (os_Member_variable_action&,
			     const os_member_variable& member_variable);
    virtual ~os_Member_variable_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Member_variable_action& get_member_variable_action () const;
    const os_member_variable& get_member_variable () const;
    void* get_class_object () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  protected: // Embedded data
    const os_member_variable* member_variable;
    void* class_object;

  };


/***********************************************************************
  class os_Member_variable_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Member_variable_action : public os_Action {

  public: // Construction
    os_Member_variable_action 
	(os_Predef_action* predef_action = 0,
	 os_Enum_action* enum_action = 0,
	 os_Pointer_action* pointer_action = 0,
	 os_Array_action* array_action = 0,
	 os_Class_action* class_action = 0,
	 os_Function_action* function_action = 0,
	 os_Indirect_action* indirect_action = 0);
    os_Member_variable_action 
	(const os_Member_variable_action& member_variable_action);
    virtual ~os_Member_variable_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Member_variable_action& member_variable_action,
			void* class_object, 
			const os_member_variable& given_member_variable)
      { 
      os_Member_variable_node node(member_variable_action, class_object, 
        given_member_variable);
      os_Member_variable_action& action = node.setup_action();
      (action)(class_object, given_member_variable);
      }
    static void invoke (os_Member_variable_action& member_variable_action,
			const os_member_variable& given_member_variable)
      { 
      os_Member_variable_node node(member_variable_action,
        given_member_variable);
      os_Member_variable_action& action = node.setup_action();
      (action)(given_member_variable);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Modifiers
    void set_class_action (os_Class_action& action);
    void set_indirect_action (os_Indirect_action& action);

  public: // Actions
    virtual void operator () (void* class_object, 
			      const os_member_variable& member_variable);
    virtual void operator () (const os_member_variable& member_variable);

  protected: // Embedded data
    os_Predef_action* predef_action;
    os_Enum_action* enum_action;
    os_Pointer_action* pointer_action;
    os_Array_action* array_action;
    os_Class_action* class_action;
    os_Function_action* function_action;
    os_Indirect_action* indirect_action;

  protected: // Accessors
    os_Member_variable_node& get_member_variable_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Class_action;
    friend class os_Class_specialization;

  };


/***********************************************************************
  class os_Member_function_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Member_function_node : public os_Action_node {

  public: // Construction
    os_Member_function_node (os_Member_function_action&, 
      void* class_object, 
      const os_member_function& member_function);
    virtual ~os_Member_function_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Member_function_action& get_member_function_action () const;
    const os_member_function& get_member_function () const;
    void* get_class_object () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  protected: // Embedded data
    const os_member_function& member_function;
    void* class_object;

  };


/***********************************************************************
  class os_Member_function_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Member_function_action : public os_Action {

  public: // Construction
    os_Member_function_action ();
    os_Member_function_action 
	(const os_Member_function_action& member_function_action);
    virtual ~os_Member_function_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Member_function_action& member_function_action,
			void* class_object, 
			const os_member_function& given_member_function)
      { os_Member_function_node node(member_function_action, class_object, 
				     given_member_function);
	os_Member_function_action& action = node.setup_action();
	(action)(class_object, given_member_function);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (void* class_object, 
			      const os_member_function& member_function);
    virtual void operator () (const os_member_function& member_function);

  protected: // Accessors
    os_Member_function_node& get_member_function_node () const;

  private: // Friends
    friend class os_Class_action;
    friend class os_Class_specialization;

  };


/***********************************************************************
  class os_Member_type_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Member_type_node : public os_Action_node {

  public: // Construction
    os_Member_type_node (os_Member_type_action&,
			 const os_member_type& member_type);
    virtual ~os_Member_type_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Member_type_action& get_member_type_action () const;
    const os_member_type& get_member_type () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  protected: // Embedded data
    const os_member_type* member_type;

  };


/***********************************************************************
  class os_Member_type_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Member_type_action : public os_Action {

  public: // Construction
    os_Member_type_action (os_Enum_action* enum_action = 0,
			   os_Class_action* class_action = 0,
			   os_Indirect_action* indirect_action = 0);
    os_Member_type_action 
	(const os_Member_type_action& member_type_action);
    virtual ~os_Member_type_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke (os_Member_type_action& member_type_action,
			const os_member_type& given_member_type)
      { os_Member_type_node node(member_type_action, given_member_type);
	os_Member_type_action& action = node.setup_action();
	(action)(given_member_type);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Modifiers
    void set_class_action (os_Class_action& action);
    void set_indirect_action (os_Indirect_action& action);

  public: // Actions
    virtual void operator () (const os_member_type& member_type);

  protected: // Embedded data
    os_Enum_action* enum_action;
    os_Class_action* class_action;
    os_Indirect_action* indirect_action;

  protected: // Accessors
    os_Member_type_node& get_member_type_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Class_action;
    friend class os_Class_specialization;

  };


/***********************************************************************
  class os_Member_access_modifier_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Member_access_modifier_node : public os_Action_node {

  public: // Construction
    os_Member_access_modifier_node 
	(os_Member_access_modifier_action&, void* class_object, 
	 const os_access_modifier& access_modifier);
    virtual ~os_Member_access_modifier_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Member_access_modifier_action& get_access_modifier_action () const;
    const os_access_modifier& get_access_modifier () const;
    void* get_class_object () const;

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor &visitor) const
      { visitor.visit(*this); }

  protected: // Embedded data
    const os_access_modifier& access_modifier;
    void* class_object;

  };


/***********************************************************************
  class os_Member_access_modifier_action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Member_access_modifier_action : public os_Action {

  public: // Construction
    os_Member_access_modifier_action ();
    os_Member_access_modifier_action 
	(const os_Member_access_modifier_action& member_access_modifier_action);
    virtual ~os_Member_access_modifier_action ();
    virtual os_Action& duplicate (const os_Action*) const;

  public: // static Actions
    static void invoke
        (os_Member_access_modifier_action& access_modifier_action,
	 void* class_object, 
	 const os_access_modifier& given_access_modifier)
      { os_Member_access_modifier_node node(access_modifier_action, 
					    class_object, 
					    given_access_modifier);
	os_Member_access_modifier_action& action = node.setup_action();
	(action)(class_object, given_access_modifier);
      }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;

  public: // Actions
    virtual void operator () (void* class_object, 
			      const os_access_modifier& member_access_modifier);
    virtual void operator () (const os_access_modifier& member_access_modifier);

  protected: // Accessors
    os_Member_access_modifier_node& get_member_access_modifier_node () const;

  private: // Friends
    friend class os_Class_action;
    friend class os_Class_specialization;

  };


#endif /* MEM_ACTION_HH */
