/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef OSTORE_TRAVERSE_INSTANTI_HC
#define OSTORE_TRAVERSE_INSTANTI_HC

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

#include <ostore/ostore.hh>
#include <ostore/mop.hh>

#include <ostore/traverse/traverse.hh>
#include <ostore/traverse/cls_act.hh>
#include <ostore/traverse/argument.hh>
#include <ostore/traverse/argument.hc>

//-- Forward Declarations ----------------------------------------------

#if defined (_OS_Win32)
//TODO determine correct mechanism to properly export template instantiations.

#define MY_EXPORT class __declspec(dllexport)

template MY_EXPORT os_Argument_pt<enum os_Argument::Boolean>;
template MY_EXPORT os_Argument_pt<char>;
template MY_EXPORT os_Argument_pt<short>;
template MY_EXPORT os_Argument_pt<unsigned short>;
template MY_EXPORT os_Argument_pt<int>;
template MY_EXPORT os_Argument_pt<unsigned int>;
template MY_EXPORT os_Argument_pt<long>;
template MY_EXPORT os_Argument_pt<unsigned long>;
template MY_EXPORT os_Argument_pt<float>;
template MY_EXPORT os_Argument_pt<double>;
template MY_EXPORT os_Argument_pt<char*>;
template MY_EXPORT os_Argument_pt<const char*>;


template MY_EXPORT os_Argument_positional<os_Argument::Boolean>;
template MY_EXPORT os_Argument_positional<char>;
template MY_EXPORT os_Argument_positional<short>;
template MY_EXPORT os_Argument_positional<unsigned short>;
template MY_EXPORT os_Argument_positional<int>;
template MY_EXPORT os_Argument_positional<unsigned>;
template MY_EXPORT os_Argument_positional<long>;
template MY_EXPORT os_Argument_positional<unsigned long>;
template MY_EXPORT os_Argument_positional<const char*>;
template MY_EXPORT os_Argument_positional<char*>;
template MY_EXPORT os_Argument_positional<float>;
template MY_EXPORT os_Argument_positional<double>;

template MY_EXPORT os_Argument_keyword<os_Argument::Boolean>;
template MY_EXPORT os_Argument_keyword<char>;
template MY_EXPORT os_Argument_keyword<short>;
template MY_EXPORT os_Argument_keyword<unsigned short>;
template MY_EXPORT os_Argument_keyword<int>;
template MY_EXPORT os_Argument_keyword<unsigned>;
template MY_EXPORT os_Argument_keyword<long>;
template MY_EXPORT os_Argument_keyword<unsigned long>;
template MY_EXPORT os_Argument_keyword<const char*>;
template MY_EXPORT os_Argument_keyword<char*>;
template MY_EXPORT os_Argument_keyword<float>;
template MY_EXPORT os_Argument_keyword<double>;

template MY_EXPORT os_Argument_keyword_with_values<os_Argument::Boolean>;
template MY_EXPORT os_Argument_keyword_with_values<char>;
template MY_EXPORT os_Argument_keyword_with_values<short>;
template MY_EXPORT os_Argument_keyword_with_values<unsigned short>;
template MY_EXPORT os_Argument_keyword_with_values<int>;
template MY_EXPORT os_Argument_keyword_with_values<unsigned>;
template MY_EXPORT os_Argument_keyword_with_values<long>;
template MY_EXPORT os_Argument_keyword_with_values<unsigned long>;
template MY_EXPORT os_Argument_keyword_with_values<const char*>;
template MY_EXPORT os_Argument_keyword_with_values<char*>;
template MY_EXPORT os_Argument_keyword_with_values<float>;
template MY_EXPORT os_Argument_keyword_with_values<double>;

