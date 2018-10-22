/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


/******************************************************************************
FileName      : aftrtype.hh
Purpose       : to create traits
Contents      : declaration of os_Trait_<type> classes
Environment   : VC++5.0
Last Delta on : 
Revisions     : 
******************************************************************************/

#ifndef __OS_TRAIT_TYPE__
#define __OS_TRAIT_TYPE__

#include <ostore/portypes.hh>
#include <ostore/ostore.hh>
#include <ctype.h> 
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <ostore/allocators/afstring.hh>


/******************************************************************************
Class Name      : os_Trait_char  
Description     : 
Remarks         : 
******************************************************************************/
#define TS_CHAR "CHAR"

class os_Trait_char
{
    public :

    typedef char        value_type ;
    typedef char*       value_type_ptr ;
    typedef const char* value_type_const_ptr ;
    typedef const char& value_type_const_ref ;

    /* specialize conversion from string to value_type */
    static value_type from_string( const os_string& value_str )
	{
      
        value_type value = '\0' ;
        if( value_str.is_null() )
            value = '\0' ;
        else
        {
            const char* temp_str  = (const char*) value_str ;
            if( !isascii( temp_str[0] ) )
                value = '\0' ;
            else
                value = temp_str[0] ;
        }
        return value ;
    }

    /* specialize conversion from value_type to string */
    static os_string to_string( value_type_const_ref value )
	{
        char buffer[2];
        sprintf(buffer, "%c", value);
        return os_string(( const char*)&buffer) ;
    }

    /* get the null representation of the value_type */
    static value_type get_null() 
    {
       return '\0' ;    
    }
        
    /* get a unique string for os_boolean */
    static os_string get_type_string()
	{
		return os_string(TS_CHAR) ;
	}
} ;

/******************************************************************************
Class Name      : os_Trait_unsigned_int8
Description     : 
Remarks         : 
******************************************************************************/
#define TS_UNSIGNED_INT8 "UNSIGNED_INT8"

class os_Trait_unsigned_int8
{
    public :

    typedef os_unsigned_int8        value_type ;
    typedef os_unsigned_int8*       value_type_ptr ;
    typedef const os_unsigned_int8* value_type_const_ptr ;
    typedef const os_unsigned_int8& value_type_const_ref ;

    /* specialize conversion from string to value_type */
    static value_type from_string( const os_string& value_str )
	{
        long value = 0 ;
        if( value_str.is_null() )
            value = 0 ;
        else if( value_str.compare_nocase("no") == 0 || 
                 value_str.compare_nocase("false") == 0 )
            value = 0;
        else if( value_str.compare_nocase("yes") == 0 || 
                 value_str.compare_nocase("true") == 0 )
            value = 1 ;
        else
        {
            value = atol( value_str ) ;
            if ( value < 0 || value > 255 )
                value = 0 ;
        }
        return (value_type)value ;
     }

    /* specialize conversion from value_type to string */
    /* int8 ranges from  */ 
    static os_string to_string( value_type_const_ref value )
	{
        char buffer[4];
        sprintf(buffer, "%u", value);
        return os_string( (const char*) &buffer ) ;
	}

    /* get the null representation of the value_type */
    static value_type get_null() 
    {
       return 0 ;    
    }

    
    /* get a unique string for os_boolean */
    static os_string get_type_string()
	{
		return os_string(TS_UNSIGNED_INT8) ;
	}
} ;

/******************************************************************************
Class Name      : os_Trait_unsigned_int16
Description     : 
Remarks         : 
******************************************************************************/

#define TS_UNSIGNED_INT16 "UNSIGNED_INT16"

class os_Trait_unsigned_int16
{
    public :

    typedef os_unsigned_int16        value_type ;
    typedef os_unsigned_int16*       value_type_ptr ;
    typedef const os_unsigned_int16* value_type_const_ptr ;
    typedef const os_unsigned_int16& value_type_const_ref ;

    /* specialize conversion from string to value_type */
    static value_type from_string( const os_string& value_str )
	{
        long value = 0 ;
        if( value_str.is_null() )
            value = 0 ;
        else if( value_str.compare_nocase("no") == 0 || 
                 value_str.compare_nocase("false") == 0 )
            value = 0;
        else if( value_str.compare_nocase("yes") == 0 || 
                 value_str.compare_nocase("true") == 0 )
            value = 1 ;
        else
        {
            value = atol( value_str ) ;
            if ( value < -32768 || value > 32767 )
                value = 0 ;
        }
        return (value_type)value ;
    }

    /* specialize conversion from value_type to string */
    static os_string to_string( value_type_const_ref value )
	{
        char buffer[6];
        sprintf(buffer, "%u", value);
        return os_string( (const char*)&buffer) ;
	}

    /* get the null representation of the value_type */
    static value_type get_null() 
    {
       return 0 ;    
    }

    
    /* get a unique string for os_unsigned_int16 */
    static os_string get_type_string()
	{
		return os_string(TS_UNSIGNED_INT16) ;
	}
} ;
/******************************************************************************
Class Name      : os_Trait_int16  
Description     : 
Remarks         : 
******************************************************************************/

#define TS_INT16 "INT16"

class os_Trait_int16
{
    public :

    typedef os_int16        value_type ;
    typedef os_int16*       value_type_ptr ;
    typedef const os_int16* value_type_const_ptr ;
    typedef const os_int16& value_type_const_ref ;

    /* specialize conversion from string to value_type */
    static value_type from_string( const os_string& value_str )
	{
        long value  = 0 ;
        if( value_str.is_null() )
            value = 0 ;
        else if( value_str.compare_nocase("no") == 0 || 
                 value_str.compare_nocase("false") == 0 )
            value = 0;
        else if( value_str.compare_nocase("yes") == 0 || 
                 value_str.compare_nocase("true") == 0 )
            value = 1 ;
        else
        {
            value = atol( value_str ) ;
            if ( value < -32768 || value > 32767  )
                value = 0 ;
        }
        return (value_type)value ;
    }

