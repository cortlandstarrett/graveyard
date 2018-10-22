/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef OSTORE_DUMPLOAD_INSTANTI_HC
#define OSTORE_DUMPLOAD_INSTANTI_HC

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

#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/coll/dict_pt.hh>
#include <ostore/coll/dict_pt.cc>

//#include <ostore/traverse/inplace.hh>
#include <ostore/traverse/traverse.hh>
#include <ostore/traverse/btreept.hh>
#include <ostore/traverse/btreept.hc>
#include <ostore/traverse/chainlst.hh>
#include <ostore/traverse/chainlst.hc>
#include <ostore/traverse/cacheref.hh>
#include <ostore/traverse/cacheref.hc>

#include <ostore/dumpload/fixup.hh>
#include <ostore/dumpload/fixup.hc>
#include <ostore/dumpload/value.hh>
#include <ostore/dumpload/value.hc>
#include <ostore/dumpload/db_table.hh>
#include <ostore/dumpload/db_tab_i.hh>

#if _OS_MicrosoftCC
#pragma warning(disable: 4660 4661)
#endif

//-- Forward Declarations ---------------------------------------------

class os_Offset_displacement_entry;

typedef _B_tree_node_pt<os_unsigned_int32, os_Offset_table_value, 64, 256> 
    os_Offset_table_nodes;
typedef _B_tree_pt<os_unsigned_int32, os_Offset_table_value, 64, 256> 
    os_Offset_table_entries;
typedef _B_tree_safe_cursor_pt<os_unsigned_int32, os_Offset_table_value, 
                               64, 256> os_Offset_table_cursor;

/***********************************************************************
  Method:      os_Chained_list_block<os_Fixup*>::get_typespec
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

os_typespec* os_Chained_list_block<os_Fixup*>::get_typespec () const
{
  return os_typespec::get_pointer();
}

/***********************************************************************
  Marking os_Dictionary<char*, os_Offset_displacement_entry*>
***********************************************************************/

/* OS_TRANSIENT_DICTIONARY_KEY_CHAR is defined elsewhere -- good luck
   finding it.  */
OS_TRANSIENT_DICTIONARY_NOKEY(char*,os_Offset_displacement_entry*); 

/***********************************************************************
  Marking os_Dictionary<os_unsigned_int32, os_unsigned_int32*>
***********************************************************************/

#ifndef OS_TRANSIENT_DICTIONARY_KEY_INT
#define OS_TRANSIENT_DICTIONARY_KEY_INT
OS_TRANSIENT_DICTIONARY(os_unsigned_int32,os_unsigned_int32*); 
#else
OS_TRANSIENT_DICTIONARY_NOKEY(os_unsigned_int32,os_unsigned_int32*); 
#endif /* OS_TRANSIENT_DICTIONARY_KEY_CHAR */

/***********************************************************************
  Marking os_Dictionary<char*, os_unsigned_int32*>
***********************************************************************/

OS_TRANSIENT_DICTIONARY_NOKEY(char*,os_unsigned_int32*); 


#ifdef _OS_Win32
template os_Input_value<os_Input_value_t::Boolean>;
template os_Input_value<char>;
template os_Input_value<short>;
template os_Input_value<unsigned short>;
template os_Input_value<int>;
template os_Input_value<unsigned int>;
template os_Input_value<long>;
template os_Input_value<unsigned long>;
template os_Input_value<float>;
template os_Input_value<double>;
template os_Input_value<char*>;

template _B_tree_node_pt<os_unsigned_int32, os_Offset_table_value, 64, 256>;
template _B_tree_pt<os_unsigned_int32, os_Offset_table_value, 64, 256>;
template _B_tree_safe_cursor_pt<os_unsigned_int32, os_Offset_table_value, 
                                64, 256>;

template os_Fixup_details<os_In_segment_location>;
template os_Fixup_details<os_In_database_location>;
template os_Fixup_details<os_Cross_database_location>;
template os_Fixup_details<os_Database_root_location>;
template os_Fixup_details<os_Database_class_key_location>;

template os_Reference_fixup<os_In_segment_fixup_details>;
template os_Reference_fixup<os_In_database_fixup_details>;
template os_Reference_fixup<os_Cross_database_fixup_details>;
template os_Reference_fixup<os_Database_root_fixup_details>;
template os_Reference_fixup<os_Database_class_key_fixup_details>;

template os_Chained_list_block<os_Offset_table_value>;
template os_Chained_list<os_Offset_table_value>;
template os_Chained_list_cursor<os_Offset_table_value>;

