/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _MOP_H
#define _MOP_H
#include <ostore/hdrstart.hh>

#include <string.h>
#include <ostore/ostore.hh>
#include <ostore/semoptwk.hh>

#include <ostore/os_types/mopexc.hh>

#define NON_CONST_COERCIONS 1


/***************************************************************************
* 									   *
* 									   *
*     	   meta object protocol for schema access			   *
* 									   *
* 									   *
***************************************************************************/



/* forward declarations for all meta classes used to represent types */
class os_type ;
class os_void_type ;
class os_type_type ;
class os_indirect_type;
class os_named_indirect_type ;
class os_anonymous_indirect_type ;
class os_integral_type ;
class os_real_type ;
class os_pointer_type ;
class os_reference_type ;
class os_pointer_to_member_type ;
class os_array_type ;
class os_class_type ;
class os_template ;
class os_instantiated_class_type ;
class os_type_template ;
class os_enum_type ;
class os_function_type ;

/* forward definitions for meta classes used to represent components of   */
/* types                                                                  */
class os_base_class ;
class os_member ;
class os_member_variable ;
class os_field_member_variable ;
class os_relationship_member_variable ;
class os_member_function ;
class os_member_type ;
class os_member_namespace ;
class os_access_modifier ;
class os_literal ;
class os_enumerator_literal ;
class os_namespace ;
class os_pointer_literal ;
class os_pragma ;
      
class os_template_instantiation ;
class os_type_template;
class os_template_actual_arg ;
class os_template_formal_arg ;
class os_template_type_formal;
class os_template_value_formal ;
class os_type_template_actual_arg;
class os_literal_template_actual_arg;

class os_app_schema;
class os_comp_schema;
class os_database_schema;
class os_schema_options;

/* PT typedefs to facilitate deparametrization */
typedef os_Set<const os_class_type*> 		os_const_classes ;
typedef os_Set<os_class_type*> 			os_classes ;
typedef os_List<const os_class_type*> 		os_const_class_list ;
typedef os_List<os_class_type*> 		os_class_list ;

typedef os_List<const os_type*>			os_const_types ;
typedef os_List<const os_base_class*>		os_const_base_classes ;

typedef os_List<const os_member*>		os_const_members ;
typedef os_List<const os_template_actual_arg*> 	os_const_template_actual_args ;
typedef os_List<const os_template_formal_arg*> 	os_const_template_formal_args ;
typedef os_List<const os_enumerator_literal*>	os_const_enumerator_literals ;
typedef os_List<const os_pragma*>		os_const_pragmas ;


typedef os_List<os_type*>			os_types ;
typedef os_List<os_base_class*>			os_base_classes ;

typedef os_List<os_member*>			os_members ;
typedef os_List<os_template_actual_arg*> 	os_template_actual_args ;
typedef os_List<os_template_formal_arg*> 	os_template_formal_args ;
typedef os_List<os_enumerator_literal*>		os_enumerator_literals ;
typedef os_List<os_pragma*>			os_pragmas ;


/* Following kludgery mandated by C++ */
/* a device to prevent accidental allocation or copying of the class */

#ifdef _OS_VCPP_19
/* A Visual C++ bug causes a warning to be issued when the
 * const and non const versions of assignment operators or
 * copy constructors are defined.
 */
#pragma warning(disable : 4521 4522)
#endif

#define FACADE_CLASS(X) \
  public: \
    X(os_type&,os_type&,os_type&,os_type&,os_type&,os_type&,os_type&); \
  private: \
    void *operator new(size_t _OS_DBALLOC_PARMS) ; \
    void operator delete(void * _OS_DBALLOC_PARMS) ; \
    X(const X&); \
    X(X&); \
    X& operator = (const X&); \
    X& operator = (X&)

#define _OS_throw(X) 


/***************************************************************************
* 									   *
*                      mop level protocol				   *
* 									   *
***************************************************************************/

class os_schema;

class _OS_DLLIMPORT(_OS_MOP) os_mop : public os_facade
{
  FACADE_CLASS(os_mop);
public:
  /* Returns the schema currently bound. The bound schema is the
     schema in which dynamically created types are deposited. After
     initialization of schema services, the current schema is bound
     to the schema found in the transient database. */
  static os_schema& current ();
  static os_schema& get_transient_schema();

  /* Initializes the portion of schema services responsible for the
     access and construction of schema types through the mop interface. */
  static void initialize ();
  
  /* Reset the portion of schema services responsible for the access and 
     construction of schema types through the mop interface. After this
     operation, the current schema is empty. */
  static void reset ();

  /* Returns the os_type associated with the given name in the
     os_schema denoted by os_mop::current(). The type returned is
     suitable for dynamic type creation. Also, the type returned is
     limited to predefined types (integral and real) and classes.
     There is no mapping of a name to an os_enum_type or an
     os_named_indirect_type. If there is no associated os_type, 
     then 0 is returned. Note, for now os_mop::current() must be the 
     transient schema setup by os_mop::initialize(). */
  static os_type* find_type (const char* name);

  /* Returns the os_namespace associated with the given name in the 
     os_schema denoted by os_mop::current(). */
  static os_namespace* find_namespace (const char* name);

  /* Copy the given classes into the transient schema. If any of the
     given classes are not well-formed or aren't from the given schema
     or the given schema is the transient schema, an exception is raised. */
  static void copy_classes (const os_schema &schema, 
			    os_const_classes &classes) _OS_throw (err_mop);

  /* Copy the given classes into the transient schema. If any of the
     given classes are not well-formed or aren't from the given schema
     or the given schema is the transient schema, an exception is raised.
     This version protects the classes from being unbound; which is
     normally a very bad idea.  Use of this function can lead to schema
     corruption which cannot be repaired. */
  static void copy_classes_protected_from_unbind(const os_schema &schema, 
			    os_const_classes &classes) _OS_throw (err_mop);

  /* Initialize the compiler metadata (virtual function table
     pointers, virtual base class tables and pointers, etc) associated
     with an object.  The object instance may be transient or
     persistent, but the schema for its class must be in the
     application schema. */
  static void initialize_object_metadata(void *object,
					 const char *type_name);
  /* Allow initialization of database only types; which may not
     have their vftbl (etc.) available to the application if true.
     Database only types are normally not handled by
     initialize_object_metatdata() because the application
     does not have complete information about the type. */
  static void initialize_object_metadata(void *object,
      const char *type_name,os_boolean databaseonly);

  /* Protect classes from unbinding during bind.
     This is very dangerous and can lead to corrupt
     schema which cannot be fixed.  Don't use it. */
  static void protect_class_from_unbind(os_class_type* a_class);
  static void clear_protected_classes();

  /* bind the compilation schema */
  static void bind (os_schema_options* schema_options)
       _OS_throw (err_mop);

  /* bind the compilation schema for hetero usage */
  static void bind (const char* hetero_set,
		    os_schema_options* schema_options,
		    os_boolean make_neutral_changes,
		    os_boolean allow_schema_reorg,
		    os_char_p * neutral_output)
      _OS_throw (err_mop);

  /* bind the compilation schema for hetero usage with an option for the
     instantiated class type alignment adjustment & to allow size mismatch */
  static void bind (const char* hetero_set,
		    os_schema_options* schema_options,
		    os_boolean make_neutral_changes,
		    os_boolean allow_schema_reorg,
		    os_char_p * neutral_output,
		    os_unsigned_int32 align_and_allow_mismatch)
      _OS_throw (err_mop);

  /* following a call to bind, the function get_neutralized_classes()
     will return the classes that were not neutral and which required
     changes to be neutral.  */
  static os_classes get_neutralized_classes ();

