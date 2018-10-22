#ifndef _EMPLOYEE_H
#define _EMPLOYEE_H
#include <iostream.h>
#include "string.hh"

class Employee
{
public:
  Employee(const char *nm, const char * d);
  virtual ~Employee ();
  //  static os_typespec* get_os_typespec ();  
  const char * getName();
  const char * getDept();
  virtual float ComputePay() const = 0;
  friend ostream& operator<<(ostream&, Employee&);
private:
  String * Name;
  String * Dept;
};

ostream& operator<<(ostream&, Employee&);

#endif

