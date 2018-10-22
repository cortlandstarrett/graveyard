/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DUMP_ACTION_HH
#define DUMP_ACTION_HH

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
#include <ostore/coll.hh>
#include <ostore/mop.hh>

#include <ostore/traverse/action.hh>
#include <ostore/traverse/seg_act.hh>
#include <ostore/traverse/wrp_act.hh>
//#include <ostore/traverse/register.hh>

#include <ostore/dumpload/dumper_stream.hh>


//-- Forward Declarations ----------------------------------------------

class os_Dumper;


/***********************************************************************
  class os_Dumper_actions
***********************************************************************/

class os_Dumper_actions : public os_Wrapper_actions {

  public: // Construction
    os_Dumper_actions
       (os_boolean is_dumping, os_boolean is_psuedo, os_boolean is_java);
    virtual ~os_Dumper_actions ();

  public: // Actions

    // os_Traverser Actions
    virtual os_boolean pre_action (const char** database_paths,
				   unsigned total_databases);
    virtual void post_action (const char** database_paths,
			      unsigned total_databases);
    virtual os_boolean pre_action (const char* database_path);

    // Database Actions
    virtual os_boolean pre_action (os_database& database);
    virtual void post_action (os_database& database);
    
    // Database Root Actions
    virtual os_boolean pre_action (os_database_root** roots,
				   os_int32 n_roots);

    // Schema Actions
    virtual os_boolean pre_action (os_schema& schema);
    virtual void post_action (os_schema& schema);

    // Segment Actions
    virtual os_boolean pre_action (os_segment& segment);
    virtual void post_action (os_segment& segment);

    // Object Actions
    virtual os_boolean pre_action_object (const os_type& actual_type, 
					  void* object);
    virtual void post_action_object (const os_type& actual_type,
 				     void* object);

    // Class Actions
    virtual os_boolean pre_action (const os_class_type& actual_class, 
				   void* object);
    virtual void post_action (const os_class_type& actual_class, 
			      void* object);

    // Predef Actions
    virtual os_boolean pre_action (const os_type& actual_type, 
				   void* object);
    virtual os_boolean pre_action (const os_type& actual_type, 
				   void* object, unsigned total_elements);
    virtual os_boolean pre_action
        (const os_type& actual_type, void* class_object,
	 const os_member_variable& member_variable);
    virtual void post_action (const os_type& actual_type, void* object);
    virtual void post_action (const os_type& actual_type, 
			      void* class_object,
			      const os_member_variable& member_variable);
    virtual os_boolean char_array_action (const os_type& actual_type, 
				    void* object, 
				    unsigned total_elements);
    virtual os_boolean number_array_action (const os_type& actual_type, 
				      void* object, 
				      unsigned total_elements);

    // Enum Actions
    virtual os_boolean pre_action
        (const os_enum_type& actual_type, void* class_object);
    virtual os_boolean pre_action (const os_enum_type& actual_type, 
				   void* object, unsigned total_elements);
    virtual os_boolean pre_action
        (const os_enum_type& actual_type, void* class_object,
	 const os_member_variable& member_variable);

    // Pointer Actions
    virtual os_boolean pre_action (const os_pointer_type& actual_pointer, 
				   void* object);
    virtual os_boolean pre_action (const os_pointer_type& actual_pointer, 
				   void* object, unsigned total_elements);

  public: // Accessors
    const os_Dumper& get_dumper () const;
    os_Dumper_stream& get_stream () const;

  protected: // Embedded data
    os_Dumper* dumper;
    /* TBD -- these flags really should be bits in an object... */
    os_boolean dumping; /* Flag showing whether to dump database or not. */
    os_boolean pseudo;  /* Flag showing whether to emit pseudo declarations
                           from source database schema. */
    os_boolean java;    /* Flag showing whether to dump in java style. */
    os_database* pending_database; /* Database for which there is a
				      pending database action. */

  protected: // Accessors
    virtual os_boolean is_pending_database_pre_action () const;

  protected: // Modifiers
    void set_dumper (os_Dumper&);

  protected: // Actions
    virtual void database_pre_action ();

