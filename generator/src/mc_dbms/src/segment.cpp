/*========================================================================
 *
 * File:      $RCSfile: segment.cpp,v $
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
#include <mc_dbms/segment.h>

const dbms_unsigned_int32 mc_dbms_segment::m_seg_number = 0;
mc_dbms_segment mc_dbms_segment::m_segment(false);
mc_dbms_segment mc_dbms_segment::m_transSegment(true);