    /* specialize conversion from value_type to string */
    static os_string to_string( value_type_const_ref value )
	{
        char buffer[7];
        os_string str_value ;
        sprintf(buffer, "%d", value);
        return os_string( (const char*)&buffer) ;
	}

    /* get the null representation of the value_type */
    static value_type get_null() 
    {
       return 0 ;
    }

    
    /* get a unique string for os_int16 */
    static os_string get_type_string()
	{
		return os_string(TS_INT16) ;
	}
} ;

/******************************************************************************
Class Name      : os_Trait_unsigned_int32  
Description     : 
Remarks         : 
******************************************************************************/

#define TS_UNSIGNED_INT32 "UNSIGNED_INT32"

class os_Trait_unsigned_int32
{
    public :

    typedef os_unsigned_int32        value_type ;
    typedef os_unsigned_int32*       value_type_ptr ;
    typedef const os_unsigned_int32* value_type_const_ptr ;
    typedef const os_unsigned_int32& value_type_const_ref ;

    /* specialize conversion from string to value_type */
    static value_type from_string( const os_string& value_str )
	{
        /* overflow not handled */
        unsigned long value = 0 ;
        if( value_str.is_null() )
            value = 0 ;
        else if( value_str.compare_nocase("no") == 0 || 
                 value_str.compare_nocase("false") == 0 )
            value = 0;
        else if( value_str.compare_nocase("yes") == 0 || 
                 value_str.compare_nocase("true") == 0 )
            value = 1 ;
        else
        {
            value = strtoul( value_str, 0, 10 ) ;
            if ( errno == ERANGE)
                value = 0 ;
        }
        return (value_type)value ;
    }

    /* specialize conversion from value_type to string */
    static os_string to_string( value_type_const_ref value )
	{
        char buffer[11];
        sprintf(buffer, "%u", value);
        return os_string((const char*)&buffer ) ;
	}

    /* get the null representation of the value_type */
    static value_type get_null() 
    {
       return 0 ;    
    }

    
    /* get a unique string for os_unsigned_int32 */
    static os_string get_type_string()
	{
		return os_string(TS_UNSIGNED_INT32) ;
	}
} ;

/******************************************************************************
Class Name      : os_Trait_int32  
Description     : 
Remarks         : 
******************************************************************************/

#define TS_INT32 "INT32"

class os_Trait_int32
{
    public :

    typedef os_int32        value_type ;
    typedef os_int32*       value_type_ptr ;
    typedef const os_int32* value_type_const_ptr ;
    typedef const os_int32& value_type_const_ref ;

    /* specialize conversion from string to value_type */
    static value_type from_string( const os_string& value_str )
	{
	    /* overflow not handled */
		long value = 0 ;
        if( value_str.is_null() ) 
            value = 0 ;
        else if( value_str.compare_nocase("no") == 0 || 
                 value_str.compare_nocase("false") == 0 )
            value = 0;
        else if( value_str.compare_nocase("yes") == 0 || 
                 value_str.compare_nocase("true") == 0 )
            value = 1 ;
        else 
        {
            value = strtol( value_str, 0, 10 ) ;
            if ( value < -2147483647 || value > 2147483647 )
                value = 0 ;
          
        }
        return (value_type)value ;
     }

    /* specialize conversion from value_type to string */
    static os_string to_string( value_type_const_ref value )
	{
        char buffer[12];
        sprintf(buffer, "%d", value);
        return os_string( (const char*)&buffer) ;
	}

    /* get the null representation of the value_type */
    static value_type get_null() 
    {
       return 0 ;    
    }
   
        
    /* get a unique string for os_boolean */
    static os_string get_type_string()
	{
		return os_string(TS_INT32) ;
	}
} ;

/******************************************************************************
Class Name      : os_Trait_const_char_pointer  
Description     : 
Remarks         : 
******************************************************************************/

#define TS_CHAR_STRING "CHAR_STRING" 

class os_Trait_const_char_pointer
{
    public :

    typedef const char* value_type ;

    /* specialize conversion from string to value_type */
    static value_type from_string( const os_string& value_str )
	{
        return value_str ;
    }

    /* specialize conversion from value_type to string */
    static os_string to_string( const char* value )
	{
         return os_string( value ) ;     
	}

    /* get the null representation of the value_type */
    static value_type get_null() 
    {
       return (const char*)0 ;    
    }

    
    /* get a unique string for o-s_int16 */
    static os_string get_type_string()
	{
		return os_string(TS_CHAR_STRING) ;
	}
} ;

/******************************************************************************
Class Name      : os_Trait_string  
Description     : 
Remarks         : 
******************************************************************************/

#define TS_OS_STRING "OS_STRING" 

class os_Trait_string
{
    public :

    typedef os_string        value_type ;
    typedef os_string*       value_type_ptr ;
    typedef const os_string* value_type_const_ptr ;
    typedef const os_string& value_type_const_ref ;

    /* specialize conversion from string to value_type */
    static value_type from_string( const os_string& value_str )
	{
        return value_str ;
    }

    /* specialize conversion from value_type to string */
    static os_string to_string( value_type_const_ref value )
	{
        return value ;
	}

    /* get the null representation of the value_type */
    static value_type get_null() 
    {
       return os_string() ;    
    }

    
    /* get a unique string for os_string */
    static os_string get_type_string()
	{
		return os_string(TS_OS_STRING) ;
	}
} ;


#endif
