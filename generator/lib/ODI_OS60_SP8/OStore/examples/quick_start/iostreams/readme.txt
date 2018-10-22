Example of a Simple Application Using iostreams
===============================================

This example and the example in the basic_os directory are
functionally similar:  they process requests for dinner
reservations at a restaurant.  However, they have different
implementations.  This example uses iostreams, and the example in
the basic_os directory uses ObjectStore.  Both examples are
intended to illustrate how to implement ObjectStore by
highlighting the differences from a non-ObjectStore implementation.

The main application (reserve) expects an integer value as the
command-line argument, representing the number of persons for which
the reservation is being made.  If there are enough tables for the
specified number, the application confirms the reservation by
outputting the number of tables that have been reserved; otherwise,
the reservation is denied.  A utility application (init_db) creates
a streams file with information specifed on the command line -- the
name of the restaurant and the number of available tables.  Each
time the main application is invoked, this file is read and (when
a reservation is confirmed) updated.

For additional information about this example, see "Writing
ObjectStore Applications:  A Guide for the First-Time User."

Files in this directory are:

    README.TXT     - this file
    doall          - script that builds and runs the example
    makefile       - makefile
    restaurant.hh  - definition of the Restaurant class
    restaurant.cpp - implementations
    main.cpp       - main application
    init_db.cpp    - initialization utility

To build and run this example, first make sure your environment
variable OS_ROOTDIR is set to the path of your ObjectStore
installation.

Then you can either type 'doall' to run all the steps of this example,
or do each step separately.  When you are done with the example, type
'make clean' to clean up.

