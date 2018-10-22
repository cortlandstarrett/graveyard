/*========================================================================
 *
 * File:      $RCSfile: persistence.h,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:53 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
/** 
 * This class is the header for the file that receives the instance data when it
 * gets written out.
 */
#ifndef _included_class_persist
#define _included_class_persist 1

#if defined(_MSC_VER)
#pragma warning(disable:4786)
#endif

#include <mc_dbms/mc_dbms_types.h>

class Persistence
{
public:
	enum SerializedState { InitialState = 0, Serialized };

	/**
	 * This function writes out all data in the instance container to our
	 * persistent store.
	 *
	 * @arg fullyQualifiedFileName	The Fully-qualified name of a file to write
	 *                             	the data to.   This has a default value of
	 *								"mcdbms.db".
	 */
	static void persist(const std::string& fullyQualifiedFileName = "mcdbms.db");
	
		/**
	 * This function loads the InstanceContainer with data that is in the 
	 * specified file.
	 *
	 * @arg fullyQualifiedFileName	The Fully-qualified name of the mcdbms 
	 *                              database file to restore.
	 */
	static void restore(const std::string& fullyQualifiedFileName = "mcdbms.db", bool ignoreMissingFile = false);	
};

#endif
