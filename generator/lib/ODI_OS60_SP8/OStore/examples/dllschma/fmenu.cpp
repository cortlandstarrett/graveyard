
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <iostream.h>
#include "common.hh"
#include "string.hh"
#include "flight.hh"
#include "plane.hh"
#include "person.hh"
#include "fmenu.hh"
#include <ostore/coll/dict_pt.cc>

#if defined(__DECCXX)
#pragma define_template os_Dictionary<char*, Plane*>
#pragma define_template _Rhash_pt<char*>
#endif // __DECCXX)

//
// Look up extent of all Flights that have been stored in the
// database.  Extent is stored at a database root called "AllFlights"
// This private method must be invoked from within a transaction.
//
os_list* FlightMenu::getAllFlights()
{
  os_list* fList = 0;
  os_database_root* flight_root = _database->find_root("AllFlights");
  if (flight_root == 0)
    {
      // root not found.
      // create root and list; set value of root; set value of _allFlights

      flight_root = _database->create_root("AllFlights");
      fList = &os_list::create(_database, 0, 100);
      flight_root->set_value(fList);
      this->_allFlights = fList;
    }
  else
    {
      // root found.  set value of _allFlights to entry point

      this->_allFlights = (os_list*)flight_root->get_value();
    }
  return (os_list*)this->_allFlights.resolve();
}

//
// Look up extent of all Planes that have been stored in the
// database.  Extent is stored at a database root called "AllPlanes"
// This private method must be invoked from within a transaction.
//

os_Dictionary<char*,Plane*>* FlightMenu::getAllPlanes()
{  
  os_Dictionary<char*,Plane*>* pDict = 0;
  os_database_root* plane_root = _database->find_root("AllPlanes");
  if (plane_root == 0)
    {
      // root not found.
      // create root and dictionary; set value of root; set value of _allPlanes

      plane_root = _database->create_root("AllPlanes");
      pDict = 
	&os_Dictionary<char*,Plane*>::create(_database, 100);
      plane_root->set_value(pDict);
      this->_allPlanes = pDict;
    }
  else
    {
      // root found.  set value of _allPlanes to entry point

      this->_allPlanes = 
	(os_Dictionary<char*,Plane*>*)plane_root->get_value();
    }
  return (os_Dictionary<char*,Plane*>*)this->_allPlanes.resolve();
}

 
//
//  Create the specified number of Flights and associated Planes,
//  and add to list.
//  

void FlightMenu::populateDB ()
{
  Flight* newFlight = 0;
  os_list * fList = 0;
  char numberBuff[10];
  cout << "Enter number of flights to create: ";
    cin >> numberBuff;
  int randVal1 = 0;
  int randVal2 = 0;
  int randVal3 = 0;
  char* listOfPlaces[20];
  srand ( (unsigned)time( NULL ) ); // trick for seeding randomizer

  OS_BEGIN_TXN(populateTXN,0,os_transaction::update)
    {      
      int numberToCreate = atoi(numberBuff);
      for (int times = 0; times < 8; ++times)
	 listOfPlaces[times] = new char[4];
      strcpy(listOfPlaces[0] ,"BOS");
      strcpy(listOfPlaces[1] ,"LAX");
      strcpy(listOfPlaces[2] ,"SFO");
      strcpy(listOfPlaces[3] ,"ACK");
      strcpy(listOfPlaces[4] ,"DEN");
      strcpy(listOfPlaces[5] ,"ATL");
      strcpy(listOfPlaces[6] ,"ORD");
      strcpy(listOfPlaces[7] ,"LGA");

      fList = (os_list *) _allFlights.resolve();
      if (!fList)
	fList = this->getAllFlights();
      for ( int i = 0; i < numberToCreate; ++i )
	{   
	  randVal1 = rand();              
	  randVal2 = rand();              
	  randVal3 = rand();
	  newFlight =  
	    new (_database,Flight::get_os_typespec()) 
	      Flight ( i,
		      listOfPlaces[randVal1%8],
		      listOfPlaces[randVal2%8],
		      randVal3%400);
	  fList -> insert(newFlight);  // Simply insert new flight into list

	  // get plane and insert into dictionary at appropriate key

	  Plane* newPlane = newFlight->getPlane();
	  os_Dictionary<char*,Plane*>* pDict = 
	    (os_Dictionary<char*,Plane*>*)_allPlanes.resolve();
	  if (!pDict)
	    pDict = this->getAllPlanes();

	  char * jjkey = (char*)"JumboJet";
	  char * jkey = (char*)"Jet";
	  char * ckey = (char*)"Commuter";

	  int maxPassengers = newPlane->getMaxPassengers();
	  if (maxPassengers < 100)
	    pDict->insert(ckey, newPlane);
	  else if (maxPassengers < 200)
	    pDict->insert(jkey, newPlane);
	  else 
	    pDict->insert(jjkey, newPlane);

	}
      cout << "Created " << numberToCreate << " new flights." << endl;
    }
  OS_END_TXN(populateTXN)

}

