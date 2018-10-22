/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef ACTION_HH
#define ACTION_HH

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
#include <ostore/portypes.hh>
#include <ostore/ostore.hh>
#include <ostore/mop.hh>

/***********************************************************************
  Forward Declarations
***********************************************************************/

class os_Traverser;

class  os_Action;
class  os_Database_action;
class  os_Root_action;
class  os_Segment_action;
class  os_Cluster_action;
class  os_Object_action;
class  os_Predef_action;
class  os_Enum_action;
class  os_Pointer_action;
class  os_Array_action;
class  os_Class_action;
class  os_Function_action;
class  os_Indirect_action;
class  os_Base_action;
class  os_Member_variable_action;
class  os_Member_function_action;
class  os_Member_type_action;
class  os_Member_access_modifier_action;
class  os_Class_specialization;
class  os_Nop_specialization;
class  os_Schema_action;

class  os_Action_node;
class  os_Database_node;
class  os_Root_node;
class  os_Segment_node;
class  os_Cluster_node;
class  os_Object_node;
class  os_Predef_node;
class  os_Enum_node;
class  os_Pointer_node;
class  os_Array_node;
class  os_Class_node;
class  os_Function_node;
class  os_Indirect_node;
class  os_Base_node;
class  os_Member_variable_node;
class  os_Member_function_node;
class  os_Member_type_node;
class  os_Member_access_modifier_node;
class  os_Class_specialization_node;
class  os_Schema_node;

class  os_Action_node_visitor;

/***********************************************************************
  typedef os_String_const_list
***********************************************************************/

//typedef os_List<const char*> os_String_const_list;


/***********************************************************************
  class os_Action_wrapper
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Action_wrapper {

  public: // Construction
    os_Action_wrapper ();
    os_Action_wrapper (const os_Action_wrapper&);
    virtual ~os_Action_wrapper ();

  public: // Accessors
    os_Traverser& get_traverser () const;
    os_boolean is_embedded () const;
    os_boolean is_within_class (unsigned level = 0) const;
    os_boolean is_within_array (unsigned level = 0) const;

  protected: // Embedded data
    os_Traverser* traverser;

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  };


/***********************************************************************
  class os_Action
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Action : public os_Action_wrapper {

  public: // Subtypes
    /* Note kind string below if updating list */
    enum Action_kind { 
        no_kind, 
        database_kind, 
        segment_kind, 
        cluster_kind,
        object_kind, 
        predef_kind, 
        enumeration_kind, 
        pointer_kind, 
        array_kind, 
        class_kind, 
        function_kind,
        indirect_kind, 
        base_kind, 
        member_variable_kind, 
        member_function_kind, 
        member_type_kind, 
        access_modifier_kind, 
        root_kind, 
        specialization_kind, 
        schema_kind, 
        nop_specialization_kind 
    };

  public: // Construction
    os_Action ();
    os_Action (const os_Action&);
    virtual ~os_Action ();
    virtual os_Action& duplicate (const os_Action*) const = 0;

  public: // Coercions
    operator const os_Database_action& () const;
    operator os_Database_action& ();
    operator const os_Segment_action& () const;
    operator os_Segment_action& ();
    operator const os_Cluster_action& () const;
    operator os_Cluster_action& ();
    operator const os_Object_action& () const;
    operator os_Object_action& ();
    operator const os_Predef_action& () const;
    operator os_Predef_action& ();
    operator const os_Enum_action& () const;
    operator os_Enum_action& ();
    operator const os_Pointer_action& () const;
    operator os_Pointer_action& ();
    operator const os_Array_action& () const;
    operator os_Array_action& ();
    operator const os_Class_action& () const;
    operator os_Class_action& ();
    operator const os_Function_action& () const;
    operator os_Function_action& ();
    operator const os_Indirect_action& () const;
    operator os_Indirect_action& ();
    operator const os_Base_action& () const;
    operator os_Base_action& ();
    operator const os_Member_variable_action& () const;
    operator os_Member_variable_action& ();
    operator const os_Member_function_action& () const;
    operator os_Member_function_action& ();
    operator const os_Member_type_action& () const;
    operator os_Member_type_action& ();
    operator const os_Member_access_modifier_action& () const;
    operator os_Member_access_modifier_action& ();
    operator const os_Root_action& () const;
    operator os_Root_action& ();
    operator const os_Class_specialization& () const;
    operator os_Class_specialization& ();
    operator const os_Nop_specialization& () const;
    operator os_Nop_specialization& ();

  public: // Accessors
    virtual Action_kind get_kind () const = 0;
    virtual int has_state () const = 0;
    const char* get_kind_string(); 

  protected: // Accessors
    os_Action_node& get_action_node () const;
    virtual void debug_stack_enter(const void* mop_obj, void* object=0);
    virtual void debug_stack_exit(const void* mop_obj, void* object=0);
    static const char* kind_string[20];
  };


/***********************************************************************
  class os_Action_node
***********************************************************************/

class _OS_DLLIMPORT(_OS_TRAVERSE) os_Action_node : public basic_undo {

