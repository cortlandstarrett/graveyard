/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_TYPESPEC
#define CLIENT_INTERFACE_TYPESPEC

#include <ostore/hdrstart.hh>
#include <ostore/portypes.hh>
#include <ostore/os_types/paddef.hh>

class os_database;

/* ObjectStore Type Specifier class - holds a name for a type
 * This is a facade class for _Pvts
 * Unlike most facade classes, it has constructors rather than being
 * instantiated by factory methods, and has data members
 * This is for API compatibility with past versions of ObjectStore
 */
class _OS_DLLIMPORT(_OS_CLIENT) os_typespec {
public:						/* PUBLIC FUNCTION MEMBERS */
  /* 'Structors and assignment operator */
  os_typespec(const char* typespec);
  os_typespec(const os_typespec& os_typespec_arg);
  void operator=(const os_typespec& os_typespec_arg);
  ~os_typespec();

  /* Accessor */
  const char* get_name() const;
  os_unsigned_int32 get_vector_padding_size(os_database *db);
  os_unsigned_int32 get_alignment_bytes(os_database *db);
  
  /* Comparison */
  os_boolean operator==(const os_typespec& os_typespec_arg) const;
  os_boolean name_is(const char *name_arg) const;

  /* Can be persistent, e.g. for os_database_root */
  static os_typespec* get_os_typespec();

  /* os_typespecs for the predefined types */
  static os_typespec* get_char();
  static os_typespec* get_short();
  static os_typespec* get_int();
  static os_typespec* get_long();
  static os_typespec* get_float();
  static os_typespec* get_double();
  static os_typespec* get_long_double();
  static os_typespec* get_pointer();

  /* signed integral types */
  static os_typespec* get_signed_char();
  static os_typespec* get_signed_short();
  static os_typespec* get_signed_int();
  static os_typespec* get_signed_long();

  /* unsigned integral types */
  static os_typespec* get_unsigned_char();
  static os_typespec* get_unsigned_short();
  static os_typespec* get_unsigned_int();
  static os_typespec* get_unsigned_long();

  /* portable types */
  static os_typespec* get_os_unsigned_int8();
  static os_typespec* get_os_signed_int8();
  static os_typespec* get_os_unsigned_int16();
  static os_typespec* get_os_int16();
  static os_typespec* get_os_unsigned_int32();
  static os_typespec* get_os_int32();
  static os_typespec* get_os_unsigned_int64();
  static os_typespec* get_os_int64();

protected:					/* PRIVATE DATA MEMBERS */
  char* typespec;				/* Name of type */
  os_pad_ptr8(typespec)
  os_unsigned_int32 type_number;		/* get_tag cache */
  char _os_pad_1[4];
};

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_TYPESPEC */
