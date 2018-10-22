/*========================================================================
 *
 * File:      $RCSfile: u_elm.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:33 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
/* Note: This slm.h taken from Elm-5.0.5 for Windows */

/*
 * $Id: u_elm.hh,v 1.9 2013/01/10 23:41:33 rmulvey Exp $ - Elan Computer Group, Inc. (c) 1997
 *
 * Copyright (c) 1989-2013 Mentor Graphics CorporationMentor Graphics CorporationMentor Graphics CorporationMentor Graphics CorporationMentor Graphics CorporationElan Computer Group, Inc.
 * All Rights Reserved.
 *
 * This is unpublished proprietary source code of Elan Computer Group, Inc.
 * The copyright notice above does not evidence any actual
 * or intended publication of such source code.
 */

#ifndef _SLM_H
#define _SLM_H

/* Borland */
#if (defined (__BORLANDC__) || defined (_Windows)) && !defined(_WINDOWS) && !defined(_DOS)
#   define _WINDOWS
#endif

/* Borland */
#if defined (__WIN32__) && !defined(WIN32)
#   define WIN32
#endif

#if defined(NETWARE) && defined(__WATCOMC__)
#include "nwmacro.h"
#endif /* NETWARE && __WATCOMC__ */

#ifndef vms 
#  ifndef _WINDOWS
#    ifndef NETWARE
#      ifndef _DOS
#        ifndef WIN32
#          ifndef NETBIOS
#            define UNIX
#          endif
#        endif
#      endif
#    endif
#  endif
#endif

#ifdef _WINDOWS
#  include <windows.h>
#endif

#include <stdio.h>
#ifdef vms
#  include <types.h>
#else
#  ifdef SVR3
#    define _XOPEN_SOURCE
#    define _POSIX_SOURCE
#    define _SYSV3
#    if defined(M88K) || defined(SGI)
#    include <netinet/types.h>
#    endif
#  endif
#  ifdef BSDTYPES
#       include <sys/bsdtypes.h>
#  endif
#  include <sys/types.h>
#  if !defined(NEXT) && !defined(APOLLO) 
#    if defined(UNIX)
#      include <unistd.h>
#    endif
#  endif
#endif
#include <stdlib.h>
#include <string.h>
#ifdef _WINDOWS
#include <time.h>
#endif

#ifdef NETWARE
#  ifdef NETWARE_NLM
#    define FAR
#  endif
#  ifdef WIN32
#    ifdef WINSOCK
#      define PASCAL __stdcall
#    else
#      define PASCAL
#    endif
#    define API
#    define NWFAR
#    define NWPASCAL
#  endif
#  ifndef _WINDOWS
#    define FAR
#  endif
#endif

#ifdef WIN32
#  ifndef FAR
#    define FAR
#  endif
#endif

#if defined (UNIX) 
#  define FAR
#  define API
#  define NWFAR
#  define NWPASCAL
#endif

#if defined(_DOS) && !defined(NETWARE)
#  define FAR
#  define API
#  define NWFAR
#  define NWPASCAL
#endif

#define SLM_KEYFILE_MAGIC    "!<Elan-License-Manager-Key>"
#define SLM_DATAFILE_MAGIC   "!<Elan-License-Manager-Data>"

/*
 * Values returned from SLM routines...
 */
#define SLM_OK                         0
#define SLM_ERROR                    (-1)
#define SLM_WAIT                     (-2)
/* SLM 2.2: SLM_FAIL renamed SLM_NO_LICENSES */
#define SLM_NO_LICENSES              (-3)
#define SLM_SRV_DOWN                 (-4)
#define SLM_AUTH_FAIL                (-5)
#define SLM_EXPIRED                  (-6)
#define SLM_NOHOST                   (-7)
#define SLM_SOCKFAIL                 (-8)
#define SLM_SENDFAIL                 (-9)
#define SLM_LOST                     (-10)
#define SLM_NOKEY                    (-11)
#define SLM_NOT_LICENSED             (-12)
#define SLM_NO_SERVICE               (-13)
#define SLM_CODE_CORRUPT             (-14)
#define SLM_NO_SUCH_FEATURE          (-15)
#define SLM_INVALID_CLIENT           (-16)
#define SLM_INSUFFICIENT_SERVERS     (-17)
#define SLM_CANT_WRITE               (-18)
#define SLM_CANT_READ                (-19)
#define SLM_SYS_NOPRIV               (-20)    /* Internal used only */
#define SLM_SUICIDE                  (-21)    /* Internal used only */
#define SLM_INVALID_DOMAIN           (-22)
#define SLM_INVALID_NLIC             (-23)
#define SLM_INVALID_FEATURE          (-24)
#define SLM_INVALID_VENDORDATA       (-25)
#define SLM_INVALID_STARTDATE        (-26)
#define SLM_INVALID_EXPIRATION       (-27)
#define SLM_INVALID_SERVERCOUNT      (-28)
#define SLM_INVALID_ARG              (-29)
#define SLM_CANT_ENCRYPT             (-30)
#define SLM_EARLY                    (-31)
#define SLM_BADDATE                  (-32)
#define SLM_INSUFFICIENT_LICENSES    (-33)
#define SLM_SDIO                     (-34)
#define SLM_SDKCHSM_NOTFOUND         (-35)
#define SLM_SDCODE_CORRUPT           (-36)
#define SLM_SDCANT_OPEN              (-37)
#define SLM_SDCANT_READ              (-38)
#define SLM_SDCANT_WRITE             (-39)
#define SLM_CANT_CREATE              (-40)
#define SLM_CANT_OPEN                (-41)
#define SLM_CANT_STAT                (-42)
#define SLM_BAD_HOSTCODETAG          (-43)
#define SLM_BAD_SECURITYTAG          (-44)
#define SLM_FILTERED                 (-45)
#define SLM_UNIX_ONLY_KEY            (-46)
#define SLM_PC_ONLY_KEY              (-47)
#define SLM_INVALID_INSTANCE         (-48)
#define SLM_LOGTAG_CORRUPT           (-49)
#define SLM_CANT_DECRYPT             (-50)
#define SLM_INVALID_OPERATOR         (-51)
#define SLM_DUPLICATE_PACK           (-52)
#define SLM_SD_NOT_ENABLED	     (-53)

