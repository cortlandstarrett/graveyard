/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OPE_HH_
#define _OPE_HH_
#include <ostore/hdrstart.hh>

#include <ostore/ostore.hh>

/* classes defined in this file */
class os_ope;
class os_ope_generic_event;


#if defined(__STDC__)
#ifndef _OS_ANSI_TOKENS
#define _OS_ANSI_TOKENS
#endif
#endif

#ifdef _OS_ANSI_TOKENS

#define DEFINE_OPE_EVENT(name,options,parent) \
  os_ope_generic_event name(#name,options,parent)
#define DEFINE_OPE_EVENT_NAMEONLY(name) \
  os_ope_generic_event name
#define DECLARE_OPE_EVENT(name) \
  extern os_ope_generic_event name
#define INITIALIZE_OPE_EVENT(name,options,parent) \
  name._initialize(#name,parent,options)

#else

#define DEFINE_OPE_EVENT(name,options,parent) \
  os_ope_generic_event name("name",options,parent)
#define DEFINE_OPE_EVENT_NAMEONLY(name) \
  os_ope_generic_event name
#define DECLARE_OPE_EVENT(name) \
  extern os_ope_generic_event name
#define INITIALIZE_OPE_EVENT(name,options,parent) \
  name._initialize("name",parent,options)
  
#endif /* _OS_ANSI_TOKENS */


/*
 ****************************************************************************
 *                                                                          *
 * OPE Retriever API                                                        *
 *                                                                          *
 ****************************************************************************
 */

extern void os_ope_link_initialize();
extern void os_ope_coll_link_initialize();

class _OS_DLLIMPORT(_OS_CLIENT) os_ope {
public:
  static void start( char const * fp =0 );
  static void stop()    { _forward(api_stop); }
  static void suspend() { _forward(api_suspend); }
  static void resume()  { _forward(api_resume); }

  /* For ObjectStore use only */
  enum { api_unknown, api_start, api_stop, api_suspend, api_resume };
private:
  static void _forward( os_unsigned_int32, ... );
};  

/*
 ****************************************************************************
 *                                                                          *
 * generic event                                                            *
 *                                                                          *
 ****************************************************************************
 */

class _OS_DLLIMPORT(_OS_CLIENT) os_ope_generic_event {
public:
  enum { svr_mtr = 1<<10, counter = 1<<11, always_enabled = 1<<12 };

  os_ope_generic_event(char* name, 
		       os_unsigned_int32 options = 0,
		       os_ope_generic_event *parent = 0);

  void raise_single( const char* format, ...);
  void raise_single( void* adr,         const char* format =0, ...);
  void raise_single( os_unsigned_int32, const char* format =0, ...);
  void raise_single( os_cluster*,       const char* format =0, ...);
  void raise_single( os_segment*,       const char* format =0, ...);
  void raise_single( os_database*,      const char* format =0, ...);

  void raise_before( const char* format, ...);
  void raise_before( void* adr,         const char* format =0, ...);
  void raise_before( os_unsigned_int32, const char* format =0, ...);
  void raise_before( os_cluster*,       const char* format =0, ...);
  void raise_before( os_segment*,       const char* format =0, ...);
  void raise_before( os_database*,      const char* format =0, ...);

  void raise_after( const char* format, ...);
  void raise_after( void* adr,         const char* format =0, ...);
  void raise_after( os_unsigned_int32, const char* format =0, ...);
  void raise_after( os_cluster*,       const char* format =0, ...);
  void raise_after( os_segment*,       const char* format =0, ...);
  void raise_after( os_database*,      const char* format =0, ...);

  void vraise_single( const char* format, va_list);
  void vraise_before( const char* format, va_list);
  void vraise_after ( const char* format, va_list);

  /* For ObjectStore use only */
  void _initialize(char* n, os_ope_generic_event *par=0, os_unsigned_int32 = 0);
  os_ope_generic_event();
protected:
  char *name;
  os_ope_generic_event *parent;
  char *env;
  os_unsigned_int32 options;
private:
  void _raise(os_unsigned_int32, void*, const char* format, va_list);
};

#include <ostore/hdrend.hh>
#endif /* _OPE_HH_ */
