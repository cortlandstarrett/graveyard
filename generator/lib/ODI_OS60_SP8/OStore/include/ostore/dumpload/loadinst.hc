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
#ifdef _OS_Win32
#include <ostore/traverse/instanti.hc>
#endif /* _OS_Win32 */
#include <ostore/traverse/register.hh>
#include <ostore/dumpload/loader.hh>
#include <ostore/dumpload/dumper.hh>
#include <ostore/dumpload/obj_loader.hh>
#include <ostore/dumpload/fix_load.hh>
//#include <ostore/dumpload/jstring_wrapper.hh>

#if _OS_MicrosoftCC
#pragma warning(disable: 4660 4661)
#endif

//-- Forward Declarations ----------------------------------------------

#if defined(_OS_Win32) || defined(__os_linux)
template os_Dictionary<void*,int*>;
template os_Dictionary<char*, os_class_type*>;
template os_Dictionary<char*, os_Type_loader*>;
template os_Dictionary<char*, os_Type_fixup_loader*>;
template os_Registration_entry<os_Type_loader*, os_Loader>;
template os_Registration_block<os_Type_loader*, os_Loader>;

template os_Registration_entry<os_Type_fixup_loader*, os_Loader>;
template os_Registration_block<os_Type_fixup_loader*, os_Loader>;

template os_Registration_entry<os_Dumper_specialization*, void*>;
template os_Registration_block<os_Dumper_specialization*, void*>;

#endif /* _OS_Win32 */


/***********************************************************************
  Specializing the instantiation for os_Registration_entry<char*, 
  os_Type_loader*, os_Loader>::set_context (Loader&)
***********************************************************************/

void os_Registration_entry<os_Type_loader*, os_Loader>::set_context
  (os_Loader& loader)
{
  value->set_loader(loader);
}


/***********************************************************************
  Specializing the instantiation for os_Registration_entry<char*, 
  os_Type_fixup_loader*, os_Loader>::set_context (Loader&)
***********************************************************************/

void os_Registration_entry<os_Type_fixup_loader*, os_Loader>::set_context
  (os_Loader& loader)
{
  value->set_loader(loader);
}


/***********************************************************************
  Marking os_Dictionary<void*, int*>
***********************************************************************/

#ifndef _OS_DECCXX  /* Template instantiation for DEC */
#ifndef OS_TRANSIENT_DICTIONARY_KEY_VOID
#define OS_TRANSIENT_DICTIONARY_KEY_VOID
OS_TRANSIENT_DICTIONARY(void*,int*); 
#else
OS_TRANSIENT_DICTIONARY_NOKEY(void*,int*); 
#endif /* OS_TRANSIENT_DICTIONARY_KEY_VOID */
#endif


/***********************************************************************
  Marking os_Dictionary<char*, os_class_type*>
***********************************************************************/
#ifndef _OS_Win32
#define OS_TRANSIENT_DICTIONARY_KEY_CHAR
#endif

#ifndef OS_TRANSIENT_DICTIONARY_KEY_CHAR
#define OS_TRANSIENT_DICTIONARY_KEY_CHAR
OS_TRANSIENT_DICTIONARY(char*,os_class_type*); 
#else
OS_TRANSIENT_DICTIONARY_NOKEY(char*,os_class_type*); 
#endif /* OS_TRANSIENT_DICTIONARY_KEY_CHAR */


/***********************************************************************
  Marking os_Dictionary<char*, os_Type_loader*>
***********************************************************************/

#ifndef _OS_Win32
#define OS_TRANSIENT_DICTIONARY_KEY_CHAR
OS_TRANSIENT_DICTIONARY_NOKEY(char*,os_Type_loader*); 
#endif /* !_OS_Win32 */

#ifdef _OS_Win32
#ifndef OS_TRANSIENT_DICTIONARY_KEY_CHAR
#define OS_TRANSIENT_DICTIONARY_KEY_CHAR
OS_TRANSIENT_DICTIONARY(char*,os_Type_loader*); 
#else
OS_TRANSIENT_DICTIONARY_NOKEY(char*,os_Type_loader*); 
#endif /* OS_TRANSIENT_DICTIONARY_KEY_CHAR */
#endif /* _OS_Win32 */

