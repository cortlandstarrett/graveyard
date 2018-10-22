/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/******************************************************************************
Project       : ODI001
FileName      : afmapitr.cc
Purpose       : This is a wrapper over os_Cursor<T>. This is a friend of 
              : _ODI_AF_Map<T> so that it can access the implementation of 
              : _ODI_AF_Map<T> 
Author        : Anjana S
Contents      : 
External 
Functions     : 
Environment   : VC++5.0
Last Delta on : 
Revisions     : 
******************************************************************************/

#include <ostore/allocators/afmapitr.hh>

/******************************************************************************
Member Function: _ODI_AF_Map_iterator( const _ODI_AF_Map<T>& coll )
Class Name     : _ODI_AF_Map_iterator<T> 
Purpose        : It intializes the embedded cursor. The cursor is constructed 
               : for the implementation of _ODI_AF_Map<T>
Parameters     : a const reference to _ODI_AF_Map<T>
Return Value   : None
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T> 
_ODI_AF_Map_iterator<T>::_ODI_AF_Map_iterator( const _ODI_AF_Map<T>& coll )
{
    
    m_p_impl = new( os_cluster::with(this), 
                    os_Cursor<T*>::get_os_typespec())
                    os_Cursor<T*>( *coll.m_p_impl ) ;
    m_p_impl->first() ;
}

/******************************************************************************
Member Function: _ODI_AF_Map_iterator( const os_Collection<T>& coll )
Class Name     : _ODI_AF_Map_iterator<T> 
Purpose        : It intializes the embedded cursor. The cursor is constructed for
               : the implementation of os_Collection<T> 
Parameters     : a const reference to os_Collection<T>
Return Value   : None
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T> 
_ODI_AF_Map_iterator<T>::_ODI_AF_Map_iterator(  const os_Collection<T*>& coll )
{

   m_p_impl = new( os_cluster::with(this), 
                    os_Cursor<T*>::get_os_typespec())
                    os_Cursor<T*>( coll ) ;
}

/******************************************************************************
Member Function: ~_ODI_AF_Map_iterator()
Class Name     : _ODI_AF_Map_iterator<T> 
Purpose        : Delete the cursor
Parameters     : None
Return Value   : None
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T>
_ODI_AF_Map_iterator<T>::~_ODI_AF_Map_iterator()
{
    delete m_p_impl ;
}

/******************************************************************************
Member Function: T* first()
Class Name     : _ODI_AF_Map_iterator<T> 
Purpose        : Set the cursor to the first element and return element. If
               : collection is empty returns zero.           
Parameters     : None
Return Value   : The first element or zero if collection is empty
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T>
T* _ODI_AF_Map_iterator<T>::first()
{
    T* value = m_p_impl->first() ;
    return value ;
}

/******************************************************************************
Member Function: T* last()
Class Name     : _ODI_AF_Map_iterator<T> 
Purpose        : Set the cursor to the last element and return element. If
               : collection is empty returns zero.                      
Parameters     : None
Return Value   : Last element or zero if collection is empty
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T>
T* _ODI_AF_Map_iterator<T>::last()
{
    T* value = m_p_impl->last() ;
    return value ;
}

/******************************************************************************
Member Function: T* next()
Class Name     : _ODI_AF_Map_iterator<T> 
Purpose        : Set the cursor to the next element and return element. If
               : collection is empty returns zero.                                 
Parameters     : None
Return Value   : the next element and returns zero if collection is empty
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T>
T* _ODI_AF_Map_iterator<T>::next()
{
    T* value = (T*)0 ;
    if( !m_p_impl->null() )
       value = m_p_impl->next() ;
    return value ;
}

/******************************************************************************
Member Function: T* previous()
Class Name     : _ODI_AF_Map_iterator<T> 
Purpose        : Set the cursor to the previous element and returns element. If
               : collection is empty returns zero.            
Parameters     : None
Return Value   : returns the element or zero if the collection is empty                
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T>
T* _ODI_AF_Map_iterator<T>::previous()
{
    T* value = (T*)0 ;
    if( !m_p_impl->null() )
       value = m_p_impl->previous() ;
    return value ;
}

/******************************************************************************
Member Function: T* retrieve()
Class Name     : _ODI_AF_Map_iterator<T> 
Purpose        : retrieves the current element. If collection is empty 
               : returns zero.           
Parameters     : None
Return Value   : returns the element.
Author         : Anjana S
Remarks        :
******************************************************************************/

template <class T>
T* _ODI_AF_Map_iterator<T>::retrieve()
{
    T* value = (T*)0;
    if( !m_p_impl->null() )
       value = m_p_impl->retrieve() ;
    return value ;
}





