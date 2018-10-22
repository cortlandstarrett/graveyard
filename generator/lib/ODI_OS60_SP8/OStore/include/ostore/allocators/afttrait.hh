/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef ___ODI_AF_TTRAIT__
#define ___ODI_AF_TTRAIT__

#include <ostore/portypes.hh>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/allocators/afstring.hh>
#include <ostore/allocators/aftrtype.hh>
#include <ostore/allocators/aftrait.hh>

#if !defined(__os_sol2c5)
class ostream ;
#endif
/******************************************************************************
Class Name      : os_Trait
Description     : this is templated implementation of os_trait abstract 
                : base class
Remarks         : 
******************************************************************************/
template <class TRAIT_TYPE, class TYPE>
class os_Trait : public os_trait
{
public:

  ODI_INST();
  
  os_Trait() {}

    /* only name is known, value is null */
    os_Trait( const os_string& trait_name )
        : os_trait( trait_name )
    {
        set_type_string( TRAIT_TYPE::get_type_string() ) ;
        m_trait_value = TRAIT_TYPE::get_null() ;
    } 

    /* name and value both are known, value is string */
    os_Trait( const os_string& trait_name, 
                   const os_string& str_trait_value )
        : os_trait( trait_name )
    {
        set_type_string( TRAIT_TYPE::get_type_string() );
        m_trait_value = TRAIT_TYPE::from_string( str_trait_value );
    }

    /* overriding pure virtual */
    os_string get()
#if defined(_OS_DECCXX) || defined(__os_xlc)
;
#else
    {
        return TRAIT_TYPE::to_string( m_trait_value );
    }
#endif
    void set( const os_string& str_trait_value )
    {
        m_trait_value = TRAIT_TYPE::from_string( str_trait_value ) ;
     
    }

    static os_typespec* get_os_typespec() ;

    private:
    
#if defined(_OS_Desktop) || defined(__os_hp11) || defined(__os_linux)
    typename TRAIT_TYPE::value_type m_trait_value ; 
#else    
    TRAIT_TYPE::value_type m_trait_value ;
#endif
    
   
}; 
template <class TRAIT_TYPE, class TYPE>
void display_traits(os_Trait<TRAIT_TYPE, TYPE>& trait )
{
  cout << "Trait Name : " << trait.get_name() 
       << "   Type :       " << trait.get_type_string()
       << "   Value :      " << trait.get() << endl;

}

//     trait list: Transient structure 

typedef os_List< os_Trait < os_Trait_unsigned_int32, os_string > * > os_Trait_List ;

#endif