template MY_EXPORT os_Argument_optional<os_Argument::Boolean>;
template MY_EXPORT os_Argument_optional<char>;
template MY_EXPORT os_Argument_optional<short>;
template MY_EXPORT os_Argument_optional<unsigned short>;
template MY_EXPORT os_Argument_optional<int>;
template MY_EXPORT os_Argument_optional<unsigned>;
template MY_EXPORT os_Argument_optional<long>;
template MY_EXPORT os_Argument_optional<unsigned long>;
template MY_EXPORT os_Argument_optional<const char*>;
template MY_EXPORT os_Argument_optional<char*>;
template MY_EXPORT os_Argument_optional<float>;
template MY_EXPORT os_Argument_optional<double>;

template MY_EXPORT os_Argument_always<os_Argument::Boolean>;
template MY_EXPORT os_Argument_always<char>;
template MY_EXPORT os_Argument_always<short>;
template MY_EXPORT os_Argument_always<unsigned short>;
template MY_EXPORT os_Argument_always<int>;
template MY_EXPORT os_Argument_always<unsigned>;
template MY_EXPORT os_Argument_always<long>;
template MY_EXPORT os_Argument_always<unsigned long>;
template MY_EXPORT os_Argument_always<const char*>;
template MY_EXPORT os_Argument_always<char*>;
template MY_EXPORT os_Argument_always<float>;
template MY_EXPORT os_Argument_always<double>;

#endif 


#if defined(_OS_HP_aCC) || defined(__os_linux)
template _CLASS os_Argument_positional<os_Argument::Boolean>;
template _CLASS os_Argument_positional<char>;
template _CLASS os_Argument_positional<short>;
template _CLASS os_Argument_positional<unsigned short>;
template _CLASS os_Argument_positional<int>;
template _CLASS os_Argument_positional<unsigned>;
template _CLASS os_Argument_positional<long>;
template _CLASS os_Argument_positional<unsigned long>;
template _CLASS os_Argument_positional<const char*>;
template _CLASS os_Argument_positional<char*>;
template _CLASS os_Argument_positional<float>;
template _CLASS os_Argument_positional<double>;

template _CLASS os_Argument_keyword<os_Argument::Boolean>;
template _CLASS os_Argument_keyword<char>;
template _CLASS os_Argument_keyword<short>;
template _CLASS os_Argument_keyword<unsigned short>;
template _CLASS os_Argument_keyword<int>;
template _CLASS os_Argument_keyword<unsigned>;
template _CLASS os_Argument_keyword<long>;
template _CLASS os_Argument_keyword<unsigned long>;
template _CLASS os_Argument_keyword<const char*>;
template _CLASS os_Argument_keyword<char*>;
template _CLASS os_Argument_keyword<float>;
template _CLASS os_Argument_keyword<double>;

template _CLASS os_Argument_keyword_with_values<os_Argument::Boolean>;
template _CLASS os_Argument_keyword_with_values<char>;
template _CLASS os_Argument_keyword_with_values<short>;
template _CLASS os_Argument_keyword_with_values<unsigned short>;
template _CLASS os_Argument_keyword_with_values<int>;
template _CLASS os_Argument_keyword_with_values<unsigned>;
template _CLASS os_Argument_keyword_with_values<long>;
template _CLASS os_Argument_keyword_with_values<unsigned long>;
template _CLASS os_Argument_keyword_with_values<const char*>;
template _CLASS os_Argument_keyword_with_values<char*>;
template _CLASS os_Argument_keyword_with_values<float>;
template _CLASS os_Argument_keyword_with_values<double>;

template _CLASS os_Argument_optional<os_Argument::Boolean>;
template _CLASS os_Argument_optional<char>;
template _CLASS os_Argument_optional<short>;
template _CLASS os_Argument_optional<unsigned short>;
template _CLASS os_Argument_optional<int>;
template _CLASS os_Argument_optional<unsigned>;
template _CLASS os_Argument_optional<long>;
template _CLASS os_Argument_optional<unsigned long>;
template _CLASS os_Argument_optional<const char*>;
template _CLASS os_Argument_optional<char*>;
template _CLASS os_Argument_optional<float>;
template _CLASS os_Argument_optional<double>;

