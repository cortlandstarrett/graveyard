//
//  Person.hh
//
//  The class Person represents a person who is a passenger on a flight.
//  Instances of Person are maintained in an embedded forward-linked list.
//  Each instance points to the previously allocated instance.  Each Person
//  may be booked on multiple flights.
//

#ifndef _PERSON_H
#define _PERSON_H

#include "string.hh"
#include "flight.hh"
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/relat.hh>

class Person;
class Flight;

class ostream;

class Person
{
  public:
    Person (char * name);
    Person& operator = (const Person& other );
    String& getName () { return _name; }
    void setName ( char* );
    static os_typespec* get_os_typespec();
    os_list* getMyFlights () { return &(_myFlights.getvalue()); }
    void setMyFlights (os_list* f) { _myFlights = *f; }
    friend ostream& operator<<(ostream& output, Person& person);

  private:
//    Flight* _myFlights;
    os_relationship_m_m(Person,_myFlights,Flight,_passengers,os_list) _myFlights;
    String _name;
};

ostream& operator<<(ostream& output, Person& person);

#endif // _PERSON_H

