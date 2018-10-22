#include <iostream.h>
#include "SalesPerson.hh"

SalesPerson::SalesPerson (const char * nm, const char* dep)
  : WageEmployee (nm, dep), commission(0), salesmade(0)
{}

void SalesPerson::setCommission (float com)
{
  commission = com;
}

void SalesPerson::setSales (float sales)
{
  salesmade = sales;
}

float SalesPerson::ComputePay () const
{
  return  WageEmployee::ComputePay() +
			  commission * salesmade;
}

