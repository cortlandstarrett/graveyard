/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CACHEREF_HC
#define CACHEREF_HC

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
  C++ Module Body
------------------------------------------------------------------------
  Module Name : handle.cc
------------------------------------------------------------------------
  Description: Provides a handle class for efficient referencing of
               objects from transient storage.
----------------------------------------------------------------------*/


//---- Includes --------------------------------------------------------

#include <ostore/osreleas.hh>
#include <ostore/ostore.hh>
//#include <ostore/traverse/inplace.hh>
#if defined(__os_cafe) || defined(_OS_DECCXX) || defined(__os_hp11)
/* CAFE dosen't like both an extern and an inline. */
#include <new.h>
#else
inline void* operator new(size_t _OS_DBALLOC_PARMS,void* loc);//{return loc;}
//#if _OS_MicrosoftCC >= 1200 /* accomodate Visual C++ 6.0 */
//static inline
//void operator delete(void*,void*) { /* do nothing */}
//#endif
#endif
#include <ostore/traverse/cacheref.hh>


/***********************************************************************
  Function:     get_address_space_change_count
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

inline long get_address_space_change_count ()
{
#if OS_MAJOR_RELEASE > 5 || (OS_MAJOR_RELEASE == 5 && OS_MINOR_RELEASE >= 1)
  return objectstore::get_address_space_generation_number();
#else
  extern long _Trans_count; 
  return _Trans_count;
#endif /* OS_MAJOR_RELEASE */
}


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Class:       os_Cached_reference
  Description: 
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/


/***********************************************************************
  Method:      os_Cached_reference::os_Cached_reference
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_Cached_reference<T>::os_Cached_reference ()
{
  reference = 0;
  pointer = 0;
  count = 0;
}


/***********************************************************************
  Method:      os_Cached_reference::os_Cached_reference
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_Cached_reference<T>::os_Cached_reference (const T* address)
{
  reference = address;
  pointer = (T*) address;
  count = get_address_space_change_count();
}


/***********************************************************************
  Method:      os_Cached_reference::os_Cached_reference
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_Cached_reference<T>::os_Cached_reference
  (const os_Cached_reference<T>& handle)
{
  reference = handle.reference;
  pointer = handle.pointer;
  count = handle.count;
}


/***********************************************************************
  Method:      os_Cached_reference::~os_Cached_reference
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_Cached_reference<T>::~os_Cached_reference ()
{
  reference = 0;
  pointer = 0;
  count = 0;
}


/***********************************************************************
  Method:      os_Cached_reference::operator =
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_Cached_reference<T>& os_Cached_reference<T>::operator = (const T* object)
{
  ::new(this) os_Cached_reference<T>(object);
  return *this;
}


/***********************************************************************
  Method:      os_Cached_reference::operator =
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_Cached_reference<T>& os_Cached_reference<T>::operator =
  (const os_Cached_reference<T>& handle)
{
  ::new(this) os_Cached_reference<T>(handle);
  return *this;
}


/***********************************************************************
  Method:      os_Cached_reference::resolve
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
T* os_Cached_reference<T>::resolve () const
{
  /* Note that the following implementation defeats any const-ness
     of the given os_Cached_reference<T>. */

  if (count != get_address_space_change_count()) {
      T** non_const_pointer = (T**)&pointer;
      *non_const_pointer = reference;
      long* non_const_count = (long*)&count;
      *non_const_count = get_address_space_change_count();
    }
  return pointer;
}


/***********************************************************************
  Method:      os_Cached_reference::operator T*
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_Cached_reference<T>::operator T* () const
{
  return resolve();
}


/***********************************************************************
  Method:      os_Cached_reference::operator ->
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
T* os_Cached_reference<T>::operator -> () const
{
  return resolve();
}


/***********************************************************************
  Method:      os_Cached_reference::operator *
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
T& os_Cached_reference<T>::operator * () const
{
  return *resolve();
}


/***********************************************************************
  Method:      os_Cached_reference::operator []
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
T& os_Cached_reference<T>::operator [] (unsigned long index) const
{
  T* base_address = resolve();
  return base_address[index];
}


/***********************************************************************
  Method:      os_Cached_reference::operator !
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator ! () const
{
  if (os_transaction::get_current())
      return ! resolve();
  else
      return ! reference;
}


/***********************************************************************
  Method:      os_Cached_reference::operator == 
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator ==
  (const os_Cached_reference<T>& handle) const
{
  if (os_transaction::get_current())
      return resolve() == handle.resolve();
  else
      return reference == handle.reference;
}


/***********************************************************************
  Method:      os_Cached_reference::operator !=
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator !=
  (const os_Cached_reference<T>& handle) const
{
  if (os_transaction::get_current())
      return resolve() != handle.resolve();
  else
      return reference != handle.reference;
}


/***********************************************************************
  Method:      os_Cached_reference::operator <
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator <
  (const os_Cached_reference<T>& handle) const
{
  if (os_transaction::get_current())
      return resolve() < handle.resolve();
  else
      return reference < handle.reference;
}


/***********************************************************************
  Method:      os_Cached_reference::operator <=
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator <=
  (const os_Cached_reference<T>& handle) const
{
  if (os_transaction::get_current())
      return resolve() <= handle.resolve();
  else
      return reference <= handle.reference;
}


/***********************************************************************
  Method:      os_Cached_reference::operator >=
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator >=
  (const os_Cached_reference<T>& handle) const
{
  if (os_transaction::get_current())
      return resolve() >= handle.resolve();
  else
      return reference >= handle.reference;
}


/***********************************************************************
  Method:      os_Cached_reference::operator >
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator >
  (const os_Cached_reference<T>& handle) const
{
  if (os_transaction::get_current())
      return resolve() > handle.resolve();
  else
      return reference > handle.reference;
}


/***********************************************************************
  Method:      os_Cached_reference::operator ==
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator == (const T* pointer) const
{
  return resolve() == pointer;
}


/***********************************************************************
  Method:      os_Cached_reference::operator !=
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator != (const T* given) const
{
  return resolve() != given;
}


/***********************************************************************
  Method:      os_Cached_reference::operator <
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator < (const T* given) const
{
  return resolve() < given;
}


/***********************************************************************
  Method:      os_Cached_reference::operator <=
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator <= (const T* given) const
{
  return resolve() <= given;
}


/***********************************************************************
  Method:      os_Cached_reference::operator >=
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator >= (const T* given) const
{
  return resolve() >= given;
}


/***********************************************************************
  Method:      os_Cached_reference::operator >
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
os_boolean os_Cached_reference<T>::operator > (const T* given) const
{
  return resolve() > given;
}


/***********************************************************************
  Method:      os_Cached_reference::_instantiate
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class T>
int os_Cached_reference<T>::_instantiate ()
{
  return 0;
}


#endif /* CACHEREF_HC */

