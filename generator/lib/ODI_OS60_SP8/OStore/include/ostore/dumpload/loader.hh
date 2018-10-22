/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef LOADER_HH
#define LOADER_HH

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

/* TBD: revisit all the static char buffers and replace with
        pointers to one buffer (this should work). When threading
        enabling is done, loaders will need loader nodes on the
        stack (like traverser action nodes) and the node associated
        with the introducing of threading will need to have a
        buffer. The other possiblity is to associated the buffer
        with an instance of os_Loader_stream. Then all the word
        pointers can refer to it. -rick@odi.com */


//-- Include files -----------------------------------------------------

#include <iostream.h>

#include <ostore/traverse/traverse.hh>
#include <ostore/dumpload/db_table.hh>
#include <ostore/dumpload/loader_stream.hh>
#include <ostore/dumpload/value.hh>

#if (_OS_MicrosoftCC >= 1200)
#pragma warning(disable: 4786)
#endif
//-- Forward Declarations ----------------------------------------------

class os_Loader_stream;
class os_Loader_header;

class os_Loader_action;
class os_Databases_loader;
class os_Database_entry_loader;
class os_Database_loader;
class os_Roots_loader;
class os_Root_entry_loader;
class os_Segment_loader;
class os_Cluster_loader;
class os_Object_loader;
class os_Type_loader;
class os_Nop_loader;
class os_Fixup_loader;
class os_Type_fixup_loader;
class os_End_block_loader;
class os_Finalization_loader;
class os_Schema_loader;
class os_Schema_file_loader;

class os_Loader_info;
class os_Loader_initial_info;
class os_Loader_translated_info;
class os_Databases_info;
class os_Database_entry_info;
class os_Database_info;
class os_Roots_info;
class os_Root_entry_info;
class os_Segment_info;
class os_Cluster_info;
class os_Object_info;
class os_Type_info;
class os_Fixup_info;
class os_Type_fixup_info;
class os_End_block_info;
class os_Finalization_info;
class os_Schema_info;
class os_Schema_file_info;


/***********************************************************************
  class os_Loader
***********************************************************************/

class os_Loader {

  public: // Subtypes
    enum os_Loader_error { 
        unknown, unimplemented, unexpected_input, uninitialized,
        bad_action_stack, bad_cast
      };
    enum os_Loader_state { none };
    typedef os_boolean (*Predicate) (os_Loader_action*);

  public: // Construction
    os_Loader (const char* work_database_path,
          const char* database_table_path,
               os_Databases_loader& databases_loader,
               os_Database_entry_loader& database_entry_loader,
               os_Database_loader& database_loader,
               os_Roots_loader& roots_loader,
               os_Root_entry_loader& root_entry_loader,
               os_Segment_loader& segment_loader,
               os_Cluster_loader& cluster_loader,
               os_Object_loader& object_loader,
               os_Fixup_loader& fixup_loader,
               os_End_block_loader& end_block_loader,
               os_Finalization_loader& finalization_loader,
               os_Schema_loader& schema_loader,
               os_Schema_file_loader& schema_file_loader,
               os_unsigned_int32 given_schema_options);
    ~os_Loader ();

  public: // Predicates
    os_boolean is_preexisting_work_database () const;
    os_boolean is_copying_schema () const;
    os_boolean is_loading_schema () const;
    os_boolean is_java () const;

  public: // Accessors
    os_Loader_header& get_header () const;
    const char* get_work_database_path () const;
    os_database& get_work_database () const;
    os_Databases_loader& get_databases_loader () const;
    os_Database_entry_loader& get_database_entry_loader () const;
    os_Database_loader& get_database_loader () const;
    os_Roots_loader& get_roots_loader () const;
    os_Root_entry_loader& get_root_entry_loader () const;
    os_Segment_loader& get_segment_loader () const;
    os_Cluster_loader& get_cluster_loader () const;
    os_Object_loader& get_object_loader () const;
    os_Fixup_loader& get_fixup_loader () const;
    os_End_block_loader& get_end_block_loader () const;
    os_Finalization_loader& get_finalization_loader () const;
    os_Schema_loader& get_schema_loader () const;
    os_Schema_file_loader& get_schema_file_loader () const;
    os_Loader_info* get_top_info () const;
    os_Loader_info* get_outermost_info () const;
    // TBD: Consider whether need class and typedef table -rick@odi.com
    os_Type_loader* find_loader (const char* type_string) const;
    os_Type_fixup_loader* find_fixup_loader (const char* type_string) const;
    os_fetch_policy get_fetch_policy () const;
    os_unsigned_int32 get_fetched_pages () const;
    const char* get_collected_schema_path () const;
    os_database* get_collected_schema_database () const;
    const char* get_dumped_schema_path () const;
    os_database* get_schema_file () const;
    const char* get_dump_filename() const;
    os_unsigned_int32 get_schema_options() {return schema_options;}

