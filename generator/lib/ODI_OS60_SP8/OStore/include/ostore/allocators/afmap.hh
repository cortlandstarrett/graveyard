/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef ___ODI_AF_MAP__
#define ___ODI_AF_MAP__

#include <ostore/portypes.hh>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/coll/dict_pt.cc>
#include <ostore/allocators/afstring.hh>
#include <ostore/allocators/afmapitr.hh>

#define _ODI_AF_MARK_MAP( value ) \
OS_MARK_DICTIONARY( os_string, value* ) \
OS_MARK_SCHEMA_TYPESPEC(( _ODI_AF_Map< value > ))

#define _ODI_AF_TRANSIENT_MAP( value ) \
OS_TRANSIENT_DICTIONARY( os_string, value* ) \
os_typespec* _ODI_AF_Map< value >::get_os_typespec() \
    { return (os_typespec*)0 ; }

#define _ODI_AF_TRANSIENT_MAP_NOKEY( value ) \
OS_TRANSIENT_DICTIONARY_NOKEY( os_string, value* ) \
os_typespec* _ODI_AF_Map< value >::get_os_typespec() \
    { return (os_typespec*)0 ; }


/******************************************************************************
Class Name      : _ODI_AF_Map  
Description     : this is a templated class and is a wrapper over the 
  			    : os_Dictionary. 
Remarks         : 
******************************************************************************/
template< class T> class _ODI_AF_Map_iterator ;

template< class T > 
class _ODI_AF_Map
{
    public:

    /* constructor and destructor */
    /* initializes pointer to the os_Dictionary object and takes care of 
    setting the behaviour */
    _ODI_AF_Map() ;
    ~_ODI_AF_Map() ;

    /* static functions */
    /* create the map persistently - will be implemented later */
    /* static os_Map<T>& create(os_database* db) ;
    static os_Map<T>& create(os_segment* seg) ;
    static os_Map<T>& create(os_object_cluster* cls) ;
    destroy map created persistently - will be implemented later
    static void destroy( os_Map< T >& map ) ; */
    static os_typespec* get_os_typespec() ; 

    /* member functions */
    /* inserts the key value pair into the map. Checks for null value, null key
    and duplicate keys before inserting */
    os_boolean insert( const os_string& key, T* value ) ;

    /* deletes the existing value if any and inserts the new key value pair */
    os_boolean force_insert( const os_string& key, T* value ) ;

    /* removes the value and returns it */
    T* remove( const os_string& key ) ;

    /* removes and deletes all the entries */
    void clear()  ;

	/* testing */
	void test_clear() ;

    /* picks the value for a specific key */
    T* retrieve( const os_string& key ) const ;

	/* picks the key at the specified cursor location */
    const os_string* retrieve_key( const _ODI_AF_Map_iterator<T>& itr ) const ;

    /* checks for the existance of a specific key */
    os_boolean exists( const os_string& key ) const ;

    /* check for an empty map */
    os_boolean is_empty() const ;

    /* os_Map iterator */ 
    friend class _ODI_AF_Map_iterator<T> ;
    
    private:

    /*Copy constructor*/
    _ODI_AF_Map( const _ODI_AF_Map<T>& map ) ;
    /*Assignment operator*/
    _ODI_AF_Map<T>& operator=( _ODI_AF_Map<T>& map ) ;

    os_Dictionary< os_string, T*>* m_p_impl;
    
} ;

#endif