#define SLM_NUMERROR                   53 

/*
 * Commands for slm_control...
 */
#define SLMC_ZEROLOG            1    /* Zero log file */
#define SLMC_DIE                2    /* Kill slmd */
#define SLMC_VERBOSE            3    /* Change message verbosity */
#define SLMC_DUMP               4    /* Cause slmd to dump system tables */
#define SLMC_SETVERSION         5    /* Set version for encryption type */
#define SLMC_SETKEYDIR          6    /* Set local keydir, like -e to slmd */
#define SLMC_SETHOLD            7    /* Set license hold time */
#define SLMC_SETBROADCAST       8    /* Set broadcast scope */
#define SLMC_BURYCLIENT         9    /* Bury a client */
#define SLMC_SETZOMBIE          10   /* Set time at which client is zombie */
#define SLMC_LOG                11   /* Copy message to log */
#define SLMC_LOG_WITH_DATE      12   /* Copy message to log w/ time stamp */
#define SLMC_LOG_WITH_DATE_USER 13   /* Copy message to log w/ time/user */
#define SLMC_HEARTBEAT_IO       14   /* Use select or non-blocking I/O */
#define SLMC_GETHOLD            15   /* Get license hold time */
#define SLMC_GET_VERBOSITY      16   /* Get current verbosity level */
#define SLMC_LOADKEYS           17   /* Scan keydirs and load any new keys */
#define SLMC_NEXT_FEATURE       18   /* Next feature available */
#define SLMC_GETLOGFILE         19   /* Get log file path -l to slmd */
#define SLMC_SLMD_RELEASE       20   /* Get slmd release string */
#define SLMC_SETHOLDBY          21   /* Set license hold by */
#define SLMC_GETHOLDBY          22   /* Get license hold by */

#define SLM_SW_FIRST_FEATURE    1000
#define SLM_SW_MAX_FEATURE      9999

/*
 * Putdata/getdata options...
 */
#define SLM_NOHEADER    1L
#define SLM_REMOVE      2L

/*
 * Arguments to SLMC_HEARTBEAT_IO:
 */
#define    SLM_USE_NON_BLOCKING_IO  ((long)(1))
#define    SLM_USE_SELECT           ((long)(2))

/*
 * Key types, set via slm_control (SLMC_SETVERSION, arg)...
 */
#define SLM_STDKEY_VERSION      'C'        /* Standard key Version */
#define SLM_NUMKEY_VERSION1     'D'        /* Before redundant servers */
#define SLM_NUMKEY_VERSION2     'E'        /* SLM Release 2.0-2.3 */
#define SLM_NUMKEY_VERSION3     'F'        /* SLM Release 4.0 */
#define SLM_NUMKEY_VERSION4     'G'        /* SLM Release 4.1,4.2 */
#define SLM_NUMKEY_VERSION      'H'        /* SLM Release 5.0 */
#define SLM_VALID_VERSIONS      "HGFEDCBA@" /* Legal key versions */

#define SLM_CRYPT_GEN           '@'

#define is_slm_numkey_version(v)  ((v) >= SLM_NUMKEY_VERSION1 && (v) <= SLM_NUMKEY_VERSION)
#define is_slm_redkey_id(v)       ((v) == '1' || (v) == '2')

#define SLM_ENCRYPT         0L
#define SLM_ENCODE          0L

#define SLM_DECRYPT         1L
#define SLM_DECODE          1L

#define SLM_GETKEYFILE      0L
#define SLM_PUTKEYFILE      1L

#define SLM_LOGTAG_SEQMOD   100000L

#ifdef PIPES
#define SLMD_RESOURCE_TYPE 12345
#define SLMD_RESOURCE_NAME "slmd"
#endif

/*
 * Client <-> daemon packet versions
 *
 * Versions prior to 2.1 were the current key type, either C, D, or E.
 *
 * Ver    Description
 * ---    -----------
 * F    Does not use the port number in the encryption routines.
 */
#define SLM_VERSION_F        'F'            /* Release 2.1 */
#define SLM_VERSION_G        'G'            /* Release 4.1 */
#define SLM_VERSION_ID       SLM_VERSION_G  /* CURRENT VERSION */
#define SLMD_VALID_VERSIONS  "GFEDC"        /* Versions slmd will accept */

#define crypt_use_port(v)    ((v) != SLM_VERSION_F && (v) != SLM_VERSION_G)

/*
 * Second argument to slm_gencode() and slm_hostid() ...
 * Max value is -1L=37777777777(oct)=ffffffff(hex)
 */
#define SLM_HOSTCODE_IDPROM_MASK    000000000077L
#define SLM_HOSTCODE_IPADDR         000000000100L      /* Use network Address */
#define SLM_HOSTCODE_IDPROM_BIT     000000000200L

#define SLM_HOSTCODE_IDPROM(n)      (SLM_HOSTCODE_IDPROM_BIT|((n) > 077 ? 077:n))

#define SLM_HOSTCODE_IDPROM2        (SLM_HOSTCODE_IDPROM_BIT|2)   /* For DEC */

#define SLM_HOSTCODE_IDPROM_NUM(v)  (v & SLM_HOSTCODE_IDPROM_MASK)

