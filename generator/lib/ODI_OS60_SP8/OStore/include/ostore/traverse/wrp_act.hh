/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef WRP_ACTION_HH
#define WRP_ACTION_HH

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
#include <ostore/mop.hh>
#include <ostore/traverse/action.hh>


/***********************************************************************
  class os_Wrapper_actions
***********************************************************************/

class  _OS_DLLIMPORT(_OS_TRAVERSE) os_Wrapper_actions : public os_Action_wrapper {

  public: // Subtypes
    enum Traversal_continuation_status { should_continue = 0, 
					 should_discontinue = 1 };

  public: // Construction
    os_Wrapper_actions ();
    virtual ~os_Wrapper_actions ();

  public: // os_Traverser Actions
    // Pre-actions
    virtual os_boolean pre_action (const char** database_paths,
				   unsigned total_databases);
    virtual os_boolean pre_action (const char* database_path);

    // Post-actions
    virtual void post_action (const char** database_paths,
			      unsigned total_databases);
    virtual void post_action (const char* database_path);

  public: // Database Actions
    // Pre-actions
    virtual os_boolean pre_action (os_database& database);
    // Post-actions
    virtual void post_action (os_database& database);

  public: // Database Root Actions
    // Pre-actions
    virtual os_boolean pre_action (os_database_root** roots, 
				   os_int32 n_roots);
    virtual os_boolean pre_action (os_database_root& root);

    // Post-actions
    virtual void post_action (os_database_root** roots, os_int32 n_roots);
    virtual void post_action (os_database_root& root);

  public: // Segment Actions
    // Pre-actions
    virtual os_boolean pre_action (os_segment& segment);
    // Post-actions
    virtual void post_action (os_segment& segment);

  public: //Cluster
     virtual os_boolean pre_action (os_cluster& cluster);
     virtual void post_action (os_cluster& cluster);

  public: // Schema Actions
    // Pre-actions
    virtual os_boolean pre_action (os_schema& schema);
    // Post-actions
    virtual void post_action (os_schema& schema);

  public: // Object Actions
    // Pre-actions
    virtual os_boolean pre_action_object (const os_type& actual_type, 
					  void* object, 
					  os_int32 count);
    virtual os_boolean pre_action_object (const os_type& actual_type, 
					  void* object);

    // Post-actions
    virtual void post_action_object (const os_type& actual_type, 
				     void* object, 
				     os_int32 count);
    virtual void post_action_object (const os_type& actual_type, 
				     void* object);

