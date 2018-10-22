Examples of Schema Evolution
============================

These examples illustrate two ways to perform schema evolution:

   * Using the ossevol utility with a post-processing application 
   * Using a schema evolution application

For more information about the examples, see "ObjectStore C++ API
User Guide", chapter 9.

Files in this directory are:

    README.TXT        - this file
    doall             - script that builds and runs the examples.
                        Note:  This script invokes ..\ug5\doall    
    makefile          - makefile
    main.cpp          - source file for the revised get_note program
                        (see NOTE below)
    note.cpp          - definitions file
    note.hh            - header file
    list.cpp          - lists database
    schema.cpp        - schema source file
    post_process.cpp  - program to perform post processing on
                        database evolved with ossevol
    evolve_schema.cpp - program to perform schema evolution

NOTE:  The source files main.cpp, note.cpp, note.h, and list.cpp
are edited versions of the source files in ..\ug5.  The change is to
add another member to the persistently stored class "note".  This
change requires that a database created by the program in ..\ug5
undergo schema evolution to make it accessible by the version of the
program in this directory.

To build and run this example, first make sure your environment
variable OS_ROOTDIR is set to the path of your ObjectStore
installation.

Then you can either type 'doall' to run all the steps of this example,
or do each step separately.  When you are done with the example, type
'nmake clean' to clean up.