/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _DSXREP_HH
#define _DSXREP_HH

#include <llpl.hh>
#include <ostore/mop.hh>
#include <os_types/os_basic.hh>
#include <os_types/osutils.hh>
#include <os_types/osthashf.hh>
os4u _ODI_hash_hash_function(void* const v);
os4 _ODI_hash_compare_function(void* const v1, void* const v2);
#include <phash.hh>
#include <os_types/xarray.hh>
#include <ostore/coll.hh>

class _Dsxrep_token;
class _Node_table;
class _Source_position;
class _Wrapped_int32;

class os_forward_class_type;
class os_forward_instantiated_class_type;
#if 0
class os_forward_som_class_type;
#endif
class _Database_schema_xrep;
class os_class_type;
class os_template_instantiation;

#if !defined(__EDG) && !defined(_OS_MicrosoftCC) && !defined(__os_linux)
class _OST_hash<const char*, os_unsigned_int32>;
#endif

#define _XREP_MAJOR_VERSION 5  /* inc for incompatible changes to the xrep */
#define _XREP_MINOR_VERSION 0  /* inc for compatible changes to the xrep */

// void _start_list(_Database_schema_xrep&, _Database_schema_xrep::direction);
// void _end_list(_Database_schema_xrep&, _Database_schema_xrep::direction);

static void emit_instantiated_class_type_rep(
				 _Database_schema_xrep&,
				 const os_class_type&,
				 const os_template_instantiation*);
  
class _ODI_R3_to_R4_Upgrade_One_DB;

class _Database_schema_xrep {

  friend class _Dsxrep_token;

public:

  _Database_schema_xrep(OS_FILE*, os_boolean comp_rep = 1);
  ~_Database_schema_xrep();

  static _ODI_R3_to_R4_Upgrade_One_DB* r3_to_r4_upgrade;

  struct tag_class_pair {
    os_unsigned_int32 tag;
    const char* class_name;
    struct tag_class_pair* next;
  };

  struct untagged_class {
    const char* class_name;
    struct untagged_class* next;
  };

  void dump(os_database *);

  const os_type*& get_updated_type(const char*,const os_schema*& schema);
  const os_type*& install_updated_type(const char*);

  /* the const of the first arg of restore is an artifact of using
     const to disambiguate the overloading of operator>> between
     (const char*&) [used for reading strings] and (char*) [used for
     reading single chars]; the caller should delete the returned
     string by casting it to a void*. */
  void restore(
    const char *&, tag_class_pair*&, untagged_class*&, untagged_class*&,
    os_boolean&,os_boolean);

public:

  enum _Xrep_kind {
    Access_modifier = 1,
    Anonymous_indirect_type,
    Array_type,
    Base_class,
    Char_type,
    Class_type,
    Compressed_rep,
    Database_pathname,
    Double_type,
    Enum_type,
    Enumerator_literal,
    Field_member_variable,
    Float_type,
    Floating_extension,
    Forward_class,
    Forward_instantiated_class,
    Function_type,
    Incremental_schema_installation,
    Instantiated_class_type,
    Integer_type,
    Integral_extension,
    Literal,
    Literal_template_actual_arg,
    Long_double_type,
    Member_function,
    Member_type,
    Member_variable,
    Missing_function_type,
    Named_indirect_type,
    Node_ref,
    Pointer_to_member_type,
    Pointer_type,
    Reference_type,
    Relationship_member_variable,
    Self_pointer_member_variable,
    Sentinel,
    Signed_char_type,
    Signed_long_type,
    Signed_short_type,
    Tag_binding,
    Template_instantiation,
    Template_type_formal,
    Template_value_formal,
    Timestamp,
    Type_template,
    Type_template_actual_arg,
    Type_type,
    Unsigned_char_type,
    Unsigned_integer_type,
    Unsigned_long_type,
    Unsigned_short_type,
    Untagged_class,
    Void_type,
    Xrep_version,
    Last_xrep_kind
    };

