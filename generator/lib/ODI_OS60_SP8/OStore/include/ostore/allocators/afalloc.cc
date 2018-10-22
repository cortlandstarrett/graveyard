/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_AFALLOC_CC
#define _OS_AFALLOC_CC 1

#include <ostore/allocators/afalloc.hh>
#include <ostore/allocators/afxalloc.hh>
#include <ostore/allocators/afalcreg.hh>

template< class T >
os_typespec * Get_Typespec(T * pt);

/******************************************************************************
Member Function: os_Allocator()
Class Name     : os_Allocator<T> 
Purpose        : Initializes the member variables to default values
Parameters     : None
Return Value   : None
Remarks        :
******************************************************************************/
template< class T >
os_Allocator<T>::os_Allocator()
{
  m_p_x_allocator = (os_extended_allocator*)0 ;
  b_bound = 0 ; 
}

/******************************************************************************
Member Function: ~os_Allocator()
Class Name     : os_Allocator<T> 
Purpose        : do nothing destructor, if cloning is done in copy constructor
               : then delete m_p_x_allocator
Parameters     : None
Return Value   : None
Remarks        :
******************************************************************************/
template< class T >
os_Allocator<T>::~os_Allocator()
{
    /* TODO: delete m_p_x_allocator if cloning is done in copy constructor */
}

/******************************************************************************
Member Function: address() const
Class Name     : os_Allocator<T> 
Purpose        : reference to pointer conversion
Parameters     : reference x
Return Value   : pointer
Remarks        :
******************************************************************************/
template< class T >
_OS_TYPENAME os_Allocator<T>::pointer os_Allocator<T>::address( reference x ) const
{
  return &x ;
}

/******************************************************************************
Member Function: address() const
Class Name     : os_Allocator<T> 
Purpose        : reference to pointer conversion
Parameters     : const_reference x
Return Value   : const_pointer
Remarks        :
******************************************************************************/
template< class T >
_OS_TYPENAME os_Allocator<T>::const_pointer os_Allocator<T>::address(const_reference x)const
{
  return &x ;
}
/******************************************************************************
Member Function: deallocate()
Class Name     : os_Allocator<T> 
Purpose        : deallocate n objects
Parameters     : pointer p, size_type number_elements
Return Value   : void
Remarks        :
******************************************************************************/
template< class T >
void os_Allocator<T>::deallocate( pointer p, size_type number_elements )
{
  if( ! b_bound ) {
    if( ! bind_imp() )
      err_allocator_framework.signal("No Extended Allocator bound to the standard allocator");
  }
  m_p_x_allocator->deallocate( p, number_elements ) ;
  return ;
}

/******************************************************************************
Member Function: construct()
Class Name     : os_Allocator<T> 
Purpose        : construct the object at the given location
Parameters     : pointer p, const T& val
Return Value   : void
Remarks        :
******************************************************************************/
template< class T >
void os_Allocator<T>::construct( pointer p, const T& val )
{
  if( p )
    *p = T( val ); 
  return;
}

/******************************************************************************
Member Function: destroy()
Class Name     : os_Allocator<T> 
Purpose        : destroy the object at the given location
Parameters     : pointer p
Return Value   : void
Remarks        :
******************************************************************************/
template< class T >
void os_Allocator<T>::destroy( pointer p )
{
  if( p )
    p->~T() ; 
  return ;
}

/******************************************************************************
Member Function: max_size() const
Class Name     : os_Allocator<T> 
Purpose        : maximum size of the object
Parameters     : None
Return Value   : size_type
Remarks        :
******************************************************************************/
template< class T >
_OS_TYPENAME os_Allocator<T>::size_type os_Allocator<T>::max_size() 
{
  if( ! b_bound ) {
    if( ! bind_imp() )
      err_allocator_framework.signal("No Extended Allocator bound to the standard allocator");
  }
  return m_p_x_allocator->max_size() ;
}

/******************************************************************************
Member Function: os_Allocator()
Class Name     : os_Allocator<T> 
Purpose        : initialization. bind to the said extended allocator
Parameters     : os_extended_allocator* p_x_alloc
Return Value   : None
Remarks        :
******************************************************************************/
template< class T >
os_Allocator<T>::os_Allocator( os_extended_allocator* p_x_alloc )
{
  m_p_x_allocator = p_x_alloc ; /* TODO: same copy or clone */
  b_bound = ( m_p_x_allocator != 0);
}