template _CLASS os_Argument_always<os_Argument::Boolean>;
template _CLASS os_Argument_always<char>;
template _CLASS os_Argument_always<short>;
template _CLASS os_Argument_always<unsigned short>;
template _CLASS os_Argument_always<int>;
template _CLASS os_Argument_always<unsigned>;
template _CLASS os_Argument_always<long>;
template _CLASS os_Argument_always<unsigned long>;
template _CLASS os_Argument_always<const char*>;
template _CLASS os_Argument_always<char*>;
template _CLASS os_Argument_always<float>;
template _CLASS os_Argument_always<double>;

#endif /* _OS_Win32 */


//-- Instantiations ----------------------------------------------------

void traverse_instantiations ()
{
  os_Argument_positional<os_Argument::Boolean> argument_positional_boolean;
  os_Argument_positional<char> argument_positional_char;
  os_Argument_positional<short> argument_positional_short;
  os_Argument_positional<unsigned short> argument_positional_unsigned_short;
  os_Argument_positional<int> argument_positional_int;
  os_Argument_positional<unsigned> argument_positional_unsigned;
  os_Argument_positional<long> argument_positional_long;
  os_Argument_positional<unsigned long> argument_positional_unsigned_long;
  os_Argument_positional<const char*> argument_positional_const_charp;
  os_Argument_positional<char*> argument_positional_charp;
  os_Argument_positional<float> argument_positional_float;
  os_Argument_positional<double> argument_positional_double;

  os_Argument_keyword<os_Argument::Boolean> argument_keyword_boolean;
  os_Argument_keyword<char> argument_keyword_char;
  os_Argument_keyword<short> argument_keyword_short;
  os_Argument_keyword<unsigned short> argument_keyword_unsigned_short;
  os_Argument_keyword<int> argument_keyword_int;
  os_Argument_keyword<unsigned> argument_keyword_unsigned;
  os_Argument_keyword<long> argument_keyword_long;
  os_Argument_keyword<unsigned long> argument_keyword_unsigned_long;
  os_Argument_keyword<const char*> argument_keyword_const_charp;
  os_Argument_keyword<char*> argument_keyword_charp;
  os_Argument_keyword<float> argument_keyword_float;
  os_Argument_keyword<double> argument_keyword_double;

  os_Argument_optional<os_Argument::Boolean> argument_optional_boolean;
  os_Argument_optional<char> argument_optional_char;
  os_Argument_optional<short> argument_optional_short;
  os_Argument_optional<unsigned short> argument_optional_unsigned_short;
  os_Argument_optional<int> argument_optional_int;
  os_Argument_optional<unsigned> argument_optional_unsigned;
  os_Argument_optional<long> argument_optional_long;
  os_Argument_optional<unsigned long> argument_optional_unsigned_long;
  os_Argument_optional<const char*> argument_optional_const_charp;
  os_Argument_optional<char*> argument_optional_charp;
  os_Argument_optional<float> argument_optional_float;
  os_Argument_optional<double> argument_optional_double;

  os_Argument_always<os_Argument::Boolean> argument_always_boolean;
  os_Argument_always<char> argument_always_char;
  os_Argument_always<short> argument_always_short;
  os_Argument_always<unsigned short> argument_always_unsigned_short;
  os_Argument_always<int> argument_always_int;
  os_Argument_always<unsigned> argument_always_unsigned;
  os_Argument_always<long> argument_always_long;
  os_Argument_always<unsigned long> argument_always_unsigned_long;
  os_Argument_always<const char*> argument_always_const_charp;
  os_Argument_always<char*> argument_always_charp;
  os_Argument_always<float> argument_always_float;
  os_Argument_always<double> argument_always_double;

  os_Argument_keyword_with_values<os_Argument::Boolean> 
      argument_keyword_with_values_boolean;
  os_Argument_keyword_with_values<char> argument_keyword_with_values_char;
  os_Argument_keyword_with_values<short> argument_keyword_with_values_short;
  os_Argument_keyword_with_values<unsigned short>
      argument_keyword_with_values_unsigned_short;
  os_Argument_keyword_with_values<int> argument_keyword_with_values_int;
  os_Argument_keyword_with_values<unsigned>
      argument_keyword_with_values_unsigned;
  os_Argument_keyword_with_values<long> argument_keyword_with_values_long;
  os_Argument_keyword_with_values<unsigned long>
      argument_keyword_with_values_unsigned_long;
  os_Argument_keyword_with_values<const char*>
      argument_keyword_with_values_const_charp;
  os_Argument_keyword_with_values<char*>
      argument_keyword_with_values_charp;
  os_Argument_keyword_with_values<float> argument_keyword_with_values_float;
  os_Argument_keyword_with_values<double> argument_keyword_with_values_double;

}