template os_Chained_list_block<os_In_segment_reference_fixup>; 
template os_Chained_list<os_In_segment_reference_fixup>; 
template os_Chained_list_cursor<os_In_segment_reference_fixup>; 

template os_Chained_list_block<os_In_database_reference_fixup>; 
template os_Chained_list<os_In_database_reference_fixup>; 
template os_Chained_list_cursor<os_In_database_reference_fixup>; 

template os_Chained_list_block<os_Cross_database_reference_fixup>; 
template os_Chained_list<os_Cross_database_reference_fixup>; 
template os_Chained_list_cursor<os_Cross_database_reference_fixup>; 

template os_Chained_list_block<os_Database_root_reference_fixup>; 
template os_Chained_list<os_Database_root_reference_fixup>; 
template os_Chained_list_cursor<os_Database_root_reference_fixup>; 

template os_Chained_list_block<os_Database_class_key_reference_fixup>; 
template os_Chained_list<os_Database_class_key_reference_fixup>; 
template os_Chained_list_cursor<os_Database_class_key_reference_fixup>; 

template os_Chained_list_block<os_Fixup*>; 
template os_Chained_list<os_Fixup*>; 
template os_Chained_list_cursor<os_Fixup*>; 

template os_Cached_reference<os_Database_table_persist>;

template os_Array<const char*>;
template os_Bag<const char*>;
template os_List<const char*>;
template os_Set<const char*>;

template os_Dictionary<char*, os_unsigned_int32*>;
template os_Dictionary<os_unsigned_int32, os_unsigned_int32*>;
template os_Dictionary<char*, os_Offset_displacement_entry*>;

#endif /* _OS_Win32 */

#ifdef _OS_DECCXX

#pragma define_template os_Input_value<os_Input_value_t::Boolean>
#pragma define_template os_Input_value<char>
#pragma define_template os_Input_value<short>
#pragma define_template os_Input_value<unsigned short>
#pragma define_template os_Input_value<int>
#pragma define_template os_Input_value<unsigned int>
#pragma define_template os_Input_value<long>
#pragma define_template os_Input_value<unsigned long>
#pragma define_template os_Input_value<float>
#pragma define_template os_Input_value<double>
#pragma define_template os_Input_value<char*>

#pragma define_template _B_tree_node_pt<os_unsigned_int32,  os_Offset_table_value, 64, 256>
#pragma define_template _B_tree_pt<os_unsigned_int32,  os_Offset_table_value, 64, 256>
#pragma define_template _B_tree_safe_cursor_pt<os_unsigned_int32, os_Offset_table_value, 64, 256>
 
#pragma define_template os_Fixup_details<os_In_segment_location>
#pragma define_template os_Fixup_details<os_In_database_location>
#pragma define_template os_Fixup_details<os_Cross_database_location>
#pragma define_template os_Fixup_details<os_Database_root_location>
#pragma define_template os_Fixup_details<os_Database_class_key_location>

#pragma define_template os_Reference_fixup<os_Cross_database_fixup_details>
#pragma define_template os_Reference_fixup<os_In_segment_fixup_details>
#pragma define_template os_Reference_fixup<os_In_database_fixup_details>
#pragma define_template os_Reference_fixup<os_Database_root_fixup_details>
#pragma define_template os_Reference_fixup<os_Database_class_key_fixup_details>

#pragma define_template os_Chained_list_block<os_Offset_table_value>
#pragma define_template os_Chained_list<os_Offset_table_value>
#pragma define_template os_Chained_list_cursor<os_Offset_table_value>

#pragma define_template os_Chained_list_block<os_Database_root_reference_fixup>
#pragma define_template os_Chained_list<os_Database_root_reference_fixup>
#pragma define_template os_Chained_list_cursor<os_Database_root_reference_fixup>

#pragma define_template os_Chained_list_block<os_Database_class_key_reference_fixup>
#pragma define_template os_Chained_list<os_Database_class_key_reference_fixup>
#pragma define_template os_Chained_list_cursor<os_Database_class_key_reference_fixup>

#pragma define_template os_Chained_list_block<os_In_segment_reference_fixup>
#pragma define_template os_Chained_list<os_In_segment_reference_fixup>
#pragma define_template os_Chained_list_cursor<os_In_segment_reference_fixup>

#pragma define_template os_Chained_list_block<os_In_database_reference_fixup> 
#pragma define_template os_Chained_list<os_In_database_reference_fixup>
#pragma define_template os_Chained_list_cursor<os_In_database_reference_fixup>

#pragma define_template os_Chained_list_block<os_Cross_database_reference_fixup>
#pragma define_template os_Chained_list<os_Cross_database_reference_fixup>
#pragma define_template os_Chained_list_cursor<os_Cross_database_reference_fixup>

