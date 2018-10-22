#include <iostream.h>
#include "Manager.hh"

Manager::Manager (const char * nm, const char * dep)
  : Employee(nm, dep), weeklysalary(0)
{}

void Manager::setSalary(float s)
{
  weeklysalary = s;
}

float Manager::ComputePay () const
{
  return weeklysalary;
}

