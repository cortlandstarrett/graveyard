/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/******************************************************************************
Project       : ODI001
FileName      : afstkitr.cc
Purpose       : This is a wrapper over os_Cursor<T>. This is a friend of 
              : _ODI_AF_Stack<T> so that it can access the implementation of 
              : _ODI_AF_Stack<T> 
Author        : Anjana S
Contents      : 
External 
Functions     : 
Environment   : VC++5.0
Last Delta on : 
Revisions     : 
******************************************************************************/

#include <ostore/allocators/afstkitr.hh>

/******************************************************************************
Member Function: _ODI_AF_Stack_iterator( const _ODI_AF_Stack<T>& coll )
Class Name     : _ODI_AF_Stack_iterator<T> 
Purpose        : It intializes the embedded cursor. The cursor is constructed 
               : for the implementation of _ODI_AF_Stack<T>
Parameters     : a const reference to _ODI_AF_Stack<T>
Return Value   : None
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T> 
_ODI_AF_Stack_iterator<T>::_ODI_AF_Stack_iterator( const _ODI_AF_Stack<T>& coll)
{
    m_p_impl = new( os_cluster::with(this),
                    os_Cursor<T*>::get_os_typespec() ) 
                    os_Cursor<T*>( *coll.m_p_impl ) ;
    m_p_impl->last() ;
}


/******************************************************************************
Member Function: ~_ODI_AF_Stack_iterator()
Class Name     : _ODI_AF_Stack_iterator<T> 
Purpose        : Delete the stack iterator
Parameters     : None
Return Value   : None
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T>
_ODI_AF_Stack_iterator<T>::~_ODI_AF_Stack_iterator()
{
	delete m_p_impl ;
}

/******************************************************************************
Member Function: T* top()
Class Name     : _ODI_AF_Stack_iterator<T> 
Purpose        : Sets the cursor to the top element ie the element which is 
               : inserted last and returns element. 
Parameters     : None
Return Value   : The top element or zero if collection is empty
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T>
T*_ODI_AF_Stack_iterator<T>::top()
{
    T* value = m_p_impl->last() ;
    return value ;
}

/******************************************************************************
Member Function: T* next()
Class Name     : _ODI_AF_Stack_iterator<T> 
Purpose        : Sets the cursor to the next element and return element. If
               : collection is empty returns zero.                                 
Parameters     : None
Return Value   : the next element and returns zero if collection is empty
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T>
T* _ODI_AF_Stack_iterator<T>::next()
{
    T* value = m_p_impl->previous() ;
    return value ;
}

/******************************************************************************
Member Function: T* retrieve()
Class Name     : _ODI_AF_Stack_iterator<T> 
Purpose        : retrieves the current element.            
Parameters     : None
Return Value   : returns the element.
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T>
T* _ODI_AF_Stack_iterator<T>::retrieve()
{
    T* value = (T*)0;
    if( !m_p_impl->null() )
       value = m_p_impl->retrieve() ;
    return value ;
}

