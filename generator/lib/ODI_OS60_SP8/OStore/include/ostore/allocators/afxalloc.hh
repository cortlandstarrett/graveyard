/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef __OS_X_ALLOCATOR__
#define __OS_X_ALLOCATOR__

#include <ostore/portypes.hh>
#include <ostore/os_int64.hh>
#include <ostore/allocators/afstring.hh>
#include <ostore/allocators/afitratr.hh>

/******************************************************************************
Class Name      : os_extended_allocator
Description     : this is a extended allocator interface
Remarks         : 
******************************************************************************/
class _OS_DLLIMPORT(_OS_ALLOC) os_extended_allocator 
{
    public:

    typedef size_t    size_type;
    typedef ptrdiff_t difference_type;

    /* do nothing constructor */
    os_extended_allocator() ;
    /* do nothing virtual destructor */
    virtual ~os_extended_allocator() ;

    /* allocate single object of size object_size, and type_spec t_spec */

    void* allocate( size_type object_size, 
		    os_typespec * t_spec, 
                    const void* hint = 0 ) ;

    void* allocate( size_type object_size, 
		    os_typespec * t_spec, 
		    size_type number_elements, 
		    const void* hint = 0 ) ;

    /* deallocatoe n objects at position p */
    virtual void deallocate( void* p, size_type number_elements ) ;

    /* get iterator for traits */
    virtual os_trait_iterator* get_traits() const;
    /* set a trait */
    virtual os_boolean set_trait( os_trait * ) ; 
    /* get a trait by name */
    virtual os_trait* get_trait( os_string trait_name ) const;
    /* initialize the state if any */
    virtual os_boolean initialize() ;
    /* clean the state if any */
    virtual os_boolean clean() ;
    /* is it a persistent allocator */
    virtual os_boolean is_persistent() ; /* if persistent return true */

    static os_typespec* get_os_typespec();

    public : /* interface */

    /* allocate single object of size object_size, for given os_typespec* */
    virtual void* allocate_type( size_type object_size, 
                                 os_typespec* type_spec,
                                 const void* hint = 0 ) = 0 ;
    /* allocate array of objects of size object_size, for given os_typespec* */
    virtual void* allocate_type( size_type object_size, 
                                 os_typespec* type_spec,
                                 size_type number_elements, 
                                 const void* hint = 0 ) = 0 ;
    virtual os_unsigned_int32 max_size() const = 0 ;
    /* create a new copy of the same allocator */
    virtual os_extended_allocator* clone() = 0 ;
    
    
} ;

os_boolean operator==( const os_extended_allocator& left_x_alloc, 
                       const os_extended_allocator& right_x_alloc ) ;
os_boolean operator!=( const os_extended_allocator& left_x_alloc, 
                       const os_extended_allocator& right_x_alloc ) ;


#endif

