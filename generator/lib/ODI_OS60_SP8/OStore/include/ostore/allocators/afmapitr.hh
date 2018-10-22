/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/******************************************************************************
FileName      : afmapitr.hh
Purpose       : create a map iterator class
Contents      : declaration of _ODI_AF_Map_iterator class
Environment   : VC++5.0
Last Delta on : 
Revisions     : 
******************************************************************************/

#ifndef ___ODI_AF_MAP_ITERATOR__
#define ___ODI_AF_MAP_ITERATOR__

#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/allocators/afmap.hh>

/******************************************************************************
Class Name      : _ODI_AF_Map_iterator  
Description     : this is a templated class and is a wrapper over the 
  			    : os_Cursor. 
Remarks         : Elements returned by the iterator, must not be deleted.
                : this is wrapper over os_Cursor, collection manipulation is
                : not allowed.
******************************************************************************/
 template<class T> class _ODI_AF_Map ;

template< class T >
class _ODI_AF_Map_iterator
{
  public :
	ODI_INST();
  
        /* order by address, safe cursor is created */
        _ODI_AF_Map_iterator( const _ODI_AF_Map<T>& coll ) ;
        /* unsafe cursor is created */
        _ODI_AF_Map_iterator( const os_Collection<T*>& coll ) ;
        /* destroy the cursor */
        ~_ODI_AF_Map_iterator() ;

        /* set the cursor to first element, and return the first element 
           if Map is empty, returns 0 */
        T* first() ;
        /* set the cursor to last element, and return the last element
           if Map is empty, returns 0 */
        T* last() ;

        /* set the cursor to next element, and return the next element 
           if m_p_impl->null() returns 0 */
        T* next() ;
        /* set the cursor to previous element, and return the previous element 
           if m_p_impl->null() returns 0 */
        T* previous() ;

        /* return the current element, if m_p_impl->null() returns 0 */
        T* retrieve() ;

        /* friend _ODI_AF_Map */
        friend class _ODI_AF_Map<T> ;
    
    private :
        /* Copy constructor is not implemented */
        _ODI_AF_Map_iterator( const _ODI_AF_Map_iterator<T>& ) ;
        /* Assignment operator is not implemented */
        _ODI_AF_Map_iterator<T>& operator=( const _ODI_AF_Map_iterator<T>& ) ;

        os_Cursor< T* >* m_p_impl ;

} ;

#endif