  enum _Attr_xrep_kind {
    Alignment = 1,
    Arg_list,
    Arg_list_kind,
    Args,
    Base_access,
    Base_classes,
    Base_member,
    Call_linkage,
    Class,
    Class_kind,
    Declares_get_os_typespec_function,
    Defines_virtual_functions,
    Defining_class,
    Dispatch_table_pointer_offset,
    Element_type,
    Enclosing_class,
    Enumerators,
    Function_kind,
    Has_dispatch_table,
    Has_instantiation,
    Indirect_virtual_base_classes,
    Instantiation,
    Internal_name,
    Introduces_virtual_functions,
    Is_abstract,
    Is_const,
    Is_field,
    Is_forward_definition,
    Is_inline,
    Is_overloaded,
    Is_persistent,
    Is_pure_virtual,
    Is_static,
    Is_unspecified,
    Is_virtual,
    Is_volatile,
    Kind,
    Literal_kind,
    Literal_val,
    Member_access,
    Member_block_alignment,
    Member_block_offset,
    Member_block_size,
    Members,
    Name,
    Node_number,
    Number_of_elements,
    Offset,
    Offset_is_valid,
    Related_class,
    Related_member_variable,
    Return_type,
    Rmv_node_number,
    Rmv_node_ref,
    Self_pointer_offset,
    Size,
    Source_position,
    Storage_class,
    Tag,
    Target_class,
    Target_type,
    Template,
    Type,
    Value,
    Virtual_base_class_no_pointer,
    Virtual_base_class_pointer_offset,
    Virtuals_redefined,
    Last_attr_xrep_kind
    };

  enum direction { in, out };

private:

  friend void _start_list(_Database_schema_xrep&, direction);
  friend void _end_list(_Database_schema_xrep&, direction);
  friend void _nl(_Database_schema_xrep&);
  friend void emit_instantiated_class_type_rep(
				 _Database_schema_xrep&,
				 const os_class_type&,
				 const os_template_instantiation*);

  _Database_schema_xrep& operator<< (const _Xrep_kind);

  /* Explanation for these peculiar signatures is that the first operator>> 
     is an assertion that the argument _Xrep_kind is the next token in the
     xrep being read while the second is used to extract whatever _Xrep_kind
     token is next in the xrep stream; use of const and & presence/absence
     was not sufficient to disambiguate the two sigs; hence the resort to 
     pointers in the latter case */
  _Database_schema_xrep& operator>> (const _Xrep_kind);
  _Database_schema_xrep& operator>> (_Xrep_kind*);

  _Database_schema_xrep& operator<< (const _Attr_xrep_kind);
  _Database_schema_xrep& operator>> (const _Attr_xrep_kind);
  _Database_schema_xrep& operator>> (_Attr_xrep_kind*);

  _Database_schema_xrep& operator<< (void
                                     (*)(_Database_schema_xrep&, direction));
  _Database_schema_xrep& operator>> (void
                                     (*)(_Database_schema_xrep&, direction));

  _Database_schema_xrep& operator<< (void (*)(_Database_schema_xrep&));

  _Database_schema_xrep& operator<< (const char *);
  _Database_schema_xrep& operator>> (const char *&);

  _Database_schema_xrep& operator<< (const char);
  _Database_schema_xrep& operator>> (const char);
  _Database_schema_xrep& operator>> (char*);

  _Database_schema_xrep& operator<< (os_unsigned_int8);
  _Database_schema_xrep& operator>> (os_unsigned_int8&);

  _Database_schema_xrep& operator<< (os_unsigned_int32);
  _Database_schema_xrep& operator>> (os_unsigned_int32&);

  _Database_schema_xrep& operator>> (_Wrapped_int32&);
  _Database_schema_xrep& operator<< (_Wrapped_int32&);

  _Database_schema_xrep& operator<< (_Source_position&);
  _Database_schema_xrep& operator>> (_Source_position&);

  _Database_schema_xrep& operator<< (os_boolean);
  _Database_schema_xrep& operator>> (os_boolean&);

