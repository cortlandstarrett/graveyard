#include <iostream.h>
#include <ostore/allocators/afalloc.cc>
#include <ostore/allocators/afcontxt.hh>
#include <ostore/allocators/afstring.hh>
#include "Employee.hh"

Employee::Employee(const char * nm, const char * dep)
{
  os_allocation_context str_ctx("String") ;
  os_Allocator<String> str_alloc ;
  str_alloc.bind() ;

  Name = new (str_alloc) String(nm);
  Dept = new (str_alloc) String(dep);

}

Employee::~Employee ()
{
  delete Name;
  delete Dept;
}

const char * Employee::getName()
{
  return Name->getString();
}

const char * Employee::getDept()
{
  return Dept->getString();
}

ostream& operator<< (ostream& os, Employee& E)
{
  return os << "Name: " << E.getName() << "  "
	    << " Dept: " << E.getDept() << "  "
	    << " Salary: " << E.ComputePay()
	    << endl;
}

