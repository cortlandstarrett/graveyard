Sessions Example 
================ 
This example is a demonstrates the session feature of ObjectStore.  A
description of this feature and example can be found in Chapter 3,
"Multithread and Multisession Applications" of the Advanced C++ API User
Guide.

Files in this directory are:

    README.TXT        - this file

    doall             - batch file which runs the whole example

    makefile          - makefile

    app_server.cpp    - main program demonstrating a simple application server

    app_server.hh     - class declarations for app_server.cpp

    error.hh          - simple error reporting abstaction

    osint.cpp         - operating specific portability layer for this
                        example. Contains abstractions for Thread, Mutex, and
                        Time

    osint.hh          - class declarations for Thread, Mutex and Time

    queue.cpp         - simple request queue implementation

    queue.hh          - request queue declarations

    request.hh        - request class declaration and definition

    value_list.hh     - class declarations and definitions for passing value
                        lists 

To build and run this example, first make sure that your environment
variable OS_ROOTDIR is set to the path of your ObjectStore installation.

Then you can

1. Type 'nmake' on Windows or 'make' on Unix to build the app_server
executable.

2. Type 'app_server appserver.db 5 10 1 3000'

   This command will start an app_server application with 10 (arg3) threads
   sharing a MVCC transaction and 1 update thread (arg4) which is also using
   its own transaction.  The latency before the MVCC transaction is refreshed
   is 5 seconds (arg 2).  The number of simultated requests is 3000 (arg5).

When you are done with this example, you may type
'nmake clean' on Windows or 'make clean' on Unix to clean up.