  public: // Modifiers
    void set_fetch_policy (os_fetch_policy policy);
    void set_fetched_pages (os_unsigned_int32 number_pages);
    void set_is_copying_schema (os_boolean);
    void set_is_loading_schema (os_boolean);
    void set_is_java (os_boolean);
    void set_collected_schema_path (const char*);
    void set_collected_schema_database (os_database& collected_schema_database);

  public: // Actions
    void load (const char** files, unsigned total_files);
    void load (const char* file, os_Loader_info&);
    os_Loader_action* load (os_Loader_stream&, os_Loader_info&,
                            Predicate is_end, os_Loader_action* action = 0);
    virtual os_Loader_action& translate (const char* word,
                                         os_Loader_translated_info& info);
    void collect_schema(os_schema& schema);

  private: // aux
    char* get_suffixed_pathname (const char* database_path, char * suffix) const;
  public: // Debugging
    static int is_debugging(os_unsigned_int32 level = 1);
    static void set_is_debugging(os_unsigned_int32 level);


  protected: // Embedded data
    char* word;
    const char* work_database_path; 
    const char* database_table_path; 
    os_database* work_database;
    os_Reference_transient<os_Loader_header> header;
    os_Databases_loader* databases_loader;
    os_Database_entry_loader* database_entry_loader;
    os_Database_loader* database_loader;
    os_Roots_loader* roots_loader;
    os_Root_entry_loader* root_entry_loader;
    os_Segment_loader* segment_loader;
    os_Cluster_loader* cluster_loader;
    os_Object_loader* object_loader;
    os_Fixup_loader* fixup_loader;
    os_End_block_loader* end_block_loader;
    os_Finalization_loader* finalization_loader;
    os_Schema_loader* schema_loader;
    os_Schema_file_loader* schema_file_loader;
    os_Loader_info* top_info;
    os_Loader_info* outermost_info;
    os_boolean preexisting_work_database;
    os_fetch_policy fetch_policy;
    os_unsigned_int32 fetched_pages;
    os_boolean copying_schema;
    os_boolean loading_schema;
    os_boolean java;
    const char * dump_filename;
    const char* collected_schema_path; 
    os_database* collected_schema_database;
    os_unsigned_int32 schema_options;
    
  protected: // Modifiers
    void prepare_resumption ();
    void prepare_commencement ();
    void finalize_load (os_Loader_initial_info& info);
    void cleanup ();

  protected: // Modifiers
    void set_top_info (os_Loader_info*);
    void set_outermost_info (os_Loader_info*);

  private: // Friends
    friend class os_Loader_action;
    friend class os_Loader_info;
    friend class os_Database_loader;
    friend class os_Segment_loader;
    friend class os_Cluster_loader;
    friend class os_Schema_loader;

  };


/***********************************************************************
  class os_Loader_header
***********************************************************************/

class os_Loader_header {
                                
  public: // Construction
    os_Loader_header ();
    ~os_Loader_header ();
                                
  public: // Accessors
    os_Database_table& get_database_table () const;
                                
  public: // Modifiers
                                
  public: // ObjectStore
    static os_typespec* get_os_typespec ();

  protected: // Embedded data
    os_Database_table* database_table;
                                
  protected: // Modifiers
    void set_database_table (os_Database_table&);
                                
  private: // Friends
    friend class os_Databases_loader;

  };
                                

/***********************************************************************
  class os_Loader_action
***********************************************************************/

class os_Loader_action {

  public: // Subtypes
    enum Kind { no_kind, loader_kind, loader_initial_kind, 
                loader_translated_kind,
                databases_kind, database_entry_kind, 
                database_kind, roots_kind, root_entry_kind, segment_kind, 
                cluster_kind, object_kind, type_kind, end_block_kind,
                nop_kind, fixup_kind, type_fixup_kind, finalization_kind,
                schema_kind, schema_file_kind };

  public: // Construction
    os_Loader_action ();
    virtual ~os_Loader_action ();

  public: // Static Accessors
    static os_boolean is_equal (const char* string1, const char* string2);
// is_match is dead.  Make sure it remains dead, damnit.  jlw@odi.com
//    static os_boolean is_match (const char* string, os_Input_values&);