/******************************************************************************
Member Function: get_extended_allocator() const
Class Name     : os_Allocator<T> 
Purpose        : get the extended allocator
Parameters     : None
Return Value   : os_extended_allocator*
Remarks        :
******************************************************************************/
template< class T >
os_extended_allocator* os_Allocator<T>::get_extended_allocator() const
{
  return ( b_bound ) ? m_p_x_allocator : (os_extended_allocator*)0 ;
}

/******************************************************************************
Member Function: set_extended_allocator()
Class Name     : os_Allocator<T> 
Purpose        : set and bind the extended allocator
Parameters     : None
Return Value   : os_extended_allocator*
Remarks        :
******************************************************************************/
template< class T >
void os_Allocator<T>::set_extended_allocator(os_extended_allocator* p_x_alloc)
{
  m_p_x_allocator = p_x_alloc ; /* TODO:delete the existing one ? */
  b_bound = ( m_p_x_allocator != 0 );
}

/******************************************************************************
Member Function: is_persistent()
Class Name     : os_Allocator<T> 
Purpose        : is the extended allocator is persistent ?
Parameters     : None
Return Value   : os_boolean
Remarks        :
******************************************************************************/
template< class T >
os_boolean os_Allocator<T>::is_persistent()
{
  if( ! b_bound ) {
    if( ! bind_imp() )
      err_allocator_framework.signal("No Extended Allocator bound to the standard allocator");
  }
  return m_p_x_allocator->is_persistent() ;
}

/******************************************************************************
Member Function: bind()
Class Name     : os_Allocator<T> 
Purpose        : bind to the extended allocator based on allocation context
               : set the state to bound
Parameters     : None
Return Value   : os_boolean
Remarks        :
******************************************************************************/
template< class T >
os_boolean os_Allocator<T>::bind()  
{
  b_bound = bind_imp() ;
  return b_bound ;
}
    
/******************************************************************************
Member Function: bind_imp()
Class Name     : os_Allocator<T> 
Purpose        : bind to the extended allocator based on allocation context
               : do not set the state to bound
Parameters     : None
Return Value   : os_boolean
Remarks        :
******************************************************************************/
template< class T >
os_boolean os_Allocator<T>::bind_imp()  
{
  m_p_x_allocator = os_allocator_registry::instance()->get_allocator();
  return (m_p_x_allocator!=0);
}

/******************************************************************************
Member Function: operator==()
Class Name     : global
Purpose        : comparison operator
Parameters     : const os_Allocator<T>&, const os_Allocator<T>&
Return Value   : os_boolean
Remarks        :
******************************************************************************/
template < class T >
os_boolean operator==(const os_Allocator<T>& left_alloc, 
                      const os_Allocator<T>& right_alloc )
{
  return( left_alloc.get_extended_allocator() == 
	  right_alloc.get_extended_allocator() ) ;
}

/******************************************************************************
Member Function: operator!=()
Class Name     : global
Purpose        : comparison operator
Parameters     : const os_Allocator<T>&, const os_Allocator<T>&
Return Value   : os_boolean
Remarks        :
******************************************************************************/
template < class T >
os_boolean operator!=(const os_Allocator<T>& left_alloc, 
                      const os_Allocator<T>& right_alloc )
{
  return( left_alloc.get_extended_allocator() != 
	  right_alloc.get_extended_allocator() ) ;
}

/******************************************************************************
Member Function: os_Allocator( const os_Allocator< T >& u_alloc ) 
Class Name     : os_Allocator<T>
Purpose        : copy constructor for Solaris
Parameters     : const os_Allocator<T>&
Return Value   : null
Remarks        : this is implemented for Solaris
******************************************************************************/
#if !defined(_OS_Desktop)
template < class T > 
os_Allocator<T>::os_Allocator( const os_Allocator< T >& u_alloc ) 
{
  m_p_x_allocator = u_alloc.get_extended_allocator() ; 
  b_bound = ( m_p_x_allocator != 0 );
}
#endif

/******************************************************************************
Member Function: get_allocated_type_typespec()
Class Name     : os_Allocator<T> 
Purpose        : get the typespec for type T
               : 
Parameters     : None
Return Value   : os_typespec *
Remarks        :
******************************************************************************/
template< class T >
os_typespec * os_Allocator<T>::get_allocated_type_typespec()  
{
  return Get_Typespec((T *) 0);
}

template< class T >
os_typespec * Get_Typespec(T * pt)  
{
  return T::get_os_typespec();
}

#endif

