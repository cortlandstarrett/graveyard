/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _TIX_H_
#define _TIX_H_
#include <ostore/hdrstart.hh>

/* tix.hh: Header file for Temporary Internal eXception mechanism. */

#if !defined (_OS_STATIC_DM) && defined (sun)
#define _OS_STATIC_DM
#endif

#ifndef _LLPL_H_
#include <ostore/hdrsys.hh>
#include <stddef.h>
#include <ostore/hdrend.hh>
#endif

#include <ostore/portypes.hh>

/* Note ports which use C++ exception semantics. */
/* Note:  for sgi, the feature macro __EXCEPTIONS is set based on whether or not the compiler option */
/* exceptions is enabled.                                                                            */
#if defined(_OS_OS2) || defined(_OS_Win32) || defined(_OS_DECCXX) || ( defined(__os_sgi_mips) && defined (__EXCEPTIONS) )
#define _OS_CPP_EXCEPTIONS
#endif

#ifndef _OS_Win32

#include <ostore/hdrsys.hh>
#include <setjmp.h>
#include <ostore/hdrend.hh>

#if defined(__os_sysv4)
#ifdef __os_sgi_mips
#if !defined(_SVR4_SOURCE) && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
typedef int sigjmp_buf[_SIGJBLEN];
extern
#ifdef __cplusplus
"C"
#endif /* __cplusplus */
int sigsetjmp (sigjmp_buf, int);
#endif /* svr4 and all of that on sgi */
#endif /* __os_sgi_mips */

#if defined(__os_sni)
typedef int sigjmp_buf[_SIGJBLEN];
extern "C" int sigsetjmp (sigjmp_buf, int);
#endif /* __os_sni */

#if defined (__os_ncr) || defined (__os_sol2)
#if __STDC__ != 0 && !defined(_POSIX_SOURCE) && !defined(_XOPEN_SOURCE)
typedef int sigjmp_buf[_SIGJBLEN];
extern "C" int sigsetjmp (sigjmp_buf, int);
#endif /* STDC and all of that */
#endif /* ncr or sol2 */

#define _ODI_jmp_buf sigjmp_buf
#define _ODI_setjmp(b) sigsetjmp(b,1)
#else
#define _ODI_jmp_buf jmp_buf
#define _ODI_setjmp setjmp
#endif /* __os_sysv4 */

#endif /* _OS_Win32 */

#ifdef __VMS
extern os_boolean condition_active;
#endif

#ifdef __cplusplus

#include <ostore/hdrsys.hh>
#include <stdarg.h>
#include <ostore/hdrend.hh>

class tix_exception;			/* defined below */
class os_lock_timeout_exception;	/* defined in ostore/except.hh */
class os_deadlock_exception;		/* defined in ostore/except.hh */

/* Definitions for DEC C++. */
typedef tix_exception* tix_exception_p;

class _ODI_arg2 {
public:
  os_int32 _msg_id;
  const char * _msg;
  _ODI_arg2(const os_int32 msg_id, const char *msg) : _msg_id(msg_id), _msg(msg) { }
  operator _ODI_arg2*() { return this; }
  operator const _ODI_arg2*() const { return this; }

};

typedef void (*tix_unhandled_exception_hook_t)
     (tix_exception_p cause, os_int32 value, os_char_p report);

class tix_exception {
public:
  char const *message;
  os_int32 message_number;
  tix_exception const *parent;

  tix_exception() {}
  tix_exception(char const *message_arg);
  tix_exception(char const *message_arg, tix_exception const *exception_arg);

  tix_exception(const _ODI_arg2 arg2);
  tix_exception(const _ODI_arg2 arg2, tix_exception const *exception_arg);
  ~tix_exception();

  void _initialize(const _ODI_arg2 arg2,
		   tix_exception const *exception_arg);
  void signal(const _ODI_arg2 * arg2 ...);

  void signal(char const *format ...);
  void signal(os_int32 value_arg, char const *format ...);

  void vsignal(char const *format, va_list args);
  void vsignal(os_int32 value_arg, char const *format, va_list args);

