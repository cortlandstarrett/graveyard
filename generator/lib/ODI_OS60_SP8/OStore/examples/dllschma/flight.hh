//
//   Flight.hh
//
//   Defines a class representing an airline flight.  Every flight has
//   an associated Plane, and maybe some passengers.
//   Instances of Flight are maintained by an ObjectStore Collection (os_list).
//

#ifndef _FLIGHT_H
#define _FLIGHT_H

#include <ostore/ostore.hh>    // Required to access ObjectStore Class Library
#include <ostore/coll.hh>
#include <ostore/relat.hh>
#include "string.hh"
#include "plane.hh"
#include "person.hh"

class Plane;
class Flight;
class Person;

class ostream;

class Flight
{
public:
  Flight ( int num, char* from, char* to, int maxPass);
  ~Flight();
  static os_typespec* get_os_typespec ();

  int getFlightNumber () const { return _flightNumber; }
  void setFlightNumber (int fnum) { _flightNumber = fnum; }
  Plane* getPlane() { return _plane; }
  void   setPlane (Plane* p) { _plane = p; }
  String& getEmbark() { return _embark; }
  void   setEmbark (char*);
  String& getDest() { return _dest; }
  void   setDest (char*);
  os_list* getPassengers () { return &(_passengers.getvalue()); }
  void setPassengers (os_list* p) { _passengers = *p; }
  friend ostream& operator<<(ostream& output, Flight& flight);
  os_backptr flightbp;

private:
  int _flightNumber;
  Plane* _plane;
//  Person* _passengers;
  os_relationship_m_m(Flight,_passengers,Person,_myFlights,os_list) _passengers;
  String _embark;
  String _dest;
};

// register query function getPlane()
os_query_function(Flight,getPlane,Plane*)

//
// overload operator << for writing Flight object
//
ostream& operator<<(ostream& output, Flight& flight);

#endif // _FLIGHT_H