#define SLM_HOSTCODE_HOSTNAME       000000000400L      /* Use hostname */
#define SLM_HOSTCODE_ETHER          000000001000L      /* Ethernet address */
#define SLM_HOSTCODE_HISECURE       000000002000L      /* Extended Redundant Key */
#define SLM_HOSTCODE_DISKID_BIT    (000000004000L)
#define SLM_HOSTCODE_DISKID_MASK    000000070000L
#define SLM_HOSTCODE_DISKID(n) \
    (((((n) >= 8 ? 7:((n)-1))<<12) & SLM_HOSTCODE_DISKID_MASK ) | \
    SLM_HOSTCODE_DISKID_BIT)
#define SLM_HOSTCODE_DISKID_NUM(v)  ((((v) >> 12) & 07) + 1)
#define SLM_HOSTCODE_NWSERIALNUM    000000100000L      /* Netware serial number */
#define SLM_HOSTCODE_VENDORHOSTID   000000200000L      /* Vendor host id */

#define SLM_HOSTCODE_DONGLEID_BIT   000000400000L
#define SLM_HOSTCODE_DONGLEID(n) \
    ((((n)>=16?15:((unsigned long)(n)-1))<<18) | SLM_HOSTCODE_DONGLEID_BIT)
#define SLM_HOSTCODE_DONGLEID_NUM(v) ((((v)>>18) & 0xf) + 1)

#define SLM_HOSTCODE_DONGLESERIALNUM  000020000000L
#define SLM_HOSTCODE_SECURITYDEVICE   000020000000L
            

#ifdef vms
#  define SLM_HOSTCODE_STANDARD    (SLM_HOSTCODE_ETHER)
#else
#  define SLM_HOSTCODE_STANDARD    (SLM_HOSTCODE_IPADDR|SLM_HOSTCODE_IDPROM2)
#endif

#define SLM_HOSTCODE_DEFAULT    0L

/*
 * Dongle types
 */
typedef enum slm_dongle_model {
        SLM_DONGLE_SPRO=1,
        SLM_DONGLE_MSU=2
} slm_dongle_model_t;

/*
 * Second argument to slm_getlicense...
 */
#define SLM_GETLIC       0000L        /* Get a license */
#define SLM_QUEUE        0121L        /* Enter into queue (was 'Q') */
#define SLM_GETQUEUED    0103L        /* Get from queue (was 'C') */

/*
 * "or" these in with any of the above
 */
#define SLM_SHARED           0040L
#define SLM_COUNT            0010L
#define SLM_unusedbit2       0004L
#define SLM_SHARE_USER      (001L << 8)
#define SLM_SHARE_HOST      (002L << 8)
#define SLM_SHARE_DISPLAY   (004L << 8)

/*
 * For SLMC_SETHOLDBY
 */
#define SLM_HOLDBY_USER     (001L)
#define SLM_HOLDBY_HOST     (002L)
#define SLM_HOLDBY_DISPLAY  (004L)

/*
 * All option bits in getlicense second argument...
 */
#define SLM_GLOPTMASK    (SLM_SHARED|SLM_COUNT|SLM_unusedbit2|SLM_SHARE_USER|SLM_SHARE_HOST|SLM_SHARE_DISPLAY)

#define SLM_UNQUEUE          0125L        /* Dequeue (was 'U') */

/*
 * Options to slm_retlicense...
 */

#define SLM_DECR(n)        (0001L | ((unsigned long)((n) & 0xffff) << 16))
#define SLM_DECR_VAL(n)    (((n) >> 16) & 0xffff)

/*
 * Options to slm_genkey/slm_genredkey...
 */
#define SLM_STDKEY          (long)000
#define SLM_STDKEYS         SLM_STDKEY
#define SLM_SHORTKEYS       (long)001
#define SLM_LITERAL_HOSTIDS (long)002
#define SLM_LITERAL_KEY     (long)004
#define SLM_MOD_KEY	    (long)005

#define SLM_MASTER        1
#define SLM_SHADOW        2
#define SLM_NO_MASTER     3

/*
 * Maximum length of various strings.
 * These are true lengths, so a null terminated string
 * buffer should be declared [LEN+1] long.
 */
#define SLM_USER_LEN            10
#define SLM_HOST_LEN            64
#define SLM_DISPLAY_LEN         64
#define SLM_IPADDR_LEN          32
#define SLM_GROUP_LEN           20
#define SLM_FEATURE_LEN         32
#define SLM_DATETAG_LEN         256
#define SLM_HOSTCODETAG_LEN     256
#define SLM_NUMFEATURE_MINLEN   2
#define SLM_NUMFEATURE_MAXLEN   12
#define SLM_ALIAS_LEN           SLM_FEATURE_LEN
#define SLM_VERSION_LEN         8
#define SLM_KEYDIR_LEN          80
#define SLM_CODE_LEN            100
#define SLM_KEY_LEN             200
#define SLM_HOSTID_LEN          128
#define SLM_VENDORDATA_LEN      (SLM_GROUP_LEN+SLM_USER_LEN+SLM_DISPLAY_LEN)
#define SLM_PATHLEN             126
#define SLM_DATA_LEN            300
#define SLM_VFIELD_LEN          64
#define SLM_SALT_LEN            256
#define SLM_PREFIX_LEN          8
#define SLM_NETBIMC_DBMS_NAME_LEN    16
#define SLM_NETADDR_LEN		SLM_NETBIMC_DBMS_NAME_LEN	/* MAX of IP, IPX, NETBIOS */
#define SLM_MESSAGE_LEN         126
#define SLM_LOGTAG_LEN          32

#define SLM_MAX_REDUNDANT_SERVERS 31

#define SLM_MAX_HOSTCODES       16
#define SLM_NO_SOFTLIMIT        0L
#define SLM_UNLIMITED_LICENSES  0xfffffffL
#define SLM_UNLIMITED_NODELCK_LICENSES -0xfffffffL

#define SLM_MULTIKEY_MAXNUMFEAT 11  /* Max number of features in a Multi-Key */
#define SLM_MULTIKEY_FEATMAXLEN  8  /* Max digits in a feature in a Multi-Key */

