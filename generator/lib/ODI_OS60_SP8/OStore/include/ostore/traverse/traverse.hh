/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef TRAVERSE_HH
#define TRAVERSE_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1997-2000 by eXcelon Corporation. All Rights Reserved. *
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
#include <ostore/traverse/db_act.hh>
#include <ostore/traverse/wrp_act.hh>

//-- Forward Declaration -----------------------------------------------

class os_Traverser;
class os_Class_action;
class os_Class_node;
class Class_Execution_Step;


/***********************************************************************
  class os_Sub_object_offset
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Sub_object_offset {

  public: // Construction
    os_Sub_object_offset (unsigned byte_offset, unsigned bit_offset);
    os_Sub_object_offset ();
    ~os_Sub_object_offset ();

  public: // Accessors
    unsigned get_byte_offset () const;
    unsigned get_bit_offset () const;

  protected: // Embedded data
    unsigned byte_offset;
    unsigned bit_offset;

  private: // Friends
    friend class os_Traverser;

  };


/***********************************************************************
  class os_Traverser
***********************************************************************/

class  _OS_DLLIMPORT(_OS_TRAVERSE) os_Traverser {

  public: // Subtypes
    enum Traverser_error {
        unknown, 
        bad_initialization, 
        bad_action_stack,
        bad_cast, 
        unexpected_traverser 
    };

    enum Debug_level { 
        no_debug, 
        database_level, 
        segment_level,
        object_level, 
        trace_level, 
        component_level,
        invocation_level, 
        frame_level 
    };

    typedef os_Class_specialization* (*Find_specialization_function) 
        (const char* class_name);

  public: // Construction
    os_Traverser (os_Wrapper_actions& wrapper_actions,
		  os_Database_action* database_action = 0,
		  Find_specialization_function specialization_function = 0);
    virtual ~os_Traverser ();

  public: // Accessors
    virtual const char* get_kind_string () const;
    os_Action_node* get_top_action_node () const;
    os_Action_node* get_outermost_action_node () const;
    os_Wrapper_actions& get_wrapper_actions () const;
    os_boolean is_handling_schema () const;
    os_boolean is_handling_schema_segment () const;
    os_boolean is_handling_indirect_types () const;
    os_boolean is_within_class (unsigned level = 0) const;
    os_boolean is_at_class_level (unsigned level) const;
    os_boolean is_within_array (unsigned level = 0) const;
    os_boolean is_at_array_level (unsigned level) const;
    os_boolean is_locking_databases () const;
    char* get_indentation () const;
    os_Class_specialization* find_specialization 
        (const char* class_name) const;
    os_Sub_object_offset get_sub_object_offset () const;
    os_Class_action* get_class_action () const;
    virtual const os_class_type &get_full_definition(const os_class_type &actual_class);
    virtual const char* get_inner_path_string(os_Action::Action_kind
					      inside_kind = os_Action::object_kind);
    virtual const char* get_full_path_string();

  public: // Modifers
    void set_wrapper_actions (os_Wrapper_actions& actions);
    void set_is_handling_schema (os_boolean is_handling);
    void set_is_handling_schema_segment (os_boolean is_handling);
    void set_is_handling_indirect_types (os_boolean);
    void set_is_locking_databases (os_boolean);
    void set_specialization_function(Find_specialization_function sf);

  public: // Actions
    void traverse (const char** database_paths, unsigned total_databases);
    void traverse (const char* database_path);
    void traverse (const char** database_paths, unsigned total_databases, os_database& affiliation);
    void traverse (const char* database_path, os_database& affiliation);
    void traverse (os_database&);
    void traverse (os_segment&);
    void traverse (os_cluster&);
    // TBD: void traverse (os_schema&);
    //void traverse (os_const_classes);
    void traverse (const os_class_type&);
    // TBD: void traverse (const os_type&);
    void traverse (const os_type&, void* object, os_int32 count);
    void traverse (const os_class_type&, void* object);

  public: // Visitors
    virtual void visit_outer_to_inner(os_Action_node_visitor &visitor,
				      os_Action_node *first = 0,
				      os_Action_node *last = 0);
    virtual void visit_inner_to_outer(os_Action_node_visitor &visitor);
    virtual void visit_after_kind_to_inner(os_Action_node_visitor &visitor,
					   os_Action::Action_kind kind =
					   os_Action::object_kind);

  public: // Error handlers
    static void signal (Traverser_error, char const* format ...);
    static void signal (Traverser_error, int value_arg, 
			char const* format ...);

  public: // Debugging
    int is_debugging (Debug_level level = database_level);
    void set_is_debugging (Debug_level);
    void enter_frame ();
    void exit_frame ();
    unsigned get_frame_level () const;

  protected: // Embedded data
    os_Database_action* database_action;
    os_Segment_action* segment_action;
    os_Cluster_action* cluster_action;
    os_Schema_action* schema_action;
    os_Object_action* object_action;
    os_Class_action* class_action;
    os_Wrapper_actions* wrapper_actions;
    os_Action_node* top_action_node;
    os_Action_node* outermost_action_node;
    unsigned nesting_level;
    os_boolean handling_schema;
    os_boolean handling_schema_segment;
    os_boolean handling_indirect_types;
    os_boolean locking_databases;
    unsigned frame_level_value;
    unsigned class_level_value;
    unsigned array_level_value;
    os_Sub_object_offset sub_object_offset;
    Find_specialization_function find_specialization_function;
    os_soft_pointer<os_schema> meta_schema;
    os_Path_visitor path_visitor;

  protected: // Accessors
    os_schema *get_meta_schema(); // caches result, so is not const

  protected: // Modifiers
    void set_top_action_node (os_Action_node*);
    void set_outermost_action_node (os_Action_node*);
    void enter_class (const os_class_type&);
    void exit_class ();
    void enter_array (const os_array_type&);
    void exit_array ();
    unsigned increment_nesting_level ();
    unsigned decrement_nesting_level ();
    void set_action (os_Database_action&);
    void set_action (os_Segment_action&);
    void set_action (os_Cluster_action&);
    void set_action (os_Schema_action&);
    void set_action (os_Object_action&);
    void set_action (os_Class_action&);
    void increment_sub_object_offset (const os_base_class&);
    void increment_sub_object_offset (const os_member_variable&);
    void decrement_sub_object_offset (const os_base_class&);
    void decrement_sub_object_offset (const os_member_variable&);

  private: //embedded data
    int debugging;

  private: // Friends
    friend class os_Action;
    friend class os_Action_node;
    friend class os_Database_node;
    friend class os_Class_node;
    friend class os_Base_node;
    friend class os_Member_variable_node;
    friend class os_Array_node;
    friend class os_Database_action;
    friend class os_Segment_action;
    friend class os_Schema_action;
    friend class os_Cluster_action;
    friend class os_Object_action;
    friend class os_Class_action;
    friend class Class_Execution_step;

  };


#endif /* TRAVERSE_HH */
