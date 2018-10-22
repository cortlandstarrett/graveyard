
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>

#include <ostore/ostore.hh>
#include <ostore/msgsys/msgexcpt.hh>
#include <ostore/msgsys/msgsys.hh>
#include <ostore/msgsys/msgtrvrs.hh>
#include <ostore/msgsys/msgdmplod.hh>
#include <ostore/coll.hh>
#include <ostore/coll/dict_pt.hh>
#include <ostore/mop.hh>

#include <ostore/traverse/argument.hh>
#include <ostore/traverse/obj_act.hh>
#include <ostore/traverse/pred_act.hh>
#include <ostore/traverse/enum_act.hh>
#include <ostore/traverse/ptr_act.hh>
#include <ostore/traverse/ary_act.hh>
#include <ostore/dumpload/dump_cls_act.hh>
#include <ostore/traverse/func_act.hh>
#include <ostore/traverse/indr_act.hh>
#include <ostore/traverse/seg_act.hh>
#include <ostore/traverse/db_act.hh>
#include <ostore/traverse/traverse.hh>
#include <ostore/traverse/root_act.hh>
#include <ostore/traverse/schm_act.hh>

#include <ostore/dumpload/db_table.hh>
#include <ostore/dumpload/dump_act.hh>
#include <ostore/dumpload/dumper.hh>
#include <ostore/dumpload/planner.hh>
#include <ostore/dumpload/dlasblck.hh>


//-- Forward Declarations ----------------------------------------------

class os_Dumper_arguments;
static os_Dumper& configure_dumper (os_Dumper_arguments& arguments);
static char* get_directory_path (const char* file_path);
static void setup_application_schema_path (const char* executable_path);


/***********************************************************************
  Function:     _os_schema_compute_schema_path
  Description:  Returns a computed schema path or null if a path could
                not be constructed. If an environment variable is 
                provided an attempt is first made to compute a schema path
                using the environment variable. If successful, this schema
                path is returned. Next any given search path is used. A
                search path must consist of one or more directory paths
                separated by a semi-colon (';'). These directory paths are
                concatenated with the given schema_name to produce candiate
                schema_paths. The first valid path found is returned. If
                no valid path is found, it is assumed that the target
                schema path denotes an eXcelon Corp. supplied schema and 
		an attempt is made to compute an appropriate path for an 
		ObjectStore distribution.
  Parameters:
    schema_name - the name of the target schema.
    environment_variable_denoting_schema_path 
                - name of environment variable possibly denoting
                  the schema path.
    search_path - the search path of directories in which to look
                  for the target schema.
  Signals:      None.
  Assumptions:  None.
  Restrictions: If the given schema_name is null, then null is returned
                immediately.
**********************************************************************/

char* _os_schema_compute_schema_path
  (const char* schema_name,
   const char* environment_variable_denoting_schema_path = 0,
   const char* search_path = 0);


/***********************************************************************
  Function:      unhandled_exception_handler
  Description: 
  Parameters:   
  Signals:      
  Assumptions:  
  Restrictions: 
**********************************************************************/

static void unhandled_exception_handler 
    (tix_exception* /*cause*/, os_int32 /*value*/, char* report)
{
    cout << "Handling an unhandled exception: " << endl;
}


/***********************************************************************
  class os_Dumper_arguments
***********************************************************************/

class os_Dumper_arguments : public os_Arguments {

  private:
    static const unsigned maximum_databases;
    static const unsigned default_cache_size;
	static const char* default_work_database_path;
    static const char* default_database_table_path;
    static const char* default_destination;