/* ------------------- License Pack stuff ------------------ */

/*
 * License Pack Types and ID length
 */
#define SLM_LICPAK_NOT		0	/* Not a license pack, Wayne */
#define SLM_LICPAK_MASK		077	/* Digits used in pack type */
#define SLM_LICPAK_PACK		001	/* License Pack */
#define SLM_LICPAK_MOD		002	/* Modify Pack */
#define SLM_LICPAK_REPL		004	/* Replacement Pack */
#define SLM_LICPAK_IDLEN	9	/* LicPak ID length */

#define slm_licpak_to_letter(n)	((n == SLM_LICPAK_PACK) ? 'P': ((n == SLM_LICPAK_REPL) ? 'R':'M'))

#define slm_pakpart(type)	((type) & SLM_LICPAK_MASK)
#define slm_is_anypak(type)	(slm_pakpart(type) != 0)
#define slm_is_licpak(type)	(slm_pakpart(type) == SLM_LICPAK_PACK)
#define slm_is_modpak(type)	(slm_pakpart(type) == SLM_LICPAK_MOD)
#define slm_is_replpak(type)	(slm_pakpart(type) == SLM_LICPAK_REPL)

/*
 * License Pack modkey operators
 * These are bit fields so that we can use more than one at a time.
 */
#define SLM_MODPAK_VDATA	00001	/* Modify Vendor Data */
#define SLM_MODPAK_EXPIRATION	00002	/* Modify Expiration */
#define SLM_MODPAK_START	00004	/* Modify Start Date */
#define SLM_MODPAK_DOMAIN	00010	/* Modify Domain */

#define slm_is_modpak_vdata(type)	(type & SLM_MODPAK_VDATA)
#define slm_is_modpak_expiration(type)	(type & SLM_MODPAK_EXPIRATION)
#define slm_is_modpak_start(type)	(type & SLM_MODPAK_START)
#define slm_is_modpak_domain(type)	(type & SLM_MODPAK_DOMAIN)

/* License Pack Epoch August 6, 1996 */
#define SLM_LICPAK_EPOCH   839371229L

/*
 * License Pack Constraint
 */
#define SLM_MAX_ARGLEN		14
#define SLM_MAX_CONSTRAINTS	6

typedef struct slm_constraints
{
        unsigned char field;
        unsigned char op;
        char arg[SLM_MAX_ARGLEN+1];
} slm_constraints_t;

typedef slm_constraints_t *SLM_CONSTRAINTS;

/*
 * Fields...
 */
#define SLM_CONSTRAINT_EOL              0       /* End-Of-List */
#define SLM_CONSTRAINT_START_DATE       1
#define SLM_CONSTRAINT_EXPIRATION       2
#define SLM_CONSTRAINT_DOMAIN           3
#define SLM_CONSTRAINT_VENDORBIT        0200
#define SLM_CONSTRAINT_VENDOR(name)     (slm_vendorfield_id(name) | SLM_CONSTRAINT_VENDORBIT)

/*
 * Operators for getlicense CONSTRAINTS and MOD keys.
 */
#define SLM_ANY		0		/* Match anything */
#define SLM_LT          1
#define SLM_LE          2
#define SLM_EQ          3
#define SLM_GE          4
#define SLM_GT          5
#define SLM_MEMBER      6
#define SLM_CONTAINS    7
#define SLM_MIN         8		/* Reserved: No implementation yet */
#define SLM_MAX         9		/* Reserved: No implementation yet */

/*
 * --------------------- END OF LICENSE PACKS ---------------------------
 */

/*
 * Convenient constants...
 */
#define SLM_EPOCH   599616000L    /* Jan 1, 1989 00:00 GMT */
#define SLM_MAXKEYDATE  (SLM_EPOCH+(9999*SLM_DAY))
#define SLM_MINUTE  (60L)        /* # of seconds in a minute */
#define SLM_HOUR    (60L*SLM_MINUTE)/* # of seconds in an hour */
#define SLM_DAY     (24L*SLM_HOUR)    /* # of seconds in a day */

/*
 * Non-network version code prefix
 */
#define SLM_NNCHR   '#'

/*
 * Collection file line types
 */
#define SLM_COLLECT_UNKNOWN     -1
#define SLM_COLLECT_COMMENT     1
#define SLM_COLLECT_ALIAS       2
#define SLM_COLLECT_SERVER      3
#define SLM_COLLECT_FEATURE     4
#define SLM_COLLECT_VERSION     5
#define SLM_COLLECT_KEY		6

typedef void FAR * SLM_INSTANCE;
typedef long SLM_CONNECTION;

            
/*
 * Netware server type for SAP requests, registered with Novell.
 * Use this value for demos.  Customers must register their own 
 * to avoid conflicts.
 */            
#ifdef NETWARE
#define SLM_NWSERVERTYPE     0x0810  
#endif


struct slm_vfields
{
    char *field;	/* Field name, such as "release" */
    int length;		/* Length in characters */
    int visible;	/* TRUE: Field shown in user reports (like elmadmin) */
};

struct slm_server
{
    long	    licenses;
    long            numpeers;
    time_t          time_remaining;
    char            host[SLM_HOST_LEN+1];
    char            status;
    char	    s_netaddr[SLM_NETADDR_LEN+1];
};

typedef struct slm_keyentry
{
    long  numservers;
    char key[SLM_KEY_LEN+1];
    char alias[SLM_ALIAS_LEN+1];
    char version[SLM_VERSION_LEN+1];
    char date_tag[SLM_DATETAG_LEN+1];
    char hostcode_tag[SLM_HOSTCODETAG_LEN+1];
    char servers[SLM_MAX_REDUNDANT_SERVERS+1][SLM_HOST_LEN+1];
} slm_keyentry_t;

