#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/coll/dict_pt.hh>
#include <ostore/manschem.hh>

#include "string.hh"
#include "Employee.hh"
#include "WageEmployee.hh"
#include "SalesPerson.hh"
#include "Manager.hh"

OS_MARK_SCHEMA_TYPE(Employee)
OS_MARK_SCHEMA_TYPE(WageEmployee)
OS_MARK_SCHEMA_TYPE(String)
OS_MARK_SCHEMA_TYPE(SalesPerson)
OS_MARK_SCHEMA_TYPE(Manager)
OS_MARK_SCHEMA_TYPE( os_List< Employee * > ) ;

