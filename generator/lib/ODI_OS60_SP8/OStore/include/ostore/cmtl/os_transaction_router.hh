/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _CMTL_INTERFACE_TRANSACTION_ROUTER_HH_
#define _CMTL_INTERFACE_TRANSACTION_ROUTER_HH_

#include <ostore/cmtl/os_txn_ctx.hh>

class _OS_DLLIMPORT(_OS_CMTL) os_transaction_router : public os_cmtl_object {
public:
    virtual os_cache *choose_cache(const os_transaction_context &transaction_context) = 0;
    virtual ~os_transaction_router() { /* empty */ }
};

#endif // end of #ifndef _CMTL_INTERFACE_TRANSACTION_ROUTER_HH_


