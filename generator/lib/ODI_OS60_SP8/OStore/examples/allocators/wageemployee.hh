#ifndef WAGE_EMPLOYEE_H
#define WAGE_EMPLOYEE_H
#include <iostream.h>
#include "string.hh"
#include "Employee.hh"


//	Derived classes

class WageEmployee : public Employee
{
public:
  WageEmployee (const char *, const char *);
  virtual ~WageEmployee () {};
  static os_typespec* get_os_typespec ();
  void setWage (float wg);
  void setHours (float hrs);
  float ComputePay() const;
private:
  float wage;
  float hours;
};

#endif
