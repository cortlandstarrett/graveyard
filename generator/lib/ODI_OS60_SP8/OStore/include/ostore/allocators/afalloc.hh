/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef __OS_ALLOCATOR__
#define __OS_ALLOCATOR__

#include <stddef.h>
#include <ostore/portypes.hh>
#include <ostore/ostore.hh>
#include <ostore/allocators/afxalloc.hh>

#if ((__SUNPRO_CC >= 0x520) && (__SUNPRO_CC_COMPAT == 4))
#define __os_sol2c4_compat
#endif


/* forward declarations */
template < class T > class os_Allocator ;

/******************************************************************************
Class Name      : os_Allocator
Description     : this is a standard allocator interface
Remarks         : 
******************************************************************************/

/* specialization for void */

#ifdef __os_sol2c5
template <> 
#endif
class os_Allocator<void>
{
    public:

    typedef void*       pointer;
    typedef const void* const_pointer;
    /*  reference-to-void members are impossible */
    typedef void  value_type;
#ifndef _OS_Desktop
    /*template <class U> 
    struct rebind { typedef os_Allocator<U> other; }; */
#else
	template <class U> 
    struct rebind { typedef os_Allocator<U> other; };
#endif

};

template < class T >
class os_Allocator 
{
    public: /* standard interface */
    
    typedef T         value_type;
    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;
    
    typedef T*        pointer;
    typedef const T*  const_pointer;
    
    typedef T&        reference;
    typedef const T&  const_reference;

    /* reference to pointer conversion */
    pointer address( reference x ) const ;
    const_pointer address( const_reference x ) const ;

    /* constructor and destructor */
    os_Allocator() ;
#ifndef _OS_Desktop
    os_Allocator( const os_Allocator< T >& u_alloc )  ;
#else
    template < class U > 
    os_Allocator( const os_Allocator< U >& u_alloc ) 
    {
        m_p_x_allocator = u_alloc.get_extended_allocator() ; /* TODO: same copy or clone */
        b_bound = ( m_p_x_allocator != 0 );
    }
#endif
    ~os_Allocator() ;

    /* allocate and deallocate */
    pointer allocate( size_type number_elements, 
                      os_Allocator<void>::const_pointer hint = 0)
    {
      if( ! b_bound ) {
	if( ! bind_imp() )
	  err_allocator_framework.signal("No Extended Allocator bound to the standard allocator");
      }

      return ( 1 == number_elements ) ?
	(pointer)(m_p_x_allocator->allocate(sizeof(T), 
					    os_Allocator<T>::get_allocated_type_typespec(),
					    hint )) :
	(pointer)(m_p_x_allocator->allocate(sizeof(T), 
					    os_Allocator<T>::get_allocated_type_typespec(),
					    number_elements, 
					    hint )) ;
    }

    void deallocate( pointer p, size_type number_elements );

    void construct( pointer p, const T& val ) ;
    void destroy( pointer p );

    size_type max_size()  ;


#ifndef _OS_Desktop
    /*template < class U > 
    struct rebind { typedef os_Allocator< U > other; };*/
#else
    template < class U > 
    struct rebind { typedef os_Allocator< U > other; };
#endif
  
    public: /* Extended Interface */
    /* initialization. bind to the said extended allocator  */
    os_Allocator( os_extended_allocator* ) ;

    /* get and set extended allocator */
    os_extended_allocator* get_extended_allocator() const ;
    void set_extended_allocator( os_extended_allocator* ) ; /* bind it */

    /* if persistent return true */
    os_boolean is_persistent() ;

    /* bind to the extended allocator based on allocation context */
    os_boolean bind() ;
    
    static os_typespec* get_allocated_type_typespec();

    private: /* private interface */
    
    /* bind is implemented here */
    os_boolean bind_imp()  ;

    os_extended_allocator* m_p_x_allocator;    /* default:0 */

    /* bound to extended allocator or not */
    os_boolean b_bound ; /* default:false */
};

/*************************************************************/

template < class T >
os_boolean operator==(const os_Allocator<T>&, const os_Allocator<T>&) ;
template < class T >
os_boolean operator!=(const os_Allocator<T>&, const os_Allocator<T>&) ;

template < class T >
void* operator new (size_t, 
		    os_Allocator<T>& alloc,
#if defined(__os_aix43) || defined(__os_sol2c5) || defined(__os_sol2c4_compat)
		    
/* AIX xlC compiler, and cafe6.0 do not allow default function arguments
   in a template */
		    const void *hint)
#else
		    const void *hint = 0)
#endif
{
  return alloc.allocate(1, hint);
}

template < class T > 
void* operator new (size_t, os_Allocator<T>& alloc,
		    size_t number_of_elements,
#if defined(__os_aix43) || defined(__os_sol2c5) || defined(__os_sol2c4_compat)
		    const void *hint)
#else
		    const void *hint = 0)
#endif
{
  return alloc.allocate(number_of_elements, hint);
}



/* placement delete operators for VC++ 6.0 */

#if (_OS_MicrosoftCC >= 1200)    /* MSVC 6.0 and above */
template < class T >
void operator delete(void* addr, os_Allocator<T>&, const void*)
{ delete addr; }

template < class T >
void operator delete(void* addr, os_Allocator<T>&, size_t number_of_elements, const void*)
{ delete _OS_VECTOR addr; }
#endif

#endif



