
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

#include <ostore/msgsys/msglod.hh>

#include <ostore/traverse/argument.hh>
#include <ostore/traverse/traverse.hh>

#include <ostore/dumpload/loader.hh>
#include <ostore/dumpload/db_loader.hh>
#include <ostore/dumpload/schema_loader.hh>
#include <ostore/dumpload/seg_loader.hh>
#include <ostore/dumpload/obj_loader.hh>
#include <ostore/dumpload/fix_load.hh>
#include <ostore/dumpload/dlasblck.hh>
#include <ostore/dumpload/os_pref_schema.hh>
#include <ostore/dumpload/jseg_loader.hh>
#include <ostore/dumpload/jdb_loader.hh>

/***********************************************************************
  Forward Declarations
**********************************************************************/

class os_Loader_arguments;
static os_Loader& configure_loader (const os_Loader_arguments&);
static char* get_directory_path (const char* file_path);
static void setup_application_schema_path (const char* executable_path);

extern void register_os_jstring_wrapper_rank_hash();

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
  os_Loader_arguments
**********************************************************************/

class os_Loader_arguments : public os_Arguments {

  private:
    static const unsigned maximum_files;
    static const char* default_work_database_path;
    static const char* default_database_table_path;
    static const char* default_architecture;

  public: // Construction
    os_Loader_arguments (int given_argc, char* given_argv[])
        : os_Arguments(given_argc, given_argv)
    {
      files = new const char*[maximum_files];

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
              *new os_Argument_keyword_with_values<os_unsigned_int32>
                  (*this, /*value_name=*/ "cache",
                   /*description=*/ "sets cache size to given integral value (bytes); ",
                   /*value_storage=*/ cache_size, 
                   /*keyword_1=*/ "-c", /*keyword_2=*/ "-cache", 
                   /*initial_value=*/ default_cache_size,
                   /*is_hidden=*/ os_Argument::_FALSE, 
                   /*is_required=*/ os_Argument::_FALSE),
	      *new os_Argument_keyword_with_values<os_unsigned_int32>
	          (*this, /*value_name*/ "policy",
		   /*description*/ "sets the fetch policy of databases created to "
		   "given integral value (page(0), stream(1), cluster(2)); "
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
                  (*this, /*value_name=*/ "cwd",
                   /*description=*/ "loads databases in the current working directory",
                   /*value_storage=*/ cwd, /*keyword=*/ "-cwd",
                   /*initial_value=*/ os_Argument::_FALSE,
                   /*applied_value=*/ os_Argument::_TRUE),
              *new os_Argument_keyword_with_values<const char*>
                  (*this, /*value_name=*/ "table",
                   /*description=*/ "sets the name of the database table file", 
                   /*value_storage=*/ database_table_path,
                   /*keyword_1=*/ "-tab", /*keyword_2=*/ "-table", 
                   /*initial_value=*/ default_database_table_path,
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
                  (*this, /*value_name=*/ "dumped_schema",
                   /*description=*/ "used to load dumped schemas",
                   /*value_storage=*/ is_dumped_schema,
                   /*keyword_1=*/ "-ds", /*keyword_2=*/ "-dumped_schema", 
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
              // The -schema_file switch is temporary, and will be
              // removed when separate database scema is implemented.
              *new os_Argument_keyword_with_values<const char*>
                  (*this, /*value_name=*/ "schema_file",
                   /*description=*/ "sets the name of the schema file", 
		   /*value_storage=*/ schema_file, 
                   /*keyword_1=*/ "-sf", /*keyword_2=*/ "-schema_file", 
                   /*initial_value=*/ 0,
                   /*is_hidden=*/ os_Argument::_TRUE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword_with_values<const char*>
                  (*this, /*value_name=*/ "architecture",
                   /*description=*/ "sets architecture", 
		   /*value_storage=*/ arch_name, 
                   /*keyword_1=*/ "-a", /*keyword_2=*/ "-architecture", 
                   /*initial_value=*/ default_architecture,
                   /*is_hidden=*/ os_Argument::_TRUE,
                   /*is_required=*/ os_Argument::_FALSE),
	      // *new os_Argument_keyword_with_values<const char*>
	      //     (*this, /*value_name=*/ "preferred_schema",
	      //     /*description=*/ "pathname of the preferred schema", 
	      //     /*value_storage=*/ prfrd_schema_file, 
	      //     /*keyword_1=*/ "-ps", /*keyword_2=*/ "-preferred_schema", 
	      //     /*initial_value=*/ 0,
	      //     /*is_hidden=*/ os_Argument::_FALSE, 
	      //     /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_keyword<os_Argument::Boolean>
                  (*this, /*value_name=*/ "dont_force_alignment",
                   /*description=*/ "do not force alignment of instantiated class types",
                   /*value_storage=*/ dfa, 
                   /*keyword_1=*/ "-dfa", /*keyword_2=*/ "-dont_force_alignment", 
                   /*initial_value=*/ os_Argument::_TRUE,
                   /*applied_value=*/ os_Argument::_FALSE,
                   /*is_hidden=*/ os_Argument::_TRUE, 
                   /*is_required=*/ os_Argument::_FALSE),
              *new os_Argument_always<const char*>
                  (*this, /*value_name=*/ "db_table.dmp dmp_files",
                   /*description=*/ "files to be loaded", 
                   /*value_storage=*/ *files, /*initial_value=*/ 0, 
                   /*value_count=*/ total_files, /*maximum_values=*/ maximum_files,
                   /*expected_values=*/ 1));
      bind();
    }
    ~os_Loader_arguments ()
    {
      delete [] files;
      files = 0;
      total_files = 0;
    }

  public: // Embedded data
    os_unsigned_int32 cache_size;
    os_unsigned_int32 fetch_policy;
    os_unsigned_int32 fetched_pages;
    os_unsigned_int32 address_space_size;
    float address_space_threshold;
    const char* work_database_path;
    const char* database_table_path;
    const char** files;
    unsigned total_files;
    os_Argument::Boolean cwd;
    os_Argument::Boolean is_copying_schema;
    os_Argument::Boolean is_dumped_schema;
    os_Argument::Boolean is_java;
    os_Argument::Boolean dfa;
    const char* schema_file;
    const char* arch_name;
    const char* prfrd_schema_file;
    static os_unsigned_int32 default_cache_size;
  };


const unsigned os_Loader_arguments::maximum_files = 64;
os_unsigned_int32 os_Loader_arguments::default_cache_size = 24 * 1024000;
const char* os_Loader_arguments::default_work_database_path = "temp_dl_.db";
const char* os_Loader_arguments::default_database_table_path = DB_TABLE_FILENAME;
const char* os_Loader_arguments::default_architecture = 0;
os_Loader_arguments* arguments = 0;

#define ADJUST_INSTANTIATION_ALIGNMENT 1
#define ALLOW_SIZE_MISMATCH 2
#define FORCE_ALIGN_AND_ALLOW_SIZE_MISMATCH 3

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

    char* cache_size_env = getenv("OS_CACHE_SIZE");
    if (cache_size_env && *cache_size_env)
      os_Loader_arguments::default_cache_size = atol(cache_size_env);
    else
      os_Loader_arguments::default_cache_size = 24 * 1024000;

    arguments = new os_Loader_arguments(argc, argv);

    // Set cache size.
    objectstore::set_cache_size(arguments->cache_size);

  // Initialize services.
  objectstore::set_client_name(argv[0]);
  setup_application_schema_path(argv[0]);
  objectstore::initialize();
  os_collection::initialize();
  os_mop::initialize();
  register_os_jstring_wrapper_rank_hash();
  tix_exception::set_unhandled_exception_hook(unhandled_exception_handler);
  
#ifndef EMITTED_LOADER
  if ( !arguments->is_java )
     cerr << "Warning: emitted loader should be used for C++" << endl;
#endif
  os_Loader& loader = configure_loader(*arguments);
  loader.load(arguments->files, arguments->total_files);

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
      _os_schema_compute_schema_path("osload.adb", "OS_OSLOAD_APPSCHEMA_PATH",
                                     directory_path);
  if (arguments->debugging)
      cout << "set_application_schema_pathname(" << app_schema_path << ")" << endl;
  if ( ! app_schema_path) {
      os_Dumpload_messages::OS_FATAL(os_Dumpload_messages::setup_application_schema_path,
                                     (directory_path ? directory_path : "NULL"));
    }
  objectstore::set_application_schema_pathname(app_schema_path);
  delete app_schema_path;
  // There is some sort of problem with deleting directory_path which
  // only happens occasionally.
  //if (directory_path)
  //    delete directory_path;
}


/***********************************************************************
  Function:      configure_loader
  Description: 
  Parameters:   
  Signals:      
  Assumptions:  
  Restrictions: 
**********************************************************************/

/* TBD: Consider, configure_loader should be reimplemented in terms of
        a static os_Loader::create() function. --rick@odi.com */

static os_Loader& configure_loader (const os_Loader_arguments& arguments)
{
  os_Databases_loader* databases_loader = new os_Databases_loader();
  os_Database_entry_loader* database_entry_loader;
  os_unsigned_int32 preferred_schema_options;

  if (arguments.dfa == os_Argument::_TRUE)
    preferred_schema_options = FORCE_ALIGN_AND_ALLOW_SIZE_MISMATCH;
  else
    preferred_schema_options = ALLOW_SIZE_MISMATCH;

  if (arguments.cwd)
    {
      if (arguments.is_java)
	database_entry_loader
          = new osji_Database_entry_loader(*databases_loader, 
					   /*should_use_current_directory*/ 1);
      else
	database_entry_loader
          = new os_Database_entry_loader(*databases_loader, 
                                         /*should_use_current_directory*/ 1);
    }
  else
    {
      if (arguments.is_java)
	database_entry_loader
          = new osji_Database_entry_loader(*databases_loader, 
					   /*should_use_current_directory*/ 0);
      else
	database_entry_loader
          = new os_Database_entry_loader(*databases_loader, 
                                         /*should_use_current_directory*/ 0);
    }

  os_Database_loader* database_loader = new os_Database_loader();

  os_Roots_loader* roots_loader = new os_Roots_loader();
  os_Root_entry_loader* root_entry_loader
      = new os_Root_entry_loader(*roots_loader);

  os_Segment_loader* segment_loader;
  if (arguments.is_java)
    segment_loader = new osji_Segment_loader();
  else
    segment_loader = new os_Segment_loader();

  os_Cluster_loader* cluster_loader = new os_Cluster_loader();
  os_Object_loader* object_loader = new os_Object_loader();
  os_Fixup_loader* fixup_loader = new os_Fixup_loader();
  os_End_block_loader* end_block_loader = new os_End_block_loader();
  os_Finalization_loader* finalization_loader = new os_Finalization_loader();
  os_Schema_loader* schema_loader = new os_Schema_loader;
  os_Schema_file_loader* schema_file_loader = new os_Schema_file_loader;

  os_Loader* loader = new os_Loader(arguments.work_database_path,
                                    arguments.database_table_path,
                                    *databases_loader,
                                    *database_entry_loader,
                                    *database_loader, *roots_loader,
                                    *root_entry_loader, *segment_loader,
                                    *cluster_loader, *object_loader,
                                    *fixup_loader, *end_block_loader,
                                    *finalization_loader, *schema_loader,
                                    *schema_file_loader,
                                    preferred_schema_options);

  loader->set_is_debugging(arguments.debugging);

  objectstore::set_incremental_schema_installation(/*true*/ 1);

   if (arguments.address_space_size)
      {
      objectstore::set_default_address_space_partition_size(arguments.address_space_size * 65536);
      }

  if (arguments.address_space_threshold)
      os_DL_address_space_controller::set_address_space_threshold
	  (arguments.address_space_threshold);

  loader->set_fetch_policy((os_fetch_policy)arguments.fetch_policy);
  loader->set_fetched_pages(arguments.fetched_pages);
  os_Loader_architecture::set(arguments.arch_name);
  if (arguments.is_copying_schema)
     {
     loader->set_is_copying_schema(os_Argument::_TRUE);
     }
  if (arguments.is_java)
     {
     loader->set_is_java(os_Argument::_TRUE);
     loader->set_is_loading_schema(os_Argument::_TRUE);
     }
  if (arguments.is_dumped_schema)
     {
     loader->set_is_loading_schema(os_Argument::_TRUE);
     }
  if (arguments.schema_file)
      loader->set_collected_schema_path(arguments.schema_file);

  // The -ps option is disabled. It is not complete.
  //  if (arguments.prfrd_schema_file)
  //    os_preferred_schema::initialize(preferred_schema_options,
  //				    arguments.work_database_path,
  //				    arguments.prfrd_schema_file);
  //  else
    os_preferred_schema::initialize(preferred_schema_options,
				    arguments.work_database_path);	


  return *loader;
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


