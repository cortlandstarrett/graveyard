/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_AF_MAP_HH
#define _OS_AF_MAP_HH 1

#include <ostore/portypes.hh>
#include <ostore/allocators/afmap.hh>

/******************************************************************************
Member Function: _ODI_AF_Map()
Class Name     : _ODI_AF_Map<T> 
Purpose        : Initializes the pointer to os_dictionary object and sets the
               : behaviour
Parameters     : None
Return Value   : None
Remarks        :
******************************************************************************/

template< class T> 
_ODI_AF_Map<T>::_ODI_AF_Map()
{
    os_cluster_with tmp_os_cluster_with = os_cluster::with(this);
    m_p_impl = &os_Dictionary<os_string, T*>::create( 
                                (os_cluster_with &) tmp_os_cluster_with);
}


/******************************************************************************
Member Function: ~_ODI_AF_Map()
Class Name     : _ODI_AF_Map<T> 
Purpose        : deletes the contents of _ODI_AF_Map datastructure and deallocates 
               : storage
Parameters     : None
Return Value   : None
Remarks        :
******************************************************************************/

template< class T> 
_ODI_AF_Map<T>::~_ODI_AF_Map()
{
    /* deletes all the elements in the map */
    clear() ;
    /* destroys the map and deallocates storage */ 
    os_Dictionary<os_string, T*>::destroy( *m_p_impl ) ;
}

/******************************************************************************
Member Function: os_boolean insert( const os_string& key, T* value )
Class Name     : _ODI_AF_Map<T> 
Purpose        : Inserts the specified element with its associated key. Checks 
               : for null key, null value and duplicate keys before inserting.
Parameters     : It takes two arguments. The first one is a const reference
               : to key and the second one is the value 
Return Value   : true if the insertion is successful and false if insertion
               : fails
Remarks        :
******************************************************************************/

template< class T> 
os_boolean _ODI_AF_Map<T>::insert( const os_string& key, T* value )
{
    os_boolean result ;
    /* check if key or value is null */ 
    if( key.is_null() || value == (T*)0 || exists( key ) ) 
       result = 0;
    else 
    {   
        m_p_impl->insert( key, value ) ;
        result = 1;
    }
        
    return result ;
}

/******************************************************************************
Member Function: os_boolean force_insert( const os_string& key, T* value )
Class Name     : _ODI_AF_Map<T> 
Purpose        : deletes the existing key value pair if any, and inserts the new 
               : key value pair
Parameters     : It takes two arguments. The first one is a const reference
               : to key and the second one is the value
Return Value   : true if the insertion is successful and false if insertion
               : fails
Remarks        :
******************************************************************************/

template< class T> 
os_boolean _ODI_AF_Map<T>::force_insert( const os_string& key, T* value )
{
    if( exists( key ) )
    {
        /* delete the old value and the key pair */ 
        T* old_value = remove( key ) ;
        delete old_value ;
    }   
    /* insert the new value for the particular key */
    os_boolean result = insert( key, value ) ;
    return result ;
}

/******************************************************************************
Member Function: T* remove( const os_string& key )
Class Name     : _ODI_AF_Map<T> 
Purpose        : This function removes the value for the particular key and 
               : returns the value.  
Parameters     : It takes a const reference to key as an argument.
Return Value   : the function returns the value
Remarks        :
******************************************************************************/

template< class T> 
T* _ODI_AF_Map<T>::remove( const os_string& key )
{
    T* value = (T*)0;
    /* check if key is null and if it exists */
    if( ! key.is_null() && exists( key ) )
    {
        value = m_p_impl->remove_value( key ) ;
    }
    return value ;
}

/******************************************************************************
Member Function: void clear()
Class Name     : _ODI_AF_Map<T> 
Purpose        : This function removes all the key value pairs and deletes all
               : the values 
Parameters     : None
Return Value   : void
Remarks        :
******************************************************************************/

template< class T> 
void _ODI_AF_Map<T>::clear()
{
   if( is_empty() ) 
        return  ;
   os_Cursor< T* > del_cur( *m_p_impl ) ;
   for ( T* value = del_cur.first(); value ; value = del_cur.next() )
          delete value ;
   m_p_impl->clear() ;
}

/******************************************************************************
Member Function: T* retrieve( const os_string& key )
Class Name     : _ODI_AF_Map<T> 
Purpose        : This function picks the value for a particular key. 
Parameters     : const reference to key
Return Value   : the function returns the value
Remarks        :
******************************************************************************/

template< class T> 
T* _ODI_AF_Map<T>::retrieve( const os_string& key ) const
{
    T* value = (T*)0 ;
    /* return the value for the particular key */ 
	if( ! key.is_null() && !is_empty() )
         value = m_p_impl->pick( key ) ;
    return value ;
}


/******************************************************************************
Member Function: os_string retrieve_key(const _ODI_AF_Map_iterator& itr ) const
Class Name     : _ODI_AF_Map<T> 
Purpose        : This function picks the key for a particular cursor location. 
Parameters     : const reference to _ODI_AF_Map_iterator
Return Value   : the function returns the key
Remarks        :
******************************************************************************/

template< class T> 
const os_string* _ODI_AF_Map<T>::retrieve_key( const _ODI_AF_Map_iterator<T>& itr ) const
{
    const os_string* key = ( os_string* )0 ;
    if ( !itr.m_p_impl->null() )
        key = m_p_impl->retrieve_key( *itr.m_p_impl ) ;
    return key ;
}

/******************************************************************************
Member Function: os_boolean exists( const os_string& key )
Class Name     : _ODI_AF_Map<T> 
Purpose        : This function checks if the key already exists
Parameters     : const reference to os_string   
Return Value   : true if the key already exists and false if it doesn't
Remarks        :
******************************************************************************/

template< class T> 
os_boolean _ODI_AF_Map<T>::exists( const os_string& key ) const
{
    os_boolean result ;
    /* returns the number of entries with this key */
    if( key.is_null() )
        result = 0;
    else
    {
        T* value = retrieve( key ) ;
        result = ( value !=0 );
    }
    return result ;
}

/******************************************************************************
Member Function: os_boolean is_empty()
Class Name     : _ODI_AF_Map<T> 
Purpose        : This function checks if the map does not contain any key value
               : pair.  
Parameters     : None
Return Value   : true if the map is empty and false if the map is not empty
Remarks        :
******************************************************************************/

template< class T> 
os_boolean _ODI_AF_Map<T>::is_empty() const
{
    os_int32 result = m_p_impl->empty() ;
    return ( result != 0 );
}

template< class T> 
void _ODI_AF_Map<T>::test_clear()
{
   if( is_empty() ) 
        return  ;
   m_p_impl->clear() ;
}

#endif /* _OS_AF_MAP_HH */
