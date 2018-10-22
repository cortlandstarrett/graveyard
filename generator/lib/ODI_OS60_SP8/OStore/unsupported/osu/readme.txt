
This unsupported library is commonly referred to as OSU MONITOR.  This
code base provides a simplified means to collect performance
information from an ObjectStore application.  It uses documented and
undocumented APIs to write events from transaction hooks, pages hooks,
realtime counters, N counters, and server stat calls to an output file
for post processing and analysis.

The code can be built into a library, linked with your application,
and deployed without any runtime overheads.  The only overheads are
incurred if you activate the collection of the events.  This is done
via the setting of an environment variable OSU_MONITOR before the
running of the application.

To build the library, use the appropriate makefile in the src directory.

To compile into your application, you'll need to:

add the following line of code after you initialize objectstore.

   osu_monitor::initialize();

If you are using multiple sessions, then include this after joining
a session just created, or intialize for all sessions at once via

   osu_monitor::initialize_all();

The public include file that must be included to find the signature of
the above functions is:

   #include <osu/monitor.hh>

You'll need to include $OS_ROOTDIR/unsupported/osu/include in your
include path or as a -I option.

To link you'll need to include the osumon library on your link line
followed by the dbutil library from ObjectStore and the socket library
for your system.  The source code has some experimental code for
writing to a socket verses writing to a file - thus the need to link
with the socket library.  If you don't want this feature you can
remove it from the osu_stream.cc file (class osu_sstream).

In order to specify to use a socket use the environment variable
(before starting your application).

 OSU_MONITOR_URL=tcp:localhost:1022

replace localhost with name of host to connect to and 1022 with port
number.

If OSU_MONITOR_URL is not specified the data collected will be written
to osu_monitor_<pid>.txt  where <pid> is the process id.

The amount of data collected is dependent upon the setting of the
OSU_MONITOR variable.  The variable is set to a series of characters
where a particular character is used to collect a unique piece of
information.  Collection is done either at transaction boundary times
or within page hooks.  The typical settings will only collect at
transaction boundary times.  Use the following symbols to collection
the associated information:

   T - realTime counters             (collected at end of txn)
   M - Meters from server status     (collected at end of txn)
   N - N counters                    (collected at end of txn)
   A - page fault Active             (collected at page fault
				      active hook)
   W - commit (Write) page           (collected at page commit hook)
   C - Create page                   (collected at page create hook)
   D - Deadlock                      (collected at deadlock hook)
   F - Fault page                    (collected at page fault hook)
   R - fetch (Read) page             (collected at page fetch hook)
   S - Swizzle (reloc)               (collected on all page relocation
                                      hooks)
   E - Evict (return) page           (collected at return pages hook)
   U - Upgrade page                  (collected at upgrade page hook)

If OSU_MONITOR is set to any value then the transaction hooks are
activated and basic CPU usage and wallclock time is collected at:

   . after transaction begin
   . before transaction commit
   . after transaction commit
   . before transaction abort
   . after transaction abort
   . before transaction retry

Example settings:

   OSU_MONITOR=TN  - collect CPU, wallclock, realtime timing and N counters
   OSU_MONITOR=TMN - add server meter information (this adds a call to
                     the server)
   OSU_MONITOR=TMNAWCDFRSEU - everything, a lot of data will be
                              written

The data is written in ASCII format.  This enables the user to write
scripts to help analysis the output.  Some example scripts are
provided in the scripts directory.  The exact format of the events
written currently is not documented but, can be understood by
reviewing the code or the scripts.

As this library is unsupported, any questions regarding it's use
should be forwarded to ostore discussion list
(ostore-discussion@objectdesign.com).  For help in tuning your
application if you are experiencing performance issues contact Object
Design Professional Services.

