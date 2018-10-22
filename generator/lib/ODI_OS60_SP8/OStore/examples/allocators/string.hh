//
// String.hh
//
// A simple internal String class to be used in the course
//

#ifndef STRING_H
#define STRING_H
#include <ostore/ostore.hh>    // Required to access ObjectStore Class Library

class ostream;

class String
{
public:
  static os_typespec* get_os_typespec ();
             //  (ObjectStore will provide implementation at build time.)

  String ( const char* str = "" );
  String ( const String& copy );
  String& operator= ( const String& from );
  ~String ();
  int operator == ( const String& compare );
  void setString ( const char *str );
  const char *getString () const;
  friend ostream& operator<<(ostream& output, String& string);

private:
  char* _strRep;
};

//
// overload operator << for writing String object
//

ostream& operator<<(ostream& output, String& string);

#endif // STRING_H

