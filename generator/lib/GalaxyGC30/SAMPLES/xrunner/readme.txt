
xruntest 
-------------------

xruntest is a simple and not particularly interesting application 
whose sole purpose is to illustrate how one establishes a connection from a 
Galaxy application to the XRunner/WinRunner automated testing tool from 
Mercury Interactive Corp.

You must have XRunner/WinRunner installed at your site for this program to be
of any use.  

For XRunner: you will need Mercury's interface library, libmic_if.a (or its 
shared library equivalent) for the program to link.  You can place 
libmic_if.a in the "lib" directory of this release, in the current directory 
or in a place that will be found by your library load path.  If you copy it, 
be sure to run "ranlib libmic_if.a" on the copy.

For WinRunner: you will need Mercury's interface library, mic_if.lib, you can 
place mic_if.lib in the current directory or you include the derectory where 
it is located to the LIB environment variable. Make sure that the 
system can find mic_if.dll from WinRunner when you run this sample.

The program puts up a dialog containing a good assortment of various Galaxy 
user interface items.  Assuming XRunner/WinRunner is running at the time, the 
program demonstrates the recording and playback capabilities of 
XRunner/WinRunner as well as the specifics of how Galaxy interacts with 
XRunner/WinRunner.

Important note: In the new 3.0 scheme, you must specify a testing library
preference or else the sample won't do Context Sensitive recording.  It is
most convenient to specify this on the command line, such as:

xruntest -vtestlib vmicrun1d.dll

where "vtestlib" is the name of the Galaxy preference, and the following
argument is the desired DLL (shared object, on Unix) to test with (currently
only one testing library, the WinRunner/XRunner integration is supported,
in both debug and non-debug flavors).  Note that this DLL is loaded as the
program is running, so the linker doesn't need to resolve any references
to it when building the sample.  Also, as a result of this scheme, you
may leave your call to vtestStartup() in your code, even when not testing.
If the testing library preference is omitted, the call is essentially a no-op.
