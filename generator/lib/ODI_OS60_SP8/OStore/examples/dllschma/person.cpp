//
//  Person.cc
//

#include <iostream.h>
#include "person.hh"

os_rel_m_m_body(Person,_myFlights,Flight,_passengers)
Person::Person ( char* name)
{
  _name.setString (name);
}

void Person::setName(char* newName)
{
  _name.setString(newName);
}


Person& Person::operator = (const Person& pers )
{
  _name = pers._name;
  return *this;
}


ostream& operator<<(ostream& output, Person& person)
{
  return output << "Person named " << person._name << endl;
}












