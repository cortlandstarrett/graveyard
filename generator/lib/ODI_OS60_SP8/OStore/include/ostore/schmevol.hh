/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _OS_SCHMEVOL_H_
#define _OS_SCHMEVOL_H_
#include <ostore/hdrstart.hh>

#include <ostore/ostore.hh>
#include <ostore/semoptwk.hh>

#ifndef _OS_COLLECTION_H_
#include <ostore/coll.hh>
#endif
	 
#include <ostore/ossevol/fbinding.hh>

class os_type ;
  

/***************************************************************************
* 									   *
* The following conventions are used throughout the schema evolution	   *
* interface:								   *
* 									   *
* 1) References are used for argument or return types wherver a null	   *
* pointer is not an acceptable value and the type of the argument is not   *
* void.									   *
* 									   *
* 									   *
* 2) The suffix 1 and 2 are used refer to unevolved and evolved objects	   *
* respectively. Thus object_1 is a pointer to an unevolved object, while   *
* object_2 is a pointer to an unevolved object in the interfaces defined   *
* below. Similarly, object_type_1 would denote the meta type description   *
* of the unevolved object, while object_type_2 denotes the evolved type	   *
* description.								   *
* 									   *
***************************************************************************/

/* the mother of all schema evolution exceptions */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_schema_evolution);

/* the requested schema evolution was unnecessary all the schemas under */
/* consideration are compatible */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_se_unnecessary);

/* cannot delete the class from the schema since other classes still depend */
/* upon it */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_se_cannot_delete_class);

/* the base type for illegal pointers of various ilks */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_se_illegal_pointer);

/* encountered a pointer to a transient object */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_se_transient_object);
		 
/* pointer to a deleted object */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_se_deleted_object);

/* pointer to the deleted component of a valid object */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_se_deleted_component);

/* pointer type mismatch */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_se_pointer_type_mismatch);

/* a void pointer that could not be interpreted unambiguously.  This is   */
/* the case when there are nested datum that occupy the same location     */
/* before schema evolution, but different locations afterwards            */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_se_ambiguous_void_pointer);


/* attempt to evolve an object to a type which is not a subtype */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_se_invalid_subtype_evolution);

/* attempt to evolve an object to a subtype in which it is not a unique
   supertype */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_se_ambiguous_subtype_evolution);

/* attempt to resolve a cross-database pointer to a database that was not
part of the set of databases being evolved */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_se_cross_database_pointer);

/* attempt to upgrade for vector headers a database which contained arrays */
/* of classes whose alignment was less than word alignment and whose size  */
/* was not a word size multiple.                                           */
_OS_DECLARE_EXCEPTION(_OS_SEVOL,err_cannot_upgrade_vector_headers);

/***************************************************************************
*   os_prim_typed_pointer is an artifice used to exclude the deref	   *
*   operator for instantiations with primitive arguments, which would	   *
*   otherwise be illegal.						   *
***************************************************************************/

template <class T>
class os_prim_typed_pointer {
  T* p ;
  const os_type& t ;
  
public:
  /* Construct a typed pointer */
    os_prim_typed_pointer(T* pointer, const os_type& type)
    : p(pointer),  t(type) {}						   

  /* returns the meta type description for the type. The type is Void     */
  /* when there is no known type because the pointer is illegal           */
  const os_type& get_type() const { return t ; }
  operator T*() const { return p ; }
} ;


#if 0 /* some day, but not yet */
template <class T>
class os_typed_pointer : public os_prim_typed_pointer<T> {

public:
  T* operator ->() const ;
  os_typed_pointer(T* pointer, const os_type& type) :
  os_prim_typed_pointer<T>(pointer,type) {}			   
} ;
#endif

typedef os_prim_typed_pointer<void> os_typed_pointer_void ;
typedef os_typed_pointer_void const& os_typed_pointer_void_const_r;

class os_old_reference;
class os_path ;

/* Definitions for DEC C++. */
typedef void*& os_void_p_r;
typedef objectstore_exception& objectstore_exception_r;
typedef os_coll_query& os_coll_query_r;
typedef os_collection const& os_collection_const_r;
typedef os_database_root& os_database_root_r;
typedef os_old_reference& os_old_reference_r;
typedef os_reference& os_reference_r;
typedef os_reference_local& os_reference_local_r;
			       
/***************************************************************************
* 									   *
* The subtype evolution function signature. It's argument is a pointer to  *
* an an unevolved object of class type. The return value if non-null is	   *
* the name of the class that the object must be evolved to. If null, the   *
* evolved object retains it's type.					   *
* 									   *
***************************************************************************/

