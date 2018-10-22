class employee;

class part
{
public:
  int part_id;
  employee *responsible_engineer;
  part(int id) {
    part_id = id;
    responsible_engineer = 0;
  }
};

