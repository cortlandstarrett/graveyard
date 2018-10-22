/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CLIENT_PTTP_MGR_HH_
#define _CLIENT_PTTP_MGR_HH_

/* This abstract class is a base class for user-defined classes
   that manage transient objects pointed to by persistent objects.
   Users must define a release method in their derived class.
*/

class os_persistent_to_transient_pointer_manager {
public:
  virtual void release(void* pointer) = 0;

protected:
  os_persistent_to_transient_pointer_manager() { }

  virtual ~os_persistent_to_transient_pointer_manager() { }
};
#endif
