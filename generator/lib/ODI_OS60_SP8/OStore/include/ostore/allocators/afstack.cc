/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_AFSTACK_CC
#define _OS_AFSTACK_CC 1

#include <iostream.h>
#include <ostore/allocators/afstack.hh>

/******************************************************************************
Member Function: _ODI_AF_Stack()
Class Name     : _ODI_AF_Stack<T> 
Purpose        : Initializes the pointer to os_List object and sets the
               : behaviour
Parameters     : None
Return Value   : None
Remarks        :
******************************************************************************/

template< class T> 
_ODI_AF_Stack<T>::_ODI_AF_Stack()
{
    os_cluster_with tmp_os_cluster_with = os_cluster::with(this);
    m_p_impl = &os_List<T*>::create((os_cluster_with&) tmp_os_cluster_with);
}


/******************************************************************************
Member Function: ~_ODI_AF_Stack()
Class Name     : _ODI_AF_Stack<T> 
Purpose        : deletes the contents of _ODI_AF_Stack datastructure and deallocates 
               : storage
Parameters     : None
Return Value   : None
Remarks        :
******************************************************************************/

template< class T> 
_ODI_AF_Stack<T>::~_ODI_AF_Stack()
{
    m_p_impl->clear() ; 
    /* destroys the stack and deallocates storage */ 
    os_List<T*>::destroy( *m_p_impl ) ;
}


/******************************************************************************
Member Function: void push( T* value )
Class Name     : _ODI_AF_Stack<T> 
Purpose        : pushes the value to the top of the stack. Null values are 
               : ignored
Parameters     : value to be pushed onto the stack
Return Value   : void
Remarks        :
******************************************************************************/

template< class T> 
void _ODI_AF_Stack<T>::push( T* value )
{
    if( value != (T*)0 )
       m_p_impl->insert( value ) ;
    return ;
}

/******************************************************************************
Member Function: T* pop()
Class Name     : _ODI_AF_Stack<T> 
Purpose        : pops the value from the top of the stack. checks for null 
               : stack
Parameters     : None
Return Value   : returns the value popped from the stack
Remarks        :
******************************************************************************/

template< class T> 
T* _ODI_AF_Stack<T>::pop()
{
    T* value = m_p_impl->remove_last() ;
    return value ;
    
}

/******************************************************************************
Member Function: void remove_all()
Class Name     : _ODI_AF_Stack<T> 
Purpose        : It removes all the values from the stack.
Parameters     : None
Return Value   : void
Remarks        :
******************************************************************************/

template< class T> 
void _ODI_AF_Stack<T>::remove_all()
{
    if( !is_empty() ) 
       m_p_impl->clear() ;
	return ;
}

/******************************************************************************
Member Function: os_boolean is_empty()
Class Name     : _ODI_AF_Stack<T> 
Purpose        : This function checks if the stack is empty
Parameters     : None
Return Value   : true if the stack is empty and false if the stack is not empty
Remarks        :
******************************************************************************/

template< class T> 
os_boolean _ODI_AF_Stack<T>::is_empty() const
{
    os_int32 result = m_p_impl->empty() ;
    return ( result != 0 );
}

#endif
