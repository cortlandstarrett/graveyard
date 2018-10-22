/* $Id: vdirent.h,v 1.19 1996/10/07 22:58:41 lis Exp $ */

#ifndef vdirentINCLUDED
#define vdirentINCLUDED 1


/*
 * Include any other files this header depends upon
 */

#ifndef vportINCLUDED
#include <vport.h>
#endif


/*
 * Include the system version of dirent.h, if its not too bad
 */

vportBEGIN_CPLUSPLUS_HEADER_PROTECTION

#if (vportDIRENT_INCLUDES_WINDOWS_H)
/* BC5 does this, and we need to make sure things are
 * set up correctly before we include windows.h the
 * first time
 */
#include vmswhdrsHEADER
#endif

#if ( ! vportBAD_DIRENT_HDR )
#include <dirent.h>
#else
#if ( ! vportBAD_SYS_DIRENT_HDR )
#include <sys/dirent.h>
#else
#if ( ! vportBAD_DIRECT_HDR )
#include <direct.h>
#endif
#endif
#endif

vportEND_CPLUSPLUS_HEADER_PROTECTION

#ifndef  vsysdirINCLUDED
#include vsysdirHEADER
#endif


/*
 * Fix up anything that may have been wrong
 */

#if (vportBAD_DIR)
#if (vportNEED_VMS_FILESYSTEM)
#ifndef __DESCRIP_LOADED
#include <descrip.h>
#endif
typedef struct _dirdesc {
        int     dd_fd;
        long    dd_loc;
        long    dd_size;
        long    dd_bbase;
        long    dd_entno;
        long    dd_bsize;
        char *  dd_buf;
        struct dsc$descriptor_s dd_devnam;
    } DIR;
#else
#define DIR void
#endif
#endif

#if (vportBAD_STRUCT_DIRENT)
#if (vportNEED_VMS_FILESYSTEM)
struct dirent  {
    ino_t           d_ino[3];                /* file number of entry */
    unsigned short  d_reclen;                /* length of this record */
    unsigned short  d_namlen;                /* length of string in d_name */
    char            d_name[255 + 1];         /* entry name */
};
#else
struct dirent {
    char d_name[1];
};
#endif
#endif

vportBEGIN_CPLUSPLUS_EXTERN_C

#if (vportNEED_OPENDIR_PROTO)
DIR *opendir( char *dirname );
#endif

#if (vportNEED_READDIR_PROTO)
struct dirent *readdir( DIR *pDir );
#endif

#if (vportNEED_REWINDDIR_PROTO)
void rewinddir( DIR *pDir );
#endif

#if (vportNEED_CLOSEDIR_PROTO)
int closedir( DIR *pDir );
#endif

#if (vportREENTRANT)
# if (vportBAD_READDIR_R)
#  if !(vportBAD_READDIR)
#   undef readdir_r
#   define readdir_r _vcompatReadDir_r

vportLINK int _vcompatReadDir_r (
   DIR             *pDir,
   struct dirent   *entry,
   struct dirent  **result
   );

#  else
#   define readdir_r(__pDir,__entry,__result)  (-1)
#  endif
# endif
#endif

vportEND_CPLUSPLUS_EXTERN_C

/*
 * * * * * * * * * * * * * * * * Miscellaneous * * * * * * * * * * * * * * * *
 */

/*
 * Formatting information for emacs in c-mode
 *
 * Local Variables:
 * c-indent-level:4
 * c-continued-statement-offset:2
 * c-brace-offset:-2
 * c-brace-imaginary-offset:0
 * c-argdecl-indent:4
 * c-label-offset:-2
 * End:
 */

#endif /* vdirentINCLUDED */

