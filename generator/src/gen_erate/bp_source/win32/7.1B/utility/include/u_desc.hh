/*========================================================================
 *
 * File:      $RCSfile: u_desc.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:33 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef U_DESC_HH
#define U_DESC_HH

#include <vchar.h>
#include <vstr.h>


#include "u_typdef.hh"


class String;


class Description : public SerializableObject

{
public:
  static Description	Default;
  static vchar * null_string;



  // Constructors & Destructor:
  //
  // Eg - Description desc1;		// A null("") description
  //		Description desc2 ("A description");
  //		String s1 ("A string description");
  //		Description desc3 = s1;
  //		Description desc4 = desc3;
  //
  Description ();
  Description (t_uint p_size);
  Description (const char* p_desc_ptr);
  Description (const vchar* p_desc_ptr);
  Description (const String& p_desc_str);
  Description (const Description& p_desc);
  ~Description ();


  // Assignments:
  //
  // Eg - Description desc1, desc2;
  //		String s1;
  //	    desc1 = desc2;
  //		desc1 = s1;
  //		desc2 = "A character string description";
  //
  Description&	operator= (const Description& p_desc);
  Description&	operator= (const String& p_string);
  Description&	operator= (const char* p_char_ptr);
  Description&	operator= (const vchar* p_char_ptr);

  Description&	operator+= (const char* p_char_ptr);
  Description&	operator+= (const vchar* p_char_ptr);
  Description&	operator+= (const Description& p_desc);

  //  Reset:
  //     1.  discard contents;
  //     2.  allocate null string in buffer of length p_len + 1
  //
  Description&	reset (t_uint p_len);


  // ACCESS fuctions
  //
  const vchar*		char_ptr () const
    { return text; }

	vchar char_at(t_uint position) const
    { return text[position]; }

  void truncate( t_uint position );

  t_uint length () const;
  t_boolean operator== (const Description& p_desc) const;
  t_boolean operator!= (const Description& p_desc) const;

  t_boolean compare_first (const vchar p_char, t_uint p_cursor) const;
  int compare_n (const char *p_char_ptr, t_uint p_n) const;
	int compare( const Description& p_string ) const;

  // Modification functions

	void append_char( const vchar p_char );

  // "delimit_character" finds each specified p_character and
  // adds p_prefix_delimiter character immediately preceding it.
  // We will return the number of p_prefix_delimiters we add.

  int delimit_character( const vchar p_delimiter, const vchar p_character );
  int pare_character( const vchar p_delimiter, const vchar p_character );

  // "parse" returns the next token that is deliminated by the delimiter
  // and removes it from "this" String.  If the skip_doubles parameter
  // is TRUE, then an occurances of p_delimeter which show up 2 in a
  // row will skipped.

  void parse( int p_start, 
                     const vchar p_delimiter,
					 Description& p_result,
                     t_boolean p_skip_doubles = FALSE);

	void parse_token_leave_ws( const Description& p_string,
                                    t_uint& cursor, Description& p_result);
	void parse_token_leave_ws( const vchar p_char, t_uint& cursor, Description& p_result);
  void parse_token (char p_char,
                           t_uint& cursor, Description& p_result, 
                           t_boolean ignore_within_ticks = FALSE,
                           t_boolean ignore_within_quotes = FALSE) const ;
  void parse_token (const Description& p_pattern,
                           t_uint& cursor, Description& p_result) const ;
  void parse_token (t_uint& cursor, Description& p_result) const ;
  void parse_token__lvalue (t_uint& cursor, Description& p_result) const ;
  void parse_token__rvalue (t_uint& cursor, Description& p_result) const ;
  void parse_token__unary_op (t_uint& cursor, Description& p_result) const ;
  void parse_token__binary_op (t_uint& cursor, Description& p_result) const ;
  void parse_to_end (t_uint& cursor, Description& p_result) const ;
  void parse_to_keyword (const char* keyword, t_uint& cursor, Description& p_result) const ;
	void parse_token__quoted_str (t_uint& p_cursor, Description& p_result) const ;
	void parse_token__ticked_str (t_uint& p_cursor, Description& p_result) const ;
	void parse_token__parened_str (t_uint& p_cursor, Description& p_result) const ;
	void convert_delimited_string (vchar p_delimiter,
                        t_boolean p_change_double_to_single, Description& p_result) const ;

  void consume_white_space (t_uint& cursor) const ;

	void convert_to_lower_case();
	void convert_to_upper_case();
	void indent_lines(int p_indent_length);
  void make_words_capital();
  void make_spaces_underbars();
	void remove_all_white_space();
  void make_corba_compliant();

	static char *createAsciiFromVchar(const vchar *inBuf);
	static void freeAsciiFromVchar(char *inBuf);

	static t_boolean find_action_spec_tag( char *description_text );

public:

	virtual long persist();

	virtual void restore();

	static char* create();

private:
  enum { INITIAL_STRING_SIZE = 16 };

  t_uint max_length;
  t_uint cur_length;
  vchar *text;
  vchar m_initial_string[INITIAL_STRING_SIZE];

  void delete_vstr_ptr();

};

class ostream;

ostream& operator<<( ostream& s, const vchar* t );


#endif

//
// Formatting information for emacs
//
// Local Variables:
// tab-width:2
// End:
//