  /* following a call to bind, the function get_failure_classes()
     will return the classes that were not neutral and for which no
     valid neutralization could be found. */
  static os_classes get_failure_classes ();

  /* Stack protocol for creating a temporary transient schema
     as the current schema for the access and construction of
     schema types through the mop interface, and then cleaning
     it up and popping back to the previous current schema
     when no longer needed.
     This is for OBJECTSTORE INTERNAL USE ONLY.
     It is currently only used by query translation. */
  static void push_transient_schema ();
  static void pop_transient_schema ();

  };

/***************************************************************************
* 									   *
*                      schema level protocol				   *
* 									   *
***************************************************************************/

class _OS_DLLIMPORT(_OS_MOP) os_schema : public os_facade
{
  FACADE_CLASS(os_schema);
public:

  enum os_schema_kind { Compilation_schema = 1, Application_schema, 
			Database_schema, os_schema_kind_pad = 1<<30 };

  os_schema_kind get_kind () const;

  /* returns the collection of all classes in the schema */
  os_const_classes get_classes() const ;
  /* returns the collection of all classes in dependency order */
  os_const_class_list get_partially_ordered_classes() const ;

  /* returns the meta description for the type with that name in the      */
  /* schema.  The name argument can be used to specify a class, or any of */
  /* the C++ fundamental types. All pointer types are treated identically */
  /* and return in "void*" being returned.  If there is no type           */
  /* associated with that name in the schema, it returns 0. For nested    */
  /* classes, the name must be a fully qualified name, that describes the */
  /* path to the nested class, eg.  outer::inner                          */
  const os_type* find_type(const char* name) const;

  /* Returns the os_namespace with the given name in the schema. */
  const os_namespace* find_namespace(const char *) const;

  /* Returns a meta schema if one can be found. Otherwise,
     signals an err_no_schema exception. */
  static const os_schema& get_meta_schema () _OS_throw (err_no_schema);

  /* Do a source level analysis of this schema. If the schema is
     bound, do a binding level analysis as well. If any errors are
     detected the appropriate exception is signalled. */
  void analyze () const _OS_throw (err_mop);

  /* Safe coercions to the appropriate actual schema type */
  operator const os_comp_schema&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_app_schema&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_database_schema&() const _OS_throw (err_mop_illegal_cast) ;

#if NON_CONST_COERCIONS
  /* Safe coercions to the appropriate actual schema type */
  operator os_comp_schema&() _OS_throw (err_mop_illegal_cast) ;
  operator os_app_schema&() _OS_throw (err_mop_illegal_cast) ;
  operator os_database_schema&() _OS_throw (err_mop_illegal_cast) ;
#endif /* NON_CONST_COERCIONS */

public:
  /* for ObjectStore internal use only */
  static void _enable_ossg_extensions();
} ;


/* Non-facade class */
class _OS_DLLIMPORT(_OS_MOP) os_schema_install_options
{
public:
  os_schema_install_options();

  void set_copy_member_functions (os_boolean);
  os_boolean get_copy_member_functions () const;

  /* For ObjectStore internal use only */
  void set_source_analysis_option(os_boolean);
  os_boolean get_source_analysis_option() const;
  void set_binding_analysis_option(os_boolean);
  os_boolean get_binding_analysis_option() const;

private:
  os_unsigned_int32 option_encoding;
};


class _OS_DLLIMPORT(_OS_MOP) os_comp_schema : public os_schema
{
  FACADE_CLASS(os_comp_schema);
public:
  /* returns the compilation schema stored in the database */
  static const os_comp_schema& get(const os_database &) _OS_throw (err_no_schema) ;

} ;


class _OS_DLLIMPORT(_OS_MOP) os_app_schema : public os_schema
{
  FACADE_CLASS(os_app_schema);
public:
  /* returns the application schema stored in the database */
  static const os_app_schema& get(const os_database &) _OS_throw (err_no_schema) ;
  static const os_app_schema& get() _OS_throw (err_no_schema) ;
} ;

class _OS_DLLIMPORT(_OS_MOP) os_database_schema : public os_schema
{
  FACADE_CLASS(os_database_schema);
public:
  /* returns the schema associated with the database. */
  static const os_database_schema& get(const os_database &)
    _OS_throw(err_no_schema) ;

  /* Returns the schema associated with the database ready
     for update. */
  static os_database_schema& get_for_update (const os_database&)
    _OS_throw(err_no_schema) ;

public:
  /* Install the given schema into this database schema. If any of the
     definitions conflict with the class definitions already present
     in the schema err_schema_validation_error is signaled.  */
  void install (os_schema &new_schema) 
      _OS_throw (err_schema_validation_error);
  /* Allow Install the given schema into this database schema. If any of the
     definitions conflict with the class definitions already present
     in the schema err_schema_validation_error is signaled.  */
  void install (os_schema &new_schema,
		os_schema_install_options const &install_opts) 
      _OS_throw (err_schema_validation_error);

public:
  /* for ObjectStore internal use only */
  const os_type* install_and_get_type(const char* name);
} ;


/***************************************************************************
* 									   *
*   			os_type protocol				   *
* 									   *
***************************************************************************/
/***************************************************************************
* 									   *
* the root of the abstract "type meta class hierarchy. Note that the	   *
* entire heirarchy is abstract, and that all of the protocol is actually   *
* implemented in terms of the repesentation heirarchy, which is not	   *
* exposed to client of MOP.						   *
* 									   *
***************************************************************************/
						       
class _OS_DLLIMPORT(_OS_MOP) os_type : public os_facade
{
  FACADE_CLASS(os_type);
public:	/* the protocol */
  enum os_type_kind
    {Undefined, Type, Void,

     Unsigned_char, Signed_char, Unsigned_short,
     Signed_short, Integer, Unsigned_integer,
     Signed_long, Unsigned_long,
		  
     Float, Double, Long_double,

     Named_indirect, Anonymous_indirect,

     Pointer, Reference, Pointer_to_member,
     
     Array, Class, Instantiated_class,
		  
     Enum, Function, 

     Char, Wchar_t, Bool_t,

     Integral_extension, Floating_extension,

     Last_type,
     os_type_kind_pad = 1<<30
     } ;
  /* returns an enumerator denoting the kind of this type expression node */
  os_type_kind get_kind() const ;
  static const char* get_kind_string(os_type_kind);
  
  os_boolean is_integral_type() const ;
  os_boolean is_real_type() const ;
  os_boolean is_class_type() const ;
  os_boolean is_pointer_type() const ;
  os_boolean is_indirect_type() const ;

  /* Returns true if the given type is not a user specified type. That
     is, the given type is a place holder and should be replaced by a
     user specified type. Otherwise, the given type is a user specified
     type and false is returned. */
  os_boolean is_unspecified () const;

  /* strips away any intervening "indirect_type" types, to get at the     */
  /* terminal type                                                        */
  const os_type& strip_indirect_types() const ;
  os_type& strip_indirect_types ();

  /* Returns the enclosing class if one exists, otherwise returns 0. */
  const os_class_type* get_enclosing_class () const;
  os_class_type* get_enclosing_class ();

  /* Returns the enclosing namespace if one exists, otherwise return 0. */
  const os_namespace* get_enclosing_namespace () const ;
  os_namespace* get_enclosing_namespace ();

  /* returns a new string containing a printable represention of the      */
  /* type.                                                                */
  char* get_string() const ;
  
  /* returns 1 if the type expression has the const type specifier */
  os_boolean is_const() const;

  /* returns 1 if the type expression has the volatile type specifier */
  os_boolean is_volatile() const;
  
