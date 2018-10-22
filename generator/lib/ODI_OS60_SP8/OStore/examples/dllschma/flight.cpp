//
//  Flight.cc
//  
#include <iostream.h>
#include <ostore/ostore.hh>
#include "flight.hh"

os_rel_m_m_body(Flight,_passengers,Person,_myFlights)

os_query_function_body(Flight,getPlane,Plane*,flightbp)

Flight::Flight ( int number, char* from, char* to, int maxPass)
{
_embark.setString (from);
_dest.setString (to);
setPlane(new (os_segment::of(this), Plane::get_os_typespec()) Plane (maxPass));
_flightNumber = number;
}

Flight::~Flight()
{
  delete _plane;
}

void Flight::setEmbark(char* from)
{
  _embark.setString(from);
}

void Flight::setDest(char* to)
{
  _dest.setString(to);
}

ostream& operator<<(ostream& output, Flight& flight)
{
  return output 
    << "Flight Number " << flight._flightNumber << ", "
      << *(flight._plane) << ", from " << flight._embark 
	<< " to " << flight._dest << endl; 
}


