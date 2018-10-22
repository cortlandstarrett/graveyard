Example of a Simple Application Using the Collections Facility
==============================================================

This example is similar to the example program in the basic_os
directory, except that this one uses ObjectStore's collections
facility so that more than one Restaurant object can be stored
in the database.  The application uses queries to access objects.

The main application (reserve) expects two command-line arguments:
the name of the restaurant and the number of persons for which the
reservation is being made.  If there are enough tables at the
restaurant with the specified name, the application confirms the
reservation by outputting the number of tables that have been
reserved; otherwise, the reservation is denied.  A utility
application (init_db) creates a database and populates a
persistently stored collection object with Restaurant objects.
Another utility (add_restaurant) allows additional Restaurant
objects to be inserted in the collection.  And yet another utility
(rlist) can be used to list all restaurants stored in the database
or just those located in the city specified as a command-line
argument.

For additional information about this example, see "Writing
ObjectStore Applications:  A Guide for the First-Time User."

Files in this directory are:

    README.TXT         - this file
    doall              - script that builds and runs the example
    makefile           - makefile
    restaurant.hh      - definition of the Restaurant class
    restaurant.cpp     - implementations
    main.cpp           - main application
    init_db.cpp        - initialization utility
    rlist.cpp          - list utility
    add_restaurant.cpp - utility for adding more restaurants

To build and run this example, first make sure your environment
variable OS_ROOTDIR is set to the path of your ObjectStore
installation.

Then you can either type 'doall' to run all the steps of this example,
or do each step separately.  When you are done with the example, type
'make clean' to clean up.