  os_boolean ancestor_of(tix_exception const *e);
  os_boolean handled_exactly();

  void _initialize(char const *message_arg, tix_exception const *exception_arg);

  static tix_unhandled_exception_hook_t set_unhandled_exception_hook 
    (tix_unhandled_exception_hook_t new_hook);

  /* Support for dynamically allocated and deallocated exceptions */

  os_deadlock_exception* get_os_deadlock_exception() const;
  os_lock_timeout_exception* get_os_lock_timeout_exception() const;
  void release_pointer();

private:
  static tix_unhandled_exception_hook_t unhandled_exception_hook;
  void fatal(os_boolean internal_error, os_int32 value_arg, char *report_buffer);

  /* Undefined declarations to suppress default definitions. */
  tix_exception(const tix_exception&);
  tix_exception& operator=(const tix_exception&);
};

extern "C" _OS_DLLIMPORT(_OS_LOW) tix_exception all_exceptions;

/* If _ODI_skip_shutdown_cleanup is true, objectstore::shutdown()
   will not perform session cleanup. Typically, the flag is set true by
   tix_exception::fatal(). The flag can also be set immediately before
   calling exit() in order to prevent objectstore cleanup. */
extern _OS_DLLIMPORT(_OS_LOW) os_boolean _ODI_skip_shutdown_cleanup;

#endif /*  __cplusplus */

enum _Basic_undo_stack_undo { _Stack };

struct tix_lwp_state;

#ifdef __cplusplus
class tix_handler {
private:
#else
typedef struct tix_exception tix_exception;
typedef struct tix_handler tix_handler;
struct tix_handler {
#endif /*  __cplusplus */
  /* data members */
  tix_handler *saved_current;	/* used to be entry_depth */

/*110697:sean:aCC:Edits for os_boolean.*/
  os_boolean save_message;
  os_boolean do_throw;
  os_boolean print_message;
  tix_handler *prev;
  tix_exception *exception_handled;
  os_boolean hook_functions_defined; /* currently unused */
  tix_lwp_state &tix_state;
#ifdef __cplusplus
public:
#endif /*  __cplusplus */
#if defined(_OS_CPP_EXCEPTIONS)
  os_boolean setjmp_done;
#endif
  os_boolean signal_happened;
#if defined(_OS_CPP_EXCEPTIONS)
  tix_handler* last_thrown;
#endif
#ifndef _OS_Win32
  _ODI_jmp_buf env;
#endif
#ifdef __cplusplus
private:
#endif /*  __cplusplus */
  os_int32 value;
  char *report;
  char *report0; /* just the sprintf output */
  tix_exception *the_exception;
#ifdef NeXT
  os_unsigned_int32 thread;
#endif
#ifdef __VMS
  os_boolean condition_active;
#endif
#if defined(_OS_CPP_EXCEPTIONS)
  void (*saved_terminate_fcn)();
#endif
#ifdef __cplusplus
public:
  void *operator new(size_t _OS_DBALLOC_PARMS, _Basic_undo_stack_undo, void *p) { return p; }	/* for C interface */
  void operator delete(void * _OS_DBALLOC_PARMS) {}	/* always on the stack */
  tix_handler(tix_exception const *exception_arg);
  ~tix_handler();
  void set_action(os_boolean sm, os_boolean th, os_boolean pm);

  /* Make some unwinding stuff visible for Oberon. */
  os_boolean _unwind_part_1(tix_exception * = 0, os_int32 = 0, char * = 0, char * = 0);
  void _unwind_part_2();

  static char *get_last_message();
  static tix_handler *get_current();
  os_int32 _internal_get_depth();
  static os_int32 get_depth();
  static os_int32 get_value();
  static char *get_report();
  static char *get_report0();
  static tix_exception *get_exception();

private:
  friend class tix_exception;

  /* added delink_this_tix_handler to work around a solaris C++ compiler bug
     that can delay the running of destructors of temporaries past the
     end of the tix handler.   aei 04/03/2001 */
  void delink_this_tix_handler();

