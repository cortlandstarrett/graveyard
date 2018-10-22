/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef VALUE_HC
#define VALUE_HC

/***********************************************************************
*                                                                      *
* Copyright (c) 1997-2000 by eXcelon Corporation. All Rights Reserved.                          *
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

//-- Include files -----------------------------------------------------

#include <iostream.h>
#include <ostore/dumpload/value.hh>
#include <ostore/ostore.hh>
#include <ostore/msgsys/msglod.hh>


/***********************************************************************
  class os_Input_value<Type>
***********************************************************************/

template<class Type>
os_Input_value<Type>::os_Input_value (Type& given_value_storage)
    : os_Input_value_t()
{
  value_storage = &given_value_storage;
}


template<class Type>
os_Input_value<Type>::os_Input_value ()
{
  value_storage = 0;
}


template<class Type>
os_Input_value<Type>::~os_Input_value ()
{
  value_storage = 0;
}


template<class Type>
Type& os_Input_value<Type>::get_value_storage () const
{
  if ( ! value_storage)
      os_Loader_messages::OS_FATAL(os_Loader_messages::input_value_get_value_storage);
  return *value_storage;
}


template<class Type>
void os_Input_value<Type>::bind (const char* actual_value,
			   os_boolean& has_error)
{
  has_error = _FALSE;
  if ( ! value_storage)
      os_Loader_messages::OS_FATAL(os_Loader_messages::input_value_bind);
  bind(actual_value, *value_storage, has_error);
  if ( ! has_error)
      set_is_bound(_TRUE);
}


template<class Type>
void os_Input_value<Type>::bind (const char* actual_value,
			   Type& given_value_storage,
			   os_boolean& has_error)
{
  set(given_value_storage, actual_value, has_error);
}


template<class Type>
void os_Input_value<Type>::display () const
{
  os_Input_value_t::display();
  cout << "    value_storage = (" << (void*)value_storage << ')';
  if (value_storage)
      cout << ' ' << get_string(*value_storage);
}


template<class Type>
os_Input_value_t::Kind os_Input_value<Type>::get_kind () const
{
  if ( ! value_storage)
      os_Loader_messages::OS_FATAL(os_Loader_messages::input_value_get_kind);
  return os_Input_value_t::get_kind(*value_storage);
}


template<class Type>
const char* os_Input_value<Type>::get_kind_string () const
{
  if ( ! value_storage)
      os_Loader_messages::OS_FATAL(os_Loader_messages::input_value_get_kind_string);
  return os_Input_value_t::get_kind_string(*value_storage);
}


#endif /* VALUE_HC */
