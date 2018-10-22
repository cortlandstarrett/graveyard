/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef CLIENT_INTERFACE_RPC_ERR
#define CLIENT_INTERFACE_RPC_ERR

#include <ostore/hdrstart.hh>

/* rpc_err.hh: External declarations of TIX exception classes for RPC errors. */
/* Before including this file, you must include ostore/tix.hh and
ostore/except.hh.  They are not included here because we want
to minimize the number of levels of include, so that users won't run
into cpp's limit. */

_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_success);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_cantencodeargs);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_cantdecoderes);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_cantsend);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_cantrecv);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_timedout);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_versmismatch);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_autherror);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_progunavail);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_progversmismatch);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_procunavail);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_cantdecodeargs);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_systemerror);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_unknownhost);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_unknownproto);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_pmapfailure);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_prognotregistered);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_failed);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_auth_ok);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_auth_badcred);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_auth_rejectedcred);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_auth_badverf);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_auth_rejectedverf);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_auth_tooweak);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_auth_invalidresp);
_OS_DECLARE_EXCEPTION(_OS_LOWNET,err_rpc_auth_failed);

#include <ostore/hdrend.hh>

#endif /* CLIENT_INTERFACE_RPC_ERR */