  /* safe coercion operators. the err_mop_illegal_cast exception is       */
  /* signaled if the cast is illegal                                      */
  operator const os_void_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_type_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_indirect_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_named_indirect_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_anonymous_indirect_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_integral_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_real_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_pointer_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_reference_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_pointer_to_member_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_array_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_class_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_instantiated_class_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_enum_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_function_type&() const _OS_throw (err_mop_illegal_cast) ;

#if NON_CONST_COERCIONS
  /* safe coercion operators. the err_mop_illegal_cast exception is       */
  /* signaled if the cast is illegal                                      */
  operator os_void_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_type_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_indirect_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_named_indirect_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_anonymous_indirect_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_integral_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_real_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_pointer_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_reference_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_pointer_to_member_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_array_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_class_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_instantiated_class_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_enum_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_function_type&() _OS_throw (err_mop_illegal_cast) ;
#endif /* NON_CONST_COERCIONS */

  /* Returns a pointer to an os_type that describes the type associated   */
  /* with the address indicated by p. It treats all of persistent storage */
  /* as a tagged address space, and returns the type associated with any  */
  /* valid location in persistent store. It returns 0, if the location is */
  /* not a valid allocated persistent storage location, ie. it doesn't    */
  /* point to the start of a valid persistent object or sub-object within */
  /* such an object. When there is an ambiguity due to objects being      */
  /* co-located at the same address, it returns the type associated with  */
  /* the outermost enclosing type associated with the same location.      */

  static const os_type* type_at(const void* p) ;

  /* Returns a pointer to an os_type that describes the type associated   */
  /* with the address indicated by p. It treats all of persistent storage */
  /* as a tagged address space, and returns the type associated with any  */
  /* valid location in persistent store. It returns 0, if the location is */
  /* not a valid allocated persistent storage location, ie. it doesn't    */
  /* point to the start of a valid persistent object or sub-object within */
  /* such an object. When there is an ambiguity due to objects being      */
  /* co-located at the same address, it returns the type associated with  */
  /* the innermost enclosing type associated with the same location.      */

  static const os_type* innermost_type_at(const void* p) ;

  /* Returns a pointer to an os_type that describes the type associated   */
  /* with the outermost object that contains p. The argument p_container  */
  /* is modified to point to the containing object, and the return type   */
  /* is the type of the containing object. If the object was allocated as */
  /* an array, it returns a non-zero element_count indicating the number  */
  /* of elements in the array, and adjusts p_container to point to the    */
  /* first element ofthe array. In the above example os_type::typeof(p,   */
  /* pp, count) would have resulted in the meta object describing "class  */
  /* d" being returned, and the pointer pp being adjusted to point to the */
  /* enclosing "d" object.                                                */
  
  static const os_type* type_containing(const void*  p,
					os_void_const_p& p_container,
					os_unsigned_int32& element_count) ;

 /* Architecture and Compiler Dependent Information Accessors. */
 public:
  /* Returns the size (in bytes) of the type. */
  os_unsigned_int32 get_size() const _OS_throw (err_mop) ;

  /* Sets the size (in bytes) of the type. */
  void set_size (os_unsigned_int32 size) _OS_throw (err_mop);

  /* Returns the alignment associated with the type. */
  os_unsigned_int32 get_alignment() const _OS_throw (err_mop) ;

  /* Sets the alignment associated with the type. */
  void set_alignment (os_unsigned_int32 alignment) _OS_throw (err_mop);

} ;


/***************************************************************************
* 									   *
*   			fundamental types protocol			   *
* 									   *
***************************************************************************/

class _OS_DLLIMPORT(_OS_MOP) os_integral_type : public os_type
{
  FACADE_CLASS(os_integral_type);
public:
  os_boolean is_signed() const;

public:
  /* Each of the following returns the canonical representation for 
     the integral type. Note that this type should not be deleted by 
     the user. We don't return a pointer to const, since types passed 
     in to the dynamic type building must be non-const */
  static os_integral_type& create_signed_char();
  static os_integral_type& create_unsigned_char();
  static os_integral_type& create_defaulted_char(os_boolean sign);
  static os_integral_type& create_char();
  static os_integral_type& create_wchar_t();
  static os_integral_type& create_short(os_boolean sign);
  static os_integral_type& create_int(os_boolean sign);
  static os_integral_type& create_long(os_boolean sign);
  static os_integral_type& create(const char*);
} ;


class _OS_DLLIMPORT(_OS_MOP) os_real_type : public os_type
{
  FACADE_CLASS(os_real_type);
public:
  static os_real_type& create_float();
  static os_real_type& create_double();
  static os_real_type& create_long_double();
  static os_real_type& create(const char*);
} ;


class _OS_DLLIMPORT(_OS_MOP) os_void_type : public os_type
{
  FACADE_CLASS(os_void_type);
public:
  static os_void_type& create();
} ;


class _OS_DLLIMPORT(_OS_MOP) os_type_type : public os_type
{
  FACADE_CLASS(os_type_type);
public:
  static os_type_type& create();
} ;



/***************************************************************************
* 									   *
*   		     enumeration type protocol				   *
* 									   *
***************************************************************************/


class _OS_DLLIMPORT(_OS_MOP) os_enumerator_literal
{
  FACADE_CLASS(os_enumerator_literal);
public:
  const char* get_name() const ;
  os_int32 get_value() const ;

public:
  static os_enumerator_literal& create(const char*, os_int32) ;
			       
  void set_name(const char*) ;
  void set_value(os_int32) ;
} ;
  
      
class _OS_DLLIMPORT(_OS_MOP) os_enum_type : public os_type
{
  FACADE_CLASS(os_enum_type);
public:
  const char* get_name() const ;
  os_const_enumerator_literals get_enumerators() const ;

  /* get an enumerator literal that names the int; return 0 if there      */
  /* isn't one. If there is more than one enumerator with this value it   */
  /* returns the first one.                                               */
  const os_enumerator_literal* get_enumerator(os_int32) const ;

  void get_source_position (os_char_const_p &file, 
			    os_unsigned_int32 &line) const;

  void get_source_position (os_char_const_p &file) const;

  void get_source_position (const os_schema & schema,
			    os_char_const_p &file, 
			    os_unsigned_int32 &line) const;

  void get_source_position (const os_schema & schema,
			    os_char_const_p &file) const;

  os_const_pragmas get_pragmas() const;

public:
  static os_enum_type& create(const char* name, os_enumerator_literals&) ;
					 
  /* associates a name with the type */
  void set_name(const char* name) ;
  
  os_enumerator_literals get_enumerators();
  /* associate the enumerators supplied for the argument with the enum    */
  /* type                                                                 */
  void set_enumerators(os_enumerator_literals&) _OS_throw (err_mop) ;
  void set_source_position (const char *file, const os_unsigned_int32 line);

  os_pragmas get_pragmas() ;
  void set_pragmas (os_pragmas&) ;
} ;


/***************************************************************************
* 									   *
*                      indirect type protocol				   *
* 									   *
***************************************************************************/
      
class _OS_DLLIMPORT(_OS_MOP) os_indirect_type : public os_type
{
  FACADE_CLASS(os_indirect_type);
public:
  const os_type& get_target_type() const ;

public:
  os_type& get_target_type();
  void set_target_type(os_type&) ;
} ;


class _OS_DLLIMPORT(_OS_MOP) os_anonymous_indirect_type 
  : public os_indirect_type
{
  FACADE_CLASS(os_anonymous_indirect_type);
public:
  /* returns 1 if the type expression has the const type specifier */
  os_boolean is_const() const;

  /* returns 1 if the type expression has the volatile type specifier */
  os_boolean is_volatile() const;
  
public:
  static os_anonymous_indirect_type& create(os_type* target) ;
  
  void set_is_const(os_boolean);
  void set_is_volatile(os_boolean) ;
} ;