typedef char* (*os_evolve_subtype_fun)(os_typed_pointer_void const&);
typedef os_func_ass<os_evolve_subtype_fun> os_evolve_subtype_fun_binding ;
typedef os_Collection<os_evolve_subtype_fun_binding*> os_evolve_subtype_fun_bindings ;
typedef os_Cursor<os_evolve_subtype_fun_binding*> evolve_subtype_fun_cursor ;

typedef os_Collection<const char*> os_charp_collection ;
typedef os_List<const char*> os_charp_list ;
typedef os_Cursor<const char*> os_charp_cursor ;

typedef void (*os_transformer)(os_void_p p) ;
typedef os_func_ass<os_transformer> os_transformer_binding ;
typedef os_Collection<os_transformer_binding*> os_transformer_bindings;
typedef os_Cursor<os_transformer_binding*> os_transformer_cursor ;

typedef void (*os_se_hook_function_void)(void) ;
typedef os_List<os_se_hook_function_void>	os_se_hook_function_list;
typedef os_Cursor<os_se_hook_function_void>	os_se_hook_function_cursor;

/***************************************************************************
* 									   *
* Illegal pointer handler function signature				   *
* 									   *
* objectstore_exception - the exception that would have been signaled if   *
* the handler were absent.						   *
* 									   *
* explanation - the error message string that would have been printed as   *
* part of unhandled exception. Deleting the string is the handler's	   *
* responsibility.							   *
* 									   *
* illegalp - a reference to the location of the illegal pointer within the *
* above object.								   *
* 									   *
* If the handler returns, it is assumed that it managed to fix the problem *
* and execution is resumed. In particular, the handler may choose to	   *
* modify the value of the pointer as appropriate.			   *
* 									   *
***************************************************************************/


/* This class is merely a type safety device. No instance of it is ever   */
/* allocated. All ptom types are expressed in terms of pointers to this   */
/* class. If C++ supported a ptom type like <type> void::*, then we would */
/* not need this subterfuge.                                              */
class os_canonical_ptom_class {
} ;

typedef os_unsigned_int32 os_canonical_ptom_class::* os_canonical_ptom ;
typedef os_canonical_ptom& os_canonical_ptom_r;

typedef void (*os_illegal_pointer_handler_fun)
     (objectstore_exception_r, os_char_p explanation, os_void_p_r illegalp) ;

typedef void (*os_illegal_pointer_to_member_handler_fun)
     (objectstore_exception_r, os_char_p explanation,
      os_canonical_ptom_r illegal_ptom) ;

typedef void (*os_illegal_reference_local_handler_fun)
     (objectstore_exception_r, os_char_p explanation,
      os_reference_local_r illegal_reference) ;

typedef void (*os_illegal_reference_handler_fun)
     (objectstore_exception_r, os_char_p explanation,
      os_reference_r illegal_reference) ;

typedef void (*os_illegal_old_reference_handler_fun)
     (objectstore_exception_r, os_char_p explanation,
      os_old_reference_r illegal_reference) ;

typedef void (*os_illegal_database_root_handler_fun)
     (objectstore_exception_r, os_char_p explanation,
      os_database_root_r illegal_database_root) ;



typedef void (*os_obsolete_index_handler_fun)	
     (os_collection_const_r, os_char_const_p index_name) ;

typedef void (*os_obsolete_query_handler_fun)     
     (os_coll_query_r q, os_char_const_p qexpr_str ) ;


typedef class _OS_schema_evolution_internal_params os_sei_params ;
	

/* os_schema_evolution serves to accumulate user-specified parameters.    */
      
class _OS_schema;

#ifndef OS_NAMEQUIV_H
class os_schema;
#endif

class os_schema_evolution {

private:
  /* os_schema_evolution does not have a constructor, so make it private  */
  /* to catch errors                                                      */
  os_schema_evolution() ;

  static class _OS_schema_evolution_internal_params& current_params() ;

public: /* Schema evolution utility functions */
  /* initiate the schema evolution */
  static void evolve(const char* workdb_name, /* may not be null */
		     const os_charp_collection& databases_to_be_evolved);
  static void evolve(const char* workdb_name, /* may not be null */
		     const char* database_name);

#ifndef OS_NAMEQUIV_H
  static void evolve (const char* workdb_name, /* may not be null */
		      const char* database_name, os_schema &new_schema);
  static void evolve (const char* workdb_name, /* may not be null */
		      const os_charp_collection& databases_to_be_evolved,
		      os_schema &new_schema);
#endif

