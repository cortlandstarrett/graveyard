//
//  force_vfts.cpp
//  

#include <iostream.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/relat.hh>
#include <ostore/coll/dict_pt.hh>
#include "string.hh"
#include "flight.hh"
#include "person.hh"
#include "plane.hh"

// Some compilers do not create virtual function tables
// required by ObjectStore.  Defining this forces the 
// creation of these tables.
 
void force_vfts(void* ptr)
{
#ifdef WIN32
  force_vfts( new os_Dictionary<char*,Plane*>);
#else
  force_vfts( new os_Dictionary<char*,Plane*>);
  force_vfts( new os_Collection<Plane*>);
  force_vfts( new os_Bag<Plane*>);
  force_vfts( new os_List<Plane*>);
  force_vfts( new os_Set<Plane*>);
  force_vfts( new os_Array<Plane*>);
  force_vfts( new os_Array<Person*>);
  force_vfts( new os_Bag<Flight*>);
  force_vfts( new os_Bag<Person*>);
  force_vfts( new os_Set<Person*>);
  force_vfts( new os_List<Person*>);
  force_vfts( new os_List<Flight*>);
  force_vfts( new os_Array<Flight*>);
  force_vfts( new os_Collection<Person*>);
  force_vfts( new os_Collection<Flight*>);
  force_vfts( new os_Set<Flight*>);
#endif
}

#if defined(__DECCXX)
#pragma define_template os_Dictionary<char*,Plane*>
#pragma define_template os_Collection<Plane*>
#pragma define_template os_Bag<Plane*>
#pragma define_template os_List<Plane*>
#pragma define_template os_Set<Plane*>
#pragma define_template os_Array<Plane*>
#pragma define_template os_Array<Person*>
#pragma define_template os_Bag<Flight*>
#pragma define_template os_Bag<Person*>
#pragma define_template os_Set<Person*>
#pragma define_template os_List<Person*>
#pragma define_template os_List<Flight*>
#pragma define_template os_Array<Flight*>
#pragma define_template os_Collection<Person*>
#pragma define_template os_Collection<Flight*>
#pragma define_template os_Set<Flight*>
#endif // __DECCXX
