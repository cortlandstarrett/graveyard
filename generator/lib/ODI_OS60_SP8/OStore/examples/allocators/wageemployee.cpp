#include <iostream.h>
#include "WageEmployee.hh"

WageEmployee::WageEmployee(const char * nm, const char * dep)
             : Employee(nm, dep), wage(0), hours(0)
{}

void WageEmployee::setWage(float wg)
{
  wage = wg;
}

void WageEmployee::setHours(float hrs)
{
  hours = hrs;
}

float WageEmployee::ComputePay() const
{
  return wage * hours;
}