class _OS_DLLIMPORT(_OS_MOP) os_named_indirect_type : public os_indirect_type
{
  FACADE_CLASS(os_named_indirect_type);
public:
  const char* get_name() const ;

  void get_source_position (os_char_const_p &file, 
			    os_unsigned_int32 &line) const;

  void get_source_position (os_char_const_p &file) const;

  void get_source_position (const os_schema & schema,
			    os_char_const_p &file, 
			    os_unsigned_int32 &line) const;

  void get_source_position (const os_schema & schema,
			    os_char_const_p &file) const;

public:
  static os_named_indirect_type& create(os_type* target, const char*) ;
  
  void set_name(const char*) ;

  void set_source_position (const char *file, const os_unsigned_int32 line);
} ;


/***************************************************************************
* 									   *
*   			pointer type protocol				   *
* 									   *
***************************************************************************/

class _OS_DLLIMPORT(_OS_MOP) os_pointer_type: public os_type
{
  FACADE_CLASS(os_pointer_type);
public:
  const os_type& get_target_type() const ;

public:
  static os_pointer_type& create(os_type* target) ;
  os_type& get_target_type();
  void set_target_type(os_type&) ;

  /* Safe coercion operators.  The err_mop_illegal_cast exception is      */
  /* signaled if the cast is illegal.                                     */
  operator const os_pointer_to_member_type&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_reference_type&() const _OS_throw (err_mop_illegal_cast) ;

#if NON_CONST_COERCIONS
  operator os_pointer_to_member_type&() _OS_throw (err_mop_illegal_cast) ;
  operator os_reference_type&() _OS_throw (err_mop_illegal_cast) ;
#endif /* NON_CONST_COERCIONS */
} ;



class _OS_DLLIMPORT(_OS_MOP) os_pointer_to_member_type: public os_pointer_type
{
  FACADE_CLASS(os_pointer_to_member_type);
public:
  const os_class_type& get_target_class() const ;

public:
  static os_pointer_to_member_type& create(os_type* target,
					   os_class_type*) ;
  os_class_type& get_target_class();
  void set_target_class(os_class_type&) ;
} ;


class _OS_DLLIMPORT(_OS_MOP) os_reference_type : public os_pointer_type
{
  FACADE_CLASS(os_reference_type);
public:
  static os_reference_type& create(os_type* target) ;
} ;

class _OS_DLLIMPORT(_OS_MOP) os_pointer_literal : public os_facade
{
  FACADE_CLASS(os_pointer_literal);
public:
  const char* get_name() const ;
  os_pointer_type& get_type() const ;

public:
  static os_pointer_literal& create(const char*, os_pointer_type*) ;
			       
  void set_name(const char*) ;
  void set_type(os_pointer_type&) ;
} ;
  
      
/***************************************************************************
* 									   *
*   			os_array_type protocol				   *
* 									   *
***************************************************************************/


class _OS_DLLIMPORT(_OS_MOP) os_array_type : public os_type
{
  FACADE_CLASS(os_array_type);
public:
  os_unsigned_int32 get_number_of_elements() const ;
  os_unsigned_int32 get_number_of_base_elements() const ;
  const os_type& get_element_type() const ;
  const os_type& get_base_element_type() const ;
  os_unsigned_int32 get_number_of_dimensions() const ;

public:
  static os_array_type& create(os_unsigned_int32 number_of_elements,
			       os_type* element_type) ;
  void set_number_of_elements(os_unsigned_int32 number_of_elements) ;
  os_type& get_element_type();
  void set_element_type(os_type& element_type) ;
} ;



/***************************************************************************
* 									   *
*   			os_function_type protocol			   *
* 									   *
***************************************************************************/


class _OS_DLLIMPORT(_OS_MOP) os_function_type : public os_type
{
  FACADE_CLASS(os_function_type);
public:
  enum os_arg_list_kind { Unknown = 1, Known, Variable, os_arg_list_kind_pad = 1<<30 } ;

  os_arg_list_kind get_arg_list_kind() const ;
  os_const_types get_arg_list() const ;
  const os_type& get_return_type() const ;

public:
  static os_function_type& create(os_unsigned_int32   /* os_arg_list_kind */,
				  os_types &args, os_type* return_type);

  void set_arg_list_kind(os_unsigned_int32 /* os_arg_list_kind */) ;
  os_types get_arg_list();
  void set_arg_list(os_types&) ;
  os_type& get_return_type();
  void set_return_type(os_type&) ;
  os_boolean equal_signature(const os_function_type &other_func, 
                             os_boolean check_return_type = 0) const;
} ;
  


/***************************************************************************
* 									   *
*                    member protocol					   *
* 									   *
***************************************************************************/

class _OS_DLLIMPORT(_OS_MOP) os_member : public os_facade
{
  FACADE_CLASS(os_member);
public:
  enum os_member_kind
    {Variable=1, Function, Type, Access_modifier, Field_variable,
     Relationship, Namespace, os_member_kind_pad=1<<30} ;
  os_member_kind get_kind() const ;

  enum os_member_access { Public=1, Private, Protected, os_member_access_pad=1<<30 } ;
  os_member_access get_access() const ;

  /* returns the class defining this member */
  const os_class_type& get_defining_class() const;
  os_class_type& get_defining_class();
		  
  /* Returns true if the given member is not a user specified member. That
     is, the given member is a place holder and should be replaced by a
     user specified member. Otherwise, the given member is a user specified
     member and false is returned. */
  os_boolean is_unspecified () const;

  /* Safe coercions to the appropriate member type.  */
  operator const os_member_variable&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_field_member_variable&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_relationship_member_variable &() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_member_function &() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_member_type &() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_member_namespace &() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_access_modifier &() const _OS_throw (err_mop_illegal_cast) ;
#if NON_CONST_COERCIONS
  /* Safe coercions to the appropriate member type.  */
  operator os_member_variable&() _OS_throw (err_mop_illegal_cast) ;
  operator os_field_member_variable&() _OS_throw (err_mop_illegal_cast) ;
  operator os_relationship_member_variable &() _OS_throw (err_mop_illegal_cast) ;
  operator os_member_function &() _OS_throw (err_mop_illegal_cast) ;
  operator os_member_type &() _OS_throw (err_mop_illegal_cast) ;
  operator os_member_namespace &() _OS_throw (err_mop_illegal_cast) ;
  operator os_access_modifier &() _OS_throw (err_mop_illegal_cast) ;
#endif /* NON_CONST_COERCIONS */
  
public:
  void set_access(os_unsigned_int32 /* os_member_access */) _OS_throw (err_mop);
} ;

/***************************************************************************
* 									   *
*                      os_class protocol				   *
* 									   *
***************************************************************************/

class _OS_DLLIMPORT(_OS_MOP) os_class_type : public os_type
{
  FACADE_CLASS(os_class_type);
public:
  enum os_class_kind { Class, Struct, Union, Anonymous_union, os_class_kind_pad = 1<<30 } ;
  enum os_microsoft_declspec_kind { No_declspec=0, Ms_dllimport, Ms_dllexport, os_microsoft_declspec_kind_pad=1<<30 } ;

  os_class_kind get_class_kind() const ;
  
  const char* get_name() const;
  /* returns true if it is a forward class definition in the schema */
  os_boolean is_forward_definition() const ;
  /* returns true iff it is a template class used for instantiating other */
  /* classes */
  os_boolean is_template_class() const ;

  /* is a candidate for persistent allocation */
  os_boolean is_persistent() const ;

