Galaxy 3.0 Multithreaded Samples
--------------------------------

The samples in this directory are intended to demonstrate the use of
three Galaxy managers: vthread, vmutex, and vcondition.


pc
--

This program illustrates basic use of threads, mutexes, and condition
variables in Galaxy 3.0. It is the classic producer/consumer
problem. There are some number of "producers" that create
elements. The producers want to place their elements in a queue, or
bounded buffer, so that they may be picked up by "consumers" and used
somehow. Producers cannot add items to a full buffer, however, and
consumers cannot pull elements from an empty buffer. This program
shows a graphical representation of the producer consumer problem with
5 producers, 5 consumers, and a buffer large enough for 6 elements. 

A single dialog will be displayed. On the left side are the 5
producers with the 5 consumers on the right. In the middle is the
buffer. The Period spinner on each thread represents the delay time
between producing or consuming, in seconds. The Thread Priority
spinner is the relative priority of each thread, which is a value
between 1 and 10. The button labled Start for each thread is used to
start or stop a thread. Its label will change to Stop when a thread is
running.

To end the program, select Quit from the File menu.


pc2
---

This program does the exact same thing as pc above. Only the
implementation is different. This sample demonstrates subclassing the
default vthread class to provide a much cleaner method of using
threads in Galaxy.


worker
------

This program demonstrates how to create a thread to perform some long
computation or other task seperate from an applications GUI. This
allows the GUI to continue to process events normally. The sample
shows a basic way to send events from the worker thread back to the
GUI thread to update GUI items in a thread-safe way.

A single dialog will be displayed with a single button labled "Start
Worker". Press the Start Worker button and a worker status dialog will
appear. A seperate thread will send events back to the GUI thread to
update the status message in the dialog. Either let the thread run to
completion (takes about 10 seconds) or press the Cancel button to stop
the thread eairly.

To end the program, select Quit from the File menu.
