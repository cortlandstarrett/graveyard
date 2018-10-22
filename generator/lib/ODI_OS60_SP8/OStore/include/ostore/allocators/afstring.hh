/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef __OS_STRING__
#define __OS_STRING__

#include <ostore/portypes.hh>
#include <ostore/ostore.hh>

/******************************************************************************
Class Name       : os_string  
Description      : This is a string class with basic string operations. This 
		 : includes string assignment and string comparison. 
Remarks          :
******************************************************************************/

extern const char* os_null_string ; 

class _OS_DLLIMPORT(_OS_ALLOC) os_string
{

public:

	/* constructors and destructor */
	os_string() ;
	os_string( const char* ch ) ;
	/* copy constructor */
	os_string( const os_string& str ) ;
	~os_string() ;

	/* operators */
	/* typecast operator for const char* */
	operator const char*() const;
	/* assignment operator */
	os_string& operator=( const os_string& str ) ;
	
	/* static functions */
	/* creation persistently - will be implemented later */
	/* static os_string& create( os_database* db ) ;
	static os_string& create( os_segment* seg ) ;
	static os_string& create( os_object_cluster& cls ) ;
	destroy the persistent object- will be implemented later 
	static void destroy( os_string& str1 ) ; */
	void destroy( ) { }; 
	static os_typespec* get_os_typespec() ;

	/* member functions */
	os_int16 compare( const os_string& str ) const;
	/* case insensitive comparison */
	os_int16 compare_nocase( const os_string& str ) const;	
	/* check for empty string */
        os_boolean is_null() const ;

	/* friend comparison operators */
	friend os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator==( const os_string& str_left, const os_string& str_right ) ;

	/* overloaded == for const char* */

	friend os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator==( const char* ch_str_left, const os_string& str_right ) ;
   

	friend os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator==( const os_string& str_left, const char* ch_str_right ) ;
	

	friend os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator!=( const os_string& str_left, const os_string& str_right ) ;


	friend os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator!=( const char* ch_str_left, const os_string& str_right ) ;

	friend os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator!=( const os_string& str_left, const char* ch_str_right ) ;

private:
	char* m_p_impl ;

} ; 

/* global comparison operators */

os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator==( const os_string& str_left, const os_string& str_right );
os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator==( const char* ch_str_left, const os_string& str_right ) ;
os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator==( const os_string& str_left, const char* ch_str_right ) ;
os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator!=( const os_string& str_left, const os_string& str_right );
os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator!=( const char* ch_str_left, const os_string& str_right );
os_boolean _OS_DLLIMPORT(_OS_ALLOC) operator!=( const os_string& str_left, const char* ch_str_right );

    
/* rank and hash functions */

os_int32 _OS_DLLIMPORT(_OS_ALLOC)  string_rank( const void* p_left_str, const void* p_right_str ) ;

os_unsigned_int32 _OS_DLLIMPORT(_OS_ALLOC) string_hash( const void* p_i_str ) ;


#endif
