Extended Allocator Example
==========================

This example shows how to build an application that uses 
ObjectStore's Extended Allocators for storing objects
persistently in an ObjectStore database.

The example has two separate steps:

   - Setup,  where the Allocator & Rules databases are setup.
     In a production environment, these databases are setup by the
     Database Administrator. 

   - Actual allocation, using the Allocators & Rules defined in the
     previous step.

Files in this directory are:

    README.TXT        - this file
    doall             - script which runs the whole example
    makefile          - makefile
    schema.cc         - application database schema source file
    Employee.hh       - Employee C++ class definition
    Employee.cc       - Employee C++ methods defined.
    Manager.hh	      - Manager derived class definition
    Manager.cc	      - Manager class methods defined
    WageEmployee.hh   - WageEmployee derived class definition
    WageEmployee.cc   - WageEmployee class methods defined
    SalesPerson.hh    - SalesPerson derived class definition
    SalesPerson.cc    - SalesPerson class methods defined
    string.hh         - string class definition
    string.cc	      - string class methods defined
    populate.cc	      - Defines functions to populate the Rules & Allocator
		        databases.
    usr_example.cc    - the application that uses extended allocators.
    dba_example.cc    - the application that creates allocator & rules 
		        databases.

To build and run this example, first make sure that your environment
variable OS_ROOTDIR is set to the path of your ObjectStore installation.

Then you can either

1. Type 'doall' to run all the steps of this example.

or, 

1. Type  'make' to make the  usr_example & dba_example executables.

2. Type 'dba_example' first to run the dba example executable. This 
   creates the allocator & rules databases which are needed in the
   second step.

3. Type 'usr_example' to run the application that allocates Employee 
   objects using the Extended allocators and prints info about the 
   Employees from the employee database.

When you are done with this example, you may type
 'make clean' to clean up.