  public: // Construction
    os_Action_node (os_Action&);
    virtual ~os_Action_node ();

  public: // Coercions
    operator const os_Database_node& () const;
    operator os_Database_node& ();
    operator const os_Segment_node& () const;
    operator os_Segment_node& ();
    operator const os_Object_node& () const;
    operator os_Object_node& ();
    operator const os_Predef_node& () const;
    operator os_Predef_node& ();
    operator const os_Enum_node& () const;
    operator os_Enum_node& ();
    operator const os_Pointer_node& () const;
    operator os_Pointer_node& ();
    operator const os_Array_node& () const;
    operator os_Array_node& ();
    operator const os_Class_node& () const;
    operator os_Class_node& ();
    operator const os_Function_node& () const;
    operator os_Function_node& ();
    operator const os_Indirect_node& () const;
    operator os_Indirect_node& ();
    operator const os_Base_node& () const;
    operator os_Base_node& ();
    operator const os_Member_variable_node& () const;
    operator os_Member_variable_node& ();
    operator const os_Member_function_node& () const;
    operator os_Member_function_node& ();
    operator const os_Member_type_node& () const;
    operator os_Member_type_node& ();
    operator const os_Member_access_modifier_node& () const;
    operator os_Member_access_modifier_node& ();
    operator const os_Root_node& () const;
    operator os_Root_node& ();
    operator const os_Class_specialization_node& () const;
    operator os_Class_specialization_node& ();

  public: // Accessors
    virtual os_Action::Action_kind get_kind () const = 0;
    os_Action_node* get_outermost_node () const;
    os_Action_node* get_previous_node () const;
    os_Action_node* get_next_node () const;
    os_Action& get_action () const;
    os_Traverser& get_traverser () const;

  public: // Modifiers
    virtual os_Action& setup_action ();

  public: // Visitors
    virtual void be_visited_by(os_Action_node_visitor&) const = 0;

  protected: // Embedded data
    os_Action_node* outermost_node;
    os_Action_node* previous_node;
    os_Action_node* next_node;
    os_Action* action;

  protected: // Modifiers
    void push ();
    os_Action_node* pop ();
    os_Action_node* top () const;

  };


/******************************************************************************
  class os_Action_node_visitor
******************************************************************************/

class  _OS_DLLIMPORT(_OS_TRAVERSE) os_Action_node_visitor
{
public:
  virtual void visit(const os_Database_node&) {}
  virtual void visit(const os_Segment_node&) {}
  virtual void visit(const os_Cluster_node&) {}
  virtual void visit(const os_Schema_node&) {}
  virtual void visit(const os_Object_node&) {}
  virtual void visit(const os_Predef_node&) {}
  virtual void visit(const os_Enum_node&) {}
  virtual void visit(const os_Pointer_node&) {}
  virtual void visit(const os_Array_node&) {}
  virtual void visit(const os_Class_node&) {}
  virtual void visit(const os_Function_node&) {}
  virtual void visit(const os_Indirect_node&) {}
  virtual void visit(const os_Base_node&) {}
  virtual void visit(const os_Member_variable_node&) {}
  virtual void visit(const os_Member_function_node&) {}
  virtual void visit(const os_Member_type_node&) {}
  virtual void visit(const os_Member_access_modifier_node&) {}
  virtual void visit(const os_Root_node&) {}
  virtual void visit(const os_Class_specialization_node&) {}
};


class  _OS_DLLIMPORT(_OS_TRAVERSE) os_Path_visitor
  : public os_Action_node_visitor
{
 public:
  virtual void visit(const os_Database_node&);
  virtual void visit(const os_Segment_node&);
  virtual void visit(const os_Cluster_node&);
  virtual void visit(const os_Object_node&);
  virtual void visit(const os_Array_node&);
  virtual void visit(const os_Class_node&);
  virtual void visit(const os_Base_node&);
  virtual void visit(const os_Member_variable_node&);
  virtual void visit(const os_Member_type_node&);
  virtual void visit(const os_Root_node&);
  //To quiet sol2c4
  virtual void visit(const os_Pointer_node&) {}
  virtual void visit(const os_Class_specialization_node&) {}
  virtual void visit(const os_Member_access_modifier_node&) {}
  virtual void visit(const os_Member_function_node&) {}
  virtual void visit(const os_Indirect_node&) {}
  virtual void visit(const os_Function_node&) {}
  virtual void visit(const os_Enum_node&) {}
  virtual void visit(const os_Predef_node&) {}
  virtual void visit(const os_Schema_node&) {}
  
 public:
  os_Path_visitor();
  ~os_Path_visitor();

  operator const char *() const;
  operator char*() const;

  void reset();

 private:
  char *buffer;
  os_unsigned_int32 buffer_length;
  os_unsigned_int32 path_length;
  os_boolean visited_class;

 private:
  void resize_buffer(os_unsigned_int32 required_space);

  os_Path_visitor &operator <<(const char *);

  os_Path_visitor &operator <<(os_unsigned_int32);
};

#endif /* ACTION_HH */
