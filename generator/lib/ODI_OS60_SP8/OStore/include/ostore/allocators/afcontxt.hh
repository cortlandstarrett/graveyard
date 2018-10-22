/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef __OS_ALLOCATION_CONTEXT__
#define __OS_ALLOCATION_CONTEXT__

#include <ostore/portypes.hh>
#include <ostore/allocators/afstring.hh>
#include <ostore/allocators/afttrait.hh>

/******************************************************************************
Class Name      : os_allocation_context
Description     : this is allocation context class
Remarks         : 
******************************************************************************/
typedef os_Trait<os_Trait_string, os_string> os_context_trait ;

class _OS_DLLIMPORT(_OS_ALLOC) os_allocation_context
{
    public:

        /* constructors and destructors */
        /* register with context stack in all constructors */
        os_allocation_context( const os_string& context_name ) ;
        os_allocation_context( const os_string& context_name, 
                               const os_string& context_value ) ;
        /* de register from context stack in destructor */
        ~os_allocation_context() ;
        
        /* match only the context name */
        os_boolean is_in_context( const os_string& context_name ) ;
        /* match context name and value, do not create another context */
        os_boolean is_in_context( const os_string& context_name, 
                                  const os_string& context_value ) ;
        /* match context name and value */
        os_boolean is_in_context( const os_allocation_context& in_context ) ;

        /* get and set methods for GUI */
        os_string get_name() const ;
        os_string get_value() const ;
        os_string get_help() const ;
        os_string get_desc() const ;
        void set_help( const os_string& help ) ;
        void set_desc( const os_string& desc ) ;

    private:

        /* not implemented */
        os_allocation_context( const os_allocation_context& in_context ) ;
        os_allocation_context& operator=( const os_allocation_context& );
          
    private:/* data */

        os_context_trait*  m_p_trait ;
        os_string            m_help ;
        os_string            m_desc ;
};

#endif
