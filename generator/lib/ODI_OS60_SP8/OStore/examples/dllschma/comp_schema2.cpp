//
// comp_schema2.cpp - This is the component schema that will be
// placed into the flight_cs2 DLL component.  It is the same
// as comp_schema.cpp but has automatic component schema load/unload
// reporting disabled.
//

#include <ostore/ostore.hh>
#include <ostore/coll.hh>    
#include <ostore/coll/dict_pt.hh>
#include <ostore/manschem.hh>               

#include "common.hh"
#include "string.hh"   
#include "flight.hh"   
#include "plane.hh"    
#include "person.hh"    

// Component schemata need a DLL identifier so we define
// one using this schema macro.  
OS_SCHEMA_DLL_ID("DLL:flight2")

// Shutoff automatic load/unload reporting.
OS_REPORT_DLL_LOAD_AND_UNLOAD(false)

// Tell ossg to use this variable name for the schema info.
OS_SCHEMA_INFO_NAME(flight_cs2_dll_schema_info)

OS_MARK_SCHEMA_TYPE(Flight)
OS_MARK_SCHEMA_TYPE(Plane)
OS_MARK_SCHEMA_TYPE(String)     
OS_MARK_SCHEMA_TYPE(Person)     
OS_MARK_DICTIONARY(char*,Plane*)

OS_MARK_QUERY_FUNCTION(Flight,getPlane)
OS_MARK_QUERY_FUNCTION(Plane,getMaxPassengers)

