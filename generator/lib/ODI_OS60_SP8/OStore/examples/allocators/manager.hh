#ifndef _MANAGER_H
#define _MANAGER_H
#include <iostream.h>
#include "string.hh"
#include "Employee.hh"


//	class derived from Employee

class Manager : public Employee
{
public:
  Manager (const char *, const char *);
  virtual ~Manager() {};
  static os_typespec* get_os_typespec ();
  void setSalary (float s);
  float ComputePay () const;
private:
  float weeklysalary;
};

#endif
