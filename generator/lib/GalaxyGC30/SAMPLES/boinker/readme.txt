
boinker Help Reference                                          December 1994
(c) Copyright 1994-95 Visix Software Inc.
All Rights Reserved.
----------------------------------------------------------------------------

Overview:
========

    The boinker sample was written to as a demo for 2 of the sessions
    presented at the Galaxy Developer Conference 1994.

    First the "ttask" classes where written for the "Object-Oriented
    Design w/ the Class Manager." These classes are not UI objects yet
    they take advantage of the object-based paradigm provided by the class
    manager. Because Galaxy/C++ has no class manager, the reasoning for
    these classes is a bit out-of-place. however, the C++ implementation
    does demonstrate how one might implement the C++ equivalent of
    "vclassVARIABLEs" and module initialization.

    Next, we use several of the guidelines presented in the
    Tips&Techniques session "Exceptions, Debugging, & Leaks" to show how
    to create your own exception subclasses, use the various vdebug macros
    to obtain argument/result-value/pre-post-invariant checking, use
    "debug" versions of methods to implement caller tracing, generate
    exceptions, and handle misc kinds of exceptions. In addition to the
    task classes, the C version has a dialogitem subclass, "Boinkitem";
    the C++ verison has "TBoinkitem" and "TOffscreenItem".

    The application specific code demonstrates how to install a top level
    exception handler that tries to exit the application a bit more
    gracefully in the event of an uncaught exception.

    So what does the application actually do? Well it opens a window and
    scribbles the word "Boink!" all over it!!! But first, it uses the task
    classes to implement a non-blocking startup application sequence,
    complete with status-showing splash screen an' all. Several options
    have been included to spice up the sample a bit; use the -help option
    to get a complete listing of the application's preferences.


Bug Reports, etc.
================

    Please send any bug reports, enhancement requests, etc. to:

                    galaxy-bugs@visix.com

    Use "boinker" in the Component field of the problem report.


Running the sample:
==================

    * Make the boinker executable

    * Run boinker. In environments that support command line arguments 
      there are several options you can specify. Here is a summary:

        -help           : shows help summary window (this does *NOT* use
                          the galaxy help server)
        -noteehee       : skip the cutsie startup messages
        -randomgeo      : randomize scale and rotation for each boink
        -norandomcolors : cycle colors "in order" r->g->b
        -str <STR>      : use <STR> instead of "BOiNk!"
        -hunk <N>       : delay for <N> seconds between each progress
                          message

    * See the boinker splash/initialization-progress window. there are
      a couple of things worth noting: 
            o the splash window returns to the event loop st. the
              window can be updated/moved/etc.
            o the window also serves as an initialization progress
              indicator (see the messages flashing by...)

      Assuming you didn't used the "-noteehee" options, the sample cycles
      through some er, "interesting" messages, burning the CPU for a few 
      seconds between each...

    * Warning: closing the splash window aborts boinker. this is how it
      was designed to work...

    * The main boinker window will open. The misc. boink items will 
      begin boinking...and there you have it...the entire function of 
      this sample.

    * To clear the accumlating boink canvas select Edit/Clear. To clear
      the canvas after each boink, turn off the "Accumulate Strings"
      toggle.

    * To change the string being drawn for each boink, either select
      a predefined string from the Strings menu, or use the Edit/Preferences
      selection to setup a default.

    * To randomize the geometry of the each string as it's boinked, use
      the Edit/Preferences selection and turn on the "Random Geometry"
      toggle.

    * The change the font of the boink string, use th Edit/Preferences 
      selection and select a new font from the standard galaxy font
      chooza.

    * To quit boinker, either select File/Quit or close the main boinker
      window
    
    * And finally, there are no hidden cookies in this sample...


Known Problems:
===============

	* (v2.5) vdraw sometimes has problems rendering rotated fonts. this
	  is seen when the "Inverse matrix requires non-zero determinant"
	  exception gets thrown during a draw operation.

------------------------------------------------------------------------------
History:

$Log: readme,v $
# Revision 1.3  1995/05/18  22:10:15  simone
# a. bumped copyright notice
# b. added section "Known Bugs" to note the "inverse matrix
#    exception" that crops from time to time
#
# Revision 1.2  1994/12/14  13:52:59  simone
# a. fillin
#

------------------------------------------------------------------------------

/*
 * Local Variables:
 * tab-stop-list:(4 8 12 16 20 24 28 32 36 40 44 48 52 56 64 72 80 88 96 104)
 * tab-width:4
 * indent-tabs-mode:t
 * truncate-lines:t
 * End:
 */