//
//  Print every Flight in the list of all flights.
//

void FlightMenu::displayAllFlights()
{
  os_list * fList = 0;
  OS_BEGIN_TXN(displayTXN,0,os_transaction::update)
    {      
      fList = (os_list *) _allFlights.resolve();
      if (!fList)
	fList = this->getAllFlights();
      if (!fList)
	cout << "Nothing to print - Flight list is empty " << endl;
      else
	{
	  os_cursor listCurs(*fList);
	  // Note:  If using a parameterized cursor,this loop is much simpler
	  for (Flight* f = (Flight*)listCurs.first();
	       (Flight*)listCurs.more();
	       f=(Flight*)listCurs.next())
	    cout << *f;

	  // Display number of planes of each type.  Use a restricted cursor
	  // to find the planes, then print the resulting counts.

	  os_Dictionary<char*,Plane*>* pDict = 
	    (os_Dictionary<char*,Plane*>*)_allPlanes.resolve();
	  if (!pDict)
	    pDict = this->getAllPlanes();

	  int jjcount = 0;
	  int jcount = 0;
	  int ccount = 0;
	  char * jjkey = (char*)"JumboJet";
	  char * jkey = (char*)"Jet";
	  char * ckey = (char*)"Commuter";

	  os_coll_range jumboRange ( os_collection::EQ, jjkey );

	  os_Cursor<Plane*> jumbo(*pDict,jumboRange);
	  Plane* p;
	  for (p=jumbo.first();jumbo.more();p=jumbo.next())
	    jjcount++;

	  cout << endl << "Planes of type " << jjkey << ": " << jjcount << endl;
	  
	  os_coll_range jetRange(os_collection::EQ,jkey);

	  os_Cursor<Plane*> jet(*pDict,jetRange);
	  for (p=jet.first();jet.more();p=jet.next())
	    jcount++;

	  cout << endl << "Planes of type " << jkey << ": " << jcount << endl;

	  os_coll_range commuterRange(os_collection::EQ,ckey);

	  os_Cursor<Plane*> commuter(*pDict,commuterRange);
	  for (p=commuter.first();commuter.more();p=commuter.next())
	    ccount++;

	  cout << endl << "Planes of type " << ckey << ": " << ccount << endl;
	}
    }
  OS_END_TXN(displayTXN)
  }


//
//  Create a new Flight and add it to the list of all flights
//  This also creates an associated Plane.
// 

void FlightMenu::addFlight()
{
  os_list* fList = 0;
  char   fnum[10], from[50], to[50], maxload[10];
  cout << "Flight number (integer) : ";
  cin >> fnum;
  cout << "\nMaximum number of passengers (integer) : ";
  cin >> maxload;
  cout << endl;
  cout << "Originating city (string) : ";
  cin >> from;
  cout << "Destination city (string) : ";
  cin >> to;

  OS_BEGIN_TXN(addTXN,0,os_transaction::update)
    {
      fList = (os_list *) _allFlights.resolve();
      if (!fList)
	fList = this->getAllFlights();
      Flight* newFlight = new (_database,Flight::get_os_typespec()) 
	Flight (atoi(fnum), from, to, atoi(maxload));
      fList -> insert(newFlight);  // Simply insert new flight into list

      // get plane and insert into dictionary at appropriate key

      Plane* newPlane = newFlight->getPlane();
      os_Dictionary<char*,Plane*>* pDict = 
	(os_Dictionary<char*,Plane*>*)_allPlanes.resolve();
      if (!pDict)
	pDict = this->getAllPlanes();
            
      char * jjkey = (char*)"JumboJet";
      char * jkey = (char*)"Jet";
      char * ckey = (char*)"Commuter";

      int maxPassengers = newPlane->getMaxPassengers();
      if (maxPassengers < 100)
	pDict->insert(ckey, newPlane);
      else if (maxPassengers < 200)
	pDict->insert(jkey, newPlane);
      else 
	pDict->insert(jjkey, newPlane);
    }
  OS_END_TXN(addTXN)

  cout << "Added new flight. " << endl;
}


