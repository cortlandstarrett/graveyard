/*========================================================================
 *
 * File:      $RCSfile: u_typdef.hh,v $
 * Version:   $Revision: 1.9 $
 * Modified:  $Date: 2013/01/10 23:41:34 $
 *
 * (c) Copyright 1992-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#ifndef U_TYPEDEF_HH
#define U_TYPEDEF_HH



typedef		void*			t_void_ptr;


typedef		char			t_char;		//  8 bit
typedef		unsigned char		t_uchar;	//  8 bit


typedef		short			t_short;	//  16-bit
typedef		unsigned short		t_ushort;	//  16-bit


typedef		int			t_int;		//  16-bit OR 32-bit
typedef		unsigned int		t_uint;		//  16-bit OR 32-bit


typedef		long			t_long;		//  32-bit
typedef		unsigned long		t_ulong;	//  32-bit


typedef		float			t_float;	//  32-bit
typedef		double			t_double;	//  64-bit


typedef		unsigned int		t_boolean;
#ifndef		FALSE
#define		FALSE			0
#endif
#ifndef		TRUE
#define		TRUE			1
#endif

#ifdef WIN32
#define PATH_DELIM_CHAR '\\'
#define PATH_DELIM_STR  "\\"
#else
#define PATH_DELIM_CHAR '/'
#define PATH_DELIM_STR  "/"
#endif



#endif
