/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
 */
#ifndef _OS_LIB_QUERIES_H_
#define _OS_LIB_QUERIES_H_
#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#include <ostore/strconv/strconv.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

/*****************************************************************************
* 									     *
* Class definitions related to user visible index and query specifications.  *
* 									     *
*****************************************************************************/
class os_database ;
class os_segment ;

/******************************************************************************
 * Utility classes to support specification of keyword parameters to queries. *
 ******************************************************************************/

class os_keyword_arg_list;
class os_keyword_arg;
class _OSRTQ_Bound_Query;
class _GWRTQ_QGM;

enum _OSRTQ_Type_Enum
{
   _OSRTQ_SIGNED_CHAR_TAG = 1,
   _OSRTQ_UNSIGNED_CHAR_TAG,
   _OSRTQ_SHORT_TAG,
   _OSRTQ_UNSIGNED_SHORT_TAG,
   _OSRTQ_INT_TAG,
   _OSRTQ_UNSIGNED_INT_TAG,
   _OSRTQ_LONG_TAG,
   _OSRTQ_UNSIGNED_LONG_TAG,
   _OSRTQ_FLOAT_TAG,
   _OSRTQ_DOUBLE_TAG,
   _OSRTQ_LONG_DOUBLE_TAG,
   _OSRTQ_POINTER_TAG,
   _OSRTQ_VOID_TAG,
   _OSRTQ_CHAR_TAG,     /* this might prove useful for dealing with   */
			/* unadorned char implementation dependencies */
   _OSRTQ_OFFSET_TAG,
   _OSRTQ_LAST_TYPE_ENUM_TAG,
   _OSRTQ_Type_Enum_pad = 1<<30
};

#ifdef _OS_MicrosoftCC
/* disable  the long double same precision as double warning */
#pragma warning(disable : 4069)
#endif

union _OS_QRY_IMPORT _OSRTQ_Type_Union
{
   os_signed_int8    sc; /* Avoid hairy conditional by using the type from portypes. */
   unsigned char     uc;
   short             ss;
   unsigned short    us;
   int               si;
   unsigned int      ui;
   long              sl;
   unsigned long     ul;
   float             f;
   double            d;
   long double       ld;
   void *            p;
   char              c;    /* this might prove useful for dealing with   */
			   /* unadorned char implementation dependencies */
#if !defined(__os_sol64) && !defined(__os_hp64)
   os_unsigned_int32        o;
#else
   os_ptr_val        o;
#endif

   /* Avoid hairy conditional by using the type from portypes. */
   _OSRTQ_Type_Union(os_signed_int8 arg) { sc = arg; };
#if defined(_OS_Desktop) || defined(__os_xlc) || defined(__os_cafe) || defined(_OS_DECCXX) || defined(__ECPP__) || defined(__os_hp11)
   _OSRTQ_Type_Union(char arg) { c = arg; };
#endif
   _OSRTQ_Type_Union() { si = 0; };
   _OSRTQ_Type_Union(unsigned char arg) { uc = arg; };
   _OSRTQ_Type_Union(short arg) { ss = arg; };
   _OSRTQ_Type_Union(unsigned short arg) { us = arg; };
   _OSRTQ_Type_Union(int arg) { si = arg; };
   _OSRTQ_Type_Union(unsigned int arg) { ui = arg; };
   _OSRTQ_Type_Union(long arg) { sl = arg; };
   _OSRTQ_Type_Union(unsigned long arg) { ul = arg; };
   _OSRTQ_Type_Union(float arg) { f = arg; };
   _OSRTQ_Type_Union(double arg) { d = arg; };
   _OSRTQ_Type_Union(long double arg) { ld = arg; };
   _OSRTQ_Type_Union(void * arg) { p = arg; };
};

class _OS_QRY_IMPORT os_keyword_arg {
   char *      name;
   _OSRTQ_Type_Union data;
   _OSRTQ_Type_Enum  type;

   os_keyword_arg(const os_keyword_arg &);

   /**   Utility to delete an os_keyword_arg when a bound query is deleted.
    **/
   static void del(os_keyword_arg *);

   friend class os_keyword_arg_list;
   friend class _OSRTQ_Bound_Query;
public:
   /* Avoid hairy conditional by using the type from portypes. */
   os_keyword_arg(const char *name_arg, os_signed_int8 val);
   os_keyword_arg(const char *name_arg, unsigned char val);
   os_keyword_arg(const char *name_arg, short val);
   os_keyword_arg(const char *name_arg, unsigned short val);
   os_keyword_arg(const char *name_arg, int val);
   os_keyword_arg(const char *name_arg, unsigned int val);
   os_keyword_arg(const char *name_arg, long val);
   os_keyword_arg(const char *name_arg, unsigned long val);
   os_keyword_arg(const char *name_arg, float val);
   os_keyword_arg(const char *name_arg, double val);
   os_keyword_arg(const char *name_arg, long double val);
#if defined(OS_NO_CONST_POINTER_KEYWORD_ARG) || defined(OS_ALLOW_BOTH_POINTER_KW_ARGS)
   os_keyword_arg(const char *name_arg, void * val);
#endif
#ifndef OS_NO_CONST_POINTER_KEYWORD_ARG
   os_keyword_arg(const char *name_arg, const void * val);
#endif
   ~os_keyword_arg() { if (name) delete [] name; }

   os_keyword_arg_list & operator , (const os_keyword_arg &) const;

public:
   static void destroy(os_keyword_arg* kw) { del(kw); }
};

