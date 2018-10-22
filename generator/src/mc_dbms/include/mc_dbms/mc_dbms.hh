/*========================================================================
 *
 * File:      $RCSfile: mc_dbms.hh,v $
 * Version:   $Revision: 1.11 $
 * Modified:  $Date: 2013/01/10 23:41:53 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
/**
 * This is the main header for for our model compiler DBMS implementation.  This
 * should be the only header file that needs to be included when access to the 
 * DBMS is required. 
 */
#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif

#ifndef MC_DBMS_HH
#define MC_DBMS_HH

#include <mc_dbms/collection.h>  
#include <mc_dbms/bag.h>  
#include <mc_dbms/list.h>  
#include <mc_dbms/set.h>  
#include <mc_dbms/cursor.h>  
#include <mc_dbms/database.h>  
#include <mc_dbms/database_root.h>  
#include <mc_dbms/segment.h>  
#include <mc_dbms/typespec.h>  
#include <mc_dbms/InstanceTracker.h>
#include <mc_dbms/macros.h>
#include <mc_dbms/persistence.h>
#include <mc_dbms/typespec.h>
#include <mc_dbms/SerializableObject.h>
#include <mc_dbms/InstanceTracker.h>
#include <mc_dbms/external_object.h>

#endif

      