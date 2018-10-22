#include <string.h>
#include <iostream.h>
#include "string.hh"

String :: String ( const char* str )
{
  if (!str)
    _strRep = 0;
  else
    {
      int charLen = strlen(str)+1;
      _strRep = new (os_cluster::of(this),os_typespec::get_char(),charLen)
	char [charLen];
      strcpy ( _strRep, str );
    }
}

String :: String ( const String& copy )
{
  int charLen = strlen (copy._strRep)+1;
  _strRep = new (os_cluster::of(this),os_typespec::get_char(),charLen)
    char [charLen];
  strcpy (_strRep, copy._strRep);
}

String& String :: operator= ( const String& from )
{
  int charLen=strlen(from._strRep)+1;
  if ( _strRep != from . _strRep )
    {
      delete [] _strRep;
      _strRep = new (os_cluster::of(this),os_typespec::get_char(),charLen)
	char [charLen];
      strcpy ( _strRep, from . _strRep );
    }
  return *this;
}

int String :: operator == ( const String& compare )
{
  if ( strcmp ( compare.getString(), _strRep ) == 0 )
    return 1;
  else
    return 0;
}

String :: ~String ()
{
  delete [] _strRep;
}

void String :: setString ( const char *str )
{
  if (!str)
    _strRep = 0;
  else
  {
    if (_strRep)
      delete [] _strRep;
    int charLen = strlen(str)+1;
    _strRep = new (os_cluster::of(this),os_typespec::get_char(),charLen)
      char [charLen];
    strcpy ( _strRep, str );
  }
}

const char * String :: getString () const
{
  return _strRep;
}

ostream& operator<<(ostream& output, String& string)
{
  return output << string._strRep;
}

