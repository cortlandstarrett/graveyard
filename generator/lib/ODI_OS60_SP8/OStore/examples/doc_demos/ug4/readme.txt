Examples of Creating and Finding Database Root
==============================================

These two example programs illustrate how to create a database root,
associate it with an entry-point object, find the root, and retrieve
the object.  For an example of a program that uses the ObjectStore
affiliation API for cross-database pointers, see ..\ug2.

For additional information about these examples, see "ObjectStore C++
API User Guide", chapter 4.

Files in this directory are:

    README.TXT    - this file
    doall         - script that runs the whole example
    makefile      - makefile
    set_part.cpp  - application file: creates root
    get_part.cpp  - application file: finds root
    part.cpp      - definitions file
    part.hh       - header file
    schema.cpp    - schema source file

To build and run this example, first make sure your environment
variable OS_ROOTDIR is set to the path of your ObjectStore
installation.

Then you can either type 'doall' to run all the steps of this example,
or do each step separately.  When you are done with the example, type
'nmake clean' to clean up.