  public: // Static Modifiers
    void set (unsigned& storage, const char* format, const char* word);

  public: // Accessors
    os_Loader& get_loader () const;
    virtual Kind get_kind () const = 0;
    virtual os_boolean is_handling_transactions (os_Loader_info* = 0) const;

  public: // Actions
    virtual os_Loader_action* operator () (os_Loader_stream& stream,
                                           os_Loader_info& info) = 0;

  public: // Coercions
    operator const os_Databases_loader& () const;
    operator const os_Database_entry_loader& () const;
    operator const os_Database_loader& () const;
    operator const os_Roots_loader& () const;
    operator const os_Root_entry_loader& () const;
    operator const os_Segment_loader& () const;
    operator const os_Cluster_loader& () const;
    operator const os_Object_loader& () const;
    operator const os_Type_loader& () const;
    operator const os_Fixup_loader& () const;
    operator const os_Type_fixup_loader& () const;
    operator const os_Nop_loader& () const;
    operator const os_End_block_loader& () const;
    operator const os_Finalization_loader& () const;
    operator const os_Schema_loader& () const;
    operator const os_Schema_file_loader& () const;
    operator os_Databases_loader& ();
    operator os_Database_entry_loader& ();
    operator os_Database_loader& ();
    operator os_Roots_loader& ();
    operator os_Root_entry_loader& ();
    operator os_Segment_loader& ();
    operator os_Cluster_loader& ();
    operator os_Object_loader& ();
    operator os_Type_loader& ();
    operator os_Fixup_loader& ();
    operator os_Type_fixup_loader& ();
    operator os_Nop_loader& ();
    operator os_End_block_loader& ();
    operator os_Finalization_loader& ();
    operator os_Schema_loader& ();
    operator os_Schema_file_loader& ();
                                
  protected: // Embedded data
    os_Loader* loader;
    char* word; // TBD: this should refer to one buffer for all inputs.

  protected: // Modifiers
    void set_loader (os_Loader&);
                                
  protected: // Actions
    virtual os_Loader_action* load (os_Loader_stream& stream,
                                    os_Loader_info&) = 0;
    virtual void create (os_Loader_info&) = 0;

  private: // Friends
    friend class os_Loader;

  };


/***********************************************************************
  class os_Loader_info
***********************************************************************/

class os_Loader_info {

  public: // Construction
    os_Loader_info ();
    os_Loader_info (os_Loader&);
    os_Loader_info (os_Loader&, os_Loader_stream&, os_Loader_info&);
    os_Loader_info (os_Loader_action&, os_Loader_stream&);
    os_Loader_info (os_Loader_action&, os_Loader_stream&, os_Loader_info&);
    os_Loader_info (const os_Loader_info&);
    virtual ~os_Loader_info ();

  public: // Coercions
    operator const os_Loader_initial_info& () const;
    operator const os_Loader_translated_info& () const;
    operator const os_Databases_info& () const;
    operator const os_Database_entry_info& () const;
    operator const os_Database_info& () const;
    operator const os_Roots_info& () const;
    operator const os_Root_entry_info& () const;
    operator const os_Segment_info& () const;
    operator const os_Cluster_info& () const;
    operator const os_Object_info& () const;
    operator const os_Type_info& () const;
    operator const os_Fixup_info& () const;
    operator const os_Type_fixup_info& () const;
    operator const os_End_block_info& () const;
    operator const os_Finalization_info& () const;
    operator const os_Schema_info& () const;
    operator const os_Schema_file_info& () const;
    operator os_Loader_initial_info& ();
    operator os_Loader_translated_info& ();
    operator os_Databases_info& ();
    operator os_Database_entry_info& ();
    operator os_Database_info& ();
    operator os_Roots_info& ();
    operator os_Root_entry_info& ();
    operator os_Segment_info& ();
    operator os_Cluster_info& ();
    operator os_Object_info& ();
    operator os_Type_info& ();
    operator os_Fixup_info& ();
    operator os_Type_fixup_info& ();
    operator os_End_block_info& ();
    operator os_Finalization_info& ();
    operator os_Schema_info& ();
    operator os_Schema_file_info& ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const = 0;
    os_Loader_info* get_outermost_info () const;
    os_Loader_info* get_previous_info () const;
    os_Loader_info* get_next_info () const;
    os_boolean has_pending_info () const;
    os_Loader_info* get_pending_info () const;
    os_Loader_action& get_loader_action () const;
    os_Loader& get_loader () const;

