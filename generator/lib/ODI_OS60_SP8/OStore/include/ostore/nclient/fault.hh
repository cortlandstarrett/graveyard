/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_FAULT
#define CLIENT_INTERFACE_FAULT 1

#include <ostore/portypes.hh>
#include <ostore/hdrstart.hh>

#ifdef _OS_Win32
struct OS_EXCEPTION_POINTERS;
typedef void (__cdecl *os_se_translator_function)(os_unsigned_int32, struct OS_EXCEPTION_POINTERS*);
#endif

#ifdef _AIX
/* access these from dbx to trap on faults */

/* examine this when you see a stack trace with the signal handler
   at the bottom */
extern int _Os_fault_count;
/* set this to the value of _Os_fault_count - 1 */
extern int _Os_fault_trap;
/* set a breakpoint on this */
extern "C" void _Os_fault_bk();
#endif

/* _ODI_fault_handler is used to control the lifetime of the fault
 * translator for the thread.  The default usage of _ODI_fault_handler
 * creates the fault translator in its constructor for the first
 * (outermost) instance of the class, and removes the fault translator
 * in the destructor of that first (outermost) instance.  The field
 * remove_fault_handler is initialized to true if a fault
 * translator does not exist in this thread at the time the instance is
 * constructed, and to false if a fault translator does exist.
 * remove_fault_handler is used only by the destructor to
 * determine if the fault translator and potentially per thread data
 * should be removed from the thread.  Nested instances of this class
 * basically do nothing.
 * The method remove_fault_translator_at_end is provided to override
 * the default behavior, and allow the application to explicitly
 * control when the fault translator is removed and other per thread 
 * data cleanup is performed.  It resets the remove_fault_handler
 * field.  The destructor will perform no action
 * if remove_fault_handler is false.  If it is true, it will
 * remove the fault translator, and if the field do_per_thread_cleanup
 * is true, will perform cleanup on per thread data. 
 */
class _OS_DLLIMPORT(_OS_CLIENT) _ODI_fault_handler {
private:
  os_boolean do_per_thread_cleanup;
  os_boolean remove_fault_handler;
public:
  _ODI_fault_handler();
  _ODI_fault_handler(os_boolean do_per_thread_cleanup_arg);
  ~_ODI_fault_handler();
  void remove_fault_translator_at_end( os_boolean b );
#if defined(_OS_OS2)
private:
  os_unsigned_int32 handler[4];
#endif	/* _OS_OS2 */
};

class os_session;

#if defined(_OS_Win32)
/* On Win32, we have an se_translator function that actually does all
** the work.  It's set by _ODI_fault_handler and reset by the dtor.
** _ODI_fault_handler sets the flag so you don't get an error
** saying you omit the macro.  The catch will never happen. */
#define OS_ESTABLISH_FAULT_HANDLER { \
  try { _ODI_fault_handler _ODI_handler;
/* OS_ESTABLISH_FAULT_HANDLER_WITH_CLEANUP() is used by OSJI */
#define OS_ESTABLISH_FAULT_HANDLER_WITH_CLEANUP(DO_CLEANUP) { \
  try { _ODI_fault_handler _ODI_handler(DO_CLEANUP);
#define OS_END_FAULT_HANDLER \
      } catch (_ODI_fault_handler&) {} }
#else
#define OS_ESTABLISH_FAULT_HANDLER {{ \
  _ODI_fault_handler _ODI_handler;
#define OS_ESTABLISH_FAULT_HANDLER_WITH_CLEANUP(DO_CLEANUP) {{ \
  _ODI_fault_handler _ODI_handler(DO_CLEANUP);
#define OS_END_FAULT_HANDLER }}
#endif

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_FAULT */
