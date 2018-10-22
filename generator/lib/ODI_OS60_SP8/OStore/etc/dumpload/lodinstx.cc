
/***********************************************************************
*                                                                      *
*  Copyright (c) 1997-2000 by eXcelon Corporation. All Rights Reserved.    *
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

#include <ostore/portypes.hh>
#include <traverse/register.hh>
#include <traverse/register.hc>
#include <ostore/dumpload/dumper.hh>

/* The following only wants to be included on systems
   with a completely global link time namespace. --rick@odi.com */
/* TBD: figure out the right macro name to ensure the above
        constraint. --rick@odi.com */
#ifndef _OS_Win32
#include <ostore/traverse/instanti.hc>
#include "l_instanti.hc"
#include <ostore/dumpload/loadinst.hc>
#include "jstring_wrapper.hh"
#endif
#include <ostore/dumpload/intrplod.hh>

os_boolean _ODI_hash_compare_function(const char* x, const char* y)
{
	if (!x && !y) return 1;
	if (!strcmp(x,y)) return 1;
	return 0;
}

os_unsigned_int32 _ODI_hash_hash_function(const char* cpc) {
  register char *p= (char *)cpc ;
  register char c1=0, c2=0, c3=0, c4=0 ;
  while (*p) {
    c1 += *p++ ; 
    if (*p) c2 += *p++ ; else break ;
    if (*p) c3 += *p++ ; else break ;
    if (*p) c4 += *p++ ; else break ;
  }
  return ((c1) << 24) | ((c2) << 16) | ((c3) << 8) | (c4);
}


//-- Instantiations ----------------------------------------------------

void dummy_instantiations ()
{
#if !defined(_OS_DECCXX) && !defined(_OS_Win32) && !defined(__os_xlc)
  os_List<os_Embedded_fixup*> l;
  os_List<os_Embedded_loader*> l1;
  os_List<os_Embedded_constructor*> l2;
#endif
#if defined(__os_cafe) || defined(__os_aix43)
  os_Dictionary<os_int32, void*> var1;
  os_Dictionary<os_jstring_wrapper, void*> var2;
#endif
}


/***********************************************************************
  Marking os_Dictionary<>
***********************************************************************/

#if defined(_OS_HP_aCC)
template _CLASS os_Dictionary<os_int32, void*>;
template _CLASS os_Dictionary<os_jstring_wrapper, void*>;
#endif

#ifdef _OS_DECCXX  /* Template instantiation for DEC */
#pragma define_template _Rhash_pt<os_int32>
#pragma define_template _Rhash_pt<os_jstring_wrapper>
#pragma define_template os_Dictionary<os_int32, void*>
#pragma define_template os_Dictionary<os_jstring_wrapper, void*>
#endif
#ifdef __os_sgi_mips  /* Template instantiation for sgi */
#pragma instantiate os_Dictionary<os_int32, void*>
#pragma instantiate os_Dictionary<os_jstring_wrapper, void*>
#endif

#if defined(__os_linux)

template _Rhash_pt<os_int32>;
template _Rhash_pt<os_jstring_wrapper>;
template os_Dictionary<os_int32, void*>;
template os_Dictionary<os_jstring_wrapper, void*>;

#endif


os_typespec* 
_Hash_table_entry<const char*, os_Type_fixup_loader*>::get_os_typespec()
{
  static os_typespec* t = 
    new os_typespec("_hash_table_entry<const char*,os_Type_fixup_loader*>");
  return t;
}

os_typespec* 
_Hash_table_entry<const char*, os_Dumper_specialization*>::get_os_typespec()
{
  static os_typespec* t = 
    new os_typespec("_hash_table_entry<const char*,os_Dumper_specialization*>");
  return t;
}

os_typespec* 
_Hash_table_entry<const char*, os_Type_loader*>::get_os_typespec()
{
  static os_typespec* t = 
   new os_typespec("_hash_table_entry<const char*,os_Type_loader*>");
  return t;
}


os_typespec* 
_Hash_table_entry<const char*, os_Fixup_registration_entry*>::get_os_typespec()
{
  static os_typespec* t = 
    new os_typespec("_hash_table_entry<const char*,os_Fixup_Registration_entry*>");
  return t;
}
 

