Examples of TIX Exception Handling Facility
========================

These examples illustrate the TIX exception handling facility.  For
additional information about these examples, see "ObjectStore C++
API User Guide", chapter 6.

Files in this directory are:

    README.TXT    - this file
    doall         - script that runs the whole example
    makefile      - makefile
    tix_nest.cpp  - nested TIX exception handler
    no_hndlr.cpp  - handles exceptions outside TIX handler
    make_dbs.cpp  - creates two databases used by the examples

To build and run this example, first make sure your environment
variable OS_ROOTDIR is set to the path of your ObjectStore
installation.

Then you can either type 'doall' to run all the steps of this example,
or do each step separately.  When you are done with the example, type
'nmake clean' to clean up.

NOTE: Normal execution of this example will produce warning and/or
error messages.

