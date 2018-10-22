/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _PREF_SCHM_H
#define _PREF_SCHM_H

#include <ostore/mop.hh>

/***************************************************************************
* 									   *
* 									   *
*     	   	os_preferred_schema class				   *
*                                                                          *
* A preferred schema is a schema which contains the set of all the         *
* class definitions which a user prefers to be used when running           *
* osload to load a database.  The preferred schema contains those          *
* types along with those types' base classes, member types, and any        *
* other information needed to create these new type representations.       *
*                                                                          *
* The os_preferred_schema object represents the preferred schema           *
* used by osload during its execution.  There can be only one              *
* preferred schema in use by osload at any time.                           *
* 									   *
***************************************************************************/

class os_preferred_schema 
{
public:

  typedef enum {DatabaseSchema, ApplicationSchema} TreatAs;

  /*
    os_preferred_schema::initialize() creates an instance
    of preferred schema object & initializes the static
    data member p_self.  This function takes the name of 
    the preferred schema & opens the schema DB.
    It must be called before using the preferred schema.
  */

  static void initialize(os_unsigned_int32, // align_and_allow_mismatch
			 const char* work_db_path,
			 const char* pathname = NULL);

  ~os_preferred_schema();

  /*
    os_preferred_schema::get() returns a reference to a
    preferred schema object. There is only one instance
    of the os_preferred_schema object.
  */

  static os_preferred_schema & get();

  const os_type* find_type(const char*) const;
  const os_schema& get_schema() const;
  void merge_schema(os_unsigned_int32, const char*);

private:
  os_database * p_db;
  static os_preferred_schema * p_self;
  os_preferred_schema * p_ps; 
  os_schema * p_os;
  os_retain_address save_p_os;
  void set_schema(os_schema *ps) { p_os = ps;}
  os_preferred_schema(const char*, TreatAs);
  os_preferred_schema();
};

#endif	/* _PREF_SCHM_H */

