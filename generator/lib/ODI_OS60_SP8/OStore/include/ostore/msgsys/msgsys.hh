/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _MSGSYS_H_
#define _MSGSYS_H_

#if defined(OS_DLL_MSGSYS)
#define OS_MSGSYS_EXCEPTION(name)	\
extern _OS_DECLSPEC_DLLEXPORT objectstore_exception name
#else
#define OS_MSGSYS_EXCEPTION(name)	\
extern _OS_DECLSPEC_DLLIMPORT objectstore_exception name
#endif

#if defined(OS_DLL_MSGS)
#define OS_MSGS_EXCEPTION(name)	\
extern _OS_DECLSPEC_DLLEXPORT objectstore_exception name
#else
#define OS_MSGS_EXCEPTION(name)	\
extern _OS_DECLSPEC_DLLIMPORT objectstore_exception name
#endif

#include <stdarg.h>
#include <ostore/msgsys/msgexcpt.hh>


OS_MSGSYS_EXCEPTION(install_failure_1);
OS_MSGSYS_EXCEPTION(install_failure_2);
OS_MSGSYS_EXCEPTION(message_failure_1);
OS_MSGSYS_EXCEPTION(message_failure_2);

class os_Message_item
   {
public:
   int                     tag;
   os_Message_exception*      error;
//   os_Exception*           cpp_error; /* os_Eceptions are not const */
//   objectstore_exception*  tix_error;
   const char*             text;
   };

typedef os_Message_item* os_message_array;

class os_Message; /* pointed at for install. defined below. */

class os_Message_system
   {
public:
   enum exception_style
      {
      cpp,
      tix
      };
   os_Message_system() {}
   ~os_Message_system() {}
   static void set_exception_type(exception_style type);
   static void set_on_fatal
      (void (*fn)(const os_message_array array,int id,
      const char* file, const int line,
      va_list v));
   static void set_on_error
      (void (*fn)(const os_message_array array,int id,
      const char* file, const int line,
      va_list v));
   static void set_on_warn
      (void (*fn)(const os_message_array array,int id,va_list v));
   static void set_on_info
      (void (*fn)(const os_message_array array,int id,va_list v));
   static void set_on_format(char* (*fn)(const char* subsystem,
      int global_id,const char* file, const int line,
      const char* fmt,va_list v));
   static void install(const os_message_array array,
                       const int first,const int last,os_Message* super);
   static void fatal(const os_message_array array,const int id,
                     int global_id,const char* subsystem,
                     const char* file, const int line,
                     va_list v);
   static void error(const os_message_array array,const int id,
                     int global_id,const char* subsystem,
                     const char* file, const int line,
                     va_list v);
   static void warn(const os_message_array array,const int id,
                    int global_id,const char* subsystem,va_list v);
   static void info(const os_message_array array,const int id,
                    int global_id,const char* subsystem,va_list v);
private:
   static char* format(const char* subsystem,int global_id,
      const char* file, const int line,
      const char* fmt,va_list v);
   static char* (*on_format)(const char* subsystem,
      int global_id,const char* file, const int line,
      const char* fmt,va_list v);
   static void (*on_fatal)(const os_message_array array,int id,
      const char* file, const int line,
      va_list v);
   static void (*on_error)(const os_message_array array,int id,
      const char* file, const int line,
      va_list v);
   static void (*on_warn)(const os_message_array array,int id,va_list v);
   static void (*on_info)(const os_message_array array,int id,va_list v);
   static exception_style exception_type;
   };

extern os_Message_system the_Message_system;

class os_Message
   {
public:
   enum messageid
      {
      last_defined_message = 0,
      next_available_message = 0
      };
   static void message_kludge(os_Message* ptr,char* file,int line);
   static void fatal(const int id,...);
   static void error(const int id,...);
   static void  warn(const int id,...);
   static void  info(const int id,...);
   static os_Message* get_self();
protected:
   os_Message(const os_message_array array,
      int first_message,int last_message,
      os_Message* super,
      char* name);
   ~os_Message()
      {}
   void vfatal(const int id,
      const char* file, const int line,
      va_list v) const;
   void verror(const int id,
      const char* file, const int line,
      va_list v) const;
   void vwarn(const int id,va_list v) const;
   void vinfo(const int id,va_list v) const;
/* data members */
   const os_message_array theArray;
   const int first_message_id;
   const int last_message_id;
   const os_Message* const superior;
   const char* name;
/* static data -- used to capture source file and line info */
   static char* file;
   static int line;
   static os_Message* pthis;
   };

/* Macros */

#define OS_NUMBER_OF_SUBSYSTEM_MESSAGES(current,super) \
   current::last_defined_message - \
   super::next_available_message

#define OS_DECLARE_SUBSYSTEM_CHAINING(superior) \
      last_defined_message, \
      next_available_message = (superior::next_available_message + 1000)

#define OS_DECLARE_SUBSYSTEM_MESSAGES(current) \
private: \
   current(); \
public: \
   static current* get_self(); \
   static void message_kludge(char* _file,int _line)

#define OS_INITIALIZE_SUBSYSTEM_MESSAGES(array,current,superior) \
current::current() \
   : os_Message(array, \
      superior::next_available_message, \
      current::last_defined_message, \
      superior::get_self(), \
      #current) \
   {} \
current* p##current = 0; \
current* current::get_self() \
   { \
   if (p##current) \
      return p##current; \
   p##current = new current(); \
   return p##current; \
      } \
void current::message_kludge(char* _file,int _line) \
   { \
   os_Message::message_kludge(current::get_self(),_file,_line); \
   }

#define OS_FATAL message_kludge(__FILE__,__LINE__), os_Message::fatal
#define OS_ERROR message_kludge(__FILE__,__LINE__), os_Message::error
#define OS_WARN message_kludge(__FILE__,__LINE__), os_Message::warn
#define OS_INFO message_kludge(__FILE__,__LINE__), os_Message::info

#endif
