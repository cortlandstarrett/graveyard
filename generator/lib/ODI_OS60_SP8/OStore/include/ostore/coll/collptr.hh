/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


 // file: collptr_hh
// Added 4/98 by fein
// This file contains the declaration of os_coll_ptr which is the new unit
// of collections storage.  This is needed for two reasons:
//   - Collections (6.0 and up are based on os_soft_pointers which must
//     be wrapped in class to be persistent.
//   - It allows changibility between the different soft pointer types
//     and hard pointers.


#ifndef COLLPTR_HH
#define COLLPTR_HH

#ifndef _OS_PSE_COLL
#include <ostore/hdrstart.hh>
#include <ostore/nclient/softptr.hh>
#else
#include <os_pse/psecoll/hdrstart.hh>
#include <os_pse/softptr.hh>
_OS_BEGIN_NAMESPACE(os_pse)
#endif

#if defined(__os_hp11)
#if defined(__ptr)
#undef __ptr
#endif
#if defined(_ptr)
#undef _ptr
#endif
#endif

// This is a dummy class that represents an os_soft_pointer32
class _OS_COLL_IMPORT os_coll_soft_pointer32_void {

public:
  // Construction/Destruction
  os_coll_soft_pointer32_void() {_ptr = 0;}
  os_coll_soft_pointer32_void(void* ptr) {_ptr = ptr;}
  os_coll_soft_pointer32_void(const os_coll_soft_pointer32_void & other) {_ptr = other._ptr;}
  ~os_coll_soft_pointer32_void() {}

public:
  // General use API
  void * resolve() const {return _ptr;} 

  // General use operator overloadings
  os_coll_soft_pointer32_void& operator=(void* ptr) {_ptr = ptr; return *this;}
  os_coll_soft_pointer32_void& operator=(os_coll_soft_pointer32_void const &r) {_ptr = r._ptr; return *this;} 
  operator void*() const {return _ptr;}
  
  os_boolean operator== (os_coll_soft_pointer32_void const& r) const {return (_ptr == r._ptr);} 
  os_boolean operator < (os_coll_soft_pointer32_void const& r) const {return (_ptr < r._ptr);} 
  os_boolean operator > (os_coll_soft_pointer32_void const& r) const {return (_ptr > r._ptr);} 
 
  os_boolean operator != (os_coll_soft_pointer32_void const& r) const {return (_ptr != r._ptr); }
  os_boolean operator >= (os_coll_soft_pointer32_void const& r) const {return (_ptr != r._ptr); }
  os_boolean operator <= (os_coll_soft_pointer32_void const& r) const {return (_ptr != r._ptr); }
 
  os_boolean operator ! () const {return (!_ptr);}

private:
  void * _ptr;

};

// This is a dummy class that represents an os_soft_pointer64
class _OS_COLL_IMPORT os_coll_soft_pointer64_void {

public:
  // Construction/Destruction
  os_coll_soft_pointer64_void() {_ptr = 0;}
  os_coll_soft_pointer64_void(void* ptr) {_ptr = ptr;}
  os_coll_soft_pointer64_void(const os_coll_soft_pointer64_void & other) {_ptr = other._ptr;}
  ~os_coll_soft_pointer64_void() {}

public:
  // General use API
  void * resolve() const {return _ptr;} 

  // General use operator overloadings
  os_coll_soft_pointer64_void& operator=(void* ptr) {_ptr = ptr; return *this;}
  os_coll_soft_pointer64_void& operator=(os_coll_soft_pointer64_void const &r) {_ptr = r._ptr; return *this;} 
  operator void*() const {return _ptr;}
  
  os_boolean operator== (os_coll_soft_pointer64_void const& r) const {return (_ptr == r._ptr);} 
  os_boolean operator < (os_coll_soft_pointer64_void const& r) const {return (_ptr < r._ptr);} 
  os_boolean operator > (os_coll_soft_pointer64_void const& r) const {return (_ptr > r._ptr);} 
 
  os_boolean operator != (os_coll_soft_pointer64_void const& r) const {return (_ptr != r._ptr); }
  os_boolean operator >= (os_coll_soft_pointer64_void const& r) const {return (_ptr != r._ptr); }
  os_boolean operator <= (os_coll_soft_pointer64_void const& r) const {return (_ptr != r._ptr); }
 
  os_boolean operator ! () const {return (!_ptr);}

private:
  void * _ptr;

};



// Only one of these should be defined at a time. 
#define COLL_SOFT_POINTERS
//#define COLL_USE_HARD_POINTERS


class _OS_COLL_IMPORT os_coll_ptr {

public:
  // Construction/Destruction
  os_coll_ptr() {_ptr = 0;}

  os_coll_ptr(void* ptr) {_ptr = ptr;}
  os_coll_ptr(const os_coll_ptr & ptr) {_ptr = ptr._ptr; }
  ~os_coll_ptr() {}

public:
  // General use API
  void* resolve() const {
#ifdef COLL_SOFT_POINTERS
    return _ptr.resolve();
#else
    return _ptr;
#endif
  }

  // General use operator overloadings
  os_coll_ptr& operator=(void* ptr) {
    _ptr = ptr;
    return *this;
  }

  os_coll_ptr& operator=(os_coll_ptr const &r) {
    _ptr = r._ptr;
    return *this;
  }

  operator void*() const {return _ptr;}
  
  os_boolean operator== (os_coll_ptr const& r) const {return (_ptr == r._ptr);}
  os_boolean operator== (void const* _p) const {return (_ptr == _p);}
  os_boolean operator < (os_coll_ptr const& r) const { return (_ptr < r._ptr);}
  os_boolean operator > (os_coll_ptr const& r) const { return (_ptr > r._ptr);}
 
  os_boolean operator != (os_coll_ptr const& r) const { return (_ptr != r._ptr);}
  os_boolean operator >= (os_coll_ptr const& r) const { return (_ptr >= r._ptr);}
  os_boolean operator <= (os_coll_ptr const& r) const { return (_ptr <= r._ptr);}
 
  os_boolean operator ! () const {return !_ptr;}

  static os_typespec * get_os_typespec();
private:
  // This is the actual unit of storage
#ifdef COLL_SOFT_POINTERS
#ifdef _OS_64BIT_NATIVE
     os_soft_pointer64_void _ptr;
#else
     os_soft_pointer32_void _ptr;
#endif
#else
    void * _ptr;
#endif

};



typedef os_coll_ptr void_coll_ptr;

#if !defined(_OS_PSE_COLL)
#include <ostore/hdrend.hh>
#else
_OS_END_NAMESPACE
#include <os_pse/psecoll/hdrend.hh>
#endif

#endif

    

