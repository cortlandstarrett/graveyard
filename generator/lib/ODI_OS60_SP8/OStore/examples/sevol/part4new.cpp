#include <stdlib.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include "part4new.hh"
#include "dbname4.h"

/* A function to force vftable inclusion for collections templates */
/* and types epart and mpart */
void force_vfts (void*){
  force_vfts(new os_Array<cell*>);
  force_vfts(new os_Bag<cell*>);
  force_vfts(new os_Collection<cell*>);
  force_vfts(new os_List<cell*>);
  force_vfts(new os_Set<cell*>);

  force_vfts(new os_Array<brep*>);
  force_vfts(new os_Bag<brep*>);
  force_vfts(new os_Collection<brep*>);
  force_vfts(new os_List<brep*>);
  force_vfts(new os_Set<brep*>);

  force_vfts(new os_Array<part*>);
  force_vfts(new os_Bag<part*>);
  force_vfts(new os_Collection<part*>);
  force_vfts(new os_List<part*>);
  force_vfts(new os_Set<part*>);

  force_vfts(new os_Array<epart*>);
  force_vfts(new os_Bag<epart*>);
  force_vfts(new os_Collection<epart*>);
  force_vfts(new os_List<epart*>);
  force_vfts(new os_Set<epart*>);

  force_vfts(new os_Array<mpart*>);
  force_vfts(new os_Bag<mpart*>);
  force_vfts(new os_Collection<mpart*>);
  force_vfts(new os_List<mpart*>);
  force_vfts(new os_Set<mpart*>);

  force_vfts(new epart(0,0));
  force_vfts(new mpart(0,0));
}

/* part virtual member functions - one must be out of line to get the vtbls */
/* for these types properly into the executable with some compilers.  See */
/* known bugs list report 6808 for a detailed explanation. */

char * part::part_type() { return (char*)""; }

char * epart::part_type() { return (char*)"e"; }

char * mpart::part_type() { return (char*)"m"; }

