/*========================================================================
 *
 * File:      $RCSfile: u_desc.cc,v $
 * Version:   $Revision: 1.12 $
 * Modified:  $Date: 2013/01/10 23:41:59 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include "u_desc.hh"
#include "u_string.hh"
#include "u_trace.hh"
#include "u_error.hh"
#include "u_tspec.hh"	

// Transient statics go here.
//
Description Description::Default = "";
static vchar s_null_string = 0;
vchar * Description::null_string = &s_null_string;
static t_uint save_len = 0;
#define BUFFER_STRETCH 32

static mc_dbms_segment *get_transient_segment()
{
  static mc_dbms_segment *transient_seg = 0;
  if (! transient_seg)
    {
      transient_seg = mc_dbms_segment::get_transient_segment();
    }
  return transient_seg;
}

static vchar *
new_vstr_ptr_stretch( Description *p_string_ptr, t_uint &p_len )
{

  // If allocating memory in the transient segment, get some extra space
  mc_dbms_segment *seg_ptr = mc_dbms_segment::of( p_string_ptr );
  if (seg_ptr == get_transient_segment())
  {
    p_len += BUFFER_STRETCH;
  }
  t_uint t_len = p_len + 1;
  vchar *new_char_ptr = new(seg_ptr, vchar_type, t_len) vchar[t_len];
  return( new_char_ptr );
}

static vchar *
new_vstr_ptr( Description *p_string_ptr, t_uint p_len )
{

  mc_dbms_segment *seg_ptr = mc_dbms_segment::of( p_string_ptr );
  p_len++;     // room for the trailing null
  vchar *new_char_ptr = new(seg_ptr, vchar_type, p_len) vchar[p_len];
  return( new_char_ptr );
}

void Description::delete_vstr_ptr()
{
    if ( text != m_initial_string )
    {
      operator delete(text, "");  // Remove from InstanceTracker
      delete [] text;
    }
}

// Description constructors follow
//
Description::Description()
{
  m_initial_string[0] = 0;
  max_length = INITIAL_STRING_SIZE - 1;
  text = m_initial_string;
  text[0] = 0;
  cur_length = 0;
}

Description::Description( t_uint p_len )
{
  m_initial_string[0] = 0;
  if ( p_len < INITIAL_STRING_SIZE )
  {
    max_length = INITIAL_STRING_SIZE - 1;
    text = m_initial_string;
    text[0] = 0;
  }
  else
  {
    max_length = p_len;
    text = new_vstr_ptr( this, max_length );
    text[0] = 0;
  }
  cur_length = 0;
}

Description::Description( const char *p_char_ptr )
{
  m_initial_string[0] = 0;
  if ( p_char_ptr == 0 )
  {
    max_length = INITIAL_STRING_SIZE - 1;
    text = m_initial_string;
    text[0] = 0;
    cur_length = 0;
  }
  else
  {
	  t_uint p_cur_length = ::strlen( p_char_ptr );
      if ( p_cur_length < INITIAL_STRING_SIZE )
      {
        max_length = INITIAL_STRING_SIZE - 1;
        text = m_initial_string;
      }
      else
      {
        max_length = p_cur_length;
        text = new_vstr_ptr( this, max_length );
      }
      vcharCopyScribed( vcharScribeLiteral ( p_char_ptr ), text  );
      cur_length = p_cur_length;
  }
}

Description::Description( const vchar *p_char_ptr )
{
  m_initial_string[0] = 0;
  if ( p_char_ptr == 0 )
  {
    max_length = INITIAL_STRING_SIZE - 1;
    text = m_initial_string;
    text[0] = 0;
    cur_length = 0;
  }
  else
  {
    t_uint p_cur_length = vcharLength( p_char_ptr );
    if ( p_cur_length < INITIAL_STRING_SIZE )
    {
      max_length = INITIAL_STRING_SIZE - 1;
      text = m_initial_string;
    }
    else
    {
      max_length = p_cur_length;
      text = new_vstr_ptr( this, max_length );
    }
    vcharCopyFast( p_char_ptr, text  );
    cur_length = p_cur_length;
  }
}


Description::Description( const String &p_string )
{
  m_initial_string[0] = 0;
  t_uint p_cur_length = strlen(p_string.char_ptr());
  if (p_cur_length != p_string.length ())
  {
		LOG_ERROR ((L_log_string,
			"Description::Description (const String&):  length stored in string does not match actual char array length."));
		LOG_ERROR ((L_log_string,
			"Description::Description (const String&):  string was %S",
                vcharScribeASCII(p_string.char_ptr()) ));
		LOG_ERROR ((L_log_string,
			"Description::Description (const String&):  actual string length=%d", p_cur_length));
		LOG_ERROR ((L_log_string,
			"Description::Description (const String&):  length stored in string=%d", p_string.length()));
  }
  if ( p_cur_length < INITIAL_STRING_SIZE )
  {
    max_length = INITIAL_STRING_SIZE - 1;
    text = m_initial_string;
  }
  else
  {
    max_length = p_cur_length;
    text = new_vstr_ptr_stretch( this, max_length );
  }
  vcharCopyScribed( vcharScribeASCII ( p_string.char_ptr() ), text  );
  cur_length = p_cur_length;
}

Description::Description( const Description &p_desc )
{
  t_uint p_cur_length = p_desc.length();
  if ( p_cur_length < INITIAL_STRING_SIZE )
  {
    max_length = INITIAL_STRING_SIZE - 1;
    text = m_initial_string;
  }
  else
  {
    max_length = p_cur_length;
    text = new_vstr_ptr( this, max_length );
  }
  vcharCopyFast( p_desc.char_ptr(), text  );
  cur_length = p_cur_length;
}

// Destructor

Description::~Description()
{
  delete_vstr_ptr();
}

void Description::truncate( t_uint position )
{
  if (position <= max_length)
    {
      text[position] = 0;
      cur_length = position;
    }
  // else leave length what it is
}


// Assignment

Description &
Description::operator=( const Description &p_desc )
{
  // If we are assigning a description to itself, then we don't
  // need to do anything.
  if ( this == &p_desc )
	{
	  return( *this );
	}

  t_uint p_cur_length = p_desc.length();
  if (p_cur_length > max_length || p_cur_length == 0)
  {
      delete_vstr_ptr();
      if ( p_cur_length < INITIAL_STRING_SIZE )
      {
        max_length = INITIAL_STRING_SIZE - 1;
        text = m_initial_string;
      }
      else
      {
        max_length = p_cur_length;
        text = new_vstr_ptr_stretch( this, max_length );
      }
  }
  vcharCopyFast( p_desc.char_ptr(), text );
  cur_length = p_cur_length;
  
  return ( *this );
}


Description &
Description::operator=( const String &p_string )
{
  t_uint p_cur_length = strlen(p_string.char_ptr());
  if (p_cur_length != p_string.length ())
  {
		LOG_ERROR ((L_log_string,
			"Description::operator= (const String&):  length stored in string does not match actual char array length."));
		LOG_ERROR ((L_log_string,
			"Description::operator= (const String&):  string was %S",
                vcharScribeASCII(p_string.char_ptr()) ));
		LOG_ERROR ((L_log_string,
			"Description::operator= (const String&):  actual string length=%d", p_cur_length));
		LOG_ERROR ((L_log_string,
			"Description::operator= (const String&):  length stored in string=%d", p_string.length()));
  }
  if (p_cur_length > max_length)
    {
      delete_vstr_ptr();
      max_length = p_cur_length;
      text = new_vstr_ptr_stretch( this, max_length );
    }
  vcharCopyScribed( vcharScribeASCII ( p_string.char_ptr() ), text  );
  cur_length = p_cur_length;

  return ( *this );

}


Description &
Description::operator=( const char *p_char_ptr )
{
  t_uint p_cur_length = 0;
  if ( p_char_ptr )
    p_cur_length = ::strlen( p_char_ptr );
  if (p_cur_length > max_length)
    {
      delete_vstr_ptr();
      max_length = p_cur_length;
      text = new_vstr_ptr( this, max_length );
    }
  vcharCopyScribed( vcharScribeLiteral ( p_char_ptr ), text  );
  cur_length = p_cur_length;

  return ( *this );

}

Description &
Description::operator=( const vchar *p_char_ptr )
{
  t_uint p_cur_length = 0;
  if ( p_char_ptr )
    p_cur_length = vcharLength( p_char_ptr );
  if (p_cur_length > max_length)
    {
      delete_vstr_ptr();
      max_length = p_cur_length;
      text = new_vstr_ptr_stretch( this, max_length );
    }
  vcharCopyFast( p_char_ptr , text  );
  cur_length = p_cur_length;

  return ( *this );
}

Description &
Description::operator+=( const char *p_char_ptr )
{
  if ( p_char_ptr == 0 )
	{
    return ( *this );
  }
  else
	{
	  t_uint p_cur_length = cur_length + ::strlen( p_char_ptr );
    if (p_cur_length > max_length)
      {
        max_length = p_cur_length;
        vchar *new_text = new_vstr_ptr_stretch( this, max_length );
        vcharCopyFast( text, new_text );
        vchar *p = new_text + cur_length;
        vcharCopyScribed( vcharScribeLiteral ( p_char_ptr ), p  );
        delete_vstr_ptr();
        text = new_text;
        cur_length = p_cur_length;
      }
    else
      {
        vchar *p = &text[cur_length];
        vcharCopyScribed( vcharScribeLiteral ( p_char_ptr ), p  );
        cur_length = p_cur_length;
      }
	}

  return ( *this );
}

Description &
Description::operator+=( const vchar *p_char_ptr )
{
  if ( p_char_ptr == 0 )
	{
    return ( *this );
  }
  else
	{
	  t_uint p_cur_length = cur_length + vcharLength( p_char_ptr );
    if (p_cur_length > max_length)
      {
        max_length = p_cur_length;
        vchar *new_text = new_vstr_ptr_stretch( this, max_length );
        vcharCopyFast( text, new_text );
        vchar *p = new_text + cur_length;
        vcharCopyFast( p_char_ptr, p  );
        delete_vstr_ptr();
        text = new_text;
        cur_length = p_cur_length;
      }
    else
      {
        vchar *p = &text[cur_length];
        vcharCopyFast( p_char_ptr, p  );
        cur_length = p_cur_length;
      }
	}

  return ( *this );
}

Description &
Description::operator+=( const Description &p_desc )
{
  t_uint p_cur_length = cur_length + p_desc.length();
  if (p_cur_length > max_length)
    {
      max_length = p_cur_length;
      vchar *new_text = new_vstr_ptr_stretch( this, max_length );
      vcharCopyFast( text, new_text );
      vchar *p = new_text + cur_length;
      vcharCopyFast( p_desc.char_ptr(), p );
      delete_vstr_ptr();
      text = new_text;
      cur_length = p_cur_length;
    }
  else
    {
      vchar *p = &text[cur_length];
      vcharCopyFast( p_desc.char_ptr(), p );
      cur_length = p_cur_length;
    }

  return ( *this );
}

Description &
Description::reset( t_uint p_len )
{
  if (max_length != p_len)
    {
      delete_vstr_ptr();
      max_length = p_len;
      text = new_vstr_ptr( this, max_length);
    }
  text[0] = 0;
  cur_length = 0;

  return ( *this );
}

t_uint Description::length () const
{
	return cur_length; 
}

t_boolean Description::operator== (const Description& p_desc) const
{
    if ( cur_length != p_desc.cur_length )
    {
        return FALSE;
    }
    vchar *p1 = text;
    vchar *p2 = p_desc.text;
    for ( int i = 0; i < cur_length; ++i )
    {
        if ( *p1++ != *p2++ )
            return FALSE;
    }
    return TRUE;
}

t_boolean Description::operator!= (const Description& p_desc) const
{
    if ( cur_length != p_desc.cur_length )
    {
        return TRUE;
    }
    vchar *p1 = text;
    vchar *p2 = p_desc.text;
    for ( int i = 0; i < cur_length; ++i )
    {
        if ( *p1++ != *p2++ )
            return TRUE;
    }
    return FALSE;
}

t_boolean Description::compare_first (const vchar p_char,
                                      t_uint p_cursor) const
{
	return (text[p_cursor] == p_char);
}

int Description::compare_n (const char* p_char_ptr, t_uint p_length) const
{
  int rc = 1;
  if (p_char_ptr == 0)
    {
      rc = vcharCompareBounded(text, vcharGetEmptyString(), p_length);
    }
  else
    {
      vstr* comp_text = vstrCloneScribed( vcharScribeLiteral(p_char_ptr) );
      rc = vcharCompareBounded(text, comp_text, p_length);
      vstrDestroy( comp_text );
    }
  return (rc == 0);
}

int Description::compare( const Description& p_string ) const
{
  return (vcharCompare( text, p_string.text ));
}

void Description::append_char( const vchar p_char )
{
  t_uint p_cur_length = cur_length + 1;
  if (p_cur_length > max_length)
    {
      max_length = p_cur_length;
      vchar *new_text = new_vstr_ptr_stretch( this, max_length );
      vcharCopyFast( text, new_text );
      vchar *p = new_text + cur_length;
      *p++ = p_char;
      *p = 0;
      delete_vstr_ptr();
      text = new_text;
      cur_length = p_cur_length;
    }
  else
    {
      vchar *p = &text[cur_length];
      *p++ = p_char;
      *p = 0;
      cur_length = p_cur_length;
    }
}

void Description::parse( int p_start, 
       const vchar p_delimiter, Description& p_result, t_boolean p_skip_doubles)
{

// First find delimiter or end of string, whichever comes first.
// that if the string contains the delimiter as part of its data, then
// it will be immediately followed by another delimeter. We also want to
// make sure we don't have an empty string.

LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
	( L_log_string, "Entered Description::parse()...p_start = %d, p_delimiter = %d, p_skip_doubles = %d", p_start, (int)p_delimiter, p_skip_doubles ));

int index = p_start;
t_boolean found = FALSE;
t_uint len  = cur_length;

vchar nil = vcharFromASCII('\0');

while ( ( found == FALSE ) && ( text[ index ] != nil ) && ( index < len ) )
{
	if ( text[ index ] == p_delimiter )
	{
		if ( ( text[ index + 1 ] != nil ) && ( ( index + 1 ) < len ) )
		{
			if ( text[ index + 1 ] == p_delimiter )
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

// If we found delimiter, create new token String up to it 
// If we did not find the delimiter, then we
// must be at the end of the String which means the entire String is the
// token to be returned.
// Note that at this point, index either points at the delimiter
// or at the null terminating character.

if ( found )
{
  size_t found_len = index - p_start;
  if ( p_result.max_length < found_len )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = found_len;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }
  vcharCopyBounded( &text[p_start], p_result.text, found_len );
  p_result.truncate(found_len);

}
else
{
    p_result = text;
}

LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_END,
	( L_log_string, "Exitted Description::parse()...found = %d, len = %d", found, (index-p_start) ));

}

int
Description::delimit_character( const vchar p_delimiter,
                                const vchar p_character )
{

  LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
	  ( L_log_string, "Entered Description::delimit_character()...p_delimiter = %d, p_character = %d", (int)p_delimiter, (int)p_character ));

  // First find out how many p_characters we need to delimit.

  int count = 0;
  vchar nil = vcharFromASCII('\0');
  for ( int index = 0;
	    ( text[ index ] != nil ) && ( index < cur_length );
	    index++ )
  {
 	  if ( text[ index ] == p_character )
  	{
	    count++;
    }
  }


  // Create new Description by simply looping thru and 
  // inserting the delimiter in
  // front of each p_character.

  if ( count != 0 )
  {
    t_uint new_length = cur_length + count;
    vchar *new_string = new_vstr_ptr( this, new_length );

  	t_uint old_string_pos = 0;
	  t_uint new_string_pos = 0;

    while ( text[ old_string_pos ] != nil )
	  {
		  if ( text[ old_string_pos ] == p_character )
  		{
	  		new_string[ new_string_pos++ ] = p_delimiter;
		  }
      new_string[ new_string_pos++ ] = text[ old_string_pos++ ];
	  }

  	new_string[ new_string_pos ] = nil;

    delete_vstr_ptr();
    text = new_string;
    
    max_length = new_length;
    cur_length = new_string_pos;
  }

  LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_END,
	  ( L_log_string, "Exitted Description::delimit_character()...count = %d", count ));

  return( count );

}

int
Description::pare_character( const vchar p_delimiter,
                             const vchar p_character )
{
  LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_BEGIN,
	  ( L_log_string, "Entered Description::pare_character()...p_delimiter = %d, p_character = %d", (int)p_delimiter, (int)p_character ));

  int count = 0;
  if ( cur_length != 0 )
  {
    t_uint new_max_length = cur_length;
    vchar *new_text = new_vstr_ptr( this, new_max_length );
    vchar nil = vcharFromASCII('\0');
    vchar match[3] = { p_delimiter, p_character, nil };
    vchar replace[2] = { p_character, nil };
    vcharCopyScribedBounded(
      vcharScribeReplace(text, match, replace), new_text, cur_length + 1);
    t_uint new_cur_length = vcharLength(new_text);
    count = cur_length - new_cur_length;
    delete_vstr_ptr();
    text = new_text;
    cur_length = new_cur_length;
    max_length = new_max_length;
  }  

  LOG_TRACE( L_N_PROJ_NB, L_HI_FUNCTION_END,
	  ( L_log_string, "Exitted Description::pare_character()...count = %d", count ));

  return count;
}

void 
Description::parse_token_leave_ws( const vchar p_char, t_uint& p_cursor, Description& p_result)
{
	Description temp_desc(1);
	temp_desc.text[0] = p_char;
  temp_desc.truncate(1);

	parse_token_leave_ws( temp_desc, p_cursor, p_result );
}

void 
Description::parse_token_leave_ws( const Description& p_str, t_uint& p_cursor, Description& p_result)
{
  //  Use first non-white space character as the first token character.
  //
  t_uint first_char_position = p_cursor;
    
  //  Search for the next occurance of word delimeter.
  //
  t_boolean done = FALSE;

  while ((! done) && (p_cursor < length()))
    {
      if (vcharCompareBounded (&(text [p_cursor]), p_str.char_ptr (),
                               p_str.length ()) == 0)
        {
          done = TRUE;
        }
      else
        {
          p_cursor++;
        }
    }
  //  Back up to first non-white space character.
  //
  t_int last_char_position = 0;
  if (p_cursor > 0)
    {
      last_char_position = p_cursor - 1;
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
  if (length < 0)
    length = 0;
    
  if ( p_result.max_length < length )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = length;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }
  if (length > 0)
    {
      vcharCopyBounded (&(text [first_char_position]), 
                        p_result.text, length);
      p_result.truncate(length);
    }
  else
  {
      p_result = Description::Default;
  }

}

void
Description::convert_to_lower_case ()

{
  vscribe *scribe = vcharScribeToLowerCase( text );
  t_uint new_cur_length = vscribeGetLength(scribe);
  if (new_cur_length > max_length)
    {
      // scribes are not reliable when new/delete is called
      // between scribe creation and deletion, so clone 
      // the scribe into a dynamic string.
      vscribeDestroy(scribe);
      vchar *new_text = new_vstr_ptr( this, new_cur_length );
      vscribe *scribe = vcharScribeToLowerCase( text );
      vcharCopyScribed( scribe, new_text );
     
      delete_vstr_ptr();
      text = new_text;
      cur_length = new_cur_length;
      max_length = new_cur_length;
    }
  else
    {
      vcharCopyScribed( scribe, text );
      cur_length = new_cur_length;
    }
}

void
Description::convert_to_upper_case ()

{
  vscribe *scribe = vcharScribeToUpperCase( text );
  t_uint new_cur_length = vscribeGetLength(scribe);
  if (new_cur_length > max_length)
    {
      // scribes are not reliable when new/delete is called
      // between scribe creation and deletion, so clone 
      // the scribe into a dynamic string.
      vscribeDestroy(scribe);
      vchar *new_text = new_vstr_ptr( this, new_cur_length );
      vscribe *scribe = vcharScribeToUpperCase( text );
      vcharCopyScribed( scribe, new_text );
     
      delete_vstr_ptr();
      text = new_text;
      cur_length = new_cur_length;
      max_length = new_cur_length;
    }
  else
    {
      vcharCopyScribed( scribe, text );
      cur_length = new_cur_length;
    }
}

void
Description::indent_lines(int p_indent_length)

{
  // First find out how many \n we need to delimit.
  int count = 0;
  vchar nil = vcharFromASCII('\0');
  vchar nl = vcharFromASCII('\n');
  for ( t_uint index = 0;
        ( text[ index ] != nil ) && ( index < cur_length );
        index++ )
    {
      if ( text[ index ] == nl )
        count++;
    }

  if (count)
    {
      // After each '\n' in text, insert p_indent_length spaces
      t_uint new_cur_length = cur_length + ( count * p_indent_length );
      vchar *new_text = new_vstr_ptr( this, new_cur_length );

      // match string is newline only
      vchar match[2] = { nl,nil };

      // replace string is newline + p_indent_length spaces
      vchar space = vcharFromASCII(' ');
      vchar *replace = new vchar[p_indent_length + 2];
      replace[0] = nl;
      for (int i=1; i <= p_indent_length; i++)
        replace[i] = space;
      replace[p_indent_length + 1] = nil;

      vcharCopyScribed(vcharScribeReplace(text, match, replace),
                       new_text);
      delete [] replace;
	
      // now put the expanded text in this->text
      delete_vstr_ptr();
      text = new_text;
      cur_length = new_cur_length;
      max_length = new_cur_length;
    }
}

void Description::make_words_capital()
{
	t_boolean begin_new_word = TRUE;
	for (t_uint i = 0; text[i] != '\0';	i++)
	{
		if (vcharIsWhiteSpace (text [i]))
		{
			begin_new_word = TRUE;
		}
		else if (begin_new_word)
		{
			if ((text[i] >= 'a')
				&& (text[i] <= 'z'))
			{  
				text[i] -= 0x20;
			}
			begin_new_word = FALSE;
		}
		else
		{
			if ((text[i] >= 'A')
				&& (text[i] <= 'Z'))
			{  
				text[i] += 0x20;
			}
		}
	}
}

void Description::make_corba_compliant()
{
	t_boolean begin_first_word = TRUE;
	t_boolean begin_subsequent_word = FALSE;
	for (t_uint i = 0; text [i] != '\0'; i++)
	{
		if (! (((text [i] >= 'a')
			&& (text [i] <= 'z'))
			||
			((text [i] >= 'A')
			&& (text [i] <= 'Z'))
			||
			((text [i] >= '0')
			&& (text [i] <= '9'))))
		{
			if (! begin_first_word)
			{
				begin_subsequent_word = TRUE;
			}
		}
		else if (begin_subsequent_word)
		{
			if ((text [i] >= 'a')
				&& (text [i] <= 'z'))
			{  
				text [i] -= 0x20;
			}
			begin_subsequent_word = FALSE;
		}
		else
		{
			begin_first_word = FALSE;
			if ((text [i] >= 'A')
				&& (text [i] <= 'Z'))
			{  
				text [i] += 0x20;
			}
		}
	}
			
			
	Description tmp2_str (text);
	t_uint i2 = 0;
	for (t_uint i3 = 0;	tmp2_str.text [i3] != '\0';	i3++)
	{
		if (((tmp2_str.text [i3] >= 'a')
			&& (tmp2_str.text [i3] <= 'z'))
			||
			((tmp2_str.text [i3] >= 'A')
			&& (tmp2_str.text [i3] <= 'Z'))
			||
			((tmp2_str.text [i3] >= '0')
			&& (tmp2_str.text [i3] <= '9')))
		{
			text [i2++] = tmp2_str.text [i3];
		}
	}
	truncate(i2);
}

void Description::make_spaces_underbars()
{
	for (t_uint i = 0; text [i] != '\0'; i++)
	{
		if (vcharIsWhiteSpace (text [i]) )
		{
			text [i] = vcharFromLiteral('_');
		}
	}
}

void Description::remove_all_white_space()
{
  t_uint i = 0;
	for (t_uint i2 = 0; i2 < cur_length; i2++)
	{
		if (! vcharIsWhiteSpace (text[i2]) )
		{
			text[i++] = text[i2];
		}
	}
  truncate(i);
}

void
Description::parse_to_end (t_uint &p_cursor, Description& p_result) const

{
  t_uint length = 0;
  if (p_cursor < cur_length)
  {
    length = cur_length - p_cursor;
  }
    
  if ( p_result.max_length < length )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = length;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }
    
  if (length > 0)
  {    
      vcharCopyBounded (&text[p_cursor], p_result.text, length);
      p_result.truncate(length);
  }
  else
  {
      p_result = Description::Default;
  }
    
  p_cursor = cur_length;

}

void
Description::parse_token (t_uint &p_cursor, Description& p_result) const

{
	//  Remove leading white space.
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text[p_cursor])));
       p_cursor++)
    ;  // do nothing
  
  //  Use first non-white space character as the first token character.
  t_uint first_char_position = p_cursor;

  //  Search for the next occurance of white space.
  t_boolean done = FALSE;
  while ((! done) && (p_cursor < cur_length))
    {
      if (vcharIsWhiteSpace (text[p_cursor]))
        {
          done = TRUE;
        }
      else
        {
          p_cursor++;
        }
    }
	
        
  //  Build a string with the characters found between the white space.
  t_int length = p_cursor - first_char_position;
  if (length < 0)
    length = 0;
    
  if ( p_result.max_length < length )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = length;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }
  if (length > 0)
    {
    	vcharCopyBounded (&text[first_char_position], p_result.text, length);
      p_result.truncate(length);
    }
  else
  {
      p_result = Description::Default;
  }
}


void
Description::parse_token (char p_char, t_uint &p_cursor, Description& p_result,
                          t_boolean p_ignore_within_ticks,
                          t_boolean p_ignore_within_quotes) const 

{
  //  Remove leading white space.
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text[p_cursor])));
       p_cursor++)
    ;  // do nothing


  vchar l_tick = vcharFromASCII('\'');
  vchar l_quote = vcharFromASCII('"');
  vchar l_char = vcharFromASCII(p_char);

  //  Use first non-white space character as the first token character.
  t_uint first_char_position = p_cursor;

  //  Search for the next occurance of delimeter.
  t_boolean done = FALSE;
  while ((! done) && (p_cursor < cur_length))
    {
      if (p_ignore_within_ticks)
        {
          if (text[p_cursor] == l_tick)
            {
              //  Have come across a begin ' character - need to find the
              //    end ' character.
              //
              t_boolean end_tick_found = FALSE;
              while ((! end_tick_found) && (p_cursor < cur_length))
                {
                  p_cursor++;
                  if (text[p_cursor] == l_tick)
                    {
                      if (text[p_cursor + 1] == l_tick)
                        {
                          //  Have come across a repeated ' character -
                          //    increment the cursor one additional time
                          //    so it is ignored.
                          //
                          p_cursor++;
                        }
                      else
                        {
                          end_tick_found = TRUE;
                        }
                    }
                }
            }
        }
      
      if (p_ignore_within_quotes)
        {
          if (text [p_cursor] == l_quote)
            {
              //  Have come across a begin " character - need to find the
              //    end " character.
              //
              
              t_boolean end_quote_found = FALSE;
              while ((! end_quote_found) && (p_cursor < cur_length))
                {
                  p_cursor++;
                  if (text[p_cursor] == l_quote)
                    {
                      if (text[p_cursor + 1] == l_quote)
                        {
                          //  Have come across a repeated " character -
                          //    increment the cursor one additional time
                          //    so it is ignored.
                          //
                          p_cursor++;
                        }
                      else
                        {
                          end_quote_found = TRUE;
                        }
                    }
                }
            }
        }
      
      if (text[p_cursor] == l_char)
        {
          done = TRUE;
        }
      else
        {
          p_cursor++;
        }
    }
        

  //  Back up to first non-white space character.
  t_int last_char_position = 0;
  if (p_cursor > 0)
    {
      for (last_char_position = p_cursor - 1;
           ((last_char_position > 0)
            && (last_char_position > first_char_position)
            && (vcharIsWhiteSpace (text[last_char_position])));
           last_char_position--)
        ;  // do nothing
    }
  else
    {
      //  We want a 0 length string to result...
      last_char_position = -1;
    }
  
        
  //  Build a string with the characters found between the white space.
  t_int length = last_char_position - first_char_position + 1;
  if (length < 0)
    length = 0;
    
  if ( p_result.max_length < length )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = length;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }
  if (length > 0)
    {
    	vcharCopyBounded (&text[first_char_position], p_result.text, length);
      p_result.truncate(length);
    }
  else
  {
      p_result = Description::Default;
  }

}

void
Description::consume_white_space (t_uint &p_cursor) const

{
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text[p_cursor])));
       p_cursor++)
		;  // do nothing
}



void
Description::parse_token (const Description& p_pattern,
                          t_uint &p_cursor, Description& p_result) const 

{
  //  Remove leading white space.
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text[p_cursor])));
       p_cursor++)
    ;  // do nothing
	
  //  Use first non-white space character as the first token character.
  t_uint first_char_position = p_cursor;

  //  Search for the next occurance of delimeter.
  t_boolean done = FALSE;
  while ((! done) && (p_cursor < cur_length))
    {
      if (vcharCompareBounded(&text[p_cursor],
                              p_pattern.char_ptr(),
                              p_pattern.length()) == 0)
        {
          done = TRUE;
        }
      else
        {
          p_cursor++;
        }
    }

  //  Back up to first non-white space character.
  t_int last_char_position = 0;
  if (p_cursor > 0)
    {
      for (last_char_position = p_cursor - 1;
           ((last_char_position > 0)
            && (last_char_position > first_char_position)
            && (vcharIsWhiteSpace (text[last_char_position])));
           last_char_position--)
        ;  // do nothing
    }
  else
    {
      //  We want a 0 length string to result...
      //
      last_char_position = -1;
    }

  //  Build a string with the characters found between the white space.
  t_int length = last_char_position - first_char_position + 1;
  if (length < 0)
    length = 0;
    
  if ( p_result.max_length < length )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = length;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }
  if (length > 0)
    {
      vcharCopyBounded (&text[first_char_position], p_result.text, length);
      p_result.truncate(length);
    }
  else
  {
      p_result = Description::Default;
  }
	
}

void
Description::parse_token__lvalue (t_uint& p_cursor, Description& p_result) const
{
  //  Remove leading white space.
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text [p_cursor])));
       p_cursor++)
    ;  // do nothing


  //  Use first non-white space character as the first token character.
  t_uint first_char_position = p_cursor;


  //  Search for the end of the lvalue.
  t_boolean done = FALSE;
  while ((! done) && (p_cursor < cur_length))
    {
      if (text [p_cursor] == vcharFromASCII('\''))
        {
          //  Have come across a begin ' character - need to find the
          //    end ' character.
          //
          t_boolean end_tick_found = FALSE;
          while ((! end_tick_found) && (p_cursor < cur_length))
            {
              p_cursor++;
              if (text [p_cursor] == vcharFromASCII('\''))
                {
                  if (text [p_cursor + 1] == vcharFromASCII('\''))
                    {
                      //  Have come across a repeated ' character -
                      //    increment the cursor one additional time
                      //    so it is ignored.
                      //
                      p_cursor++;
                    }
                  else
                    {
                      end_tick_found = TRUE;
                    }
                }
            }
        }

      switch (text [p_cursor])
        {
        case '=':
          done = TRUE;
          break;

        default:
          p_cursor++;
          break;
        }
    }
        

  //  Back up to first non-white space character.
  //
  t_int last_char_position = 0;
  if (p_cursor > 0)
    {
      for (last_char_position = p_cursor - 1;
           ((last_char_position > 0)
            && (last_char_position > first_char_position)
            && (vcharIsWhiteSpace (text [last_char_position])));
           last_char_position--)
        ;  // do nothing
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
  if (length < 0)
    length = 0;
    
  if ( p_result.max_length < length )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = length;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }
  if (length > 0)
    {
      vcharCopyBounded(&(text [first_char_position]), p_result.text, length);
      p_result.truncate(length);
    }
  else
  {
      p_result = Description::Default;
  }

}


void
Description::parse_token__rvalue (t_uint& p_cursor, Description& p_result) const
{
  //  Remove leading white space.
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text [p_cursor])));
       p_cursor++)
    ;  // do nothing

  //  Use first non-white space character as the first token character.
  t_uint first_char_position = p_cursor;

  //  Search for the end of the rvalue.
  t_boolean done = FALSE;
  t_boolean first_char = TRUE;
  while ((! done) && (p_cursor < cur_length))
    {
      if ((first_char) && (text [p_cursor] == '-'))
        {
          //  Have come across a negative indicator for a number - move
          //    the cursor over this '-' sign so that it is not interpreted
          //    as a subtraction operator...
          //
          p_cursor++;
        }
      first_char = FALSE;

      if (text [p_cursor] == vcharFromASCII('\''))
        {
          //  Have come across a begin ' character - need to find the
          //    end ' character.
          //
          t_boolean end_tick_found = FALSE;
          while ((! end_tick_found) && (p_cursor < cur_length))
            {
              p_cursor++;
              if (text [p_cursor] == vcharFromASCII('\''))
                {
                  if (text [p_cursor + 1] == vcharFromASCII('\''))
                    {
                      //  Have come across a repeated ' character -
                      //    increment the cursor one additional time
                      //    so it is ignored.
                      //
                      p_cursor++;
                    }
                  else
                    {
                      end_tick_found = TRUE;
                    }
                }
            }
        }
      
      if (text [p_cursor] == vcharFromASCII('"'))
        {
          //  Have come across a begin " character - need to find the
          //    end " character.
          //
          t_boolean end_quote_found = FALSE;
          while ((! end_quote_found) && (p_cursor < cur_length))
            {
              p_cursor++;
              if (text [p_cursor] == vcharFromASCII('"'))
                {
                  if (text [p_cursor + 1] == vcharFromASCII('"'))
                    {
                      //  Have come across a repeated " character -
                      //    increment the cursor one additional time
                      //    so it is ignored.
                      //
                      p_cursor++;
                    }
                  else
                    {
                      end_quote_found = TRUE;
                    }
                }
            }
        }

      switch (text [p_cursor])
        {
        case 'A':
        case 'a':
          //  Make sure "and" is not part of word (eg - "land")
          //
          if (((text [p_cursor + 1] == 'N') ||
               (text [p_cursor + 1] == 'n'))
              &&
              ((text [p_cursor + 2] == 'D') ||
               (text [p_cursor + 2] == 'd'))
              &&
              vcharIsWhiteSpace (text [p_cursor + 3])
              &&
              ( ( p_cursor > 0 ) 
                && ( vcharIsWhiteSpace (text [p_cursor - 1]))))
            {
              done = TRUE;
            }
          else
            {
              p_cursor++;
            }
          break;
          
        case 'O':
        case 'o':
          //  Make sure "or" is not part of word (eg - "color")
          //
          if (((text [p_cursor + 1] == 'R') ||
               (text [p_cursor + 1] == 'r'))
              &&
              vcharIsWhiteSpace (text [p_cursor + 2])
              &&
              ( ( p_cursor > 0 ) && ( vcharIsWhiteSpace (text [p_cursor - 1]))))
            {
              done = TRUE;
            }
          else
            {
              p_cursor++;
            }
          break;
          
        case '=':
        case '!':
          if (text [p_cursor + 1] == '=')
            {
              done = TRUE;
            }
          else
            {
              p_cursor++;
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
          p_cursor++;
          break;
        }
    }
        

  //  Back up to first non-white space character.
  //
  t_int last_char_position = 0;
  if (p_cursor > 0)
    {
      for (last_char_position = p_cursor - 1;
           ((last_char_position > 0)
            && (last_char_position > first_char_position)
            && (vcharIsWhiteSpace (text [last_char_position])));
           last_char_position--)
        ;  // do nothing
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
  if (length < 0)
    length = 0;
    
  if ( p_result.max_length < length )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = length;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }

  if (length > 0)
    {
      vcharCopyBounded(&(text [first_char_position]), p_result.text, length);
      p_result.truncate(length);
    }
  else
  {
      p_result = Description::Default;
  }

}


void
Description::parse_token__unary_op (t_uint& p_cursor, Description& p_result) const

{
  static const int max_kw_size = 15;
  static Description tmp_str (max_kw_size + 1);

  static const int num_kws = 11;
  static const Description keys[num_kws] = {
    "EMPTY",
    "NOT_EMPTY",
    "FIRST",
    "NOT_FIRST",
    "LAST",
    "NOT_LAST",
    "CARDINALITY",
    "OBJ_KEY_LETTERS",
    "INITIALIZED",
    "NOT_INITIALIZED",
    "NOT"
  };

  //  Remove leading white space.
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text [p_cursor])));
       p_cursor++)
    ;  // do nothing

  //  Build a temporary string for the operator.
  for (int ii = 0;
       (((p_cursor + ii) < cur_length) && (ii < max_kw_size + 1));
       ii++)
    {
      tmp_str.text [ii] = text [p_cursor + ii];
    }
  tmp_str.truncate(ii);
  tmp_str.convert_to_upper_case ();

  // look for keyword
  const Description *result;
  t_boolean found = FALSE;
  register t_uint l;
  for (register int i=0; ((i < num_kws) && (! found)); i++)
    {
      result = &keys[i];
      l = result->cur_length;
      if ((vcharIsWhiteSpace (tmp_str.char_at(l)))
          &&  (vcharCompareBounded(tmp_str.text, result->text, l) == 0))
        {
          p_cursor += l;
          tmp_str.truncate(l);
          found = TRUE;
        }
    }

  if ( ! found )
    tmp_str.truncate(0);

  p_result = tmp_str;
}


void
Description::parse_token__binary_op (t_uint& p_cursor, Description& p_result) const

{
  static const int max_kw_size = 3;
  static Description tmp_str (max_kw_size + 1);

  static const int num_kws = 15;
  static const Description keys[num_kws] = {
    "AND",
    "OR",
    "+",
    "-",
    "*",
    "/",
    "%",
    "|",
    "&",
    "<=",
    "<",
    "==",
    "!=",
    ">=",
    ">"
  };

  //  Remove leading white space.
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text [p_cursor])));
       p_cursor++)
    ;  // do nothing

  //  Build a temporary string for the operator.
  for (int ii = 0;
       (((p_cursor + ii) < cur_length) && (ii < max_kw_size + 1));
       ii++)
    {
      tmp_str.text [ii] = text [p_cursor + ii];
    }
  tmp_str.truncate(ii);
  tmp_str.convert_to_upper_case ();

  // look for keyword
  const Description *result;
  t_boolean found = FALSE;
  register t_uint l;
  for (register int i=0; ((i < num_kws) && (! found)); i++)
    {
      result = &keys[i];
      l = result->cur_length;
      if (vcharCompareBounded(tmp_str.text, result->text, l) == 0)
        {
          p_cursor += l;
          tmp_str.truncate(l);
          found = TRUE;
        }
    }

  if ( ! found )
    tmp_str.truncate(0);
        
  p_result = tmp_str;
}

void
Description::parse_token__quoted_str (t_uint& p_cursor, Description& p_result) const
{
  if ( p_result.max_length < cur_length )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = cur_length;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }

  //  Remove leading white space.
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text [p_cursor])));
       p_cursor++)
		;  // do nothing
	
  if (text [p_cursor] == vcharFromASCII('"'))
    {
      //  Use first character beyond the quote as the first token character.
      p_cursor++;
      t_uint first_char_position = p_cursor;
	
      //  Search for the end of the quoted string.
      t_uint result_cursor = 0;
      t_boolean done = FALSE;
      while ((! done) && (p_cursor < cur_length))
        {
          if (text [p_cursor] == vcharFromASCII('"'))
            {
              if (((p_cursor + 1) < cur_length)
                  &&
                  (text [p_cursor + 1] == vcharFromASCII('"')))
                {
                  p_result.text[result_cursor] = text[p_cursor];
                  result_cursor++;
                  p_cursor++;
                  p_cursor++;
                }
              else
                {
                  done = TRUE;
                }
            }
          else
            {
              p_result.text[result_cursor] = text[p_cursor];
              result_cursor++;
              p_cursor++;
            }
        }
      if (text [p_cursor] != vcharFromASCII('"'))
        {
          // No ending quote. Throw away any gathered text.
          p_result = Description::Default;
        }
      else
        {
          //  Increment beyond the ending quote character.
          p_cursor++;
          p_result.truncate(result_cursor);
        }
    }
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End  GS_string::parse_token__quoted_str()  Result:\"%s\"",
      p_result.char_ptr()));
}

void
Description::parse_token__ticked_str (t_uint& p_cursor, Description& p_result) const  

{
  if ( p_result.max_length < cur_length )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = cur_length;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }

  //  Remove leading white space.
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text[p_cursor])));
       p_cursor++)
    ;  // do nothing


  if (text[p_cursor] == vcharFromASCII('\''))
    {
      //  Use first character beyond the tick as the first token character.
      p_cursor++;
      t_uint first_char_position = p_cursor;

      //  Search for the end of the ticked string.
      t_uint result_cursor = 0;
      t_boolean done = FALSE;
      while ((! done) && (p_cursor < cur_length))
        {
          if (text[p_cursor] == vcharFromASCII('\''))
            {
              if (((p_cursor + 1) < cur_length)
                  &&
                  (text[p_cursor + 1] == vcharFromASCII('\'')))
                {
                  p_result.text[result_cursor] = text[p_cursor];
                  result_cursor++;
                  p_cursor++;
                  p_cursor++;
                }
              else
                {
                  done = TRUE;
                }
            }
          else
            {
              p_result.text[result_cursor] = text[p_cursor];
              result_cursor++;
              p_cursor++;
            }
        }
      if (text[p_cursor] != vcharFromASCII('\''))
        {
          p_result = Description::Default;
        }
      else
        {
          //  Increment beyond the tick character.
          //
          p_cursor++;
          p_result.truncate(result_cursor);
        }
    }
	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End  GS_string::parse_token__ticked_str()  Result:'%s'",
      p_result.char_ptr()));
}

void
Description::parse_token__parened_str (t_uint& p_cursor, Description& p_result) const
{
  
  //  Remove leading white space.
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text [p_cursor])));
       p_cursor++)
    ;  // do nothing

  if (text [p_cursor] == '(')
    {
      //  Use first character beyond '(' as the first token character.
      p_cursor++;
      t_uint first_char_position = p_cursor;
      
      //  Search for the end of the parened string.
      t_boolean done = FALSE;
      t_uint paren_depth = 0;
      while ((! done) && (p_cursor < cur_length))
        {
          if (text [p_cursor] == vcharFromASCII('\''))
            {
              //  Have come across a begin ' character - need to find the
              //    end ' character.
              t_boolean end_tick_found = FALSE;
              while ((! end_tick_found) && (p_cursor < cur_length))
                {
                  p_cursor++;
                  if (text [p_cursor] == vcharFromASCII('\''))
                    {
                      if (text [p_cursor + 1] == vcharFromASCII('\''))
                        {
                          //  Have come across a repeated ' character -
                          //    increment the cursor one additional time
                          //    so it is ignored.
                          p_cursor++;
                        }
                      else
                        {
                          end_tick_found = TRUE;
                          p_cursor++;
                        }
                    }
                }
            }
          else if (text [p_cursor] == vcharFromASCII('"'))
            {
              //  Have come across a begin " character - need to find the
              //    end " character.
              t_boolean end_quote_found = FALSE;
              while ((! end_quote_found) && (p_cursor < cur_length))
                {
                  p_cursor++;
                  if (text [p_cursor] == vcharFromASCII('"'))
                    {
                      if (text [p_cursor + 1] == vcharFromASCII('"'))
                        {
                          //  Have come across a repeated " character -
                          //    increment the cursor one additional time
                          //    so it is ignored.
                          p_cursor++;
                        }
                      else
                        {
                          end_quote_found = TRUE;
                          p_cursor++;
                        }
                    }
                }
            }
          else if (text [p_cursor] == '(')
            {
              paren_depth++;
              p_cursor++;
            }
          else if (text [p_cursor] == ')')
            {
              if (paren_depth > 0)
                {
                  paren_depth--;
                  p_cursor++;
                }
              else
                {
                  done = TRUE;
                }
            }
          else
            {
              p_cursor++;
            }
        }
      if (text [p_cursor] == ')')
        {
          // Build a string with the characters found between the
          // paren's - do NOT include the '(' and ')' characters.
          t_int length = p_cursor - first_char_position;
          if (length < 0)
            length = 0;
          Description result2 (length);
          if (length > 0)
            {
              vcharCopyBounded(&text[first_char_position],
                               result2.text, length);
              result2.truncate(length);
              p_result = result2;
            }
          else
          {
              p_result = Description::Default;
          }
          //  Increment beyond the paren character.
          p_cursor++;
        }
    }

	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End  GS_string::parse_token__parened_str()  Result:'%s'",
      p_result.char_ptr()));

}

void
Description::parse_to_keyword (const char* p_keyword_str, t_uint& p_cursor, Description& p_result) const
{
  Description keyword_str (p_keyword_str);

  //  Remove leading white space.
  for (;
       ((p_cursor < cur_length) && (vcharIsWhiteSpace (text [p_cursor])));
       p_cursor++)
    ;  // do nothing

    //  Use first non-white space character as the first token character.
  t_uint first_char_position = p_cursor;

  //  Search for the next occurance of delimeter.
  t_boolean done = FALSE;
  while ((! done) && (p_cursor < cur_length))
    {
      if (text [p_cursor] == vcharFromASCII('\''))
        {
          //  Have come across a begin ' character - need to find the
          //    end ' character.
          //
          t_boolean end_tick_found = FALSE;
          while ((! end_tick_found) && (p_cursor < cur_length))
            {
              p_cursor++;
              if (text [p_cursor] == vcharFromASCII('\''))
                {
                  if (text [p_cursor + 1] == vcharFromASCII('\''))
                    {
                      //  Have come across a repeated ' character -
                      //    increment the cursor one additional time
                      //    so it is ignored.
                      p_cursor++;
                    }
                  else
                    {
                      end_tick_found = TRUE;
                    }
                }
            }
        }
      if (text [p_cursor] == vcharFromASCII('"'))
        {
          //  Have come across a begin " character - need to find the
          //    end " character.
          t_boolean end_quote_found = FALSE;
          while ((! end_quote_found) && (p_cursor < cur_length))
            {
              p_cursor++;
              if (text [p_cursor] == vcharFromASCII('"'))
                {
                  if (text [p_cursor + 1] == vcharFromASCII('"'))
                    {
                      //  Have come across a repeated " character -
                      //    increment the cursor one additional time
                      //    so it is ignored.
                      p_cursor++;
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
           (match_found) && ((ii + p_cursor) < cur_length)
             && (ii <= keyword_str.length ());
           ii++)
        {
          if ((ii == 0) || (ii == (keyword_str.length () + 1)))
            {
              //  Keyword must be surrounded by whitespace.
              if (! vcharIsWhiteSpace (text [ii + p_cursor]))
                {
                  match_found = FALSE;
                }
            }
          else
            {
              char str_char = ((text [ii + p_cursor] >= 'a')
                               && (text [ii + p_cursor] <= 'z'))
                ? (text [ii + p_cursor] - 0x20)
                : (text [ii + p_cursor]);
              char keyword_char = ((keyword_str.text [ii - 1] >= 'a')
                                   && (keyword_str.text [ii - 1] <= 'z'))
                ? (keyword_str.text [ii - 1] - 0x20)
                : (keyword_str.text [ii - 1]);
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
          done = TRUE;
          p_cursor++;
        }
      else
        {
          p_cursor++;
        }
    }      

  //  Back up to first non-white space character.
  t_int last_char_position = 0;
  if (p_cursor > 0)
    {
      for (last_char_position = p_cursor - 1;
           ((last_char_position > 0)
            && (last_char_position > first_char_position)
            && (vcharIsWhiteSpace (text [last_char_position])));
           last_char_position--)
        ;  // do nothing
    }
  else
    {
      //  We want a 0 length string to result...
      last_char_position = -1;
    }
   
  //  Build a string with the characters found between the white space.
  t_int length = last_char_position - first_char_position + 1;
  if (length < 0)
    length = 0;
    
  if ( p_result.max_length < length )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = length;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }
  if (length > 0)
    {
      vcharCopyBounded(&(text [first_char_position]), p_result.text, length);
      p_result.truncate(length);
    }

	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End  GS_string::parse_to_keyword()  Result:'%s'",
      p_result.char_ptr()));

}

// Note: this function will work if 'this' and p_result are
// the same instance.

void
Description::convert_delimited_string (vchar p_delimiter,
              t_boolean p_change_double_to_single, Description& p_result) const

{
  if (text[0] != p_delimiter)
    {
      LOG_ERROR ((L_log_string,
	    "Description::convert_delimited_string ():  called with string which does NOT begin with the delimiter"));
    }

  if (text[cur_length - 1] != p_delimiter)
    {
      LOG_ERROR ((L_log_string,
	    "Description::convert_delimited_string ():  called with string which does NOT end with the delimiter"));
    }

  if ( p_result.max_length < cur_length )
  {
      p_result.delete_vstr_ptr ();
      p_result.max_length = cur_length;
      p_result.text = new_vstr_ptr_stretch( &p_result, p_result.max_length );
      p_result.text[0] = 0;
      p_result.cur_length = 0;
  }

  t_uint i = 0;

  //  Begin on 2nd character and end on 2nd to last character so the begin
  //    and end delimiters are taken off.
  for (t_uint j = 1;
       j < (cur_length - 1);
       j++)
    {
      p_result.text [i++] = text [j];
      if (p_change_double_to_single)
        {
          if ((text[j] == p_delimiter)
              &&
              (text[j + 1] == p_delimiter))
            {
              //  Repeated delimiter has occurred - skip the second delimiter.
              j++;
            }
        }
    }
  p_result.truncate(i);

	LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
	    "End  GS_string::convert_delimited_string()  Result:'%s'",
      p_result.char_ptr()));
  
}


char *
Description::createAsciiFromVchar(const vchar *p_inBuf)
{
  char *outBufAscii =
    (char *) vcharExportAlloc( vcharScribeASCIIExport( p_inBuf ) );
  const char ascii_space   = ' ';
  const char ascii_alpha   = 'Z';
  const char ascii_numeric = '9';
  const char ascii_punc    = '?';
  
  // Change all non-ascii characters in p_action_desc 
  // to something appropriate
  register const vchar *vchar_ptr = p_inBuf;
  register char *char_ptr = outBufAscii;
  while (*char_ptr)
    {
      if ( *char_ptr == ascii_space )
        {
          if ( ! vcharIsWhiteSpace( *vchar_ptr ) )
            {
              if ( vcharIsAlphabetic( *vchar_ptr ) )
                *char_ptr = ascii_alpha;
              else if ( vcharIsNumeric( *vchar_ptr ) )
                *char_ptr = ascii_numeric;
              else if ( vcharIsPunctuation( *vchar_ptr ) )
                *char_ptr = ascii_punc;
              else if ( vcharIsGraphic( *vchar_ptr ) )
                *char_ptr = ascii_alpha;
              else
                *char_ptr = ascii_punc;
            }
        }
      char_ptr++;
      vchar_ptr++;
    }
  return outBufAscii;
}

void Description::freeAsciiFromVchar(char *inBuf)
{
	if ( inBuf )
	{
		vcharExportFree( inBuf );
	}
}

#include <iostream.h>

ostream& operator<<( ostream& s, const vchar* t )
{
	char * local_str = (char*) vcharExportAlloc(vcharScribeSystemExport(t));
	s << local_str;
  vcharExportFree(local_str);
	return s;
}

t_boolean Description::find_action_spec_tag( char *description_text )
{
  LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_BEGIN, (L_log_string,
	 "Begin Description::find_action_spec_tag ()."));


  GS_string description_str( description_text );
  t_boolean interpret = FALSE;
  description_str.consume_white_space ();
  if (((description_str.cursor () + 1) < description_str.length ())
      && (description_str [description_str.cursor ()] == '/')
      && (description_str [description_str.cursor () + 1] == '/'))
    {
      description_str++;
      description_str++;
      if (description_str.cursor () < description_str.length ())
        {
          GS_string keyword_str (description_str.parse_token (':'));
          if (description_str == ':')
            {
              keyword_str.convert_to_upper_case ();
              if (keyword_str == "ACTION_SPECIFICATION")
                {
                  description_str++;
                  if (description_str.cursor () < description_str.length ())
                    {
                      GS_string value_str (description_str.parse_token ());
                      value_str.convert_to_upper_case ();
                      if (value_str == "TRUE")
                        {
                          interpret = TRUE;
                        }
                    }
                }
            }
        }
    }

  LOG_TRACE (L_N_PROJ_NB, L_FUNCTION_END, (L_log_string,
    "End Description::find_action_spec_tag()."));

  return interpret;

}

long Description::persist() 
{
	long numBytes = 0;
	numBytes += writeLong(max_length);
	long sizeOfString = (cur_length*sizeof(vchar));
	if (sizeOfString) {
		// If there is a string to persist then get the trailing null
		sizeOfString += sizeof(vchar);
	}
	numBytes += writeBlob((char*)text, sizeOfString);
	return numBytes;
}

void Description::restore() 
{
	max_length = readLong();
	
	// Allocate the buffer if we need to
	if ( max_length < INITIAL_STRING_SIZE ) {
		text = m_initial_string;
	} else {
		text = new_vstr_ptr( this, max_length);
	}
	
	cur_length = readBlob((char*)text) / sizeof(vchar);
	if (cur_length) {
		// If there was a string to persist, then subtract the ize of the
		// trailing null.  We only subtract 1 here and not sizeof(vchar) because this
		// variable tracks the number of character in the string, not the number of bytes.
		cur_length -= 1;
	}

}

char* Description::create() 
{
	Description* newInstance = new Description();
	newInstance->restore();
	return (char*)newInstance;
}


//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
