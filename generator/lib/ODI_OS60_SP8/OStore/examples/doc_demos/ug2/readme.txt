Example of a Simple ObjectStore Application
===========================================

This example illustrates commonly used features of ObjectStore
applications.  The main application is a bookclub program that
allows the user to select a book for a reader.  The program maintains
two databases, one for information about readers and the other for
information about books.  Utility applications are included to
initialize the databases and list the reader database.  The main
application assumes that both databases have been initialized.

For additional information about this example, see "ObjectStore C++
API User Guide", chapter 2.

Files in this directory are:

    README.TXT    - this file
    doall         - script that runs the whole example
    makefile      - makefile
    main.cpp      - main application
    bookclub.cpp  - definitions
    bookclub.hh   - header file
    init_bc.cpp   - initializes databases
    list_bc.cpp   - lists readers database
    schema.cpp    - schema source file
    names         - names of readers, book titles, and authors
                    for initialization
    selection1,
    selection2,
    selection3    - files to use instead of standard output, when
                    running the main application out of doall    

To build and run this example, first make sure your environment
variable OS_ROOTDIR is set to the path of your ObjectStore
installation.

Then you can either type 'doall' to run all the steps of this example,
or do each step separately.  When you are done with the example, type
'nmake clean' to clean up.