  protected: // Embedded data
    os_Loader_info* outermost_info;
    os_Loader_info* previous_info;
    os_Loader_info* next_info;
    os_Loader_info* pending_info;
    os_Loader* loader;
    os_Loader_action* loader_action;
    os_Loader_stream* loader_stream;
    const char* previous_string_buffer;

  protected: // Modifiers
    void push (os_Loader_info*);
    os_Loader_info* pop ();
    os_Loader_info* top () const;
    void set_pending_info (os_Loader_info*);

  private: // Friends
    friend class os_End_block_loader;

  };


/***********************************************************************
  class os_Loader_initial_info
***********************************************************************/

/* TBD: Some os_Loader state will moved here so that multi-threaded loads
        can be accommodated. Each thread will have its own stack of
        os_Loader_info. What follows is the class used for the initial
        os_Loader_info. --rick@odi.com */

class os_Loader_initial_info : public os_Loader_info {

  public: // Construction
    os_Loader_initial_info (os_Loader&);
    ~os_Loader_initial_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;
    os_database* get_current_database () const;
    os_segment* get_current_segment () const;
    os_cluster* get_current_cluster () const;
    os_Dumper_reference get_original_location () const;
    os_Database_info* get_pending_database_info () const;

  protected: // Embedded data
    char* word;
    os_Loader_info* top_info;
    os_Loader_info* outermost_info;
    os_database* current_database;
    os_segment* current_segment;
    os_cluster* current_cluster;
    os_Dumper_reference original_location;
    os_Database_info* pending_database_info;
    
  protected: // Modifiers
    void set_current_database (os_database*);
    void set_current_segment (os_segment*);
    void set_current_cluster (os_cluster*);
    void set_original_location (os_Dumper_reference);
    void set_pending_database_info (os_Database_info*);

  private: // Friends
    friend class os_Loader;
    friend class os_Loader_translated_info;

  };


/***********************************************************************
  class os_Loader_translated_info
***********************************************************************/

/* TBD: Some os_Loader state will moved here so that multi-threaded loads
        can be accommodated. Each thread will have its own stack of
        os_Loader_info. What follows is the class used for the translated
        os_Loader_info. --rick@odi.com */

class os_Loader_translated_info : public os_Loader_info {

  public: // Construction
    os_Loader_translated_info (os_Loader&, os_Loader_stream&,
                               os_Loader_info& previous_info,
                               os_Loader::Predicate is_end);
    ~os_Loader_translated_info ();

  public: // Accessors
    virtual os_Loader_action::Kind get_kind () const;
    os_database* get_current_database () const;
    os_segment* get_current_segment () const;
    os_cluster* get_current_cluster () const;
    os_Dumper_reference get_original_location () const;
    os_Database_info* get_pending_database_info () const;

    // Modifiers
    void set_original_location (os_Dumper_reference);

  protected: // Embedded data
    os_Loader_initial_info* initial_info;
    os_Loader::Predicate is_end;

  protected: // Modifiers
    void set_current_database (os_database*);
    void set_current_segment (os_segment*);
    void set_current_cluster (os_cluster*);
    void set_pending_database_info (os_Database_info*);

  private: // Friends
    friend class os_Loader;
    friend class os_Database_loader;
    friend class os_Database_info;
    friend class os_Schema_loader;
    friend class os_Schema_info;
    friend class os_Segment_loader;
    friend class os_Segment_info;
    friend class os_Cluster_loader;
    friend class os_Cluster_info;
    friend class os_Object_loader;
    friend class os_Object_info;
    friend class os_Fixup_loader;
    friend class os_Fixup_info;
    friend class os_Schema_file_loader;
    friend class os_Schema_file_info;

  };


/***********************************************************************
  os_Loader registration types
***********************************************************************/

template <class Key, class Value> 
class os_Registration_entry;

template <class Key, class Value> 
class os_Registration_block;

template <class Key, class Value> 
class os_Registrations;

typedef os_Registration_entry<os_Type_loader*, os_Loader>
    os_Loader_registration_entry;
typedef os_Registration_block<os_Type_loader*, os_Loader>
    os_Loader_registration_block;
typedef os_Registrations<os_Type_loader*, os_Loader> os_Loader_registrations;


/***********************************************************************
  os_Fixup registration types
***********************************************************************/

typedef os_Registration_entry<os_Type_fixup_loader*, os_Loader>
    os_Fixup_registration_entry;
typedef os_Registration_block<os_Type_fixup_loader*, os_Loader>
    os_Fixup_registration_block;
typedef os_Registrations<os_Type_fixup_loader*, os_Loader>
    os_Fixup_registrations;


#endif /* LOADER_HH */
