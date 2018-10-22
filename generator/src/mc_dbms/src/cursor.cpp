/*========================================================================
 *
 * File:      $RCSfile: cursor.cpp,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:41:48 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/cursor.h>
#include <mc_dbms/typespec.h>

mc_dbms_typespec mc_dbms_cursor::m_type( "mc_dbms_cursor", sizeof(mc_dbms_cursor) );
mc_dbms_typespec* mc_dbms_cursor::get_mc_dbms_typespec()
{
	return &m_type;
}