class _OS_QRY_IMPORT os_keyword_arg_list {
   os_keyword_arg kw_arg;
   const os_keyword_arg_list * next;
   os_boolean internal;

   /**   Utilities used to evacuate os_keyword_args from the stack at the time
    **   a bound query is created.
    **/
   void copy_internal() const;
   const os_keyword_arg_list & copy() const;

   /**   Utility to delete an os_keyword_arg_list when a bound query is
    **   deleted.
    **/
   static void del(os_keyword_arg_list *);

   friend class _OSRTQ_Bound_Query;
   friend class os_keyword_arg;
public:
   os_keyword_arg_list & operator , (const os_keyword_arg &) ;
   os_keyword_arg_list(const os_keyword_arg &, const os_keyword_arg_list * =0);
   ~os_keyword_arg_list() {}
   static void destroy_list(os_keyword_arg_list *);

   void set_internal() { internal = 1; }
   os_boolean get_internal() const { return internal; }
} ;


#ifdef OS_PRE_R3_CACHE_QUERY_DEFAULT
#define OS_CACHE_QUERY_DEFAULT 1
#else
#define OS_CACHE_QUERY_DEFAULT 0
#endif

typedef void (*_Gateway_Query)();
/***
 ***  os_coll_query represents a specification of a query suitable for
 ***  persistent storage.
 ***/
class _OS_QRY_IMPORT os_coll_query : public os_virtual_behavior64
{
protected:
   os_coll_query();
   virtual ~os_coll_query();
public:
   static const os_coll_query &create(
      const char *element_type,
      const char *query_string,
      os_database*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create(
      const char *element_type,
      const char *query_string,
      os_segment*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create(
      const char *element_type,
      const char *query_string,
      const void*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_pick(
      const char *element_type,
      const char *query_string,
      os_database*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_pick(
      const char *element_type,
      const char *query_string,
      os_segment*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_pick(
      const char *element_type,
      const char *query_string,
      const void*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_exists(
      const char *element_type,
      const char *query_string,
      os_database*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_exists(
      const char *element_type,
      const char *query_string,
      os_segment*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_exists(
      const char *element_type,
      const char *query_string,
      const void*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create(
      const char *element_type,
      const char *query_string,
      os_str_conv::encode_type string_literal_char_encoding,
      os_database*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create(
      const char *element_type,
      const char *query_string,
      os_str_conv::encode_type string_literal_char_encoding,
      os_segment*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create(
      const char *element_type,
      const char *query_string,
      os_str_conv::encode_type string_literal_char_encoding,
      const void*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_pick(
      const char *element_type,
      const char *query_string,
      os_str_conv::encode_type string_literal_char_encoding,
      os_database*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_pick(
      const char *element_type,
      const char *query_string,
      os_str_conv::encode_type string_literal_char_encoding,
      os_segment*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_pick(
      const char *element_type,
      const char *query_string,
      os_str_conv::encode_type string_literal_char_encoding,
      const void*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_exists(
      const char *element_type,
      const char *query_string,
      os_str_conv::encode_type string_literal_char_encoding,
      os_database*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_exists(
      const char *element_type,
      const char *query_string,
      os_str_conv::encode_type string_literal_char_encoding,
      os_segment*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static const os_coll_query &create_exists(
      const char *element_type,
      const char *query_string,
      os_str_conv::encode_type string_literal_char_encoding,
      const void*,
      os_boolean cache_query = OS_CACHE_QUERY_DEFAULT,
      const char* file_name = 0,
      os_unsigned_int32 line = 0);

   static void destroy(const os_coll_query &);

  
   /**
    **   Accessors to information at the time the query was created.
    **/
   virtual const char *      get_element_type() const;
   virtual const char *      get_query_string() const;
   virtual const char *      get_file_name()    const;
   virtual os_unsigned_int32 get_line_number()  const;

public:

   /**
    **  These functions are for internal testing purposes only.
    **/

   /* Returns newly allocated memory.  Must be freed by caller via operator
      delete.
    */
   virtual char** _get_potentially_useful_indexes() const;
};

/***
 ***  A transient representation of a query, with all its free variables
 ***  bound. It is suitable for direct evaluation in the context of the
 ***  appropriate collection.
 ***/
class _OS_QRY_IMPORT os_bound_query
{
   friend class _GWRTQ_QGM;
/* xlC bug workaround */
#ifdef __os_xlc
   friend class os_collection;
#else
   friend os_collection& os_collection::query(const os_bound_query &,
					      os_boolean) const;
   friend void * os_collection::query_pick(const os_bound_query &) const;
   friend os_int32 os_collection::exists(const os_bound_query &) const;
#endif

   _OSRTQ_Bound_Query * bindings;
public:
   /**
    **   Provide some minimal amount of interference to a user newing a
    **   os_bound_query in persistent space.  There isn't any way in C++ to
    **   completely shut off only persistent news.
    **/
#ifndef _OS_OS2
   void * operator new(size_t size _OS_DBALLOC_PARMS);
   /* compilers complain if they don't match */
   void operator delete (void * _OS_DBALLOC_PARMS);
#endif
   os_bound_query(   /* for queries that need binding */
      const os_coll_query &,
      const os_keyword_arg_list &);
   os_bound_query(   /* for queries that purport not to need binding */
      const os_coll_query &);
   ~os_bound_query();
};

#ifndef _OS_PSE_COLL
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif
#endif /* _OS_LIB_QUERIES_H_ */