/***********************************************************************
  Marking os_Dictionary<os_int32, void*>
  Marking os_Dictionary<os_jstring_wrapper, void*>
	for OSJI
***********************************************************************/
/*
#ifndef _OS_Win32
#define OS_TRANSIENT_DICTIONARY_KEY_INT
//OS_TRANSIENT_DICTIONARY_NOKEY(os_int32, void*); 
//OS_TRANSIENT_DICTIONARY_NOKEY(os_jstring_wrapper, void*); 
#endif*/ /* !_OS_Win32 */

//#ifdef _OS_Win32
//#ifndef OS_TRANSIENT_DICTIONARY_KEY_INT
//#define OS_TRANSIENT_DICTIONARY_KEY_INT
//OS_TRANSIENT_DICTIONARY(os_int32,void*); 
//OS_TRANSIENT_DICTIONARY(os_jstring_wrapper,void*); 
//#else
//OS_TRANSIENT_DICTIONARY_NOKEY(os_int32, void*); 
//OS_TRANSIENT_DICTIONARY_NOKEY(os_jstring_wrapper, void*); 
//#endif /* OS_TRANSIENT_DICTIONARY_KEY_INT */
//#endif /* _OS_Win32 */

/***********************************************************************
  Marking os_Dictionary<char*, os_Type_fixup_loader*>
***********************************************************************/

#ifndef OS_TRANSIENT_DICTIONARY_KEY_CHAR
#define OS_TRANSIENT_DICTIONARY_KEY_CHAR
OS_TRANSIENT_DICTIONARY(char*,os_Type_fixup_loader*); 
#else
OS_TRANSIENT_DICTIONARY_NOKEY(char*,os_Type_fixup_loader*); 
#endif /* OS_TRANSIENT_DICTIONARY_KEY_CHAR */

/***********************************************************************
  Marking os_Dictionary<char*, os_Dumper_specialization*>
***********************************************************************/

#ifndef OS_TRANSIENT_DICTIONARY_KEY_CHAR
#define OS_TRANSIENT_DICTIONARY_KEY_CHAR
OS_TRANSIENT_DICTIONARY(char*,os_Dumper_specialization*); 
#else
OS_TRANSIENT_DICTIONARY_NOKEY(char*,os_Dumper_specialization*); 
#endif /* OS_TRANSIENT_DICTIONARY_KEY_CHAR */

#if defined(_OS_HP_aCC)
template _CLASS os_Dictionary<void*,int*>;
template _CLASS os_Dictionary<char*, _CLASS os_Type_loader*>;
template _CLASS os_Dictionary<char*, _CLASS os_Type_fixup_loader*>;
//template _CLASS os_Dictionary<os_int32, void*>;
//template _CLASS os_Dictionary<os_jstring_wrapper, void*>;

template _CLASS os_Registration_entry<_CLASS os_Type_loader*, _CLASS os_Loader>;
template _CLASS os_Registration_block<_CLASS os_Type_loader*, _CLASS os_Loader>;

template _CLASS os_Registration_entry<_CLASS os_Type_fixup_loader*, _CLASS os_Loader>;
template _CLASS os_Registration_block<_CLASS os_Type_fixup_loader*, _CLASS os_Loader>;

template _CLASS os_Registration_entry<_CLASS os_Dumper_specialization*, void*>;
template _CLASS os_Registration_block<_CLASS os_Dumper_specialization*, void*>;
#endif

#if defined(__os_sol2c5)
template class os_Dictionary<void*,int*>;
template class os_Dictionary<char*, class os_Type_loader*>;
template class os_Dictionary<char*, class os_Type_fixup_loader*>;
//template class os_Dictionary<os_int32, void*>;
//template class os_Dictionary<os_jstring_wrapper, void*>;

