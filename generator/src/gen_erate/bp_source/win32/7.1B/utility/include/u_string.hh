/*========================================================================
 *
 * File:      $RCSfile: u_string.hh,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/mc_dbms.hh>

#ifndef U_STRING_HH
#define U_STRING_HH


//
// REMARKS:
//
//		It is important to note that this class can be used persistently
//		or transiently. A String is transient with a "plain-ole" new and
//		persistent with an overloaded MC_DBMS new. Even though this class is
//		general-purpose, it still depends on MC_DBMS (hence in this
//		db_utility directory).
//


// Include those header files that are DIRECTLY needed by this one.

#include <string.h>


#include "u_typdef.hh"


//
// CLASS: String
//
// DESCRIPTION:
//
//		This class creates a general-purpose String class.
//
// REMARKS:
//
//		None.
//

class String
	{
	public:
		// MANAGER functions

		// Constructors
		// Eg - String s1;			// null/empty zero-length string
		//	    String s2(10); 		// null("") string of length 10
		//		String s3( "Goto Hell" );
		//		String s4 = s3;

		String();
		String( t_uint p_len  );
		String( const char *p_str_ptr );
		String( const String &p_string );
		~String();

		// IMPLEMENTOR functions

		// Assignment
		// Eg - String s1;
		//		String s2;
		//		s1 = s2;
		//		s1 = "plain ole character string";

		String& operator=( const String &p_string );
		String& operator=( const char *p_str_ptr );

		// Comparison operator == (returns TRUE/FALSE)
		// Eg - String s1 = "Kentucky Sux";
		//		String s2 = "Kentucky Sucks";
		//		if ( s1 == s2 ) { ... }

		t_boolean operator==( const String &p_string ) const;
		t_boolean operator==( const char *p_char_ptr ) const;

		t_boolean operator!=( const String &p_string ) const
			{ return( ! ( *this == p_string ) ); }
		t_boolean operator!=( const char *p_char_ptr ) const
			{ return( ! ( *this == p_char_ptr ) ); }

		// Compare function similar to "strcmp"
		// Returns < 0 if s1<s2; 0 if s1 == s2; > 0 if s1>s2
		// Eg - int result = s1.compare( s2 );

		int compare( const String &p_string ) const;
		int compare( const char *p_char_ptr ) const;

		// Concatenation using "+="
		//		Eg - String s1( "UM " );
		//			 String s2( "is #1" );
		//			 s1 += s2;		// s1 <--- "UM is #1"
		//			 s1 += "28 OSU 0";   // s1 <--- "UM 28 OSU 0"

		String& operator+=( const String &p_string );
		String& operator+=( const char *p_str_ptr );

		// Concatenation using "+"
		//		Eg - String s1( "Iowa State" );
		//			 String s2( " Wins" );
		//			 String s3 = s1 + s2;	// s3 <--- "Iowa State Wins"
		//			 s3 = s1 + " Loses";  // s3 <--- "Iowa State Loses"

		String operator+( const String &p_string ) const;
		String operator+( const char *p_str_ptr ) const;

		// Treat String like an array index. Can be used as l-value or r-value
		//		Eg - String s1( "NCSU is great" );
		//			 char sub_char = s1[ 3 ];		// sub_char <--- "U"
		//
		//			 String s2( "ISU Wins" );
		//			 s2[ 0 ] = 'O';		// s2<--- "OSU Sux"

		const char& operator[]( t_uint p_index )
             { return str_ptr[ p_index ]; }

		String& reset( t_uint p_len = 0 );  // discard current contents;
			// null string in buffer of length p_len + 1

		// "parse" returns the next token that is deliminated by the delimiter
		// and removes it from "this" String.  If the skip_doubles parameter
		// is TRUE, then an occurances of p_delimeter which show up 2 in a
		// row will skipped.

		String parse( const char p_delimiter, t_boolean p_skip_doubles = FALSE);

		// "delimit_character" finds each specified p_character and
		// adds p_prefix_delimiter character immediately preceding it.
		// We will return the number of p_prefix_delimiters we add.

		int delimit_character( const char p_prefix_delimiter,
			const char p_character );

		// "pare_character" finds each consecutive pair (no pun intended)
		// of the specified p_prefix_delimiter and and p_character and
		// replaces it by just the p_character (in essence simply deleting
		// the p_prefix_delimiter). The number of replaced pairs is returned.

		int pare_character( const char p_prefix_delimiter,
			const char p_character );

		// Return the beginning position of the FIRST occurrence of the
		// ENTIRE specified string. The first position starts with 0.
		// If string not found, then a negative number is returned.

		int position_of( const String &p_string ) const;
		int position_of( const char *p_string ) const;

		// Simply copy n characters from the argument and replace this entire
		// string. Of course we will only copy up to the null character ('\0')
		// in the argument if it comes before n characters.

		String& copy_n( const String &p_string, int n );
		String& copy_n( const char *p_string, int n );

		// Copy n characters from argument and append to END of this string.
		// (Or up to null if comes first).

		String& concat_n( const String &p_string, int n );
		String& concat_n( const char *p_string, int n );

        void truncate( t_uint position );

		// ACCESS functions.

		const char *char_ptr() const { return str_ptr; }
		t_uint length() const { return len; }

	private:
		char *str_ptr;
		t_uint len;

		// HELPING functions
        static char temp_during_init[2];
		char *new_str_ptr( String *p_string_ptr, t_uint p_len );
		void delete_str_ptr( char *p_string_ptr );

	};






































//
// CLASS: GS_string
//
// DESCRIPTION:
//
//      This class creates a general-purpose GS_string class.
//
// REMARKS:
//
//      None.
//

class GS_string
{
public:
    // Constructors
    // Eg - GS_string s1;                //  null/empty zero-length string
    //      GS_string s2 (10);           //  null ("") string of length 10
    //      GS_string s3 ("Objective Spectrum");
    //      GS_string s4 = s3;
    //
    GS_string ();
    GS_string (t_uint p_length);
    GS_string (const char *p_char_ptr);
    GS_string (const GS_string &p_string);
    GS_string (const String &p_string);
    ~GS_string ();



    // Assignment
    // Eg - GS_string s1;
    //      GS_string s2;
    //      s1 = s2;
    //      s1 = "plain old character string";
    //
    GS_string& operator= (const GS_string &p_string);
    GS_string& operator= (const char *p_char_ptr);



    // Comparison operator == (returns TRUE/FALSE)
    // Eg - GS_string s1 = "To Be";
    //      GS_string s2 = "To Be or Not To Be";
    //      if (s1 == s2) { ... }
    //
    t_boolean operator<  (const GS_string &p_string) const;
    t_boolean operator<= (const GS_string &p_string) const;
    t_boolean operator== (const GS_string &p_string) const;
    t_boolean operator!= (const GS_string &p_string) const;
    t_boolean operator>= (const GS_string &p_string) const;
    t_boolean operator>  (const GS_string &p_string) const;
    t_boolean operator<  (const char *p_char_ptr) const;
    t_boolean operator<= (const char *p_char_ptr) const;
    t_boolean operator== (const char *p_char_ptr) const;
    t_boolean operator!= (const char *p_char_ptr) const;
    t_boolean operator>= (const char *p_char_ptr) const;
    t_boolean operator>  (const char *p_char_ptr) const;
    t_boolean operator== (const char p_char) const;
    t_boolean operator!= (const char p_char) const;


    
    // Compare function similar to "strcmp"
    // Returns < 0 if s1<s2; 0 if s1 == s2; > 0 if s1>s2
    // Eg - int result = s1.compare (s2);
    //
    int compare_n (const GS_string &p_string, t_uint p_n) const;
    int compare_n (const GS_string &p_string, t_uint p_start_char, t_uint p_n) const;
    int compare_n (const char *p_char_ptr, t_uint p_n) const;
    int compare_n (const char *p_char_ptr, t_uint p_start_char, t_uint p_n) const;



    // Concatenation using "+="
    // Eg - GS_string s1 ("cobble");
    //      GS_string s2 ("stone");
    //      s1 += s2;      // s1 <--- "cobblestone"
    //      s1 += "rock";  // s1 <--- "cobblerock"
    //
    GS_string& operator+= (const GS_string &p_string);
    GS_string& operator+= (const char *p_char_ptr);
    GS_string& operator+= (const char p_char);
    
    
    
    // Concatenation using "+"
    // Eg - GS_string s1 ("Iowa State");
    //      GS_string s2 (" is Great");
    //      GS_string s3 = s1 + s2;   // s3 <--- "Iowa State is Great"
    //      s3 = s1 + " Rules Carolina";  // s3 <--- "Iowa State Rules Carolina"
    //
    GS_string operator+ (const GS_string &p_string) const;
    GS_string operator+ (const char *p_char_ptr) const;
    GS_string operator+ (const char p_char) const;
    
    
    
    // Treat GS_string like an array index. Can be used as l-value or r-value
    // Eg - GS_string s1 ("NCSU is Great");
    //      char sub_char = s1 [3];              // sub_char <--- "U"
    //      GS_string s2 ("ISU is Great");
    //      s2 [0] = 'O';                        // s2<--- "OSU is Great"
    //
    char& operator[] (t_uint p_index);
    
    
    
    // Cursor Functions.
    //
    char curr_char ();
    GS_string& operator++ (int);
    GS_string& operator-- (int);
    t_uint operator+= (t_uint p_increment);
    t_uint reset_cursor (t_uint p_cursor = 0);
// This enumerator should not be modified.  The enumerations can be ORed together
// and are taken back apart in parse_token().
    enum e_parse_modifier {GS_NO_PARSE_MODIFIER=0x0,
			   GS_IGNORE_WITHIN_TICKS=0x1,
			   GS_IGNORE_REPEATED_TICKS_WITHIN_TICKS=0x3,
			   GS_IGNORE_WITHIN_QUOTES=0x01,
			   GS_IGNORE_REPEATED_QUOTES_WITHIN_QUOTES=0x03};
    GS_string parse_token (
	int p_parse_modifier = GS_NO_PARSE_MODIFIER);
    GS_string parse_token (char p_char,
	int p_parse_modifier = GS_NO_PARSE_MODIFIER);
    GS_string parse_token (const GS_string& p_str,
	int p_parse_modifier = GS_NO_PARSE_MODIFIER);

    GS_string parse_token_leave_ws (char p_char,
	int p_parse_modifier = GS_NO_PARSE_MODIFIER);
    GS_string parse_token_leave_ws (const GS_string& p_str,
	int p_parse_modifier = GS_NO_PARSE_MODIFIER);

    GS_string parse_to_keyword (const GS_string& p_str);
    GS_string parse_to_end ();
    GS_string parse_token__ticked_str ();
    GS_string parse_token__quoted_str ();
    GS_string parse_token__parened_str ();
    GS_string parse_token__lvalue ();
    GS_string parse_token__rvalue ();
    GS_string parse_token__unary_op ();
    GS_string parse_token__binary_op ();
    GS_string parse_token__parameter (const GS_string& p_param_name_str) const;
    void consume_white_space ();
    enum e_conversion_modifier {GS_NO_CONVERSION_MODIFIER=0x0,
				GS_CHANGE_REPEATED_DELIMITERS_TO_SINGLES=0x1};
    GS_string convert_delimited_string (char p_delimiter,
	e_conversion_modifier p_conversion_modifier =GS_NO_CONVERSION_MODIFIER);
    


    // Reset the length of the string and discard the current contents.
    //
    GS_string& reset (t_uint p_length);
    void recalc_length ();
    
    
    
    // Simply copy n characters from the argument and replace the entire
    // string (or up until null('\0'), whichever comes first).
    //
    GS_string& copy_n (const GS_string& p_string, t_uint p_n);
    GS_string& copy_n (const char* p_string, t_uint p_n);
    
    
    
    // Simply concatenate n characters from the argument to the end of the
    // string (n characters or up until null('\0'), whichever comes first).
    //
    GS_string& concat_n (const GS_string& p_string, t_uint p_n);
    GS_string& concat_n (const char* p_string, t_uint p_n);
    
    
    
    // Convert all characters in the string to upper case or lower case.
    //
    void convert_to_upper_case ();
    void convert_to_lower_case ();

    
    
    // ACCESS functions.
    //
    t_uint length () const { return m_length; }
    t_uint cursor () const { return m_cursor; }
    const char *char_ptr () const { return m_char_ptr; }




private:
    char *m_char_ptr;
    t_uint m_length;
    t_uint m_cursor;
	char m_null_string;

	void delete_char_ptr();
};




extern GS_string GS_string__NULL;




#endif