//
//  Retrieve one flight.
//

void FlightMenu::getFlight()
{
  os_list* fList = 0;
  Flight * aFlight = 0;
  cout << "Getting one arbitrary flight from the list" << endl;

  OS_BEGIN_TXN(getTXN,0,os_transaction::update)
    {
      fList = (os_list *) _allFlights.resolve();
      if (!fList)
	fList = this->getAllFlights();
      aFlight = (Flight*)(fList ->pick());  // Casting not required when
      if (aFlight)                          // using templates.
	cout << *aFlight;
      else
	cout << "Nothing to print - Flight list is empty " << endl;
    }
  OS_END_TXN(getTXN)
}


//
//  Find a Person (list maintained by lastPerson data member) with
//  the specified name.  If a Person already exists with that name,
//  book the Person on a randomly selected Flight (Use getFlight()).
//  If there is no such Person, create a new Person and add to the 
//  lastPerson list.  In either case, add that Person to the Flight's
//  list of passengers, and add the Flight to the Person's list of
//  flights.
//

void FlightMenu::bookPassenger() 
{

//  Uncomment this code when you modify the member function
/*****************************************
  char  passengerName[50];
  cout << "Passenger name (string) : ";
  cin >> passengerName;
******************************************/

//  Remove this line when you modify the member function
  cout << "Sorry!  Not implemented yet. " << endl;
}

//
//  Find and print all flights which embark from and arrive at the 
//  specified locations.
//


void FlightMenu::locationQuery() 
{
//  Uncomment this code when you modify the member function

  char  from[50], to[50];
  cout << "Originating city (string) : ";
  cin >> from;
  cout << "Destination city (string) : ";
  cin >> to;

//  Remove this line when you modify the member function

  OS_BEGIN_TXN(look_for_flights,0,os_transaction::update)
    {
      os_list * fList = (os_list *) _allFlights.resolve();
      if (!fList)
	fList = this->getAllFlights();

      // create query object with two free references

      const os_coll_query& qry = 
	os_coll_query::create("Flight*",
	 "((strcmp((char*)startPoint,_embark._strRep)==0)&& \
             (strcmp((char*)endPoint,_dest._strRep)==0))",_database);
      
      // bind query object's free references to user input

      const os_bound_query boundQuery 
	( qry,
	 (os_keyword_arg ( "startPoint", from ),
	  os_keyword_arg ( "endPoint", to )));

      // execute collection-valued query

      os_collection& result = fList->query(boundQuery);
      if ( result . empty() )
	cout << "Sorry, no flights available. " << endl;
      else
	{
	  // display all flights in result collection

	  os_cursor resultCurs (result);
	  cout << "The following flights are available:" << endl;
	  for (Flight* f = (Flight*)resultCurs.first();
	       (Flight*)resultCurs.more();
	       f=(Flight*)resultCurs.next())
	    cout << *f;
	}

      delete (os_collection*) &result;
    }
  OS_END_TXN(look_for_flights)


}


