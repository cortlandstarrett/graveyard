/*========================================================================
 *
 * File:      $RCSfile: u_string.cc,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:42:00 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

// CONTENTS:
//
//	This file contains the implemenation of the String class.
//
// REMARKS:
//
//	It is important to note that this class can be used persistently
//	or transiently; HOWEVER, to do so means we depend upon the
//	Object Store (OS) OODB.
//


#include <iostream.h>
#include <ctype.h>
#include <string.h>

#include "u_typdef.hh"

#include <u_error.hh>
#include "u_trace.hh"

#include "u_string.hh"

// MC_DBMS specific, but needed for persistent/
// transient flexibility/transparency.

#include "u_mc_dbms.hh"
#include "u_tspec.hh"	


#define MIN( a, b ) ( a < b ? a : b )


GS_string GS_string__NULL ("");

char String::temp_during_init[2] = "";

void String::delete_str_ptr( char *p_string_ptr )
{
	if ( p_string_ptr != temp_during_init )
	{
	    operator delete( p_string_ptr, "");	  // Remove from InstanceTracker
		delete [] p_string_ptr;
	}
}

char *String::new_str_ptr( String *p_string_ptr, t_uint p_len )
{
	char * new_char_ptr = temp_during_init;
	if ( MCDBMSInit::ok_to_initialize() )
	{
  		new_char_ptr = new( mc_dbms_segment::of( p_string_ptr), char_type, p_len + 1 )
    	char[ p_len + 1 ];
	}
  	return( new_char_ptr );
}


#ifdef PERFORMANCE_TESTING
long Trans_string_bytes = 0;

static mc_dbms_segment *get_transient_segment()
{
  static mc_dbms_segment *transient_seg = 0;
  if (! transient_seg)
    {
      transient_seg = mc_dbms_segment::get_transient_segment();
    }
  return transient_seg;
}
#endif


//
// FUNCTION(S): String::String()
//
// PURPOSE:
//
//		These are the constructors for creating a new String.
//
// REMARKS:
//
//		For flexibility (and correctness), several different constructors are
//		provided.
//
//		All constructors are coded such that if a user does a persistent
//		new, then they get a persistent String and if they do a transient new
//		they get a transient String.
//

String::String()
{

len = 0;
str_ptr = new_str_ptr( this, len );
str_ptr[0] = '\0';

#ifdef PERFORMANCE_TESTING
mc_dbms_segment *seg = mc_dbms_segment::of( this );

if ( seg == get_transient_segment() )
	{
	Trans_string_bytes += 1;
	LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
		( L_log_string, "String::String()...Trans_string_bytes = %d", Trans_string_bytes ) );
	}
#endif

}


String::String( t_uint p_len )
{

str_ptr = new_str_ptr( this, p_len );
str_ptr[0] = '\0';
len = p_len;

#ifdef PERFORMANCE_TESTING
mc_dbms_segment *seg = mc_dbms_segment::of( this );

if ( seg == get_transient_segment() )
	{
	Trans_string_bytes += len + 1;
	LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
		( L_log_string, "String::String()...Trans_string_bytes = %d", Trans_string_bytes ) );
	}
#endif

}

String::String( const char *p_str_ptr )
{

if ( p_str_ptr == 0 )
	{
	len = 0;
	str_ptr = new_str_ptr( this, len );
	str_ptr[0] = '\0';
	}
else
	{
	len = strlen( p_str_ptr );
	str_ptr = new_str_ptr( this, len );
	strcpy( str_ptr, p_str_ptr );
	}

#ifdef PERFORMANCE_TESTING
mc_dbms_segment *seg = mc_dbms_segment::of( this );

if ( seg == get_transient_segment() )
	{
	Trans_string_bytes += len + 1;
	LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
		( L_log_string, "String::String()...Trans_string_bytes = %d", Trans_string_bytes ) );
	}
#endif

}

String::String( const String& p_string )
{

len = p_string.len;
str_ptr = new_str_ptr( this, len );
strcpy( str_ptr, p_string.str_ptr );

#ifdef PERFORMANCE_TESTING
mc_dbms_segment *seg = mc_dbms_segment::of( this );

if ( seg == get_transient_segment() )
	{
	Trans_string_bytes += len + 1;
	LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
		( L_log_string, "String::String()...Trans_string_bytes = %d", Trans_string_bytes ) );
	}
#endif

}

String::~String()
{

	delete_str_ptr( str_ptr );


#ifdef PERFORMANCE_TESTING
if ( mc_dbms_segment::of( this ) == get_transient_segment() )
	{
	Trans_string_bytes -= len + 1;
	LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
		( L_log_string, "String::~String()...Trans_string_bytes = %d", Trans_string_bytes ) );
	}
#endif

}


//
// FUNCTION(S): String::operator=
//
// PURPOSE:
//
//		Assignment operator for assigning one String or character string to
//		another.
//
// REMARKS:
//
//		None.
//

String&
String::operator=( const String& p_string )
{

// If we are assigning a string to itself, then we don't need to do anything.

if ( this == &p_string )
	{
	return( *this );
	}

delete_str_ptr( str_ptr );

#ifdef PERFORMANCE_TESTING
mc_dbms_segment *seg = mc_dbms_segment::of( this );

if ( seg == get_transient_segment() )
	{
	Trans_string_bytes -= len + 1;
	}
#endif

len = p_string.len;
str_ptr = new_str_ptr( this, len );
strcpy( str_ptr, p_string.str_ptr );

#ifdef PERFORMANCE_TESTING
if ( seg == get_transient_segment() )
	{
	Trans_string_bytes += len + 1;
	LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
		( L_log_string, "String::=...Trans_string_bytes = %d", Trans_string_bytes ) );
	}
#endif

return( *this );

}

String&
String::operator=( const char *p_str_ptr )
{

#ifdef PERFORMANCE_TESTING
mc_dbms_segment *seg = mc_dbms_segment::of( this );

if ( seg == get_transient_segment() )
	{
	Trans_string_bytes -= len + 1;
	}
#endif

char * old_str_ptr = str_ptr;

if ( p_str_ptr == 0 )
	{
	len = 0;
	str_ptr = new_str_ptr( this, len );
	str_ptr[0] = '\0';
	}
else
	{
	len = strlen( p_str_ptr );
	str_ptr = new_str_ptr( this, len );
	strcpy( str_ptr, p_str_ptr );
	}

delete_str_ptr( old_str_ptr );

#ifdef PERFORMANCE_TESTING
if ( seg == get_transient_segment() )
	{
	Trans_string_bytes += len + 1;
	LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
		( L_log_string, "String::=...Trans_string_bytes = %d", Trans_string_bytes ) );
	}
#endif

return( *this );

}

//
// FUNCTION(S): String::operator==
//
// PURPOSE:
//
//		Overloaded equality operator between Strings and character string.
//
// REMARKS:
//
//		None.
//

t_boolean
String::operator==( const String& p_string ) const
{

if ( strcmp( str_ptr, p_string.str_ptr ) == 0 )
	return( TRUE );
else
	return ( FALSE );

}


t_boolean
String::operator==( const char *p_char_ptr ) const
{
t_boolean rc;

if ( p_char_ptr == 0 )
	{
	if ( strcmp( str_ptr, "" ) == 0 )
		{
		rc =  TRUE;
		}
	else
		{
		rc =  FALSE;
		}
	}
else
	{
	if ( strcmp( str_ptr, p_char_ptr ) == 0 )
		{
		rc =  TRUE;
		}
	else
		{
		rc =  FALSE;
		}
	}

return( rc );

}


//
// FUNCTION(S): String::compare
//
// PURPOSE:
//
//		Provide the same functionality for Strings as "strcmp" does for
//		C character strings.
//
// REMARKS:
//
//		None.
//

int
String::compare( const String& p_string ) const
{

return( strcmp( str_ptr, p_string.str_ptr ) );

}


int
String::compare( const char *p_char_ptr ) const
{

if ( p_char_ptr == 0 )
	{
	return( strcmp( str_ptr, "" ) );
	}
else
	{
	return( strcmp( str_ptr, p_char_ptr ) );
	}

}


//
// FUNCTION(S): String::operator+=
//
// PURPOSE:
//
//		Use "+=" to concatenate a String to a given String object
//		changing the String object.
//
// REMARKS:
//
//		Eg - String s1( "cobble" );
//			 String s2( "stone" );
//			 s1 += s2;		// s1 <--- "cobblestone"
//

String&
String::operator+=( const String& p_string )
{

len += p_string.len;

char *buf_ptr = new_str_ptr( this, len );
strcpy( buf_ptr, str_ptr );
strcat( buf_ptr, p_string.str_ptr );
delete_str_ptr( str_ptr );
str_ptr = buf_ptr;

#ifdef PERFORMANCE_TESTING
mc_dbms_segment *seg = mc_dbms_segment::of( this );

if ( seg == get_transient_segment() )
	{
	Trans_string_bytes += p_string.len;
	LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
		( L_log_string, "String::+=...Trans_string_bytes = %d", Trans_string_bytes ) );
	}
#endif

return *this;

}


String&
String::operator+=( const char *p_str_ptr )
{

if ( p_str_ptr == 0 )
	{
	return( *this );
	}

int arg_len = strlen( p_str_ptr );
len += arg_len;
char *buf_ptr = new_str_ptr( this, len );
strcpy( buf_ptr, str_ptr );
strcat( buf_ptr, p_str_ptr );
delete_str_ptr( str_ptr );
str_ptr = buf_ptr;

#ifdef PERFORMANCE_TESTING
mc_dbms_segment *seg = mc_dbms_segment::of( this );

if ( seg == get_transient_segment() )
	{
	Trans_string_bytes += arg_len;
	LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
		( L_log_string, "String::+=...Trans_string_bytes = %d", Trans_string_bytes ) );
	}
#endif

return *this;

}

//
// FUNCTION(S): String::operator+
//
// PURPOSE:
//
//		Use arithmetic "+" to concatenate two strings together and generating
//		third while leaving the two intact.
//
// REMARKS:
//
//		Eg - String s1( "cobble" );
//			 String s2( "stone" );
//			 String s3 = s1 + s2;	// s3 <--- "cobblestone"
//

String
String::operator+( const String& p_string ) const
{

String result = *this;
result += p_string;		// use previously defined "+=" concatenation
return result;

}

String
String::operator+( const char *p_str_ptr ) const
{

String result = *this;

if ( p_str_ptr != 0 )
	{
	result += p_str_ptr;	// use previously defined "+=" concatenation
	}

return result;

}

String &
String::reset( t_uint p_len )
{

#ifdef PERFORMANCE_TESTING
mc_dbms_segment *seg = mc_dbms_segment::of( this );

if ( seg == get_transient_segment() )
	{
	Trans_string_bytes -= len;
	Trans_string_bytes += p_len;
	LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
		( L_log_string, "String::reset()...Trans_string_bytes = %d", Trans_string_bytes ) );
	}
#endif

char *buf_ptr = new_str_ptr( this, p_len );
buf_ptr[ 0 ] = '\0';
len = p_len;
delete_str_ptr( str_ptr );
str_ptr = buf_ptr;

return *this;

}

void
String::truncate( t_uint p_len )
{
  if (p_len < len)
    {
      str_ptr[p_len] = 0;
      len = p_len;
    }
  // else leave length what it is
}

String
String::parse( const char p_delimiter, t_boolean p_skip_doubles )
{

// First find delimiter or end of string, whichever comes first.
// that if the string contains the delimiter as part of its data, then
// it will be immediately followed by another delimeter. We also want to
// make sure we don't have an empty string.

LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
	( L_log_string, "Entered String::parse()...p_delimiter = %c, p_skip_doubles = %d, len = %d, string = %S",
    vcharFromASCII(p_delimiter),
    p_skip_doubles,
    len,
    vcharScribeASCII(str_ptr) ));

int index = 0;
t_boolean found = FALSE;

while ( ( found == FALSE ) && ( str_ptr[ index ] != '\0' ) && ( index < len ) )
{
	if ( str_ptr[ index ] == p_delimiter )
	{
		if ( ( str_ptr[ index + 1 ] != '\0' ) && ( ( index + 1 ) < len ) )
		{
			if ( str_ptr[ index + 1 ] == p_delimiter )
			{
				if ( p_skip_doubles )
				{
					index++;
					index++;
				}
				else
				{
					found = TRUE;
				}
			}
			else
			{
				found = TRUE;
			}
		}
		else
		{
			found = TRUE;
		}
	}
	else
	{
		index++;
	}
}

// If we found delimiter, create new token String up to it and delete the
// token from "this" String. If we did not find the delimiter, then we
// must be at the end of the String which means the entire String is the
// token to be returned; in this case, don't forget to make "this" String
// a null one. Note that at this point, index either points at the delimiter
// or at the null terminating character.

String token;	// token to be returned

if ( found == FALSE )
	{
	token = *this;

	// "this" String now becomes empty

	delete_str_ptr( str_ptr );
	str_ptr = new_str_ptr( this, 1 );
	str_ptr[ 0 ] = '\0';
	len = 0;
	}
else
	{
	token.copy_n( str_ptr, index );		// index is also number to copy

	// We must remove token from beginning of this String, including delimiter.

	String new_string = &str_ptr[ index + 1 ];
	*this = new_string;
	}

LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_END,
	( L_log_string, "Exitted String::parse()...found = %d, len = %d, token = %S", found, len, vcharScribeASCII(token.char_ptr()) ));

return( token );

}


int
String::delimit_character( const char p_delimiter, const char p_character )
{

LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
	( L_log_string, "Entered String::delimit_character()...p_delimiter = %c, p_character = %c, len = %d, string = %S",
    vcharFromASCII(p_delimiter),
    vcharFromASCII(p_character),
    len,
    vcharScribeASCII(str_ptr) ));

// First find out how many p_characters we need to delimit.

for ( int index = 0, count = 0;
	  ( str_ptr[ index ] != '\0' ) && ( index < len );
	  index++ )
	{
	if ( str_ptr[ index ] == p_character )
		{
		count++;
		}
	}


// Create new String by simply looping thru and inserting the delimiter in
// front of each p_character.

if ( count != 0 )
	{
	String new_string( len + count + 1 );

	int old_string_pos = 0;
	int new_string_pos = 0;

    while ( str_ptr[ old_string_pos ] != '\0' )
		{
		if ( str_ptr[ old_string_pos ] == p_character )
			{
			new_string.str_ptr[ new_string_pos++ ] = p_delimiter;
			new_string.str_ptr[ new_string_pos++ ] =
              str_ptr[ old_string_pos++ ];
			}
		else
			{
			new_string.str_ptr[ new_string_pos++ ] =
              str_ptr[ old_string_pos++ ];
			}
		}

	new_string.str_ptr[ new_string_pos ] = '\0';

	*this = new_string;
	}

LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_END,
	( L_log_string, "Exitted String::delimit_character()...count = %d, len = %d, string = %S",
    count, 
    len,
    vcharScribeASCII(str_ptr) ));

return( count );

}


int
String::pare_character( const char p_delimiter, const char p_character )
{

LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
	( L_log_string, "Entered String::pare_character()...p_delimiter = %c, p_character = %c, len = %d, string = %s",
    vcharFromASCII(p_delimiter),
    vcharFromASCII(p_character),
    len,
    vcharScribeASCII(str_ptr) ));

// First find out how many p_delimiters we need to eliminate.

int index = 0;
int count = 0;

while ( str_ptr[ index ] != '\0' )
	{
	if ( ( str_ptr[ index++ ] == p_delimiter ) &&
		 ( str_ptr[ index ] == p_character ) )
			{
			count++;
			index++;
			}
	}


// Create new String by simply looping thru and eliminating the p_delimiter in
// each p_delimiter/p_character pair.

if ( count != 0 )
	{
	String new_string( len - count + 1 );

	int old_string_pos = 0;
	int new_string_pos = 0;

    while ( str_ptr[ old_string_pos ] != '\0' )
		{
		if ( str_ptr[ old_string_pos ] == p_delimiter )
			{
			if ( str_ptr[ ++old_string_pos ] == p_character )
				{
				new_string.str_ptr[ new_string_pos++ ] =
                  str_ptr[ old_string_pos++ ];
				count++;
				}
			else
				{
				// copy in delimiter if not followed by p_character
				new_string.str_ptr[ new_string_pos++ ] =
                  str_ptr[ old_string_pos - 1 ];
				}
			}
		else
			{
			new_string.str_ptr[ new_string_pos++ ] =
              str_ptr[ old_string_pos++ ];
			}
		}

	new_string.str_ptr[ new_string_pos ] = '\0';

	*this = new_string;
	}

LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_END,
	( L_log_string, "Exitted String::pare_character()...count = %d, len = %d, string = %S",
    count,
    len,
    vcharScribeASCII(str_ptr) ));

return( count );

}


String&
String::copy_n( const char *p_str_ptr, int n )
{

// If p_str_ptr is shorter than n, then we will use p_str_ptr's length so we
// don't have a bunch of unused null bytes. Note also that if n is negative,
// we will simply create a null string of length 0.

if ( n < 0 )
	{
	n = 0;
	}

int parm_str_len = strlen( p_str_ptr );

len = MIN( n, parm_str_len );
char * old_str_ptr = str_ptr;
str_ptr = new_str_ptr( this, len );
strncpy( str_ptr, p_str_ptr, len );
str_ptr[ len ] = '\0';

delete_str_ptr( old_str_ptr );

return( *this );

}


String&
String::copy_n( const String& p_string, int n )
{

// Treat special case of assigning a substring of ourself.

if ( this == &p_string )
	{
	String tmp_str = p_string;
	copy_n( tmp_str.str_ptr, n );
	}
else
	{
	copy_n( p_string.str_ptr, n );
	}

return( *this );

}


int
String::position_of( const char *p_string ) const
{
int position;

// Use the C function "strstr" to do the real work for us.

char *position_ptr = strstr( str_ptr, p_string );

if ( position_ptr == 0 )
	{
	position = -1;
	}
else
	{
	position = position_ptr - str_ptr;
	}

return( position );

}


int
String::position_of( const String &p_string ) const
{
int position;

// If the p_string parameter is ourself, then of course we match beginning
// at the first position (ie - zeroeth position).

if ( this == &p_string )
	{
	position = 0;
	}
else
	{
	position = position_of( p_string.str_ptr );
	}

return( position );

}

//
// FUNCTION(S): GS_string::GS_string()
//
// PURPOSE:
//
//      These are the constructors for creating a new GS_string.
//
// REMARKS:
//
//      For flexibility (and correctness), several different constructors are
//      provided.
//
//      All constructors are coded such that if a user does a persistent
//      new, then they get a persistent GS_string and if they do a transient
//      new they get a transient GS_string.
//

GS_string::GS_string ():
  m_null_string(0)

{
    m_length = 0;
    m_cursor = 0;
    m_char_ptr = &m_null_string;
    m_char_ptr [0] = '\0';
}


GS_string::GS_string (t_uint p_length):
  m_null_string(0)

{
    m_length = p_length;
    m_cursor = 0;
    m_char_ptr = new char [m_length + 5];
    m_char_ptr [0] = '\0';
}


GS_string::GS_string (const char *p_char_ptr):
  m_null_string(0)

{
    if (p_char_ptr == 0)
    {
        m_length = 0;
        m_cursor = 0;
        m_char_ptr = &m_null_string;
        m_char_ptr [0] = '\0';
    }
    else
    {
        m_length = strlen (p_char_ptr);
        m_cursor = 0;
        m_char_ptr = new char [m_length + 5];
        strcpy (m_char_ptr, p_char_ptr);
    }
}


GS_string::GS_string (const GS_string& p_string):
  m_null_string(0)

{
	m_length = strlen (p_string.m_char_ptr);
	if (m_length != p_string.m_length)
	{
		LOG_ERROR ((L_log_string,
                    "GS_string::GS_string (const GS_string&):  length stored in string does not match actual char array length.\n\tstring was %S\n\tactual string length=%d\n\tlength stored in string=%d",
                    vcharScribeASCII(p_string.char_ptr()),
                    m_length,
                    p_string.m_length));
	}
    m_cursor = 0;
    m_char_ptr = new char [m_length + 5];
    strcpy (m_char_ptr, p_string.m_char_ptr);
}


GS_string::GS_string (const String& p_string):
  m_null_string(0)

{
	m_length = strlen (p_string.char_ptr ());
	if (m_length != p_string.length ())
	{
		LOG_ERROR ((L_log_string,
                    "GS_string::GS_string (const GS_string&):  length stored in string does not match actual char array length.\n\tstring was %S\n\tactual string length=%d\n\tlength stored in string=%d",
                    vcharScribeASCII(p_string.char_ptr()),
                    m_length,
                    p_string.length()));
	}
    m_cursor = 0;
    m_char_ptr = new char [m_length + 5];
    strcpy (m_char_ptr, p_string.char_ptr ());
}


GS_string::~GS_string ()

{
    delete_char_ptr();
}

void GS_string::delete_char_ptr()
{
    if ( m_char_ptr != &m_null_string )
    {
        delete [] m_char_ptr;
    }
}


//
// FUNCTION(S): GS_string::operator=
//
// PURPOSE:
//
//      Assignment operator for assigning one GS_string or character string
//      to another.
//
// REMARKS:
//
//      None.
//

GS_string&
GS_string::operator= (const GS_string& p_string)

{
    if (this == &p_string)
    {
        //  If we are assigning a string to itself, then we don't need to do
        //    copy.
        //
        m_cursor = 0;
    }
    else
    {
        //  Delete what is currently in this string's character array - it is
        //    going to be replaced in the assignment.
        //
        delete_char_ptr();
        
        
        //  Assign the new string to this string.
        //
		m_length = strlen (p_string.m_char_ptr);
		if (m_length != p_string.m_length)
		{
		LOG_ERROR ((L_log_string,
                    "GS_string::GS_string (const GS_string&):  length stored in string does not match actual char array length.\n\tstring was %S\n\tactual string length=%d\n\tlength stored in string=%d",
                    vcharScribeASCII(p_string.m_char_ptr),
                    m_length,
                    p_string.m_length));
		}
        m_cursor = 0;
        m_char_ptr = new char [m_length + 1];
        strcpy (m_char_ptr, p_string.m_char_ptr);
    }
    

    return *this;
}


GS_string&
GS_string::operator= (const char *p_char_ptr)
{
    //  Delete what is currently in this string's character array - it is
    //    going to be replaced in the assignment.
    //
    delete_char_ptr();


    if (p_char_ptr == 0)
    {
        m_length = 0;
        m_cursor = 0;
        m_char_ptr = new char [m_length + 5];
        m_char_ptr [0] = '\0';
    }
    else
    {
        m_length = strlen (p_char_ptr);
        m_cursor = 0;
        m_char_ptr = new char [m_length + 5];
        strcpy (m_char_ptr, p_char_ptr);
    }


    return *this;
}




//
// FUNCTION(S): GS_string::operator==
//
// PURPOSE:
//
//      Overloaded equality operator between GS_strings and character string.
//
// REMARKS:
//
//      None.
//

t_boolean
GS_string::operator< (const GS_string& p_string) const

{
    return (strcmp (m_char_ptr, p_string.m_char_ptr) < 0);
}


t_boolean
GS_string::operator<= (const GS_string& p_string) const

{
    return (strcmp (m_char_ptr, p_string.m_char_ptr) <= 0);
}



t_boolean
GS_string::operator== (const GS_string& p_string) const

{
    if ( m_length != p_string.m_length )
    {
        return FALSE;
    }
    char *p1 = m_char_ptr;
    char *p2 = p_string.m_char_ptr;
    for ( int i = 0; i < m_length; ++i )
    {
        if ( *p1++ != *p2++ )
            return FALSE;
    }
    return TRUE;
}


t_boolean
GS_string::operator!= (const GS_string& p_string) const

{
    if ( m_length != p_string.m_length )
    {
        return TRUE;
    }
    char *p1 = m_char_ptr;
    char *p2 = p_string.m_char_ptr;
    for ( int i = 0; i < m_length; ++i )
    {
        if ( *p1++ != *p2++ )
            return TRUE;
    }
    return FALSE;
//    return (strcmp (m_char_ptr, p_string.m_char_ptr) != 0);
}


t_boolean
GS_string::operator>= (const GS_string& p_string) const

{
    return (strcmp (m_char_ptr, p_string.m_char_ptr) >= 0);
}


t_boolean
GS_string::operator> (const GS_string& p_string) const

{
    return (strcmp (m_char_ptr, p_string.m_char_ptr) > 0);
}


t_boolean
GS_string::operator< (const char *p_char_ptr) const

{
    if (!p_char_ptr)
    {
        return (strcmp (m_char_ptr, "") < 0);
    }


    return (strcmp (m_char_ptr, p_char_ptr) < 0);
}


t_boolean
GS_string::operator<= (const char *p_char_ptr) const

{
    if (!p_char_ptr)
    {
        return (strcmp (m_char_ptr, "") <= 0);
    }


    return (strcmp (m_char_ptr, p_char_ptr) <= 0);
}


t_boolean
GS_string::operator== (const char *p_char_ptr) const

{
    if (!p_char_ptr)
    {
        if ( m_char_ptr[0] == '\0' )
            return TRUE;
        else
            return FALSE;
    }

    if ( m_length != strlen(p_char_ptr) )
    {
        return FALSE;
    }
    char *p1 = m_char_ptr;
    const char *p2 = p_char_ptr;
    for ( int i = 0; i < m_length; ++i )
    {
        if ( *p1++ != *p2++ )
            return FALSE;
    }
    return TRUE;
}


t_boolean
GS_string::operator!= (const char *p_char_ptr) const

{
    if (!p_char_ptr)
    {
        if ( m_char_ptr[0] == '\0' )
            return FALSE;
        else
            return TRUE;
    }

    if ( m_length != strlen(p_char_ptr) )
    {
        return TRUE;
    }
    char *p1 = m_char_ptr;
    const char *p2 = p_char_ptr;
    for ( int i = 0; i < m_length; ++i )
    {
        if ( *p1++ != *p2++ )
            return TRUE;
    }
    return FALSE;
}


t_boolean
GS_string::operator>= (const char *p_char_ptr) const

{
    if (! p_char_ptr)
    {
        return (strcmp (m_char_ptr, "") >= 0);
    }


    return (strcmp (m_char_ptr, p_char_ptr) >= 0);
}


t_boolean
GS_string::operator> (const char *p_char_ptr) const

{
    if (! p_char_ptr)
    {
        return (strcmp (m_char_ptr, "") > 0);
    }


    return (strcmp (m_char_ptr, p_char_ptr) > 0);
}


t_boolean
GS_string::operator== (const char p_char) const

{
    if (m_char_ptr [m_cursor] == p_char)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


t_boolean
GS_string::operator!= (const char p_char) const

{
    if (m_char_ptr [m_cursor] == p_char)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}




//
// FUNCTION(S): GS_string::compare   &   GS_string::compare_n
//
// PURPOSE:
//
//      Provide the same functionality for GS_strings as "strcmp" does for
//      C character strings.
//
// REMARKS:
//
//      None.
//

int
GS_string::compare_n (const GS_string& p_string, t_uint p_n) const

{
    return (strncmp (m_char_ptr, p_string.m_char_ptr, p_n) == 0);
}


int
GS_string::compare_n (const char *p_char_ptr, t_uint p_n) const

{
    if (p_char_ptr == 0)
    {
        return (strncmp (m_char_ptr, "", p_n) == 0);
    }
    else
    {
        return (strncmp (m_char_ptr, p_char_ptr, p_n) == 0);
    }
}


int
GS_string::compare_n (const GS_string& p_string, t_uint p_start_char, t_uint p_n) const

{
    return (strncmp (&(m_char_ptr [p_start_char]), p_string.m_char_ptr, p_n) == 0);
}


int
GS_string::compare_n (const char *p_char_ptr, t_uint p_start_char, t_uint p_n) const

{
    if (p_char_ptr == 0)
    {
        return (strncmp (&(m_char_ptr [p_start_char]), "", p_n) == 0);
    }
    else
    {
        return (strncmp (&(m_char_ptr [p_start_char]), p_char_ptr, p_n) == 0);
    }
}




//
// FUNCTION(S): GS_string::operator+=
//
// PURPOSE:
//
//      Use "+=" to concatenate a GS_string to a given GS_string object
//      changing the GS_string object.
//
// REMARKS:
//
//      Eg - GS_string s1( "cobble" );
//           GS_string s2( "stone" );
//           s1 += s2;      // s1 <--- "cobblestone"
//

GS_string&
GS_string::operator+= (const GS_string& p_string)

{
    m_length = strlen (m_char_ptr) + strlen (p_string.m_char_ptr);
    m_cursor = 0;
    char* buf_ptr = new char [m_length + 5];
    strcpy (buf_ptr, m_char_ptr);
    strcat (buf_ptr, p_string.m_char_ptr);
    delete_char_ptr();
    m_char_ptr = buf_ptr;


    return *this;
}


GS_string&
GS_string::operator+= (const char *p_char_ptr)

{
    if (p_char_ptr == 0)
    {
        m_cursor = 0;
    }
    else
    {
	m_length = strlen (m_char_ptr) + strlen (p_char_ptr);
        m_cursor = 0;
        char* buf_ptr = new char [m_length + 5];
        strcpy (buf_ptr, m_char_ptr);
        strcat (buf_ptr, p_char_ptr);
        delete_char_ptr();
        m_char_ptr = buf_ptr;
    }

    return *this;
}


GS_string&
GS_string::operator+= (const char p_char_to_add)

{
    m_length = strlen (m_char_ptr) + 1;
    char* buf_ptr = new char [m_length + 5];
    strcpy (buf_ptr, m_char_ptr);
    buf_ptr [m_length - 1] = p_char_to_add;
    buf_ptr [m_length] = '\0';
    delete_char_ptr();
    m_char_ptr = buf_ptr;
    
    
    return *this;
}




//
// FUNCTION(S): GS_string::operator+
//
// PURPOSE:
//
//      Use arithmetic "+" to concatenate two strings together and generating
//      third while leaving the two intact.
//
// REMARKS:
//
//      Eg - GS_string s1( "cobble" );
//           GS_string s2( "stone" );
//           GS_string s3 = s1 + s2;   // s3 <--- "cobblestone"
//

GS_string
GS_string::operator+ (const GS_string& p_string) const

{
    GS_string result = *this;
    
    result += p_string;     // use previously defined "+=" concatenation
    
    return result;
}


GS_string
GS_string::operator+ (const char *p_char_ptr) const

{
    GS_string result = *this;

    if ( p_char_ptr != 0 )
    {
        result += p_char_ptr;    // use previously defined "+=" concatenation
    }

    return result;
}


GS_string
GS_string::operator+ (const char p_char) const

{
    GS_string result = *this;

    result += p_char;

    return result;
}




//
//
//

char&
GS_string::operator[] (t_uint p_index)

{
    if (p_index < 0)
    {
	LOG_ERROR ((L_log_string,
	    "GS_string::operator[] (t_uint):  p_index < 0."));
        return m_char_ptr [0];
    }
    else if (p_index > m_length)
    {
      if (m_length)
        {
          LOG_ERROR ((L_log_string,
                      "GS_string::operator[] (t_uint):  p_index > m_length."));
        }
      return m_char_ptr [0];
    }
    
    
    return m_char_ptr [p_index];
}




char
GS_string::curr_char ()

{
  if (m_cursor < 0)
    {
      LOG_ERROR ((L_log_string,
                  "GS_string::curr_char ():  m_cursor < 0."));
        m_cursor = 0;
        return '\0';
    }
  else if (m_cursor > m_length)
    {
      if (m_length)
        {
          LOG_ERROR ((L_log_string,
                      "GS_string::curr_char ():  m_cursor > m_length."));
          m_cursor = m_length;
        }
      return '\0';
    }
  return m_char_ptr [m_cursor];
}



GS_string&
GS_string::operator++ (int)
{
  if (m_cursor < 0)
    {
      LOG_ERROR ((L_log_string,
                  "GS_string::operator++ (int):  m_cursor < 0."));
      m_cursor = 0;
    }
  else if (m_cursor >= m_length)
    {
      if (m_length)
        {
          LOG_ERROR ((L_log_string,
                      "GS_string::operator++ (int):  m_cursor >= m_length."));
        }
      m_cursor = m_length;
    }
  else
    {
      m_cursor += 1;
    }  
  return *this;
}




GS_string&
GS_string::operator-- (int)
{
  if (m_cursor <= 0)
    {
      LOG_ERROR ((L_log_string,
                  "GS_string::operator-- (int):  m_cursor <= 0."));
      m_cursor = 0;
    }
  else if (m_cursor > m_length)
    {
      if (m_length)
        {
          LOG_ERROR ((L_log_string,
                      "GS_string::operator-- (int):  m_cursor > m_length."));
        }
      m_cursor = m_length;
    }
  else
    {
      m_cursor -= 1;
    }
  return *this;
}




t_uint
GS_string::operator+= (t_uint p_increment)

{
  if (m_cursor < 0)
    {
      LOG_ERROR ((L_log_string,
                  "GS_string::operator+= ():  m_cursor < 0."));
      if (p_increment <= m_length)
        {
          m_cursor = p_increment;
        }
      else
        {
          m_cursor = m_length;
        }
    }
  else if (m_cursor + p_increment > m_length)
    {
      if (m_length)
        {
          LOG_ERROR ((L_log_string,
                      "GS_string::operator+= ():  m_cursor + p_increment > m_length."));
        }
      m_cursor = m_length;
    }
  else
    {
      m_cursor += p_increment;
    }
  return m_cursor;
}
  



t_uint
GS_string::reset_cursor (t_uint p_cursor)

{
  if (p_cursor < m_length - 1)
    {
      m_cursor = p_cursor;
    }
  else
    {
      m_cursor = m_length - 1;
    }
  
  return m_cursor;
};



//
//
//

GS_string
GS_string::parse_to_end ()

{
    t_int length = m_length - m_cursor;
    if (length < 0) length = 0;
    
    GS_string result (length);
    
    if (length > 0)
    {    
	    strncpy ((char*) result.char_ptr (), &(m_char_ptr [m_cursor]), length);
    }
    result [length] = '\0';

    
    m_cursor = m_length;
    
    
    return result;
}





GS_string
GS_string::parse_token (int p_parse_modifier) 

{
    //  Remove leading white space.
    //
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);


    //  Use first non-white space character as the first token character.
    //
    t_uint first_char_position = m_cursor;


    //  Search for the next occurance of white space.
    //
    t_boolean done = FALSE;
    while ((! done) && (m_cursor < m_length))
    {
	if (p_parse_modifier & GS_IGNORE_WITHIN_TICKS)
	{
	    if (m_char_ptr [m_cursor] == '\'')
	    {
		//  Have come across a begin ' character - need to find the
		//    end ' character.
		//
		t_boolean end_tick_found = FALSE;
		while ((! end_tick_found) && (m_cursor < m_length))
		{
		    m_cursor++;
		    if (m_char_ptr [m_cursor] == '\'')
		    {
			if (p_parse_modifier
			    & GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS)
			{
			    if (m_char_ptr [m_cursor + 1] == '\'')
			    {
				//  Have come across a repeated ' character -
				//    increment the cursor one additional time
				//    so it is ignored.
				//
				m_cursor++;
			    }
			    else
			    {
				end_tick_found = TRUE;
			    }
			}
			else
			{
			    end_tick_found = TRUE;
			}
		    }
		}
	    }
	}


	if (p_parse_modifier & GS_IGNORE_WITHIN_QUOTES)
	{
	    if (m_char_ptr [m_cursor] == '\"')
	    {
		//  Have come across a begin " character - need to find the
		//    end " character.
		//
		t_boolean end_quote_found = FALSE;
		while ((! end_quote_found) && (m_cursor < m_length))
		{
		    m_cursor++;
		    if (m_char_ptr [m_cursor] == '\"')
		    {
			if (p_parse_modifier
			    & GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)
			{
			    if (m_char_ptr [m_cursor + 1] == '\"')
			    {
				//  Have come across a repeated " character -
				//    increment the cursor one additional time
				//    so it is ignored.
				//
				m_cursor++;
			    }
			    else
			    {
				end_quote_found = TRUE;
			    }
			}
			else
			{
			    end_quote_found = TRUE;
			}
		    }
		}
	    }
	}


	if (isspace (m_char_ptr [m_cursor]))
	{
	    done = TRUE;
	}
	else
	{
	    m_cursor++;
	}
    }
        
        
    //  Build a string with the characters found between the white space.
    //
    t_int length = m_cursor - first_char_position;
    if (length < 0) length = 0;
    
    GS_string result (length);
    if (length > 0)
    {
    	strncpy ((char*) result.char_ptr (), &(m_char_ptr [first_char_position]), length);
    }
    result [length] = '\0';


    return result;
}





GS_string
GS_string::parse_token (char p_char, int p_parse_modifier) 

{
    //  Remove leading white space.
    //
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);


    //  Use first non-white space character as the first token character.
    //
    t_uint first_char_position = m_cursor;


    //  Search for the next occurance of delimeter.
    //
	t_boolean end_tick_found = TRUE;
	t_boolean end_quote_found = TRUE;
    t_boolean done = FALSE;
    while ((! done) && (m_cursor < m_length))
    {
	if (p_parse_modifier & GS_IGNORE_WITHIN_TICKS)
	{
	    if (m_char_ptr [m_cursor] == '\'')
	    {
		//  Have come across a begin ' character - need to find the
		//    end ' character.
		//
		end_tick_found = FALSE;
		while ((! end_tick_found) && (m_cursor < m_length))
		{
		    m_cursor++;
		    if (m_char_ptr [m_cursor] == '\'')
		    {
			if (p_parse_modifier
			    & GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS)
			{
			    if (m_char_ptr [m_cursor + 1] == '\'')
			    {
				//  Have come across a repeated ' character -
				//    increment the cursor one additional time
				//    so it is ignored.
				//
				m_cursor++;
			    }
			    else
			    {
				end_tick_found = TRUE;
			    }
			}
			else
			{
			    end_tick_found = TRUE;
			}
		    }
		}
	    }
	}


	if (p_parse_modifier & GS_IGNORE_WITHIN_QUOTES)
	{
	    if (m_char_ptr [m_cursor] == '\"')
	    {
		//  Have come across a begin " character - need to find the
		//    end " character.
		//
		end_quote_found = FALSE;
		while ((! end_quote_found) && (m_cursor < m_length))
		{
		    m_cursor++;
		    if (m_char_ptr [m_cursor] == '\"')
		    {
			if (p_parse_modifier
			    & GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)
			{
			    if (m_char_ptr [m_cursor + 1] == '\"')
			    {
				//  Have come across a repeated " character -
				//    increment the cursor one additional time
				//    so it is ignored.
				//
				m_cursor++;
			    }
			    else
			    {
				end_quote_found = TRUE;
			    }
			}
			else
			{
			    end_quote_found = TRUE;
			}
		    }
		}
	    }
	}


	if (m_char_ptr [m_cursor] == p_char)
	{
	    done = TRUE;
	}
	else
	{
	    m_cursor++;
	}
    }
        

    // m_cursor is double incremented if we reach end-of line
    // in a quoted or ticked string
    if ( m_cursor > m_length )
    {
        m_cursor = m_length;
    }

    //  Back up to first non-white space character.
    //
    t_int last_char_position = 0;
    if (m_cursor > 0)
    {
	for (last_char_position = m_cursor - 1;
	    ((last_char_position > 0)
		&& (last_char_position > first_char_position)
		&& (isspace (m_char_ptr [last_char_position])));
	    last_char_position--);
    }
    else
    {
	//  We want a 0 length string to result...
	//
	last_char_position = -1;
    }

        
    //  Build a string with the characters found between the white space.
    //
    t_int length = last_char_position - first_char_position + 1;
    if (length < 0) length = 0;
    
    GS_string result (length);
    if (length > 0)
    {
	strncpy ((char*) result.char_ptr (), &(m_char_ptr [first_char_position]), length);
    }
    result [length] = '\0';


    return result;
}





GS_string
GS_string::parse_token
    (const GS_string& p_str, int p_parse_modifier) 

{
    //  Remove leading white space.
    //
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);


    //  Use first non-white space character as the first token character.
    //
    t_uint first_char_position = m_cursor;


    //  Search for the next occurance of word delimeter.
    //
    t_boolean done = FALSE;
    while ((! done) && (m_cursor < m_length))
    {
	if (p_parse_modifier & GS_IGNORE_WITHIN_TICKS)
	{
	    if (m_char_ptr [m_cursor] == '\'')
	    {
		//  Have come across a begin ' character - need to find the
		//    end ' character.
		//
		t_boolean end_tick_found = FALSE;
		while ((! end_tick_found) && (m_cursor < m_length))
		{
		    m_cursor++;
		    if (m_char_ptr [m_cursor] == '\'')
		    {
			if (p_parse_modifier
			    & GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS)
			{
			    if (m_char_ptr [m_cursor + 1] == '\'')
			    {
				//  Have come across a repeated ' character -
				//    increment the cursor one additional time
				//    so it is ignored.
				//
				m_cursor++;
			    }
			    else
			    {
				end_tick_found = TRUE;
			    }
			}
			else
			{
			    end_tick_found = TRUE;
			}
		    }
		}
	    }
	}


	if (p_parse_modifier & GS_IGNORE_WITHIN_QUOTES)
	{
	    if (m_char_ptr [m_cursor] == '\"')
	    {
		//  Have come across a begin " character - need to find the
		//    end " character.
		//
		t_boolean end_quote_found = FALSE;
		while ((! end_quote_found) && (m_cursor < m_length))
		{
		    m_cursor++;
		    if (m_char_ptr [m_cursor] == '\"')
		    {
			if (p_parse_modifier
			    & GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)
			{
			    if (m_char_ptr [m_cursor + 1] == '\"')
			    {
				//  Have come across a repeated " character -
				//    increment the cursor one additional time
				//    so it is ignored.
				//
				m_cursor++;
			    }
			    else
			    {
				end_quote_found = TRUE;
			    }
			}
			else
			{
			    end_quote_found = TRUE;
			}
		    }
		}
	    }
	}


        if (strncmp (&(m_char_ptr [m_cursor]), p_str.char_ptr (),
	    p_str.length ()) == 0)
	{
	    done = TRUE;
	}
	else
	{
	    m_cursor++;
	}
    }


    //  Back up to first non-white space character.
    //
    t_int last_char_position = 0;
    if (m_cursor > 0)
    {
	for (last_char_position = m_cursor - 1;
	    ((last_char_position > 0)
		&& (last_char_position > first_char_position)
		&& (isspace (m_char_ptr [last_char_position])));
	    last_char_position--);
    }
    else
    {
	//  We want a 0 length string to result...
	//
	last_char_position = -1;
    }


    //  Build a string with the characters found between the white space.
    //
    t_int length = last_char_position - first_char_position + 1;
    if (length < 0) length = 0;
    
    GS_string result (length);
    if (length > 0)
    {
        strncpy ((char*) result.char_ptr (), &(m_char_ptr [first_char_position]), length);
    }
    result [length] = '\0';


    return result;
}


GS_string
GS_string::parse_token_leave_ws(char p_char, int p_parse_modifier)

{

    //  Use first non-white space character as the first token character.
    //
    t_uint first_char_position = m_cursor;


    //  Search for the next occurance of delimeter.
    //
    t_boolean done = FALSE;
    while ((! done) && (m_cursor < m_length))
    {
	if (p_parse_modifier & GS_IGNORE_WITHIN_TICKS)
	{
	    if (m_char_ptr [m_cursor] == '\'')
	    {
		//  Have come across a begin ' character - need to find the
		//    end ' character.
		//
		t_boolean end_tick_found = FALSE;
		while ((! end_tick_found) && (m_cursor < m_length))
		{
		    m_cursor++;
		    if (m_char_ptr [m_cursor] == '\'')
		    {
			if (p_parse_modifier
			    & GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS)
			{
			    if (m_char_ptr [m_cursor + 1] == '\'')
			    {
				//  Have come across a repeated ' character -
				//    increment the cursor one additional time
				//    so it is ignored.
				//
				m_cursor++;
			    }
			    else
			    {
				end_tick_found = TRUE;
			    }
			}
			else
			{
			    end_tick_found = TRUE;
			}
		    }
		}
	    }
	}


	if (p_parse_modifier & GS_IGNORE_WITHIN_QUOTES)
	{
	    if (m_char_ptr [m_cursor] == '\"')
	    {
		//  Have come across a begin " character - need to find the
		//    end " character.
		//
		t_boolean end_quote_found = FALSE;
		while ((! end_quote_found) && (m_cursor < m_length))
		{
		    m_cursor++;
		    if (m_char_ptr [m_cursor] == '\"')
		    {
			if (p_parse_modifier
			    & GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)
			{
			    if (m_char_ptr [m_cursor + 1] == '\"')
			    {
				//  Have come across a repeated " character -
				//    increment the cursor one additional time
				//    so it is ignored.
				//
				m_cursor++;
			    }
			    else
			    {
				end_quote_found = TRUE;
			    }
			}
			else
			{
			    end_quote_found = TRUE;
			}
		    }
		}
	    }
	}


	if (m_char_ptr [m_cursor] == p_char)
	{
	    done = TRUE;
	}
	else
	{
	    m_cursor++;
	}
    }
        

    //  Back up to first non-white space character.
    //
    t_int last_char_position = 0;
    if (m_cursor > 0)
    {
	last_char_position = m_cursor - 1;
    }
    else
    {
	//  We want a 0 length string to result...
	//
	last_char_position = -1;
    }

        
    //  Build a string with the characters found between the white space.
    //
    t_int length = last_char_position - first_char_position + 1;
    if (length < 0) length = 0;
    
    GS_string result (length);
    if (length > 0)
    {
	strncpy ((char*) result.char_ptr (), &(m_char_ptr [first_char_position]), length);
    }
    result [length] = '\0';


    return result;
}


GS_string
GS_string::parse_token_leave_ws
    (const GS_string& p_str, int p_parse_modifier) 

{

    //  Use first non-white space character as the first token character.
    //
    t_uint first_char_position = m_cursor;


    //  Search for the next occurance of word delimeter.
    //
    t_boolean done = FALSE;
    while ((! done) && (m_cursor < m_length))
    {
	if (p_parse_modifier & GS_IGNORE_WITHIN_TICKS)
	{
	    if (m_char_ptr [m_cursor] == '\'')
	    {
		//  Have come across a begin ' character - need to find the
		//    end ' character.
		//
		t_boolean end_tick_found = FALSE;
		while ((! end_tick_found) && (m_cursor < m_length))
		{
		    m_cursor++;
		    if (m_char_ptr [m_cursor] == '\'')
		    {
			if (p_parse_modifier
			    & GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS)
			{
			    if (m_char_ptr [m_cursor + 1] == '\'')
			    {
				//  Have come across a repeated ' character -
				//    increment the cursor one additional time
				//    so it is ignored.
				//
				m_cursor++;
			    }
			    else
			    {
				end_tick_found = TRUE;
			    }
			}
			else
			{
			    end_tick_found = TRUE;
			}
		    }
		}
	    }
	}


	if (p_parse_modifier & GS_IGNORE_WITHIN_QUOTES)
	{
	    if (m_char_ptr [m_cursor] == '\"')
	    {
		//  Have come across a begin " character - need to find the
		//    end " character.
		//
		t_boolean end_quote_found = FALSE;
		while ((! end_quote_found) && (m_cursor < m_length))
		{
		    m_cursor++;
		    if (m_char_ptr [m_cursor] == '\"')
		    {
			if (p_parse_modifier
			    & GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES)
			{
			    if (m_char_ptr [m_cursor + 1] == '\"')
			    {
				//  Have come across a repeated " character -
				//    increment the cursor one additional time
				//    so it is ignored.
				//
				m_cursor++;
			    }
			    else
			    {
				end_quote_found = TRUE;
			    }
			}
			else
			{
			    end_quote_found = TRUE;
			}
		    }
		}
	    }
	}


        if (strncmp (&(m_char_ptr [m_cursor]), p_str.char_ptr (),
	    p_str.length ()) == 0)
	{
	    done = TRUE;
	}
	else
	{
	    m_cursor++;
	}
    }


    //  Back up to first non-white space character.
    //
    t_int last_char_position = 0;
    if (m_cursor > 0)
    {
	last_char_position = m_cursor - 1;
    }
    else
    {
	//  We want a 0 length string to result...
	//
	last_char_position = -1;
    }


    //  Build a string with the characters found between the white space.
    //
    t_int length = last_char_position - first_char_position + 1;
    if (length < 0) length = 0;
    
    GS_string result (length);
    if (length > 0)
    {
        strncpy ((char*) result.char_ptr (), &(m_char_ptr [first_char_position]), length);
    }
    result [length] = '\0';


    return result;
}



GS_string
GS_string::parse_to_keyword (const GS_string& p_keyword_str) 

{
    GS_string keyword_str (p_keyword_str);


    //  Remove leading white space.
    //
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);


    //  Use first non-white space character as the first token character.
    //
    t_uint first_char_position = m_cursor;


    //  Search for the next occurance of delimeter.
    //
    t_boolean done = FALSE;
    while ((! done) && (m_cursor < m_length))
    {
	if (m_char_ptr [m_cursor] == '\'')
	{
	    //  Have come across a begin ' character - need to find the
	    //    end ' character.
	    //
	    t_boolean end_tick_found = FALSE;
	    while ((! end_tick_found) && (m_cursor < m_length))
	    {
		m_cursor++;
		if (m_char_ptr [m_cursor] == '\'')
		{
		    if (m_char_ptr [m_cursor + 1] == '\'')
		    {
			//  Have come across a repeated ' character -
			//    increment the cursor one additional time
			//    so it is ignored.
			//
			m_cursor++;
		    }
		    else
		    {
			end_tick_found = TRUE;
		    }
		}
	    }
	}


	if (m_char_ptr [m_cursor] == '\"')
	{
	    //  Have come across a begin " character - need to find the
	    //    end " character.
	    //
	    t_boolean end_quote_found = FALSE;
	    while ((! end_quote_found) && (m_cursor < m_length))
	    {
		m_cursor++;
		if (m_char_ptr [m_cursor] == '\"')
		{
		    if (m_char_ptr [m_cursor + 1] == '\"')
		    {
			//  Have come across a repeated " character -
			//    increment the cursor one additional time
			//    so it is ignored.
			//
			m_cursor++;
		    }
		    else
		    {
			end_quote_found = TRUE;
		    }
		}
	    }
	}


	t_boolean match_found = TRUE;
	for (t_uint ii = 0;
	    (match_found) && ((ii + m_cursor) < m_length)
		&& (ii <= keyword_str.length ());
	    ii++)
	{
	    if ((ii == 0) || (ii == (keyword_str.length () + 1)))
	    {
		//  Keyword must be surrounded by whitespace.
		//
		if (! isspace (m_char_ptr [ii + m_cursor]))
		{
		    match_found = FALSE;
		}
	    }
	    else
	    {
		char str_char
		    = ((m_char_ptr [ii + m_cursor] >= 'a')
			&& (m_char_ptr [ii + m_cursor] <= 'z'))
		    ? (m_char_ptr [ii + m_cursor] - 0x20)
		    : (m_char_ptr [ii + m_cursor]);
		char keyword_char
		    = ((keyword_str [ii - 1] >= 'a')
			&& (keyword_str [ii - 1] <= 'z'))
		    ? (keyword_str [ii - 1] - 0x20)
		    : (keyword_str [ii - 1]);
		if (str_char != keyword_char)
		{
		    match_found = FALSE;
		}
	    }
	}
	if (ii < (keyword_str.length ()))
	{
	    match_found = FALSE;
	}


	if (match_found)
	{
	    //  Make sure to move the cursor over the white space character
	    //    right before the keyword.
	    //
	    done = TRUE;
	    m_cursor++;
	}
	else
	{
	    m_cursor++;
	}
    }
        

    //  Back up to first non-white space character.
    //
    t_int last_char_position = 0;
    if (m_cursor > 0)
    {
	for (last_char_position = m_cursor - 1;
	    ((last_char_position > 0)
		&& (last_char_position > first_char_position)
		&& (isspace (m_char_ptr [last_char_position])));
	    last_char_position--);
    }
    else
    {
	//  We want a 0 length string to result...
	//
	last_char_position = -1;
    }

        
    //  Build a string with the characters found between the white space.
    //
    t_int length = last_char_position - first_char_position + 1;
    if (length < 0) length = 0;
    
    GS_string result (length);
    if (length > 0)
    {
	strncpy ((char*) result.char_ptr (), &(m_char_ptr [first_char_position]), length);
    }
    result [length] = '\0';


    return result;
}





GS_string
GS_string::convert_delimited_string (char p_delimiter,
    e_conversion_modifier p_conversion_modifier)

{
    if (m_char_ptr [0] != p_delimiter)
    {
	LOG_ERROR ((L_log_string,
	    "GS_string::convert_delimited_string ():  called with string which does NOT begin with the delimiter"));
    }


    if (m_char_ptr [m_length - 1] != p_delimiter)
    {
	LOG_ERROR ((L_log_string,
	    "GS_string::convert_delimited_string ():  called with string which does NOT end with the delimiter"));
    }


    GS_string result (m_length);
    t_uint i = 0;


    //  Begin on 2nd character and end on 2nd to last character so the begin
    //    and end delimiters are taken off.
    //
    for (t_uint j = 1;
	j < (m_length - 1);
	j++)
    {
	result [i++] = m_char_ptr [j];
	if (p_conversion_modifier | GS_CHANGE_REPEATED_DELIMITERS_TO_SINGLES)
	{
	    if ((m_char_ptr [j] == p_delimiter)
		&&
		(m_char_ptr [j + 1] == p_delimiter))
	    {
		//  Repeated delimiter has occurred - skip the second delimiter.
		//
		j++;
	    }
	}
    }


    result [i] = '\0';
    result.recalc_length ();


    return result;
}





GS_string
GS_string::parse_token__ticked_str () 

{
    //  Remove leading white space.
    //
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);


    if (m_char_ptr [m_cursor] != '\'')
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1:  GS_string::parse_token__ticked_str (\"\")."));
	return "";
    }


    //  Use first character beyond the tick as the first token character.
    //
    m_cursor++;
    t_uint first_char_position = m_cursor;


    //  Search for the end of the ticked string.
    //
    GS_string result;
    t_boolean done = FALSE;
    while ((! done) && (m_cursor < m_length))
    {
	if (m_char_ptr [m_cursor] == '\'')
	{
	    if (((m_cursor + 1) < m_length)
		&&
		(m_char_ptr [m_cursor + 1] == '\''))
	    {
		result += m_char_ptr [m_cursor];
		m_cursor++;
		m_cursor++;
	    }
	    else
	    {
		done = TRUE;
	    }
	}
	else
	{
	    result += m_char_ptr [m_cursor];
	    m_cursor++;
	}
    }


    if (m_char_ptr [m_cursor] != '\'')
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  GS_string::parse_token__ticked_str (\"\")."));
	return "";
    }


    //  Increment beyond the tick character.
    //
    m_cursor++;


    return result;
}





GS_string
GS_string::parse_token__quoted_str () 

{
    //  Remove leading white space.
    //
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);


    if (m_char_ptr [m_cursor] != '\"')
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1:  GS_string::parse_token__quoted_str (\"\")."));
	return "";
    }


    //  Use first character beyond the quote as the first token character.
    //
    m_cursor++;
    t_uint first_char_position = m_cursor;


    //  Search for the end of the quoted string.
    //
    GS_string result;
    t_boolean done = FALSE;
    while ((! done) && (m_cursor < m_length))
    {
	if (m_char_ptr [m_cursor] == '\"')
	{
	    if (((m_cursor + 1) < m_length)
		&&
		(m_char_ptr [m_cursor + 1] == '\"'))
	    {
		result += m_char_ptr [m_cursor];
		m_cursor++;
		m_cursor++;
	    }
	    else
	    {
		done = TRUE;
	    }
	}
	else
	{
	    result += m_char_ptr [m_cursor];
	    m_cursor++;
	}
    }


    if (m_char_ptr [m_cursor] != '\"')
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  GS_string::parse_token__quoted_str (\"\")."));
	return "";
    }


    //  Increment beyond the quote character.
    //
    m_cursor++;


    return result;
}





GS_string
GS_string::parse_token__parened_str ()

{
    //  Remove leading white space.
    //
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);


    if (m_char_ptr [m_cursor] != '(')
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #1:  GS_string::parse_token__parened_str (\"\")."));
	return "";
    }


    //  Use first character beyond '(' as the first token character.
    //
    m_cursor++;
    t_uint first_char_position = m_cursor;


    //  Search for the end of the parened string.
    //
    t_boolean done = FALSE;
    t_uint paren_depth = 0;
    while ((! done) && (m_cursor < m_length))
    {
	if (m_char_ptr [m_cursor] == '\'')
	{
	    //  Have come across a begin ' character - need to find the
	    //    end ' character.
	    //
	    t_boolean end_tick_found = FALSE;
	    while ((! end_tick_found) && (m_cursor < m_length))
	    {
		m_cursor++;
		if (m_char_ptr [m_cursor] == '\'')
		{
		    if (m_char_ptr [m_cursor + 1] == '\'')
		    {
			//  Have come across a repeated ' character -
			//    increment the cursor one additional time
			//    so it is ignored.
			//
			m_cursor++;
		    }
		    else
		    {
			end_tick_found = TRUE;
		    }
		}
	    }
	    if ((end_tick_found) && (m_char_ptr [m_cursor] == '\''))
	    {
		m_cursor++;
	    }
	}
	else if (m_char_ptr [m_cursor] == '\"')
	{
	    //  Have come across a begin " character - need to find the
	    //    end " character.
	    //
	    t_boolean end_quote_found = FALSE;
	    while ((! end_quote_found) && (m_cursor < m_length))
	    {
		m_cursor++;
		if (m_char_ptr [m_cursor] == '\"')
		{
		    if (m_char_ptr [m_cursor + 1] == '\"')
		    {
			//  Have come across a repeated " character -
			//    increment the cursor one additional time
			//    so it is ignored.
			//
			m_cursor++;
		    }
		    else
		    {
			end_quote_found = TRUE;
		    }
		}
	    }
	    if ((end_quote_found) && (m_char_ptr [m_cursor] == '\"'))
	    {
		m_cursor++;
	    }
	}
	else if (m_char_ptr [m_cursor] == '(')
	{
	    paren_depth++;
	    m_cursor++;
	}
	else if (m_char_ptr [m_cursor] == ')')
	{
	    if (paren_depth > 0)
	    {
		paren_depth--;
		m_cursor++;
	    }
	    else
	    {
		done = TRUE;
	    }
	}
	else
	{
	    m_cursor++;
	}
    }


    if (m_char_ptr [m_cursor] != ')')
    {
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End #2:  GS_string::parse_token__parened_str (\"\")."));
	return "";
    }


    //  Build a string with the characters found between the paren's - do NOT
    //    include the '(' and ')' characters.
    //
    t_int length = m_cursor - first_char_position;
    if (length < 0) length = 0;
    
    GS_string result (length);
    if (length > 0)
    {
        strncpy ((char*) result.char_ptr (),
	    &(m_char_ptr [first_char_position]), length);
    }
    result [length] = '\0';


    //  Increment beyond the quote character.
    //
    m_cursor++;


    return result;
}





GS_string
GS_string::parse_token__lvalue () 

{
    //  Remove leading white space.
    //
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);


    //  Use first non-white space character as the first token character.
    //
    t_uint first_char_position = m_cursor;


    //  Search for the end of the lvalue.
    //
    t_boolean done = FALSE;
    while ((! done) && (m_cursor < m_length))
    {
	if (m_char_ptr [m_cursor] == '\'')
	{
	    //  Have come across a begin ' character - need to find the
	    //    end ' character.
	    //
	    t_boolean end_tick_found = FALSE;
	    while ((! end_tick_found) && (m_cursor < m_length))
	    {
		m_cursor++;
		if (m_char_ptr [m_cursor] == '\'')
		{
		    if (m_char_ptr [m_cursor + 1] == '\'')
		    {
			//  Have come across a repeated ' character -
			//    increment the cursor one additional time
			//    so it is ignored.
			//
			m_cursor++;
		    }
		    else
		    {
			end_tick_found = TRUE;
		    }
		}
	    }
	}


	switch (m_char_ptr [m_cursor])
	{
	case '=':
	    done = TRUE;
	    break;

	default:
	    m_cursor++;
	    break;
	}
    }
        

    //  Back up to first non-white space character.
    //
    t_int last_char_position = 0;
    if (m_cursor > 0)
    {
	for (last_char_position = m_cursor - 1;
	    ((last_char_position > 0)
		&& (last_char_position > first_char_position)
		&& (isspace (m_char_ptr [last_char_position])));
	    last_char_position--);
    }
    else
    {
	//  We want a 0 length string to result...
	//
	last_char_position = -1;
    }

        
    //  Build a string with the characters found between the white space.
    //
    t_int length = last_char_position - first_char_position + 1;
    if (length < 0) length = 0;
    
    GS_string result (length);
    if (length > 0)
    {
	strncpy ((char*) result.char_ptr (),
	    &(m_char_ptr [first_char_position]), length);
    }
    result [length] = '\0';


    return result;
}


GS_string
GS_string::parse_token__rvalue () 

{
    //  Remove leading white space.
    //
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);


    //  Use first non-white space character as the first token character.
    //
    t_uint first_char_position = m_cursor;


    //  Search for the end of the rvalue.
    //
    t_boolean done = FALSE;
    t_boolean first_char = TRUE;
    while ((! done) && (m_cursor < m_length))
    {
	if ((first_char) && (m_char_ptr [m_cursor] == '-'))
	{
	    //  Have come across a negative indicator for a number - move
	    //    the cursor over this '-' sign so that it is not interpreted
	    //    as a subtraction operator...
	    //
	    m_cursor++;
	}
	first_char = FALSE;


	if (m_char_ptr [m_cursor] == '\'')
	{
	    //  Have come across a begin ' character - need to find the
	    //    end ' character.
	    //
	    t_boolean end_tick_found = FALSE;
	    while ((! end_tick_found) && (m_cursor < m_length))
	    {
		m_cursor++;
		if (m_char_ptr [m_cursor] == '\'')
		{
		    if (m_char_ptr [m_cursor + 1] == '\'')
		    {
			//  Have come across a repeated ' character -
			//    increment the cursor one additional time
			//    so it is ignored.
			//
			m_cursor++;
		    }
		    else
		    {
			end_tick_found = TRUE;
		    }
		}
	    }
	}


	if (m_char_ptr [m_cursor] == '\"')
	{
	    //  Have come across a begin " character - need to find the
	    //    end " character.
	    //
	    t_boolean end_quote_found = FALSE;
	    while ((! end_quote_found) && (m_cursor < m_length))
	    {
		m_cursor++;
		if (m_char_ptr [m_cursor] == '\"')
		{
		    if (m_char_ptr [m_cursor + 1] == '\"')
		    {
			//  Have come across a repeated " character -
			//    increment the cursor one additional time
			//    so it is ignored.
			//
			m_cursor++;
		    }
		    else
		    {
			end_quote_found = TRUE;
		    }
		}
	    }
	}


	switch (m_char_ptr [m_cursor])
	{
	case 'A':
	case 'a':
	    //  Make sure "and" is not part of word (eg - "land")
	    //
	    if (((m_char_ptr [m_cursor + 1] == 'N') ||
		 (m_char_ptr [m_cursor + 1] == 'n'))
		 &&
		((m_char_ptr [m_cursor + 2] == 'D') ||
		 (m_char_ptr [m_cursor + 2] == 'd'))
		 &&
		 isspace (m_char_ptr [m_cursor + 3])
		 &&
		 ( ( m_cursor > 0 ) && ( isspace (m_char_ptr [m_cursor - 1]))))
	    {
		done = TRUE;
	    }
	    else
	    {
		m_cursor++;
	    }
	    break;

	case 'O':
	case 'o':
	    //  Make sure "or" is not part of word (eg - "color")
	    //
	    if (((m_char_ptr [m_cursor + 1] == 'R') ||
		(m_char_ptr [m_cursor + 1] == 'r'))
		 &&
		 isspace (m_char_ptr [m_cursor + 2])
		 &&
		 ( ( m_cursor > 0 ) && ( isspace (m_char_ptr [m_cursor - 1]))))
	    {
		done = TRUE;
	    }
	    else
	    {
		m_cursor++;
	    }
	    break;

	case '=':
	case '!':
	    if (m_char_ptr [m_cursor + 1] == '=')
	    {
		done = TRUE;
	    }
	    else
	    {
		m_cursor++;
	    }
	    break;

	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '<':
	case '>':
	case ',':
	case ')':
	case ';':
	case '|':
	case '&':
	    done = TRUE;
	    break;

	default:
	    m_cursor++;
	    break;
	}
    }
        

    //  Back up to first non-white space character.
    //
    t_int last_char_position = 0;
    if (m_cursor > 0)
    {
	for (last_char_position = m_cursor - 1;
	    ((last_char_position > 0)
		&& (last_char_position > first_char_position)
		&& (isspace (m_char_ptr [last_char_position])));
	    last_char_position--);
    }
    else
    {
	//  We want a 0 length string to result...
	//
	last_char_position = -1;
    }

        
    //  Build a string with the characters found between the white space.
    //
    t_int length = last_char_position - first_char_position + 1;
    if (length < 0) length = 0;
    
    GS_string result (length);
    if (length > 0)
    {
	strncpy ((char*) result.char_ptr (),
	    &(m_char_ptr [first_char_position]), length);
    }
    result [length] = '\0';


    return result;
}


GS_string
GS_string::parse_token__unary_op () 

{
    //  Remove leading white space.
    //
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);


    //  Build a temporary string for the operator.
    //
    GS_string tmp_str (20);
    for (int ii = 0;
	(((m_cursor + ii) < m_length) && (ii < 19));
	ii++)
    {
	tmp_str [ii] = m_char_ptr [m_cursor + ii];
    }
    tmp_str [ii] = '\0';
    tmp_str.recalc_length ();
    tmp_str.convert_to_upper_case ();


    //  Test tmp_str against all unary operators - test for NOT last because
    //    other unary operators begin with NOT...
    //
    GS_string result;
    if ((strncmp (tmp_str.m_char_ptr, "EMPTY", 5) == 0)
	&&
	(isspace (tmp_str [5])))
    {
	result = "EMPTY";
        m_cursor += 5;
    }
    else if ((strncmp (tmp_str.m_char_ptr, "NOT_EMPTY", 9) == 0)
	&&
	(isspace (tmp_str [9])))
    {
	result = "NOT_EMPTY";
        m_cursor += 9;
    }
    else if ((strncmp (tmp_str.m_char_ptr, "FIRST", 5) == 0)
	&&
	(isspace (tmp_str [5])))
    {
	result = "FIRST";
        m_cursor += 5;
    }
    else if ((strncmp (tmp_str.m_char_ptr, "NOT_FIRST", 9) == 0)
	&&
	(isspace (tmp_str [9])))
    {
	result = "NOT_FIRST";
        m_cursor += 9;
    }
    else if ((strncmp (tmp_str.m_char_ptr, "LAST", 4) == 0)
	&&
	(isspace (tmp_str [4])))
    {
	result = "LAST";
        m_cursor += 4;
    }
    else if ((strncmp (tmp_str.m_char_ptr, "NOT_LAST", 8) == 0)
	&&
	(isspace (tmp_str [8])))
    {
	result = "NOT_LAST";
        m_cursor += 8;
    }
    else if ((strncmp (tmp_str.m_char_ptr, "CARDINALITY", 11) == 0)
	&&
	(isspace (tmp_str [11])))
    {
	result = "CARDINALITY";
        m_cursor += 11;
    }
    else if ((strncmp (tmp_str.m_char_ptr, "OBJ_KEY_LETTERS", 15) == 0)
	&&
	(isspace (tmp_str [15])))
    {
	result = "OBJ_KEY_LETTERS";
        m_cursor += 15;
    }
    else if ((strncmp (tmp_str.m_char_ptr, "INITIALIZED", 11) == 0)
	&&
	(isspace (tmp_str [11])))
    {
	result = "INITIALIZED";
        m_cursor += 11;
    }
    else if ((strncmp (tmp_str.m_char_ptr, "NOT_INITIALIZED", 15) == 0)
	&&
	(isspace (tmp_str [15])))
    {
	result = "NOT_INITIALIZED";
        m_cursor += 15;
    }
    else if ((strncmp (tmp_str.m_char_ptr, "NOT", 3) == 0)
	&&
	(isspace (tmp_str [3])))
    {
	result = "NOT";
        m_cursor += 3;
    }

        
    return result;
}


GS_string
GS_string::parse_token__binary_op () 

{
    //  Remove leading white space.
    //
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);


    //  Build a temporary string for the operator.
    //
    GS_string tmp_str (20);
    for (int ii = 0;
	(((m_cursor + ii) < m_length) && (ii < 19));
	ii++)
    {
	tmp_str [ii] = m_char_ptr [m_cursor + ii];
    }
    tmp_str [ii] = '\0';
    tmp_str.recalc_length ();
    tmp_str.convert_to_upper_case ();


    //  Test tmp_str against all binary operators.
    //
    GS_string result;


    if (strncmp (tmp_str.m_char_ptr, "AND", 3) == 0)
    {
	result = "AND";
        m_cursor += 3;
    }
    else if (strncmp (tmp_str.m_char_ptr, "OR", 2) == 0)
    {
	result = "OR";
        m_cursor += 2;
    }
    else
    {
	switch (tmp_str [0])
	{
	case '+':
	    result = "+";
	    m_cursor += 1;
	    break;

	case '-':
	    result = "-";
	    m_cursor += 1;
	    break;

	case '*':
	    result = "*";
	    m_cursor += 1;
	    break;

	case '/':
	    result = "/";
	    m_cursor += 1;
	    break;

	case '%':
	    result = "%";
	    m_cursor += 1;
	    break;

	case '|':
	    result = "|";
	    m_cursor += 1;
	    break;

	case '&':
	    result = "&";
	    m_cursor += 1;
	    break;

	case '<':
	    if (tmp_str [1] == '=')
	    {
		result = "<=";
		m_cursor += 2;
	    }
	    else
	    {
		result = "<";
		m_cursor += 1;
	    }
	    break;

	case '=':
	    if (tmp_str [1] == '=')
	    {
		result = "==";
		m_cursor += 2;
	    }
	    break;

	case '!':
	    if (tmp_str [1] == '=')
	    {
		result = "!=";
		m_cursor += 2;
	    }
	    break;

	case '>':
	    if (tmp_str [1] == '=')
	    {
		result = ">=";
		m_cursor += 2;
	    }
	    else
	    {
		result = ">";
		m_cursor += 1;
	    }
	    break;

	default:
	    break;
	}
    }

        
    return result;
}





GS_string
GS_string::parse_token__parameter (const GS_string& p_param_name_str) const

{
    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	"Begin  GS_string::parse_token__parameter (p_param_name_str=\"%S\").",
	vcharScribeASCII(p_param_name_str.char_ptr()) ));


    GS_string param_list_str = m_char_ptr;


    //  Skip over the '(' character if the caller left it on.
    //
    if (param_list_str.curr_char () == '(')
    {
	param_list_str++;
    }


    GS_string param_value_str;
    t_boolean found = FALSE;
    while ((! found) && (param_list_str.cursor () < param_list_str.length ()))
    {
	GS_string keyword_str (param_list_str.parse_token (':'));
	if (param_list_str.curr_char () != ':')
	{
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #1:  GS_string::parse_token__parameter (\"\")."));
	    return "";
	}
	param_list_str++;

	if (keyword_str == p_param_name_str)
	{
	    found = TRUE;
	}

	GS_string param_value_str = param_list_str.parse_token (',', 
	    GS_string::GS_IGNORE_WITHIN_TICKS |
	    GS_string::GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS |
	    GS_string::GS_IGNORE_WITHIN_QUOTES |
	    GS_string::GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES); 

	if (param_list_str.curr_char () == ',')
	{
	    param_list_str++;
	}
    }


    if (param_value_str [0] == '\"')
    {
	//  Remove the quote characters off the begining and end of the
	//    parameter value.
	//
	param_value_str++;
	GS_string unquoted_param_value_str (param_value_str.parse_to_end ());
	if (unquoted_param_value_str [unquoted_param_value_str.length () - 1]
	    != '\"')
	{
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #2:  GS_string::parse_token__parameter (\"\")."));
	    return "";
	}
	unquoted_param_value_str [unquoted_param_value_str.length () - 1]
	    = '\0';
	unquoted_param_value_str.recalc_length ();
	param_value_str = unquoted_param_value_str;
    }
    else if (param_value_str [0] == '\'')
    {
	//  Remove the tick characters off the begining and end of the
	//    parameter value.
	//
	param_value_str++;
	GS_string unticked_param_value_str (param_value_str.parse_to_end ());
	if (unticked_param_value_str [unticked_param_value_str.length () - 1]
	    != '\'')
	{
	    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
		"End #3:  GS_string::parse_token__parameter (\"\")."));
	    return "";
	}
	unticked_param_value_str [unticked_param_value_str.length () - 1]
	    = '\0';
	unticked_param_value_str.recalc_length ();
	param_value_str = unticked_param_value_str;
    }


    LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	"End #4:  GS_string::parse_token__parameter (%S=\"%S\").",
	vcharScribeASCII(p_param_name_str.char_ptr ()),
  vcharScribeASCII(param_value_str.char_ptr ()) ));
    return param_value_str;
}




//
//
//

void
GS_string::consume_white_space ()

{
    for (;
        ((m_cursor < m_length) && (isspace (m_char_ptr [m_cursor])));
        m_cursor++);
}




//
//
//

GS_string&
GS_string::reset (t_uint p_length)

{
    char *buf_ptr = new char [p_length + 1];
    buf_ptr [0] = '\0';
    m_length = p_length;
    m_cursor = 0;
    delete_char_ptr();
    m_char_ptr = buf_ptr;

    return *this;
}




void
GS_string::recalc_length ()

{
    m_length = strlen (m_char_ptr);
}




//
//
//

GS_string&
GS_string::copy_n (const GS_string& p_string, t_uint p_n)
{
    if (this == &p_string)
    {
        // Treat special case of assigning a substring to ourself.
        //
        GS_string tmp_str = p_string;
        delete_char_ptr();
        m_length = (p_string.m_length >= p_n) ? p_n : p_string.m_length;
        m_cursor = 0;
        m_char_ptr = new char [m_length + 5];
        strncpy (m_char_ptr, p_string.m_char_ptr, m_length);
        m_char_ptr [m_length] = '\0';
        return *this;
    }
    else
    {
        delete_char_ptr();
        m_length = (p_string.m_length >= p_n) ? p_n : p_string.m_length;
        m_cursor = 0;
        m_char_ptr = new char [m_length + 5];
        strncpy (m_char_ptr, p_string.m_char_ptr, m_length);
        m_char_ptr [m_length] = '\0';
    }
    

    return *this;
}


GS_string&
GS_string::copy_n (const char *p_char_ptr, t_uint p_n)

{
    if ( p_char_ptr == 0 )
    {
        m_length = 0;
        m_cursor = 0;
        delete_char_ptr();
        m_char_ptr = new char [m_length + 5];
        m_char_ptr [0] = '\0';
    }
    else
    {
        t_uint char_length = strlen (p_char_ptr);
        m_length = (char_length >= p_n) ? p_n : char_length;
        m_cursor = 0;
        delete_char_ptr();
        m_char_ptr = new char [m_length + 5];
        strncpy (m_char_ptr, p_char_ptr, m_length);
        m_char_ptr [m_length] = '\0';
    }
    

    return *this;
}




//
//
//

GS_string&
GS_string::concat_n (const GS_string& p_string, t_uint p_n)
{
    m_length = (m_length + p_string.m_length >= p_n) ? p_n : m_length + p_string.m_length;
    m_cursor = 0;
    char *buf_ptr = new char [m_length + 5];
    strcpy (buf_ptr, m_char_ptr);
    strncat (buf_ptr, p_string.m_char_ptr, p_n);
    buf_ptr [m_length] = '\0';
    delete_char_ptr();
    m_char_ptr = buf_ptr;
    return *this;
}


GS_string&
GS_string::concat_n (const char *p_char_ptr, t_uint p_n)

{
    if ( p_char_ptr != 0 )
    {
        t_uint char_length = strlen (p_char_ptr);
        m_length = (char_length >= p_n) ? m_length + p_n : m_length + char_length;
        m_cursor = 0;
        char *buf_ptr = new char [m_length + 5];
        strcpy (buf_ptr, m_char_ptr);
        strncat (buf_ptr, p_char_ptr, p_n);
        buf_ptr [m_length] = '\0';
        delete_char_ptr();
        m_char_ptr = buf_ptr;
    }
    

    return *this;
}




void
GS_string::convert_to_upper_case ()

{
    int i = m_length - 1;
    while (i >= 0)
    {
	if ((m_char_ptr [i] >= 'a') && (m_char_ptr [i] <= 'z'))
	{  
	    m_char_ptr [i] -= 0x20;
	}
	i--;
    }
}




void
GS_string::convert_to_lower_case ()

{
    int i = m_length - 1;
    while (i >= 0)
    {
	if ((m_char_ptr [i] >= 'A') && (m_char_ptr [i] <= 'Z'))
	{  
	    m_char_ptr [i] += 0x20;
	}
	i--;
    }
}



