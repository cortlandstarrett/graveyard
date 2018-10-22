#include <stdlib.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include "part4pre.hh"
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

  force_vfts(new part(0,0));
}

/* part virtual member functions - one must be out of line to get the vtbls */
/* for these types properly into the executable with some compilers.  See */
/* known bugs list report 6808 for a detailed explanation. */

char * part::part_type() { return (char*)""; }

