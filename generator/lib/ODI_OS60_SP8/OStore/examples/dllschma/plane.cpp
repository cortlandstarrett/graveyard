//
//  Plane.cc
//

#include <iostream.h>
#include "plane.hh"


os_query_function_body(Plane,getMaxPassengers,int,planebp)


Plane::Plane(int loadMax)
{
  _maxPassengers = loadMax;
}

ostream& operator<<(ostream& output, Plane& plane)
{
  return output << "Plane with " << plane._maxPassengers << " seats";
}




