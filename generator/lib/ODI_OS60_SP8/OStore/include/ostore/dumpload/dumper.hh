/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef DUMPER_HH
#define DUMPER_HH

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

#include <assert.h>

#include <ostore/ostore.hh>
#include <ostore/coll.hh>

#include <ostore/dumpload/dump_cls_act.hh>
#include <ostore/dumpload/dump_act.hh>
#include <ostore/dumpload/dmp_ref.hh>
#include <ostore/dumpload/dumper_stream.hh>



//-- Forward Declarations ----------------------------------------------

class os_Planning_action;


/***********************************************************************
  class os_Dumper
***********************************************************************/

class os_Dumper {

  public: // Subtypes
    enum os_Dumper_error { unknown };

  public: // Construction
    os_Dumper (
	       const char* given_work_database_path,
	       const char* database_table_path,
	       os_Traverser& traverser, os_Dumper_actions& dumper_actions,
	       const char* given_dump_pathname = 0);
  virtual ~os_Dumper ();
  
  public: // Static Accessors
    static os_Dumper_stream& get_default_stream ();
    static os_Planning_action* find_planner (const char* type_string);
    static void set_current_dumper(os_Dumper*);
    static os_Dumper* get_current_dumper(void);

  public: // Predicates
    os_boolean is_preexisting_work_database () const;
    os_boolean is_copying_schema () const;
    os_boolean is_dumping_schema () const;

  public: // Accessors
    os_Traverser& get_traverser();
    const char* get_work_database_path () const;
    const char* get_database_table_path () const;
    os_database& get_work_database () const;
    os_fetch_policy get_fetch_policy () const;
    os_unsigned_int32 get_fetched_pages () const;
    char* get_dump_pathname (const char* database_path) const;
    char* get_schema_dump_pathname (const char* database_path) const;
    const char* get_copied_schema_path () const;
    const char* get_dumped_schema_path () const;
    os_Dumper_stream* get_schema_file () const;

  private:
    char* get_suffixed_pathname (const char* database_path, char * suffix) const;

  public: // Modifiers
    void set_fetch_policy (os_fetch_policy policy);
    void set_fetched_pages (os_unsigned_int32 number_pages);
    void set_is_copying_schema (os_boolean);
    void set_is_dumping_schema (os_boolean);
    void set_copied_schema_path (const char*);
    void set_dumped_schema_path (const char*);
    void set_schema_file (os_Dumper_stream& schema_file);

  public: // Actions
    void dump (const char** database_paths, unsigned total_databases);
    void dump_schema (const char** database_paths, unsigned total_databases);
    void dump (const char* class_name, void* object);

  protected: // Embedded data
    os_Traverser* traverser;
    os_Dumper_actions* dumper_actions;
    const char* work_database_path; 
    const char* database_table_path;
    os_database* work_database;
    os_boolean preexisting_work_database;
    os_fetch_policy fetch_policy;
    os_unsigned_int32 fetched_pages;
    const char* dump_pathname;
    os_boolean copying_schema;
    os_boolean dumping_schema;
    const char* copied_schema_path; 
    const char* dumped_schema_path; 
    os_Dumper_stream* schema_file;

  protected: // Modifiers
    void prepare_resumption (unsigned total_databases);
    void prepare_commencement (unsigned total_databases);
    void cleanup ();
    
  };


/***********************************************************************
  os_Dumper registration types
***********************************************************************/

class os_Dumper_specialization;

template <class Key, class Value> 
class os_Registration_entry;

template <class Key, class Value> 
class os_Registration_block;

template <class Key, class Value> 
class os_Registrations;


typedef os_Registration_entry<os_Dumper_specialization*, os_Dumper>
    os_Dumper_registration_entry;
typedef os_Registration_block<os_Dumper_specialization*, os_Dumper>
    os_Dumper_registration_block;
typedef os_Registrations<os_Dumper_specialization*, os_Dumper>
    os_Dumper_registrations;


/***********************************************************************
  class os_Dumper_specialization
***********************************************************************/

class os_Dumper_specialization : public os_Class_specialization {

  public: // Accessors

    /* Return the os_Dumper associated with this os_Dumper_specialization. */
    os_Dumper& get_dumper () const;

