//
// This is the regular application schema which is used
// by only the 'flights' example.
//

#include <ostore/ostore.hh>
#include <ostore/coll.hh>    
#include <ostore/coll/dict_pt.hh>
#include <ostore/manschem.hh>               

#include "string.hh"   
#include "flight.hh"   
#include "plane.hh"    
#include "person.hh"    

OS_MARK_SCHEMA_TYPE(Flight)
OS_MARK_SCHEMA_TYPE(Plane)
OS_MARK_SCHEMA_TYPE(String)     
OS_MARK_SCHEMA_TYPE(Person)     
OS_MARK_DICTIONARY(char*,Plane*)

OS_MARK_QUERY_FUNCTION(Flight,getPlane)
OS_MARK_QUERY_FUNCTION(Plane,getMaxPassengers)

