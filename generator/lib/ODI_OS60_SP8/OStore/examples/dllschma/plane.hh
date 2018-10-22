//
//  Plane.hh
//
//  The class Plane represents an airplane.  Instances of this class are
//  associated with a particular instance of Flight.

#ifndef _PLANE_H
#define _PLANE_H

#include <ostore/ostore.hh>    // Required to access ObjectStore Class Library
#include <ostore/coll.hh> 
#include "string.hh"

class ostream;

class Plane
{
public:
  static os_typespec* get_os_typespec ();
             //  (ObjectStore will provide implementation at build time.)

  Plane ( int loadMax);
  int getMaxPassengers() { return _maxPassengers; }
  void setMaxPassengers(int m) { _maxPassengers = m; }
  friend ostream& operator<<(ostream& output, Plane& plane);
  os_backptr planebp;

private:
  int _maxPassengers;
};

// register query function getMaxPassengers()

os_query_function(Plane,getMaxPassengers,int)

//
// overload operator << for writing Plane object
//

ostream& operator<<(ostream& output, Plane& plane);

#endif // _PLANE_H

