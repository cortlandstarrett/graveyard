/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef COL_PLAN_HH
#define COL_PLAN_HH

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
#include <ostore/traverse/wrp_act.hh>
#include <ostore/traverse/traverse.hh>

//-- forward declarations ---------------------------------------------
class os_Dumper;

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Class: os_Ignore_actions 
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
  
class os_Ignore_actions : public os_Wrapper_actions {

public: // Constructor
	os_Ignore_actions(os_Traverser& traverser);

public: // Pointer Actions
	// Pre-actions
   virtual os_boolean pre_action (const os_pointer_type& actual_pointer, 
	    void* object);

	virtual os_boolean pre_action (const os_pointer_type& actual_pointer, 
	    void* object, unsigned total_elements);

   virtual os_boolean pre_action (void* a, const os_member_variable& b);
	// Registration of ignoreable objects
	static void ignore (os_Dumper& dumper, const os_class_type & class_type, void * object);
// Shut up Solaris
   virtual os_boolean pre_action (const char** a, unsigned b)
      {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_indirect_type& a, const os_member_variable& b)
      {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_indirect_type& a)
      {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_indirect_type& a, void* b, unsigned c)
      {return os_Wrapper_actions::pre_action(a,b,c);}
   virtual os_boolean pre_action (const os_indirect_type& a, void* b)
      {return os_Wrapper_actions::pre_action(a,b);}
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
   virtual os_boolean pre_action (const os_enum_type& a, void* b, const os_member_variable& c)
      {return os_Wrapper_actions::pre_action(a,b,c);}
   virtual os_boolean pre_action (const os_enum_type& a, void* b, unsigned c)
      {return os_Wrapper_actions::pre_action(a,b,c);}
   virtual os_boolean pre_action (const os_enum_type& a, void* b)
      {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_type& a, const os_member_variable& b)
      {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_type& a)
      {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_type& a, void* b, const os_member_variable& c)
      {return os_Wrapper_actions::pre_action(a,b,c);}
   virtual os_boolean pre_action (const os_type& a, void* b, unsigned c)
      {return os_Wrapper_actions::pre_action(a,b,c);}
   virtual os_boolean pre_action (const os_type& a, void* b)
      {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_member_type& a)
      {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_member_variable& a)
      {return os_Wrapper_actions::pre_action(a);}
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
   virtual os_boolean pre_action (const os_class_type& a, void* b)
      {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_array_type& a, const os_member_variable& b)
      {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (const os_array_type& a)
      {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const os_array_type& a, void* b)
      {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (os_schema& a)
      {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (os_segment& a)
      {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (os_database_root& a)
      {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (os_database_root** a, int b)
      {return os_Wrapper_actions::pre_action(a,b);}
   virtual os_boolean pre_action (os_database& a)
      {return os_Wrapper_actions::pre_action(a);}
   virtual os_boolean pre_action (const char* a)
      {return os_Wrapper_actions::pre_action(a);}

};

#endif 