  private: // Friends
    friend class os_Traverser;
    friend class os_Dumper;
    friend class os_Dumper_segment_action;

// shut Solaris up
   virtual void post_action (const char* a)
      {os_Wrapper_actions::post_action(a);}
   virtual void post_action (os_database_root** a,os_int32 b)
      {os_Wrapper_actions::post_action(a,b);}
   virtual os_boolean pre_action (const os_indirect_type& a,const os_member_variable& b)
      {return os_Wrapper_actions::pre_action(a,b);}
   virtual void post_action (const os_indirect_type& a,const os_member_variable& b)
      {os_Wrapper_actions::post_action(a,b);}
   virtual os_boolean pre_action (const os_indirect_type& a)
      {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_indirect_type& a,void* b)
      {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_indirect_type& a,void* b,unsigned c)
      {return os_Wrapper_actions::pre_action(a,b,c);}
   virtual os_boolean pre_action (const os_function_type& a)
       {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_pointer_type& a, const os_member_variable& b)
       {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_pointer_type& a)
       {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_enum_type& a, const os_member_variable& b)
       {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_enum_type& a)
       {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_type& a, const os_member_variable& b)
       {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_type& a)
       {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_member_type& a)
       {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_member_variable& a)
       {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (void* a, const os_member_variable& b)
       {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_base_class& a)
       {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (void* a, const os_base_class& b)
       {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_class_type& a, const os_member_variable& b)
       {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_class_type& a)
       {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_class_type& a, void* b, unsigned c)
       {return os_Wrapper_actions::pre_action(a,b,c);}
   virtual os_boolean pre_action (const os_array_type& a, const os_member_variable& b)
       {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_array_type& a)
       {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_array_type& a, void* b)
       {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (os_database_root& a)
       {return os_Wrapper_actions::pre_action(a);}
   virtual void post_action (const os_indirect_type& a)
       {os_Wrapper_actions::post_action(a);}
   virtual void post_action (const os_indirect_type& a, void* b, unsigned c)
       {os_Wrapper_actions::post_action(a,b,c);}
   virtual void post_action (const os_indirect_type& a, void* b)
       {os_Wrapper_actions::post_action(a,b);}
   virtual void post_action (const os_function_type& a)
       {os_Wrapper_actions::post_action(a);}
   virtual void post_action (const os_pointer_type& a, const os_member_variable& b)
       {os_Wrapper_actions::post_action(a,b);}
   virtual void post_action (const os_pointer_type& a)
       {os_Wrapper_actions::post_action(a);}
   virtual void post_action (const os_pointer_type& a, void* b, unsigned c)
       {os_Wrapper_actions::post_action(a,b,c);}
   virtual void post_action (const os_pointer_type& a, void* b)
       {os_Wrapper_actions::post_action(a,b);}
   virtual void post_action (const os_enum_type& a, const os_member_variable& b)
       {os_Wrapper_actions::post_action(a,b);}
   virtual void post_action (const os_enum_type& a)
       {os_Wrapper_actions::post_action(a);}
   virtual void post_action (const os_enum_type& a, void* b, const os_member_variable& c)
       {os_Wrapper_actions::post_action(a,b,c);}
   virtual void post_action (const os_enum_type& a, void* b, unsigned c)
       {os_Wrapper_actions::post_action(a,b,c);}
   virtual void post_action (const os_enum_type& a, void* b)
       {os_Wrapper_actions::post_action(a,b);}
   virtual void post_action (const os_type& a, const os_member_variable& b)
       {os_Wrapper_actions::post_action(a,b);}
   virtual void post_action (const os_type& a)
       {os_Wrapper_actions::post_action(a);}
   virtual void post_action (const os_type& a, void* b, unsigned c)
       {os_Wrapper_actions::post_action(a,b,c);}
   virtual void post_action (const os_member_type& a)
       {os_Wrapper_actions::post_action(a);}
   virtual void post_action (const os_member_variable& a)
       {os_Wrapper_actions::post_action(a);}
   virtual void post_action (void* a, const os_member_variable& b)
       {os_Wrapper_actions::post_action(a,b);}
   virtual void post_action (const os_base_class& a)
       {os_Wrapper_actions::post_action(a);}
   virtual void post_action (void* a, const os_base_class& b)
       {os_Wrapper_actions::post_action(a,b);}
   virtual void post_action (const os_class_type& a, const os_member_variable& b)
       {os_Wrapper_actions::post_action(a,b);}
   virtual void post_action (const os_class_type& a)
       {os_Wrapper_actions::post_action(a);}
   virtual void post_action (const os_class_type& a, void* b, unsigned c)
       {os_Wrapper_actions::post_action(a,b,c);}
   virtual void post_action (const os_array_type& a, const os_member_variable& b)
       {os_Wrapper_actions::post_action(a,b);}
   virtual void post_action (const os_array_type& a)
       {os_Wrapper_actions::post_action(a);}
   virtual void post_action (const os_array_type& a, void* b)
       {os_Wrapper_actions::post_action(a,b);}
   virtual void post_action (os_database_root& a)
       {os_Wrapper_actions::post_action(a);}
   virtual void post_action (const os_type& a, void* b, int c)
       {os_Wrapper_actions::post_action_object(a,b,c);}
   virtual os_boolean pre_action_object (const os_type& a, void* b, int c)
       {return os_Wrapper_actions::pre_action_object(a,b,c);}
   virtual void post_action_object (const os_type& a, void* b, int c)
       {os_Wrapper_actions::post_action_object(a,b,c);}
  };


/***********************************************************************
  class os_Dumper_segment_action
***********************************************************************/

class os_Dumper_segment_action : public os_Segment_action {

  public: // Construction
    os_Dumper_segment_action (os_Object_action* object_action = 0);
    os_Dumper_segment_action (const os_Dumper_segment_action& segment_action);
    virtual ~os_Dumper_segment_action ();

  public: // Actions
    virtual void operator () (os_segment& segment);

  protected: // Actions
    virtual void segment_action (os_segment& segment);
    virtual void segment_planning_action (os_segment& segment);
    virtual void segment_dumping_action (os_segment& segment);

  };


#endif /* DUMP_ACTION_HH */
