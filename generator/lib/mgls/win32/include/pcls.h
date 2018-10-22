/* HEADER
 *     pcls.h - Header file for the Mentor Graphics PC/Win32 licensing system
 *
 * Copyright 1992-2008 Mentor Graphics Corporation
 * All Rights Reserved
 *
 * THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY
 * INFORMATION WHICH IS THE PROPERTY OF MENTOR
 * GRAPHICS CORPORATION OR ITS LICENSORS AND IS
 * SUBJECT TO LICENSE TERMS.
 *
 * AUTHOR
 *     Mike Frison
 *
 * DESCRIPTION
 *     This file should be #include'ed in all application source files that
 *     will call functions from the MGC PC/Win32 licensing system.
 */

#if !defined(PCLS_H)
#define PCLS_H

/* Return values from most PCLS functions */
#define MGC_LIC_OK      0
#define MGC_LIC_FAIL    1
#define MGC_LIC_ERR     2

/* Extra Return Value for mgc_lic_valid */
#define MGC_LIC_INUSE   3

/* Values used when calling mgc_lic_idle() */
#define MGC_LIC_BUSY    3
#define MGC_LIC_IDLE    4

/* Extra Return Value for mgc_add_authdata() */
#define FLEX_LIC_ERR    5 

/* The version of licensing */
#define PCLS_VERSION "feb 25 2008"

/* This type defines the clases of applications supported by PCLS */

typedef enum MGCLICAPPTYPE
{
   MGC_LIC_APP_BATCH,
   MGC_LIC_APP_INTER,
   MGC_LIC_APP_NO_ERR_MSG,
   MGC_LIC_APP_B_NODUP,
   MGC_LIC_APP_I_NODUP
}  MgcLicAppType;

/* This section relates to the mgc_lic_set_attr() and mgc_lic_get_attr()*/
/* functions that are not currently supported */
#define MGC_LIC_A_VAL_TYPE unsigned long
typedef enum MGCLICATTRTYPE
{
   MGC_LIC_A_MULTIPLE_COUNTS,
   MGC_LIC_A_QUEUE,
   MGC_LIC_A_PKGINFO_DATE,
   MGC_LIC_A_ANY_ENABLED,
   MGC_LIC_A_CHECK_INTERVAL,
   MGC_LIC_A_CONN_TIMEOUT,
   MGC_LIC_A_DISABLE_ENV,
   MGC_LIC_A_DISPLAY_OVERRIDE,
   MGC_LIC_A_HOST_OVERRIDE,
   MGC_LIC_A_LF_LIST,
   MGC_LIC_A_LICENSE_FILE_PTR,
   MGC_LIC_A_LICENSE_INUSE,
   MGC_LIC_A_NO_DEMO,
   MGC_LIC_A_RETRY_COUNT,
   MGC_LIC_A_RETRY_INTERVAL,
   MGC_LIC_A_USER_EXITCALL,
   MGC_LIC_A_USER_OVERRIDE,
   MGC_LIC_A_USER_RECONNECT,
   MGC_LIC_A_USER_RECONNECT_DONE,
   MGC_LIC_A_LIC_PER_INVOKE,
   MGC_LIC_A_LICENSE_SOURCE,
   MGC_LIC_A_NONE
}   MgcLicAttrType;

/*This will pull in the licensing functions from pcls.dll */
#if !defined(PCLSDLL) 
#ifdef __cplusplus
extern "C" {
#endif

   extern int        mgc_lic_init(double, char *, MgcLicAppType);
   extern int        mgc_lic_valid(int[], int, int);
   extern int        mgc_lic_co(int[], int, int);
   extern int        mgc_lic_ci(int[], int);
   extern int        mgc_lic_idle(short);
   extern int        mgc_lic_set_attr(MgcLicAttrType, MGC_LIC_A_VAL_TYPE);
   extern int        mgc_lic_get_attr(MgcLicAttrType, MGC_LIC_A_VAL_TYPE *);
   extern int        mgc_lic_timer(void);
   extern char       *mgc_lic_display(int);
   extern char       *mgc_lic_hostname(int);
   extern char       *mgc_lic_username(int);
   extern char       *mgc_lic_errstring(void);
   extern void       mgc_lic_cleanup(void);
   extern double     mgc_lic_version(void);
   extern const char *mgc_last_co(void);
   extern int        mgc_lic_which( char * );
   extern void       set_dll_var(char *);

#ifdef __cplusplus
}
#endif

#endif

#endif /* PCLS_H */
