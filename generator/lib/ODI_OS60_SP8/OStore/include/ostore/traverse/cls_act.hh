/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLS_ACTION_HH
#define CLS_ACTION_HH

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
#include <ostore/mop.hh>
#include <ostore/traverse/obj_act.hh>
#include <ostore/traverse/base_act.hh>
#include <ostore/traverse/mem_act.hh>
#include <ostore/traverse/wrp_act.hh>


/***********************************************************************
  class os_Class_node
***********************************************************************/

template <class Key, class Value>  class _OST_hash;

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Class_node : public os_Object_node {

 public: // Construction
  os_Class_node (os_Class_action&, const os_class_type&, void* object);
  os_Class_node (os_Class_action&, const os_class_type&, 
		 void* object, unsigned total_elements);
  os_Class_node (os_Class_action&, const os_class_type&);
  os_Class_node (os_Class_action&, const os_class_type&,
		 const os_member_variable& member_variable);
  virtual ~os_Class_node ();

 public: // Accessors
  typedef _OST_hash<const char*, os_type*> Processed_siblings ;
  virtual os_Action::Action_kind get_kind () const;
  os_Class_action& get_class_action () const;
  const os_class_type& get_class_type () const;
    

 public: // Visitors
  virtual void be_visited_by(os_Action_node_visitor &visitor) const
    { visitor.visit(*this); }

 public:
  Processed_siblings& get_processed_siblings () const;

 private:// Embedded data
  Processed_siblings* processed_siblings;
  
};

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Class_action : public os_Action {
 public:

 public: // Construction

  os_Class_action (os_Base_action* base_action = 0,
		   os_Member_variable_action* variable_action = 0,
		   os_Member_function_action* function_action = 0,
		   os_Member_type_action* type_action = 0,
		   os_Member_access_modifier_action* access_modifier_action = 0);

  os_Class_action (const os_Class_action& class_action);

  virtual ~os_Class_action ();

  virtual os_Action& duplicate (const os_Action*) const;

 public: // static Actions
  static void invoke (os_Class_action& class_action,
		      const os_class_type& actual_class,
		      void* given_object);
  static void invoke (os_Class_action& class_action,
		      const os_class_type& actual_class);
  static void invoke (os_Class_action& class_action,
		      const os_class_type& actual_class,
		      const os_member_variable& member_variable);
  
 public: // Accessors
  virtual Action_kind get_kind () const;
  virtual int has_state () const;
  virtual os_boolean is_most_derived_class() const;
  virtual os_boolean is_specializing () const;
  os_boolean is_definition_order () const;
  os_boolean is_layout_order () const;

 public: // Modifiers
  void set_is_definition_order ();
  void set_is_layout_order ();
  void set_is_specializing (os_boolean);
  
 public: // Actions
  virtual void operator () (const os_class_type& actual_class, 
			    void* object);
  virtual void operator () (const os_class_type& actual_class);
  virtual void operator () (const os_class_type& actual_class,
			    const os_member_variable& member_variable);

 public: // Component Actions
  virtual void apply_component_actions 
    (const os_class_type& actual_class, void* object);
  virtual void apply_component_actions 
    (const os_class_type& actual_class);



 protected: // Embedded data
  virtual os_unsigned_int32 get_union_discriminant(const os_class_type &actual_union,
						   void *object) const;
  os_Base_action* base_action;
  os_Member_variable_action* variable_action;
  os_Member_function_action* function_action;
  os_Member_type_action* type_action;
  os_Member_access_modifier_action* access_modifier_action;
  os_boolean layout_order;
  os_boolean specializing;

 protected: // Accessors
  os_Class_node& get_class_node () const;
  os_boolean is_unprocessed_sibling (const os_class_type& actual_class,
				     const os_type& type) const;

 protected: // Modifiers
  virtual void set_traverser (os_Traverser&);
  void insert_processed_sibling (const os_type& given_type);


 protected: // Actions
  void process_sibling (const os_class_type& actual_class,
			const os_type& type);

 private: // Friends
  friend class os_Object_action;
  friend class os_Member_variable_action;
  friend class os_Member_type_action;
  friend class os_Base_action;
  friend class os_Indirect_action;
  friend class os_Array_action;
  friend class os_Schema_action;
};


/***********************************************************************
  class os_Class_specialization_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Class_specialization_node : public os_Object_node {

  public: // Construction
    os_Class_specialization_node (os_Class_specialization&,
				  const os_class_type&, void* object);
    os_Class_specialization_node (os_Class_specialization&,
				  const os_class_type&, void* object,
				  unsigned total_elements);
    os_Class_specialization_node (os_Class_specialization&,
				  const os_class_type&);
    os_Class_specialization_node (os_Class_specialization&,
				  const os_class_type&,
				  const os_member_variable& member_variable);
    virtual ~os_Class_specialization_node ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const;
    os_Class_specialization& get_class_specialization () const;
    const os_class_type& get_class_type () const;

  };


/***********************************************************************
  class os_Class_specialization
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Class_specialization : public os_Class_action {

  public: // static Actions
    static void invoke (os_Class_specialization& class_specialization,
      os_Traverser& traverser,
      const os_class_type& actual_class, 
      void* given_object) { 
      /* TBD: revisit the setting of a os_Class_specialization's traverser
      in this manner. While each os_Traverser within a process
      can be expected to have its own action instances, this
      would currently be problematic for specializations as
      there is only one set per process. --rick@odi.com */
      class_specialization.set_traverser(traverser);
      os_Class_specialization_node node(class_specialization, actual_class,
        given_object);
      os_Class_specialization& action = node.setup_action();
      (action)(actual_class, given_object);
    }

    static void invoke (os_Class_specialization& class_specialization,
      os_Traverser& traverser,
      const os_class_type& actual_class) { 
      /* TBD: revisit the setting of a os_Class_specialization's traverser
      in this manner. While each os_Traverser within a process
      can be expected to have its own action instances, this
      would currently be problematic for specializations as
      there is only one set per process. --rick@odi.com */
      class_specialization.set_traverser(traverser);
      os_Class_specialization_node node(class_specialization, actual_class);
      os_Class_specialization& action = node.setup_action();
      (action)(actual_class);
    }

    static void invoke (os_Class_specialization& class_specialization,
      os_Traverser& traverser,
      const os_class_type& actual_class,
      const os_member_variable& member_variable)    { 
      /* TBD: revisit the setting of a os_Class_specialization's traverser
      in this manner. While each os_Traverser within a process
      can be expected to have its own action instances, this
      would currently be problematic for specializations as
      there is only one set per process. --rick@odi.com */
      class_specialization.set_traverser(traverser);
      os_Class_specialization_node node(class_specialization, actual_class,
        member_variable);
      os_Class_specialization& action = node.setup_action();
      (action)(actual_class, member_variable);
    }

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual int has_state () const;
    virtual os_boolean is_specializing () const;
    const char* get_class_name () const;


  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    const char* class_name;

  protected: // Accessors
    os_Class_specialization_node& get_class_specialization_node () const;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Class_specialization_node;

  };


/***********************************************************************
  class os_Nop_specialization
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Nop_specialization : public os_Class_specialization {

  public: // Accessors
    virtual Action_kind get_kind () const;
    virtual os_boolean is_specializing () const;

  public: // Actions
    virtual void operator () (const os_class_type& actual_class, 
			      void* object);
    virtual void operator () (const os_class_type& actual_class, 
			      void* object, unsigned total_elements);
    virtual void operator () (const os_class_type& actual_class);
    virtual void operator () (const os_class_type& actual_class,
			      const os_member_variable& member_variable);

  };




#endif /* CLS_ACTION_HH */