template class os_Registration_entry<class os_Type_loader*, class os_Loader>;
template class os_Registration_block<class os_Type_loader*, class os_Loader>;

template class os_Registration_entry<class os_Type_fixup_loader*, class os_Loader>;
template class os_Registration_block<class os_Type_fixup_loader*, class os_Loader>;

template class os_Registration_entry<class os_Dumper_specialization*, void*>;
template class os_Registration_block<class os_Dumper_specialization*, void*>;

#endif

#ifdef _OS_DECCXX  /* Template instantiation for DEC */
#pragma define_template os_Dictionary<void*,int*>
#pragma define_template os_Dictionary<char*, os_Type_loader*>
#pragma define_template os_Dictionary<char*, os_class_type*>
#pragma define_template os_Dictionary<char*, os_Type_fixup_loader*>

#pragma define_template os_Registration_entry<os_Type_loader*, os_Loader>
#pragma define_template os_Registration_block<os_Type_loader*, os_Loader>

#pragma define_template os_Registration_entry<os_Type_fixup_loader*, os_Loader>
#pragma define_template os_Registration_block<os_Type_fixup_loader*, os_Loader>

#pragma define_template os_Registration_entry<os_Dumper_specialization*, void*>
#pragma define_template os_Registration_block<os_Dumper_specialization*, void*>

#pragma define_template os_Dictionary<char*, os_Dumper_specialization*>

//#pragma define_template _Rhash_pt<os_int32>
//#pragma define_template _Rhash_pt<os_jstring_wrapper>

//#pragma define_template os_Dictionary<os_int32, void*>
//#pragma define_template os_Dictionary<os_jstring_wrapper, void*>

instantiate_dictionary_void() // exists only in load
   {
   os_Dictionary<void*,int*> foo;
   }

#endif /* _OS_DECCXX */
#ifdef __os_sgi_mips  /* Template instantiation for DEC */
#pragma instantiate os_Dictionary<void*,int*>
#pragma instantiate os_Dictionary<char*, os_Type_loader*>
#pragma instantiate os_Dictionary<char*, os_class_type*>
#pragma instantiate os_Dictionary<char*, os_Type_fixup_loader*>

//#pragma instantiate os_Dictionary<os_int32, void*>
//#pragma instantiate os_Dictionary<os_jstring_wrapper, void*>

#pragma instantiate os_Registration_entry<os_Type_loader*, os_Loader>
#pragma instantiate os_Registration_block<os_Type_loader*, os_Loader>

#pragma instantiate os_Registration_entry<os_Type_fixup_loader*, os_Loader>
#pragma instantiate os_Registration_block<os_Type_fixup_loader*, os_Loader>

#pragma instantiate os_Registration_entry<os_Dumper_specialization*, void*>
#pragma instantiate os_Registration_block<os_Dumper_specialization*, void*>
#pragma instantiate os_Dictionary<char*, os_Dumper_specialization*>

#endif /* __os_sgi_mips */

//-- Instantiations ----------------------------------------------------

void loader_instantiations ()
{
  os_Registration_entry<os_Type_loader*, os_Loader>::_instantiate();
  os_Registration_block<os_Type_loader*, os_Loader>::_instantiate();
  os_Registration_entry<os_Type_fixup_loader*, os_Loader>::_instantiate();
  os_Registration_block<os_Type_fixup_loader*, os_Loader>::_instantiate();
  os_Collection<const char*> coll;
  os_Array<const char*> ary;
  os_Dictionary<char*, os_class_type*> var0;
/*
#if defined(__os_cafe)
  os_Dictionary<os_int32, void*> var1;
  os_Dictionary<os_jstring_wrapper, void*> var2;
#endif
*/
#if !defined(_OS_DECCXX) || !defined(__os_sgi_mips) 
  os_Registration_entry<os_Dumper_specialization*, void*>::_instantiate();
  os_Registration_block<os_Dumper_specialization*, void*>::_instantiate();
#endif
}




