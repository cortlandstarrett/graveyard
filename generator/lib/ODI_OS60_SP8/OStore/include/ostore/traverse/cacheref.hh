/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CACHEREF_HH
#define CACHEREF_HH
/***********************************************************************
*                                                                      *
* Copyright (c) 1991-2000 by eXcelon Corporation. All Rights Reserved.                          *
*                                                                      *
* eXcelon Corporation Confidential Restricted material.  This work     *
* contains confidential trade secrets of eXcelon Corp..  Use,          *
* examination, copying, transfer and/or disclosure to others are       *
* prohibited, except with the express written agreement of eXcelon     *
* Corp.                                                                *
*                                                                      *
* THIS WORK IS PROVIDED AS IS, WHERE IS, WITH ABSOLUTELY NO WARRANTIES *
* WHATSOEVER, WHETHER EXPRESS OR IMPLIED.                              *
*                                                                      *
***********************************************************************/

/*----------------------------------------------------------------------
  C++ Module Header
------------------------------------------------------------------------
  Module Name : cacheref.hh
------------------------------------------------------------------------
  Description: Provides a cached referece class for efficient referencing
               of objects from persistent storage.
----------------------------------------------------------------------*/


//-- Include files -----------------------------------------------------

#include <ostore/ostore.hh>


/***********************************************************************
  class os_Cached_reference
***********************************************************************/

template <class T>
class _OS_DLLIMPORT(_OS_TRAVERSE) os_Cached_reference {

  public: // Construction
    os_Cached_reference ();
    os_Cached_reference (const T*);
    os_Cached_reference (const os_Cached_reference<T>&);
    ~os_Cached_reference ();

  public: // Assignment operators
    os_Cached_reference<T>& operator = (const T*);
    os_Cached_reference<T>& operator = (const os_Cached_reference<T>&);

  public: // Accessors
    T* resolve () const;
    operator T* () const;
    T* operator -> () const;
    T& operator * () const;
    T& operator [] (unsigned long index) const;

  public: // Negation operator
    os_boolean operator ! () const;

  public: // Comparision operators
    os_boolean operator == (const os_Cached_reference<T>&) const;
    os_boolean operator != (const os_Cached_reference<T>&) const;
    os_boolean operator < (const os_Cached_reference<T>&) const;
    os_boolean operator <= (const os_Cached_reference<T>&) const;
    os_boolean operator >= (const os_Cached_reference<T>&) const;
    os_boolean operator > (const os_Cached_reference<T>&) const;

    os_boolean operator == (const T*) const;
    os_boolean operator != (const T*) const;
    os_boolean operator < (const T*) const;
    os_boolean operator <= (const T*) const;
    os_boolean operator >= (const T*) const;
    os_boolean operator > (const T*) const;

  protected: // Embedded data
    os_Reference_transient<T> reference;
    T* pointer;
    long count;

  public: // Instantiation
    static int _instantiate ();

  };

#endif /* CACHEREF_HH */

