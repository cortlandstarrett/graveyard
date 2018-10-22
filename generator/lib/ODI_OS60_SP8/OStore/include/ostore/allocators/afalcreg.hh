/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef ___ODI_AF_ALLOCATOR_REGISTRY__
#define ___ODI_AF_ALLOCATOR_REGISTRY__

#include <ostore/portypes.hh>
#include <ostore/allocators/afstring.hh>
#include <ostore/allocators/afxalloc.hh>
#include <ostore/allocators/afitratr.hh>

/******************************************************************************
Class Name      : os_allocator_registry
Description     : this is allocator registry class
Remarks         : 
******************************************************************************/
typedef _ODI_AF_Map< os_extended_allocator > _ODI_allocator_map ;


class _OS_DLLIMPORT(_OS_ALLOC) os_allocator_registry
{
    public :

        /* destructor */
        ~os_allocator_registry() ;

        /* get the unique instance of the allocator registry
           if not initialized, initialize it */
        static os_allocator_registry* instance() ;

        static os_typespec* get_os_typespec() ;

        /* set the allocator db path and the allocator root name */
        static void alloc_db( os_string database_path, os_string root_name ) ;


        /* register the given allocator with given name, 
           if an allocator exists with same name do not register */
        os_boolean enter( os_string alloc_name, 
                          os_extended_allocator* p_alloc ) ;
        /* deregister the allocator by given name and return.
           if no allocator registed with the given name return null */
        os_extended_allocator* remove( os_string alloc_name ) ;

        /* get allocator name from rule engine, and 
           return the allocator by given name */
        os_extended_allocator* get_allocator() ;

        /* return the allocator with given name.
           if not existing, return null */
        os_extended_allocator* get_allocator( os_string alloc_name ) ;

        /* create an iterator for all the allocator registered and return.*/
        os_alloc_iterator*     get_allocators() ;
        /* get the name of the allocator, pointed to by allocator iterator */
        os_string* get_allocator_name( const os_alloc_iterator& alloc_itr ) ;

        os_boolean clear_registry() ;

	/* checks for the existance of a specific allocator */
	os_boolean exists( const os_string& alloc_name ) const ;

   protected:

        /* protected constructor */
        os_allocator_registry() ;

    private:

        /* if necessay, read the state from database and initialize itself */
        os_boolean initialize() ;

        /* not implemented */
        os_allocator_registry( const os_allocator_registry& ) ;
        os_allocator_registry& operator=( const os_allocator_registry& );


    private :

        static os_allocator_registry* m_p_self ;
        _ODI_allocator_map* m_p_allocators ;

};

#endif
