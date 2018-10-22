/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/******************************************************************************
FileName      : afitratr.hh
Purpose       : create typedef for iterator
Contents      : declaration of os_trait_iterator, os_rule_iterator, 
              : os_context_iterator
Environment   : VC++5.0
Last Delta on : 
Revisions     : 
******************************************************************************/
#ifndef __OS_ITERATOR__
#define __OS_ITERATOR__

#include <ostore/allocators/afmapitr.cc>
#include <ostore/allocators/afstkitr.cc>
#include <ostore/allocators/aftrait.hh>

class _ODI_AF_string ;
class os_allocation_context ;
class os_extended_allocator ;
/******************************************************************************
Class Name      : iterators
Description     : this is a typedef for the iterators 
Remarks         : 
******************************************************************************/
typedef _ODI_AF_Map_iterator< os_trait >     os_trait_iterator ;
typedef _ODI_AF_Map_iterator< os_string >    os_rule_iterator ;
typedef _ODI_AF_Map_iterator< os_extended_allocator > os_alloc_iterator ;
typedef _ODI_AF_Stack_iterator< os_allocation_context > os_context_iterator ;

#endif