  /* This function describes in words the changes that will not be        */
  /* carried out automatically by the schema evolution, but will require  */
  /* some sort of programming intervention via user transformers or some  */
  /* ensuing cleanup code. It is expected that this function will         */
  /* normally be invoked as a prelude to planning an extensive schema     */
  /* evolution.                                                           */
  static void task_list(const char* wdbname,
			const os_charp_collection& databases_to_be_evolved);
  static void task_list(const char* workdb_name, /* may not be null */
			const char* database_name);

  /* The functions get_evolved_object and get_unevolved_object serve to   */
  /* translate pointers from evolved objects into typed pointers to       */
  /* unevolved objects vice versa.                                        */
  /*                                                                      */
  /* Excluding cases of subtype schema evolution, the type associated     */
  /* with the unevolved and evolved types must name the same class or     */
  /* primitive type.                                                      */

  /* Returns a typed pointer to the evolved object.  A null               */
  /* os_prim_typed_pointer is returned if the object was not evolved.     */
  /* Colocation ambiguities are ignored by this function, and the         */
  /* outermost colocated type is returned in case of ambiguity.           */
  static os_typed_pointer_void get_evolved_object(const void* object_1) ;
  
  /* The function get_unevolved_object will signal the exception          */
  /* err_schema_evolution, if the unevolved object has had it's storage   */
  /* recycled.                                                            */
  static os_typed_pointer_void get_unevolved_object(const void* object_2) ;

  /* A variant of the above of functions above that does not check to see */
  /* if the object indicated by the address is valid. It assumes that     */
  /* only the address (and not the object) is of interest.                */
  static os_typed_pointer_void get_evolved_address(const void* addr_1) ;
  static os_typed_pointer_void get_unevolved_address(const void* addr_2) ;

public: /* setting parameters for schema evolution */
     
  /* the database defining the schema to evolve to. It may be either a    */
  /* compilation or an application schema database. The default uses the  */
  /* processes application schema.                                        */
  static void set_evolved_schema_db_name(const char* evolved_schema_db_name);
  static const char* get_evolved_schema_db_name() ;
					 
  /* A list of dll schema databases to use in conjunction with the        */
  /* primary application schema database specified.  The default value is */
  /* a null list in which case only the application or compilation schema */
  /* database is used.                                                    */
  static void augment_dll_schema_db_names
    (const os_charp_collection& dll_schema_db_names);
  static void augment_dll_schema_db_names(const char* c);
  static os_charp_collection* get_dll_schema_db_names() ;

  /* Augment the set of classes to be deleted as part of the evolution.   */
  /* Before evolution is initiated, the set must be closed so that if any */
  /* class is listed, all classes dependent upon it must also be part of  */
  /* the set.                                                             */
  static void augment_classes_to_be_removed
    (const os_charp_collection& classes_to_be_removed);
  static void augment_classes_to_be_removed (const char* class_to_be_removed);

  /* Augment the set of classes that may optionally be present in the       */
  /* database to be evolved. This is used to ensure that no spurious error  */
  /* messages are produced for classes that may have transformers           */
  /* assocaited with them, but are not part of the current schema, perhaps  */
  /* because schema is being incrementally installed.                       */
  static void augment_optional_classes(const os_charp_collection&) ;
  static void augment_optional_classes(const char*);
	 
  /* Augment the set of classes whose storage can be reclaimed            */
  /* immediately, after the default transformation is completed, since    */
  /* they are not referenced by user transformations.                     */
  static void augment_classes_to_be_recycled
    (const os_charp_collection& classes_to_be_recycled) ;
  static void augment_classes_to_be_recycled (const char* class_to_be_recycled) ;

  /* used to determine whether all classes may be recycled */
  static void set_recycle_all_classes(os_boolean) ;

  /* Determines whether an attempt to use an ambiguous void pointer       */
  /* results in an illegal handler being invoked (the default behavior)   */
  /* or whether the pointer is simply resolved to the enclosing colocated */
  /* object                                                               */
  static void set_resolve_ambiguous_void_pointers(os_boolean) ;
	 
  /* Augment the mappings from class names to the evolution subtype       */
  /* functions that determine the subtype an object will evolve to.       */
  static void augment_subtype_selectors(const os_evolve_subtype_fun_bindings&) ;
  static void augment_subtype_selectors(const os_evolve_subtype_fun_binding&) ;
  
  /* Augment the mapping from class names to transformer functions        */
  /* defined by the user.                                                 */
  static void augment_pre_evol_transformers(const os_transformer_bindings&);
  static void augment_pre_evol_transformers(const os_transformer_binding&);