  /* Undefined declarations to suppress default definitions. */
  void *operator new(size_t _OS_DBALLOC_PARMS);		/* always on the stack */
  tix_handler(const tix_handler&);
  tix_handler& operator=(const tix_handler&);
#endif /*  __cplusplus */
};

#ifndef __cplusplus
typedef struct basic_undo basic_undo;
#endif /*  __cplusplus */

#ifdef __cplusplus
struct tix_lwp_state;

#ifdef _OS_CPP_EXCEPTIONS
#ifdef _OS_Win32
/* _OS_NATIVE_BASIC_UNDO should only be defined on platforms that have native
   CPP exceptions, and that actually do run all dtors, even those in the
   top-most frame below a fault handler when the fault handler throws the
   exception (currently, Solaris does not meet this last criterion) */
#define _OS_NATIVE_BASIC_UNDO
#endif
#endif
  
#ifndef _OS_NATIVE_BASIC_UNDO
class _OS_DLLIMPORT(_OS_LOW) basic_undo {
  basic_undo *next;
  tix_lwp_state &tix_state;
  tix_exception *exception;
protected:
  os_boolean has_exception() const { return exception != 0; }
  tix_exception* get_exception() const { return (tix_exception*)exception; }
private:
  tix_handler *handler_nesting;
public:
  void *operator new(size_t _OS_DBALLOC_PARMS, _Basic_undo_stack_undo, void *p) { return p; }	/* for C interface */
  void operator delete (void * _OS_DBALLOC_PARMS); /* always on the stack */
  basic_undo();
  virtual ~basic_undo();
private:
  friend class tix_exception;
  friend class tix_handler;
  static void unwind_to_depth(os_int32 handler_depth, tix_exception *cause,
                              os_boolean do_delete = 0);

  /* Undefined declarations to suppress default definitions. */
  /* They may be undefined, but some compilers reference them
     from derived classes, so they can't be private */
/* re-privatised to figure out what is going on on CAFE, where
   they end up being CALLED */
 private:
  basic_undo(const basic_undo&);
  basic_undo& operator=(const basic_undo&);
  void *operator new(size_t _OS_DBALLOC_PARMS);		/* always on the stack */
};
#else
class _OS_DLLIMPORT(_OS_LOW) basic_undo {
protected:
  os_boolean has_exception() const;
  tix_exception* get_exception() const;
public:
  void *operator new(size_t _OS_DBALLOC_PARMS, _Basic_undo_stack_undo, void *p) { return p; }	/* for C interface */
  void operator delete (void * _OS_DBALLOC_PARMS); /* always on the stack */
  basic_undo();
  virtual ~basic_undo();

  /* Undefined declarations to suppress default definitions. */
  /* They may be undefined, but some compilers reference them
     from derived classes, so they can't be private */
  /* re-privatised to figure out what is going on on CAFE, where
   they end up being CALLED */
private:
  basic_undo(const basic_undo&);
  basic_undo& operator=(const basic_undo&);
  void *operator new(size_t _OS_DBALLOC_PARMS);		/* always on the stack */
};
#endif /* _OS_NATIVE_BASIC_UNDO */

class tix_context {
private:
  tix_context *next;
  const char *format;
  const os_int32 fid;
  const char *string1, *string2, *string3, *string4;
  tix_handler *handler_nesting;
public:
  void operator delete (void * _OS_DBALLOC_PARMS) {}	/* always on the stack */

  tix_context(const char *f);
  tix_context(const char *f, const char *s1);
  tix_context(const char *f, const char *s1, const char *s2);
  tix_context(const char *f, const char *s1, const char *s2, const char *s3);
  tix_context(const char *f, const char *s1, const char *s2, const char *s3, const char *s4);

  tix_context(const _ODI_arg2 arg2);
  tix_context(const _ODI_arg2 arg2, const char *s1);
  tix_context(const _ODI_arg2 arg2, const char *s1, const char *s2);
  tix_context(const _ODI_arg2 arg2, const char *s1, const char *s2, const char *s3);
  tix_context(const _ODI_arg2 arg2, const char *s1, const char *s2, const char *s3, const char *s4);

