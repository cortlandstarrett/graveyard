//
//  FlightMenu.hh
//  
//  FlightMenu is a class which displays menu options, accepts selection 
//  from user, and performs selected operation.
//

#ifndef _FLIGHTMENU_H
#define _FLIGHTMENU_H

#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/relat.hh>
#include <ostore/coll/dict_pt.hh>

class Flight;
class Plane;

class FlightMenu
{
public:
  FlightMenu(os_database* DB) {_database=DB; }
  void getFlight();
  void displayAndPollInput();
  void addFlight();
  void displayAllFlights(); 
  void populateDB(); 
  void bookPassenger();
  void locationQuery();
  void passengerQuery();

private:
  os_reference_transient _allFlights;  // ref to list of all instances of Flight
  os_reference_transient _allPlanes;  // dictionary of all instances of Planes
  void setAllFlights( os_list * fList );  // reset database root
  os_list* getAllFlights( );  // look up/set database root
  os_Dictionary<char*,Plane*>* getAllPlanes( );  // look up/set database root
  os_database* _database;     // The database in which we store
                                // all of our persistent objects
};


#endif // _FLIGHTMENU_H
