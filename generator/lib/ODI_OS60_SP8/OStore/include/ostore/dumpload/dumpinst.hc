/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


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
#include <ostore/coll.hh>
#include <ostore/coll/dict_pt.hh>
#include <ostore/coll/dict_pt.cc>

#include <ostore/traverse/traverse.hh>
#include <ostore/traverse/register.hh>
#ifndef _OS_DECCXX
//#include <ostore/traverse/register.hc>
#endif

#include <ostore/dumpload/dumper.hh>
#include <ostore/dumpload/planner.hh>

#if _OS_MicrosoftCC
#pragma warning(disable: 4660 4661)
#endif

//-- Forward Declarations ----------------------------------------------

typedef os_Dictionary<char*, os_Dumper_specialization*> 
    os_Dumper_specialization_dictionary; 

typedef os_Dictionary<char*, void*> os_Dumper_void_dictionary; 

#ifdef _OS_Win32
template os_Dictionary<char*, os_Dumper_specialization*>;

template os_Dictionary<char*, os_Planning_action*>;

template os_Dictionary<char*, void*>;

template os_Registration_entry<os_Dumper_specialization*, os_Dumper>;
template os_Registration_block<os_Dumper_specialization*, os_Dumper>;

template os_Registration_entry<os_Planning_action*, os_Dumper>;
template os_Registration_block<os_Planning_action*, os_Dumper>;

#endif /* _OS_Win32 */

#ifdef __os_linux
template os_Dictionary<char*, os_Dumper_specialization*>;

template os_Dictionary<char*, os_Planning_action*>;

template os_Dictionary<char*, void*>;

template os_Registration_entry<os_Dumper_specialization*, os_Dumper>;
template os_Registration_block<os_Dumper_specialization*, os_Dumper>;

template os_Registration_entry<os_Planning_action*, os_Dumper>;
template os_Registration_block<os_Planning_action*, os_Dumper>;

#endif /* __os_linux */
//-- Instantiations ----------------------------------------------------

#if !defined(_OS_DECCXX) || !defined(__os_sgi_mips)
void dumper_instantiations ()
{
  os_Dumper_specialization_dictionary dumper_specialization_dictionary;
  os_Collection<const char*> coll;
  os_Array<const char*> arr;
  os_Dumper_void_dictionary dumper_void_dictionary;
}
#endif



/***********************************************************************
  Marking os_Dictionary<char*, os_Class_specialization*>
***********************************************************************/

#ifndef OS_TRANSIENT_DICTIONARY_KEY_CHAR
#define OS_TRANSIENT_DICTIONARY_KEY_CHAR
OS_TRANSIENT_DICTIONARY(char*,os_Dumper_specialization*); 
#else
OS_TRANSIENT_DICTIONARY_NOKEY(char*,os_Dumper_specialization*); 
#endif /* OS_TRANSIENT_DICTIONARY_KEY_CHAR */

/***********************************************************************
  Marking os_Dictionary<char*, os_Planning_action*>
***********************************************************************/

#ifndef OS_TRANSIENT_DICTIONARY_KEY_CHAR
#define OS_TRANSIENT_DICTIONARY_KEY_CHAR
OS_TRANSIENT_DICTIONARY(char*,os_Planning_action*); 
#else
OS_TRANSIENT_DICTIONARY_NOKEY(char*,os_Planning_action*); 
#endif /* OS_TRANSIENT_DICTIONARY_KEY_CHAR */

/***********************************************************************
  Marking os_Dictionary<char*, void*>
***********************************************************************/

#ifndef OS_TRANSIENT_DICTIONARY_KEY_CHAR
#define OS_TRANSIENT_DICTIONARY_KEY_CHAR
OS_TRANSIENT_DICTIONARY(char*,void*); 
#else
OS_TRANSIENT_DICTIONARY_NOKEY(char*,void*); 
#endif /* OS_TRANSIENT_DICTIONARY_KEY_CHAR */

#ifdef _OS_HP_aCC

template _CLASS os_Dictionary<char*,  _CLASS os_Dumper_specialization*>;

template _CLASS os_Dictionary<char*,  _CLASS os_Planning_action*>;

template _CLASS os_Dictionary<char*, void*>;

template _CLASS os_Registration_block< _CLASS os_Dumper_specialization*,  _CLASS os_Dumper>;
template _CLASS os_Registration_entry< _CLASS os_Dumper_specialization*,  _CLASS os_Dumper>;

template _CLASS os_Registration_block< _CLASS os_Planning_action*,  _CLASS os_Dumper>;
template _CLASS os_Registration_entry< _CLASS os_Planning_action*,  _CLASS os_Dumper>;

#endif /* _OS_HP_aCC */

#ifdef __os_sol2c5

template class os_Dictionary<char*,  class os_Dumper_specialization*>;

template class os_Dictionary<char*,  class os_Planning_action*>;

template class os_Dictionary<char*, void*>;

template class os_Registration_block< class os_Dumper_specialization*,  class os_Dumper>;
template class os_Registration_entry< class os_Dumper_specialization*,  class os_Dumper>;

template class os_Registration_block< class os_Planning_action*,  class os_Dumper>;
template class os_Registration_entry< class os_Planning_action*,  class os_Dumper>;


#endif /* __os_sol2c5 */

#ifdef _OS_DECCXX
#pragma define_template os_Dictionary<char*, os_Dumper_specialization*>
#pragma define_template os_Dictionary<char*, os_Planning_action*>
#pragma define_template os_Dictionary<char*, void*>

#pragma define_template os_Registration_entry<os_Dumper_specialization*, os_Dumper>
#pragma define_template os_Registration_entry<os_Planning_action*, os_Dumper>

#pragma define_template os_Registration_block<os_Dumper_specialization*, os_Dumper>
#pragma define_template os_Registration_block<os_Planning_action*, os_Dumper>

#endif /* _OS_DECCXX */

#ifdef __os_sgi_mips
#pragma instantiate os_Dictionary<char*, os_Dumper_specialization*>
#pragma instantiate os_Dictionary<char*, os_Planning_action*>
#pragma instantiate os_Dictionary<char*, void*>

#pragma instantiate os_Registration_entry<os_Dumper_specialization*, os_Dumper>
#pragma instantiate os_Registration_entry<os_Planning_action*, os_Dumper>

#pragma instantiate os_Registration_block<os_Dumper_specialization*, os_Dumper>
#pragma instantiate os_Registration_block<os_Planning_action*, os_Dumper>


#endif /* __os_sig_mips */








