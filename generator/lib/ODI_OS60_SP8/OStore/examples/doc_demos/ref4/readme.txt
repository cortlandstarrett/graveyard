Examples of ObjectStore Macros
==============================

These examples illustrate some of the ObjectStore macros.  For
additional information about these examples, see "ObjectStore C++
API Reference", chapter 4.

Files in this directory are:

    README.TXT       - this file
    doall            - script that runs the whole example
    makefile         - makefile
    def_exc.cpp      - creates a user-defined TIX exception
    tix_example.cpp  - establishes a TIX exception handler
    txn_example.cpp  - establishes a lexical transaction

To build and run these examples, first make sure your environment
variable OS_ROOTDIR is set to the path of your ObjectStore
installation.

Then you can either type 'doall' to run all the steps of this example,
or do each step separately.  When you are done with the example, type
'nmake clean' to clean up.

NOTE: Normal execution of this example will produce warning and/or
error messages.
