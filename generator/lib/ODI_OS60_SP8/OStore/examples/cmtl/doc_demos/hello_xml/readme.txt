This directory contains the source files for a very simple
application that exercises some of the basic features of
CMTL, including the cache pool manager, cache pool, caches,
virtual transactions, and basic transaction contexts.  The
application knows nothing about application servers and
therefore does nothing with global transactions.

The files in this directory are:

doall - Script to build and run the example
hello.cpp - Source code for the example.
hello.h - header file.
hello.xml - cache pool manager configuration file.
main.cpp - main function for the example.
makefile - used by the system make utility.
readme.txt - This file


What the Example Does
---------------------

The application does the following:

1. Configures and creates a cache pool manager with a cache
   pool that consists of an update cache and an MVCC cache.
   The application uses an XML-based configuration file to
   configure the cache pool manager.

2. Creates a database.

3. Sets up a logical database name mapping so that the
   application can reference the database by its logical name
   rather than its physical name.

4. Performs a virtual transaction that creates a database
   root and establishes a logical root mapping to the root
   that enables access to the root by a logical name.

5. Performs a read-only virtual transaction that reads the
   root value.

6. Performs an update virtual transaction to set the root to
   another value.

7. Performs another read-only virtual transaction to read the
   new root value.

The application uses the OS_BEGIN_VT and OS_END_VT macros to
set up lexical transactions.

Building and Executing the Program
----------------------------------

You can use the doall.bat file to build and run the application
by entering "doall" at the prompt.