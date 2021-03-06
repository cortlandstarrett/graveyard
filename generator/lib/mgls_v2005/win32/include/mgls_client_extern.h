/*
** HEADER
**    mgls_client_extern.h -- This file contains the external declaration
**                            of the MGLS interfaces.
**
** COPYRIGHT
**
**    Copyright Mentor Graphics Corporation 2004
**    All Rights Reserved.
**
** WRITTEN BY:
**   Mahmood TahanPesar
**
** DESCRIPTION
**    This file contains the external declaration of MGLS interfaces used
**    by clients.
**
** USER GUIDE
**
*/

#ifndef INCLUDED_MGLS_CLIENT_EXTERN
#define INCLUDED_MGLS_CLIENT_EXTERN

#ifdef _WIN32

#include "mgls_licensing.h"
#include "mgls_client_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

   extern struct MGLS_ERRNO_STRUCT mgls_errstrct;
   extern long mgls_errno;
   extern long core_Mheap_alloc( int );
   extern long core_Mheap_allocv( int, char * );
   extern long core_Mheap_stat( long );
   extern long core_Mheap_free( long );
   extern long core_Mheap_clean( void );
   extern long core_Mheap_set( int, long );
   extern long core_Mheap_get( int, long * );
   extern long core_Mheap_valid( int );
   extern long core_Mheap_validv( int, char * );
   extern long core_Mheap_errs( char ** );
   extern long core_Mheap_release( void );
   extern long core_Mheap_which( int, int * );
   extern long core_Mheap_retry( void );
   extern long core_Mheap_licinfo( struct MGLS_LICINFO * );

#ifdef __cplusplus
}
#endif

#else

#ifdef __cplusplus

#ifndef __signal_h
#include <signal.h>
#endif

extern "C" {

    extern long mgls_errno;
    extern long core_Mheap_alloc(int application_id);
    extern long core_Mheap_allocv(int app_id, char *app_date);
    extern long core_Mheap_stat(long transaction_id);
    extern long core_Mheap_free(long transaction_id);
    extern long core_Mheap_clean();
    extern long core_Mheap_set(int which, long new_value);
    extern long core_Mheap_get(int which, long *current_value);
    extern long core_Mheap_valid(int application_id);
    extern long core_Mheap_list(int *num_of_ids, int **id_list);
    extern long core_Mheap_getpid(char *fname, int *pid);
    extern long core_Mheap_lookup(int pid, char *fname);
    extern long core_Mheap_which(int transaction_id, int *actual_id);
    extern long core_Mheap_debug(char *fname, int option);
    extern long core_Mheap_errs(char **error_string);
    extern long Mh_sigchld( void (*disp)(), void (**prev_disp)() );
    extern long Mh_set_sigchld( void (*disp)(), sigset_t m_sa_mask,
                                int *m_sa_flags, void (**prev_disp)());
    extern long core_Mheap_retry();
    extern long core_Mheap_release();
    extern long core_Mheap_licinfo( struct MGLS_LICINFO * );

}

#else

extern long mgls_errno;

    extern long core_Mheap_alloc(   /* int application_id */ );
    extern long core_Mheap_allocv(  /* int application_id, char *app_date */ );
    extern long core_Mheap_stat(    /*long transaction_id*/ );
    extern long core_Mheap_free(    /*long transaction_id*/ );
    extern long core_Mheap_clean(   );
    extern long core_Mheap_set(     /*int which, long new_value*/ );
    extern long core_Mheap_get(     /*int which, long *current_value*/ );
    extern long core_Mheap_valid(   /*int application_id*/ );
    extern long core_Mheap_list(    /*int *num_of_ids, int **id_list*/ );
    extern long core_Mheap_getpid(  /*char *fname, int *pid*/ );
    extern long core_Mheap_lookup(  /*int pid, char *fname*/ );
    extern long core_Mheap_which(   /*int transaction_id, int *actual_id*/ );
    extern long core_Mheap_debug(   /*char *fname, int option*/ );
    extern long core_Mheap_errs(    /*char **error_string*/ );
    extern long Mh_sigchld(         /*void (*disp)(), void (*prev_disp)()*/ );
    extern long Mh_set_sigchld(     /*void (*disp)(), sigset_t m_sa_mask,*/
                                    /*int *m_sa_flags, void (*prev_disp)()*/ );
    extern long core_Mheap_retry();
    extern long core_Mheap_release();
    extern long core_Mheap_licinfo( struct MGLS_LICINFO * );

#endif

#endif

#endif
