/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef BOOTSPC_HH
#define BOOTSPC_HH

class os_Meaningless_class_specialization : public os_Dumper_specialization {

  public: // Accessors
    virtual os_boolean should_emit_loader
        (const os_class_type& class_type) const
       {return 0;}
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const;
    virtual os_boolean should_emit_instantiation
        (const os_class_type& class_type) const
       {return 0;}
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;
    virtual char* get_marking_string
        (const os_class_type& class_type) const;
    virtual os_boolean is_meaningful
        (const os_class_type& class_type) const;
  };

/***********************************************************************
  class os_Meaningless_class_dumper
***********************************************************************/

class os_Meaningless_class_dumper : public os_Meaningless_class_specialization {

  public: // Actions
    virtual void operator () (const os_class_type& actual_class, 
			      void* object);
    virtual void operator () (const os_class_type& actual_class, 
			      void* object, unsigned total_elements);
    virtual void operator () (const os_class_type& actual_class);
    virtual void operator () (const os_class_type& actual_class,
			      const os_member_variable& member_variable);
  };

#endif
