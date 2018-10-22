Example of Notifications
========================

This example illustrates how to send and receive notifications.
For more information about the example, see "ObjectStore C++ API
User Guide", chapter 8.

Note:  Running this program requires two processes and therefore
will not work under ObjectStore/Single.  However, the
%OS_ROOTDIR%\examples\notify directory includes a similar example
designed to run under ObjectStore/Single, using multiple sessions.

Files in this directory are:

    README.TXT    - this file
    doall         - script that runs the whole example
    makefile      - makefile
    notify_d.cpp  - notifications example program
    doze.cpp      - a version of the UNIX sleep command

To build and run this example, first make sure your environment
variable OS_ROOTDIR is set to the path of your ObjectStore
installation.

Then you can either type 'doall' to run all the steps of this example,
or do each step separately.  When you are done with the example, type
'nmake clean' to clean up.


