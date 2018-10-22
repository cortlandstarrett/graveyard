Simple Inverse Relationship Test Example
========================================
This example shows how to create inverse data members and
relationships between members in a database.

Files in this directory are:

    README.TXT        - this file

    doall.bat         - batch file which runs the whole example

    makefile          - makefile

    schema.cc         - application database schema source file

    coll_put.cc       - collection creation C++  code
    part.cc           - collection retrieval C++  code
    invtest.cc        - inverse relationship test code
    employee.hh       - employee C++  class definition
    part.hh           - part C++  class definition

To build and run this example, first make sure that your environment
variable OS_ROOTDIR is set to the path of your ObjectStore installation.

Then you can either

1. Type 'doall' to run all the steps of this example.

or, to do each step of this example separately, do:

1. Type 'nmake' to make the coll_put and invtest executables.

2. Type 'coll_put' to run the coll_put executable.  This creates
   the invtest.db database and populates it with a collection and
   relationship objects.

3. Type 'invtest' to run the inventory test in the databases.
   Note that it only makes sense to run this program once.  After its
   first execution there is no relationship to manipulate.

When you are done with this example, you may type
'nmake clean' to clean up.