  /* is the class abstract */
  os_boolean is_abstract() const ;

  /* get the microsoft declspec enum bits */
  os_microsoft_declspec_kind get_microsoft_declspec () const;

  /* returns a list of base classes in declaration order */
  os_const_base_classes get_base_classes() const
    _OS_throw(err_mop_forward_definition);

  /* returns the base class by that name, if it is a direct nonvirtual base class */
  /* of this class or any virtual base						  */
  const os_base_class* find_base_class(const char* name) const
    _OS_throw(err_mop_forward_definition); 
		     
  /* returns the list of virtual base classes whose storage is allocated  */
  /* as part of this class for an object of this type                     */
  os_const_base_classes get_allocated_virtual_base_classes() const
    _OS_throw (err_mop_forward_definition) ;
   
  /* returns a list of indirect virtual base classes */
  os_const_base_classes get_indirect_virtual_base_classes() const
    _OS_throw(err_mop_forward_definition);

  /* returns the list of members(data, function, and type in declaration  */
  /* order                                                                */
  os_const_members get_members() const _OS_throw(err_mop_forward_definition) ;

  /* returns a member variable by that name, if it is a direct member of 
     the class */
  const os_member_variable* find_member_variable (const char* name) const;

  const os_member_variable* get_backpointer(os_unsigned_int32& offset) const;

  os_const_pragmas get_pragmas() const;

  os_boolean declares_get_os_typespec_function () const;
  os_member::os_member_access get_access_of_get_os_typespec_function () const;
  os_boolean defines_virtual_functions () const;
  os_boolean introduces_virtual_functions () const;

  void get_source_position (os_char_const_p &file, 
			    os_unsigned_int32 &line) const;

  void get_source_position (os_char_const_p &file) const;

  void get_source_position (const os_schema & schema,
			    os_char_const_p &file, 
			    os_unsigned_int32 &line) const;

  void get_source_position (const os_schema & schema,
			    os_char_const_p &file) const;

  /* Returns a reference to an os_class_type that describes the type 
     associated with the most derived object that contains the given object. 
     The argument most_derived_object is modified to point to the most derived
     object containing the given object, and the return type is the type of 
     the most derived class. If the most derived class can not be determined 
     or the outermost type is not a class, an exception is raised. */
  
  static const os_class_type& get_most_derived_class
      (const void *object, os_void_const_p &most_derived_object);

  /* does the class have any user defined constructor */
  os_boolean has_constructor() const ;

  /* does the class have any user defined destructor */
  os_boolean has_destructor() const ;

public:
  static os_class_type& create(const char* name);
  static os_class_type& create(const char* name, os_base_classes&, os_members&,
			       os_boolean defines_virtual_functions) ;
  void set_class_kind(os_unsigned_int32 /* os_class_kind */) ;
  void set_name(const char*) ;
  void set_is_forward_definition(os_boolean) ;
  void set_is_persistent(os_boolean) ;
  void set_is_abstract(os_boolean) ;
  void set_defines_virtual_functions(os_boolean) ;
  void set_introduces_virtual_functions(os_boolean) ;
  os_base_classes get_base_classes()
    _OS_throw(err_mop_forward_definition);
  os_base_classes get_allocated_virtual_base_classes()
    _OS_throw (err_mop_forward_definition);
  os_base_class* find_base_class(const char* name)
    _OS_throw(err_mop_forward_definition); 
  void set_base_classes(os_base_classes&) ;
  os_base_classes get_indirect_virtual_base_classes()
    _OS_throw(err_mop_forward_definition);
  /* This function should only be called after the direct bases of
     a class have been set. */
  void set_indirect_virtual_base_classes (os_base_classes&);
  os_members get_members() _OS_throw(err_mop_forward_definition);
  os_member_variable* find_member_variable (const char* name);
  void set_members(os_members&) ;
  os_pragmas get_pragmas() ;
  void set_pragmas (os_pragmas&) ;
  void set_declares_get_os_typespec_function (os_boolean);
  void set_access_of_get_os_typespec_function (os_unsigned_int32 /*os_member_access*/);
  void set_source_position (const char *file, const os_unsigned_int32 line);

  void set_has_constructor(os_boolean) ;
  void set_has_destructor(os_boolean) ;

  /* set the microsoft declspec enum bits */
  void set_microsoft_declspec (os_unsigned_int32 /* os_microsoft_declspec_kind */ );

 /* Architecture and Compiler Dependent Information Accessors. */
 public:
  /* returns true if it has a dispatch table */
  os_boolean has_dispatch_table() const _OS_throw (err_mop_forward_definition);
  
  /* returns the offset at which the pointer to the dispatch table is     */
  /* stored. It signals err_mop if !has_dispatch_table()                  */
  os_int32 get_dispatch_table_pointer_offset() const
    _OS_throw(err_mop_forward_definition) ;
  
  void set_dispatch_table_pointer_offset (os_int32 offset);

  os_unsigned_int32 get_size_as_base () const;

  /* Safe coercions */
  operator const os_instantiated_class_type&() const _OS_throw (err_mop_illegal_cast) ;

#if NON_CONST_COERCIONS
  operator os_instantiated_class_type&() _OS_throw (err_mop_illegal_cast) ;
#endif /* NON_CONST_COERCIONS */

 public:
  /* internal class binding functions */

  /* self pointers */
  os_boolean _has_self_pointer() const _OS_throw (err_mop_forward_definition);
  os_int32 _get_self_pointer_offset() const
    _OS_throw(err_mop_forward_definition) ;
  void _set_self_pointer_offset (os_int32 offset);

  /* virtual base table pointers */
  os_boolean _has_virtual_base_table_pointer() const
    _OS_throw (err_mop_forward_definition);
  os_int32 _get_virtual_base_table_pointer_offset() const
    _OS_throw(err_mop_forward_definition) ;
  void _set_virtual_base_table_pointer_offset (os_int32 offset);

  /* construction displacement members */
  void _set_construction_displacement_offset (os_int32 offset,
					      os_base_class& base);
public:
  /* for ObjectStore internal use only */
  os_boolean is_name_place_holder_class() const;
} ;



class _OS_DLLIMPORT(_OS_MOP) os_instantiated_class_type 
   : public os_class_type
{
  FACADE_CLASS(os_instantiated_class_type);
public:
  const os_template_instantiation& get_instantiation() const
    _OS_throw (err_mop_forward_definition) ;

public:
  static os_instantiated_class_type& create(const char* name);
  static os_instantiated_class_type&
      create(const char* name, os_base_classes&, os_members&,
	     os_template_instantiation*, os_boolean defines_virtual_functions);
  os_template_instantiation& get_instantiation()
    _OS_throw (err_mop_forward_definition);
  void set_instantiation(os_template_instantiation&) ;
public:
  /* for ObjectStore internal use only */
  os_boolean is_pseudo_instantiation() const;
} ;
      

/***************************************************************************
* 									   *
* 		   os_namespace protocol				   *
* 									   *
***************************************************************************/

class _OS_DLLIMPORT(_OS_MOP) os_namespace : public os_facade
{
  FACADE_CLASS(os_namespace);
public:
  static os_namespace& create(const char* name);
  static os_namespace& create(const char* name, os_members&) ;

  /* Returns the enclosing namespace if one exists, otherwise return 0. */
  const os_namespace* get_enclosing_namespace () const ;
  os_namespace* get_enclosing_namespace ();

  const char* get_name () const ;
  os_members get_members () ;
  os_const_members get_members () const ;

  void set_name(const char*) ;
  void set_members(os_members&) ;
};


/***************************************************************************
* 									   *
* 		   base class protocol					   *
* 									   *
***************************************************************************/

