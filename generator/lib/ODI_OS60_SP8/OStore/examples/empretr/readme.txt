Employee Retrieval Example
==========================
This example shows how to store and retrieve objects of your
own C++  types in an ObjectStore database.

Files in this directory are:

    README.TXT        - this file

    doall.bat         - batch file which runs the whole example

    makefile          - makefile

    schema.cc         - application database schema source file

    employee.hh       - employee C++  class definition
    empretr.cc        - employee id retrieval C++  code
    part.hh           - part C++  class definition
    partinit.cc       - part initialization C++  code

To build and run this example, first make sure that your environment
variable OS_ROOTDIR is set to the path of your ObjectStore installation.

Then you can either

1. Type 'doall' to run all the steps of this example.

or, to do each step of this example separately, do:

1. Type 'nmake' to make the partinit and empretr executables.

2. Type 'partinit' to run the partinit executable.  This creates
   the empretr.db ObjectStore database and stores employee and
   part objects in the database.

3. Type 'empretr' to run the empretr executable.  This retrieves
   and prints the id of the engineer from the database.

When you are done with this example, you may type
'nmake clean' to clean up.