os_typespec* 
_Hash_table_entry<const char*, os_Loader_registration_entry*>::get_os_typespec()
{
  static os_typespec* t = 
    new os_typespec("_hash_table_entry<const char*,os_Loader_Registration_entry*>");
  return t;
}

os_typespec* 
_Hash_table_entry<const char*, os_Dumper_registration_entry*>::get_os_typespec()
{
  static os_typespec* t = 
    new os_typespec("_hash_table_entry<const char*,os_Dumper_Registration_entry*>");
  return t;
}

typedef os_Registration_entry<os_Dumper_specialization*, void*>
os_Dummy_registry; 

os_typespec* _Hash_table_entry<const char*,os_Dummy_registry*>::get_os_typespec()
{
  static os_typespec* t = 
   new os_typespec("_hash_table_entry<const char*,os_Dummy_registry*>");
  return t;
}


#if defined(_OS_DECCXX)
/* Putting these here since they mess up load if I put them in instanti.hc  */ 

os_typespec* _Dict_pt_slot<void*>::get_os_typespec()
{
  return os_typespec::get_pointer();
}

os_typespec* _Rhash_pt<void*>::get_os_typespec()
{
  return os_typespec::get_pointer();
}

#endif

#if defined(__os_sol2c5)
template class os_Registrations<class os_Type_loader*, class os_Loader>;
template class os_Registrations<class os_Type_fixup_loader*, class os_Loader>;
template class os_Registrations<class  os_Dumper_specialization*, void*>;
#endif

#ifdef _OS_DECCXX  /* Template instantiation for DEC */
#pragma define_template os_Registrations<os_Type_loader*, os_Loader>
#pragma define_template os_Registrations<os_Type_fixup_loader*, os_Loader>
#pragma define_template os_Registrations<os_Dumper_specialization*, void*>
//TMP
#pragma define_template _OST_hash<const char*, os_type*>
#pragma define_template _OST_hash<const char*, os_Type_loader*>
#pragma define_template _OST_hash<const char*, os_Dumper_specialization*>
#pragma define_template _OST_hash<const char*, os_Type_fixup_loader*>
#pragma define_template _OST_hash<const char*, os_Registration_entry<os_Type_loader*, os_Loader>*>
#pragma define_template _OST_hash<const char*, os_Registration_entry<os_Type_fixup_loader*, os_Loader>*>

#pragma define_template _OST_hash_walker<const char*, os_Type_fixup_loader*>
#pragma define_template _OST_hash_walker<const char*, os_Dumper_specialization*>
#pragma define_template _OST_hash_walker<const char*, os_Type_loader*>
#pragma define_template _OST_hash_walker<const char*, os_type*>
#pragma define_template _OST_hash_walker<const char*, os_Registration_entry<os_Dumper_specialization*, void*>*>
#pragma_define_template _OST_hash_walker<const char*, os_Registration_entry<os_Type_loader*, os_Loader>*>
#pragma define_template _OST_hash_walker<const char*, os_Registration_entry<os_Type_fixup_loader*, os_Loader>*>
#pragma define_template _OST_hash<const char*, os_Registration_entry<os_Dumper_specialization*, void*>*>
#pragma define_template _OST_hash_walker<const char*, os_Registration_entry<os_Type_loader*, os_Loader>*>




#endif 

#ifdef __os_sgi_mips  /* Template instantiation for DEC */
#pragma instantiate os_Registrations<os_Type_loader*, os_Loader>
#pragma instantiate os_Registrations<os_Type_fixup_loader*, os_Loader>
#pragma instantiate os_Registrations<os_Dumper_specialization*, void*>
#endif

#if defined(_OS_Win32) || defined(__os_linux)
template os_Registrations<os_Type_loader*, os_Loader>;
template os_Registrations<os_Type_fixup_loader*, os_Loader>;
template os_Registrations<os_Dumper_specialization*, void*>;
#endif

#if defined(_OS_HP_aCC)
template _CLASS os_Registrations<_CLASS os_Type_loader*, _CLASS os_Loader>;
template _CLASS os_Registrations<_CLASS os_Type_fixup_loader*, _CLASS os_Loader>;
template _CLASS os_Registrations<_CLASS  os_Dumper_specialization*, void*>;
#endif