class _OS_DLLIMPORT(_OS_MOP) os_base_class : public os_facade
{
  FACADE_CLASS(os_base_class);
public:
  const os_class_type& get_class() const ;
  
  enum os_base_access { Public=1, Private, Protected, os_base_access_pad=1<<30 } ;
  os_base_access get_access() const ;

  /* true if this is a virtual base class definition */
  os_boolean is_virtual() const ;
  
  /* the offset to this class relative to the defining class. For virtual */
  /* base classes this offset is only meaningful if the base class was    */
  /* obtained via a call to get_allocated_virtual_base_classes            */
  os_unsigned_int32 get_offset() const ;

  /* Return the offset of this virtual base class (this os_base_class must
     be virtual) within the given most derived class. */
  os_unsigned_int32 get_offset (const os_class_type &most_derived_class) const;

  os_unsigned_int32 get_size () const;

  /* True if any virtual functions inherited from this base class are
     overridden by the derived class */
  os_boolean virtuals_redefined () const ;

public:
  static os_base_class& create(os_unsigned_int32 /* os_base_access */,
			       os_boolean is_virtual, os_class_type*) ;
  void set_access(os_unsigned_int32 /* os_base_access */) ;
  /* Not yet implemented
  void set_is_virtual(os_boolean) ;
  */
  os_class_type& get_class();
  void set_class(os_class_type&) ;
  void set_offset(os_unsigned_int32) ;
  void set_virtuals_redefined (os_boolean) ;

 public:
  os_unsigned_int32 get_virtual_base_class_pointer_offset () const
      _OS_throw (err_mop);
  void set_virtual_base_class_pointer_offset (os_unsigned_int32 offset)
      _OS_throw (err_mop);
  void set_virtual_base_class_no_pointer () _OS_throw (err_mop);
  os_boolean virtual_base_class_has_pointer() const _OS_throw (err_mop);
} ;


/***************************************************************************
* 									   *
*                    member implementations				   *
* 									   *
***************************************************************************/

class _OS_DLLIMPORT(_OS_MOP) os_member_variable : public os_member
{
  FACADE_CLASS(os_member_variable);
public:
  /* the name associated with the member */
  const char* get_name() const ;

  /* the type associated with the member */
  const os_type& get_type() const ;
  
  /* the size in bytes */
  os_unsigned_int32 get_size() const _OS_throw (error_mop) ;
  
  /* the offset to the data member relative to the defining class */
  os_unsigned_int32 get_offset() const _OS_throw (error_mop) ;
		  
  enum os_storage_class { Regular, Persistent, Static, os_storage_class_pad=1<<30 } ;

  os_storage_class get_storage_class () const;

  /* attributes of interest */
  /* true iff the member is a bit field */
  os_boolean is_field() const ;
  /* true iff it is a static data member */
  os_boolean is_static() const ;
  /* true iff it is a persistent data member */
  os_boolean is_persistent() const ;

  void get_source_position (os_char_const_p &file, 
			    os_unsigned_int32 &line) const;

  void get_source_position (os_char_const_p &file) const;

  void get_source_position (const os_schema & schema,
			    os_char_const_p &file, 
			    os_unsigned_int32 &line) const;

  void get_source_position (const os_schema & schema,
			    os_char_const_p &file) const;

public:
  static os_member_variable& create(const char* name, os_type* type) ;
  void set_name(const char* name) ;
  os_type& get_type() ;
  void set_type(os_type& type) ;
  void set_storage_class(os_unsigned_int32) ;
  void set_offset(os_unsigned_int32) ;
  void set_source_position (const char *file, const os_unsigned_int32 line);

  /* Safe coercions */
  operator const os_field_member_variable&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_relationship_member_variable&() const _OS_throw (err_mop_illegal_cast) ;

#if NON_CONST_COERCIONS
  operator os_field_member_variable&() _OS_throw (err_mop_illegal_cast) ;
  operator os_relationship_member_variable&() _OS_throw (err_mop_illegal_cast) ;
#endif /* NON_CONST_COERCIONS */
} ;


/* Returns a pointer to the base class or member, as specified by the     */
/* argument given the pointer to the directly enclosing class in the      */
/* argument "p"                                                           */
_OS_DLLIMPORT(_OS_MOP) void *os_fetch_address(void* p, const os_member_variable&) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void *os_fetch_address(void* p, const os_base_class&);


/* functions to fetch and store primitive values into member variables    */
/* Sam:: please **DO NOT** convert the following to port types. They are  */
/* correct as they stand in terms of the native C++ types                 */

/* fetch and store pointer values */

_OS_DLLIMPORT(_OS_MOP) void* os_fetch
(const void* p, const os_member_variable&, os_void_p& value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const void* value) _OS_throw (err_mop) ;

/* signed and unsigned integral values */

_OS_DLLIMPORT(_OS_MOP) unsigned long os_fetch
(const void* p, const os_member_variable&, unsigned long& value)
     _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) long os_fetch
(const void* p, const os_member_variable&, long& value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const unsigned long value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const long value) _OS_throw (err_mop) ;

/* int */
_OS_DLLIMPORT(_OS_MOP) unsigned int os_fetch
(const void* p, const os_member_variable&, unsigned int& value)
     _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) int os_fetch
(const void* p, const os_member_variable&, int& value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const  unsigned int value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const int value) _OS_throw (err_mop) ;

/* short */
_OS_DLLIMPORT(_OS_MOP) unsigned short os_fetch
(const void* p, const os_member_variable&, unsigned short& value)
     _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) short os_fetch
(const void* p, const os_member_variable&, short& value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const  unsigned short value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const short value) _OS_throw (err_mop) ;

/* char */
_OS_DLLIMPORT(_OS_MOP) unsigned char os_fetch
(const void* p, const os_member_variable&, unsigned char& value)
     _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) signed char os_fetch
(const void* p, const os_member_variable&, signed char& value)
     _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) char os_fetch
(const void* p, const os_member_variable&, char& value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const  unsigned char value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const  signed char value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const char value) _OS_throw (err_mop) ;

/* wchar_t */
_OS_DLLIMPORT(_OS_MOP) wchar_t os_fetch
(const void* p, const os_member_variable&, wchar_t& value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const wchar_t value) _OS_throw (err_mop) ;

/* float */
_OS_DLLIMPORT(_OS_MOP) float os_fetch
(const void* p, const os_member_variable&, float& value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const float value) _OS_throw (err_mop) ;

/* double */
_OS_DLLIMPORT(_OS_MOP) double os_fetch
(const void* p, const os_member_variable&, double& value) _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const double value) _OS_throw (err_mop) ;

#ifdef _OS_MicrosoftCC
/* disable  the long double same precision as double warning */
#pragma warning(disable : 4069)
#endif

/* long double */
_OS_DLLIMPORT(_OS_MOP) long double os_fetch
(const void* p, const os_member_variable&, long double& value)
     _OS_throw (err_mop) ;
_OS_DLLIMPORT(_OS_MOP) void os_store (void* p, const os_member_variable&,
	       const long double value) _OS_throw (err_mop) ;
	       

class _OS_DLLIMPORT(_OS_MOP) os_field_member_variable 
  : public os_member_variable
{
  FACADE_CLASS(os_field_member_variable);
public:
  /* the size in bits occupied by the member.  */
  os_unsigned_int8 get_size() const ;

  /* the offset in bytes and bits to the data member relative to the      */
  /* defining class                                                       */
  void get_offset(os_unsigned_int32& bytes, os_unsigned_int8& bits) const ;

public:
  static os_field_member_variable& create(const char* name, os_type* type,
					  os_unsigned_int8 size_in_bits) ;
  void set_size(os_unsigned_int8 size_in_bits) ;
  void set_offset(os_unsigned_int32 bytes, os_unsigned_int8 bits);
} ;



