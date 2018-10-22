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

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream.h>

#include "chainlst.hh"


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Class:       os_Chained_list
  Description: 
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/


/***********************************************************************
  Variable:      os_Chained_list::default_block_size
  Description: 
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
os_unsigned_int32 os_Chained_list<Element_type>::default_block_size = 4096;


/***********************************************************************
  Method:      os_Chained_list::os_Chained_list
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
os_Chained_list<Element_type>::os_Chained_list 
    (os_unsigned_int32 given_block_size)
{
  first_block = 0;
  last_block = 0;
  block_size = given_block_size;
}


/***********************************************************************
  Method:      os_Chained_list::~os_Chained_list
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
os_Chained_list<Element_type>::~os_Chained_list ()
{
  os_Chained_list_block<Element_type>* block = first_block;
  while (block) {
      os_Chained_list_block<Element_type>* target_block = block;
      block = block->next;
      delete target_block;
    }
  first_block = 0;
  last_block = 0;
  block_size = 0;
}


/***********************************************************************
  Method:      os_Chained_list::get_default_block_size
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
os_unsigned_int32 os_Chained_list<Element_type>::get_default_block_size ()
{
  return default_block_size;
}


/***********************************************************************
  Method:      os_Chained_list::set_default_block_size
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
void os_Chained_list<Element_type>::set_default_block_size
    (os_unsigned_int32 given_block_size)
{
  default_block_size = given_block_size;
}


/***********************************************************************
  Method:      os_Chained_list::is_empty
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
os_boolean os_Chained_list<Element_type>::is_empty () const
{
  os_Chained_list_block<Element_type>* block;
  for (block = first_block; block; block = block->next) {
      if (block->used)
	  return 0;
    }
  return 1;
}


/***********************************************************************
  Method:      os_Chained_list::get_unused_slot
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
Element_type* os_Chained_list<Element_type>::get_unused_slot ()
{
  if ( ! last_block) {
      first_block = new(os_segment::of(this), 
			os_Chained_list_block<Element_type>::get_os_typespec())
	  os_Chained_list_block<Element_type>(block_size);
      last_block = first_block;
    }
  Element_type* slot = last_block->get_unused_slot(block_size);
  if ( ! slot) {
      os_Chained_list_block<Element_type>* new_block 
	  = new(os_segment::of(this), 
		os_Chained_list_block<Element_type>::get_os_typespec())
	    os_Chained_list_block<Element_type>(block_size);
      last_block->next = new_block;
      last_block = new_block;
      slot = last_block->get_unused_slot(block_size);
    }
  return slot;
}


/***********************************************************************
  Method:      os_Chained_list::append
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
Element_type& os_Chained_list<Element_type>::append (const Element_type& value)
{
  Element_type* slot = get_unused_slot();
  *slot = value;
  return *slot;
}


/***********************************************************************
  Method:      os_Chained_list::empty
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
void os_Chained_list<Element_type>::empty ()
{
  os_Chained_list_block<Element_type>* block;
  for (block = first_block; block; block = block->next)
      block->empty();
}


/***********************************************************************
  Method:      os_Chained_list::clear
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
void os_Chained_list<Element_type>::clear ()
{
  os_Chained_list_block<Element_type>* block;
  for (block = first_block; block; block = block->next)
      block->clear(block_size);
}


/***********************************************************************
  Method:      os_Chained_list::_instantiate
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
int os_Chained_list<Element_type>::_instantiate ()
{
  return 0;
}


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Class:       os_Chained_list_block
  Description: 
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/


/***********************************************************************
  Method:      os_Chained_list_block::os_Chained_list_block
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
os_Chained_list_block<Element_type>::os_Chained_list_block 
    (os_unsigned_int32 block_size)
{
  next = 0;
  used = 0;
  values = new (os_segment::of(this), get_typespec(), block_size)
      Element_type[block_size];
}


/***********************************************************************
  Method:      os_Chained_list_block::~os_Chained_list_block
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
os_Chained_list_block<Element_type>::~os_Chained_list_block ()
{
  next = 0;
  used = 0;
  delete [] values;
  values = 0;
}


/***********************************************************************
  Method:      os_Chained_list_block::get_unused_slot
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
Element_type* os_Chained_list_block<Element_type>::get_unused_slot
    (os_unsigned_int32 block_size)
{
  if (used >= block_size)
      return 0;
  else {
      ++used;
      return &values[used - 1];
    }
}


/***********************************************************************
  Method:      os_Chained_list_block::empty
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
void os_Chained_list_block<Element_type>::empty ()
{
  used = 0;
}


/***********************************************************************
  Method:      os_Chained_list_block::clear
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
void os_Chained_list_block<Element_type>::clear (os_unsigned_int32 block_size)
{
  os_unsigned_int32 size = sizeof(Element_type) * block_size;
  memset(values, 0, size);
  used = 0;
}


/***********************************************************************
  Method:      os_Chained_list_block::get_typespec
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
os_typespec* os_Chained_list_block<Element_type>::get_typespec () const
{
  return Element_type::get_os_typespec();
}


/***********************************************************************
  Method:      os_Chained_list_block::_instantiate
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
int os_Chained_list_block<Element_type>::_instantiate ()
{
  return 0;
}


/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  Class:       os_Chained_list_cursor
  Description: 
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/


/***********************************************************************
  Method:      os_Chained_list_cursor::os_Chained_list_cursor
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
os_Chained_list_cursor<Element_type>::os_Chained_list_cursor 
    (const os_Chained_list<Element_type>& given_list)
{
  list = (os_Chained_list<Element_type>*)&given_list;
  block = list->first_block;
  block_index = 0;
}


/***********************************************************************
  Method:      os_Chained_list_cursor::~os_Chained_list_cursor
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
os_Chained_list_cursor<Element_type>::~os_Chained_list_cursor ()
{
  list = 0;
  block = 0;
  block_index = 0;
}


/***********************************************************************
  Method:      os_Chained_list_cursor::first
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
Element_type* os_Chained_list_cursor<Element_type>::first ()
{
  block_index = 0;
  for (block = list->first_block; block; block = block->next) {
      if (block_index < block->used)
	  return &(block->values)[block_index];
    }
  return 0;
}


/***********************************************************************
  Method:      os_Chained_list_cursor::next
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
Element_type* os_Chained_list_cursor<Element_type>::next ()
{
  ++block_index;
  for ( ; block; block = block->next) {
      if (block_index < block->used)
	  return &(block->values)[block_index];
      else
	  block_index = 0;
    }
  return 0;
}


/***********************************************************************
  Method:      os_Chained_list_cursor::current
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
Element_type* os_Chained_list_cursor<Element_type>::current ()
{
  for ( ; block; block = block->next) {
      if (block_index < block->used)
	  return &(block->values)[block_index];
    }
  return 0;
}


/***********************************************************************
  Method:      os_Chained_list_cursor::_instantiate
  Description: 
  Parameters:	
  Signals:	
  Assumptions:
  Restrictions:
***********************************************************************/

template <class Element_type>
int os_Chained_list_cursor<Element_type>::_instantiate ()
{
  return 0;
}