typedef struct slm_keydata
{
    long    nlic[SLM_MULTIKEY_MAXNUMFEAT];
    long    soft_nlic[SLM_MULTIKEY_MAXNUMFEAT];
    long    licpak_id;		 /* Generation date from slm_licpak_id() */
    long    server_count;        /* Number of codes, 1 per server */
    long    multikey;            /* Number of nlic entries */
    long    resource_attached;   /* Autoload feature.res */
    long    licpak_type;	 /* LicPak type: SLM_LICPAK_PACK, _MOD, _REPL */
    long    test_what;
    long    test_op;		 /* Operator, >, >=, ... */
    long    replace_what;
    long    test_vd_start;
    long    test_vd_length;
    long    replace_vd_start;
    long    replace_vd_length;
    time_t  start_date;
    time_t  expiration;
    time_t  test_start_date;
    time_t  test_expiration;
    char    feature[SLM_FEATURE_LEN+1];
    char    code[SLM_MAX_REDUNDANT_SERVERS+1][SLM_CODE_LEN+1];
    char    vendordata[SLM_VENDORDATA_LEN+1];
    char    domain;
    char    test_domain;
    char    test_vdata[SLM_VENDORDATA_LEN+1];
} slm_keydata_t;

typedef struct slm_hostinfo
{
    long    num_idprom;
    long    num_diskid;
    long    num_dongleid;
    char FAR *   ipaddr;
    char FAR *   hostname;
    char FAR *   idprom;
    char FAR *   ether;
    char FAR *   nwserialnum;
    char FAR *   diskid;
    char FAR *   dongleid;
    char FAR *   dongleserialnum;
    char FAR *   vendorhostid;
} slm_hostinfo_t;

typedef struct slm_hostlockdata
{
    long	hostcode;
    slm_hostinfo_t info;
} slm_hostlockdata_t;


struct slm_featureinfo
{
    long   numlic;          /* Total # of licenses for feature among all Packs */
    long   soft_numlic;     /* Total Soft limit among all Packs */
    long   numresv;         /* Total # of licenses reserved among all Packs */
    long   numresv_for_me;  /* # of licenses reserved for me among all Packs */
    long   inuse_resv;      /* # of reserved licenses in use among all Packs */
    long   inuse_free;      /* # of free pool licenses in use among all Packs */
    long   avail_to_me;     /* # available to me among all Packs */
    time_t         start_date;       /* Earliest start date among all Packs */
    time_t         expiration;       /* Earliest expiration among all Packs */
    time_t         installed;        /* Last installed date */
    char feature[SLM_FEATURE_LEN+1]; /* Feature name */

    /* Information across all packs ... */
    char           alias[SLM_FEATURE_LEN+1];	    /* Alias in 1st Pack */
    char           vendordata[SLM_VENDORDATA_LEN+1];/* Vendor Data if same in all Packs */
    char           domain;           /* Widest Domain among all Packs */
    char           node_locked;      /* Non-zero if all Packs are node locked */
    char           resource_attached;/* Non-zero if any Pack has resource attached */
};

struct slm_packinfo
{
    long  numlic;                          /* Total # of licenses for feature */
    long  soft_numlic;                     /* Soft limit */
    long  numresv;                         /* Total # of licenses reserved */
    long  numresv_for_me;                  /* # of licenses reserved for me */
    long  inuse_resv;                      /* # of reserved licenses in use */
    long  inuse_free;                      /* # of free pool licenses in use */
    long  avail_to_me;                     /* # available to me */
    long  packid_major;			    /* Pack ID, a number 0-99 */
    long  packid_minor;			    /* Pack Split number */
    time_t         start_date;                      /* Date feature starts */
    time_t         expiration;                      /* Date feature expires */
    time_t         installed;                       /* Date feature installed */
    char           feature[SLM_FEATURE_LEN+1];      /* Feature name */
    char           alias[SLM_FEATURE_LEN+1];        /* Feature name alias */
    char           vendordata[SLM_VENDORDATA_LEN+1];/* Optional Vendor Data */
    char           domain;                          /* Domain */
    char           node_locked;                     /* Non-zero if license is node locked */
    char           resource_attached;               /* Autoload feature.res */
};

struct slm_user
{
    long tokens;		/* Number of tokens allocated */
    long pid;                        /* Client's PID */
    long cid;                        /* Client's Elm ID */
    long lid;                        /* Client's License ID */
    long shared;                     /* shared count (0 if not) */
    long packid_major;		    /* License pack ID */
    long packid_minor;		    /* License pack ID */
    SLM_CONNECTION handle;	    /* Client's Handle */
    time_t          start_time;     /* Time started feature */
    time_t          alive_time;     /* Last "alive" time */
    time_t          hold_time;      /* Time to hold to */
    char user[SLM_USER_LEN+1];      /* User name */
    char host[SLM_HOST_LEN+1];      /* Host name */
    char display[SLM_DISPLAY_LEN+1];/* X-11 DISPLAY */
    char group[SLM_GROUP_LEN+1];    /* Group (if a reserved license) */
    char connected;                 /* 'V', 'H', or 'C' */

};

typedef struct slm_requestdata {
    long tokens;
    long cid;
    long lid;        /* negative if queueing */
    char FAR *feature;
    char FAR *user;
    char FAR *host;
    char FAR *display;
} slm_requestdata_t;


#define SLM_NOCONNECTION (SLM_CONNECTION)(-1)

#if defined(C_plusplus) || defined(__cplusplus) || defined (NETWARE)
#  ifndef ANSI_C
#    define ANSI_C
#  endif
/* Note:
 * Only the ANSI standard method (stdarg) of accessing variable arguments is available to the 
 * slmd server running under Netware (as an NLM).
 * The Microsoft C++ compiler (used for Windows and DOS clients of NLM server) also
 * supports only the ANSI method.  The Microsoft C compiler (used for the Windows-native server)
 * supports the UNIX method (varargs), but we are using the C++ compiler for the Netware client(s).
 */
