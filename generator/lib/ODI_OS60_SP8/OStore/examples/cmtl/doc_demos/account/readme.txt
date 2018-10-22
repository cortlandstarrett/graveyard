This directory contains the source files, makefile, and a doall.bat script
to build and run two simple bank-account applications (init_db and account)
that illustrate basic features of CMTL.  The init_db application creates a
database and populates it with a collection of Account objects.  The main
application (account) enables the user to access the Account objects (for
example, make a deposit or withdraw).  You must run init_db before account.

The files in this directory include:

    account.cpp - implements the Account class
    account.h - include files, defines, and definition of Account class
    init_db.cpp - application to create database and populate it
    main.cpp - main application to perform different account operations
    schema_src.cpp - schema source file
    account.xml - configuration information in XML format
    makefile - builds both applications
    doall.bat - builds and runs both applications
    readme.txt - you're reading it

A note on main.cpp:  As noted in the "CMTL Guide and Reference", this file
contains both static and dynamic versions of a virtual transaction; see the
definition of the function withdraw().  The source code includes two
versions of this function, one using a static transaction and the other
using a dynamic transaction.  To use the dynamic version, you'll need to
uncomment it and comment out the other version.  Functionally, they are
both the same.

