/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef LOADER_STREAM_HH
#define LOADER_STREAM_HH

/***********************************************************************
*                                                                      *
* Copyright (c) 1997-2000 by eXcelon Corporation. All Rights Reserved.                          *
*                                                                      *
* eXcelon Corporation Confidential Restricted material.  This work     *
* contains confidential trade secrets of eXcelon Corp..  Use,          *
* examination, copying, transfer and/or disclosure to others are       *
* prohibited, except with the express written agreement of eXcelon     *
* Corp.                                                                *
*                                                                      *
* THIS WORK IS PROVIDED AS IS, WHERE IS, WITH ABSOLUTELY NO WARRANTIES *
* WHATSOEVER, WHETHER EXPRESS OR IMPLIED.                              *
*                                                                      *
***********************************************************************/

//-- Include files -----------------------------------------------------

#include <fstream.h>
#include <ostore/dumpload/dmp_ref.hh>
#include <ostore/dumpload/value.hh>


/***********************************************************************
  class os_Loader_stream
***********************************************************************/

class os_Loader_stream : public ifstream {

  public: // Construction
    os_Loader_stream (const char* filename);
    ~os_Loader_stream ();

  public: // Manipulator Input
    os_Loader_stream& operator >> (istream& (*manipulator)(istream&));
    os_Loader_stream& operator >> (ios& (*manipulator)(ios&));

  public: // String Input
    os_Loader_stream& get (char*, int maximum_length, char terminator = '\n');
    os_Loader_stream& get (int length,char*);
    os_Loader_stream& get (unsigned char*, int maximum_length, 
			   char terminator = '\n');
    os_Loader_stream& get (signed char*, int maximum_length, 
			   char terminator = '\n');
    os_Loader_stream& operator >> (char*&);
    os_Loader_stream& operator >> (unsigned char*);
    os_Loader_stream& operator >> (signed char*);

  public: // Char Input
    os_Loader_stream& get (char&);
    os_Loader_stream& get (unsigned char&);
    os_Loader_stream& get (signed char&);
    os_Loader_stream& operator >> (char&);
    os_Loader_stream& operator >> (unsigned char&);
    os_Loader_stream& operator >> (signed char&);

  public: // Short Input
    os_Loader_stream& operator >> (short&);
    os_Loader_stream& operator >> (unsigned short&);

  public: // Int Input
    os_Loader_stream& operator >> (int&);
    os_Loader_stream& operator >> (unsigned int&);

  public: // Long Input
    os_Loader_stream& operator >> (long&);
    os_Loader_stream& operator >> (unsigned long&);

  public: // os_unsigned_int64 Input
    os_Loader_stream& operator >> (os_unsigned_int64&);

  public: // Real Input
    os_Loader_stream& operator >> (float&);
    os_Loader_stream& operator >> (double&);
    os_Loader_stream& operator >> (long double&);

  public: // Values Input
    os_Loader_stream& operator >> (os_Input_values&);
    os_Loader_stream& operator >> (os_Dumper_reference& reference);
    os_Loader_stream& operator >> (os_Fixup_reference& reference);

  public: // streambuf Input
    os_Loader_stream& get (streambuf&, char terminator = '\n');

  protected: // Embedded data
    unsigned string_buffer_size;
    char* first_string_buffer;
    char* string_buffer;

  protected: // Modifiers
    const char* push_string_buffer ();
    void pop_string_buffer (const char* previous_string_buffer);

  private: // Friends
    friend class os_Loader_info;

  };


#endif /* LOADER_STREAM_HH */