#pragma define_template os_Chained_list<os_Fixup*>
#pragma define_template os_Chained_list_cursor<os_Fixup*>
#pragma define_template os_Chained_list_block<os_Fixup*>

#pragma define_template _Rhash_pt<void*>
#pragma define_template _Rhash_pt<char*>
#pragma define_template _Rhash_pt<os_unsigned_int32>

#pragma define_template os_Dictionary<char*, os_unsigned_int32*>
#pragma define_template os_Dictionary<os_unsigned_int32, os_unsigned_int32*>
#pragma define_template os_Dictionary<char*, os_Offset_displacement_entry*>

#pragma define_template os_Cached_reference<os_Database_table_persist>

#endif

#ifdef __os_sgi_mips

#pragma instantiate os_Input_value<os_Input_value_t::Boolean>
#pragma instantiate os_Input_value<char>
#pragma instantiate os_Input_value<short>
#pragma instantiate os_Input_value<unsigned short>
#pragma instantiate os_Input_value<int>
#pragma instantiate os_Input_value<unsigned int>
#pragma instantiate os_Input_value<long>
#pragma instantiate os_Input_value<unsigned long>
#pragma instantiate os_Input_value<float>
#pragma instantiate os_Input_value<double>
#pragma instantiate os_Input_value<char*>

#pragma instantiate  _B_tree_node_pt<os_unsigned_int32,  os_Offset_table_value, 64, 256>
#pragma instantiate _B_tree_pt<os_unsigned_int32,  os_Offset_table_value, 64, 256>
#pragma instantiate _B_tree_safe_cursor_pt<os_unsigned_int32, os_Offset_table_value, 64, 256>
 
#pragma instantiate os_Fixup_details<os_In_segment_location>
#pragma instantiate os_Fixup_details<os_In_database_location>
#pragma instantiate os_Fixup_details<os_Cross_database_location>
#pragma instantiate os_Fixup_details<os_Database_root_location>
#pragma instantiate os_Fixup_details<os_Database_class_key_location>

#pragma instantiate os_Reference_fixup<os_Cross_database_fixup_details>
#pragma instantiate os_Reference_fixup<os_In_segment_fixup_details>
#pragma instantiate os_Reference_fixup<os_In_database_fixup_details>
#pragma instantiate os_Reference_fixup<os_Database_root_fixup_details>
#pragma instantiate os_Reference_fixup<os_Database_class_key_fixup_details>

#pragma instantiate os_Chained_list_block<os_Offset_table_value>
#pragma instantiate os_Chained_list<os_Offset_table_value>
#pragma instantiate os_Chained_list_cursor<os_Offset_table_value>

#pragma instantiate os_Chained_list_block<os_Database_root_reference_fixup>
#pragma instantiate os_Chained_list<os_Database_root_reference_fixup>
#pragma instantiate os_Chained_list_cursor<os_Database_root_reference_fixup>

#pragma instantiate os_Chained_list_block<os_Database_class_key_reference_fixup>
#pragma instantiate os_Chained_list<os_Database_class_key_reference_fixup>
#pragma instantiate os_Chained_list_cursor<os_Database_class_key_reference_fixup>

#pragma instantiate os_Chained_list_block<os_In_segment_reference_fixup>
#pragma instantiate os_Chained_list<os_In_segment_reference_fixup>
#pragma instantiate os_Chained_list_cursor<os_In_segment_reference_fixup>

#pragma instantiate os_Chained_list_block<os_In_database_reference_fixup> 
#pragma instantiate os_Chained_list<os_In_database_reference_fixup>
#pragma instantiate os_Chained_list_cursor<os_In_database_reference_fixup>

#pragma instantiate os_Chained_list_block<os_Cross_database_reference_fixup>
#pragma instantiate os_Chained_list<os_Cross_database_reference_fixup>
#pragma instantiate os_Chained_list_cursor<os_Cross_database_reference_fixup>

#pragma instantiate os_Chained_list<os_Fixup*>
#pragma instantiate os_Chained_list_cursor<os_Fixup*>

#pragma instantiate os_Chained_list_block<os_Fixup*>

#pragma instantiate os_Cached_reference<os_Database_table_persist>

#pragma instantiate os_Dictionary<char*, os_unsigned_int32*>
#pragma instantiate os_Dictionary<os_unsigned_int32, os_unsigned_int32*>
#pragma instantiate os_Dictionary<char*, os_Offset_displacement_entry*>

#endif

#ifdef __os_linux

