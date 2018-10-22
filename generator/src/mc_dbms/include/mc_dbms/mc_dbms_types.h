/*========================================================================
 *
 * File:      $RCSfile: mc_dbms_types.h,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:52 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef _included_mc_dbms_types_
#define _included_mc_dbms_types_ 1

#include <string>

typedef int						dbms_int;
typedef bool					dbms_boolean;
typedef	double					dbms_real;
typedef std::string				dbms_string;
typedef unsigned long			dbms_unsigned_int32;
typedef long					dbms_int32;
typedef	char*					dbms_char_ptr;
typedef	const char*				dbms_const_char_ptr;
typedef const void*				dbms_const_void_ptr;

#endif /* _included_mc3020_dbms_types_ */