  _Database_schema_xrep& operator<< (os_const_types&);
  _Database_schema_xrep& operator>> (os_types*&);

  _Database_schema_xrep& operator<< (const os_type&);
  _Database_schema_xrep& operator>> (os_type*&);

  _Database_schema_xrep& operator<< (const os_forward_class_type&);
  _Database_schema_xrep& operator>> (os_forward_class_type*&);
  
  _Database_schema_xrep& operator<< (const os_forward_instantiated_class_type&);
  _Database_schema_xrep& operator>> (os_forward_instantiated_class_type*&);
  
#if 0
  _Database_schema_xrep& operator<< (const os_forward_som_class_type&);
  _Database_schema_xrep& operator>> (os_forward_som_class_type*&);
#endif
  
  _Database_schema_xrep& operator<< (const os_class_type&);
  _Database_schema_xrep& operator>> (os_class_type*&);

  _Database_schema_xrep& operator<< (const os_instantiated_class_type&);
  _Database_schema_xrep& operator>> (os_instantiated_class_type*&);

  _Database_schema_xrep& operator<< (os_class_type::os_class_kind);
  _Database_schema_xrep& operator>> (os_class_type::os_class_kind&);

  _Database_schema_xrep& operator<< (const os_anonymous_indirect_type&);
  _Database_schema_xrep& operator>> (os_anonymous_indirect_type*&);

  _Database_schema_xrep& operator<< (const os_named_indirect_type&);
  _Database_schema_xrep& operator>> (os_named_indirect_type*&);

  _Database_schema_xrep& operator<< (const os_pointer_type&);
  _Database_schema_xrep& operator>> (os_pointer_type*&);

  _Database_schema_xrep& operator<< (const os_reference_type&);
  _Database_schema_xrep& operator>> (os_reference_type*&);

  _Database_schema_xrep& operator<< (const os_pointer_to_member_type&);
  _Database_schema_xrep& operator>> (os_pointer_to_member_type*&);

  _Database_schema_xrep& operator<< (const os_array_type&);
  _Database_schema_xrep& operator>> (os_array_type*&);

  _Database_schema_xrep& operator<< (const os_enum_type&);
  _Database_schema_xrep& operator>> (os_enum_type*&);

  _Database_schema_xrep& operator<< (os_const_enumerator_literals&);
  _Database_schema_xrep& operator>> (os_enumerator_literals*&);

  _Database_schema_xrep& operator<< (const os_enumerator_literal&);
  _Database_schema_xrep& operator>> (os_enumerator_literal*&);

  _Database_schema_xrep& operator<< (const os_function_type&);
  _Database_schema_xrep& operator>> (os_function_type*&);

  _Database_schema_xrep& operator<< (os_function_type::os_arg_list_kind);
  _Database_schema_xrep& operator>> (os_function_type::os_arg_list_kind&);

  _Database_schema_xrep& operator<< (os_const_members&);
  _Database_schema_xrep& operator>> (os_members*&);

  _Database_schema_xrep& operator<< (const os_member&);
  _Database_schema_xrep& operator>> (os_member*&);

  _Database_schema_xrep& operator<< (os_member::os_member_access);
  _Database_schema_xrep& operator>> (os_member::os_member_access&);

  _Database_schema_xrep& operator<< (const os_member_variable&);
  _Database_schema_xrep& operator>> (os_member_variable*&);

  _Database_schema_xrep& operator<< (os_member_variable::os_storage_class);
  _Database_schema_xrep& operator>> (os_member_variable::os_storage_class&);

  _Database_schema_xrep& operator<< (const os_field_member_variable&);
  _Database_schema_xrep& operator>> (os_field_member_variable*&);

  _Database_schema_xrep& operator<< (const os_relationship_member_variable&);
  _Database_schema_xrep& operator>> (os_relationship_member_variable*&);

  _Database_schema_xrep& operator<< (const os_member_function&);
  _Database_schema_xrep& operator>> (os_member_function*&);