template os_Input_value<os_Input_value_t::Boolean>;
template os_Input_value<char>;
template os_Input_value<short>;
template os_Input_value<unsigned short>;
template os_Input_value<int>;
template os_Input_value<unsigned int>;
template os_Input_value<long>;
template os_Input_value<unsigned long>;
template os_Input_value<float>;
template os_Input_value<double>;
template os_Input_value<char*>;

template _B_tree_node_pt<os_unsigned_int32,  os_Offset_table_value, 64, 256>;
template _B_tree_pt<os_unsigned_int32,  os_Offset_table_value, 64, 256>;
template _B_tree_safe_cursor_pt<os_unsigned_int32, os_Offset_table_value, 64, 256>;
 
template os_Fixup_details<os_In_segment_location>;
template os_Fixup_details<os_In_database_location>;
template os_Fixup_details<os_Cross_database_location>;
template os_Fixup_details<os_Database_root_location>;
template os_Fixup_details<os_Database_class_key_location>;

template os_Reference_fixup<os_Cross_database_fixup_details>;
template os_Reference_fixup<os_In_segment_fixup_details>;
template os_Reference_fixup<os_In_database_fixup_details>;
template os_Reference_fixup<os_Database_root_fixup_details>;
template os_Reference_fixup<os_Database_class_key_fixup_details>;

template os_Chained_list_block<os_Offset_table_value>;
template os_Chained_list<os_Offset_table_value>;
template os_Chained_list_cursor<os_Offset_table_value>;

template os_Chained_list_block<os_Database_root_reference_fixup>;
template os_Chained_list<os_Database_root_reference_fixup>;
template os_Chained_list_cursor<os_Database_root_reference_fixup>;

template os_Chained_list_block<os_Database_class_key_reference_fixup>;
template os_Chained_list<os_Database_class_key_reference_fixup>;
template os_Chained_list_cursor<os_Database_class_key_reference_fixup>;

template os_Chained_list_block<os_In_segment_reference_fixup>;
template os_Chained_list<os_In_segment_reference_fixup>;
template os_Chained_list_cursor<os_In_segment_reference_fixup>;

template os_Chained_list_block<os_In_database_reference_fixup> ;
template os_Chained_list<os_In_database_reference_fixup>;
template os_Chained_list_cursor<os_In_database_reference_fixup>;

template os_Chained_list_block<os_Cross_database_reference_fixup>;
template os_Chained_list<os_Cross_database_reference_fixup>;
template os_Chained_list_cursor<os_Cross_database_reference_fixup>;

template os_Chained_list<os_Fixup*>;
template os_Chained_list_cursor<os_Fixup*>;
template os_Chained_list_block<os_Fixup*>;

template os_Cached_reference<os_Database_table_persist>;

#endif

#if defined (__os_hp11) || defined (__os_sol2c5)

template class os_Input_value<os_Input_value_t::Boolean>;
template class os_Input_value<char>;
template class os_Input_value<short>;
template class os_Input_value<unsigned short>;
template class os_Input_value<int>;
template class os_Input_value<unsigned int>;
template class os_Input_value<long>;
template class os_Input_value<unsigned long>;
template class os_Input_value<float>;
template class os_Input_value<double>;
template class os_Input_value<char*>;

template class _B_tree_node_pt<os_unsigned_int32, os_Offset_table_value, 64, 256>;
template class _B_tree_pt<os_unsigned_int32, os_Offset_table_value, 64, 256>;
template class _B_tree_safe_cursor_pt<os_unsigned_int32, os_Offset_table_value,                                64, 256>;

template class os_Fixup_details<os_In_segment_location>;
template class os_Fixup_details<os_In_database_location>;
template class os_Fixup_details<os_Cross_database_location>;
template class os_Fixup_details<os_Database_root_location>;
template class os_Fixup_details<os_Database_class_key_location>;

template class os_Reference_fixup<os_In_segment_fixup_details>;
template class os_Reference_fixup<os_In_database_fixup_details>;
template class os_Reference_fixup<os_Cross_database_fixup_details>;
template class os_Reference_fixup<os_Database_root_fixup_details>;
template class os_Reference_fixup<os_Database_class_key_fixup_details>;

template class os_Chained_list_block<class os_Offset_table_value>;
template class os_Chained_list<class os_Offset_table_value>;
template class os_Chained_list_cursor<class os_Offset_table_value>;

template class os_Chained_list_block<os_In_segment_reference_fixup>; 
template class os_Chained_list<os_In_segment_reference_fixup>; 
template class os_Chained_list_cursor<os_In_segment_reference_fixup>; 

template class os_Chained_list_block<os_In_database_reference_fixup>; 
template class os_Chained_list<os_In_database_reference_fixup>; 
template class os_Chained_list_cursor<os_In_database_reference_fixup>; 

