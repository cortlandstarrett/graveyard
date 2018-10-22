#include <iostream.h>
#include <ostore/ostore.hh>
#include <ostore/coll.hh>
#include <ostore/allocators/osalloc.hh>
#include <ostore/allocators/afspecials.cc>
#include "string.h"
#include "Employee.hh"
#include "WageEmployee.hh"
#include "SalesPerson.hh"
#include "Manager.hh"
#include "dbname.h"

typedef os_List<Employee *>  EmployeeList;

int main(int argc, void * argv[])
{

  EmployeeList * EList;
  os_database *db;

  objectstore::initialize();
  os_collection::initialize();

  OS_ESTABLISH_FAULT_HANDLER

  OS_BEGIN_TXN(tx1, 0, os_transaction::update)

    os_extended_allocator* p_ext_alloc = 0;

    os_index_key( os_string, string_rank, string_hash ) ;

    os_set_db::set_rule_db( rules_db_name, "Rules" ) ;
    os_set_db::set_alloc_db( allocator_db_name,"Allocators" );

    os_allocation_context emp_context ("EmployeeList");
    os_Allocator<EmployeeList> emp_alloc;
    emp_alloc.bind();
    p_ext_alloc = emp_alloc.get_extended_allocator() ;
    os_string database_str = (p_ext_alloc->get_trait(DB_ALLOC_PATHNAME_TRAIT))->get();

    TIX_HANDLE( err_database_not_found )
      db = os_database::open(database_str, 0, 0666);
    TIX_EXCEPTION
    {
      cout << "Error: Database " << database_str <<  " does not exist" << endl;
      return 1;
    }
    TIX_END_HANDLE ;

    EList = new (emp_alloc) EmployeeList;

    os_allocation_context we_context ("WageEmployee");
    os_Allocator<WageEmployee> we_alloc;
    we_alloc.bind();
    p_ext_alloc = we_alloc.get_extended_allocator() ;

    WageEmployee * we = new (we_alloc)

                           WageEmployee ("Bill Shapiro", "Administration");
    we->setHours(40.0);
    we->setWage (15.00);

    EList->insert(we);

    char* context_value ;
    char* context_name = (char*)"Employee" ;
    putenv( (char*)"Employee=SalesPerson" );
    context_value = getenv("Employee") ;
    os_allocation_context sp_context(context_name, context_value) ;
    os_Allocator<SalesPerson> sp_alloc;
    sp_alloc.bind();

    SalesPerson * sp = new (sp_alloc)

                            SalesPerson ("John Smith", "Sales");
    sp->setHours(40.0);
    sp->setWage (15.00);
    sp->setCommission(0.05);
    sp->setSales(2000.0);

    EList->insert(sp);

    os_database_root * emp_root = db->create_root("Employees");
    emp_root->set_value(EList, EmployeeList::get_os_typespec());

    db->close();

    os_allocation_context manager_ctx("Employee", "Manager") ;
    os_Allocator<Manager> manager_alloc ;

    manager_alloc.bind() ;

    TIX_HANDLE( err_database_not_found )
      db = os_database::open(example_db_name, 0, 0666);
    TIX_EXCEPTION
    {
      cout << "Error: Database " << example_db_name <<  " does not exist" << endl;
      return 1;
    }
    TIX_END_HANDLE ;

    Manager * M = new (manager_alloc) Manager ("John Rose", "Engineering");

    M->setSalary(1500.00);
    os_database_root * m_root = db->create_root("Managers");
    m_root->set_value(M, Manager::get_os_typespec());
    db->close();

    OS_END_TXN(tx1)

  OS_BEGIN_TXN(tx3, 0, os_transaction::read_only)

    EmployeeList *eptr;

    TIX_HANDLE( err_database_not_found )
      db = os_database::open(example_db_name, 0, 0666);
    TIX_EXCEPTION
    {
      cout << "Error: Database " << example_db_name <<  " does not exist" << endl;
      return 1;
    }
    TIX_END_HANDLE ;

    eptr = (EmployeeList *) db->find_root("Employees")->get_value(EmployeeList::get_os_typespec());

    cout << endl << "******  Output ****** " << endl;

    os_Cursor<Employee *> cursor(*eptr);

    for (Employee * ptr = cursor.first(); cursor.more(); ptr = cursor.next())
      cout << *ptr;

    Employee * ptr1 = (Employee *)db->find_root("Managers")->get_value(Manager::get_os_typespec());
      cout << *ptr1;

    cout << endl;

    db->close();

  OS_END_TXN(tx3)

  OS_END_FAULT_HANDLER
  objectstore::shutdown();
  return 0;
}

