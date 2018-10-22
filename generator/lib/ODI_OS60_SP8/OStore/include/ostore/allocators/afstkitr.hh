/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/******************************************************************************
FileName      : afstkitr.hh
Purpose       : create a stack iterator class
Contents      : declaration of _ODI_AF_Stack_iterator class
Environment   : VC++5.0
Last Delta on : 
Revisions     : 
******************************************************************************/

#ifndef ___ODI_AF_STACK_ITERATOR__
#define ___ODI_AF_STACK_ITERATOR__

#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/allocators/afstack.hh>

/******************************************************************************
Class Name      : _ODI_AF_Stack_iterator  
Description     : this is a templated class and is a wrapper over the 
  			    : os_Cursor. 
Remarks         : Elements returned by the iterator, must not be deleted.
                : this is wrapper over os_Cursor, collection manipulation is
                : not allowed. This is only forward iterator, that iterates 
                : from top of stack to bottom of stack
******************************************************************************/

template< class T >
class _ODI_AF_Stack_iterator
{
    public :
	ODI_INST();

        /* safe cursor is created */
        _ODI_AF_Stack_iterator( const _ODI_AF_Stack<T>& coll ) ;
        /* destroy the cursor */
        ~_ODI_AF_Stack_iterator() ;

        /* set the cursor to Top element, and return the Top element if Stack 
           is empty, return 0. Top element mean last element in list */
        T* top() ;

        /* set the cursor to next element in the stack, and return the next 
           element. if m_p_impl->null() return 0. next element mean previous
           element in the list */
        T* next() ;

        /* return the current element, if m_p_impl->null() return 0 */
        T* retrieve() ;
    
    private :
        /* Copy constructor is not implemented */
        _ODI_AF_Stack_iterator( const _ODI_AF_Stack_iterator<T>& ) ;
        /* Assignment operator is not implemented */
        _ODI_AF_Stack_iterator<T>& operator=( const _ODI_AF_Stack_iterator<T>& ) ;

        os_Cursor< T* >* m_p_impl ;

} ;

#endif