    /* Returns true (non-zero) when a loader should be emitted for
       this specialization's corresponding class. Otherwise, false
       (zero) is returned and a loader is not emitted. By default,
       this function returns false as it expected that a class
       requiring specialization will have its loader defined and
       implemented by hand. */
    virtual os_boolean should_emit_loader
        (const os_class_type& class_type) const;

    /* Returns true (non-zero) when the type being specialized should
       have its default constructor used with the emitted code of a
       loader's create() function. Otherwise, false (zero) is return
       when the special loader constructor (<Type>(<Type>_data&))
       should be used by the emitter. */
    virtual os_boolean should_use_default_constructor
        (const os_class_type& class_type) const = 0;

    /* By default, get_specialization_name() returns null. This tells
       the emitter to use the name of the class associated with this
       os_Dumper_specialization. If needed, a Dumper_specialization can
       override this function and return some special name. This name
       will be used for the <Type> part in the emitting of names of
       the form: <Type>_loader, <Type>_info, and <Type>_data. It is
       the caller's responsibility to delete the resulting string. */
    virtual char* get_specialization_name
        (const os_class_type& class_type) const;

    /* By default, get_marking_string() returns null. This tells the
       emitter to use the default marking string for marking a type
       for inclusion in an ObjectStore application schema. The default
       marking string is "OS_MARK_SCHEMA_TYPESPEC(Type)" where Type is
       the type being specialized. If necessary, a specialization can
       return an alternate marking string.  For example, instantiated
       types of os_Dictionary use "OS_MARK_DICTIONARY(Key,Value)"
       where Key is the key type and Value is the value type of the
       instantiated dictionary. It is the caller's responsibility to
       delete the resulting string. */
    virtual char* get_marking_string (const os_class_type& class_type) const;

    /* By default, should_emit_instantiation() returns false (zero).
       If instantiation code needs to be emitted for a type being
       specialized, override this function to return true
       (non-zero). */
    virtual os_boolean should_emit_instantiation
        (const os_class_type& class_type) const;

    /* By default, get_instantiation_string() returns null. This tells
       the emitter to emit the default instantiation for the current
       architecture. If some special instantiation code is required,
       an override of this function can provide it. This function will
       only be invoked if should_emit_instantiation() has been
       overrided to return true. It is the caller's responsibility to
       delete the resulting string. */
    virtual char* get_instantiation_string
        (const os_class_type& class_type) const;

    /* This predicate anwsers the question as to whether the class
       associated with this specialization is meaningful to the dump
       and load. By default, is_meaningful() returns true (non-zero).
       In every case where is_meaning() returns false (zero), it will
       will be assumed that the associated class has a default
       constructor that will make an instance of the class valid
       without any additional information or action. An example, of an
       unmeaningful class is a class used for alignment, padding, or
       introducing virtual behavior for the sake of neutralization
       (see os_virtual_behavior). */
    virtual os_boolean is_meaningful
        (const os_class_type& class_type) const;

    /* Return the os_Dumper_stream on to which to dump. */
    os_Dumper_stream& get_stream () const;

  protected: // Embedded data
    os_Dumper* dumper;

  public: // Modifiers
    void set_dumper (os_Dumper&);

  private: // Friends
  //    friend void os_Dumper_registration_entry::set_context (os_Dumper& dumper);

  };


/***********************************************************************
  os_Nop_dumper
***********************************************************************/

class os_Nop_dumper_specialization : public os_Dumper_specialization {

public: // Accessors
   os_Action::Action_kind get_kind () const;
   os_boolean should_use_default_constructor(const os_class_type&) const;
   char* get_specialization_name (const os_class_type&) const;
   char* get_marking_string (const os_class_type&) const;
   os_boolean is_meaningful (const os_class_type&) const;
   };


/***********************************************************************
  os_Nop_dumper
***********************************************************************/

class os_Nop_dumper : public os_Nop_dumper_specialization {

  public: // Actions
    virtual void operator () (const os_class_type& actual_class, 
                              void* object);
    virtual void operator () (const os_class_type& actual_class, 
                              void* object, unsigned total_elements);
    virtual void operator () (const os_class_type& actual_class);
    virtual void operator () (const os_class_type& actual_class,
                              const os_member_variable& member_variable);

  };


#endif /* DUMPER_HH */