  public: // Array Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_array_type& actual_array, 
				   void* object);
    virtual os_boolean pre_action (const os_array_type& actual_array);
    virtual os_boolean pre_action 
        (const os_array_type& actual_array,
	 const os_member_variable& member_variable);

    virtual os_boolean pre_action (const os_array_type &actual_array,
				   void *object, void *element,
				   unsigned total_elements, unsigned index);


    // Post-actions
    virtual void post_action (const os_array_type& actual_array, 
			      void* object);
    virtual void post_action (const os_array_type& actual_array);
    virtual void post_action (const os_array_type& actual_array,
			      const os_member_variable& member_variable);

    virtual void post_action (const os_array_type &actual_array,
			      void *object, void *element,
			      unsigned total_elements, unsigned index);

  public: // Class Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_class_type& actual_class, 
				   void* object);
    virtual os_boolean pre_action (const os_class_type& actual_class, 
				   void* object, unsigned total_elements);
    virtual os_boolean pre_action (const os_class_type& actual_class);
    virtual os_boolean pre_action
        (const os_class_type& actual_class,
	 const os_member_variable& member_variable);

    // Post-actions
    virtual void post_action (const os_class_type& actual_class, 
			      void* object);
    virtual void post_action (const os_class_type& actual_class, 
			      void* object, unsigned total_elements);
    virtual void post_action (const os_class_type& actual_class);
    virtual void post_action (const os_class_type& actual_class,
			      const os_member_variable& member_variable);

  public: // Base Actions
    // Pre-actions
    virtual os_boolean pre_action (void* class_object, 
				   const os_base_class& base_class);
    virtual os_boolean pre_action (const os_base_class& base_class);

    // Post-actions
    virtual void post_action (void* class_object, 
			      const os_base_class& base_class);
    virtual void post_action (const os_base_class& base_class);

  public: // Member Variable Actions
    // Pre-actions
    virtual os_boolean pre_action 
        (void* class_object, const os_member_variable& member_variable);
    virtual os_boolean pre_action 
        (const os_member_variable& member_variable);

    // Pre-actions
    virtual void post_action (void* class_object, 
			      const os_member_variable& member_variable);
    virtual void post_action (const os_member_variable& member_variable);


  public: // Member Type Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_member_type& member_type);

    // Pre-actions
    virtual void post_action (const os_member_type& member_type);


  public: // Predef Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_type& actual_type,
				   void* object);
    virtual os_boolean pre_action (const os_type& actual_type, 
				   void* object, unsigned total_elements);
    /*
    The pre_action overloading with os_member_variable is
    called for predefined types which are members, but not
    for arrays.  This is because integral types might be
    bit fields, and the field information is in the os_memeber_variable.
    */
    virtual os_boolean pre_action 
        (const os_type& actual_type, void* class_object,
	 const os_member_variable& member_variable);
    virtual os_boolean pre_action (const os_type& actual_type);
    virtual os_boolean pre_action 
        (const os_type& actual_type, 
	 const os_member_variable& member_variable);

    // Post-actions
    virtual void post_action (const os_type& actual_type, void* object);
    virtual void post_action (const os_type& actual_type, void* object, 
			      unsigned total_elements);
    virtual void post_action (const os_type& actual_type, 
			      void* class_object,
			      const os_member_variable& member_variable);
    virtual void post_action (const os_type& actual_type);
    virtual void post_action (const os_type& actual_type, 
			      const os_member_variable& member_variable);
    virtual os_boolean char_array_action (const os_type& actual_type, 
				    void* object, 
				    unsigned total_elements);
    virtual os_boolean number_array_action (const os_type& actual_type, 
				      void* object, 
				      unsigned total_elements);

  public: // Enum Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_enum_type& actual_type, 
				   void* object);
    virtual os_boolean pre_action (const os_enum_type& actual_type, 
				   void* object, unsigned total_elements);
    /*
    The pre_action overloading with os_member_variable is
    called for enum types which are members, but not
    for arrays.  This is because enums might be
    bit fields, and the field information is in the os_memeber_variable.
    */
    virtual os_boolean pre_action 
        (const os_enum_type& actual_type, void* class_object,
	 const os_member_variable& member_variable);
    virtual os_boolean pre_action (const os_enum_type& actual_type);
    virtual os_boolean pre_action 
        (const os_enum_type& actual_type,
	 const os_member_variable& member_variable);

    // Post-actions
    virtual void post_action (const os_enum_type& actual_type, 
			      void* object);
    virtual void post_action (const os_enum_type& actual_type, 
			      void* object, unsigned total_elements);
    virtual void post_action (const os_enum_type& actual_type, 
			      void* class_object,
			      const os_member_variable& member_variable);
    virtual void post_action (const os_enum_type& actual_type);
    virtual void post_action (const os_enum_type& actual_type,
			      const os_member_variable& member_variable);

  public: // Pointer Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_pointer_type& actual_pointer, 
				   void* object);
    virtual os_boolean pre_action (const os_pointer_type& actual_pointer, 
				   void* object, unsigned total_elements);
    virtual os_boolean pre_action (const os_pointer_type& actual_pointer);
    virtual os_boolean pre_action 
        (const os_pointer_type& actual_pointer,
	 const os_member_variable& member_variable);

    // Post-actions
    virtual void post_action (const os_pointer_type& actual_pointer, 
			      void* object);
    virtual void post_action (const os_pointer_type& actual_pointer, 
			      void* object, unsigned total_elements);
    virtual void post_action (const os_pointer_type& actual_pointer);
    virtual void post_action (const os_pointer_type& actual_pointer,
			      const os_member_variable& member_variable);

  public: // Function Actions
    // Pre-actions
    virtual os_boolean pre_action (const os_function_type& actual_type);
    // Post-actions
    virtual void post_action (const os_function_type& actual_type);

  public: // Indirect Actions
    // Pre-actions
    virtual os_boolean pre_action 
        (const os_indirect_type& actual_indirect_type, void* object);
    virtual os_boolean pre_action
        (const os_indirect_type& actual_indirect_type, void* object,
	 unsigned total_elements);
    virtual os_boolean pre_action
        (const os_indirect_type& actual_indirect_type);
    virtual os_boolean pre_action
        (const os_indirect_type& actual_indirect_type,
	 const os_member_variable& member_variable);

    // Post-actions
    virtual void post_action (const os_indirect_type& actual_indirect_type,
			      void* object);
    virtual void post_action (const os_indirect_type& actual_indirect_type,
			      void* object, unsigned total_elements);
    virtual void post_action (const os_indirect_type& actual_indirect_type);
    virtual void post_action (const os_indirect_type& actual_indirect_type,
			      const os_member_variable& member_variable);

  protected: // Modifiers
    virtual void set_traverser (os_Traverser&);

  private: // Friends
    friend class os_Traverser;

  };


#endif /* WRP_ACTION_HH */
