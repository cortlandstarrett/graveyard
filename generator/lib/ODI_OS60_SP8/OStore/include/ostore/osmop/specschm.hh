/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_SPECIAL_SCHEMA_HDR_
#define _OS_SPECIAL_SCHEMA_HDR_
#include <ostore/hdrstart.hh>

class os_schema;
class os_member_function;

/* Definitions for DEC C++. */
typedef os_member_function const& os_member_function_const_r;

typedef void (*os_special_schema_error_callback)
   	     (os_char_const_p error_message,
   	      os_int32 /* really os_special_schema::error_kind */ error_kind);
   
typedef os_char_p (*os_special_schema_discriminant_callback)
		  (os_member_function_const_r mf);

class os_special_schema {

 /**
  ** This class provides support for generating compilation schemas.
  ** This class is not instantiable and serves as a name scope only.
  **/

 public:

  /**
   ** This must be called before using any other functions on this class.
   **/
  static void initialize();

  /**
   ** This updates the named compilation schema with the contents of
   ** the schema specified as the second argument.  The target schema
   ** is created if it does not already exist.
   **
   ** This function must be called from within an update transaction.
   ** If any errors occur, this function will abort the transaction.
   **
   ** In the current implementation, the source schema must be the
   ** current transient comp schema.  All errors and warnings are
   ** reported through the error callback.
   **/
  static void update (const char* source_file_name,
		      const char* target_compilation_schema_db_name,
		      const os_schema& source_schema);

  /**
   ** These values are passed to the error callback function.
   ** The meanings are:
   **	warning		Informative messages that do not prevent
   **			the schema from being updated.
   **	error		Processing can proceed, but the mop will
   **			force the transaction to abort before any
   **			schema updates occur.
   **	fatal		Processing cannot proceed.  If the error
   **			callback returns, the mop will terminate
   **			the process.
   **/
  enum error_kind { none, warning, error, fatal, error_kind_pad = 1<<30 };

  /**
   ** Error callback interface
   ** The callback is used to report all schema update errors and warnings.
   **/
  static
  os_special_schema_error_callback get_error_callback();
  static
  void set_error_callback(os_special_schema_error_callback f);

  /**
   ** Discriminant callback interface
   ** The callback is used to determine the link name of all
   ** discriminant functions.  The result returned by the callback
   ** should be a zero terminated string allocated using new.
   **/
  static
  os_special_schema_discriminant_callback get_discriminant_callback();
  static
  void set_discriminant_callback(os_special_schema_discriminant_callback f);

 private:

   /**
    ** This private constructor prevents instantiation.
    **/
   os_special_schema() {};
};

#include <ostore/hdrend.hh>
#endif	/*--- ndef _OS_SPECIAL_SCHEMA_HDR_ ---*/