#  ifndef __cplusplus
#    define __cplusplus
#  endif    
#  ifdef NETWARE_NLM
#    define EXTERN  extern
#  else                    
#    define EXTERN  extern "C"
#  endif
#  define SLM_CONST    const
#  define CARGS(args)  args
#else

#  if defined (__GNUC__) || defined(__STDC__) || defined (_WINDOWS) || (defined(__BORLANDC__) && defined(_DOS))
                        /* ANSI-C */
#  if !defined (ANSI_C) && ( !defined (_WINDOWS) || defined (__BORLANDC__))
#    define ANSI_C
#  endif
#  define EXTERN        extern
#  define SLM_CONST     const
#  define CARGS(args)   args

#  else
                        /* K&R C */
#    define EXTERN      extern 
#    define SLM_CONST
#    define CARGS(args) ()
#  endif  
#endif

#ifdef _XtIntrinsic_h
#define XTAPPCONTEXT    XtAppContext
#else
#define XTAPPCONTEXT    void *
#endif

#define SLM_UINT        unsigned int
#define SLM_UCHAR       unsigned char
#define SLM_ULONG       unsigned long

#if defined(_WINDOWS) && !defined(WIN32)
#  define WINDOWS_31
#endif

#ifdef WINDOWS_31
#  define EEXPORT FAR PASCAL  __export
#  define WINSTATIC static
#  define sprintf wsprintf
#elif defined (WIN32)
#  define EEXPORT _stdcall
#  define WINSTATIC
#else
#  define EEXPORT
#  define WINSTATIC
#endif

#if defined (WIN32) && defined (NETWARE)
#  define Dllexport __declspec ( dllexport )
#  define Dllimport __declspec ( dllimport )
#else
#  define Dllexport 
#  define Dllimport
#endif


#if defined ( _WINDOWS) || defined (NETWARE)
EXTERN int EEXPORT    getopt    CARGS((int, char **, char *));
EXTERN char *optarg;
EXTERN int optind;
#endif

#ifdef ANSI_C
#define SLM_NOCALLBACK        ((long (*)(SLM_INSTANCE, SLM_CONNECTION, long))0)
#else
#define SLM_NOCALLBACK        ((long (*)())0)
#endif

/*  Salt file variables 
 */
EXTERN char             slm_host[];
EXTERN long		slm_hostcodes[];
EXTERN char             slm_icon_description[];
EXTERN int              slm_keyaccept;
EXTERN char             slm_keydir[];
EXTERN char             slm_object[];
EXTERN SLM_UINT         slm_port;
EXTERN SLM_UINT         slm_port_salt;
EXTERN char             slm_salt[];
EXTERN unsigned int     slm_nwserver_type;
EXTERN unsigned int     slm_nwsocket;
EXTERN char             slm_service[];
EXTERN char             slm_srelease[];
EXTERN struct           slm_vfields slm_vfields[];
EXTERN int              slm_donglemodels;
EXTERN char *           slm_serialportlocations[];
EXTERN int              slm_dongleinitialized;
EXTERN int              slm_generichostiddongle;
EXTERN int              slm_motiflogowidth;
EXTERN int              slm_motiflogoheight;
EXTERN unsigned char *  slm_motiflogobits;
EXTERN char *           slm_motifversionstring;
EXTERN char *           slm_motifcompanystring;
EXTERN int              slm_skipsecuretagcheck;
EXTERN int              slm_mipsabi_nohexidprom;
#if defined (_WINDOWS) || defined (NETWARE)
EXTERN     char         slm_icon_name[];
#endif
EXTERN long             slmd_zombie_minimum;
EXTERN long             slmd_zombie_default;
EXTERN long             slmd_init_default;
EXTERN int              slmd_secure_log;

/*
 * EZ API Functions and Globals
 */
#ifdef ANSI_C
typedef	void (*EZFUNC) (char *, char *);
#else
typedef void (*EZFUNC) ();
#endif
#define NO_EZCALLBACK	((EZFUNC)0)

EXTERN char FAR *EEXPORT ez_checkout     CARGS((SLM_CONST char FAR *, char FAR *, EZFUNC));
EXTERN long EEXPORT      ez_checkout_txt CARGS((SLM_CONST char FAR *, char FAR *, EZFUNC, char FAR *, long));

EXTERN char FAR *EEXPORT ez_checkin      CARGS((SLM_CONST char FAR *));
EXTERN long EEXPORT      ez_checkin_txt  CARGS((SLM_CONST char FAR *, char FAR *, long));

EXTERN SLM_INSTANCE ez_instance;
EXTERN SLM_CONNECTION ez_connection;
EXTERN char ez_server[];

#ifdef ANSI_C
# include <stdarg.h>
#else
# include <varargs.h>
#endif

/*
 * UNIX Only Function API
 */
#ifdef UNIX
# ifdef ANSI_C
EXTERN int           EEXPORT slm_lmsend(SLM_INSTANCE, char *, ...);
EXTERN int           EEXPORT slm_lmstart(SLM_INSTANCE, char *, ...);
EXTERN int           EEXPORT slm_lmshutdown(SLM_INSTANCE);
# else
EXTERN int           EEXPORT slm_lmsend();
EXTERN int           EEXPORT slm_lmstart();
EXTERN int           EEXPORT slm_lmshutdown();
# endif
#endif

/*
 * Function API
 * Declaration format...
 *        EXTERN type name    CARGS((arglist))
 * Note: use double parens with CARGS.
 *
 * The declarations below may be sorted with "sort -b -d +2"
 *
 * Note: 16-bit Windows must use "far" keyword when passing pointers to API functions
 */