#ifdef _OS_DECCXX  /* Template instantiation for DEC */
#pragma define_template os_Argument_keyword<os_Argument::Boolean>
#pragma define_template os_Argument_keyword<char>
#pragma define_template os_Argument_keyword<short>
#pragma define_template os_Argument_keyword<unsigned short>
#pragma define_template os_Argument_keyword<int>
#pragma define_template os_Argument_keyword<unsigned>
#pragma define_template os_Argument_keyword<long>
#pragma define_template os_Argument_keyword<unsigned long>
#pragma define_template os_Argument_keyword<const char*>
#pragma define_template os_Argument_keyword<char*>
#pragma define_template os_Argument_keyword<float>
#pragma define_template os_Argument_keyword<double>

#pragma define_template os_Argument_positional<os_Argument::Boolean>
#pragma define_template os_Argument_positional<char>
#pragma define_template os_Argument_positional<short>
#pragma define_template os_Argument_positional<unsigned short>
#pragma define_template os_Argument_positional<int>
#pragma define_template os_Argument_positional<unsigned>
#pragma define_template os_Argument_positional<long>
#pragma define_template os_Argument_positional<unsigned long>
#pragma define_template os_Argument_positional<const char*>
#pragma define_template os_Argument_positional<char*>
#pragma define_template os_Argument_positional<float>
#pragma define_template os_Argument_positional<double>

#pragma define_template os_Argument_optional<os_Argument::Boolean>
#pragma define_template os_Argument_optional<char>
#pragma define_template os_Argument_optional<short>
#pragma define_template os_Argument_optional<unsigned short>
#pragma define_template os_Argument_optional<int>
#pragma define_template os_Argument_optional<unsigned>
#pragma define_template os_Argument_optional<long>
#pragma define_template os_Argument_optional<unsigned long>
#pragma define_template os_Argument_optional<const char*>
#pragma define_template os_Argument_optional<char*>
#pragma define_template os_Argument_optional<float>
#pragma define_template os_Argument_optional<double>

#pragma define_template os_Argument_keyword_with_values<os_Argument::Boolean>
#pragma define_template os_Argument_keyword_with_values<char>
#pragma define_template os_Argument_keyword_with_values<short>
#pragma define_template os_Argument_keyword_with_values<unsigned short>
#pragma define_template os_Argument_keyword_with_values<int>
#pragma define_template os_Argument_keyword_with_values<unsigned>
#pragma define_template os_Argument_keyword_with_values<long>
#pragma define_template os_Argument_keyword_with_values<unsigned long>
#pragma define_template os_Argument_keyword_with_values<const char*>
#pragma define_template os_Argument_keyword_with_values<char*>
#pragma define_template os_Argument_keyword_with_values<float>
#pragma define_template os_Argument_keyword_with_values<double>

#pragma define_template os_Argument_always<os_Argument::Boolean>
#pragma define_template os_Argument_always<char>
#pragma define_template os_Argument_always<short>
#pragma define_template os_Argument_always<unsigned short>
#pragma define_template os_Argument_always<int>
#pragma define_template os_Argument_always<unsigned>
#pragma define_template os_Argument_always<long>
#pragma define_template os_Argument_always<unsigned long>
#pragma define_template os_Argument_always<const char*>
#pragma define_template os_Argument_always<char*>
#pragma define_template os_Argument_always<float>
#pragma define_template os_Argument_always<double>

