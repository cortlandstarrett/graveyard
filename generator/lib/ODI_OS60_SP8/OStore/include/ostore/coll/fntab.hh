/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _COLL_FN_TAB
#define _COLL_FN_TAB

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrstart.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

class os_function_info;
class os_function_info_holder;
class os_dictionary;
class os_backptr;

/* Definitions for DEC C++. */
typedef os_function_info* os_function_info_p;

enum os_fi_ptr_responsibility { os_fi_no_problem = 0, 
				os_fi_caller_responsible = 1,
			        os_fi_ptr_responsibility_pad = 1<<30 };
enum os_fi_member_kind { os_fi_functionm = 0, os_fi_datam = 2, os_fi_member_kind_pad = 1<<30 };
enum os_fi_class_type { os_fi_non_som = 0, os_fi_som = 4, os_fi_class_type_pad = 1<<30 };
enum os_fi_masks { os_fi_resp_mask = 1, os_fi_kind_mask = 2, 
		   os_fi_ctype_mask = 4, os_fi_masks_pad = 1<<30 };

typedef os_function_info_p (*os_fn_info_callback)(os_char_const_p, os_char_const_p);

class _OS_COLL_IMPORT os_function_map {

private:

  static os_dictionary* _map;
  static os_function_info_holder* fihold;
  

public:

  static void insert_item(os_function_info* fi);
  static void remove_item(const char* cls, const char* member);
  static os_function_info* find_item(const char* cls, const char* member);

};

class os_function_info_holder {
public:
  os_function_info_holder* _next;
  os_function_info* _thing;

  os_function_info_holder(os_function_info* th, os_function_info_holder* n)
  : _thing(th), _next(n) {}
  ~os_function_info_holder() {}
};

class _OS_COLL_IMPORT os_function_info : public os_virtual_behavior64 {

protected:

  char* _class;
  char* _member;
  char* _return_type;
  os_unsigned_int32 _return_type_size;

  os_int32 _backptr_offset;
  os_unsigned_int32 _flags;
  
public:

  /* only used for temporary objects which don't get inserted into the mapping.
     (For example: in order to find a particular os_function_info in the mapping
     one could create an instance on the stack using this constructor. (Creating
     an instance using the other constructor won't work).
   */
  os_function_info(const char* cls, const char* member);

  os_function_info(const char* cls, const char* member, const char* return_type,
		   os_unsigned_int32 return_type_size,
		   os_int32 backptr_offset = -1,
		   os_int32 resp = os_fi_no_problem, 
		   os_int32 ctype = os_fi_non_som,
		   os_boolean insert_into_mapping = 1);
  virtual ~os_function_info();

  char* get_class() const { return _class; }
  char* get_member() const { return _member; }

  char* get_return_type() const
  { return _return_type; }

  os_unsigned_int32 get_return_type_size() const
  { return _return_type_size; }

  os_int32 get_responsibility() 
  { return _flags & os_fi_resp_mask; }

  os_int32 get_class_type() const 
  { return _flags & os_fi_ctype_mask; }

public:

  /* virtual functions which can be defined by subclasses */

  virtual os_backptr* get_os_backptr(void* obj) const;
  virtual void get_value(void* obj, void* pval) const;
  virtual os_function_info* copy(void* obj) const;

public:
  
  static os_int32 _rank(const void* v1, const void* v2);
  static os_unsigned_int32 _hash(const void* v);
};


#if defined(_OS_ANSI_TOKENS)
#define _ODI_Concat(x,y)x##y
#define _ODI_Concat3(x,y,z) x##y##z
#define _ODI_Concat4(x,y,z,w)x##y##z##w
#define _ODI_Concat5(x,y,z,w,v)x##y##z##w##v
#define _ODI_Str(x) (char*)#x
#define _ODI_Str_ptr(typ) _ODI_Str(typ##*)
#else
#define _ODI_Str(x) (char*)"x"
#define _ODI_Self(x)x

#define _ODI_Concat(x,y)_ODI_Self(x)y

#define _ODI_Concat3(x,y,z)_ODI_Concat(x,y)z

#define _ODI_Concat4(x,y,z,w)_ODI_Concat3(x,y,z)w

#define _ODI_Concat5(x,y,z,w,v)_ODI_Concat4(x,y,z,w)v

#define _ODI_Str_ptr(typ) (char*)"typ*"
#endif

#if !defined(_OS_PSE_COLL)

#define os_query_function(__class,func,typ)\
class _ODI_Concat4(os_,__class,_,func) : public os_function_info { public:\
  virtual void get_value(void* obj,void* pval) const; \
  virtual os_function_info* copy(void* obj) const;\
  _ODI_Concat4(os_,__class,_,func)(char* cls, char* member, char* return_type,\
			      os_unsigned_int32 return_type_size,\
			      os_ptr_val backptr_offset = -1,\
			      os_boolean insert_into_map=0) :\
  os_function_info(cls,member,return_type,return_type_size,backptr_offset,\
		   os_fi_no_problem, os_fi_non_som, insert_into_map) {}\
  ~_ODI_Concat4(os_,__class,_,func)() {}\
  static os_typespec* get_os_typespec();\
};


#define os_query_function_body(__class,func,typ,bpname)\
void _ODI_Concat4(os_,__class,_,func)::get_value(void* obj, void* pval) const\
 { (*(typ*)pval) = ((__class*)obj)->func(); }\
