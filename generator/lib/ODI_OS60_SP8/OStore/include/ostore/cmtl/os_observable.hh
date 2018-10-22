/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_OS_OBSERVABLE_HH_
#define _CMTL_INTERFACE_OS_OBSERVABLE_HH_

#include <ostore/cmtl/common.hh>

class os_observable;

class _OS_DLLIMPORT(_OS_CMTL) os_observer {
 public:
    virtual void update(os_observable *obs, os_cmtl_object *arg) = 0;
    virtual os_boolean operator==(const os_observer &other) const = 0;
};

// Simmilar to Java's Observable class.
class _OS_DLLIMPORT(_OS_CMTL) os_observable : public os_cmtl_object {
 public:
    virtual void add_observer(os_observer *obj) = 0;
    virtual void delete_observer(os_observer *obj) = 0;
    virtual void delete_observers() = 0;
    virtual void clear_changed() = 0;
    virtual os_boolean has_changed() = 0;
    virtual void notify_observers(os_cmtl_object *arg) = 0;
    virtual int count_observers() = 0;
    virtual void set_changed() = 0;
    virtual ~os_observable() { /* empty */ }
};

#endif // end of #ifndef _CMTL_INTERFACE_OS_OBSERVABLE_HH_


