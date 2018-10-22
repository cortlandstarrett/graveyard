/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _DLL_FNDR_HH_
#define _DLL_FNDR_HH_
#include <ostore/hdrstart.hh>

#include <ostore/portypes.hh>


/* Base class for DLL Identifier prefix handler classes */
/* This is not a persistent object */
class _OS_DLLIMPORT(_OS_CLIENT) os_DLL_finder {
public:
  /* Functions that must be provided by a subclass */
  virtual os_DLL_handle load_DLL(const char* DLL_identifier,
                                 os_boolean error_if_not_found) = 0;
  virtual os_boolean equal_DLL_identifiers_same_prefix
		(const char* id1, const char* id2) = 0;

  /* Registration functions provided by the base class */
  void register_(const char* prefix);
  void unregister(const char* prefix);
  static os_DLL_finder* get(const char* DLL_identifier);

  /* Function that users can call */
  static os_boolean equal_DLL_identifiers(const char* id1, const char* id2);

protected:
  /* Xstructors of this abstract base class are protected */
  os_DLL_finder();
  virtual ~os_DLL_finder();
};

/* To inform ObjectStore how to understand a DLL prefix, create an instance of
 * a subclass of os_DLL_finder and call its register member function with the
 * prefix string.  Be sure to unregister the prefix before deleting the 
 * instance.  It is customary for each subclass of os_DLL_finder to know the
 * prefix that it implements and have a constructor and destructor that call
 * register_ and unregister respectively.  It is NOT permitted to register a
 * DLL finder from a static constructor; call objectstore::initialize first.
 *
 * register_ has that name because register is a reserved word.
 */

#include <ostore/hdrend.hh>
#endif /* _DLL_FNDR_HH_ */