EXTERN long           EEXPORT slm_alive             CARGS((SLM_INSTANCE, SLM_CONNECTION, char FAR *));
EXTERN long           EEXPORT slm_allalive          CARGS((SLM_INSTANCE, SLM_CONNECTION, char FAR *));
EXTERN long           EEXPORT slm_checklock         CARGS((SLM_INSTANCE, SLM_CONST char FAR *, SLM_CONST char FAR *, long (FAR *)()));
EXTERN long           EEXPORT slm_checksum          CARGS((SLM_INSTANCE, SLM_CONST char FAR *));
EXTERN long           EEXPORT slm_chklicense        CARGS((SLM_INSTANCE, SLM_CONNECTION, char FAR *, long));
EXTERN long           EEXPORT slm_clientid          CARGS((SLM_INSTANCE, SLM_CONNECTION));
EXTERN long           EEXPORT slm_endapi            CARGS((SLM_INSTANCE FAR *));
EXTERN long           EEXPORT slm_codedecode        CARGS((SLM_INSTANCE, SLM_CONST char FAR *, char FAR *, char FAR *));
EXTERN SLM_CONNECTION EEXPORT slm_connect           CARGS((SLM_INSTANCE, char FAR *, SLM_CONST char FAR *, SLM_CONST char FAR *, long (FAR*)(SLM_INSTANCE, SLM_CONNECTION, long)));
EXTERN long           EEXPORT slm_control           CARGS((SLM_INSTANCE, SLM_CONNECTION, long, long));
EXTERN time_t         EEXPORT slm_date_decode       CARGS((SLM_INSTANCE, char FAR *, char FAR *, char, char FAR *));
EXTERN long           EEXPORT slm_date_encode       CARGS((SLM_INSTANCE, char FAR *, char FAR *, time_t, char, char FAR *));
EXTERN long           EEXPORT slm_disconnect        CARGS((SLM_INSTANCE, SLM_CONNECTION));
EXTERN long           EEXPORT slm_gencode           CARGS((SLM_INSTANCE, char FAR *, SLM_CONST char FAR *, long));
EXTERN long           EEXPORT slm_getdata           CARGS((SLM_INSTANCE, SLM_CONNECTION, SLM_CONST char FAR *, char FAR *));
EXTERN long           EEXPORT slm_getdatafile       CARGS((SLM_INSTANCE, SLM_CONST char FAR *, char FAR *, long));
EXTERN long           EEXPORT slm_getfeatureinfo    CARGS((SLM_INSTANCE, SLM_CONNECTION, struct slm_featureinfo FAR *, SLM_CONST char FAR *, long));
EXTERN long            EEXPORT slm_getpackinfo    CARGS((SLM_INSTANCE, SLM_CONNECTION, struct slm_packinfo FAR *, SLM_CONST char FAR *, long, long, long));
EXTERN long           EEXPORT slm_getkeyfile        CARGS((SLM_INSTANCE, slm_keyentry_t FAR *, SLM_CONST char FAR *));
EXTERN long           EEXPORT slm_getlicense        CARGS((SLM_INSTANCE, SLM_CONNECTION, SLM_CONST char FAR *, long, long, slm_constraints_t FAR *, long FAR *));
EXTERN long           EEXPORT slm_getport           CARGS((SLM_INSTANCE, char FAR *));
EXTERN char FAR *     EEXPORT slm_getrelease        CARGS((SLM_INSTANCE));
EXTERN long           EEXPORT slm_getrelease_txt    CARGS((SLM_INSTANCE,char FAR *, long));
EXTERN long           EEXPORT slm_getservers        CARGS((SLM_INSTANCE, struct slm_server FAR *, long , SLM_CONST char FAR *, SLM_CONST char FAR *));
EXTERN long           EEXPORT slm_getservuptime     CARGS((SLM_INSTANCE));
EXTERN long           EEXPORT slm_gettimeout        CARGS((SLM_INSTANCE, long FAR *, long FAR *));
EXTERN long           EEXPORT slm_getulist          CARGS((SLM_INSTANCE, SLM_CONNECTION, struct slm_user FAR *, SLM_CONST char FAR *,long));
EXTERN long           EEXPORT slm_getuser           CARGS((SLM_INSTANCE, SLM_CONNECTION, char FAR *, char FAR *, char FAR *));
EXTERN long           EEXPORT slm_getvdata          CARGS((SLM_INSTANCE, SLM_CONST char FAR *, char FAR *, char FAR *));
EXTERN char           EEXPORT slm_getversion        CARGS((SLM_INSTANCE)); /* Version ID 'A', 'B', 'C', or 'D'  */
EXTERN long           EEXPORT slm_heartbeat         CARGS((SLM_INSTANCE, SLM_CONNECTION, long, void (FAR *)(long, char FAR *)));
EXTERN long           EEXPORT slm_hostcodetag_decode CARGS((SLM_INSTANCE, char FAR *, char FAR *));
EXTERN long           EEXPORT slm_hostcodetag_encode CARGS((SLM_INSTANCE, char FAR *, char FAR *, long));
EXTERN long           EEXPORT slm_key               CARGS((SLM_INSTANCE, long, char FAR *, struct slm_keydata FAR *, unsigned long ));
EXTERN long           EEXPORT slm_keyfile           CARGS((SLM_INSTANCE, long, SLM_CONST char FAR *, slm_keyentry_t FAR *));
EXTERN unsigned long  EEXPORT slm_licpak_id	    CARGS((void));
EXTERN long           EEXPORT slm_logtag_decode     CARGS((SLM_INSTANCE, char FAR *, char FAR *, long FAR *, time_t FAR *));
EXTERN long           EEXPORT slm_logtag_encode     CARGS((SLM_INSTANCE, char FAR *, char FAR *, long, time_t));
EXTERN char FAR *     EEXPORT slm_message           CARGS((SLM_INSTANCE, SLM_CONST char FAR *, SLM_CONST char FAR *, long));
EXTERN long           EEXPORT slm_message_txt       CARGS((SLM_INSTANCE, SLM_CONST char FAR *, SLM_CONST char FAR *, long, char FAR *, long));
EXTERN long           EEXPORT slm_meter             CARGS((SLM_INSTANCE, SLM_CONNECTION, SLM_CONST char FAR *, long, long));
EXTERN long           EEXPORT slm_numcheckouts      CARGS((SLM_INSTANCE, SLM_CONNECTION));
EXTERN long           EEXPORT slm_owner             CARGS((SLM_INSTANCE, SLM_CONNECTION));
EXTERN long           EEXPORT slm_pick_hostcode     CARGS((SLM_INSTANCE));
EXTERN long           EEXPORT slm_putdata           CARGS((SLM_INSTANCE, SLM_CONNECTION, SLM_CONST char FAR *, SLM_CONST char FAR *, unsigned long));
EXTERN long           EEXPORT slm_putdatafile       CARGS((SLM_INSTANCE, SLM_CONST char FAR *, SLM_CONST char FAR *, long));
EXTERN long           EEXPORT slm_putkeyfile        CARGS((SLM_INSTANCE, SLM_CONST char FAR *, struct slm_keyentry FAR *));
EXTERN long           EEXPORT slm_putvdata          CARGS((SLM_INSTANCE, SLM_CONST char FAR *, char FAR *, char FAR *));
EXTERN long           EEXPORT slm_readycode         CARGS((SLM_INSTANCE, char FAR *, slm_hostinfo_t FAR *));
EXTERN long            EEXPORT slm_retlicense        CARGS((SLM_INSTANCE, SLM_CONNECTION, SLM_CONST char FAR *, long));
EXTERN long           EEXPORT slm_sendmessage       CARGS((SLM_INSTANCE, SLM_CONNECTION, SLM_CONST char FAR *, long, char FAR *));
EXTERN long           EEXPORT slm_setport           CARGS((SLM_INSTANCE, SLM_CONNECTION, long, char FAR *));
EXTERN long           EEXPORT slm_setsalt           CARGS((SLM_INSTANCE, SLM_CONNECTION, char FAR *));
EXTERN long           EEXPORT slm_settimeout        CARGS((SLM_INSTANCE, long, long));
EXTERN long           EEXPORT slm_setuser           CARGS((SLM_INSTANCE, SLM_CONNECTION, SLM_CONST char FAR *, SLM_CONST char FAR *, SLM_CONST char FAR *));
EXTERN long           EEXPORT slm_setversion        CARGS((SLM_INSTANCE,char));
EXTERN long           EEXPORT slm_startapi          CARGS((SLM_INSTANCE FAR *));
EXTERN long           EEXPORT slm_val_alias         CARGS((SLM_INSTANCE, SLM_CONST char FAR *));
EXTERN long           EEXPORT slm_val_feature       CARGS((SLM_INSTANCE, SLM_CONST char FAR *));
EXTERN long           EEXPORT slm_val_licenses      CARGS((SLM_INSTANCE, long));
EXTERN long           EEXPORT slm_val_vendordata    CARGS((SLM_INSTANCE, SLM_CONST char FAR *));
EXTERN long           EEXPORT slm_vendorfield_id    CARGS((SLM_CONST char *));
EXTERN long           EEXPORT slm_vid               CARGS((SLM_INSTANCE));
EXTERN long           EEXPORT slm_verify            CARGS((SLM_INSTANCE, char FAR *));
EXTERN long           EEXPORT slm_zerohostinfo      CARGS((SLM_INSTANCE, slm_hostinfo_t FAR *));
#ifndef _WINDOWS
EXTERN long           EEXPORT slm_event             CARGS((SLM_INSTANCE, long, void (FAR *)(), long));
EXTERN long           EEXPORT slm_rmevent           CARGS((SLM_INSTANCE, void (FAR *)()));
EXTERN long           EEXPORT slm_xtheartbeat       CARGS((SLM_INSTANCE, SLM_CONNECTION, XTAPPCONTEXT, long, void (FAR *)(long, char FAR *)));
EXTERN long           EEXPORT slm_xvheartbeat       CARGS((SLM_INSTANCE, SLM_CONNECTION, long, long, void (FAR *)(long, char FAR *)));
#endif

