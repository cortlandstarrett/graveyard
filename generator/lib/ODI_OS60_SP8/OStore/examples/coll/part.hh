class employee;

class part
{
public:
  int part_number;
  os_List<part*> children;
  employee *responsible_engineer;
  part (int a) {
    part_number = a;
    responsible_engineer = 0;
  }
};

