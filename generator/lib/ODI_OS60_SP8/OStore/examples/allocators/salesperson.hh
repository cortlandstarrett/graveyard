#ifndef _SALES_PERSON_H
#define _SALES_PERSON_H
#include <iostream.h>
#include "string.hh"
#include "WageEmployee.hh"

//	Derived class

class SalesPerson : public WageEmployee
{
public:
  SalesPerson (const char *, const char*);
  virtual ~SalesPerson() {};
  static os_typespec* get_os_typespec (); 
  void setCommission (float com);
  void setSales (float sales);
  float ComputePay () const;
private:
  float commission;
  float salesmade;
};

#endif
