Hello World 2 Example
=====================
This example is a standard 'hello world' program enhanced
to store and increment an integer counter in an ObjectStore
database.

Files in this directory are:

    README.TXT        - this file

    doall.bat         - batch file which runs the whole example

    makefile          - makefile

    schema.cc         - application database schema source file

    cntinit.cc        - count initialization C++  code
    hello2.cc         - hello world 2 C++  code

To build and run this example, first make sure that your environment
variable OS_ROOTDIR is set to the path of your ObjectStore installation.

Then you can either

1. Type 'doall' to run all the steps of this example.

   Note the ObjectStore Schema Generator (ossg) will display a warning
   indicating that there were no types marked for inclusion in the
   generated schema.  For the purposes of this example this warning
   can be safely ignored.

or, to do each step of this example separately, do:

1. Type 'nmake' to make the cntinit and hello2 executables.

   Note the ObjectStore Schema Generator (ossg) will display a warning
   indicating that there were no types marked for inclusion in the
   generated schema.  For the purposes of this example this warning
   can be safely ignored.

2. Type 'cntinit' to run the cntinit executable.  This creates
   the hello2.db ObjectStore database, initializes a counter
   in the database to zero and then displays the value of the counter.

3. Type 'hello2' to run the hello2 executable.  This increments
   the counter in the hello2.db database and displays the new
   value of the counter.

4. Run hello2 several times, watching the counter in the
   database increment.

When you are done with this example, you may type
'nmake clean' to clean up.

