/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/



#ifndef _CLIENTINTERFACE_H_
#define _CLIENTINTERFACE_H_
#include <ostore/hdrstart.hh>

/* client.hh: Primary header file for ObjectStore applications:
basic data structures, exceptions, etc. */

/* NOTE: All functions whose names start with underscores are for
ObjectStore's internal use only, and should not be used by
applications.  The only reason that they aren't "private" is that this
would require an unwieldy number of "friend" declarations. */

#include <ostore/portypes.hh>
#include <ostore/except.hh>
#include <ostore/nclient/os_sess.hh>
#include <ostore/nclient/errors.hh>
#include <ostore/nclient/objstore.hh>
#include <ostore/nclient/database.hh>
#include <ostore/nclient/seg_acc.hh>
#include <ostore/nclient/segment.hh>
#include <ostore/nclient/cluster.hh>
#include <ostore/nclient/typespec.hh>
#include <ostore/nclient/schema_han.hh>
#include <ostore/nclient/root.hh>
#include <ostore/nclient/persnew.hh>
#include <ostore/nclient/objcurs.hh>
#include <ostore/nclient/server.hh>
#include <ostore/nclient/ref.hh>
#include <ostore/nclient/notify.hh>
#include <ostore/nclient/transact.hh>
#include <ostore/nclient/fault.hh>
#include <ostore/nclient/asmarker.hh>
#include <ostore/nclient/retaddr.hh>
#include <ostore/nclient/softptr.hh>
#include <ostore/nclient/objcount.hh>
#include <ostore/nclient/pttp_mgr.hh>

/* Runtime support for the debugger. */
extern "C" void _Debugger_simulate_segv(os_unsigned_int32 address, os_int32 length, os_boolean for_write);


#include <ostore/hdrend.hh>
#endif /* _CLIENTINTERFACE_H_ */