  ~tix_context();
  void print_report(char *);
private:
  void init();
  friend class tix_exception;
  friend class tix_handler;
  static void unwind_to_depth(os_int32 handler_depth, char *report);

  /* Undefined declarations to suppress default definitions. */
  void *operator new(size_t _OS_DBALLOC_PARMS);		/* always on the stack */
  tix_context (const tix_context&);
  tix_context& operator= (const tix_context&);
};

/* no one EVER signals tix_no_exception */
extern "C" _OS_DLLIMPORT(_OS_LOW) tix_exception tix_no_exception;

#if defined(_OS_CPP_EXCEPTIONS)

#if defined(_OS_MicrosoftCC)
/* Foolproofing: report an error if the user attempts to compile without
** the /EHa option, required for C++ exception-handling semantics */
#pragma warning(error:4530)
/* More foolproofing: require /MD. */
#ifndef _DLL
#ifndef _ODI_OSSG_
#include "You must compile with the /MD option."
#endif
#endif
#if defined(_DEBUG) && !defined(_ODI_FORCE_OSTORE_LIB)
/* Microsoft VC++ 4.2 and above set _DEBUG when /MDd is specified, to mean
** "link with msvcrtd.lib and the debug C runtime".  We do the same.  If
** you use _DEBUG for your own debugging, you can define _ODI_FORCE_OSTORE_LIB
** to force the use of ostore.lib instead of ostored.lib
*/
#pragma comment(lib, "ostored.lib")
#else
#pragma comment(lib, "ostore.lib")
#endif
#endif

#ifdef __os_sol2c5
/* work around Sun bug in exception handling to prevent the */
  /* optimizer from removing try blocks without function calls in them */
  /* Also ensure that the register buffers are flushed to work around 
     another bug with the forte compiler. */ 
inline void _ODI_tix_dummy_fcn_call() {asm("ta 3");}

#elif defined(__os_cafe)
#define TIX_DUMMY1 _ODI_tix_dummy_fcn_call();
/* work around Sun bug in exception handling to prevent the */
  /* optimizer from removing try blocks without function calls in them */
inline void _ODI_tix_dummy_fcn_call() {}
#define TIX_DUMMY1 _ODI_tix_dummy_fcn_call();
#else
#define TIX_DUMMY1
#endif

#ifdef _OS_DECCXX
/* work around DEC bug in exception handling */
extern void _ODI_tix_dummy_fcn_call();
#define TIX_DUMMY2 _ODI_tix_dummy_fcn_call();
#else
#define TIX_DUMMY2
#endif

#define TIX_HANDLE(exception_handled) {				\
	tix_handler tix_local_handler(&exception_handled);	\
	try {	TIX_DUMMY1
            

#define TIX_HANDLE_IF(flag,exception_handled) {				\
	tix_handler tix_local_handler(flag ? &exception_handled : &tix_no_exception);	\
	try { TIX_DUMMY1

#define TIX_EXCEPTION } catch (tix_handler* handler) { \
	if (handler != &tix_local_handler) \
	  throw; \
	else \
	  tix_local_handler._unwind_part_2(); \
	} \
	TIX_DUMMY2 \
	if (tix_local_handler.signal_happened) {

#define TIX_END_HANDLE } }

#else /* _OS_CPP_EXCEPTIONS */

#define TIX_HANDLE(exception_handled) {				\
	tix_handler tix_local_handler(&exception_handled);	\
	if (!_ODI_setjmp(tix_local_handler.env)) {

#define TIX_HANDLE_IF(flag,exception_handled) {				\
	tix_handler tix_local_handler(flag ? &exception_handled : &tix_no_exception);	\
	if (!_ODI_setjmp(tix_local_handler.env)) {

#define TIX_EXCEPTION } else {

#define TIX_END_HANDLE } }

#endif /* _OS_CPP_EXCEPTIONS */

#endif /* __cplusplus */

#include <ostore/hdrend.hh>
#endif /* _TIX_H_ */
