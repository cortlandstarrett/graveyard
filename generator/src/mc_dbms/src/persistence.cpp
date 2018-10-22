/*========================================================================
 *
 * File:      $RCSfile: persistence.cpp,v $
 * Version:   $Revision: 1.10 $
 * Modified:  $Date: 2013/01/10 23:41:48 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/persistence.h>
#include <mc_dbms/InstanceTracker.h>
#include <mc_dbms/typespec.h>
#include <fstream>
#include <iostream>

void Persistence::persist(const std::string& fullyQualifiedFileName)
{	
	std::fstream fout(fullyQualifiedFileName.c_str(), std::ios::binary | std::ios::out);
	if ( !fout ) {
		std::string msg("Unable to open the file ");
		msg += fullyQualifiedFileName + " for writting.";
		throw std::runtime_error(msg);
	}
	
	SerializableObject::setOutputStream(fout);
	
	// First dump-out the information about embedded types.  We'll need this
	// in order to restore.
	mc_dbms_typespec::serialize();
	
	// Now recursively dump all the data
	mc_dbms_database::get_persistent_database()->persist();	
}

void Persistence::restore(const std::string& fullyQualifiedFileName, bool ignoreMissingFile)
{
	std::fstream fin(fullyQualifiedFileName.c_str(), std::ios::binary | std::ios::in);
	if ( !fin ) {
		if ( ignoreMissingFile ) {
			return;
		} else {
			std::string msg("Unable to open the file ");
			msg += fullyQualifiedFileName + " for reading.";
			throw std::runtime_error(msg);
		}
	}
	
	SerializableObject::setInputStream(fin);
	
	// We restore in the same order we dumped...  First restore typespec data,
	// and then restore everything else.
	mc_dbms_typespec::restore();
	mc_dbms_database::get_persistent_database()->restore();
}
