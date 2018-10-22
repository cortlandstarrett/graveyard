#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/relat.hh>
class employee;
class part;
extern os_Set<part*> *part_extent;

class part
{
public:
  int part_number;
  os_relationship_m_1(part,children,part,parent,os_List<part*>) children;
  os_relationship_1_m(part,parent,part,children,part*) parent; 
  employee* responsible_engineer;

  part (int a, employee* e) {
    part_number = a;
    parent = 0;
    responsible_engineer = e;
    part_extent->insert(this);
  }

  ~part() { part_extent->remove(this); }
  static os_typespec* get_os_typespec();
};
