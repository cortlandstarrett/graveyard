/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef Dumper_stream_HH
#define Dumper_stream_HH

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
  class os_Dumper_stream
***********************************************************************/

class os_Dumper_stream : public ostream
   {
public: // Construction
   os_Dumper_stream (const char* filename);
   os_Dumper_stream (const ostream& out);
  ~os_Dumper_stream ();
public:  // assignment
   os_Dumper_stream& operator=(const char*);
public: // Manipulator Output
   os_Dumper_stream& operator<< (ostream& (*manipulator)(ostream&));
   os_Dumper_stream& operator<< (os_Dumper_stream& (*manipulator)(os_Dumper_stream&));
   os_Dumper_stream& operator<< (ios& (*manipulator)(ios&));
public: // String Output
   os_Dumper_stream& put (const char*, int length, char terminator = 0);
   os_Dumper_stream& put (const unsigned char*, int length);
   os_Dumper_stream& put (const signed char*, int length);
   os_Dumper_stream& operator<< (const char*);
   os_Dumper_stream& operator<< (const unsigned char*);
   os_Dumper_stream& operator<< (const signed char*);
public: // Char Output
   os_Dumper_stream& put (const char&);
   os_Dumper_stream& put (const unsigned char&);
   os_Dumper_stream& put (const signed char&);
   os_Dumper_stream& operator<< (const char&);
   os_Dumper_stream& operator<< (const unsigned char&);
   os_Dumper_stream& operator<< (const signed char&);
public: // Short Output
   os_Dumper_stream& operator<< (const short&);
   os_Dumper_stream& operator<< (const unsigned short&);
public: // Int Output
   os_Dumper_stream& operator<< (const int&);
   os_Dumper_stream& operator<< (const unsigned int&);
public: // Long Output
   os_Dumper_stream& operator<< (const long&);
   os_Dumper_stream& operator<< (const unsigned long&);
public: // os_unsigned_int64 output
   os_Dumper_stream& operator<< (const os_int64&);
   os_Dumper_stream& operator<< (const os_unsigned_int64&);
public: // Real Output
   os_Dumper_stream& operator<< (const float&);
   os_Dumper_stream& operator<< (const double&);
   os_Dumper_stream& operator<< (const long double&);
public: // os_Dumper_reference Output
   os_Dumper_stream& operator<< (const os_Dumper_reference&);
public:  // manipulators
   os_Dumper_stream& quote() {_quote = !_quote; return *this;}
   os_boolean is_quoting() {return _quote;}
private:
   void outchar(const unsigned char value);
private:  // assignment
   os_Dumper_stream& operator=(streambuf* _sb);
private: // Embedded data
   os_boolean _quote;
   ostream* stream;
   };
inline os_Dumper_stream& string_quote(os_Dumper_stream& s)
   {
   if (s.is_quoting())
      {
      s.quote();
      s << "\"";
      return s;
      }
   s << "\"";
   return s.quote();
   }
inline os_Dumper_stream& char_quote(os_Dumper_stream& s)
   {
   if (s.is_quoting())
      {
      s.quote();
      s << "\'";
      return s;
      }
   s << "\'";
   return s.quote();
   }

#endif /* Dumper_stream_HH */
