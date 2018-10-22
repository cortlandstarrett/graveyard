#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/relat.hh>
#include "employee.hh"
#include "part.hh"

/* provide the body definitions for the relationship members */

os_rel_m_1_body(part,children,part,parent)
os_rel_1_m_body(part,parent,part,children)

/* A function to force vftable inclusion for collections templates */
void force_vfts (void*){
  force_vfts(new os_Array<part*>);
  force_vfts(new os_Bag<part*>);
  force_vfts(new os_Collection<part*>);
  force_vfts(new os_List<part*>);
  force_vfts(new os_Set<part*>);
}