#pragma define_template os_Argument_pt<char*>
#pragma define_template os_Argument_pt<const char*>
#pragma define_template os_Argument_pt<unsigned long>
#pragma define_template os_Argument_pt<long>
#pragma define_template os_Argument_pt<unsigned int>
#pragma define_template os_Argument_pt<int>
#pragma define_template os_Argument_pt<unsigned short>
#pragma define_template os_Argument_pt<short>
#pragma define_template os_Argument_pt<char>
#pragma define_template os_Argument_pt<os_Argument::Boolean>
#pragma define_template os_Argument_pt<float>
#pragma define_template os_Argument_pt<double>

#endif /* End for DEC */

#if defined (__os_sol2c5)
template class os_Argument_keyword<os_Argument::Boolean>;
template class os_Argument_keyword<char>;
template class os_Argument_keyword<short>;
template class os_Argument_keyword<unsigned short>;
template class os_Argument_keyword<int>;
template class os_Argument_keyword<unsigned>;
template class os_Argument_keyword<long>;
template class os_Argument_keyword<unsigned long>;
template class os_Argument_keyword<const char*>;
template class os_Argument_keyword<char*>;
template class os_Argument_keyword<float>;
template class os_Argument_keyword<double>;

template class os_Argument_positional<os_Argument::Boolean>;
template class os_Argument_positional<char>;
template class os_Argument_positional<short>;
template class os_Argument_positional<unsigned short>;
template class os_Argument_positional<int>;
template class os_Argument_positional<unsigned>;
template class os_Argument_positional<long>;
template class os_Argument_positional<unsigned long>;
template class os_Argument_positional<const char*>;
template class os_Argument_positional<char*>;
template class os_Argument_positional<float>;
template class os_Argument_positional<double>;

template class os_Argument_optional<os_Argument::Boolean>;
template class os_Argument_optional<char>;
template class os_Argument_optional<short>;
template class os_Argument_optional<unsigned short>;
template class os_Argument_optional<int>;
template class os_Argument_optional<unsigned>;
template class os_Argument_optional<long>;
template class os_Argument_optional<unsigned long>;
template class os_Argument_optional<const char*>;
template class os_Argument_optional<char*>;
template class os_Argument_optional<float>;
template class os_Argument_optional<double>;

template class os_Argument_keyword_with_values<os_Argument::Boolean>;
template class os_Argument_keyword_with_values<char>;
template class os_Argument_keyword_with_values<short>;
template class os_Argument_keyword_with_values<unsigned short>;
template class os_Argument_keyword_with_values<int>;
template class os_Argument_keyword_with_values<unsigned>;
template class os_Argument_keyword_with_values<long>;
template class os_Argument_keyword_with_values<unsigned long>;
template class os_Argument_keyword_with_values<const char*>;
template class os_Argument_keyword_with_values<char*>;
template class os_Argument_keyword_with_values<float>;
template class os_Argument_keyword_with_values<double>;

template class os_Argument_always<os_Argument::Boolean>;
template class os_Argument_always<char>;
template class os_Argument_always<short>;
template class os_Argument_always<unsigned short>;
template class os_Argument_always<int>;
template class os_Argument_always<unsigned>;
template class os_Argument_always<long>;
template class os_Argument_always<unsigned long>;
template class os_Argument_always<const char*>;
template class os_Argument_always<char*>;
template class os_Argument_always<float>;
template class os_Argument_always<double>;

template class os_Argument_pt<char*>;
template class os_Argument_pt<const char*>;
template class os_Argument_pt<unsigned long>;
template class os_Argument_pt<long>;
template class os_Argument_pt<unsigned int>;
template class os_Argument_pt<int>;
template class os_Argument_pt<unsigned short>;
template class os_Argument_pt<short>;
template class os_Argument_pt<char>;
template class os_Argument_pt<os_Argument::Boolean>;
template class os_Argument_pt<float>;
template class os_Argument_pt<double>;

#endif 

void goober ()
{

  os_Argument_keyword_with_values<char const *> char_arg;
}

#endif /* OSTORE_TRAVERSE_INSTANTI_HC */



