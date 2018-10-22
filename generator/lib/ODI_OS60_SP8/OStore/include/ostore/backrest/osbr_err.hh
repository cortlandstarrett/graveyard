/*
    ObjectStore Release 6.0 Service Pack 8/VC 6.0

    Copyright (c) eXcelon Corporation 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002
    All Rights Reserved.  Patent Pending.
*/


#ifndef _OSBR_OSBR_ERR_HH
#define _OSBR_OSBR_ERR_HH

/********************************/
/*	include files		*/
/********************************/

#include <ostore/except.hh>

/********************************/
/*	declare exceptions	*/
/********************************/

_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_all_exceptions);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_misc);

_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_invalid_backup_data);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_bad_incremental_data);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_not_incremental_file);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_incomplete_backup_data);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_out_of_space);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_cant_open_volume);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_cant_open_db);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_not_supported);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_unknown_media_capacity);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_sync_timed_out);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_recovery_complete);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_restore_deadlocked);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_cant_open_exclusive);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_directory_not_found);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_path_exists);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_mem_io);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_db_crf_mismatch);
_OS_DECLARE_EXCEPTION(_OS_BACKREST,err_osbr_invalid_arguments);

/********************************/

#endif /* _OSBR_OSBR_ERR_HH */
