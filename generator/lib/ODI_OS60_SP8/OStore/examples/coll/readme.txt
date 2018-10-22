Simple Collections Example
==========================
This example shows how to create a collection in a database
and then retrieve objects from the collection.

Files in this directory are:

    README.TXT        - this file

    doall.bat         - batch file which runs the whole example

    makefile          - makefile

    schema.cc         - application database schema source file

    coll_put.cc       - collection creation C++  code
    coll_get.cc       - collection retrieval C++  code
    employee.hh       - employee C++  class definition
    part.hh           - part C++  class definition

To build and run this example, first make sure that your environment
variable OS_ROOTDIR is set to the path of your ObjectStore installation.

Then you can either

1. Type 'doall' to run all the steps of this example.

or, to do each step of this example separately, do:

1. Type 'nmake' to make the coll_put and coll_get executables.

2. Type 'coll_put' to run the coll_put executable.  This creates
   the coll.db database and populates it with a collection.

3. Type 'coll_get' to run the coll_get executable.  This opens
   the database, retrieves and prints the contents of the collection.

When you are done with this example, you may type
'nmake clean' to clean up.