  public: // Construction
    os_Dumper_arguments (int given_argc, char* given_argv[])
        : os_Arguments(given_argc, given_argv)
    {
      databases = new const char*[maximum_databases];

      /* Note that os_Argument_always should be the last argument specified. */
      arguments 
          = &(*new os_Argument_keyword<os_Argument::Boolean>
                  (*this, /*value_name=*/ "verbose", 
                   /*description=*/ "initiates verbose output", 
                   /*value_storage=*/ verbose,
                   /*keyword_1=*/ "-v", /*keyword_2=*/ "-verbose", 
                   /*initial_value=*/ os_Argument::_FALSE, 
                   /*applied_value=*/ os_Argument::_TRUE,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword_with_values<int>
                  (*this, /*value_name=*/ "level",
                   /*description=*/ "sets debugging level to given integral value", 
                   /*value_storage=*/ debugging, 
                   /*keyword_1=*/ "-d", /*keyword_2=*/ "-debug", 
                   /*initial_value=*/ 0, /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword<os_Argument::Boolean>
                  (*this, /*value_name=*/ "indirects",
                   /*description=*/ "initiates handling of indirect types",
                   /*value_storage=*/ indirects,
                   /*keyword_1=*/ "-i", /*keyword_2=*/ "-indirects", 
                   /*initial_value=*/ os_Argument::_FALSE,
                   /*applied_value=*/ os_Argument::_TRUE,
                   /*is_hidden=*/ os_Argument::_TRUE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword<os_Argument::Boolean>
                  (*this, /*value_name=*/ "emit",
                   /*description=*/ "initiates emitting of loader",
                   /*value_storage=*/ emitting,
                   /*keyword_1=*/ "-e", /*keyword_2=*/ "-emit", 
                   /*initial_value=*/ os_Argument::_FALSE, 
                   /*applied_value=*/ os_Argument::_TRUE,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword_with_values<os_unsigned_int32>
                  (*this, /*value_name=*/ "cache",
                   /*description=*/ "sets cache size to given integral value (bytes); "
		   "default is 24 MB", 
                   /*value_storage=*/ cache_size, 
                   /*keyword_1=*/ "-c", /*keyword_2=*/ "-cache", 
                   /*initial_value=*/ default_cache_size,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
	      *new os_Argument_keyword_with_values<os_unsigned_int32>
	          (*this, /*value_name*/ "policy",
		   /*description*/ "sets the fetch policy of databases created to "
		   "given integral value (page(1), stream(1), cluster(2)); "
		   "default is page(0)", 
		   /*value_storage*/ fetch_policy, 
		   /*keyword_1=*/ "-f", /*keyword_2=*/ "-policy", 
		   /*initial_value=*/ /*page*/ 0,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
	      *new os_Argument_keyword_with_values<os_unsigned_int32>
	          (*this, /*value_name*/ "pages",
		   /*description*/ "sets the pages fetched from databases created "
		   "to given integral value; default is 8", 
		   /*value_storage*/ fetched_pages, 
		   /*keyword_1=*/ "-p", /*keyword_2=*/ "-pages",
		   /*initial_value=*/ 8,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword_with_values<os_unsigned_int32>
                  (*this, /*value_name=*/ "size",
                   /*description=*/ "sets address space size to given integral "
		   "value (bytes); default is unassigned space or OS_AS_SIZE",
		   /*value_storage=*/ address_space_size, 
                   /*keyword_1=*/ "-s", /*keyword_2=*/ "-size", 
                   /*initial_value=*/ 0,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword_with_values<float>
                  (*this, /*value_name=*/ "threshold",
                   /*description=*/ "sets address space usage threshold to given "
		   "percentage value [0.00,1.00]; default is 0.50", 
		   /*value_storage=*/ address_space_threshold, 
                   /*keyword_1=*/ "-t", /*keyword_2=*/ "-threshold", 
                   /*initial_value=*/ 0,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword_with_values<const char*>
                  (*this, /*value_name=*/ "workdb",
                   /*description=*/ "sets the name of the work database", 
                   /*value_storage=*/ work_database_path,
                   /*keyword_1=*/ "-w", /*keyword_2=*/ "-workdb", 
                   /*initial_value=*/ default_work_database_path,
                   /*is_hidden=*/ os_Argument::_TRUE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword<os_Argument::Boolean>
                  (*this, /*value_name=*/ "pseudo",
                   /*description=*/ "causes generation of pseudo declarations",
                   /*value_storage=*/ pseudo,
                   /*keyword_1=*/ "-u", /*keyword_2=*/ "-pseudo", 
                   /*initial_value=*/ os_Argument::_FALSE,
                   /*applied_value=*/ os_Argument::_TRUE,
                   /*is_hidden=*/ os_Argument::_TRUE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword_with_values<const char*>
                  (*this, /*value_name=*/ "table",
                   /*description=*/ "sets the name of the database table file", 
                   /*value_storage=*/ database_table_path,
                   /*keyword_1=*/ "-tab", /*keyword_2=*/ "-table", 
                   /*initial_value=*/ default_database_table_path,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword_with_values<const char*>
                  (*this, /*value_name=*/ "dump_pathname",
                   /*description=*/ "path of dump destination", 
                   /*value_storage=*/ dump_pathname,
                   /*keyword_1=*/ "-h", /*keyword_2=*/ "-path", 
                   /*initial_value=*/ default_destination,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword<os_Argument::Boolean>
                  (*this, /*value_name=*/ "java",
                   /*description=*/ "used for Java databases",
                   /*value_storage=*/ is_java,
                   /*keyword_1=*/ "-j", /*keyword_2=*/ "-java", 
                   /*initial_value=*/ os_Argument::_FALSE,
                   /*applied_value=*/ os_Argument::_TRUE,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword<os_Argument::Boolean>
                  (*this, /*value_name=*/ "copy_schema",
                   /*description=*/ "causes schema to be copied",
                   /*value_storage=*/ is_copying_schema,
                   /*keyword_1=*/ "-cs", /*keyword_2=*/ "-copy_schema", 
                   /*initial_value=*/ os_Argument::_FALSE,
                   /*applied_value=*/ os_Argument::_TRUE,
                   /*is_hidden=*/ os_Argument::_TRUE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword_with_values<const char*>
                  (*this, /*value_name=*/ "schema_file",
                   /*description=*/ "sets the name of the copied schema file", 
		   /*value_storage=*/ schema_file, 
                   /*keyword_1=*/ "-sf", /*keyword_2=*/ "-schema_file", 
                   /*initial_value=*/ 0,
                   /*is_hidden=*/ os_Argument::_TRUE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword<os_Argument::Boolean>
                  (*this, /*value_name=*/ "dump_schema",
                   /*description=*/ "causes schema to be dumped",
                   /*value_storage=*/ is_dumping_schema,
                   /*keyword_1=*/ "-ds", /*keyword_2=*/ "-dump_schema", 
                   /*initial_value=*/ os_Argument::_FALSE,
                   /*applied_value=*/ os_Argument::_TRUE,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_always<const char*>
                  (*this, /*value_name=*/ "databases",
                   /*description=*/ "databases to be dumped", 
                   /*value_storage=*/ *databases, /*initial_value=*/ 0, 
                   /*value_count=*/ total_databases,
                   /*maximum_values=*/ maximum_databases, /*expected_values=*/ 1));
      bind();
    }
    ~os_Dumper_arguments ()
    {
      delete [] databases;
      databases = 0;
      total_databases = 0;
    }

  public: // Embedded data
    const char** databases;
    const char* database_table_path;
    unsigned total_databases;
    os_Argument::Boolean emitting;
    os_Argument::Boolean pseudo;
    os_unsigned_int32 cache_size;
    os_unsigned_int32 fetch_policy;
    os_unsigned_int32 fetched_pages;
    os_unsigned_int32 address_space_size;
    float address_space_threshold;
    const char* dump_pathname;
    const char* work_database_path;
    os_Argument::Boolean is_copying_schema;
    const char* schema_file;
    os_Argument::Boolean is_dumping_schema;
    os_Argument::Boolean is_java;
  };

const unsigned os_Dumper_arguments::maximum_databases = 64;
const unsigned os_Dumper_arguments::default_cache_size = 24 * 1024000;
const char* os_Dumper_arguments::default_work_database_path = "temp_dl_.db";
const char* os_Dumper_arguments::default_database_table_path = DB_TABLE_FILENAME;
os_Dumper_arguments* arguments = 0;
const char* os_Dumper_arguments::default_destination = 0;

/***********************************************************************
  Function:      main
  Description: 
  Parameters:   
  Signals:      
  Assumptions:  
  Restrictions: 
**********************************************************************/

int main (int argc, char* argv[])
{
  OS_ESTABLISH_FAULT_HANDLER

  arguments = new os_Dumper_arguments(argc, argv);

  // Set cache size.
  objectstore::set_cache_size(arguments->cache_size);

  // Initialize ObjectStore.
  objectstore::set_client_name(argv[0]);
  setup_application_schema_path(argv[0]);
  objectstore::initialize();
  os_collection::initialize();
  os_mop::initialize();
  tix_exception::set_unhandled_exception_hook(unhandled_exception_handler);
  
  os_Dumper& dumper = configure_dumper(*arguments);
  if ( dumper.is_dumping_schema() )
    dumper.dump_schema(arguments->databases, arguments->total_databases);
  dumper.dump(arguments->databases, arguments->total_databases);

  objectstore::shutdown();
  OS_END_FAULT_HANDLER

  return 0;
}


/***********************************************************************
  Function:      setup_application_schema_path
  Description: 
  Parameters:   
  Signals:      
  Assumptions:  
  Restrictions: 
**********************************************************************/

static void setup_application_schema_path (const char* executable_path)
{
  char* directory_path = get_directory_path(executable_path);
  if (arguments->debugging)
      cout << "schema search path = " << (directory_path ? directory_path : "NULL")
           << endl;
  char* app_schema_path =
      _os_schema_compute_schema_path("osdump.adb", "OS_OSDUMP_APPSCHEMA_PATH",
                                     directory_path);
  if (arguments->debugging)
      cout << "set_application_schema_pathname(" << app_schema_path << ")" << endl;
  if ( ! app_schema_path) {
      os_Dumpload_messages::OS_FATAL(os_Dumpload_messages::setup_application_schema_path,
                                     (directory_path ? directory_path : "NULL"));
    }
  objectstore::set_application_schema_pathname(app_schema_path);

  if (directory_path)
      delete directory_path;
}


/***********************************************************************
  Function:      configure_dumper
  Description: 
  Parameters:   
  Signals:      
  Assumptions:  
  Restrictions: 
**********************************************************************/

/* TBD: Consider, configure_dumper should be reimplemented in terms of
        a static os_Dumper::create() function. --rick@odi.com */

static os_Dumper& configure_dumper (os_Dumper_arguments& arguments)
{
  os_Predef_action* predef_action = new os_Predef_action();

  os_Enum_action* enum_action = new os_Enum_action();

  os_Pointer_action* pointer_action = new os_Pointer_action();

  os_Function_action* function_action = new os_Function_action();

  os_Array_action* array_action 
      = new os_Array_action(predef_action, enum_action, pointer_action,
                            /*class_action*/ 0, function_action);

  os_Indirect_action* indirect_action 
      = new os_Indirect_action(predef_action, enum_action, pointer_action,
                               array_action, /*class_action*/ 0,
                               function_action, /*indirect_action*/ 0);

  os_Base_action* base_action = new os_Base_action(/*class_action*/ 0);

  os_Member_variable_action* member_variable_action 
      = new os_Member_variable_action(predef_action, enum_action,
                                      pointer_action, array_action,
                                      /*class_action*/ 0, function_action,
                                      /*indirect_action*/ 0);

  os_Member_type_action* member_type_action
      = new os_Member_type_action(enum_action, /* class_action */ 0,
                                  /* indirect_action */ 0);

  os_Class_action* class_action 
    = new os_Class_action(base_action, member_variable_action,
			  /*member_function_action*/ 0,
			  member_type_action,
			  /*member_access_modifier_action*/ 0);

  member_type_action->set_class_action(*class_action);

  array_action->set_class_action(*class_action);
  array_action->set_indirect_action(*indirect_action);

  indirect_action->set_class_action(*class_action);
  indirect_action->set_indirect_action(*indirect_action);

  base_action->set_class_action(*class_action);

  member_variable_action->set_class_action(*class_action);
  member_variable_action->set_indirect_action(*indirect_action);

  os_Object_action* object_action 
      = new os_Object_action(predef_action, enum_action, pointer_action,
                             array_action, class_action, function_action,
                             indirect_action);

  os_Segment_action* segment_action
      = new os_Dumper_segment_action(object_action);

  os_Root_action *root_action = new os_Root_action();

  os_Schema_action* schema_action
      = new os_Schema_action(object_action, class_action);

  os_Database_action* database_action;
  if (arguments.emitting)
      database_action
          = new os_Database_action(/*segment_action*/ 0, /*root_action*/ 0, 
                                   schema_action);
  else if (arguments.is_copying_schema)
      database_action
          = new os_Database_action(segment_action, root_action, 
                                   schema_action,
                                   /*should_do_roots_last*/ 1);
  else
      database_action
          = new os_Database_action(segment_action, root_action, 
                                   /*schema_action*/ 0,
                                   /*should_do_roots_last*/ 1);

  os_boolean dump_flag = arguments.emitting ? 0 : 1; 
  os_boolean pseudo_flag = arguments.emitting && arguments.pseudo ? 1: 0;
  os_boolean java_flag = arguments.is_java ? 1 : 0; 

  os_Dumper_actions* dumper_actions
      = new os_Dumper_actions(dump_flag, pseudo_flag, java_flag);

  os_Traverser* traverser
      = new os_Traverser(*dumper_actions, database_action);
			 // (os_Traverser::Find_specialization_function)
  //                         os_Dumper_registrations::find);

  traverser->set_is_debugging
      (arguments.debugging > os_Traverser::object_level ?
       (os_Traverser::Debug_level)arguments.debugging 
       : os_Traverser::object_level);
  traverser->set_is_locking_databases(/*osbool*/ 1);
  if (arguments.emitting || arguments.is_copying_schema)
      traverser->set_is_handling_schema(/*osbool*/ 1);

  os_Dumper* dumper = new os_Dumper(
     arguments.work_database_path,
     arguments.database_table_path,
     *traverser,
     *dumper_actions,
     arguments.dump_pathname);

  //  os_Dumper_registrations::register_entries(*dumper);
  //  os_Planner_registrations::register_entries(*dumper);

  if (arguments.address_space_size)
      os_DL_address_space_controller::set_address_space_total
	  (arguments.address_space_size);

  if (arguments.address_space_threshold)
      os_DL_address_space_controller::set_address_space_threshold
	  (arguments.address_space_threshold);

  dumper->set_fetch_policy((os_fetch_policy)arguments.fetch_policy);
  dumper->set_fetched_pages(arguments.fetched_pages);
  dumper->set_is_copying_schema(arguments.is_copying_schema);
   //
   // If Java then force other settings as appropriate here.
   //
   if (java_flag)
      {
      dumper->set_is_dumping_schema(os_Argument::_TRUE);
      }
   if (arguments.is_dumping_schema)
      {
      dumper->set_is_dumping_schema(os_Argument::_TRUE);
      }
  if (arguments.schema_file)
     dumper->set_copied_schema_path(arguments.schema_file);

  if (arguments.debugging) {
    //      os_Dumper_registrations::dump("Dumper Specializations");
    //      os_Planner_registrations::dump("Planner Specializations");
    }

  return *dumper;
}


/***********************************************************************
  Function:     get_directory_path
  Description:  
  Parameters:   
  Signals:      
  Assumptions:  
  Restrictions: 
**********************************************************************/

static char* get_directory_path (const char* given_file_path)
{
#ifdef _OS_Win32
  char separator = '\\';
#else
  char separator = '/';
#endif
  unsigned length = strlen(given_file_path);
  char* file_path = new char[length + 1];
  strcpy(file_path, given_file_path);
  for (int index = length; index >= 0; --index) {
      if (file_path[index] == separator) {
          if (index > 0 && file_path[index - 1] == separator)
              file_path[index - 1] = '\0';
          else
              file_path[index] = '\0';
          return file_path;
        }
    }
  file_path[0] = '.';
  file_path[1] = '\0';
  return file_path;
}