template class os_Chained_list_block<os_Cross_database_reference_fixup>; 
template class os_Chained_list<os_Cross_database_reference_fixup>; 
template class os_Chained_list_cursor<os_Cross_database_reference_fixup>; 

template class os_Chained_list_block<os_Database_root_reference_fixup>; 
template class os_Chained_list<os_Database_root_reference_fixup>; 
template class os_Chained_list_cursor<os_Database_root_reference_fixup>; 

template class os_Chained_list_block<os_Database_class_key_reference_fixup>; 
template class os_Chained_list<os_Database_class_key_reference_fixup>; 
template class os_Chained_list_cursor<os_Database_class_key_reference_fixup>; 

template class os_Chained_list_block<class os_Fixup*>; 
template class os_Chained_list<class os_Fixup*>; 
template class os_Chained_list_cursor<class os_Fixup*>; 

template class os_Cached_reference<class os_Database_table_persist>;

template class os_Array<const char*>;
template class os_Bag<const char*>;
template class os_List<const char*>;
template class os_Set<const char*>;

template class os_Dictionary<char*, os_unsigned_int32*>;
template class os_Dictionary<os_unsigned_int32, os_unsigned_int32*>;
template class os_Dictionary<char*, os_Offset_displacement_entry*>;

#endif /* __os_hp11  || __os_sol2c5*/


//-- Instantiations ----------------------------------------------------

void dump_load_instantiations ()
{
#ifdef _OS_Win
  os_Array<const char*> strings_array;
  os_Bag<const char*> strings_bag;
  os_List<const char*> strings_list;
  os_Set<const char*> strings_set;
#endif /* _OS_Win */
  os_Input_value<os_Input_value_t::Boolean> value_boolean;
  os_Input_value<char> value_char;
  os_Input_value<short> value_short;
  os_Input_value<unsigned short> value_unsigned_short;
  os_Input_value<int> value_int;
  os_Input_value<unsigned int> value_unsigned_int;
  os_Input_value<long> value_long;
  os_Input_value<unsigned long> value_unsigned_long;
  os_Input_value<float> value_float;
  os_Input_value<double> value_double;
  os_Input_value<char*> value_string;

  os_Offset_table_entries offset_table_entries;
  os_Offset_table_cursor offset_table_cursor;

  os_Offset_table_value_block::_instantiate();
  os_Offset_table_values::_instantiate();
  os_Offset_table_value_cursor::_instantiate();

  os_In_segment_fixup_details in_segment_fixup_details();
  os_In_segment_reference_fixup in_segment_reference_fixup();

  os_In_segment_reference_fixup_block::_instantiate();
  os_In_segment_reference_fixups::_instantiate();
  os_In_segment_reference_fixup_cursor::_instantiate();

  os_In_database_fixup_details in_database_fixup_details();
  os_In_database_reference_fixup in_database_reference_fixup();

  os_In_database_reference_fixup_block::_instantiate();
  os_In_database_reference_fixups::_instantiate();
  os_In_database_reference_fixup_cursor::_instantiate();

  os_Cross_database_fixup_details cross_database_fixup_details();
  os_Cross_database_reference_fixup cross_database_reference_fixup();

  os_Cross_database_reference_fixup_block::_instantiate();
  os_Cross_database_reference_fixups::_instantiate();
  os_Cross_database_reference_fixup_cursor::_instantiate();

  os_Database_root_fixup_details database_root_fixup_details();
  os_Database_root_reference_fixup database_root_reference_fixup();

  os_Database_root_reference_fixup_block::_instantiate();
  os_Database_root_reference_fixups::_instantiate();
  os_Database_root_reference_fixup_cursor::_instantiate();

  os_Database_class_key_fixup_details database_class_key_fixup_details();
  os_Database_class_key_reference_fixup database_class_key_reference_fixup();

  os_Database_class_key_reference_fixup_block::_instantiate();
  os_Database_class_key_reference_fixups::_instantiate();
  os_Database_class_key_reference_fixup_cursor::_instantiate();

  os_Fixup_block::_instantiate();
  os_Fixups::_instantiate();
  os_Fixup_cursor::_instantiate();

  os_Cached_reference<os_Database_table_persist>::_instantiate();

  os_Dictionary<char*, os_unsigned_int32*> foo1;
  os_Dictionary<os_unsigned_int32, os_unsigned_int32*> foo2;
  os_Dictionary<char*, os_Offset_displacement_entry*> classes;

}

#endif /* OSTORE_DUMPLOAD_INSTANTI_HC */
