/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/*
*/
#ifndef _fbinding_hh
#define _fbinding_hh	
#include <ostore/hdrstart.hh>

/* To avoid strdup inclusion follies */
extern char* _SE_strdup(const char*) ;

template <class Ftype> class os_func_ass {
public:
  char* 	class_name ;
  char*         fun_name ;
  
  const Ftype    	funcp ;
  os_func_ass(const char* cn, Ftype f, const char* fn=0)
    : class_name(cn ? _SE_strdup((char*)cn) : 0), funcp(f), 
      fun_name(fn ? _SE_strdup((char*)fn) : 0) {}
  
  os_func_ass(const os_func_ass<Ftype>& fb)
    : class_name((fb.class_name) ? _SE_strdup(fb.class_name):0),
       funcp(fb.funcp),
       fun_name(fb.fun_name ? _SE_strdup(fb.fun_name) : 0) {}
  
  ~os_func_ass() { 
    delete [] class_name ;
    delete [] fun_name ;}
} ;

#include <ostore/hdrend.hh>
#endif