void FlightMenu::passengerQuery()
{

//  Uncomment this code when you modify the member function for queries
  char numberBuff[10];
  int numberOfSeats = 0;
  cout << "Minimum number of seats: ";
  cin >> numberBuff;
  numberOfSeats = atoi(numberBuff);

//  Remove this line when you modify the member function
  OS_BEGIN_TXN(big_enuf_planes,0,os_transaction::update)
  {
      os_list * fList = (os_list *) _allFlights.resolve();
      if (!fList)
	fList = this->getAllFlights();

      // create query object with one free reference

      const os_coll_query& planeQry =
	os_coll_query::create
	  ("Flight*", "getPlane()->getMaxPassengers() >= (int)pass",_database);

      // bind free reference to user input

      const os_bound_query boundQuery 
	( planeQry, os_keyword_arg ( "pass", numberOfSeats ) ); 

      // execute query

      os_collection& result = fList->query( boundQuery );
      if ( result.empty())
	cout << "No planes hold that many passengers." << endl;
      else
	{
	  os_cursor resultCurs (result);
	  cout << "The following flights are available:" << endl;
	  for (Flight* f = (Flight*)resultCurs.first();
	       (Flight*)resultCurs.more();
	       f=(Flight*)resultCurs.next())
	    cout << *f;
	}
      delete (os_collection*) &result;
    }
  OS_END_TXN(big_enuf_planes)

}


// 
//  Menu display loop
//

void FlightMenu :: displayAndPollInput ()
{

  Flight* whichFlt = 0;
  int finished = 0; // FALSE
  char choice[] = "0";
  while ( !finished )
    {
      cout << endl << endl << endl;
      cout << "\t FLIGHT MENU " << endl;
      cout << "\t_______________________";
      cout << endl << endl;
      cout << "\t1." << "\t" << "...Populate Database..." << endl;
      cout << "\t2." << "\t" << "...Show All Flights..." << endl;
      cout << "\t3." << "\t" << "...Add Flight..." << endl;
      cout << "\t4." << "\t" << "...Get Flight..." << endl;
      cout << "\t5." << "\t" << "...Book a Passenger..." << endl;
      cout << "\t6." << "\t" << "...Find Flights On A Particular Route..." << endl;
      cout << "\t7." << "\t" << "...Find Flights With Big Enough Planes..." << endl;
      cout << "\t8." << "\t" << "...Exit And Close Database..." << endl;
      cout << endl << endl;
      cout << "\t\t\t" << "Please enter choice (1,2,3,4,5,6,7,or 8):";
      cin  >> choice;
      cout << endl;
      int ichoice = atoi(choice);
      switch ( ichoice )
	{
	case 1: 
	  populateDB();	  
	  break;
	case 2: 
	  displayAllFlights();	  
	  break;
	case 3: 
	  addFlight ();
	  break;
	case 4:
	  getFlight();
	  break;
	case 5:
	  bookPassenger();
	  break;
	case 6:
	  locationQuery();
	  break;
	case 7:
	  passengerQuery();
	  break;
	case 8:
	  cout << "Leaving component ... " << endl;
	  finished = 1;  // TRUE
	  break;
	default:
	  cerr << "Invalid choice [" << choice << "]";  
	  break;
	} // end switch
    } // end loop forever
} // end displayAndPollInput 


//
// flight_cs entry point.  Users of this component must link to
// this function or lookup its symbol name.
//
USE_DLL_EXPORT int
flight_db_component(const char *flight_db_path)
{
  os_collection::initialize();
  os_database* flightDB = 0;
  TIX_HANDLE(all_exceptions) {
    TIX_HANDLE(err_directory_not_found) {
      TIX_HANDLE(err_database_not_found) {
	flightDB = os_database::open(flight_db_path);
      } TIX_EXCEPTION {
	// err_database_not_found
	cout << "Database not found . . . creating it " << endl;
	flightDB = os_database::open(flight_db_path,0,0644);
      } TIX_END_HANDLE;
      FlightMenu Office(flightDB);
      Office.displayAndPollInput ();
      flightDB->close();
    } TIX_EXCEPTION {
      // err_directory_not_found
      cout << "Sorry! Directory specified was not found " << endl;
      return 1;
    } TIX_END_HANDLE;
  } TIX_EXCEPTION {
    // all_exceptions
    cout << "Sorry!  Exception was raised" << endl;
    cout << "Here is more information about this exception: " << endl;
    cout << tix_handler::get_report();
    return 1;
  } TIX_END_HANDLE; // all_exceptions
  return 0;
}



