Simple Dictionary Example
=========================
This example shows how to create and use ObjectStore Dictionary
class.

Files in this directory are:

    README.TXT        - this file

    doall.bat         - batch file which runs the whole example

    makefile          - makefile

    schema.cc         - application database schema source file

    main.cc           - Dictionary creation/usage C++ code
    dnary.hh          - student, course, and grade C++ definition
    dnary.cc          - student, course, and grade C++ implementation

To build and run this example, first make sure that your environment
variable OS_ROOTDIR is set to the path of your ObjectStore installation.

Then you can either

1. Type 'doall' to run all the steps of this example.

or, to do each step of this example separately, do:

1. Type 'nmake' to make the dict executable.

2. Type 'dict' to run the dict executable.

When you are done with this example, you may type
'nmake clean' to clean up.