  _Database_schema_xrep& operator<< (os_member_function::os_call_linkage);
  _Database_schema_xrep& operator>> (os_member_function::os_call_linkage&);

  _Database_schema_xrep& operator<< (os_member_function::os_function_kind);
  _Database_schema_xrep& operator>> (os_member_function::os_function_kind&);

  _Database_schema_xrep& operator<< (const os_member_type&);
  _Database_schema_xrep& operator>> (os_member_type*&);

  _Database_schema_xrep& operator<< (const os_access_modifier&);
  _Database_schema_xrep& operator>> (os_access_modifier*&);

  _Database_schema_xrep& operator<< (os_const_base_classes&);
  _Database_schema_xrep& operator>> (os_base_classes*&);

  _Database_schema_xrep& operator<< (const os_base_class&);
  _Database_schema_xrep& operator>> (os_base_class*&);

  _Database_schema_xrep& operator<< (os_base_class::os_base_access);
  _Database_schema_xrep& operator>> (os_base_class::os_base_access&);

  _Database_schema_xrep& operator<< (const os_template_instantiation&);
  _Database_schema_xrep& operator>> (os_template_instantiation*&);

  _Database_schema_xrep& operator<< (os_const_template_actual_args&);
  _Database_schema_xrep& operator>> (os_template_actual_args*&);

  _Database_schema_xrep& operator<< (os_const_template_formal_args&);
  _Database_schema_xrep& operator>> (os_template_formal_args*&);

  _Database_schema_xrep& operator<< (const os_template&);
  _Database_schema_xrep& operator>> (os_template*&);

  _Database_schema_xrep& operator<< (const os_type_template&);
  _Database_schema_xrep& operator>> (os_type_template*&);

  _Database_schema_xrep& operator<< (const os_template_formal_arg&);
  _Database_schema_xrep& operator>> (os_template_formal_arg*&);

  _Database_schema_xrep& operator<< (const os_template_type_formal&);
  _Database_schema_xrep& operator>> (os_template_type_formal*&);

  _Database_schema_xrep& operator<< (const os_template_value_formal&);
  _Database_schema_xrep& operator>> (os_template_value_formal*&);

  _Database_schema_xrep& operator<< (const os_template_actual_arg&);
  _Database_schema_xrep& operator>> (os_template_actual_arg*&);

  _Database_schema_xrep& operator<< (const os_type_template_actual_arg&);
  _Database_schema_xrep& operator>> (os_type_template_actual_arg*&);

  _Database_schema_xrep& operator<< (const os_literal_template_actual_arg&);
  _Database_schema_xrep& operator>> (os_literal_template_actual_arg*&);

  _Database_schema_xrep& operator<< (const os_literal&);
  _Database_schema_xrep& operator>> (os_literal*&);

  _Database_schema_xrep& operator<< (os_literal::os_literal_kind);
  _Database_schema_xrep& operator>> (os_literal::os_literal_kind&);

  _Database_schema_xrep& operator<< (signed long);
  _Database_schema_xrep& operator>> (signed long&);

  _Database_schema_xrep& operator<< (unsigned long);
  _Database_schema_xrep& operator>> (unsigned long&);

/* really */ private:
  void do_indent();
  OS_FILE* file;
  os_boolean compressed_rep;
  _OST_hash<const char *, os_unsigned_int32>* dump_line_table;
  _Pextensible_array<const char *>* restore_line_table;
  os_unsigned_int32 indent;
  os_unsigned_int32 line_key;
  char current_line[1000];
  char* cursor;
  char* end_of_current_line;
  _Node_table* node_table;

  os_int32 get_enum_val(char *[]);
  _Database_schema_xrep& operator>> (_Dsxrep_token&);

  os_boolean updating_types;

  /* This member is used for determining whether or not to ignore the type from
     the dumped schema. */
  os_boolean ignoring_type;

  /* This member is used for determining whether or not to ignore the template
     class type from the dumped schema when dealing with an instantiated
     class.  When dealing with an instantiated class, ignoring_type deals with
     the instantiated class while ignoring_class_type deals with the template
     class. */
  os_boolean ignoring_class_type;