os_function_info* _ODI_Concat4(os_,__class,_,func)::copy(void* obj) const\
  { return (os_function_info*)\
      new (os_cluster::with(obj),\
	   _ODI_Concat4(os_,__class,_,func)::get_os_typespec())\
         _ODI_Concat4(os_,__class,_,func)(_class,_member,_return_type,\
				     _return_type_size, _backptr_offset,0);\
  }\
_ODI_Concat4(os_,__class,_,func)  _ODI_Concat4(os_tmp_,__class,_,func)\
(_ODI_Str(__class),_ODI_Str(func), _ODI_Str(typ), sizeof(typ),\
(os_ptr_val)&(((__class*)0)->bpname),1);

#define os_query_function_body_const(__class,func,typ)\
void _ODI_Concat4(os_,__class,_,func)::get_value(void* obj, void* pval) const\
 { (*(typ*)pval)=((__class*)obj)->func(); }\
os_function_info* _ODI_Concat4(os_,__class,_,func)::copy(void* obj) const\
  { return (os_function_info*)\
      new (os_cluster::with(obj),\
	   _ODI_Concat4(os_,__class,_,func)::get_os_typespec())\
         _ODI_Concat4(os_,__class,_,func)(_class,_member,_return_type,\
				     _return_type_size, _backptr_offset,0);\
  }\
_ODI_Concat4(os_,__class,_,func)  _ODI_Concat4(os_tmp_,__class,_,func)\
     (_ODI_Str(__class),_ODI_Str(func), _ODI_Str(typ), sizeof(typ),-1,1);


#define os_query_function_returning_ref(__class,func,typ)\
class _ODI_Concat4(os_,__class,_,func) : public os_function_info { public:\
  virtual void get_value(void* obj,void* pval) const; \
  virtual os_function_info* copy(void* obj) const;\
  _ODI_Concat4(os_,__class,_,func)(char* cls, char* member, char* return_type,\
			      os_unsigned_int32 return_type_size,\
			      os_ptr_val backptr_offset = -1,\
			      os_boolean insert_into_map=0) :\
  os_function_info(cls,member,return_type,return_type_size,backptr_offset,\
		   os_fi_no_problem, os_fi_non_som, insert_into_map) {}\
  ~_ODI_Concat4(os_,__class,_,func)() {}\
  static os_typespec* get_os_typespec();\
};

#define os_query_function_body_returning_ref(__class,func,typ,bpname)\
void _ODI_Concat4(os_,__class,_,func)::get_value(void* obj, void* pval) const\
 { (*(typ**)pval)=&((__class*)obj)->func(); }\
os_function_info* _ODI_Concat4(os_,__class,_,func)::copy(void* obj) const\
  { return (os_function_info*)\
      new (os_cluster::with(obj),\
	   _ODI_Concat4(os_,__class,_,func)::get_os_typespec())\
         _ODI_Concat4(os_,__class,_,func)(_class,_member,_return_type,\
				     _return_type_size, _backptr_offset,0);\
  }\
_ODI_Concat4(os_,__class,_,func)  _ODI_Concat4(os_tmp_,__class,_,func)\
(_ODI_Str(__class),_ODI_Str(func), _ODI_Str_ptr(typ), sizeof(_ODI_Str_ptr(typ)),\
(os_ptr_val)&(((__class*)0)->bpname),1);

#define os_query_function_body_with_namespace(__class,__classWithNS,func,typ,bpname)\
void _ODI_Concat4(os_,__class,_,func)::get_value(void* obj, void* pval) const\
 { (*(typ*)pval) = ((__class*)obj)->func(); }\
os_function_info* _ODI_Concat4(os_,__class,_,func)::copy(void* obj) const\
  { return (os_function_info*)\
      new (os_cluster::with(obj),\
	   _ODI_Concat4(os_,__class,_,func)::get_os_typespec())\
         _ODI_Concat4(os_,__class,_,func)(_class,_member,_return_type,\
				     _return_type_size, _backptr_offset,0);\
  }\
_ODI_Concat4(os_,__class,_,func)  _ODI_Concat4(os_tmp_,__class,_,func)\
(_ODI_Str(__classWithNS),_ODI_Str(func), _ODI_Str(typ), sizeof(typ),\
(os_ptr_val)&(((__class*)0)->bpname),1);

#define OS_MARK_QUERY_FUNCTION(__class,func)\
OS_MARK_SCHEMA_TYPE(_ODI_Concat4(os_,__class,_,func));

#else
//undef it to avoid warning when using both OStore and PSE
#ifdef os_query_function
#undef os_query_function
#endif
#ifdef os_query_function_body
#undef os_query_function_body
#endif
#ifdef os_query_function_body_const
#undef os_query_function_body_const
#endif

#ifdef os_query_function_returning_ref
#undef os_query_function_returning_ref
#endif

#ifdef os_query_function_body_returning_ref
#undef os_query_function_body_returning_ref
#endif

#ifdef os_query_function_body_with_namespace
#undef os_query_function_body_with_namespace
#endif

#ifdef OS_MARK_QUERY_FUNCTION
#undef OS_MARK_QUERY_FUNCTION
#endif
#define os_query_function(__class,func,typ)
#define os_query_function_body(__class,func,typ,bpname)
#define os_query_function_body_const(__class,func,typ)
#define os_query_function_returning_ref(__class,func,typ)
#define os_query_function_body_returning_ref(__class,func,typ,bpname)
#define os_query_function_body_with_namespace(__class,__classWithNS,func,typ,bpname)
#define OS_MARK_QUERY_FUNCTION(__class,func)
#endif

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif
