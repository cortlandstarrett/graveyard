/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef ___ODI_AF_STACK__
#define ___ODI_AF_STACK__

#include <ostore/portypes.hh>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/allocators/afstring.hh>

/* forward declarations */
template< class T > class _ODI_AF_Stack_iterator ;

/******************************************************************************
Class Name      : _ODI_AF_Stack 
Description     : this is a templated class and is a wrapper over os_List to
                : to provide the behavior of stack
Remarks         : 
******************************************************************************/

template< class T > 
class _ODI_AF_Stack
{
    public:

    /* constructor and destructor */
    /* initializes pointer to the os_List object and sets the behavior */
    _ODI_AF_Stack() ;
    /* Remove all the value pushed on the stack, do not delete the value
       deletes the os_List object */
    ~_ODI_AF_Stack() ;

    static os_typespec* get_os_typespec() ;

    /* member functions */
    /* push the value at the top of the stack, null is ignored */
    void push( T* value ) ;
    /* remove the value from the top of the stack and return */
    T* pop() ;
    /* remove all the entries, do not delete the values */
    void remove_all()  ;
    /* check for an empty stack */
    os_boolean is_empty() const ;

    friend class _ODI_AF_Stack_iterator<T> ;

    private:

    /* Copy constructor */
     _ODI_AF_Stack( const  _ODI_AF_Stack<T>& stack ) ;
    /* Assignment operator */
     _ODI_AF_Stack<T>& operator=( const  _ODI_AF_Stack<T>& stack ) ;	

    os_List<T*>* m_p_impl;
    
} ;

#endif
