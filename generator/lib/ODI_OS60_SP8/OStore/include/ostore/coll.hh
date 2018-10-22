/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OS_COLLECTION_H_
#define _OS_COLLECTION_H_
#include <ostore/hdrstart.hh>

/* User compilation environment for collections. */

#include <ostore/coll/coll.hh>
#include <ostore/coll/set.hh>
#include <ostore/coll/bag.hh>
#include <ostore/coll/list.hh>
#include <ostore/coll/array.hh>
#include <ostore/coll/cursor.hh>
#include <ostore/coll/ixonly.hh>


#if !defined(OS_NO_COLLECTION_TEMPLATES)
#include <ostore/coll/coll_pt.hh>
#include <ostore/coll/set_pt.hh>
#include <ostore/coll/bag_pt.hh>
#include <ostore/coll/list_pt.hh>
#include <ostore/coll/array_pt.hh>
#include <ostore/coll/cursorpt.hh>
#include <ostore/coll/nlist.hh>
#endif

#include <ostore/coll/indexkey.hh>

#include <ostore/coll/query.hh>
#include <ostore/coll/qrun.hh>

#include <ostore/coll/backptr.hh>
#include <ostore/coll/bplist.hh>
#include <ostore/coll/iname.hh>
#include <ostore/coll/fntab.hh>
#include <ostore/coll/idxmaint.hh>
#include <ostore/coll/path.hh>

#include <ostore/hdrend.hh>
#endif