   untagged_class *forward_def_table;
   os_const_classes classes_we_already_have;
};

typedef _Database_schema_xrep::tag_class_pair dsxrep_tag_class_pair;
typedef _Database_schema_xrep::untagged_class dsxrep_untagged_class;

/* Amber #09785, DySak 11/02/95.
   Reuse a convenient existing struct but give it a name which more precisely
   describes its usage in the alternate context. */
typedef _Database_schema_xrep::untagged_class dsxrep_forward_def_class;

extern char** _Xrep_kind_names;
extern char** _Attr_xrep_kind_names;
extern char** _Class_kind_names;
extern char** _Member_access_names;
extern char** _Storage_class_names;
extern char** _Arg_list_kind_names;
extern char** _Call_linkage_names;
extern char** _Function_kind_names;

class _Dsxrep_token {
    
  friend _Database_schema_xrep& 
         _Database_schema_xrep::operator>> (_Dsxrep_token&);

public:
  _Dsxrep_token();
  ~_Dsxrep_token();

  operator char();
  operator os_unsigned_int32();
  operator _Wrapped_int32();
  operator os_unsigned_int8();
  operator char*();
  operator _Database_schema_xrep::_Attr_xrep_kind();
  operator _Database_schema_xrep::_Xrep_kind();
  operator os_boolean();
  operator signed long();
  operator unsigned long();
private:
  char* rep;
};

class _Wrapped_int32 {

public:
  _Wrapped_int32();
  _Wrapped_int32(os_int32);
  os_int32 val;
  operator os_int32();
};

os_unsigned_int32 hash_hash_function(void * const &);
os_boolean hash_compare_function(void * const &,
                                 void * const &);

class _Hash_table_entry<void*,os_unsigned_int32>
{ 
public:
  /* class _Hash_table_entry<void*,os_unsigned_int32> size 12 alignment 4 */
   void*             key ;   /* offset 0 size 4 alignment 4 */
   os_unsigned_int32 value ; /* offset 4 size 4 alignment 4 */
   char status ;             /* offset 8 size 1 alignment 1 */
   char _os_pad_[3] ;        /* offset 9 size 3 alignment 1 */
   static os_typespec* get_os_typespec();
};  /* class _Hash_table_entry<void*,os_unsigned_int32> */

#if !defined(__EDG) && !defined(_OS_MicrosoftCC) && !defined(__os_linux)
class _OST_hash<void*, os_unsigned_int32>;
#endif

class _Node_table {
public:
  _Node_table();
  ~_Node_table();

  /* this interface is ugly: the fundamental flaw is that _Database_schema_xrep
     should be cleft into two classes one: for dumping schema and one for
     restoring schema.  However it isn't and there is this single class for
     representing mappings from void* to os_unsigned_int32s and mappings from 
     os_unsigned_int32s to void* through the following two protocols. */

  /* dump-side protocol for mapping nodes in a schema to "node numbers",
     i.e. unique 32 uints */
  os_boolean enter(const void*, os_unsigned_int32&);

  /* restore-side protocol for mapping node numbers to the restored nodes
     corresponding to them. */
  void enter(os_unsigned_int32, const void*);
  const void* lookup(os_unsigned_int32); /* return 0 if not there */

private:
  _OST_hash<void*,os_unsigned_int32>* dump_table;
  os_unsigned_int32 next_node_number;

  _Pextensible_array<const void*> *restore_table;
};

class _Source_position {
public:
  _Source_position();
  _Source_position(const os_type &);
  _Source_position(const os_member_variable&);
  _Source_position(const os_member_function&);
  
  void set_file(const char *);
  void set_line(os_unsigned_int32);
  
  const char *get_file();
  os_unsigned_int32 get_line();
  
private:
  _ODI_xstring frep;
  os_unsigned_int32 lrep;
};

os_boolean suppressed_class_name(const char*);

#endif