class _OS_DLLIMPORT(_OS_MOP) os_relationship_member_variable 
  : public os_member_variable
{
  FACADE_CLASS(os_relationship_member_variable);
public:
  const os_class_type& get_related_class() const ;
  const os_relationship_member_variable& get_related_member() const ;

public:
  static os_relationship_member_variable& create
      (const char* name, const os_type*  type,
       const os_class_type* related_class,
       const os_relationship_member_variable* related_member);

  os_class_type& get_related_class();
  void set_related_class(os_class_type&) ;
  os_relationship_member_variable& get_related_member();
  void set_related_member_variable(os_relationship_member_variable&);
};


class _OS_DLLIMPORT(_OS_MOP) os_member_function : public os_member
{
  FACADE_CLASS(os_member_function);
public:
  /* the name associated with the member */
  const char* get_name() const ;

  /* attributes */
  os_boolean is_inline() const ;
  os_boolean is_static() const ;
  os_boolean is_pure_virtual() const ;
  os_boolean is_virtual() const ;
  os_boolean is_overloaded() const ;
  os_boolean is_const() const ;
  os_boolean is_volatile() const ;
  
  const os_function_type& get_type() const ;

  enum os_function_kind { Regular,
			  /* applicable only if it is a member function */
			  Constructor, Destructor, 
			  Cast_op, /* the return type gives the cast type */
			  /* the operators that can be overloaded */
			  New_op, Delete_op,
			  Plus_op, Minus_op, Mul_op, Div_op, Mod_op,
			  Xor_op, And_op, Or_op, Comp_op,
			  Not_op, Assign_op, Lt_op, Gt_op,
			  Plus_assign_op, Minus_assign_op, Mul_assign_op,
			  Div_assign_op, Mod_assign_op,
			  Xor_assign_op, And_assign_op, Or_assign_op,
			  Lsh_op, Rsh_op, 
			  Lsh_assign_op, Rsh_assign_op,
			  Eq_op, Neq_op, Le_op, Ge_op,
			  And_and_op, Or_or_op,
			  Inc_op, Dec_op, Comma_op,
			  Member_deref_op, Deref_op,
			  Paren_op, Subscript_op,
			  Vec_new_op, Vec_delete_op,
			  os_function_kind_pad=1<<30 };

  os_function_kind get_function_kind () const;

  enum os_call_linkage { No_linkage, C_linkage, C_plus_plus_linkage,
			 Fortran_linkage, os_call_linkage_pad=1<<30 };

  os_call_linkage get_call_linkage () const;

  void get_source_position (os_char_const_p &file, 
			    os_unsigned_int32 &line) const;

  void get_source_position (os_char_const_p &file) const;

  void get_source_position (const os_schema & schema,
			    os_char_const_p &file, 
			    os_unsigned_int32 &line) const;

  void get_source_position (const os_schema & schema,
			    os_char_const_p &file) const;

public:
  static os_member_function& create(const char* name, os_function_type*) ;

  void set_name(const char* name) ;
  os_function_type& get_type() ;
  void set_type(os_function_type&) ;
  
  void set_is_inline(os_boolean) ;
  void set_is_static(os_boolean) ;
  void set_is_pure_virtual(os_boolean) ;
  void set_is_virtual(os_boolean) ;
  void set_is_overloaded(os_boolean) ;
  void set_is_const(os_boolean) ;
  void set_is_volatile(os_boolean) ;

  void set_function_kind (os_function_kind);
  void set_call_linkage (os_call_linkage);

  void set_source_position (const char *file, const os_unsigned_int32 line);
} ;


  
class _OS_DLLIMPORT(_OS_MOP) os_member_type : public os_member
{
  FACADE_CLASS(os_member_type);
public:
  const os_type& get_type() const ;

public:
  static os_member_type& create(os_type*) ;

  os_type& get_type() ;
  void set_type(os_type&) ;
} ;



class _OS_DLLIMPORT(_OS_MOP) os_member_namespace : public os_member
{
  FACADE_CLASS(os_member_namespace);
public:
  const os_namespace& get_namespace() const ;

public:
  static os_member_namespace& create(os_namespace*) ;

  os_namespace& get_namespace() ;
  void set_namespace(os_namespace&);
} ;



class _OS_DLLIMPORT(_OS_MOP) os_access_modifier : public os_member
{
  FACADE_CLASS(os_access_modifier);
public:
  /* returns the member whose access was modified */
  const os_member &get_base_member() const ;

public:
  static os_access_modifier& create(os_member*) ;

  os_member &get_base_member();
  void set_base_member(os_member&) ;
} ;


/***************************************************************************
* 									   *
* 			parameterized type protocol			   *
* 									   *
***************************************************************************/


class _OS_DLLIMPORT(_OS_MOP) os_template_instantiation : public os_facade
{
  FACADE_CLASS(os_template_instantiation);
public:
  /* obtain the template that was instantiated */
  const os_template& get_template() const ;
  /* obtain the list of actual arguments used to instantiate the template */
  os_const_template_actual_args get_args() const ;

public:
  static os_template_instantiation& create(os_template*,
					   os_template_actual_args*) ;
  os_template& get_template();
  void set_template(os_template&) ;
  os_template_actual_args get_args();
  void set_args(os_template_actual_args&) ;
} ;


class _OS_DLLIMPORT(_OS_MOP) os_template : public os_facade
{
  FACADE_CLASS(os_template);
public:
  enum os_template_kind { Type = 1, Function, os_template_kind_pad = 1<<30 } ;
  os_template_kind kind() const ;
  os_template_kind get_kind() const ;

  /* obtain the list of formal arguments to the template */
  os_const_template_formal_args get_args() const ;
  /* Safe coercions to the appropriate template kind */
  operator const os_type_template&() const _OS_throw (err_mop_illegal_cast) ;
  /* Safe coercions to the appropriate template kind */
#if NON_CONST_COERCIONS
  operator os_type_template&() _OS_throw (err_mop_illegal_cast) ;
#endif /* NON_CONST_COERCIONS */

  /* Returns true if the given template is not a user specified template. That
     is, the given template is a place holder and should be replaced by a
     user specified template. Otherwise, the given template is a user specified
     template and false is returned. */
  os_boolean is_unspecified () const;

public:
  os_template_formal_args get_args();
  void set_args(os_template_formal_args&) ;
} ;

class os_template_arg_map; // A class similar to a simple os_Dictionary

