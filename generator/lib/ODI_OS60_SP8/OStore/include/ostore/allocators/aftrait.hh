/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/******************************************************************************
FileName      : aftrait.hh
Purpose       : to create traits
Contents      : declaration of os_trait class
Environment   : VC++5.0
Last Delta on : 
Revisions     : 
******************************************************************************/

#ifndef __OS_TRAIT__
#define __OS_TRAIT__

#include <ostore/portypes.hh>
#include <ostore/allocators/afstring.hh>

/******************************************************************************
Class Name      : os_trait
Description     : this is abstract base class for traits
Remarks         : 
******************************************************************************/
class _OS_DLLIMPORT(_OS_ALLOC) os_trait : public os_virtual_behavior
{
    public:


    os_trait() {}

    os_trait( const os_string& trait_name ) ;

    virtual os_string  get()  = 0 ;
    virtual void set( const os_string& str_trait_value ) = 0 ;

    os_string get_name() ;

    os_string get_type_string() ;
 
    protected:

    void set_type_string( const os_string& type_string ) ;
       
    os_string m_trait_name ;
    os_string m_type_string ;
};

#endif