/* Utility functions */
EXTERN char FAR *     EEXPORT slu_cgmtime           CARGS((time_t FAR *));
EXTERN long           EEXPORT slu_cgmtime_txt       CARGS((time_t FAR *,char FAR *, long ));
EXTERN long           EEXPORT slu_sleep             CARGS((long )); 
EXTERN time_t         EEXPORT slu_zonetime          CARGS((time_t FAR *));
#ifdef _WINDOWS
EXTERN long           EEXPORT slu_getwindefault     CARGS((char FAR *, char FAR *, char FAR *, char FAR *, long, char FAR *));
EXTERN long           EEXPORT slu_putwindefault     CARGS((char FAR *, char FAR *, char FAR *, char FAR *));
#endif

/* Call back functions */
EXTERN char FAR *     (*slmd_startup_callback)          CARGS((void));
EXTERN long           (*slmd_message_callback)          CARGS((slm_requestdata_t FAR *,char FAR *,long ,char FAR *));
EXTERN long           (*slmd_getlicensefilter_callback) CARGS((slm_requestdata_t FAR *));
EXTERN void           (*slmd_getlicense_callback)       CARGS((slm_requestdata_t FAR *));
EXTERN void           (*slmd_retlicense_callback)       CARGS((slm_requestdata_t FAR *));
EXTERN long           (*slm_vendorhostid_callback)      CARGS((char FAR *,long));

EXTERN long           (*slm_startapi_callback)          CARGS((SLM_INSTANCE));
EXTERN long           (*slm_endapi_callback)            CARGS((SLM_INSTANCE));
#endif
