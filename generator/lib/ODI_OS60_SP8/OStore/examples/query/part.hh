class employee;
class part;
extern os_Set<part*> *part_extent;

class part
{
public:
  int part_number;
  os_List<part*> children;
  employee* responsible_engineer;

  part (int a, employee* e)
  {
    part_number = a;
    responsible_engineer = e;
    part_extent->insert(this);
  }

  ~part(){ part_extent->remove(this);}
  static os_typespec* get_os_typespec();
};

