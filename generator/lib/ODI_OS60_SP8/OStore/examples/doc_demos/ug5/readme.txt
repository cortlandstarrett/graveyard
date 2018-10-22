Examples of Transactions
========================

These examples illustrate lexical, dynamic, and nested transactions.
The example of a nested transaction also shows how to construct an
abort-only transaction.  For additional information about the
examples, see "ObjectStore C++ API User Guide", chapter 5.

Files in this directory are:

    README.TXT    - this file
    doall         - script that runs the whole example
    makefile      - makefile
    main.cpp      - lexical transaction
    note.cpp      - definitions file
    note.hh       - header file
    dyn_txn.cpp   - dynamic transaction
    txn_nest.cpp  - nested transaction
    list.cpp      - lists database
    schema.cpp    - schema source file
    note1,
    note2,
    note3         - files to use instead of standard output, when
                    running main application from doall script

To build and run this example, first make sure your environment
variable OS_ROOTDIR is set to the path of your ObjectStore
installation.

Then you can either type 'doall' to run all the steps of this example,
or do each step separately.  When you are done with the example, type
'nmake clean' to clean up.

