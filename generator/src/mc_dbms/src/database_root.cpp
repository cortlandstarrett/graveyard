/*========================================================================
 *
 * File:      $RCSfile: database_root.cpp,v $
 * Version:   $Revision: 1.12 $
 * Modified:  $Date: 2013/01/10 23:41:47 $
 *
 * (c) Copyright 2005-2013 by Mentor Graphics Corp. All rights reserved.
 *
 *========================================================================
 * This document contains information proprietary and confidential to
 * Mentor Graphics Corp., and is not for external distribution.
 *======================================================================== 
 */
#include <mc_dbms/database_root.h>
#include <mc_dbms/typespec.h>
#include <mc_dbms/InstanceTracker.h>

std::list<mc_dbms_database*> databases;

mc_dbms_database_root::mc_dbms_database_root() :
   	m_name("mc_dbms_database_root"),
   	m_value(0)
{ }

void mc_dbms_database_root::set_value(void *new_value)
{
	m_value = new_value;
}

mc_dbms_database_root& mc_dbms_database_root::operator=( const mc_dbms_database_root& val)
{
	m_value = val.m_value;
	m_name = val.m_name;
	return *this;
}

long mc_dbms_database_root::persist()
{
	long bytesWritten = writeString(m_name);
	bytesWritten += InstanceTracker::Instance::persist(reinterpret_cast<char*>(m_value));

	return bytesWritten;
}

	
mc_dbms_database_root*  mc_dbms_database_root::create()
{
	mc_dbms_database_root* newRoot = new mc_dbms_database_root();
	newRoot->m_name = readString();
	newRoot->m_value = InstanceTracker::Instance::create()->m_block;
	return newRoot;
}