class _OS_DLLIMPORT(_OS_MOP) os_type_template : public os_template
{
  FACADE_CLASS(os_type_template);
public:
  /* return the type being parameterized */
  const os_type& get_type() const ;

public:
  static os_type_template& create(os_type*, os_template_formal_args&) ;
  os_type& get_type();
  void set_type(os_type&) ;
  //
  // instantiate_class() will only work if the os_type_template and
  //  all it's parts are already in the transient schema.
  //  You may wish to clear is_persistent before merging the schema,
  //   you may also wish to mark the instantiated class as persistent.
  //  If the os_type_template is not an os_class_type then NULL
  //  will be returned.
  // Note: Literal template arguments are not supported by ossg and
  //  might not be sucessfully instantiated by the current implementation
  //  of instantiate_class.
  //
  os_instantiated_class_type* instantiate_class(os_template_actual_args* args);
protected:
   // The protected instantiations cannot be made public
   //  until os_template_arg_map is replaced with an os_Dictionary.
  os_instantiated_class_type* instantiate_class(os_class_type* type,os_template_arg_map& map,
      os_template_instantiation* template_instantiation);
  os_class_type* instantiate_class(os_class_type* type,os_template_arg_map& map);
  os_base_class* instantiate_base_class(os_base_class* base,os_template_arg_map& map);
  os_base_classes* instantiate_base_classes(os_base_classes*,os_template_arg_map&);
  os_member_variable* instantiate_member_variable(os_member_variable* member,
                                                 os_template_arg_map& map);
  os_field_member_variable* instantiate_field_member_variable(os_field_member_variable* member,
                                                 os_template_arg_map& map);
  os_relationship_member_variable* instantiate_relationship_member_variable(
                                                 os_relationship_member_variable* member,
                                                 os_template_arg_map& map);
  os_member_function* instantiate_member_function(os_member_function* member,
                                                 os_template_arg_map& map);
  os_member_type* instantiate_member_type(os_member_type* member,
                                                 os_template_arg_map& map);
  os_access_modifier* instantiate_member_access_modifier(os_access_modifier* member,
                                                 os_template_arg_map& map);
  os_member* instantiate_member(os_member*,os_template_arg_map&);
  os_members* instantiate_members(os_members*,os_template_arg_map&);
} ;

class _OS_DLLIMPORT(_OS_MOP) os_template_formal_arg : public os_facade
{
  FACADE_CLASS(os_template_formal_arg);
public:
  enum os_template_formal_arg_kind { Type, Value, os_template_formal_arg_kind_pad = 1<<30 };
  os_template_formal_arg_kind get_kind () const;
  const char* get_name () const;
public:
  void set_name (const char *name);

  /* Safe coercions to the appropriate formal arg type */
  operator const os_template_type_formal&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_template_value_formal&() const _OS_throw (err_mop_illegal_cast) ;
#if NON_CONST_COERCIONS
  /* Safe coercions to the appropriate formal arg type */
  operator os_template_type_formal&() _OS_throw (err_mop_illegal_cast) ;
  operator os_template_value_formal&() _OS_throw (err_mop_illegal_cast) ;
#endif /* NON_CONST_COERCIONS */
};


class _OS_DLLIMPORT(_OS_MOP) os_template_type_formal 
	: public os_template_formal_arg
{
  FACADE_CLASS(os_template_type_formal);
public:
  static os_template_type_formal& create (const char *name);
};


class _OS_DLLIMPORT(_OS_MOP) os_template_value_formal 
	: public os_template_formal_arg
{
  FACADE_CLASS(os_template_value_formal);
public:
  const os_type& get_type () const;
public:
  static os_template_value_formal& create (const char *name, os_type *type);
  os_type& get_type ();
  void set_type (os_type&);
};


/***************************************************************************
* 									   *
*   			Template actual arg protocol			   *
* 									   *
***************************************************************************/

class _OS_DLLIMPORT(_OS_MOP) os_template_actual_arg : public os_facade
{
  FACADE_CLASS(os_template_actual_arg);
public:
  enum os_template_actual_arg_kind { type_actual, literal_actual, os_template_actual_arg_kind_pad = 1<<30 } ;
  os_template_actual_arg_kind get_kind() const ;
  /* Safe coercions to the appropriate acual arg type */
  operator const os_type_template_actual_arg&() const _OS_throw (err_mop_illegal_cast) ;
  operator const os_literal_template_actual_arg&() const _OS_throw (err_mop_illegal_cast) ;

#if NON_CONST_COERCIONS
  /* Safe coercions to the appropriate acual arg type */
  operator os_type_template_actual_arg&() _OS_throw (err_mop_illegal_cast) ;
  operator os_literal_template_actual_arg&() _OS_throw (err_mop_illegal_cast) ;
#endif /* NON_CONST_COERCIONS */
} ;

class _OS_DLLIMPORT(_OS_MOP) os_type_template_actual_arg 
  : public os_template_actual_arg
{
  FACADE_CLASS(os_type_template_actual_arg);
public:
  /* returns the type bound to the template actual argument */
  const os_type &get_type() const ;
public:
  static os_type_template_actual_arg& create(os_type*) ;
  os_type &get_type();
  void set_type(os_type&) ;
};


class _OS_DLLIMPORT(_OS_MOP) os_literal_template_actual_arg 
  : public os_template_actual_arg
{
  FACADE_CLASS(os_literal_template_actual_arg);
public:
  const os_literal& get_literal () const;
public:
  static os_literal_template_actual_arg& create (os_literal*);
  os_literal& get_literal ();
  void set_literal (os_literal&);
};


/***************************************************************************
* 									   *
*   			    Literal protocol			           *
* 									   *
***************************************************************************/

class _OS_DLLIMPORT(_OS_MOP) os_literal : public os_facade
{
  FACADE_CLASS(os_literal);
public:
  enum os_literal_kind {
    Unused_literal,
    Enumerator_literal, Function_literal, Function_literal_template,
    Unsigned_char_literal, Signed_char_literal,
    Unsigned_short_literal, Signed_short_literal,
    Integer_literal, Unsigned_integer_literal,
    Signed_long_literal, Unsigned_long_literal,
    Char_literal, Pointer_literal, Wchar_t_literal,
    Last_literal, os_literal_kind_pad = 1<<30 };
  os_literal_kind get_kind () const;
  const os_type& get_type () const;
  os_type& get_type ();
  /* Returns true if the given literal is not a user specified literal. That
     is, the given literal is a place holder and should be replaced by a
     user specified literal. Otherwise, the given literal is a user specified
     literal and false is returned. */
  os_boolean is_unspecified () const;
  public:
  static os_literal& create_char (char);
  static os_literal& create_wchar_t (wchar_t);
  static os_literal& create_signed_char (signed char);
  static os_literal& create_unsigned_char (unsigned char);
  static os_literal& create_signed_short (signed short);
  static os_literal& create_unsigned_short (unsigned short);
  static os_literal& create_signed_int (signed int);
  static os_literal& create_unsigned_int (unsigned int);
  static os_literal& create_signed_long (signed long);
  static os_literal& create_unsigned_long (unsigned long);
  static os_literal& create_enum_literal (os_enumerator_literal&);
  static os_literal& create_pointer_literal (os_pointer_literal&);
public:
  char get_char_value () const;
  wchar_t get_wchar_t_value () const;
  long get_signed_integral_value () const;
  unsigned long get_unsigned_integral_value () const;
  const os_enumerator_literal& get_enum_literal () const;
  const os_pointer_literal& get_pointer_literal () const;
  os_enumerator_literal& get_enum_literal ();
  os_pointer_literal& get_pointer_literal ();
};

/***************************************************************************
* 									   *
*   			    Pragma protocol			           *
* 									   *
***************************************************************************/


class _OS_DLLIMPORT(_OS_MOP) os_pragma : public os_facade
{
  FACADE_CLASS(os_pragma);
public:
  const char* get_string () const;
  /* Returns true if the given pragma is not a recognized pragma.
     Unrecognized pragmas have no effect on schema binding, but may
     be useful for the user. */
  os_boolean is_recognized () const;
public:
  static os_pragma& create (const char* string);

};

/***************************************************************************
* 									   *
*   			    Schema options			           *
* 									   *
***************************************************************************/


class _OS_DLLIMPORT(_OS_MOP) os_schema_options : public os_facade
{
  FACADE_CLASS(os_schema_options);
public:
  static os_schema_options& create (const char* filename);
  static os_schema_options& create ();

  void add_option_line (const char* line);

  void destroy ();
};

#ifdef _OS_DECCXX
#undef wchar_t
#endif

#include <ostore/hdrend.hh>
#endif /* _MOP_H */