  static void augment_post_evol_transformers(const os_transformer_bindings&);
  static void augment_post_evol_transformers(const os_transformer_binding&);

  static void augment_nonversioned_transformers(const os_transformer_bindings&);
  static void augment_nonversioned_transformers(const os_transformer_binding&);

#ifdef VERSIONS_EXTRACTION
  static void augment_initializer_transformers(const os_transformer_bindings&);
  static void augment_initializer_transformers(const os_transformer_binding&);
#endif /* VERSIONS_EXTRACTION */

  static void augment_nonversion_setup_hooks(os_se_hook_function_void);
  static void augment_nonversion_cleanup_hooks(os_se_hook_function_void);

  /* Hook function will get called for setting up things like vgroups in  */
  /* a context where schema validation is disabled.                       */
  static void set_pre_evolution_setup_hook(os_se_hook_function_void);

  /* The option that determines whether local references are relative to  */
  /* the db within which they reside. Defaults to zero.                   */
  static void set_local_references_are_db_relative(os_boolean) ;
  
  /* The level of explanation provided during evolution. It's silent by   */
  /* default. When not silent, the explanation is produced on stderr      */
  enum { silent, phase_level, type_level, object_level, verbose } ;
  static void set_explanation_level(os_unsigned_int32) ;

  /* Set the name of the file to which task list information is written.  */
  static void set_task_list_file_name(const char* file_name);

  /* Don't check for the existence of classes with transformers in the    */
  /* schemas participating in the evolution. It's okay for them to be     */
  /* absent.                                                              */
  static void set_disable_transformer_class_checks(os_boolean) ; 

  /* Ignore any illegal pointers encountered during schema evolution.  If */
  /* this is set to true and an illegal_pointer_handler_function is       */
  /* specified, the handler is invoked first, if it fails to correct the  */
  /* pointer, the illegal value is retained.                              */
  static void set_ignore_illegal_pointers(os_boolean) ;
  static os_boolean get_ignore_illegal_pointers() ;

  /* Use a optimization that doesn't checkpoint each phase. This          */
  /* optimization is on by default when the database is ~0.8 of the cache */
  /* size. Use this option with caution, since misuse could result in     */
  /* excessive page replacement and/or potential VM thrashing.            */
  static void set_optimize_checkpoints(os_boolean) ;
	
  /* Upgrade vectors to have vector headers as part of the evolution        */
  static void set_upgrade_vector_headers(os_boolean) ;
  
public: /* handlers for resumable errors */
  /*  The handler function for illegal pointers                         */
  static void set_illegal_pointer_handler(os_illegal_pointer_handler_fun) ;
  static void set_illegal_pointer_handler(os_illegal_pointer_to_member_handler_fun);
  
  /* handler for os_reference_local, os_reference_this_DB, reference_local */
  static void set_illegal_pointer_handler(os_illegal_reference_local_handler_fun);
  
  /* handler for os_reference */
  static void set_illegal_pointer_handler(os_illegal_reference_handler_fun);
  /* handler for os_old_reference */
  static void set_illegal_pointer_handler(os_illegal_old_reference_handler_fun);
  
  /* handler for os_database_root */
  static void set_illegal_pointer_handler(os_illegal_database_root_handler_fun);

  /* handler for indexes that have been made obsolete due to SE */
  static void set_obsolete_index_handler(os_obsolete_index_handler_fun) ;
  static os_obsolete_index_handler_fun get_obsolete_index_handler() ;

  /* handler for queries that have been made obsolete due to SE */
  static void set_obsolete_query_handler(os_obsolete_query_handler_fun) ;
  static os_obsolete_query_handler_fun get_obsolete_query_handler() ;

public: /* rudimentary interface to get at type and path strings */
  static char* path_name(const os_path&) ;

  /* returns a typed pointer to the object enclosing the pointer p */
  static os_typed_pointer_void get_enclosing_object(const void* p) ;
  
  /* obtains a path object describing the path from the enclosing class   */
  /* to the member indicated by p. If p is a pointer to an unenclosed     */
  /* primitive type it returns 0                                          */
  static os_path* get_path_to_member(const void* p) ;
	
public: /* internal functions that need to be public */
  /* get the unevolved and evolved tarnsient versions of the schema */
  static const class _OS_schema& _get_unevolved_schema() ;
  static const class _OS_schema& _get_evolved_schema() ;

  /* force only a schema installation */
  static void _set_force_schema_installation(os_boolean) ;

public: /* access to special versions-related things */
  static os_int32 get_explanation_level();
  static os_database * get_work_database();
} ;

#include <ostore/hdrend.hh>
#endif
